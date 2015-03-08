#ifndef COMMANDER_H
#define COMMANDER_H

#include <QObject>
#include <QStringList>
#include <QUdpSocket>
#include <QSettings>
#include <QLocalServer>
#include <QLocalSocket>
#include <QApplication>
#include <QByteArray>
#include <QProcess>
#include <QList>

class Commander : public QObject
{
    Q_OBJECT
public:
    explicit Commander(QObject *parent = 0);
    ~Commander();
    QSettings *config;
    QUdpSocket socket;
    QLocalServer lse;
    QLocalSocket lso;
    Q_INVOKABLE QString port();
    Q_INVOKABLE QStringList cmd();
    Q_INVOKABLE void send(QString port,QString cmds);
    Q_INVOKABLE void start(QString Port);
    Q_INVOKABLE void stop();

signals:
    void show();
public slots:
    void show_m(){
        emit show();
    }
    void process();
};

#endif // COMMANDER_H
