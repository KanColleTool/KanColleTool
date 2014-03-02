#ifndef KVMAINWINDOW_H
#define KVMAINWINDOW_H

#include <QMainWindow>
#include <QWebView>
#include <QMessageBox>
#include <QNetworkDiskCache>

#include "KVNetworkAccessManager.h"

class KVMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	KVMainWindow(QWidget *parent=0, Qt::WindowFlags flags=0);

protected:
	void loadTranslation(QString language="en");
	void loadSettings();
	void generateAPILinkURL();

public slots:
	void loadBundledIndex();
	void checkForUpdates();
	void askForAPILink(bool reload=true);
	void openSettings();
	void implementSettings(bool start=false);
	void clearCache();
	void showAbout();

private slots:
	void onVersionCheckFinished();
	void onLoadStarted();
	void onLoadFinished(bool ok);
	void onTranslationLoadFailed(QString error);

	void setHTMLAPILink();

	// Never actually emmitted yet; I'm trying to get the proxy
	// stable before I start poking at the responses.
	//void onAPIError(KVProxyServer::APIStatus error);

protected:
	QWebView *webView;

	KVNetworkAccessManager *wvManager, manager;
	QNetworkDiskCache *cache;

	QString server, apiToken;
	QUrl apiLink;
};

#endif
