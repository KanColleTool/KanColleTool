#include "KVNetworkReply.h"

#include <QNetworkAccessManager>
#include <QBuffer>
#include <QTimer>

#include "KVTranslator.h"

struct KVNetworkReplyPrivate
{
	QNetworkReply *copied;

	QByteArray content;
	qint64 offset;
	bool finished;
};

KVNetworkReply::KVNetworkReply(QObject *parent, QNetworkReply *toCopy)
	: QNetworkReply(parent)
{
	d = new KVNetworkReplyPrivate;
	d->copied = toCopy;

	setOperation(d->copied->operation());
	setRequest(d->copied->request());
	setUrl(d->copied->url());

	// Translate reply when it's complete
	connect(d->copied, SIGNAL(finished()), this, SLOT(translateRequest()));

	connect(d->copied, SIGNAL(encrypted()), this, SIGNAL(encrypted()));
}

KVNetworkReply::~KVNetworkReply()
{
	delete d;
}

void KVNetworkReply::copyAttribute(QNetworkRequest::Attribute attr)
{
	QVariant attribute = d->copied->attribute(attr);
	if(attribute.isValid())
		setAttribute(attr, attribute);
}

void KVNetworkReply::translateRequest()
{
	if(isFinished()) return;

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

	//qDebug() << "to translate:" << data.constData();

	KVTranslator *translator = KVTranslator::instance();
	data = translator->translateJson(data);

	d->content = data.toUtf8();
	d->offset = 0;
	setHeader(QNetworkRequest::ContentLengthHeader, QVariant(d->content.size()));

	open(ReadOnly | Unbuffered);
	//qDebug() << "translated:" << d->content.constData();

	setFinished(true);

	emit finished();
	emit readChannelFinished();
	emit readyRead();
}

// Whether this reply has finished loading
bool KVNetworkReply::isFinished() const { return d->finished; }
bool KVNetworkReply::isRunning() const { return !d->finished; }
void KVNetworkReply::setFinished(bool finished) { d->finished = finished; }

qint64 KVNetworkReply::bytesAvailable() const
{
	return d->content.size() - d->offset + QIODevice::bytesAvailable();
}

qint64 KVNetworkReply::readData(char *data, qint64 maxSize)
{
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
void KVNetworkReply::ignoreSslErrors(const QList<QSslError> &errors)
{ d->copied->ignoreSslErrors(errors); }
QNetworkAccessManager* KVNetworkReply::manager() const
{ return d->copied->manager(); }
void KVNetworkReply::setSslConfiguration(const QSslConfiguration &config)
{ d->copied->setSslConfiguration(config); }
QSslConfiguration KVNetworkReply::sslConfiguration() const
{ return d->copied->sslConfiguration(); }
bool KVNetworkReply::event(QEvent *e)
{ return d->copied->event(e); }
void KVNetworkReply::close()
{ QNetworkReply::close(); d->copied->close(); }

void KVNetworkReply::abort()
{ setFinished(true); d->copied->abort(); }
void KVNetworkReply::ignoreSslErrors()
{ d->copied->ignoreSslErrors(); }
bool KVNetworkReply::isSequential() const
{	return true; }
