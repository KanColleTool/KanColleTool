#include "KCSettingsDialog.h"
#include "ui_KCSettingsDialog.h"
#include "KCMainWindow.h"
#include "KCDefaults.h"

KCSettingsDialog::KCSettingsDialog(KCMainWindow *parent, Qt::WindowFlags f):
	QDialog(parent, f),
	ui(new Ui::KCSettingsDialog)
{
	ui->setupUi(this);
	
	ui->minimizeToTrayCheckbox->setChecked(settings.value("minimizeToTray", kDefaultMinimizeToTray).toBool());
	ui->translationCheckbox->setChecked(settings.value("toolTranslation", kDefaultTranslation).toBool());
	ui->livestreamCheckbox->setChecked(settings.value("livestream", kDefaultLivestream).toBool());
	ui->autorefreshCheckbox->setChecked(settings.value("autorefresh", kDefaultAutorefresh).toBool());
	ui->autorefreshInterval->setTime(QTime(0,0,0,0).addSecs(settings.value("autorefreshInterval", kDefaultAutorefresh).toInt()));
	
	// This whole thing makes no sense on OSX, so just hide the whole box there
	// The application is always running (only) in the menu bar there
#ifdef __APPLE__
	ui->minimizeToTrayContainer->hide();
#endif
	
	// Autoadjust the size to fit, because that's easier than trying to make it
	// look everywhere good manually. Takes into account font size differences
	// and stuff too, so yeah.
	this->adjustSize();
}

KCSettingsDialog::~KCSettingsDialog()
{
	
}

void KCSettingsDialog::done(int r)
{
	if(r == QDialog::Accepted)
	{
		settings.setValue("minimizeToTray", ui->minimizeToTrayCheckbox->isChecked());
		settings.setValue("toolTranslation", ui->translationCheckbox->isChecked());
		settings.setValue("livestream", ui->livestreamCheckbox->isChecked());
		settings.setValue("autorefresh", ui->autorefreshCheckbox->isChecked());
		settings.setValue("autorefreshInterval", QTime(0,0,0,0).secsTo(ui->autorefreshInterval->time()));
		settings.sync();
	}
	
	QDialog::done(r);
}
