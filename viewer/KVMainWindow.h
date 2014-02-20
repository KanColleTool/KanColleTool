#ifndef KVMAINWINDOW_H
#define KVMAINWINDOW_H

#include <QMainWindow>
#include <QWebView>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkDiskCache>

class KVMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	KVMainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);

protected:
	void loadTranslation(QString language = "en");
	void loadBundledIndex();
	void loadSettings();
	void generateAPILinkURL();

public slots:
	void checkForUpdates();
	void askForAPILink(bool reload = true);
	void toggleTranslation(bool toEnable = false);
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
	QMessageBox *loadingMessageBox;

	QNetworkAccessManager *wvManager, manager;
	QNetworkDiskCache *cache;

	QString server, apiToken;
	QUrl apiLink;
};

#endif
