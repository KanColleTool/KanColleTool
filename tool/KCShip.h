#ifndef KCSHIP_H
#define KCSHIP_H

#include <QObject>
#include <QVariant>
#include <QMap>

class KCShip : public QObject
{
public:
	KCShip(QObject *parent = 0);
	KCShip(QVariantMap data = QVariantMap(), QObject *parent = 0);
	virtual ~KCShip();
	
	int master;
	
	QString name, reading;
	int id, admiral;
	int level, exp;
	bool heartLock;
	
	struct { int cur, max; } hpBase; // HP bar data below
	struct { int cur, max; } firepowerBase, firepower;
	struct { int cur, max; } torpedoBase, torpedo;
	struct { int cur, max; } antiairBase, antiair;
	struct { int cur, max; } antisubBase, antisub;
	struct { int cur, max; } armorBase, armor;
	struct { int cur, max; } evasion;
	struct { int cur, max; } lineOfSightBase, lineOfSight;
	struct { int cur, max; } luckBase, luck;
	int range, speed;
	
	int hp, maxHp;
	int ammo, maxAmmo, ammoCost;
	int fuel, maxFuel, fuelCost;
	int condition;
	
	int equipment[5];
	int equipmentSlots;
	
	struct { int steel, fuel; } repairCost;
	int repairTime;	// In Seconds
	QString repairTimeStr;
	
	// Unknown values
	int _houm[2], _raim[2];
	int _kyouka[4];
	int _onslot[5];
	
protected:
	void loadFrom(QVariantMap data);
};

#endif
