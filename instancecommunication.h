#ifndef INSTANCECOMMUNICATION_H
#define INSTANCECOMMUNICATION_H

#include <QString>
#include <QObject>
#include <QTcpServer>

class InstanceCommunication : QObject
{
    Q_OBJECT

    QTcpServer serverInstance;
public:
    InstanceCommunication();

    /**
     *@brief send command to another instance
    */
    static void Send(QString cmd);

private slots:

    /**
     *@brief new connection from another instance
    */
    void newConnectionInstance();

    /**
     *@brief another instance sent data
    */
    void readyReadInstance();
};

#endif // INSTANCECOMMUNICATION_H
