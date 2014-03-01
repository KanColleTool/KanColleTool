#include "KCToolServer.h"
#include <QTcpSocket>
#include "KCClient.h"

KCToolServer::KCToolServer(QObject *parent) :
	QTcpServer(parent), enabled(true), client(0) {
	connect(this, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

KCToolServer::~KCToolServer() {

}

void KCToolServer::setClient(KCClient *c) {
	client = c;
}

void KCToolServer::handleRequest(QTcpSocket *socket) {
	// Get the data out of it
	QString method = socket->property("method").toString();
	QString path = socket->property("path").toString();
	QByteArray content = socket->property("buffer").toByteArray();
	QVariantMap headers = socket->property("headers").toMap();

	// Write out a reply to the client
	socket->write("HTTP/1.1 204 No Content\r\n\r\n");

	// Handle POSTs
	if(method == "POST") {
		QVariant data = client->dataFromRawResponse(content);

		client->callPFunc(path, data);
	} else {
		// I might add other methods later (if I find a use), but for now, refuse them
		qDebug() << "Invalid Method:" << method << "(" << path << ")";
	}

	if(headers.value("Connection").toString() != "close") {
		// If it's not a Connection: close request, reset the state properties
		socket->setProperty("firstLineRead", QVariant());
		socket->setProperty("headerRead", QVariant());
		socket->setProperty("method", QVariant());
		socket->setProperty("path", QVariant());
		socket->setProperty("buffer", QVariant());
		socket->setProperty("headers", QVariant());
	} else {
		// Otherwise, close it behind us
		socket->close();
	}
}

void KCToolServer::onNewConnection() {
	while(this->hasPendingConnections()) 	{
		QTcpSocket *socket = this->nextPendingConnection();
		connect(socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));
	}
}

void KCToolServer::onSocketReadyRead()
{
	QTcpSocket *socket = qobject_cast<QTcpSocket*>(QObject::sender());

	// Parse the first line
	if(!socket->property("firstLineRead").toBool())
	{
		QString line(socket->readLine());
		int sepPos1(line.indexOf(" "));
		int sepPos2(line.indexOf(" ", sepPos1+1));
		QString method(line.left(sepPos1));
		QString path(line.mid(sepPos1+1, sepPos2 - sepPos1 - 1));
		socket->setProperty("method", method);
		socket->setProperty("path", path);
		socket->setProperty("firstLineRead", true);
	}

	// Parse Headers!
	if(!socket->property("headerRead").toBool()) {
		QVariantMap headers(socket->property("headers").toMap());

		while(socket->canReadLine()) {
			QString line = QString(socket->readLine()).trimmed();

			// The header section is terminated by an empty line
			if(line == "") {
				socket->setProperty("headerRead", true);
				break;
			}

			// Split it up
			int sepPos(line.indexOf(":"));
			QString key(line.left(sepPos).trimmed());
			QString val(line.mid(sepPos+1).trimmed());
			headers.insertMulti(key, val);
		}

		socket->setProperty("headers", headers);
	}

	qint64 contentLength = socket->property("headers").toMap().value("Content-Length").toLongLong();
	// Read the body into a buffer
	if(socket->bytesAvailable()) {
		QByteArray buffer(socket->property("buffer").toByteArray());
		qint64 toRead = contentLength - buffer.size();
		buffer.append(socket->read(toRead));
		socket->setProperty("buffer", buffer);
		socket->setProperty("toRead", contentLength - buffer.size());

		// If we have a Content-Length (toLong() fails with 0)
		if(contentLength > 0 && buffer.size() >= contentLength)
			this->handleRequest(socket);
	} else if(contentLength == -1 || contentLength == 0) {
		this->handleRequest(socket);
	}
}
