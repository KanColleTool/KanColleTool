#ifndef KCMAINWINDOW_H
#define KCMAINWINDOW_H

#include <QMainWindow>

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
	Ui::KCMainWindow *ui;
};

#endif // KCMAINWINDOW_H
