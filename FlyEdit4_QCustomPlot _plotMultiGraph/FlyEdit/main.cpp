#include "flyedit.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FlyEdit w;
	w.show();
	return a.exec();
}
