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

#endif
