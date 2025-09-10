#ifndef JSBRIDGE_H
#define JSBRIDGE_H

#include <QObject>
#include <QStringList>
#include <QDebug>

/** @addtogroup javascript_gui */
/*@{*/
class JavaScriptBridge : public QObject {

    Q_OBJECT

public:
    JavaScriptBridge(QObject* parent);
    Q_INVOKABLE QStringList bridge(QString);

    /**
    *@brief js Message Qeue
    */
    QStringList MessageQeue;

private:
    QObject* parent_;

signals:
    void NewMessage(QString);

    /**
    *@brief signal connected to MainWindow::SendEventToJavaScript
    */
    void SendEventToJavaScript();

public slots:

    /**
    *@brief slot connected to MainWindow::SendEventToBridge - receives forwarder message from MainWindow to js js bridge
    *@details appends message to Message Qeue and emits JavaScriptBridge::SendEventToJavaScript
    */
    void SendNewGuiEvent(QString);
};
/*@}*/
#endif // JSBRIDGE_H
