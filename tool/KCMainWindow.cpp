#include "KCMainWindow.h"
#include "ui_KCMainWindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QSettings>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>
#include "KCShip.h"
#include "KCShipMaster.h"
#include "KCDock.h"
#include "KCMacUtils.h"
#include "KCUtil.h"

KCMainWindow::KCMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::KCMainWindow),
	apiLinkDialogOpen(false)
{
	ui->setupUi(this);
	
	this->_setupClient();
	this->_setupTrayIcon();
	this->_setupUI();
	
	// Make a timer that updates the dock timers, with a 1sec interval
	connect(&timerUpdateTimer, SIGNAL(timeout()), this, SLOT(updateTimers()));
	timerUpdateTimer.start(1000);
	
	// Set the Fleets page regardless of what the UI file says.
	// (This saves me from accidentally releasing a version with the wrong
	// start page due to me editing another one right beforehand)
	this->on_actionFleets_triggered();
}

KCMainWindow::~KCMainWindow()
{
	delete ui;
}

void KCMainWindow::_setupTrayIcon()
{
	// Create the Tray Icon
	trayIcon = new QSystemTrayIcon(QIcon(":/KanColleTool.png"), this);
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
			this, SLOT(onTrayIconActivated(QSystemTrayIcon::ActivationReason)));
	trayIcon->show();
	
	// Set up the menu for it, but not if we're on a Mac.
	// On Mac, it's more convenient to have a click bring up the main window
	// (since left-click also brings up the menu there)
#ifndef __APPLE__
	trayMenu = new QMenu("KanColleTool", this);
	trayMenu->addAction("Show", this, SLOT(showApplication()));
	trayMenu->addAction("Exit", qApp, SLOT(quit()));
	trayIcon->setContextMenu(this->trayMenu);
#endif
}

void KCMainWindow::_setupUI()
{
	// Right-align some items on the toolbar
	QWidget *toolbarSpacer = new QWidget();
	toolbarSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	ui->toolBar->insertWidget(ui->actionRefresh, toolbarSpacer);
	
	// Set up the Fleets page
	{
		// Unset the min height; it glitches stuff up
		ui->fleetsTabBar->setMinimumHeight(0);
		
		// Add four tabs
		ui->fleetsTabBar->addTab("Fleet 1");
		ui->fleetsTabBar->addTab("Fleet 2");
		ui->fleetsTabBar->addTab("Fleet 3");
		ui->fleetsTabBar->addTab("Fleet 4");
	}
	
	// Set up the Constructions page
	{
		// Listen for clicks on the spoiler buttons to update the UI
		connect(ui->constructionSpoil1, SIGNAL(toggled(bool)), this, SLOT(updateConstructionsPage()));
		connect(ui->constructionSpoil2, SIGNAL(toggled(bool)), this, SLOT(updateConstructionsPage()));
		connect(ui->constructionSpoil3, SIGNAL(toggled(bool)), this, SLOT(updateConstructionsPage()));
		connect(ui->constructionSpoil4, SIGNAL(toggled(bool)), this, SLOT(updateConstructionsPage()));
	}
	
	// On Mac, make the window join all spaces
	// (why isn't there a Qt call for this...)
#ifdef __APPLE__
	macSetWindowOnAllWorkspaces(this);
#endif
}

void KCMainWindow::_setupClient()
{
	client = new KCClient(this);
	
	connect(client, SIGNAL(credentialsGained()), this, SLOT(onCredentialsGained()));
	connect(client, SIGNAL(receivedMasterShips()), this, SLOT(onReceivedMasterShips()));
	connect(client, SIGNAL(receivedPlayerShips()), this, SLOT(onReceivedPlayerShips()));
	connect(client, SIGNAL(receivedPlayerFleets()), this, SLOT(onReceivedPlayerFleets()));
	connect(client, SIGNAL(receivedPlayerRepairs()), this, SLOT(onReceivedPlayerRepairs()));
	connect(client, SIGNAL(receivedPlayerConstructions()), this, SLOT(onReceivedPlayerConstructions()));
	connect(client, SIGNAL(requestError(KCClient::ErrorCode)), this, SLOT(onRequestError(KCClient::ErrorCode)));
	connect(client, SIGNAL(dockCompleted(KCDock *)), this, SLOT(onDockCompleted(KCDock *)));
	
	if(!client->hasCredentials())
	{
		this->askForAPILink();
		
		// Quit if the user pressed Cancel, instead of erroring out
		if(!client->hasCredentials())
			qApp->quit();
	}
	else this->onCredentialsGained();
}

bool KCMainWindow::isApplicationActive()
{
#ifdef __APPLE__
	return (macApplicationIsActive() && this->isVisible());
#else
	return this->hasFocus();
#endif
}

void KCMainWindow::toggleApplication()
{
	if(!this->isApplicationActive())
		this->showApplication();
	else
		this->hideApplication();
}

void KCMainWindow::showApplication()
{
#ifdef __APPLE__
	macApplicationActivate();
	this->show();
#else
	this->show();
	this->setFocus();
	this->activateWindow();
	this->raise();
#endif
}

void KCMainWindow::hideApplication()
{
	this->hide();
}

void KCMainWindow::askForAPILink()
{
	if(apiLinkDialogOpen)
		return;
	
	apiLinkDialogOpen = true;
	QUrl url = QInputDialog::getText(this, "Enter API Link", "<p>Enter your API Link.<br />It should look something like:</p><p><code>http://125.6.189.xxx/kcs/mainD2.swf?api_token=xxxxxxxxxxxxxxxxxxxx...</code></p>");
	QUrlQuery query(url);
	apiLinkDialogOpen = false;
	
	client->setCredentials(url.host(), query.queryItemValue("api_token"));
}

void KCMainWindow::updateFleetsPage()
{
	ui->fleetsPage->setUpdatesEnabled(false);
	
	// Hide all the boxes by default, then show the ones we use below
	for(int i = 0; i < 6; i++)
		findChild<QGroupBox*>(QString("fleetBox") + QString::number(i+1))->hide();
	
	// If there is no such fleet, return here and leave all boxes hidden
	if(!client->fleets.contains(ui->fleetsTabBar->currentIndex()+1))
	{
		ui->fleetsPage->setUpdatesEnabled(true);
		return;
	}
	
	// Otherwise, retreive it
	KCFleet *fleet = client->fleets[ui->fleetsTabBar->currentIndex()+1];
	
	// Loop through all the ships in the fleet and put their info up
	for(int i = 0; i < fleet->shipCount; i++)
	{
		KCShip *ship = client->ships[fleet->ships[i]];
		if(!ship) continue;
		
		QString iS = QString::number(i+1);
		
		QGroupBox *box = findChild<QGroupBox*>(QString("fleetBox") + iS);
		QLabel *nameLabel = findChild<QLabel*>(QString("fleetName") + iS);
		QLabel *readingLabel = findChild<QLabel*>(QString("fleetReading") + iS);
		QProgressBar *hpBar = findChild<QProgressBar*>(QString("fleetHpBar") + iS);
		QProgressBar *ammoBar = findChild<QProgressBar*>(QString("fleetAmmoBar") + iS);
		QProgressBar *fuelBar = findChild<QProgressBar*>(QString("fleetFuelBar") + iS);
		QLabel *levelLabel = findChild<QLabel*>(QString("fleetLevel") + iS);
		QLabel *condLabel = findChild<QLabel*>(QString("fleetCond") + iS);
		
		box->show();
		nameLabel->setText(ship->name);
		readingLabel->setText(ship->reading);
		hpBar->setRange(0, ship->maxHp);
		hpBar->setValue(ship->hp);
		ammoBar->setRange(0, ship->maxAmmo);
		ammoBar->setValue(ship->ammo);
		fuelBar->setRange(0, ship->maxFuel);
		fuelBar->setValue(ship->fuel);
		levelLabel->setText(QString::number(ship->level));
		condLabel->setText(QString::number(ship->condition));
	}
	
	ui->fleetsPage->setUpdatesEnabled(true);
}

void KCMainWindow::updateShipsPage()
{
	ui->shipsPage->setUpdatesEnabled(false);
	
	ui->shipsTable->setSortingEnabled(false);
	ui->shipsTable->setRowCount(client->ships.count());
	
	int row = 0;
	foreach(KCShip *ship, client->ships)
	{
		TABLE_SET_ITEM(ui->shipsTable, row, 0, ship->level);
		TABLE_SET_ITEM(ui->shipsTable, row, 1, ship->maxHp);
		TABLE_SET_ITEM(ui->shipsTable, row, 2, ship->firepower.cur);
		TABLE_SET_ITEM(ui->shipsTable, row, 3, ship->torpedo.cur);
		TABLE_SET_ITEM(ui->shipsTable, row, 4, ship->evasion.cur);
		TABLE_SET_ITEM(ui->shipsTable, row, 5, ship->antiair.cur);
		TABLE_SET_ITEM(ui->shipsTable, row, 6, ship->antisub.cur);
		TABLE_SET_ITEM(ui->shipsTable, row, 7, ship->speed);
		TABLE_SET_ITEM(ui->shipsTable, row, 8, QString("%1 (%2)").arg(ship->name, ship->reading));
		
		++row;
	}
	
	ui->shipsTable->setSortingEnabled(true);
	
	ui->shipsPage->setUpdatesEnabled(true);
}

void KCMainWindow::updateRepairsPage()
{
	ui->repairsPage->setUpdatesEnabled(false);
	
	int i = 0;
	foreach(KCDock *dock, client->repairDocks)
	{
		QString iS = QString::number(i+1);
		QGroupBox *box = findChild<QGroupBox*>(QString("repairBox") + iS);
		QLabel *nameLabel = findChild<QLabel*>(QString("repairName") + iS);
		QLabel *readingLabel = findChild<QLabel*>(QString("repairReading") + iS);
		QLabel *repairTimerLabel = findChild<QLabel*>(QString("repairTimer") + iS);
		
		if(dock->state == KCDock::Locked)
		{
			box->setEnabled(false);
			nameLabel->setText("(Locked)");
			readingLabel->setText("");
			repairTimerLabel->setText("");
		}
		else if(dock->state == KCDock::Empty)
		{
			box->setEnabled(true);
			nameLabel->setText("(Empty)");
			readingLabel->setText("");
			repairTimerLabel->setText("0:00:00");
		}
		else if(dock->state == KCDock::Occupied)
		{
			box->setEnabled(true);
			KCShip *ship = client->ships[dock->shipID];
			if(ship)
			{
				nameLabel->setText(ship->name);
				readingLabel->setText(ship->reading);
				repairTimerLabel->setText(delta(dock->complete).toString("H:mm:ss"));
			}
		}
		else qWarning() << "Unknown State for Repair Dock" << i << ":" << dock->state;
		
		++i;
	}
	
	ui->repairsPage->setUpdatesEnabled(true);	
}

void KCMainWindow::updateConstructionsPage()
{
	// Whee copypaste!
	
	ui->constructionPage->setUpdatesEnabled(false);
	
	int i = 0;
	foreach(KCDock *dock, client->constructionDocks)
	{
		QString iS = QString::number(i+1);
		QGroupBox *box = findChild<QGroupBox*>(QString("constructionBox") + iS);
		QLabel *nameLabel = findChild<QLabel*>(QString("constructionName") + iS);
		QLabel *readingLabel = findChild<QLabel*>(QString("constructionReading") + iS);
		QLabel *buildTimerLabel = findChild<QLabel*>(QString("constructionTimer") + iS);
		QCheckBox *spoilCheckbox = findChild<QCheckBox*>(QString("constructionSpoil") + iS);
		
		if(dock->state == KCDock::Locked)
		{
			box->setEnabled(false);
			nameLabel->setText("(Locked)");
			readingLabel->setText("");
			buildTimerLabel->setText("");
			spoilCheckbox->hide();
		}
		else if(dock->state == KCDock::Empty)
		{
			box->setEnabled(true);
			nameLabel->setText("(Empty)");
			readingLabel->setText("");
			buildTimerLabel->setText("0:00:00");
			spoilCheckbox->hide();
			spoilCheckbox->setChecked(false);	// Uncheck it!
		}
		else if(dock->state == KCDock::Occupied || dock->state == KCDock::Building)
		{
			box->setEnabled(true);
			
			if(spoilCheckbox->isChecked())
			{
				KCShipMaster *ship = client->masterShips[dock->shipID];
				if(ship)
				{
					nameLabel->setText(ship->name);
					readingLabel->setText(ship->reading);
				}
				else
				{
					nameLabel->setText("...");
					readingLabel->setText("Loading...");
				}
			}
			else
			{
				nameLabel->setText("???");
				readingLabel->setText("");
			}
			
			buildTimerLabel->setText(delta(dock->complete).toString("H:mm:ss"));
			spoilCheckbox->show();
		}
		else qWarning() << "Unknown State for Construction Dock" << i << ":" << dock->state;
		
		++i;
	}
	
	ui->constructionPage->setUpdatesEnabled(true);
}

void KCMainWindow::updateTimers()
{
	// Repair Docks
	{
		int i = 0;
		foreach(KCDock *dock, client->repairDocks)
		{
			if(dock->state == KCDock::Occupied)
			{
				QLabel *label = findChild<QLabel*>(QString("repairTimer") + QString::number(i+1));
				label->setText(delta(dock->complete).toString("H:mm:ss"));
			}
			++i;
		}
	}
	
	// Construction Docks
	{
		int i = 0;
		foreach(KCDock *dock, client->constructionDocks)
		{
			if(dock->state == KCDock::Building)
			{
				QLabel *label = findChild<QLabel*>(QString("constructionTimer") + QString::number(i+1));
				label->setText(delta(dock->complete).toString("H:mm:ss"));
			}
			++i;
		}
	}
}

void KCMainWindow::onCredentialsGained()
{
	qDebug() << "Credentials Gained";
	client->requestMasterShips();
	client->requestPlayerShips();
	client->requestPlayerFleets();
	client->requestPlayerRepairs();
	client->requestPlayerConstructions();
}

void KCMainWindow::onReceivedMasterShips()
{
	qDebug() << "Received Master Ship Data" << client->masterShips.size();
	updateConstructionsPage();
}

void KCMainWindow::onReceivedPlayerShips()
{
	qDebug() << "Received Player Ship Data" << client->ships.size();
	updateFleetsPage();
	updateShipsPage();
	updateRepairsPage();
}

void KCMainWindow::onReceivedPlayerFleets()
{
	qDebug() << "Received Player Fleet Data" << client->fleets.size();
	
	// If we're on an active tab, update it
	if(ui->fleetsTabBar->currentIndex() < client->fleets.size())
		updateFleetsPage();
	
	// Disable locked fleets; if the user is on an invalid page, this will
	// move them to Fleet #1, and trigger updateFleetsPage from currentChanged
	for(int i = 0; i < ui->fleetsTabBar->count(); i++)
		ui->fleetsTabBar->setTabEnabled(i, i < client->fleets.size());
}

void KCMainWindow::onReceivedPlayerRepairs()
{
	qDebug() << "Received Player Repairs Data" << client->repairDocks.size();
	updateRepairsPage();
}

void KCMainWindow::onReceivedPlayerConstructions()
{
	qDebug() << "Received Player Constructions Data" << client->constructionDocks.size();
	updateConstructionsPage();
}

void KCMainWindow::onRequestError(KCClient::ErrorCode error)
{
	switch(error)
	{
		case KCClient::JsonError:
			QMessageBox::warning(this, "JSON Error", "The response was malformed JSON and could not be parsed. This could mean that there's something messing with your internet connection.");
			break;
		case KCClient::InvalidAPIVersion:
			QMessageBox::critical(this, "Invalid API Version", "KanColle changed their API, and this program is outdated.");
			qApp->quit();
			break;	// OCD
		case KCClient::InvalidCredentials:
			this->askForAPILink();
			break;
		default:
			QMessageBox::warning(this, "Unknown Error", "An unknown error occurred.");
	}
}

void KCMainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
#ifdef __APPLE__
	Q_UNUSED(reason);
	this->toggleApplication();
#else
	if(reason != QSystemTrayIcon::Context)
		this->toggleApplication();
#endif
}

void KCMainWindow::onDockCompleted(KCDock *dock)
{
	if(dock->isConstruction)
	{
		KCShipMaster *shipMaster = client->masterShips[dock->shipID];
		if(shipMaster)
			trayIcon->showMessage("Construction Completed!",
				QString("Say hello to %1 (%2)!").arg(shipMaster->name, shipMaster->reading));
		else
			trayIcon->showMessage("Construction Completed!",
				QString("Say hello to your new shipgirl!"));
	}
	else
	{
		KCShip *ship = client->ships[dock->shipID];
		if(ship)
			trayIcon->showMessage("Repair Completed!",
				QString("%1 (%2) is all healthy again!").arg(ship->name, ship->reading));
		else
			trayIcon->showMessage("Repair Completed!",
				QString("Your shipgirl is all healthy again!"));
	}
}

void KCMainWindow::on_actionFleets_triggered()
{
	ui->actionFleets->setEnabled(false);
	ui->actionShips->setEnabled(true);
	ui->actionRepairs->setEnabled(true);
	ui->actionConstruction->setEnabled(true);
	ui->stackedWidget->setCurrentWidget(ui->fleetsPage);
}

void KCMainWindow::on_actionShips_triggered()
{
	ui->actionFleets->setEnabled(true);
	ui->actionShips->setEnabled(false);
	ui->actionRepairs->setEnabled(true);
	ui->actionConstruction->setEnabled(true);
	ui->stackedWidget->setCurrentWidget(ui->shipsPage);
}

void KCMainWindow::on_actionRepairs_triggered()
{
	ui->actionFleets->setEnabled(true);
	ui->actionShips->setEnabled(true);
	ui->actionRepairs->setEnabled(false);
	ui->actionConstruction->setEnabled(true);
	ui->stackedWidget->setCurrentWidget(ui->repairsPage);
}

void KCMainWindow::on_actionConstruction_triggered()
{
	ui->actionFleets->setEnabled(true);
	ui->actionShips->setEnabled(true);
	ui->actionRepairs->setEnabled(true);
	ui->actionConstruction->setEnabled(false);
	ui->stackedWidget->setCurrentWidget(ui->constructionPage);
}

void KCMainWindow::on_actionRefresh_triggered()
{
    client->requestPlayerShips();
	client->requestPlayerFleets();
	client->requestPlayerRepairs();
	client->requestPlayerConstructions();
}

void KCMainWindow::on_fleetsTabBar_currentChanged(int index)
{
	//qDebug() << "Fleets page on Tab" << index;
	Q_UNUSED(index);
	updateFleetsPage();
}
