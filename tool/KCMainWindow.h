#ifndef KCMAINWINDOW_H
#define KCMAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QPointer>
#include "KCClient.h"

namespace Ui {
	class KCMainWindow;
}

class KCMainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit KCMainWindow(QWidget *parent = 0);
	~KCMainWindow();
	
private:
	void _setupTrayIcon();
	void _setupUI();
	void _setupClient();
	
public:
	bool isApplicationActive();
	
public slots:
	void toggleApplication();
	void showApplication();
	void hideApplication();
	
	void askForAPILink();
	
private slots:
	void onCredentialsGained();
	void onReceivedMasterShips();
	void onReceivedPlayerShips();
	void onRequestError(KCClient::ErrorCode error);
	
	void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
	
	void on_fleetsTabBar_currentChanged(int index);
	
private:
	Ui::KCMainWindow *ui;
	
	QSystemTrayIcon *trayIcon;
	QMenu *trayMenu;
	
	KCClient *client;
	
	bool apiLinkDialogOpen;
};

#endif // KCMAINWINDOW_H
