#ifndef KCSHIPMASTER_H
#define KCSHIPMASTER_H

#include <QObject>
#include <QVariant>

#include "KCGameObject.h"

class KCShipType : public KCGameObject {
	Q_OBJECT

public:
	KCShipType(const QVariantMap &data, int loadId=0, QObject *parent=0);
	virtual ~KCShipType();

	void loadFrom(const QVariantMap &data, int loadId) override;

	static constexpr int expToLv[150] = {
		0,       100,     300,     600,     1000,    1500,    2100,    2800,    3600,    4500,
		5500,    6600,    7800,    9100,    10500,   12000,   13600,   15300,   17100,   19000,
		21000,   23100,   25300,   27600,   30000,   32500,   35100,   37800,   40600,   43500,
		46500,   49600,   52800,   56100,   59500,   63000,   66600,   70300,   74100,   78000,
		82000,   86100,   90300,   94600,   99000,   103500,  108100,  112800,  117600,  122500,
		127500,  132700,  138100,  143700,  149500,  155500,  161700,  168100,  174700,  181500,
		188500,  195800,  203400,  211300,  219500,  228000,  236800,  245900,  255300,  265000,
		275000,  285400,  296200,  307400,  319000,  331000,  343400,  356200,  369400,  383000,
		397000,  411500,  426500,  442000,  458000,  474500,  491500,  509000,  527000,  545500,
		564500,  584500,  606500,  631500,  661500,  701500,  761500,  851500,  1000000, 1000000,
		1010000, 1011000, 1013000, 1016000, 1020000, 1025000, 1031000, 1038000, 1046000, 1055000,
		1065000, 1077000, 1091000, 1107000, 1125000, 1145000, 1168000, 1194000, 1223000, 1255000,
		1290000, 1329000, 1372000, 1419000, 1470000, 1525000, 1584000, 1647000, 1714000, 1785000,
		1860000, 1940000, 2025000, 2115000, 2210000, 2310000, 2415000, 2525000, 2640000, 2760000,
		2887000, 3021000, 3162000, 3310000, 3465000, 3628000, 3799000, 3978000, 4165000, 4360000
	};

	QString name, reading;
	QString description;
	int id, cardno, sclass, ctype, cindex;
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
