#ifndef KCMAINWINDOW_H
#define KCMAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QPointer>
#include <QTimer>
#include <QNetworkAccessManager>
#include "KCClient.h"
#include "KCToolServer.h"

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
	void _showDisclaimer();
	
protected:
	virtual void closeEvent(QCloseEvent *event);
	
public:
	bool isApplicationActive();
	
public slots:
	void toggleApplication();
	void showApplication();
	void hideApplication();
	
	void askForAPILink();
	void updateFleetsPage();
	void updateShipsPage();
	void updateRepairsPage();
	void updateConstructionsPage();
	void updateTimers();
	void updateSettingThings();
	
private slots:
	void onTranslationLoadFinished();
	void onTranslationLoadFailed(QString error);
	void onCredentialsGained();
	void onReceivedMasterShips();
	void onReceivedPlayerShips();
	void onReceivedPlayerFleets();
	void onReceivedPlayerRepairs();
	void onReceivedPlayerConstructions();
	void onRequestError(KCClient::ErrorCode error);
	
	void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
	void onDockCompleted(KCDock *dock);
	void onMissionCompleted(KCFleet *fleet);
	
	void on_actionFleets_triggered();
	void on_actionShips_triggered();
	void on_actionRepairs_triggered();
	void on_actionConstruction_triggered();
	void on_actionRefresh_triggered();
	void on_actionSettings_triggered();
	
	void on_fleetsTabBar_currentChanged(int index);
	
private:
	Ui::KCMainWindow *ui;
	
	QSystemTrayIcon *trayIcon;
	QMenu *trayMenu;
	QTimer timerUpdateTimer, refreshTimer;
	
	KCClient *client;
	KCToolServer *server;
	QNetworkAccessManager manager;
	
	bool apiLinkDialogOpen;
};

#endif // KCMAINWINDOW_H
