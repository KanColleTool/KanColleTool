#ifndef KVMAINWINDOW_H
#define KVMAINWINDOW_H

#include <QMainWindow>
#include <QWebView>
#include <QNetworkAccessManager>
#include <QNetworkDiskCache>
#include "KVProxyServer.h"

class KVMainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	KVMainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	
protected:
	void loadBundledIndex();
	void loadAPILink();
	void generateAPILinkURL();
	
public slots:
	void askForAPILink();
	void showAbout();
	
private slots:
	void onLoadStarted();
	void onLoadFinished(bool ok);
	
protected:
	QWebView *webView;
	QNetworkAccessManager *netManager;
	QNetworkDiskCache *cache;
	KVProxyServer *proxy;
	
	QString server, apiToken;
	QUrl apiLink;
};

#endif
