#include "KCMainWindow.h"
#include "ui_KCMainWindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QShortcut>
#include <QLocalSocket>
#include <QSettings>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>
#include "KCSettingsDialog.h"
#include "KCTranslator.h"
#include "KCShip.h"
#include "KCShipMaster.h"
#include "KCDock.h"
#include "KCMacUtils.h"
#include "KCUtil.h"
#include "KCDefaults.h"

KCMainWindow::KCMainWindow(QWidget *parent) :
	QMainWindow(parent), ui(new Ui::KCMainWindow),
	trayIcon(0), trayMenu(0), client(0), server(0),
	apiLinkDialogOpen(false) {}

bool KCMainWindow::init() {
	ui->setupUi(this);

	QMessageBox loadingMessageBox(QMessageBox::NoIcon, "Loading...",
	                              "This should only take a few moments.",
	                              QMessageBox::Cancel, this);
	loadingMessageBox.open();

	if(!this->_setupServer()) return false;
	this->_setupClient();
	this->_setupTrayIcon();
	this->_setupUI();

	loadingMessageBox.accept();

	this->_showDisclaimer();

	// Setup settings and stuff
	connect(&refreshTimer, SIGNAL(timeout()), this, SLOT(on_actionRefresh_triggered()));
	this->updateSettingThings();

	// Load the translation
	KCTranslator *tl = KCTranslator::instance();
	connect(tl, SIGNAL(loadFinished()), this, SLOT(onTranslationLoadFinished()));
	connect(tl, SIGNAL(loadFailed(QString)), this, SLOT(onTranslationLoadFailed(QString)));
	tl->loadTranslation();

	// Make a timer that updates the dock timers, with a 1sec interval
	connect(&timerUpdateTimer, SIGNAL(timeout()), this, SLOT(updateTimers()));
	timerUpdateTimer.start(1000);
	updateTimers();	// Don't wait a whole second to update timers

	// Set the Fleets page regardless of what the UI file says.
	// (This saves me from accidentally releasing a version with the wrong
	// start page due to me editing another one right beforehand)
	this->on_actionFleets_triggered();

	return true;
}

KCMainWindow::~KCMainWindow() {
	delete trayIcon;
	delete trayMenu;
	delete ui;
	delete client;
	delete server;
}

bool KCMainWindow::_setupServer() {
	server = new KCToolServer(this);

	connect(server, SIGNAL(focusRequested()), SLOT(showApplication()));
	if(!server->listen("KanColleTool")) {
		QLocalSocket *socket = new QLocalSocket;
		socket->connectToServer("KanColleTool");

		if(socket->waitForConnected(1000)) {
			socket->write("focus");
			socket->flush();
			socket->close();

			return false;
		} else {
			server->removeServer("KanColleTool");
			server->listen("KanColleTool");
		}
	}
	return true;
}

void KCMainWindow::_setupClient()
{
	client = new KCClient(this);
	server->setClient(client);

	connect(client, SIGNAL(credentialsGained()), this, SLOT(onCredentialsGained()));
	connect(client, SIGNAL(receivedMasterShips()), this, SLOT(onReceivedMasterShips()));
	connect(client, SIGNAL(receivedPlayerShips()), this, SLOT(onReceivedPlayerShips()));
	connect(client, SIGNAL(receivedPlayerFleets()), this, SLOT(onReceivedPlayerFleets()));
	connect(client, SIGNAL(receivedPlayerRepairs()), this, SLOT(onReceivedPlayerRepairs()));
	connect(client, SIGNAL(receivedPlayerConstructions()), this, SLOT(onReceivedPlayerConstructions()));
	connect(client, SIGNAL(requestError(KCClient::ErrorCode)), this, SLOT(onRequestError(KCClient::ErrorCode)));
	connect(client, SIGNAL(dockCompleted(KCDock *)), this, SLOT(onDockCompleted(KCDock *)));
	connect(client, SIGNAL(missionCompleted(KCFleet*)), this, SLOT(onMissionCompleted(KCFleet*)));

	QEventLoop loop;
	loop.connect(client, SIGNAL(receivedMasterShips()), SLOT(quit()));
	QSettings settings;
	if(settings.value("usenetwork", kDefaultUseNetwork).toBool()) {
		if(!client->hasCredentials()) {
			this->askForAPILink();

			// Quit if the user pressed Cancel, instead of erroring out
			if(!client->hasCredentials())
				qApp->quit();
		} else {
			this->onCredentialsGained();
		}
	} else {
		client->safeMasterShips();
	}
	loop.exec();
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
#if !defined(__APPLE__)
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
	ui->toolBar->insertWidget(ui->actionSettings, toolbarSpacer);

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

#ifdef __APPLE__
	// On Mac, make the window join all spaces
	// (why isn't there a Qt call for this...)
	macSetWindowOnAllWorkspaces(this);

	// Cmd+R (given to Qt as Ctrl+R and remapped) makes more sense for the
	// refresh command than F5 on OSX, where you generally avoid F-keys
	ui->actionRefresh->setShortcut(Qt::CTRL|Qt::Key_R);
#endif

	// On Mac, we get Cmd+Q to quit for free. On anything else, set it up like this
#if !defined(__APPLE__)
	QShortcut *quitShortcut = new QShortcut(QKeySequence("Ctrl+Q"), this);
	connect(quitShortcut, SIGNAL(activated()), qApp, SLOT(quit()));
#endif
}

void KCMainWindow::_showDisclaimer()
{
	QSettings settings;

	// Only show the disclaimer if it has not already been shown
	// Using an int here because I might want to show it again if I make any
	// big changes to it sometime; shouldn't happen though...
	if(settings.value("disclaimerShown", 0).toInt() <= 0)
	{
		QMessageBox::information(this, "Disclaimer",
			"<p>"
#if __APPLE__
			"Disclaimer:"
			"</p>"
			"<p>"
#endif
			"It's important to note that KanColleTool is not a cheat tool.<br /> "
			"It will not let you do anything the game would not usually let you do."
			"</p>"
			"<p>"
			"Using KanColleTool will not increase your chances of getting banned.<br />"
			"If you're a foreign player, that's already reason enough to ban you, but KCT "
			"is impossible to differentiate from a web browser on their end."
			"</p>");
		settings.setValue("disclaimerShown", 1);
	}
}

void KCMainWindow::closeEvent(QCloseEvent *event)
{
	QSettings settings;
	if(settings.value("minimizeToTray", kDefaultMinimizeToTray).toBool())
	{
		// The first time the application is minimized to the tray, display a
		// message to alert the user about this, in case their window manager
		// hides it by default (*cough* Windows 7 *cough*).
		// This doesn't make sense on OSX, because the program is always in the
		// menu bar in the first place there, with no dock icon at all.
#if !defined(__APPLE__)
		if(!settings.value("closeToTrayNotificationShown").toBool())
		{
			trayIcon->showMessage("Still running!", "KanColleTool is still running in the tray.\nYou can disable that in the settings.");
			settings.setValue("closeToTrayNotificationShown", true);
		}
#endif
	}
	else
	{
		// Just quit if we're not set to stay in the tray when closed
		qApp->quit();
	}

	event->accept();
}

void KCMainWindow::keyPressEvent(QKeyEvent *event)
{
	// Only do this on the fleets page
	if(!ui->actionFleets->isEnabled())
	{
		int moveToTab = -1;
		switch(event->key())
		{
			case Qt::Key_1:		moveToTab = 0; break;
			case Qt::Key_2:		moveToTab = 1; break;
			case Qt::Key_3:		moveToTab = 2; break;
			case Qt::Key_4:		moveToTab = 3; break;
			default: break;
		}

		if(moveToTab != -1)
			if(ui->fleetsTabBar->isTabEnabled(moveToTab))
				ui->fleetsTabBar->setCurrentIndex(moveToTab);
	}

	QMainWindow::keyPressEvent(event);
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
	if(fleet)
	{
		// Loop through all the ships in the fleet and put their info up
		for(int i = 0; i < fleet->shipCount; i++)
		{
			KCShip *ship = client->ships[fleet->ships[i]];
			if(!ship) continue;
			KCShipMaster *type = client->masterShips[ship->master];
			if(!type) continue;

			QString iS = QString::number(i+1);

			QGroupBox *box = findChild<QGroupBox*>(QString("fleetBox") + iS);
			QProgressBar *hpBar = findChild<QProgressBar*>(QString("fleetHpBar") + iS);
			QProgressBar *ammoBar = findChild<QProgressBar*>(QString("fleetAmmoBar") + iS);
			QProgressBar *fuelBar = findChild<QProgressBar*>(QString("fleetFuelBar") + iS);
			QLabel *levelLabel = findChild<QLabel*>(QString("fleetLevel") + iS);
			QLabel *condLabel = findChild<QLabel*>(QString("fleetCond") + iS);

			box->show();
			box->setTitle(kcTranslate(type->name));
			hpBar->setRange(0, ship->hp.max);
			hpBar->setValue(ship->hp.cur);
			ammoBar->setRange(0, type->maxAmmo);
			ammoBar->setValue(ship->ammo);
			fuelBar->setRange(0, type->maxFuel);
			fuelBar->setValue(ship->fuel);
			levelLabel->setText(QString::number(ship->level));
			condLabel->setText(QString::number(ship->condition));
		}
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
		if(!ship) continue;
		KCShipMaster *type = client->masterShips[ship->master];
		if(!type) continue;

		TABLE_SET_ITEM(ui->shipsTable, row, 0, ship->level);
		TABLE_SET_ITEM(ui->shipsTable, row, 1, ship->hp.max);
		TABLE_SET_ITEM(ui->shipsTable, row, 2, ship->firepower.cur);
		TABLE_SET_ITEM(ui->shipsTable, row, 3, ship->torpedo.cur);
		TABLE_SET_ITEM(ui->shipsTable, row, 4, ship->evasion.cur);
		TABLE_SET_ITEM(ui->shipsTable, row, 5, ship->antiair.cur);
		TABLE_SET_ITEM(ui->shipsTable, row, 6, ship->antisub.cur);
		TABLE_SET_ITEM(ui->shipsTable, row, 7, type->speed);
		TABLE_SET_ITEM(ui->shipsTable, row, 8, kcTranslate(type->name));

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
		if(!dock) continue;

		QString iS = QString::number(i+1);
		QGroupBox *box = findChild<QGroupBox*>(QString("repairBox") + iS);
		QLabel *nameLabel = findChild<QLabel*>(QString("repairName") + iS);
		QLabel *repairTimerLabel = findChild<QLabel*>(QString("repairTimer") + iS);

		if(dock->state == KCDock::Locked)
		{
			box->setEnabled(false);
			nameLabel->setText("(Locked)");
			repairTimerLabel->setText("");
		}
		else if(dock->state == KCDock::Empty)
		{
			box->setEnabled(true);
			nameLabel->setText("(Empty)");
			repairTimerLabel->setText("0:00:00");
		}
		else if(dock->state == KCDock::Occupied)
		{
			box->setEnabled(true);
			KCShip *ship = client->ships[dock->shipID];
			if(ship)
			{
				KCShipMaster *type = client->masterShips[ship->master];
				if(type)
					nameLabel->setText(kcTranslate(type->name));
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
		if(!dock) continue;

		QString iS = QString::number(i+1);
		QGroupBox *box = findChild<QGroupBox*>(QString("constructionBox") + iS);
		QLabel *nameLabel = findChild<QLabel*>(QString("constructionName") + iS);
		QLabel *buildTimerLabel = findChild<QLabel*>(QString("constructionTimer") + iS);
		QCheckBox *spoilCheckbox = findChild<QCheckBox*>(QString("constructionSpoil") + iS);

		if(dock->state == KCDock::Locked)
		{
			box->setEnabled(false);
			nameLabel->setText("(Locked)");
			buildTimerLabel->setText("");
			spoilCheckbox->hide();
		}
		else if(dock->state == KCDock::Empty)
		{
			box->setEnabled(true);
			nameLabel->setText("(Empty)");
			buildTimerLabel->setText("0:00:00");
			spoilCheckbox->hide();
			spoilCheckbox->setChecked(false);	// Uncheck it!
		}
		else if(dock->state == KCDock::Occupied || dock->state == KCDock::Building || dock->state == KCDock::Finished)
		{
			box->setEnabled(true);

			if(spoilCheckbox->isChecked())
			{
				KCShipMaster *ship = client->masterShips[dock->shipID];
				if(ship)
					nameLabel->setText(kcTranslate(ship->name));
				else
					nameLabel->setText("(Loading...)");
			}
			else
				nameLabel->setText("???");

			if(dock->state == KCDock::Occupied || dock->state == KCDock::Building)
				buildTimerLabel->setText(delta(dock->complete).toString("H:mm:ss"));
			else
				buildTimerLabel->setText("0:00:00");
			spoilCheckbox->show();
		}
		else qWarning() << "Unknown State for Construction Dock" << i << ":" << dock->state;

		++i;
	}

	ui->constructionPage->setUpdatesEnabled(true);
}

void KCMainWindow::updateTimers()
{
	// Fleet Status
	{
		KCFleet *fleet = client->fleets[ui->fleetsTabBar->currentIndex()+1];

		// Second condition is a hack to make sure to wait for updateFleetsPage()
		if(fleet && !ui->fleetBox1->isHidden())
		{
			ui->fleetStatus->show();

			bool busy = false;
			QString status = "Combat-Ready";
			QTime dT;

			// Check if the fleet is out on an expedition
			if(fleet->mission.page > 0 && fleet->mission.no > 0 && fleet->mission.complete > QDateTime::currentDateTime())
			{
				busy = true;
				status = QString("Doing Expedition %1-%2").arg(
					QString::number(fleet->mission.page), QString::number(fleet->mission.no));
				dT = delta(fleet->mission.complete);
			}

			// Check if anyone is in the bath; you never disturb a lady who's
			// taking a bath, not even if an Airfield Hime invades the base
			foreach(KCDock *dock, client->repairDocks)
			{
				// Skip already done or empty (completion time = Epoch+0ms) docks
				if(dock->complete < QDateTime::currentDateTime())
					continue;

				for(int i = 0; i < fleet->shipCount; i++)
				{
					if(fleet->ships[i] == dock->shipID)
					{
						// Make sure to use the longest reppair countdown
						QTime dT2 = delta(dock->complete);
						if(dT2 < dT)
							continue;

						KCShip *ship = client->ships[fleet->ships[i]];
						KCShipMaster *type = client->masterShips[ship->master];
						busy = true;
						if(type)
							status = QString("%1 is taking a bath").arg(kcTranslate(type->name));
						dT = dT2;
					}
				}
			}

			// Show it all
			if(busy)
			{
				ui->fleetStatus->setText(status);
				ui->fleetCountdown->setText(dT.toString("H:mm:ss"));
				ui->fleetCountdownContainer->show();
			}
			else
			{
				ui->fleetStatus->setText(status);
				ui->fleetCountdownContainer->hide();
			}
		}
		else
		{
			ui->fleetStatus->hide();
			ui->fleetCountdownContainer->hide();
		}
	}

	// Repair Docks
	{
		int i = 0;
		foreach(KCDock *dock, client->repairDocks)
		{
			if(!dock) continue;

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
			if(!dock) continue;

			if(dock->state == KCDock::Building)
			{
				QLabel *label = findChild<QLabel*>(QString("constructionTimer") + QString::number(i+1));
				label->setText(delta(dock->complete).toString("H:mm:ss"));
			}
			++i;
		}
	}
}

void KCMainWindow::updateSettingThings()
{
	QSettings settings;

	// Translation
	{
		bool wasEnabled = KCTranslator::instance()->enabled;
		bool newEnabled = settings.value("toolTranslation", kDefaultTranslation).toBool();
		qDebug() << "Translation Enabled:" << wasEnabled << "->" << newEnabled;
		KCTranslator::instance()->enabled = newEnabled;

		if(wasEnabled != newEnabled)
		{
			this->updateFleetsPage();
			this->updateShipsPage();
			this->updateRepairsPage();
			this->updateConstructionsPage();
		}
	}

	// Server for Viewer data livestreaming
	server->enabled = settings.value("livestream", kDefaultLivestream).toBool();

	useNetwork = settings.value("usenetwork", kDefaultUseNetwork).toBool();

	// Autorefreshing
	if(settings.value("autorefresh", kDefaultAutorefresh).toBool())
		refreshTimer.start(settings.value("autorefreshInterval", kDefaultAutorefreshInterval).toInt()*1000);
	else
		refreshTimer.stop();
}

void KCMainWindow::onTranslationLoadFinished()
{
	qDebug() << "Received Translation Data!";
	// Update all the things!
	updateFleetsPage();
	updateShipsPage();
	updateRepairsPage();
	updateConstructionsPage();
}

void KCMainWindow::onTranslationLoadFailed(QString error)
{
	qDebug() << "Failed to load Translation Data..." << error;
	QMessageBox::StandardButton button = QMessageBox::warning(this, "Couldn't load Translation", "You may choose to continue without translation data, but everything will be in Japanese.", QMessageBox::Ok|QMessageBox::Retry, QMessageBox::Retry);
	if(button == QMessageBox::Retry)
		KCTranslator::instance()->loadTranslation();
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
	{
		updateFleetsPage();
		updateTimers();
	}

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

		// Only name the ship if the player has asked for a spoiler already
		bool spoil = false;
		for(int i = 0; i < client->constructionDocks.size(); i++)
			if(client->constructionDocks[i] == dock)
				spoil = findChild<QCheckBox*>(QString("constructionSpoil") + QString::number(i+1))->isChecked();

		if(shipMaster && spoil)
			trayIcon->showMessage("Construction Completed!",
				QString("Say hello to %1!").arg(kcTranslate(shipMaster->name)));
		else
			trayIcon->showMessage("Construction Completed!",
				QString("Say hello to your new shipgirl!"));

		updateConstructionsPage();
	}
	else
	{
		KCShip *ship = client->ships[dock->shipID];
		if(ship) {
			KCShipMaster *type = client->masterShips[ship->master];
			if(type)
				trayIcon->showMessage("Repair Completed!",
				                      QString("%1 is all healthy again!").arg(kcTranslate(type->name)));
		} else {
			trayIcon->showMessage("Repair Completed!",
				QString("Your shipgirl is all healthy again!"));
		}

		updateRepairsPage();
	}
}

void KCMainWindow::onMissionCompleted(KCFleet *fleet)
{
	int id = client->fleets.key(fleet);
	trayIcon->showMessage("Expedition Complete",
		QString("Fleet %1 returned from Expedition %2-%3").arg(
			QString::number(id), QString::number(fleet->mission.page), QString::number(fleet->mission.no)));
	updateTimers();
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
	if(!client->hasCredentials()) {
		this->askForAPILink();

		// Cancel the refresh if the user pressed Cancel, instead of erroring out
		if(!client->hasCredentials())
			return;
	}

	client->requestPlayerShips();
	client->requestPlayerFleets();
	client->requestPlayerRepairs();
	client->requestPlayerConstructions();
}

void KCMainWindow::on_actionSettings_triggered()
{
	KCSettingsDialog *settingsDialog = new KCSettingsDialog(this);
	connect(settingsDialog, SIGNAL(accepted()), this, SLOT(updateSettingThings()));
	connect(settingsDialog, SIGNAL(finished(int)), settingsDialog, SLOT(deleteLater()));
	settingsDialog->show();
}

void KCMainWindow::on_fleetsTabBar_currentChanged(int index)
{
	//qDebug() << "Fleets page on Tab" << index;
	Q_UNUSED(index);
	updateFleetsPage();
	updateTimers();
}
