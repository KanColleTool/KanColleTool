#include "KCMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QCoreApplication::setApplicationName("KanColleTool");
	QCoreApplication::setApplicationVersion("1.0b1");
	QCoreApplication::setOrganizationName("MacaroniCode");
	
	QApplication a(argc, argv);
	KCMainWindow w;
	w.show();
	
	return a.exec();
}
