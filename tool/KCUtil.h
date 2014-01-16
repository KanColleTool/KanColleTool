#ifndef KCUTIL_H
#define KCUTIL_H

inline QTime delta(const QDateTime &d1, const QDateTime &d2 = QDateTime::currentDateTimeUtc())
{
	qint64 msecs = d1.toMSecsSinceEpoch() - d2.toMSecsSinceEpoch();
	return QTime::fromMSecsSinceStartOfDay(msecs);
}

#endif
