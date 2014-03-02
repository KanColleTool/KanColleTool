#ifndef KCSHIP_H
#define KCSHIP_H

#include <QObject>
#include <QVariant>
#include <QMap>

#include "KCGameObject.h"

class KCShip : public KCGameObject {
	Q_OBJECT

public:
	KCShip(const QVariantMap &data, int loadId=0, QObject *parent=0);
	virtual ~KCShip();

	void loadFrom(const QVariantMap &data, int loadId) override;

	int master;

	int id;
	int level, exp;

	struct { int cur, max; } hp;
	struct { int cur, max; } firepower;
	struct { int cur, max; } torpedo;
	struct { int cur, max; } antiair;
	struct { int cur, max; } antisub;
	struct { int cur, max; } armor;
	struct { int cur, max; } evasion;
	struct { int cur, max; } lineOfSight;
	struct { int cur, max; } luck;

	int ammo, fuel;
	int condition;

	int equipment[5];
	int equipmentSlots;

	struct { int steel, fuel; } repairCost;
	int repairTime;	// In Seconds
	QString repairTimeStr;

	bool heartLock;

	// Unknown values
	int _kyouka[4];
	int _onslot[5];
};

#endif
