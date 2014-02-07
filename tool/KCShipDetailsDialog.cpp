#include "KCShipDetailsDialog.h"
#include "ui_KCShipDetailsDialog.h"

KCShipDetailsDialog::KCShipDetailsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::KCShipDetailsDialog)
{
	ui->setupUi(this);
}

KCShipDetailsDialog::~KCShipDetailsDialog()
{
	delete ui;
}
