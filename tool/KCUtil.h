#ifndef KCUTIL_H
#define KCUTIL_H

inline
QTime delta(const QDateTime &d1, const QDateTime &d2 = QDateTime::currentDateTimeUtc())
{
	qint64 msecs = d1.toMSecsSinceEpoch() - d2.toMSecsSinceEpoch();
	return QTime::fromMSecsSinceStartOfDay(msecs);
}

#define TABLE_SET_ITEM(_table, _row, _col, _value) \
	{\
		QTableWidgetItem *item = new QTableWidgetItem(); \
		item->setData(Qt::EditRole, _value); \
		_table->setItem(_row, _col, item); \
	}

#endif
