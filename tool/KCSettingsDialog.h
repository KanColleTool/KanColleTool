#ifndef KCSETTINGSDIALOG_H
#define KCSETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
	class KCSettingsDialog;
}

class KCMainWindow;
class KCSettingsDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit KCSettingsDialog(KCMainWindow *parent = 0, Qt::WindowFlags f = 0);
	virtual ~KCSettingsDialog();
	
public slots:
	virtual void done(int r);
	
private:
	Ui::KCSettingsDialog *ui;
	QSettings settings;
};

#endif
