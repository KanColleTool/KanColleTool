#include "KCShipMaster.h"
#include "KCWrapperUtils.h"

KCShipMaster::KCShipMaster(QObject *parent) : KCShipMaster(QVariantMap(), parent) {}

KCShipMaster::KCShipMaster(QVariantMap data, QObject *parent):
	QObject(parent)
{
	loadFrom(data);
}

KCShipMaster::~KCShipMaster()
{
	
}

void KCShipMaster::loadFrom(QVariantMap data)
{
	// All of these are retrieved in the order they are in the API responses
	// to make debugging eventual incorrect values easier.
	extract(data, remodel.ammo, "api_afterbull");
	extract(data, remodel.fuel, "api_afterfuel");
	extract(data, remodel.level, "api_afterlv");
	extract(data, remodel.into, "api_aftershipid");
	extract(data, _atap, 2, "api_atap");
	extract(data, rarity, "api_backs");
	extract(data, _bakk, 2, "api_bakk");
	extract(data, _baku, 2, "api_baku");
	extract(data, dismantle.fuel, "api_broken", 0);
	extract(data, dismantle.ammo, "api_broken", 1);
	extract(data, dismantle.steel, "api_broken", 2);
	extract(data, dismantle.bauxite, "api_broken", 3);
	extract(data, buildTime, "api_buildtime");
	extract(data, maxAmmo, "api_bull_max");
	extract(data, cindex, "api_cnum");
	extract(data, ctype, "api_ctype");
	extract(data, _defeq, 4, "api_defeq");
	extract(data, encountered, "api_enqflg");
	extract(data, maxFuel, "api_fuel_max");
	extract(data, getMessage, "api_getmes");
	extract(data, _grow, 8, "api_grow");
	extract(data, _gumax, 4, "api_gumax");
	extract(data, firepower.base, "api_houg", 0);
	extract(data, firepower.max, "api_houg", 1);
	extract(data, _houk, 2, "api_houk");
	extract(data, _houm, 2, "api_houm");
	extract(data, id, "api_id");
	extract(data, evasion.base, "api_kaih", 0);
	extract(data, evasion.max, "api_kaih", 1);
	extract(data, range, "api_leng");
	extract(data, luck.base, "api_luck", 0);
	extract(data, luck.max, "api_luck", 1);
	extract(data, planeCapacity, 4, "api_maxeq");
	extract(data, _missions, "api_missions");
	extract(data, modernization.firepower, "api_powup", 0);
	extract(data, modernization.torpedo, "api_powup", 1);
	extract(data, modernization.antiair, "api_powup", 2);
	extract(data, modernization.armor, "api_powup", 3);
	extract(data, torpedo.base, "api_raig", 0);
	extract(data, torpedo.max, "api_raig", 1);
	extract(data, _raik, 2, "api_raik");
	extract(data, _raim, 2, "api_raim");
	extract(data, _sakb, 2, "api_sakb");
	extract(data, lineOfSight.base, "api_saku", 0);
	extract(data, lineOfSight.max, "api_saku", 1);
	extract(data, description, "api_sinfo");
	extract(data, equipmentSlots, "api_slot_num");
	extract(data, cardno, "api_sortno");
	extract(data, armor.base, "api_souk", 0);
	extract(data, armor.max, "api_souk", 1);
	extract(data, type, "api_stype");
	extract(data, _systems, "api_systems");
	extract(data, hp.base, "api_taik", 0);
	extract(data, hp.max, "api_taik", 1);
	extract(data, antisub.base, "api_tais", 0);
	extract(data, antisub.max, "api_tais", 1);
	extract(data, _touchs, 3, "api_touchs");
	extract(data, _tous, 2, "api_tous");
	extract(data, antiair.base, "api_tyku", 0);
	extract(data, antiair.max, "api_tyku", 1);
	extract(data, voicef, "api_voicef");
	extract(data, reading, "api_yomi");
}
