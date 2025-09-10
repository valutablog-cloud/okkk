#include "jsbridge.h"

JavaScriptBridge::JavaScriptBridge(QObject *parent) :
    QObject(parent), parent_(parent)
{
}

void JavaScriptBridge::SendNewGuiEvent(QString tosend){

     MessageQeue.append(tosend);

     emit SendEventToJavaScript();
}

QStringList JavaScriptBridge::bridge(QString l){

    if(l.size() > 0){

        emit NewMessage(l);

        return QStringList();
    }

    QStringList tmp = MessageQeue;

    return tmp;
}
