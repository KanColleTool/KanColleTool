#ifndef KCFLEET_H
#define KCFLEET_H

#include <QObject>
#include <QVariant>
#include <QMap>
#include <QDateTime>
#include <QTimer>

#include "KCGameObject.h"

class KCClient;
class KCFleet : public KCGameObject {
	Q_OBJECT

public:
	KCFleet(const QVariantMap &data=QVariantMap(), int loadId=0, KCClient *parent=0);
	virtual ~KCFleet();

	void loadFrom(const QVariantMap &data, int loadId) override;

	int id, admiral;
	QString name;
	int ships[6];
	int shipCount;
	struct { int page; int no; QDateTime complete; } mission;

signals:
	void missionCompleted();

private slots:
	void onMissionTimeout();

private:
	QTimer missionTimer;
};

#endif
