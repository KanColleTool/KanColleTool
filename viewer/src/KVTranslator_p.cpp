#include "KVTranslator.h"

// Copied from https://qt.gitorious.org/qt/qtbase/source/1756a84756807a9849aa507e77845dfdf31b8020:src/corelib/json/qjsonwriter.cpp#L57
inline uchar hexdig(uint u) {
	return (u < 0xa ? '0' + u : 'a' + u - 0xa);
}

QString KVTranslator::jsonEscape(const QString &s) {
	const uchar replacement = '?';
	QByteArray ba(s.length(), Qt::Uninitialized);

	uchar *cursor = (uchar *)ba.data();
	const uchar *ba_end = cursor + ba.length();

	const QChar *ch = (const QChar *)s.constData();
	const QChar *end = ch + s.length();

	int surrogate_high = -1;

	while (ch < end) {
		if (cursor >= ba_end - 6) {
			// ensure we have enough space
			int pos = cursor - (const uchar *)ba.constData();
			ba.resize(ba.size()*2);
			cursor = (uchar *)ba.data() + pos;
			ba_end = (const uchar *)ba.constData() + ba.length();
		}

		uint u = ch->unicode();
		if (surrogate_high >= 0) {
			if (ch->isLowSurrogate()) {
				u = QChar::surrogateToUcs4(surrogate_high, u);
				surrogate_high = -1;
			} else {
				// high surrogate without low
				*cursor = replacement;
				++ch;
				surrogate_high = -1;
				continue;
			}
		} else if (ch->isLowSurrogate()) {
			// low surrogate without high
			*cursor = replacement;
			++ch;
			continue;
		} else if (ch->isHighSurrogate()) {
			surrogate_high = u;
			++ch;
			continue;
		}

		if (u < 0x80) {
			if (u < 0x20 || u == 0x22 || u == 0x5c) {
				*cursor++ = '\\';
				switch (u) {
				case 0x22:
					*cursor++ = '"';
					break;
				case 0x5c:
					*cursor++ = '\\';
					break;
				case 0x8:
					*cursor++ = 'b';
					break;
				case 0xc:
					*cursor++ = 'f';
					break;
				case 0xa:
					*cursor++ = 'n';
					break;
				case 0xd:
					*cursor++ = 'r';
					break;
				case 0x9:
					*cursor++ = 't';
					break;
				default:
					*cursor++ = 'u';
					*cursor++ = '0';
					*cursor++ = '0';
					*cursor++ = hexdig(u>>4);
					*cursor++ = hexdig(u & 0xf);
				}
			} else {
				*cursor++ = (uchar)u;
			}
		} else {
			if (u < 0x0800) {
				*cursor++ = 0xc0 | ((uchar) (u >> 6));
			} else {
				// is it one of the Unicode non-characters?
				if (QChar::isNonCharacter(u)) {
					*cursor++ = replacement;
					++ch;
					continue;
				}

				if (QChar::requiresSurrogates(u)) {
					*cursor++ = 0xf0 | ((uchar) (u >> 18));
					*cursor++ = 0x80 | (((uchar) (u >> 12)) & 0x3f);
				} else {
					*cursor++ = 0xe0 | (((uchar) (u >> 12)) & 0x3f);
				}
				*cursor++ = 0x80 | (((uchar) (u >> 6)) & 0x3f);
			}
			*cursor++ = 0x80 | ((uchar) (u&0x3f));
		}
		++ch;
	}

	ba.resize(cursor - (const uchar *)ba.constData());
	return ba;
}

KVTranslator::JsonState::JsonState() : JsonState(Invalid, -1) {}

KVTranslator::JsonState::JsonState(JsonContext c, int s, int ai) :
	context(c), start(s), arri(ai) {}

KVTranslator::JsonState::operator QString() const {
	QString ret;
	switch(context) {
	case Start:
		ret += "Start";
		break;
	case End:
		ret += "End";
		break;
	case Object:
		ret += "Object";
		break;
	case Array:
		ret += "Array";
		break;
	case Key:
		ret += "Key";
		break;
	case AfterKey:
		ret += "AfterKey";
		break;
	case Value:
		ret += "Value";
		break;
	case NonString:
		ret += "NonString";
		break;
	case String:
		ret += "String";
		break;
	case AfterValue:
		ret += "AfterValue";
		break;
	case Invalid:
		return "Invalid";
	}

	ret += "(" + QString::number(start);
	if(context == Array) {
		ret += ", " + QString::number(arri);
	}
	ret += ")";

	return ret;
}

KVTranslator::Reader::Reader(const QByteArray &json) : i(0), data(json) {}

const QByteArray KVTranslator::Reader::readTo(int e) {
	int s = i;
	i = e;
	return data.mid(s, e-s);
}

const QByteArray KVTranslator::Reader::readAll() {
	int s = i;
	i = data.size();
	return data.mid(s);
}
