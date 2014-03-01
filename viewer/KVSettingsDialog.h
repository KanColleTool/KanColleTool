#ifndef KVSETTINGSDIALOG_H
#define KVSETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

class QAbstractButton;
namespace Ui {
	class KVSettingsDialog;
}

class KVMainWindow;
class KVSettingsDialog : public QDialog {
	Q_OBJECT

public:
	explicit KVSettingsDialog(KVMainWindow *parent=0, Qt::WindowFlags f=0);
	virtual ~KVSettingsDialog();

public slots:
	virtual void accept();
	virtual void setSettings();
	virtual void buttonClicked(QAbstractButton *button);

signals:
	void apply();

private:
	Ui::KVSettingsDialog *ui;
	QSettings settings;
};

#endif // KVSETTINGSDIALOG_H
