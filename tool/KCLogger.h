#ifndef KCLOGGER_H
#define KCLOGGER_H

#include <QObject>

class KCLogger : public QObject
{
	Q_OBJECT
	
public:
	KCLogger(QObject *parent = 0);
	virtual ~KCLogger();
};

#endif
