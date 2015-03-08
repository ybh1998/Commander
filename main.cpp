#include <QApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
#include "commander.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator trans;
    QSettings config("config.ini",QSettings::IniFormat);
    QString language=config.value("/commander/language/").toString();
    trans.load(language);
    app.installTranslator(&trans);
    qmlRegisterType<Commander>("ybh1998.Commander",1,0,"Commander");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
