#ifndef KCFLEET_H
#define KCFLEET_H

#include <QObject>
#include <QVariant>
#include <QMap>

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
};

#endif
