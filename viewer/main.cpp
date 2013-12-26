#include <QApplication>
#include <QWebSettings>
#include "KVMainWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QCoreApplication::setApplicationName("KCTViewer");
	QCoreApplication::setApplicationVersion("1.0.0b1");
	QCoreApplication::setOrganizationName("MacaroniCode");
	
	QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
	
	KVMainWindow win;
	win.show();
	
	app.exec();
}
