#ifndef KCGAMEWINDOW_H
#define KCGAMEWINDOW_H

#include <QMainWindow>
#include <QWebView>
#include "KCClient.h"

class KCGameWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit KCGameWindow(KCClient *client, QWidget *parent = 0);
	
private slots:
	void onLoadStarted();
	void onLoadProgress(int progress);
	void onLoadFinished(bool ok);
	
protected:
	QWebView *webView;
	
	KCClient *client;
};

#endif // KCGAMEWINDOW_H
