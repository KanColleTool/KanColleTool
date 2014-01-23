#include <QApplication>
#include <QWebSettings>
#include <QDebug>
#include "KVMainWindow.h"
#include "KVProxy.h"
#include "version.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QCoreApplication::setApplicationName("KanColleTool");
	QCoreApplication::setApplicationVersion(KCT_VERSION);
	QCoreApplication::setOrganizationName("MacaroniCode");
	
	QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
	
	QStringList args = QCoreApplication::arguments();
	
	// The --debug-proxy argument starts the program in Proxy Debug mode, with no
	// GUI and only the proxy server running on IPv4 port 12345.
	if(args.contains("--debug-proxy"))
	{
		qDebug() << "Starting Proxy on Port 12345...";
		KVProxy *proxy = new KVProxy(0, 12345);
        proxy->run();
	}
	// If we're not debugging the proxy, just start normally.
	else
	{
		KVMainWindow *win = new KVMainWindow();
		win->show();
	}
	
	return app.exec();
}
