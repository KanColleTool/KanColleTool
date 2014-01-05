#ifndef KCWRAPPERMACROS_H
#define KCWRAPPERMACROS_H

#include <QSequentialIterable>

/*
 * Extract a single item from a variant map into a T&
 */
template<typename T>
void extract(const QVariantMap &source, T& dest, const QString& key)
{
	dest = source[key].value<T>();
}

/*
 * Extract a list of items from a variant map into a T[]
 */
template<typename T>
void extract(const QVariantMap &source, T dest[], int count, const QString& key)
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
void extract(const QVariantMap &source, T& dest, const QString &key, int index)
{
	QSequentialIterable iter = source[key].value<QSequentialIterable>();
	dest = iter.at(index).value<T>();
}

/*
 * Extract or update data from an API response into a QMap<int, modelT*>&
 */
template<class modelT>
void modelizeResponse(const QVariant &data, QMap<int, modelT*> &target, QString idKey = "api_id")
{
	QList<QVariant> dataList = data.toList();
	foreach(QVariant item, dataList)
	{
		QVariantMap itemMap = item.toMap();
		modelT *ship = target.value(itemMap.value(idKey).toInt());
		
		if(!ship)
			target.insert(itemMap.value(idKey).toInt(), new modelT(itemMap));
		else
			ship->loadFrom(itemMap);
	}
}

#endif
