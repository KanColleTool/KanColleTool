#include <QtTest/QtTest>

#include <QNetworkRequest>
#include <QNetworkReply>

#include "../src/KVTranslator.h"

class TestKVTranslator : public QObject {
	Q_OBJECT
private slots:
	void initTestCase();
	void simpleTest();
	void realTest();
	void failTest();
};

void TestKVTranslator::initTestCase() {
	KVTranslator::instance()->loadTranslation();
}

void TestKVTranslator::simpleTest() {
	QByteArray toTranslate = "svdata={\"object\":{\"key1\":\"string\", \"key2\":\"string\", \"arr_in_obj\":[1,0,0,3]},\"array\": [\"string\"\t,\t\t\"string1\", 343, null, false],\r\n\"bool\": true, \"key_with\\nnewline\": null,\"array_of_objs\":[{\"id\":0,\"data\":\"string with\\n\\twhitespace\"},{\"id\":1,\"unicode_data\":\"\\u2000\\u20ff\"},{\"id\":2,\"haruna\":\"\u699B\u540D\"}]}";

	QByteArray translated = KVTranslator::instance()->translateJson(toTranslate);
	QCOMPARE(translated.constData(), "svdata={\"object\":{\"key1\":\"string\", \"key2\":\"string\", \"arr_in_obj\":[1,0,0,3]},\"array\": [\"string\"\t,\t\t\"string1\", 343, null, false],\r\n\"bool\": true, \"key_with\\nnewline\": null,\"array_of_objs\":[{\"id\":0,\"data\":\"string with\\n\\twhitespace\"},{\"id\":1,\"unicode_data\":\"\\u2000\\u20ff\"},{\"id\":2,\"haruna\":\"Haruna\"}]}");
}

void TestKVTranslator::realTest() {
	QNetworkAccessManager manager;
	QNetworkRequest request(QString("http://kancolletool.github.io/kctool/mastership.json"));
	QNetworkReply *reply = manager.get(request);
	QEventLoop loop;
	loop.connect(reply, SIGNAL(finished()), SLOT(quit()));
	loop.exec();
	QByteArray toTranslate = reply->readAll();
	QByteArray translated = KVTranslator::instance()->translateJson(toTranslate);
	QVERIFY(translated != toTranslate);
	// Compare with something...
}

void TestKVTranslator::failTest() {

}

QTEST_MAIN(TestKVTranslator)
#include "TestKVTranslator.moc"
