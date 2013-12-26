#include "KVMainWindow.h"
#include <QWebFrame>
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include <QUrl>
#include <QUrlQuery>
#include <QSettings>
#include <QDebug>

KVMainWindow::KVMainWindow(QWidget *parent, Qt::WindowFlags flags):
	QMainWindow(parent, flags)
{
	this->setWindowTitle("KanColleTool Viewer");
	
	webView = new QWebView(this);
	connect(webView, SIGNAL(loadStarted()), this, SLOT(onLoadStarted()));
	connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));
	
	// We don't want a right-click to bring up a context menu containing only "Reload",
	// nor do we want scrollbars so big that they make themselves necessary.
	webView->setContextMenuPolicy(Qt::PreventContextMenu);
	webView->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
	webView->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
	
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
	if(!settings.contains("server") || !settings.contains("apiToken"))
	{
		QUrl url(this->askForAPILink());
		QUrlQuery query(url);
		
		server = url.host();
		apiToken = query.queryItemValue("api_token");
		settings.setValue("server", server);
		settings.setValue("apiToken", apiToken);
		settings.sync();
	}
	else
	{
		server = settings.value("server").toString();
		apiToken = settings.value("apiToken").toString();
	}
	
	apiLink = QUrl(QString("http://%1/kcs/mainD2.swf?api_token=%2").arg(server, apiToken));
	
	qDebug() << "Server:" << server;
	qDebug() << "API Token:" << apiToken;
	qDebug() << "API Link:" << apiLink.toString();
}

QString KVMainWindow::askForAPILink()
{
	return QInputDialog::getText(this, "Enter API Link", "Please enter your API Link.<br /><br />It should look something like:<br /><code>http://125.6.XXX.XXX/kcs/mainD2.swf?api_token=xxxxxxxxxx...</code>");
}

void KVMainWindow::onLoadStarted()
{
	qDebug() << "Loading Started...";
}

void KVMainWindow::onLoadFinished(bool ok)
{
	qDebug() << "Finished Loading!" << ok;
	if(ok)
		webView->page()->mainFrame()->evaluateJavaScript(QString("setAPILink(\"%1\"); null").arg(apiLink.toString()));
}
