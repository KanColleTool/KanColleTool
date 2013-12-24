#include "KCMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	// Setup some version stuff; this lets us use the default QSettings
	// constructor anywhere, without having to specify this over and over
	QCoreApplication::setApplicationName("KanColleTool");
	QCoreApplication::setApplicationVersion("1.0b1");
	QCoreApplication::setOrganizationName("MacaroniCode");
	
	// Make an application!
	QApplication a(argc, argv);
	
	// We want to stay in the tray, not quit when the window goes away
	a.setQuitOnLastWindowClosed(false);
	
	// Create the window, which owns the tray icon, but don't show it!
	KCMainWindow w;
	Q_UNUSED(w);
	//w.show(); // Not in the final version!
	
	// Aaand... start the main loop
	return a.exec();
}
