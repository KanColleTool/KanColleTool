#ifndef KCFLEET_H
#define KCFLEET_H

#include <QObject>
#include <QVariant>
#include <QMap>
#include <QDateTime>

class KCFleet : public QObject
{
public:
	KCFleet(QObject *parent = 0);
	KCFleet(QVariantMap data = QVariantMap(), QObject *parent = 0);
	virtual ~KCFleet();
	
	void loadFrom(QVariantMap data);
	
	int id, admiral;
	QString name;
	int ships[6];
	int shipCount;
	struct { int page; int no; QDateTime complete; } mission;
};

#endif
