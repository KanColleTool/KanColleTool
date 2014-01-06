#ifndef KCDOCK_H
#define KCDOCK_H

#include <QObject>
#include <QVariant>
#include <QMap>
#include <QDateTime>

class KCDock : public QObject
{
	Q_OBJECT
public:
	enum State {
		Locked = -1,
		Empty = 1,
		Occupied = 2,
		Finished = 3
	};
	
	KCDock(QObject *parent = 0);
	KCDock(QVariantMap data = QVariantMap(), QObject *parent = 0);
	virtual ~KCDock();
	
	void loadFrom(QVariantMap data);
	
	int id;
	State state;
	int shipID;
	QDateTime complete;
	int fuel, ammo, steel, baux;
};

#endif // KCDOCK_H
