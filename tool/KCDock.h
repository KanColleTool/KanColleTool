#ifndef KCDOCK_H
#define KCDOCK_H

#include <QObject>
#include <QVariant>
#include <QMap>
#include <QDateTime>
#include <QTimer>

class KCClient;
class KCDock : public QObject
{
	Q_OBJECT
public:
	enum State {
		Locked = -1,
		Empty = 0,
		Occupied = 1,
		Building = 2,
		Finished = 3
	};
	
	KCDock(QObject *parent = 0);
	KCDock(QVariantMap data = QVariantMap(), QObject *parent = 0);
	KCDock(KCClient *parent = 0);
	KCDock(QVariantMap data = QVariantMap(), KCClient *parent = 0);
	virtual ~KCDock();
	
	void loadFrom(QVariantMap data);
	
	int id;
	int state;
	int shipID;
	QDateTime complete;
	int fuel, ammo, steel, baux;
	bool isConstruction;
	
signals:
	void completed();
	
private slots:
	void onTimeout();
	
private:
	QTimer timer;
};

#endif // KCDOCK_H
