#ifndef KVNETWORKREPLY_H
#define KVNETWORKREPLY_H

#include <QNetworkReply>
#include <QByteArray>

/*
 * This class is a bit complicated in its function, so it deserves a proper
 * explanation. It's a thin wrapper around QNetworkReply, that just leeches off
 * an existing reply.
 * 
 * When the wrapped reply finishes, the wrapper copies its data into itself,
 * throws the contents at the translator, then pretends to have received all of
 * the data in one single chunk (with a Content-Length set) and immediately
 * emits its own finished() signal to deliver the response.
 * 
 * This class is created by KVNetworkAccessManager, and should ONLY be used for
 * API calls; you can probably imagine yourself what'd happen if a large GET
 * got this treatment.
 * 
 * Inspired by a blog post by Richard Moore (and I stole his readData() impl):
 * https://blogs.kde.org/2010/08/28/implementing-reusable-custom-qnetworkreply
 */
class KVNetworkReply : public QNetworkReply
{
	Q_OBJECT
	
public:
	KVNetworkReply(QNetworkReply *wrappedReply, QObject *parent = 0); //Protected in the superclass
	~KVNetworkReply();
	
	// Reimplemented
	virtual qint64 bytesAvailable() const;
	virtual bool isSequential() const;
	
	// Forwarded
	virtual void setReadBufferSize(qint64 size);
	
public slots:
	// Reimplemented
	virtual void abort();
	
	// Forwarded
	virtual void ignoreSslErrors();
	
protected:
	// Reimplemented
	virtual qint64 readData(char *data, qint64 maxSize);
	
private slots:
	void onWrappedReplyFinished();
	
private:
	void cloneWrappedReply();
	void processBuffer();
	
	QNetworkReply *wrappedReply;
	QByteArray buffer;
	qint64 offset;
};

#endif
