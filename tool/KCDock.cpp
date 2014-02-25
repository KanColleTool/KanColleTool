#include "KCDock.h"
#include "KCWrapperUtils.h"
#include "KCUtil.h"
#include "KCClient.h"
#include <QDebug>
#include <QRegExp>

KCDock::KCDock(const QVariantMap &data, int loadId, KCClient *parent) :
	KCGameObject(parent) {
	connect(this, SIGNAL(completed()), parent, SLOT(onDockCompleted()));
	loadFrom(data, loadId);
}

KCDock::~KCDock() {

}

void KCDock::loadFrom(const QVariantMap &data, int loadId) {
	Q_UNUSED(loadId);

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
	extractTimestamp(data, complete, "api_complete_time");
	// string api_complete_time_str When it'll be complete, YYYY-MM-DD HH:MM:SS
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
	else
		timer.stop();
}

void KCDock::onTimeout()
{
	state = (isConstruction ? Finished : Empty);
	emit completed();
}
