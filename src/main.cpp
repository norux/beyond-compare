#include "mainwindow.h"
#include <QTranslator>
#include <QResource>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTranslator translator;
	QString locale = QLocale::system().name();

	qDebug() << locale;

	QResource::registerResource("./resource/resource.rcc");

	translator.load(":/translations/" + locale);
	a.installTranslator(&translator);

	MainWindow w;
	w.show();

	return a.exec();
}
