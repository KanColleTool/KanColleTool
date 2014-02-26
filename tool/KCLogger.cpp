#include "KCLogger.h"
#include <QStandardPaths>
#include <QDir>

KCLogger::KCLogger(QObject *parent):
	QObject(parent)
{
	QDir dataDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
	dataDir.mkpath(dataDir.absolutePath());
	//db = QSqlDatabase::addDatabase("QSQLITE", "logDB");
}

KCLogger::~KCLogger()
{
	
}
	
void KCLogger::logDrop(int shipID)
{
	
}

void KCLogger::logCraftShip(int fuel, int ammo, int steel, int baux, int cmat, int shipID)
{
	
}

void KCLogger::logCraftItem(int fuel, int ammo, int steel, int baux, int itemID)
{
	
}
