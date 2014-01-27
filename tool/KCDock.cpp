#include "KCDock.h"
#include "KCWrapperUtils.h"
#include "KCUtil.h"
#include "KCClient.h"
#include <QDebug>
#include <QRegExp>

KCDock::KCDock(QObject *parent) : KCDock(QVariantMap(), parent) {}

KCDock::KCDock(QVariantMap data, QObject *parent):
	QObject(parent)
{
	timer.setSingleShot(true);
	connect(&timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
	loadFrom(data);
}

KCDock::KCDock(KCClient *parent) : KCDock(QVariantMap(), parent) {}

KCDock::KCDock(QVariantMap data, KCClient *parent) : KCDock(data, (QObject*)parent)
{
	connect(this, SIGNAL(completed()), parent, SLOT(onDockCompleted()));
}

KCDock::~KCDock()
{
	
}

void KCDock::loadFrom(QVariantMap data)
{
	// int api_member_id ID of the admiral who owns the dock
	// int api_id Local ID of the dock
	extract(data, id, "api_id");
	// int api_state State; 1 = Unused, 2 = Building, 3 = Finished
	extract(data, state, "api_state");
	// int api_ship_id ID of the ship being repaired
	// - or -
	// int api_created_ship_id ID of the ship that will be created
	if(data.contains("api_ship_id"))
	{
		extract(data, shipID, "api_ship_id");
		isConstruction = false;
	}
	else
	{
		extract(data, shipID, "api_created_ship_id");
		isConstruction = true;
	}
	// int api_complete_time ??? (definitely not a timestamp...)
	// string api_complete_time_str When it'll be complete, YYYY-MM-DD HH:MM:SS
	QString completeStr;
	extract(data, completeStr, "api_complete_time_str");
	complete = QDateTime::fromString(completeStr, "yyyy-MM-dd HH:mm:ss");
	complete = adjustDateTimeForTimezoneOffset(complete, 9*60*60);
	// int api_item1 Fuel used
	extract(data, fuel, "api_item1");
	// int api_item2 Ammo used
	extract(data, ammo, "api_item2");
	// int api_item3 Steel used
	extract(data, steel, "api_item3");
	// int api_item4 Bauxite used
	extract(data, baux, "api_item4");
	
	// Start the timer
	if(state == Occupied || state == Building)
		timer.start(complete.toMSecsSinceEpoch() - QDateTime::currentMSecsSinceEpoch());
}

void KCDock::onTimeout()
{
	state = (isConstruction ? Finished : Empty);
	emit completed();
}
