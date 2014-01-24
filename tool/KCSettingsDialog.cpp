#include "KCSettingsDialog.h"
#include "ui_KCSettingsDialog.h"
#include "KCMainWindow.h"
#include "KCDefaults.h"

KCSettingsDialog::KCSettingsDialog(KCMainWindow *parent, Qt::WindowFlags f):
	QDialog(parent, f),
	ui(new Ui::KCSettingsDialog)
{
	ui->setupUi(this);
	
	ui->autorefreshInterval->setSelectedSection(QDateTimeEdit::MinuteSection);
	
	// Livestreaming is not yet implemented
	//ui->livestreamCheckbox->setChecked(settings.value("livestream", kDefaultLivestream).toBool());
	ui->autorefreshCheckbox->setChecked(settings.value("autorefresh", kDefaultAutorefresh).toBool());
	ui->autorefreshInterval->setTime(QTime(0,0,0,0).addSecs(settings.value("autorefreshInterval", kDefaultAutorefresh).toInt()));
}

KCSettingsDialog::~KCSettingsDialog()
{
	
}

void KCSettingsDialog::done(int r)
{
	if(r == QDialog::Accepted)
	{
		//settings.setValue("livestream", ui->livestreamCheckbox->isChecked());
		settings.setValue("autorefresh", ui->autorefreshCheckbox->isChecked());
		settings.setValue("autorefreshInterval", QTime(0,0,0,0).secsTo(ui->autorefreshInterval->time()));
		settings.sync();
	}
	
	QDialog::done(r);
}
