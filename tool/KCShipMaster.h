#ifndef KCSHIPMASTER_H
#define KCSHIPMASTER_H

#include <QObject>
#include <QVariant>

class KCShipMaster : public QObject
{
	Q_OBJECT

public:
	KCShipMaster(QObject *parent = 0);
	KCShipMaster(QVariantMap data = QVariantMap(), QObject *parent = 0);
	virtual ~KCShipMaster();

	void loadFrom(QVariantMap data);

	QString name, reading;
	QString description;
	int id, cardno, type, ctype, cindex;
	int rarity, buildTime;
	int maxAmmo, maxFuel;

	bool encountered;
	QString getMessage;

	struct { int level, into, ammo, fuel; } remodel;
	struct { int fuel, ammo, steel, baux; } dismantle;
	struct { int firepower, torpedo, antiair, armor; } modernization;

	struct { int base, max; } hp;
	struct { int base, max; } firepower;
	struct { int base, max; } torpedo;
	struct { int base, max; } antiair;
	struct { int base, max; } armor;
	struct { int base, max; } antisub;
	struct { int base, max; } evasion;
	struct { int base, max; } lineOfSight;
	struct { int base, max; } luck; // Luck can't be boosted anyways (and the max is stupidly high across the board...)
	int range;
	int speed;

	int planeCapacity[4];
	int equipmentSlots;

	int voicef;

	// Unknown values, saved to be able to look for exceptions from the
	// patterns we know (like _baku != {0,0})
	int _atap[2], _bakk[2], _baku[2];
	int _defeq[4], _grow[8], _gumax[4];
	int _houk[2], _houm[2], _raik[2], _raim[2];
	int _sakb[2], _tous[2];
	int _sokuh;
	QVariant _homemes, _gomes, _gomes2;
	QVariant _missions, _systems, _touchs[3];
};

#endif
