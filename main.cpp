#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QTextCodec>

#include "mainwindow.h"
#include "utilities.h"

#define DEFAULT_CODEC "UTF-8"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator myTranslator;
    //QTextCodec::setCodecForTr(QTextCodec::codecForName(DEFAULT_CODEC));
    myTranslator.load("ERPRock_pt.qm",Utilities::getResourcesPath()+"/i18n/");
    a.installTranslator(&myTranslator);

    MainWindow w;
    w.showMaximized();

    return a.exec();
}
