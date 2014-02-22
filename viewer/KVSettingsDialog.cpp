#include "KVSettingsDialog.h"
#include "ui_KVSettingsDialog.h"
#include "KVMainWindow.h"
#include "KVDefaults.h"

KVSettingsDialog::KVSettingsDialog(KVMainWindow *parent, Qt::WindowFlags f) :
	QDialog(parent, f),
	ui(new Ui::KVSettingsDialog)
{
	ui->setupUi(this);

	ui->translationCheckbox->setChecked(
		settings.value("viewerTranslation", kDefaultTranslation).toBool());

	this->adjustSize();
}

KVSettingsDialog::~KVSettingsDialog()
{

}

void KVSettingsDialog::done(int r)
{
	if(r == QDialog::Accepted)
	{
		settings.setValue("viewerTranslation", ui->translationCheckbox->isChecked());
		settings.sync();
	}

	QDialog::done(r);
}
