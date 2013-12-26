#include "KVMainWindow.h"
#include <QWebFrame>
#include <QMessageBox>
#include <QFile>
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
	
	// Load the bundled index.html file
	this->loadBundledIndex();
}

void KVMainWindow::loadBundledIndex()
{
	QFile file(":/index.html");
	if(file.open(QIODevice::ReadOnly))
	{
		webView->setHtml(file.readAll(), QUrl("http://125.6.189.71/kcs/mainD2.swf?api_token=8d697e460ae560de116270fb881ad57ded311b23"));
	}
	else
	{
		QMessageBox::critical(this, "Can't load resource", "Couldn't load the local resources needed to start the client.<br /><br />I have no idea how you even managed to make this happen, since the resources are supposed to be inside the executable, but it probably involved a recompilation that went wrong.<br /><br /><code>index.html</code> needs to be in the root of <code>resources.qrc</code>.");
		exit(1);
	}
}

void KVMainWindow::onLoadStarted()
{
	qDebug() << "Loading Started...";
}

void KVMainWindow::onLoadFinished(bool ok)
{
	qDebug() << "Finished Loading!" << ok;
}
