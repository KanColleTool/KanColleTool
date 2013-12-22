#include "KCMainWindow.h"
#include "ui_KCMainWindow.h"
#include <QInputDialog>
#include <QSettings>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>

#ifdef __APPLE__
#include <Carbon/Carbon.h>
#endif

KCMainWindow::KCMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::KCMainWindow)
{
	ui->setupUi(this);
	
	this->_setupTrayIcon();
	this->_setupUI();
	
	// Check the settings for the API link
	QSettings settings;
	if(settings.contains("server") && settings.contains("apiToken"))
	{
		server = settings.value("server").toString();
		apiToken = settings.value("apiToken").toString();
	}
	else this->askForAPILink();
}

KCMainWindow::~KCMainWindow()
{
	QSettings settings;
	settings.setValue("server", server);
	settings.setValue("apiToken", apiToken);
	
	delete ui;
}

void KCMainWindow::_setupTrayIcon()
{
	// Create the Tray Icon
	this->trayIcon = new QSystemTrayIcon(QIcon(":/icon.png"), this);
	connect(this->trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
			this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
	this->trayIcon->show();
	
	// Set up the menu for it, but not if we're on a Mac.
	// On Mac, it's more convenient to have a click bring up the main window
	// (since left-click also brings up the menu there)
#ifndef __APPLE__
	this->trayMenu = new QMenu("KanColleTool", this);
	this->trayMenu->addAction("Show", this, SLOT(showApplication()));
	this->trayMenu->addSeparator();
	this->trayIcon->setContextMenu(this->trayMenu);
#endif
}

void KCMainWindow::_setupUI()
{
	// Right-align the Launch Game button with a spacer
	QWidget *spacer = new QWidget(this);
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	ui->toolBar->insertWidget(ui->actionSettings, spacer);
}

bool KCMainWindow::isApplicationActive()
{
#ifdef __APPLE__
	// On Mac OS X, compare the current process' serial to the front
	// process' serial, as well as check if the window is active.
	// this->hasFocus() is local to the program's space, so it can't
	// be used here.
	ProcessSerialNumber myPSN;
	if(GetCurrentProcess(&myPSN) != noErr)
		qFatal("<Mac> Error getting PSN!");
	
	ProcessSerialNumber frontPSN;
	if(GetFrontProcess(&frontPSN) != noErr)
		qFatal("<Mac> Error getting front PSN!");
	
	return (myPSN.highLongOfPSN == frontPSN.highLongOfPSN &&
			myPSN.lowLongOfPSN == frontPSN.lowLongOfPSN &&
			this->isVisible());
#else
	// Otherwise, we only have to check if the window has focus or not
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
	ProcessSerialNumber myPSN;
	if(GetCurrentProcess(&myPSN) == noErr)
		SetFrontProcess(&myPSN);
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
	QUrl url = QInputDialog::getText(this, "Enter API Link", "<p>Enter your API Link.<br />It should look something like:</p><p><code>http://125.6.189.xxx/kcs/mainD2.swf?api_token=xxxxxxxxxxxxxxxxxxxx...</code></p>");
	QUrlQuery query(url);
	
	server = url.host();
	apiToken = query.queryItemValue("api_token");
}

void KCMainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
#ifdef __APPLE__
	Q_UNUSED(reason);
	this->toggleApplication();
#else
	if(reason != QSystemTrayIcon::Context)
		this->toggleApplication();
#endif
}
