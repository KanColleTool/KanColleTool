#include <QAbstractButton>

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
	ui->proxyCheckbox->setChecked(settings.value("proxy", kDefaultProxy).toBool());
	ui->proxyServerEdit->setText(settings.value("proxyServer", kDefaultProxyServer).toString());
	ui->proxyPortBox->setValue(settings.value("proxyPort", kDefaultProxyPort).toInt());
	ui->proxyUserEdit->setText(settings.value("proxyUser", kDefaultProxyUser).toString());
	ui->proxyPassEdit->setText(settings.value("proxyPass", kDefaultProxyPass).toString());
	switch(settings.value("proxyType", kDefaultProxyType).toInt())
	{
	default:
	case QNetworkProxy::Socks5Proxy:
		ui->socksProxyRadio->setChecked(true);
		break;
	case QNetworkProxy::HttpProxy:
		ui->httpProxyRadio->setChecked(true);
		break;
	}

	this->adjustSize();
	this->setFixedSize(this->size());
}

KVSettingsDialog::~KVSettingsDialog()
{

}

void KVSettingsDialog::done(int r)
{
	if(r == QDialog::Accepted) {
		settings.setValue("viewerTranslation", ui->translationCheckbox->isChecked());
		settings.setValue("proxy", ui->proxyCheckbox->isChecked());
		settings.setValue("proxyServer", ui->proxyServerEdit->text());
		settings.setValue("proxyPort", ui->proxyPortBox->value());
		if(ui->socksProxyRadio->isChecked())
			settings.setValue("proxyType", QNetworkProxy::Socks5Proxy);
		else if(ui->httpProxyRadio->isChecked())
			settings.setValue("proxyType", QNetworkProxy::HttpProxy);

		settings.sync();
	}

	QDialog::done(r);
}
