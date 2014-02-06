#include "KCFleet.h"
#include "KCWrapperUtils.h"
#include "KCClient.h"

KCFleet::KCFleet(QObject *parent) : KCFleet(QVariantMap(), parent) {}

KCFleet::KCFleet(QVariantMap data, QObject *parent):
	QObject(parent)
{
	missionTimer.setSingleShot(true);
	connect(&missionTimer, SIGNAL(timeout()), this, SLOT(onMissionTimeout()));
	loadFrom(data);
}

KCFleet::KCFleet(KCClient *parent) : KCFleet(QVariantMap(), parent) {}

KCFleet::KCFleet(QVariantMap data, KCClient *parent) : KCFleet(data, (QObject*)parent)
{
	connect(this, SIGNAL(missionCompleted()), parent, SLOT(onMissionCompleted()));
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
	// int[4] api_mission - The expedition the fleet is currently on (page, number, completion timestamp, ???)
	extract(data, mission.page, "api_mission", 0);
	extract(data, mission.no, "api_mission", 1);
	qint64 missionCT;
	extract(data, missionCT, "api_mission", 2);
	mission.complete = QDateTime::fromMSecsSinceEpoch(missionCT);
	// string api_flagship - ??? (always "0" for me)
	// int[6] api_ship - Local ID of the ships in the fleet
	extract(data, ships, 6, "api_ship");
	extractCount(data, shipCount, "api_ship");
	
	if(mission.page > 0 && mission.no > 0 && mission.complete > QDateTime::currentDateTime())
		missionTimer.start(mission.complete.toMSecsSinceEpoch() - QDateTime::currentMSecsSinceEpoch());
	else
		missionTimer.stop();
}

void KCFleet::onMissionTimeout()
{
	emit missionCompleted();
}
