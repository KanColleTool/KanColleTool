#include "KVUtil.h"
#include <QRegularExpression>
#include <QChar>

//
// Taken from http://stackoverflow.com/a/7047000
//
QString unescape(QString str)
{
	QRegularExpression re("(\\\\u[0-9a-fA-F]{4})");
	QRegularExpressionMatchIterator it = re.globalMatch(str);
	while (it.hasNext())
	{
		QRegularExpressionMatch match = it.next();
		str.replace(match.capturedStart(), match.capturedLength(),
		            QChar(match.captured(1).right(4).toUShort(0, 16)));
	}

	return str;
}
