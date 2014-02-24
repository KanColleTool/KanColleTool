#include "KCShip.h"
#include "KCWrapperUtils.h"

KCShip::KCShip(QObject *parent) : KCShip(QVariantMap(), parent) {}

KCShip::KCShip(QVariantMap data, QObject *parent, bool use2):
	QObject(parent)
{
	if(use2) loadFrom2(data);
	else loadFrom(data);
}

KCShip::~KCShip()
{

}

void KCShip::loadFrom(const QVariantMap &data) {
	// Unlike KCShipMaster, I'm keeping only the values we actually use here.
	// The Master object has most of this stuff already, so we're just keeping
	// the individual girl's values here.
	// (And her name, because not letting her keep her own name would be mean.)
	// Again, in the same order as in the API response to make missing values
	// easier to spot, not like it's really needed here...

	// int api_afterlv - Remodel level
	// int api_aftershipid - Remodels into...
	// int api_backs - Rarity
	// int[4] api_baku - Seems unused...
	// int[4] api_broken - Resources gained for deconstructing her
	// int api_bull - Bullets held
	extract(data, ammo, "api_bull");
	// int api_bull_max - Bullet capacity
	extract(data, maxAmmo, "api_bull_max");
	// int api_cond - Condition (fatigue)
	extract(data, condition, "api_cond");
	// int api_exp - Total EXP
	extract(data, exp, "api_exp");
	// int api_fuel - Fuel
	extract(data, fuel, "api_fuel");
	// int api_fuel_max - Fuel capacity
	extract(data, maxFuel, "api_fuel_max");
	// ??? api_gomes - ??? (always null?)
	// ??? api_gomes2 - ??? (always null?)
	// int[2] api_houg - Firepower, with modernization (cur, max)
	extract(data, firepowerBase.cur, "api_houg", 0);
	extract(data, firepowerBase.max, "api_houg", 1);
	// int[2] api_houm - ???
	extract(data, _houm, 2, "api_houm");
	// int api_id - Her local ID (just an identifier in your deck)
	extract(data, id, "api_id");
	// int[2] api_kaihi - Evasion, with equipment
	extract(data, evasion.cur, "api_kaihi", 0);
	extract(data, evasion.max, "api_kaihi", 1);
	// int[2] api_karyoku - Firepower, with modernization and equipment (cur, max)
	extract(data, firepower.cur, "api_karyoku", 0);
	extract(data, firepower.max, "api_karyoku", 1);
	// int[4] api_kyouka - Something to do with modernization
	extract(data, _kyouka, 4, "api_kyouka");
	// int api_leng - Range
	extract(data, range, "api_leng");
	// int[2] api_luck - Luck, with modernizations (current, max)
	extract(data, luckBase.cur, "api_luck", 0);
	extract(data, luckBase.max, "api_luck", 1);
	// int[2] api_lucky - Luck, with modernization and equipment (current, max)
	extract(data, luck.cur, "api_lucky", 0);
	extract(data, luck.max, "api_lucky", 1);
	// int api_lv - Level
	extract(data, level, "api_lv");
	// int api_maxhp - Max HP
	extract(data, maxHp, "api_maxhp");
	// int api_member_id - ID of her admiral
	extract(data, admiral, "api_member_id");
	// string api_name - Her name, with Kanji
	extract(data, name, "api_name");
	// int[2] api_ndock_item - Current cost to repair (Steel, Fuel)
	extract(data, repairCost.steel, "api_ndock_item", 0);
	extract(data, repairCost.fuel, "api_ndock_item", 1);
	// int api_ndock_time - Current repair time, in seconds
	extract(data, repairTime, "api_ndock_time");
	// string api_ndock_time_str - Current time to repair (in the format HH:MM:SS)
	extract(data, repairTimeStr, "api_ndock_time_str");
	// int api_nowhp - Current HP
	extract(data, hp, "api_nowhp");
	// int[5] api_onslot - ???
	extract(data, _onslot, 5, "api_onslot");
	// int[4] api_powup - Bonus when used for modernization, ( FP, TP, AA, AM )
	// int[2] api_raig - Torpedo, with modernization (cur, max)
	extract(data, torpedoBase.cur, "api_raig", 0);
	extract(data, torpedoBase.max, "api_raig", 1);
	// int[2] api_raim - Seems unused (always [ 0, 0 ])
	extract(data, _raim, 2, "api_raim");
	// int[2] api_raisou - Torpedo, with modernization and equipment (cur, max)
	extract(data, torpedo.cur, "api_raisou", 0);
	extract(data, torpedo.max, "api_raisou", 1);
	// int[2] api_saku - Line of Sight, with modernization (cur, max)
	extract(data, lineOfSightBase.cur, "api_saku", 0);
	extract(data, lineOfSightBase.max, "api_saku", 1);
	// int[2] api_sakuteki - Line of Sight, with modernization and equipment (cur, max)
	extract(data, lineOfSight.cur, "api_sakuteki", 0);
	extract(data, lineOfSight.max, "api_sakuteki", 1);
	// int api_ship_id - ID of the ship
	extract(data, master, "api_ship_id");
	// int[5] api_slot - What's equipped in each slot
	extract(data, equipment, 5, "api_slot");
	// int api_slotnum - Available number of slots
	extract(data, equipmentSlots, "api_slotnum");
	// int api_soku - Speed
	extract(data, speed, "api_soku");
	// int api_sortno - The number on the card
	// int api_souk - Armor, with modernization (cur, max)
	extract(data, armorBase.cur, "api_souk", 0);
	extract(data, armorBase.max, "api_souk", 1);
	// int api_soukou - Armor, with modernization and equipment (cur, max)
	extract(data, armor.cur, "api_soukou", 0);
	extract(data, armor.max, "api_soukou", 1);
	// int api_srate - Always seems to be the same as api_star
	// int api_star - "Heart Lock"?
	extract(data, heartLock, "api_star");
	// int api_stype - Ship Type
	// int[2] api_taik - Endurance/Max HP (cur, max)
	extract(data, hpBase.cur, "api_taik", 0);
	extract(data, hpBase.max, "api_taik", 1);
	// int[2] api_taiku - Anti-Air, with modernization and equipment (cur, max)
	extract(data, antiair.cur, "api_taiku", 0);
	extract(data, antiair.max, "api_taiku", 1);
	// int[2] api_taisen - Anti-Sub (cur, max)
	extract(data, antisub.cur, "api_taisen", 0);
	extract(data, antisub.max, "api_taisen", 1);
	// int[2] api_tyku - Anti-Air, with modernization (cur, max)
	extract(data, antiairBase.cur, "api_tyku", 0);
	extract(data, antiairBase.max, "api_tyku", 1);
	// int[2] api_use_bull - Ammo cost per point to resupply
	extract(data, ammoCost, "api_use_bull");
	// int[2] api_use_fuel - Fuel cost per point to resupply
	extract(data, fuelCost, "api_use_fuel");
	// int[2] api_voicef - 1 or 3 if the ship has extra (hourly?) voice clips
	// string api_yomi - Name, in Hiragana/Katakana
	extract(data, reading, "api_yomi");
}

void KCShip::loadFrom2(const QVariantMap &data) {
	extract(data, master, "api_ship_id");
	extract(data, level, "api_lv");
	extract(data, exp, "api_exp");
	extract(data, hp, "api_nowhp");
	extract(data, maxHp, "api_maxhp");
	extract(data, range, "api_leng");
	extract(data, equipment, 5, "api_slot");
	extract(data, _kyouka, 4, "api_kyouka");
	extract(data, fuel, "api_fuel");
	extract(data, ammo, "api_bull");
	extract(data, equipmentSlots, "api_slotnum");
	extract(data, repairTime, "api_ndock_time");
	extract(data, repairCost.steel, "api_ndock_item", 0);
	extract(data, repairCost.fuel, "api_ndock_item", 1);
	extract(data, condition, "api_cond");
	extract(data, firepower.cur, "api_karyoku", 0);
	extract(data, firepower.max, "api_karyoku", 1);
	extract(data, torpedo.cur, "api_raisou", 0);
	extract(data, torpedo.max, "api_raisou", 1);
	extract(data, antiair.cur, "api_taiku", 0);
	extract(data, antiair.max, "api_taiku", 1);
	extract(data, armor.cur, "api_soukou", 0);
	extract(data, armor.max, "api_soukou", 1);
	extract(data, evasion.cur, "api_kaihi", 0);
	extract(data, evasion.max, "api_kaihi", 1);
	extract(data, antisub.cur, "api_taisen", 0);
	extract(data, antisub.max, "api_taisen", 1);
	extract(data, lineOfSight.cur, "api_sakuteki", 0);
	extract(data, lineOfSight.max, "api_sakuteki", 1);
	extract(data, luck.cur, "api_lucky", 0);
	extract(data, luck.max, "api_lucky", 1);
	extract(data, heartLock, "api_locked");
}
