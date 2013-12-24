#ifndef KCPLAYERSHIP_H
#define KCPLAYERSHIP_H

#include <QString>

class KCPlayerShip
{
public:
	KCPlayerShip(QVariant data);
	virtual ~KCPlayerShip();
	
	QString name, reading;
	int rarity;
	int remodelLevel, remodelID;
};

#endif