#include "KCMainWindow.h"
#include "ui_KCMainWindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QSettings>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>

#ifdef __APPLE__
#include <Carbon/Carbon.h>
#include <objc/objc-runtime.h>
#endif

KCMainWindow::KCMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::KCMainWindow)
{
	ui->setupUi(this);
	
	this->_setupTrayIcon();
	this->_setupUI();
	this->_setupClient();
	this->_setupProxyServer();
}

KCMainWindow::~KCMainWindow()
{
	delete ui;
}

void KCMainWindow::_setupTrayIcon()
{
	// Create the Tray Icon
	this->trayIcon = new QSystemTrayIcon(QIcon(":/icon.png"), this);
	connect(this->trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
			this, SLOT(onTrayIconActivated(QSystemTrayIcon::ActivationReason)));
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
	/*QWidget *spacer = new QWidget(this);
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	ui->toolBar->insertWidget(ui->actionSettings, spacer);*/
	
	// On Mac and Linux, make the window join all spaces
	// (why isn't there a Qt call for this...)
#ifdef __APPLE__
	int NSWindowCollectionBehaviorCanJoinAllSpaces = 1 << 0;
	
	objc_object *macView = reinterpret_cast<objc_object *>(this->winId());
	objc_object *macWindow = objc_msgSend(macView, sel_registerName("window"));
	objc_msgSend(macWindow, sel_registerName("setCollectionBehavior:"), NSWindowCollectionBehaviorCanJoinAllSpaces);
#endif
	
#ifdef Q_WS_X11
	unsigned long data = 0xFFFFFFFF;
	
	XChangeProperty(QX11Info::display(), this->winId(),
		XInternAtom(QX11Info::display(), "_NET_WM_DESKTOP", False),
		XA_CARDINAL, 32, PropModeReplace,
		reinterpret_cast<unsigned char *>(&data), // all desktop
		1);
#endif
}

void KCMainWindow::_setupClient()
{
	this->client = new KCClient(this);
	
	connect(this->client, SIGNAL(credentialsGained()), this, SLOT(onCredentialsGained()));
	connect(this->client, SIGNAL(receivedMasterShips(QList<QVariant>)), this, SLOT(onReceivedMasterShips(QList<QVariant>)));
	connect(this->client, SIGNAL(receivedPlayerShips(QList<QVariant>)), this, SLOT(onReceivedPlayerShips(QList<QVariant>)));
	connect(this->client, SIGNAL(requestError(KCClient::ErrorCode)), this, SLOT(onRequestError(KCClient::ErrorCode)));
	
	if(!this->client->hasCredentials())
		this->askForAPILink();
}

void KCMainWindow::_setupProxyServer()
{
	this->proxyServer = new KCProxyServer(this->client, this);
	this->proxyServer->listen(QHostAddress::Any, 12345);
	qDebug() << "Proxy Server listening on Port 12345...";
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
	
	this->client->setCredentials(url.host(), query.queryItemValue("api_token"));
}

void KCMainWindow::onCredentialsGained()
{
	//this->client->requestMasterShips();
	//this->client->requestPlayerShips();
}

void KCMainWindow::onReceivedMasterShips(QList<QVariant> data)
{
	Q_UNUSED(data);
	qDebug() << "Received Master Ship Data";
}

void KCMainWindow::onReceivedPlayerShips(QList<QVariant> data)
{
	Q_UNUSED(data);
	qDebug() << "Received Player Ship Data";
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
