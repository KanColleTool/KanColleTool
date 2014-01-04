#include "KCFleet.h"
#include "KCWrapperUtils.h"

KCFleet::KCFleet(QObject *parent) : KCFleet(QVariantMap(), parent) {}

KCFleet::KCFleet(QVariantMap data, QObject *parent):
	QObject(parent)
{
	loadFrom(data);
}

KCFleet::~KCFleet()
{
	
}

void KCFleet::loadFrom(QVariantMap data)
{
	// int api_member_id - The ID of the fleet's admiral
	extract(data, admiral, "api_member_id");
	// int api_id - Local ID of the fleet
	extract(data, id, "api_id");
	// int api_name - Name of the fleet
	extract(data, name, "api_name");
	// string api_name_id - ??? (Always "" for me)
	// int[4] api_mission - ???
	// string api_flagship - ??? (always "0" for me)
	// int[6] api_ship - Local ID of the ships in the fleet
	extract(data, ships, 6, "api_ship");
}
