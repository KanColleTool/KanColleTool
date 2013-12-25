#include "KCGameWindow.h"
#include <QDebug>

KCGameWindow::KCGameWindow(KCClient *client, QWidget *parent) :
	QMainWindow(parent), client(client)
{
	webView = new QWebView(this);
	webView->setFixedSize(800, 480);
	connect(webView, SIGNAL(loadStarted()), this, SLOT(onLoadStarted()));
	connect(webView, SIGNAL(loadProgress(int progress)), this, SLOT(onLoadProgress(int progress)));
	connect(webView, SIGNAL(loadFinished(bool ok)), this, SLOT(onLoadFinished(bool ok)));
	
	this->setCentralWidget(webView);
	this->adjustSize();
	
	webView->load(QUrl(QString("http://%1/kcs/mainD2.swf?api_token=%2").arg(client->server, client->apiToken)));
}

void KCGameWindow::onLoadStarted()
{
	qDebug() << "Started Loading" << webView->url();
}

void KCGameWindow::onLoadProgress(int progress)
{
	qDebug() << "--" << progress << "percent done...";
}

void KCGameWindow::onLoadFinished(bool ok)
{
	qDebug() << "Finished Loading!" << ok;
}
