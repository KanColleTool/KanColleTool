#include "KVUtil.h"
#include <QRegExp>
#include <QChar>

// 
// Taken from http://stackoverflow.com/a/7047000
// TODO: Change the QRegExp (which is bad) to a QRegularExpression (good).
// 
QString unescape(QString str)
{
	QRegExp rx("(\\\\u[0-9a-fA-F]{4})");
	int pos = 0;
	while ((pos = rx.indexIn(str, pos)) != -1)
		str.replace(pos++, 6, QChar(rx.cap(1).right(4).toUShort(0, 16)));
	
	return str;
}
