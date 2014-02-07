#ifndef KCWRAPPERMACROS_H
#define KCWRAPPERMACROS_H

#include <QDateTime>

// QSequentialIterable isn't available before Qt 5.2, and Ubuntu is stuck on 5.0! (╯°□°)╯︵ ┻━┻
// So just because they can't keep up-to-date with things, I'll just do the quick-and-dirty
// workaround of defining QSequentialIterable to be a QList. No one will ever be able to tell.
// (Except, you know, if they look at the performance, which will be one hell of a lot worse...)
#if QT_VERSION >= 0x050200
	#include <QSequentialIterable>
#else
	#include <QList>
	#define QSequentialIterable QList<QVariant>
#endif

/*
 * Extract a single item from a variant map into a T&
 */
template<typename T>
inline void extract(const QVariantMap &source, T& dest, const QString& key)
{
	dest = source[key].value<T>();
}

/*
 * Extract a list of items from a variant map into a T[]
 */
template<typename T>
inline void extract(const QVariantMap &source, T dest[], int count, const QString& key)
{
	QSequentialIterable iter = source[key].value<QSequentialIterable>();
	int i = 0;
	foreach(const QVariant &v, iter)
	{
		dest[i] = v.value<T>();
		if(++i >= count) break;
	}
}

/*
 * Extract a single item from a list into a T&
 */
template<typename T>
inline void extract(const QVariantMap &source, T& dest, const QString &key, int index)
{
	QSequentialIterable iter = source[key].value<QSequentialIterable>();
	dest = iter.at(index).value<T>();
}

/*
 * Extract just the count of a list into an int&
 */
inline void extractCount(const QVariantMap &source, int& dest, const QString &key)
{
	dest = source[key].value<QSequentialIterable>().size();
}

/*
 * Extract a timestamp given as msecs since start of epoch into a QDateTime
 */
inline void extractTimestamp(const QVariantMap &source, QDateTime& dest, const QString &key)
{
	qint64 tmp;
	extract(source, tmp, key);
	dest = QDateTime::fromMSecsSinceEpoch(tmp);
}

/*
 * Extract or update data from an API response into a QMap<int, modelT*>&
 */
template<class modelT, class parentT>
inline void modelizeResponse(const QVariant &data, QMap<int, modelT*> &target, parentT *parent, QString idKey = "api_id")
{
	QList<QVariant> dataList = data.toList();
	foreach(QVariant item, dataList)
	{
		QVariantMap itemMap = item.toMap();
		modelT *ship = target.value(itemMap.value(idKey).toInt());
		
		if(!ship)
			target.insert(itemMap.value(idKey).toInt(), new modelT(itemMap, parent));
		else
			ship->loadFrom(itemMap);
	}
}

#endif
