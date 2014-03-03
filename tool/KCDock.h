#ifndef KCDOCK_H
#define KCDOCK_H

#include <QObject>
#include <QVariant>
#include <QMap>
#include <QDateTime>
#include <QTimer>

#include "KCGameObject.h"

class KCClient;
class KCDock : public KCGameObject {
	Q_OBJECT

public:
	enum State {
		Locked = -1,
		Empty = 0,
		Occupied = 1,
		Building = 2,
		Finished = 3
	};

	KCDock(const QVariantMap &data=QVariantMap(), int loadId=0, KCClient *parent=0);
	virtual ~KCDock();

	void loadFrom(const QVariantMap &data, int loadId) override;

	int id;
	int state;
	int shipID;
	QDateTime complete;
	int fuel, ammo, steel, baux, devmats;
	bool isConstruction;

signals:
	void completed();
	void shipChanged();

private slots:
	void onTimeout();

private:
	QTimer timer;
};

#endif // KCDOCK_H
