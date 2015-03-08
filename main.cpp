#include <QApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
#include "commander.h"
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator trans;
    if(trans.load(QString(":/%1.qm").arg(QLocale::system().name()))){
        app.installTranslator(&trans);
    }
    qmlRegisterType<Commander>("ybh1998.Commander",1,0,"Commander");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
