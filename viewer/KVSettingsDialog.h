#ifndef KVSETTINGSDIALOG_H
#define KVSETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
	class KVSettingsDialog;
}

class KVMainWindow;
class KVSettingsDialog : public QDialog
{
	Q_OBJECT

public:
	explicit KVSettingsDialog(KVMainWindow *parent=0, Qt::WindowFlags f=0);
	virtual ~KVSettingsDialog();

public slots:
	virtual void done(int r);

private:
	Ui::KVSettingsDialog *ui;
	QSettings settings;
};

#endif // KVSETTINGSDIALOG_H
