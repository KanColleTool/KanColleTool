#ifndef KVDEFAULTS_H
#define KVDEFAULTS_H

#include <QNetworkProxy>

const bool kDefaultTranslation = false;
const bool kDefaultProxy = false;
const QString kDefaultProxyServer = "localhost";
const int kDefaultProxyPort = 8080;
const int kDefaultProxyType = QNetworkProxy::Socks5Proxy;
const QString kDefaultProxyUser = "";
const QString kDefaultProxyPass = "";

#endif // KVDEFAULTS_H
