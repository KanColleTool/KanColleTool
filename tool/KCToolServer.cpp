#include "KCToolServer.h"
#include <QLocalSocket>
#include "KCClient.h"

KCToolServer::KCToolServer(QObject *parent) :
	QLocalServer(parent), enabled(true), client(0) {
	connect(this, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

KCToolServer::~KCToolServer() {

}

void KCToolServer::setClient(KCClient *c) {
	client = c;
}

void KCToolServer::handleRequest(QLocalSocket *socket) {
	// Get the data out of it
	QString operation = socket->property("operation").toString();
	QString path = socket->property("path").toString();
	QByteArray content = socket->property("buffer").toByteArray();

	if(operation == "data") {
		// Handle data from client
		QVariant data = client->dataFromRawResponse(content);

		client->callPFunc(path, data);
	} else {
		qDebug() << "Invalid Operation:" << operation << "(" << path << ")";
	}

	socket->setProperty("firstLineRead", QVariant());
	socket->setProperty("method", QVariant());
	socket->setProperty("path", QVariant());
	socket->setProperty("buffer", QVariant());
}

void KCToolServer::onNewConnection() {
	if(client) {
		while(this->hasPendingConnections()) {
			QLocalSocket *socket = this->nextPendingConnection();
			connect(socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));
		}
	}
}

void KCToolServer::onSocketReadyRead() {
	QLocalSocket *socket = qobject_cast<QLocalSocket*>(QObject::sender());

	// Parse the first line
	if(!socket->property("firstLineRead").toBool()) {
		QList<QByteArray> props = socket->readLine().simplified().split(' ');

		if(!props.size()) return;
		socket->setProperty("operation", props.at(0));

		if(props.at(0) == "focus") {
			//qDebug() << "focus requested";
			emit focusRequested();
			return;
		}
		if(!enabled) return;

		if(props.size() > 2) {
			socket->setProperty("path", props.at(1));
			socket->setProperty("length", props.at(2).toLongLong());
		}
		socket->setProperty("firstLineRead", true);
	}

	qint64 contentLength = socket->property("length").toLongLong();

	// Read the body into a buffer
	if(socket->bytesAvailable()) {
		QByteArray buffer(socket->property("buffer").toByteArray());
		buffer.append(socket->read(contentLength));
		socket->setProperty("buffer", buffer);

		// If we have a Content-Length (toLong() fails with 0)
		if(contentLength > 0 && buffer.size() >= contentLength) {
			this->handleRequest(socket);
		}
	} else if(contentLength == -1 || contentLength == 0) {
		this->handleRequest(socket);
	}
}
