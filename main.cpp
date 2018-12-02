#include "MediaPlayerV2.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MediaPlayerV2 w;
	w.show();
	return a.exec();
}
