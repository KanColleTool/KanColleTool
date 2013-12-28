#include "KVMainWindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QWebFrame>
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include <QUrl>
#include <QUrlQuery>
#include <QApplication>
#include <QNetworkProxy>
#include <QHostAddress>
#include <QSettings>
#include <QStandardPaths>
#include <QDebug>

KVMainWindow::KVMainWindow(QWidget *parent, Qt::WindowFlags flags):
	QMainWindow(parent, flags)
{
	this->setWindowTitle("KanColleTool Viewer");
	
	// Set up the window and menus and stuff
	QMenuBar *menuBar = new QMenuBar(this);
	
	QMenu *viewerMenu = menuBar->addMenu("Viewer");
	viewerMenu->addAction("Change API Link", this, SLOT(askForAPILink()))->setShortcut(Qt::CTRL + Qt::Key_L);
	viewerMenu->addAction("Clear Cache", this, SLOT(clearCache()));
	viewerMenu->addSeparator();
	viewerMenu->addAction("Quit", qApp, SLOT(quit()))->setShortcut(Qt::CTRL + Qt::Key_Q);
	
	QMenu *helpMenu = menuBar->addMenu("Help");
	helpMenu->addAction("About", this, SLOT(showAbout()));
	
	this->setMenuBar(menuBar);
	
	// Set a custom network access manager to let us set up a cache and proxy.
	// Without a cache, the game takes ages to load.
	// Without a proxy, we can't do cool things like translating the game.
	netManager = new QNetworkAccessManager(this);
	
	// Set up a cache; a larger-than-normal disk cache is quite enough for our purposes
	cache = new QNetworkDiskCache(this);
	cache->setCacheDirectory(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
	netManager->setCache(cache);
	
	// Set up a local proxy
	proxy = new KVProxyServer(this);
	proxy->listen(QHostAddress::LocalHost);
	netManager->setProxy(QNetworkProxy(QNetworkProxy::HttpProxy, "localhost", proxy->serverPort()));
	
	connect(proxy, SIGNAL(apiError(KVProxyServer::APIStatus, QString)), this, SLOT(onAPIError(KVProxyServer::APIStatus, QString)));
	
	// Set up the web view, using our custom Network Access Manager
	webView = new QWebView(this);
	webView->page()->setNetworkAccessManager(netManager);
	
	// The context menu only contains "Reload" anyways
	webView->setContextMenuPolicy(Qt::PreventContextMenu);
	// These are so large that they create a need for themselves >_>
	webView->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
	webView->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
	
	connect(webView, SIGNAL(loadStarted()), this, SLOT(onLoadStarted()));
	connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));
	
	// To set the window size right, we have to first set the central widget (which we set to
	// the web view)'s size to a fixed size, ask the window to auto-adjust to that, and then
	// fix its size to what it adjusted itself to. A bit clumsy, but it works, and won't stop
	// us from adding any additional elements to the window, as this will account for ANYTHING.
	this->setCentralWidget(webView);
	this->centralWidget()->setFixedSize(800, 480);
	this->adjustSize();
	this->setFixedSize(this->width(), this->height());
	
	// Ask for an API Link if we don't have one already, otherwise just restore it
	this->loadAPILink();
	
	// Load the bundled index.html file
	this->loadBundledIndex();
}

void KVMainWindow::loadBundledIndex()
{
	QFile file(":/index.html");
	if(file.open(QIODevice::ReadOnly))
	{
		webView->setHtml(file.readAll(), apiLink);
	}
	else
	{
		QMessageBox::critical(this, "Can't load resource", "Couldn't load the local resources needed to start the client.<br /><br />I have no idea how you even managed to make this happen, since the resources are supposed to be inside the executable, but it probably involved a recompilation that went wrong.<br /><br /><code>index.html</code> needs to be in the root of <code>resources.qrc</code>.");
		exit(1);
	}
}

void KVMainWindow::loadAPILink()
{
	QSettings settings;
	
	server = settings.value("server").toString();
	apiToken = settings.value("apiToken").toString();
	
	if(server.isEmpty() || apiToken.isEmpty())
	{
		this->askForAPILink();
		if(server.isEmpty() || apiToken.isEmpty())
			exit(0);
	}
	else this->generateAPILinkURL();
	
	qDebug() << "Server:" << server;
	qDebug() << "API Token:" << apiToken;
	qDebug() << "API Link:" << apiLink.toString();
}

void KVMainWindow::generateAPILinkURL()
{
	apiLink = QUrl(QString("http://%1/kcs/mainD2.swf?api_token=%2").arg(server, apiToken));
}

void KVMainWindow::askForAPILink()
{
	// Get the link from the user
	QString link = QInputDialog::getText(this, "Enter API Link", "Please enter your API Link.<br /><br />It should look something like:<br /><code>http://125.6.XXX.XXX/kcs/mainD2.swf?api_token=xxxxxxxxxx...</code>");
	
	// If the link is empty, the user pressed cancel, for whatever reason
	if(link.isEmpty())
		return;
	
	// Make an URL and a Query from it
	QUrl url(link);
	QUrlQuery query(url);
	
	// Extract the important bits, and generate a well-formed URL from that
	// (It's important that nothing we're doing is noticeable to the staff!)
	server = url.host();
	apiToken = query.queryItemValue("api_token");
	this->generateAPILinkURL();
	
	// Put it in the settings and force a sync
	QSettings settings;
	settings.setValue("server", server);
	settings.setValue("apiToken", apiToken);
	settings.sync();
}

void KVMainWindow::clearCache()
{
	cache->clear();
	this->loadBundledIndex();
}

void KVMainWindow::showAbout()
{
	QMessageBox::about(this, "About KCTViewer",
		QString(
			"<h1>KCTViewer&nbsp;<small>%1</small></h1>"
		).arg(
			QCoreApplication::applicationVersion()
		)
	);
}

void KVMainWindow::onLoadStarted()
{
	qDebug() << "Loading Started...";
}

void KVMainWindow::onLoadFinished(bool ok)
{
	qDebug() << "Finished Loading!" << ok;
	if(ok) this->setHTMLAPILink();
}

void KVMainWindow::setHTMLAPILink()
{
	qDebug() << "Updating API Link in the web view to" << apiLink.toString();
	webView->page()->mainFrame()->evaluateJavaScript(QString("setAPILink(\"%1\"); null").arg(apiLink.toString()));
}

void KVMainWindow::onAPIError(KVProxyServer::APIStatus error, QString message)
{
	qDebug() << error << message;
	
	QString readableError;
	
	switch(error)
	{
		case KVProxyServer::OK:
			readableError = "No Error, you shouldn't be seeing this.";
			break;
		case KVProxyServer::ExpiredAPIToken:
		case KVProxyServer::Unauthorized:
			readableError = "Either your API Link is invalid, or it has expired. That happens sometimes.";
			break;
		case KVProxyServer::InvalidVersion:
			readableError = "Invalid API Version. The game was updated, but you have an old copy.";
			break;
		default:
			readableError = "An unknown error occurred. Please tell the developers that this happened ALONG WITH THE ERROR CODE, and what you think caused it.";
	}
	
	QMessageBox::critical(this, QString("Errorcat (Code %1)").arg((int)error), readableError);
}
