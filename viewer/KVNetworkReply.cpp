#include "KVNetworkReply.h"
#include <QTimer>
#include <QDebug>

#define CLONE_ATTRIBUTE(_att) this->setAttribute(_att, wrappedReply->attribute(_att))

KVNetworkReply::KVNetworkReply(QNetworkReply *wrappedReply, QObject *parent):
	QNetworkReply(parent), wrappedReply(wrappedReply)
{
	connect(wrappedReply, SIGNAL(finished()), this, SLOT(onWrappedReplyFinished()));
}

KVNetworkReply::~KVNetworkReply()
{
	
}

qint64 KVNetworkReply::bytesAvailable() const
{
	return buffer.size() - offset;
}

bool KVNetworkReply::isSequential() const
{
	return true;
}

void KVNetworkReply::setReadBufferSize(qint64 size)
{
	wrappedReply->setReadBufferSize(size);
}

void KVNetworkReply::abort()
{
	wrappedReply->abort();
}

void KVNetworkReply::ignoreSslErrors()
{
	wrappedReply->ignoreSslErrors();
}

qint64 KVNetworkReply::readData(char *data, qint64 len)
{
	if(offset >= buffer.size())
		return -1;
	
	qint64 number = qMin(len, buffer.size() - offset);
	memcpy(data, buffer.constData() + offset, number);
	offset += number;
	
	return number;
}

void KVNetworkReply::onWrappedReplyFinished()
{
	this->cloneWrappedReply();
	
	buffer = wrappedReply->readAll();
	offset = 0;
	
	this->processBuffer();
	
	this->open(QIODevice::ReadOnly|QIODevice::Unbuffered);
	this->setHeader(QNetworkRequest::ContentLengthHeader, buffer.size());
	
	// Pretend like the whole response was just received in one big chunk, and
	// immediately finished. This will get queued up and spread over two ticks
	// of the Qt event loop by the way timers work.
	QTimer::singleShot(0, this, SIGNAL(readyRead()));
	QTimer::singleShot(0, this, SIGNAL(finished()));
}

void KVNetworkReply::cloneWrappedReply()
{
	// Clone misc things (must be done before attributes and headers)
	this->setError(wrappedReply->error(), wrappedReply->errorString());
	this->setFinished(wrappedReply->isFinished());
	this->setOperation(wrappedReply->operation());
	this->setRequest(wrappedReply->request());
	this->setUrl(wrappedReply->url());
	
	// Clone Attributes
	CLONE_ATTRIBUTE(QNetworkRequest::HttpStatusCodeAttribute);
	CLONE_ATTRIBUTE(QNetworkRequest::HttpReasonPhraseAttribute);
	CLONE_ATTRIBUTE(QNetworkRequest::RedirectionTargetAttribute);
	CLONE_ATTRIBUTE(QNetworkRequest::ConnectionEncryptedAttribute);
	CLONE_ATTRIBUTE(QNetworkRequest::CacheLoadControlAttribute);
	CLONE_ATTRIBUTE(QNetworkRequest::CacheSaveControlAttribute);
	CLONE_ATTRIBUTE(QNetworkRequest::SourceIsFromCacheAttribute);
	CLONE_ATTRIBUTE(QNetworkRequest::DoNotBufferUploadDataAttribute);
	CLONE_ATTRIBUTE(QNetworkRequest::HttpPipeliningAllowedAttribute);
	CLONE_ATTRIBUTE(QNetworkRequest::HttpPipeliningWasUsedAttribute);
	CLONE_ATTRIBUTE(QNetworkRequest::CustomVerbAttribute);
	CLONE_ATTRIBUTE(QNetworkRequest::CookieLoadControlAttribute);
	CLONE_ATTRIBUTE(QNetworkRequest::CookieSaveControlAttribute);
	CLONE_ATTRIBUTE(QNetworkRequest::AuthenticationReuseAttribute);
	CLONE_ATTRIBUTE(QNetworkRequest::BackgroundRequestAttribute);
	
	// Clone Headers
	foreach(QNetworkReply::RawHeaderPair pair, wrappedReply->rawHeaderPairs())
		this->setRawHeader(pair.first, pair.second);
}

void KVNetworkReply::processBuffer()
{
	qDebug() << "Put some buffer processing here";
	qDebug() << buffer;
}
