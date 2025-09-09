#include "instancecommunication.h"
#include "mainwindow.h"
#include "tuxlerapp.h"
#include "config.h"
#include <QTcpSocket>

InstanceCommunication::InstanceCommunication()
{
    serverInstance.listen(QHostAddress::Any, PORT_INSTANCE_COMMUNICATION);

    connect(&serverInstance, SIGNAL(newConnection()), this, SLOT(newConnectionInstance()));
}

void InstanceCommunication::Send(QString cmd){

    QTcpSocket sock;

    sock.connectToHost("127.0.0.1", PORT_INSTANCE_COMMUNICATION);

    if(sock.waitForConnected(1000)){

        sock.write(cmd.toAscii());

        sock.waitForBytesWritten(500);

        sock.close();
    }
}

void InstanceCommunication::newConnectionInstance(){

    QTcpSocket * sock = serverInstance.nextPendingConnection();

    if(sock != NULL && (sock->peerAddress() != QHostAddress::LocalHost && sock->peerAddress() != QHostAddress::LocalHostIPv6)){

        sock->close();

        sock->deleteLater();

        return;
    }

    QVariant v = 1;

    sock->setSocketOption(QAbstractSocket::KeepAliveOption, v);

    connect(sock, SIGNAL(disconnected()), sock, SLOT(deleteLater()), Qt::UniqueConnection);

    connect(sock, SIGNAL(readyRead()), this, SLOT(readyReadInstance()));
}

void InstanceCommunication::readyReadInstance(){

    QTcpSocket * sock = static_cast<QTcpSocket*>(sender());

    QByteArray command = sock->readAll();

    QStringList lst = QString::fromLatin1(command).split("\n");

    foreach(QString cmd, lst){

        if(cmd == "SHOW"){

            MainWindow::__instance->show();
            MainWindow::__instance->raise();

        }else if(cmd == "QUIT"){

            MainWindow::__instance->Exit();
        }
    }
}
