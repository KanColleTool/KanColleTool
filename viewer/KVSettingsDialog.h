#ifndef KVSETTINGSDIALOG_H
#define KVSETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

class QAbstractButton;
class KVMainWindow;
namespace Ui {
	class KVSettingsDialog;
}

class KVSettingsDialog : public QDialog {
	Q_OBJECT

public:
	explicit KVSettingsDialog(KVMainWindow *parent=0, Qt::WindowFlags f=0);
	virtual ~KVSettingsDialog();

public slots:
	virtual void accept();
	virtual void setSettings();
	virtual void buttonClicked(QAbstractButton *button);

private slots:
	void on_proxyCheckbox_stateChanged(int state);

signals:
	void apply();

private:
	Ui::KVSettingsDialog *ui;
	QSettings settings;
};

#endif // KVSETTINGSDIALOG_H
