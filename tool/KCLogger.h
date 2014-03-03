#ifndef KCLOGGER_H
#define KCLOGGER_H

#include <QObject>
#include <QSqlDatabase>

class KCLogger : public QObject
{
	Q_OBJECT
	
public:
	KCLogger(QObject *parent = 0);
	virtual ~KCLogger();
	
	void logDrop(int ship, int world, int map);
	void logCraftShip(int ship, int fuel, int ammo, int steel, int baux, int cmat);
	void logCraftItem(int item, int ammo, int steel, int baux, int itemID);
	
protected:
	QSqlDatabase db;
};

#endif
