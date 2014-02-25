#ifndef KCGAMEOBJECT_H
#define KCGAMEOBJECT_H

#include <QObject>
#include <QVariantMap>

class KCGameObject : public QObject {
	Q_OBJECT

public:
	KCGameObject(QObject *parent=0) : QObject(parent) {}
	virtual ~KCGameObject() {}

	virtual void loadFrom(const QVariantMap &data, int loadId=0)=0;
};

#endif // KCGAMEOBJECT_H
