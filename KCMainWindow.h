#ifndef KCMAINWINDOW_H
#define KCMAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QSystemTrayIcon>

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
	
public:
	bool isApplicationActive();
	
public slots:
	void toggleApplication();
	void showApplication();
	void hideApplication();
	
	void askForAPILink();
	
private slots:
	void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
	
private:
	Ui::KCMainWindow *ui;
	
	QSystemTrayIcon *trayIcon;
	QMenu *trayMenu;
	
	QString server, apiToken;
};

#endif // KCMAINWINDOW_H
