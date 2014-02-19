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

/*
 * Standard CRC32 function, this particular one being copypasted from the
 * opensource portions of the OSX Kernel, with just some formatting and
 * a nonportable include fixed, as well as using the Qt integer types.
 *
 * http://www.opensource.apple.com/source/xnu/xnu-1456.1.26/bsd/libkern/crc32.c
 *
 * I could probably use zlib's crc32 instead, but I don't know if that's
 * guaranteed to be linked to all Qt installations, so this is a safer bet.
 */
quint32 crc32(quint32 crc, const void *buf, size_t size)
{
	const quint8 *p = (quint8*)buf;
	crc = crc ^ ~0U;

	while (size--)
		crc = crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8);

	return crc ^ ~0U;
}
