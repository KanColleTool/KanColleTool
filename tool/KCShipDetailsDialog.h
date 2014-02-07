#ifndef KCSHIPDETAILSDIALOG_H
#define KCSHIPDETAILSDIALOG_H

#include <QDialog>

namespace Ui {
class KCShipDetailsDialog;
}

class KCShipDetailsDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit KCShipDetailsDialog(QWidget *parent = 0);
	~KCShipDetailsDialog();
	
private:
	Ui::KCShipDetailsDialog *ui;
};

#endif // KCSHIPDETAILSDIALOG_H
