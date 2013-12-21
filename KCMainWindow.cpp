#include "KCMainWindow.h"
#include "ui_KCMainWindow.h"

KCMainWindow::KCMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::KCMainWindow)
{
	ui->setupUi(this);
}

KCMainWindow::~KCMainWindow()
{
	delete ui;
}
