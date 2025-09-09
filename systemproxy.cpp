#include "systemproxy.h"
#include "mainwindow.h"
#include "tuxlerapp.h"

void redirect_tuxler(bool);
extern int SERVER_PORT_SOCKS;

SystemProxy::SystemProxy()
{

}

ProxySettingsStruct SystemProxy::GetProxy(char * type){

    ProxySettingsStruct st;

#ifdef Q_OS_WIN32

    QUrl u = QUrl(QLatin1String(type) + QLatin1String("://www.google.com"));

    QNetworkProxyQuery npq(u);
    QString p(type);
    npq.setProtocolTag(p);
    QList<QNetworkProxy> listOfProxies = QNetworkProxyFactory::systemProxyForQuery(npq);

    foreach(QNetworkProxy p, listOfProxies){

        st.pstring = QString(type) + QString("=") + listOfProxies[0].hostName() +
                QString(":") +
                QString::number(listOfProxies[0].port()) + ";";
        break;
    }
#endif

    return st;
}

void SystemProxy::RestoreProxy(){

#ifdef Q_OS_WIN32

	redirect_tuxler(false);

    QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

    if(settings.value("isproxyset", false).toBool()){

        MainWindow::__instance->proxySettings.Revert();

        settings.setValue("isproxyset", false);
    }
#endif

}

void SystemProxy::SetProxy(){

#ifdef Q_OS_WIN32
    QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

    if(!settings.value("isproxyset", false).toBool())
	{
		MainWindow::__instance->proxySettings.SetSocksProxyPort(SERVER_PORT_SOCKS);
        
		redirect_tuxler(true);

        if(MainWindow::__instance->proxySettings.Apply())

        settings.setValue("isproxyset", true);
    }
#endif

}
