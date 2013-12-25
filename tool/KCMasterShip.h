#ifndef KCMASTERSHIP_H
#define KCMASTERSHIP_H

#include <QString>

class KCMasterShip
{
public:
	KCMasterShip(QVariant data);
	virtual ~KCMasterShip();
	
	QString name, reading;
	int rarity;
	int buildTime;	// In Minutes
	
	int remodelID, remodelLevel, remodelAmmo, remodelFuel;
};

#endif