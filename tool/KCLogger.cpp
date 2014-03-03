#include "KCLogger.h"
#include <QStandardPaths>
#include <QDir>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

KCLogger::KCLogger(QObject *parent):
	QObject(parent)
{
	db = QSqlDatabase::database("logDB");
	if(!db.isValid())
	{
		QDir dataDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
		dataDir.mkpath(dataDir.absolutePath());
		
		QString path = dataDir.absoluteFilePath("log.db");
		qDebug() << "Opening Log Database at" << path;
		QFile dbFile(path);
		bool fileExisted = dbFile.exists();
		
		db = QSqlDatabase::addDatabase("QSQLITE", "logDB");
		db.setDatabaseName(path);
		if(!db.open())
		{
			qWarning() << "Couldn't open DB:" << db.lastError();
		}
		
		// If the file didn't exist before, then create the schema
		if(!fileExisted)
		{
			db.transaction();
			{
				// drops - Ships dropped from maps
				// -> INTEGER timestamp - The UNIX Timestamp for when the ship dropped
				// -> INTEGER ship      - The ID of the ship that dropped
				// -> INTEGER world     - The World where the ship dropped (eg. 5 in 5-4)
				// -> INTEGER map       - The Map where the ship dropped (eg. 4 in 5-4)
				QSqlQuery("CREATE TABLE drops (timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP, ship INTEGER, world INTEGER, map INTEGER);", db).exec();
				
				// craft_ship - Ships crafted
				// -> INTEGER timestamp - The UNIX Timestamp for when the construction was *started*
				// -> INTEGER ship      - The ID of the ship that was crafted
				// -> INTEGER fuel      - The amount of fuel spent
				// -> INTEGER ammo      - The amount of ammo spent
				// -> INTEGER steel     - The amount of steel spent
				// -> INTEGER baux      - The amount of bauxite spent
				// -> INTEGER devmats   - The number of development materials spent (normally 1, higher for LSC)
				QSqlQuery("CREATE TABLE craft_ship (timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP, ship INTEGER, fuel INTEGER, ammo INTEGER, steel INTEGER, baux INTEGER, devmats INTEGER);", db).exec();
				
				// craft_item - Items crafted
				// -> INTEGER timestamp - The UNIX Timestamp for when the construction was *started*
				// -> INTEGER item      - The ID of the item that was crafted
				// -> INTEGER fuel      - The amount of fuel spent
				// -> INTEGER ammo      - The amount of ammo spent
				// -> INTEGER steel     - The amount of steel spent
				// -> INTEGER baux      - The amount of bauxite spent
				QSqlQuery("CREATE TABLE craft_item (timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP, item INTEGER, fuel INTEGER, ammo INTEGER, steel INTEGER, baux INTEGER);", db).exec();
			}
			db.commit();
		}
	}
}

KCLogger::~KCLogger()
{
	
}
	
void KCLogger::logDrop(int ship, int world, int map)
{
	QSqlQuery query(db);
	query.prepare("INSERT INTO drops (ship, world, map) VALUES (:ship, :world, :map);");
	query.bindValue(":ship", ship);
	query.bindValue(":world", world);
	query.bindValue(":map", map);
	qDebug() << "Bound Values:" << query.boundValues();
	if(!query.exec())
		qWarning() << "Couldn't log Drop:" << query.lastError();
}

void KCLogger::logCraftShip(int ship, int fuel, int ammo, int steel, int baux, int cmat)
{
	QSqlQuery query(db);
	query.prepare("INSERT INTO craft_ship (ship, fuel, ammo, steel, baux, cmat) VALUES (:ship, :fuel, :ammo, :steel, :baux, :cmat);");
	query.bindValue(":ship", ship);
	query.bindValue(":fuel", fuel);
	query.bindValue(":ammo", ammo);
	query.bindValue(":steel", steel);
	query.bindValue(":baux", baux);
	query.bindValue(":cmat", cmat);
	if(!query.exec())
		qWarning() << "Couldn't log Ship Craft:" << query.lastError();
}

void KCLogger::logCraftItem(int item, int fuel, int ammo, int steel, int baux)
{
	QSqlQuery query(db);
	query.prepare("INSERT INTO craft_item (item, fuel, ammo, steel, baux) VALUES (:item, :fuel, :ammo, :steel, :baux);");
	query.bindValue(":item", item);
	query.bindValue(":fuel", fuel);
	query.bindValue(":ammo", ammo);
	query.bindValue(":steel", steel);
	query.bindValue(":baux", baux);
	if(!query.exec())
		qWarning() << "Couldn't log Item Craft:" << query.lastError();
}
