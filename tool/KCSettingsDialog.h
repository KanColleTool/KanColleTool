#ifndef KCSETTINGSDIALOG_H
#define KCSETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

class QAbstractButton;
class KCMainWindow;
namespace Ui {
	class KCSettingsDialog;
}

class KCSettingsDialog : public QDialog {
	Q_OBJECT

public:
	explicit KCSettingsDialog(KCMainWindow *parent = 0, Qt::WindowFlags f = 0);
	virtual ~KCSettingsDialog();

public slots:
	virtual void accept();
	virtual void setSettings();
	virtual void buttonClicked(QAbstractButton *button);

private slots:
	void on_useNetworkCheckbox_stateChanged(int state);
	void on_autorefreshCheckbox_stateChanged(int state);

signals:
	void apply();

private:
	Ui::KCSettingsDialog *ui;
	QSettings settings;
};

#endif
