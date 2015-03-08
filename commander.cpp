#include "commander.h"
#include <cstdlib>
Commander::Commander(QObject *parent) : QObject(parent)
{
    config=new QSettings("config.ini",QSettings::IniFormat);
    lso.connectToServer(QApplication::applicationName());
    if(lso.waitForConnected(100)) exit(0);
    lse.listen(QApplication::applicationName());
    QObject::connect(&lse,&QLocalServer::newConnection,this,&Commander::show_m);
}

Commander::~Commander()
{

}

void Commander::send(QString port, QString cmds){
    QUdpSocket send_socket;
    send_socket.writeDatagram(cmds.toLocal8Bit(),cmds.length(),QHostAddress::Broadcast,port.toInt());
}

QString Commander::port(){
    return config->value("/commander/port/").toString();
}

QStringList Commander::cmd(){
    QStringList ret;
    QString t;
    int i;
    for(i=1;;i++){
        t=config->value(QString("/commander/cmd%1/").arg(i)).toString();
        if(t=="") break;
        ret.push_back(t);
    }
    return ret;
}
void Commander::start(QString port){
    socket.bind(port.toInt());
    connect(&socket,&QUdpSocket::readyRead,this,&Commander::process);
}
void Commander::stop(){
    socket.close();
}
void Commander::process(){
    QByteArray yuancmd;
    QList<QByteArray> splitedcmd;
    QList<QByteArray>::iterator i;
    QString cmd;
    QProcess run;
    while(socket.hasPendingDatagrams()){
        yuancmd.resize(socket.pendingDatagramSize());
        socket.readDatagram(yuancmd.data(),yuancmd.size());
        splitedcmd=yuancmd.split('\n');
        for(i=splitedcmd.begin();i!=splitedcmd.end();i++){
            cmd.clear();
            cmd.append(*i);
            run.startDetached(cmd);
            run.waitForFinished();
        }
        //system(yuancmd.data());
    }
}
