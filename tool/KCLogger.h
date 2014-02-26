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
	
	void logDrop(int shipID);
	void logCraftShip(int fuel, int ammo, int steel, int baux, int cmat, int shipID);
	void logCraftItem(int fuel, int ammo, int steel, int baux, int itemID);
	
protected:
	QSqlDatabase db;
};

#endif
