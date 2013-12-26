#include <QApplication>
#include <QWebSettings>
#include "KVMainWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
	
	KVMainWindow win;
	win.show();
	
	app.exec();
}
