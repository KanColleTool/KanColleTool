#ifndef KCUTIL_H
#define KCUTIL_H

#include <QRegExp>
#include <QTime>

// 
// Taken from http://stackoverflow.com/a/7047000
// TODO: Change the QRegExp (which is bad) to a QRegularExpression (good).
// 
inline
QString unescape(QString str)
{
	QRegExp rx("(\\\\u[0-9a-fA-F]{4})");
	int pos = 0;
	while ((pos = rx.indexIn(str, pos)) != -1)
		str.replace(pos++, 6, QChar(rx.cap(1).right(4).toUShort(0, 16)));
	
	return str;
}

inline
int currentTimezoneOffset()
{
	// Take the current time in UTC, make a localtime copy of it, set the UTC
	// version to localtime to break timezone compensation and get the seconds
	// between the two, now different, but comparable, datetimes.
	QDateTime utc(QDateTime::currentDateTimeUtc());
	QDateTime local(utc.toLocalTime());
	utc.setTimeSpec(Qt::LocalTime);
	return utc.secsTo(local);
}

// This would be provided by QDateTime::setOffsetFromUtc(), but because I
// suddenly have to support Qt 5.0, here we go reimplementing it!
inline
QDateTime adjustDateTimeForTimezoneOffset(const QDateTime &dt, int offset)
{
	return dt.toUTC().addSecs(-(offset - currentTimezoneOffset())).toLocalTime();
}

inline
QTime delta(const QDateTime &d1, const QDateTime &d2 = QDateTime::currentDateTimeUtc())
{
	// Make sure both dates are in UTC, before taking the epoch-offset delta.
	qint64 msecs = d1.toUTC().toMSecsSinceEpoch() - d2.toUTC().toMSecsSinceEpoch();
	// Make a time at exactly 0:0:0:0, and add the millisecond delta to it.
	return QTime(0,0,0,0).addMSecs(msecs);
}

#define TABLE_SET_ITEM(_table, _row, _col, _value) \
	{\
		QTableWidgetItem *item = new QTableWidgetItem(); \
		item->setData(Qt::EditRole, _value); \
		_table->setItem(_row, _col, item); \
	}

#endif
