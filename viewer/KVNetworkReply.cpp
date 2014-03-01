#include "KVNetworkReply.h"

#include <QNetworkAccessManager>
#include <QBuffer>
#include <QTimer>
#include <QNetworkReply>
#include <QSslConfiguration>

#include "KVNetworkAccessManager.h"
#include "KVTranslator.h"

struct KVNetworkReplyPrivate {
	QNetworkReply *copied;

	QByteArray content;
	qint64 offset;
	bool translate;
	bool finished;

	QNetworkAccessManager *manager;
};

KVNetworkReply::KVNetworkReply(QObject *parent, QNetworkReply *toCopy,
                               QNetworkAccessManager *mgr, bool translate) :
	QNetworkReply(parent) {
	d = new KVNetworkReplyPrivate;
	d->finished = false;
	d->copied = toCopy;
	d->manager = mgr;
	d->translate = translate;

	setOperation(d->copied->operation());
	setRequest(d->copied->request());
	setUrl(d->copied->url());

	// Translate reply when it's complete
	connect(d->copied, SIGNAL(finished()), SLOT(handleResponse()));

	connect(d->copied, SIGNAL(encrypted()), SIGNAL(encrypted()));
	connect(d->copied, SIGNAL(metaDataChanged()), SIGNAL(metaDataChanged()));
}

KVNetworkReply::~KVNetworkReply() {
	delete d;
}

void KVNetworkReply::copyAttribute(QNetworkRequest::Attribute attr) {
	QVariant attribute = d->copied->attribute(attr);
	if(attribute.isValid())
		setAttribute(attr, attribute);
}

void KVNetworkReply::handleResponse() {
	if(d->finished) return;

	setError(d->copied->error(), d->copied->errorString());

	copyAttribute(QNetworkRequest::HttpStatusCodeAttribute);
	copyAttribute(QNetworkRequest::HttpReasonPhraseAttribute);
	copyAttribute(QNetworkRequest::RedirectionTargetAttribute);
	copyAttribute(QNetworkRequest::ConnectionEncryptedAttribute);
	copyAttribute(QNetworkRequest::SourceIsFromCacheAttribute);
	copyAttribute(QNetworkRequest::HttpPipeliningWasUsedAttribute);

	QList<QNetworkReply::RawHeaderPair> headers = d->copied->rawHeaderPairs();
	for(int i = 0; i < headers.size(); i++)
		setRawHeader(headers[i].first, headers[i].second);

	QString data = d->copied->readAll();
	d->copied->abort();

	//qDebug() << "content:" << data;

	if(d->translate)
		data = KVTranslator::instance()->translateJson(data).toUtf8();

	d->content = data.toUtf8();
	d->offset = 0;
	setHeader(QNetworkRequest::ContentLengthHeader, QVariant(d->content.size()));

	QNetworkRequest toolReq(QUrl("http://localhost:54321").resolved(url().path()));
	toolReq.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/json"));
	d->manager->post(toolReq, d->content);

	open(ReadOnly | Unbuffered);
	//qDebug() << "translated:" << d->content.constData();

	d->finished = true;

	emit finished();
	emit readChannelFinished();
}

qint64 KVNetworkReply::bytesAvailable() const {
	return d->content.size() - d->offset + QIODevice::bytesAvailable();
}

qint64 KVNetworkReply::readData(char *data, qint64 maxSize) {
	if (d->offset >= d->content.size())
		return -1;

	qint64 numBytes = qMin(maxSize, d->content.size() - d->offset);
	memcpy(data, d->content.constData() + d->offset, numBytes);
	d->offset += numBytes;

	return numBytes;
}

/*
 * Pass all these through to the underlying 'copied' QNetworkRequest because
 * There isn't a copy constructor. I now understand why everything in the
 * standard libraries has a copy constructor...
 */
void KVNetworkReply::ignoreSslErrors(const QList<QSslError> &errors) {
	d->copied->ignoreSslErrors(errors);
}

QNetworkAccessManager* KVNetworkReply::manager() const {
	return d->copied->manager();
}

void KVNetworkReply::setSslConfiguration(const QSslConfiguration &config) {
	d->copied->setSslConfiguration(config);
}

QSslConfiguration KVNetworkReply::sslConfiguration() const {
	return d->copied->sslConfiguration();
}

bool KVNetworkReply::event(QEvent *e) {
	return d->copied->event(e);
}

void KVNetworkReply::abort() {
	d->finished = true; d->copied->abort();
}

void KVNetworkReply::ignoreSslErrors() {
	d->copied->ignoreSslErrors();
}

bool KVNetworkReply::isSequential() const {
	return true;
}
