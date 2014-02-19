#include "KVMainWindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QWebFrame>
#include <QInputDialog>
#include <QFile>
#include <QUrl>
#include <QUrlQuery>
#include <QApplication>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QHostAddress>
#include <QSettings>
#include <QStandardPaths>
#include <QDebug>
#include <QTimer>
#include "KVNetworkAccessManager.h"
#include "KVTranslator.h"

KVMainWindow::KVMainWindow(QWidget *parent, Qt::WindowFlags flags):
	QMainWindow(parent, flags)
{
	// Load settings from the settings file
	this->loadSettings();

	this->setWindowTitle("KanColleTool Viewer");

	// Set up the window and menus and stuff
	QMenuBar *menuBar = new QMenuBar(this);

	QMenu *viewerMenu = menuBar->addMenu("Viewer");
	viewerMenu->addAction("Change API Link", this, SLOT(askForAPILink()), Qt::CTRL + Qt::Key_L);
	QAction *translationAction = viewerMenu->addAction("Enable Translation", this, SLOT(toggleTranslation(bool)));
	translationAction->setCheckable(true);
	translationAction->setChecked(KVTranslator::instance()->enabled);
	viewerMenu->addAction("Clear Cache", this, SLOT(clearCache()));
	viewerMenu->addSeparator();
	viewerMenu->addAction("Quit", qApp, SLOT(quit()), Qt::CTRL + Qt::Key_Q);

	QMenu *helpMenu = menuBar->addMenu("Help");
	helpMenu->addAction("About", this, SLOT(showAbout()));
	// Updates on Linux are handled by the package manager
#if !defined(Q_OS_LINUX)
	helpMenu->addAction("Check for Updates", this, SLOT(checkForUpdates()));
#endif

	this->setMenuBar(menuBar);

	// Set a custom network access manager to let us set up a cache and proxy.
	// Without a cache, the game takes ages to load.
	// Without a proxy, we can't do cool things like translating the game.
	wvManager = new KVNetworkAccessManager(this);

	// Set up a cache; a larger-than-normal disk cache is quite enough for our purposes
	cache = new QNetworkDiskCache(this);
	cache->setCacheDirectory(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
	wvManager->setCache(cache);

	//connect(proxy, SIGNAL(apiError(KVProxyServer::APIStatus)), this, SLOT(onAPIError(KVProxyServer::APIStatus)));

	// Set up the web view, using our custom Network Access Manager
	webView = new QWebView(this);
	webView->page()->setNetworkAccessManager(wvManager);

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

	// Check for updates
	// Updates on Linux are handled by the package manager
#if !defined(Q_OS_LINUX)
	this->checkForUpdates();
#endif

	// Load the translation data before doing anything, otherwise we might end
	// up with partially translated data on spotty connections.
	this->loadTranslation();

	// Load the bundled index.html file
	//this->loadBundledIndex();
}

void KVMainWindow::checkForUpdates()
{
	QNetworkReply *reply = manager.get(QNetworkRequest(QUrl("http://kancolletool.github.io/VERSION")));
	connect(reply, SIGNAL(finished()), this, SLOT(onVersionCheckFinished()));
}

void KVMainWindow::loadTranslation(QString language)
{
	loadingMessageBox = new QMessageBox(QMessageBox::NoIcon, "Loading translation...", "This should only take a moment.", QMessageBox::Cancel, this);
	QTimer::singleShot(0, loadingMessageBox, SLOT(open()));

	KVTranslator *translator = KVTranslator::instance();
	connect(translator, SIGNAL(loadFinished()), this, SLOT(onTranslationLoadFinished()));
	connect(translator, SIGNAL(loadFailed(QString)), this, SLOT(onTranslationLoadFailed(QString)));
	translator->loadTranslation(language);
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

void KVMainWindow::loadSettings()
{
	QSettings settings;

	server = settings.value("server").toString();
	apiToken = settings.value("apiToken").toString();

	if(server.isEmpty() || apiToken.isEmpty())
	{
		this->askForAPILink(false);
		if(server.isEmpty() || apiToken.isEmpty())
			exit(0);
	}
	else this->generateAPILinkURL();

	KVTranslator *translator = KVTranslator::instance();
	translator->enabled = settings.value("translation").toBool();

	qDebug() << "Server:" << server;
	qDebug() << "API Token:" << apiToken;
	qDebug() << "API Link:" << apiLink.toString();
	qDebug() << "Translation:" << (translator->enabled ? "enabled" : "disabled");
}

void KVMainWindow::generateAPILinkURL()
{
	apiLink = QUrl(QString("http://%1/kcs/mainD2.swf?api_token=%2").arg(server, apiToken));
}

void KVMainWindow::askForAPILink(bool reload)
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

	// If we're in-game and expected to reload the page, do so.
	// This is NOT true when called from loadAPILink(), and should
	// be true when called from the menu item.
	if(reload)
		this->loadBundledIndex();
}

void KVMainWindow::toggleTranslation(bool checked)
{
	KVTranslator *translator = KVTranslator::instance();
	translator->enabled = checked;

	QSettings settings;
	settings.setValue("translation", translator->enabled);
	settings.sync();

	this->loadBundledIndex();
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

void KVMainWindow::onVersionCheckFinished()
{
	QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());

	// If the check failed, do nothing
	if(reply->error() != QNetworkReply::NoError)
		return;

	// Parse the version numbers
	QString newVersion = QString::fromUtf8(reply->readAll()).trimmed();
	QList<int> newVersionComponents;
	foreach(QString part, newVersion.split("."))
		newVersionComponents.append(part.toInt());

	QString appVersion = qApp->applicationVersion();
	QList<int> appVersionComponents;
	foreach(QString part, appVersion.split("."))
		appVersionComponents.append(part.toInt());

	// Compare component-per-component to see if we're outdated
	bool outdated = false;
	for(int i = 0; i < qMin(newVersionComponents.length(), appVersionComponents.length()); i++)
	{
		if(newVersionComponents[i] != appVersionComponents[i])
		{
			outdated = (newVersionComponents[i] > appVersionComponents[i]);
			break;
		}
	}

	// Display a message if we are
	if(outdated)
		QMessageBox::information(this, "New Version Available", "Version " + newVersion + " has been released, and is available at:<br /><a href=\"http://kancolletool.github.io/downloads/\">http://kancolletool.github.io/downloads/</a>");
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

void KVMainWindow::onTranslationLoadFinished()
{
	qDebug() << "Translation finished loading!";
	loadingMessageBox->accept();
	delete loadingMessageBox;

	this->loadBundledIndex();
}

void KVMainWindow::onTranslationLoadFailed(QString error)
{
	qDebug() << "Translation failed to load:" << error;
	loadingMessageBox->reject();
	delete loadingMessageBox;

	QMessageBox::StandardButton button = QMessageBox::warning(this, "Couldn't load translation", "This might mean that your connection is bad. You can continue without translation, but the game will be in Japanese.", QMessageBox::Retry|QMessageBox::Ok, QMessageBox::Ok);

	// To retry, just send the request again.
	if(button == QMessageBox::Retry)
		this->loadTranslation();

	// To ignore it, just pretend like it succeeded.
	else
		this->onTranslationLoadFinished();
}

void KVMainWindow::setHTMLAPILink()
{
	qDebug() << "Updating web view credentials to" << server << "-" << apiToken;
	webView->page()->mainFrame()->evaluateJavaScript(QString("setCredentials(\"%1\", \"%2\"); null").arg(server, apiToken));
}

/*void KVMainWindow::onAPIError(KVProxyServer::APIStatus error)
{
	qDebug() << error;

	QString readableError;

	switch(error)
	{
		case KVProxyServer::OK:
			readableError = "No Error, you shouldn't be seeing this.";
			break;
		case KVProxyServer::Unauthorized:
			readableError = "Either your API Link is invalid, or it has expired. That happens sometimes.";
			break;
		case KVProxyServer::InvalidAPIVersion:
		case KVProxyServer::MissingParameters:
			readableError = "The game was updated, but you have an old client.";
			break;
		default:
			readableError = "An unknown error occurred. Please tell the developers that this happened ALONG WITH THE ERROR CODE, and what you think caused it.";
	}

	QMessageBox::critical(this, QString("Errorcat (Code %1)").arg((int)error), readableError);
}*/
