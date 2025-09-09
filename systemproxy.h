#ifndef SYSTEMPROXY_H
#define SYSTEMPROXY_H

#include <QString>
#include <QObject>

struct ProxySettingsStruct{

    QString pstring;
    int proxytype;
    QString proxybypass;
};

/**
 *@brief set/unset OS proxy settings
*/
class SystemProxy : public QObject
{
    Q_OBJECT
public:
    SystemProxy();
    ProxySettingsStruct GetProxy(char * type);

public slots:

    /**
     *@brief set OS proxy settings to use Tuxler local proxy
    */
    void SetProxy();
    void RestoreProxy();
};

#endif // SYSTEMPROXY_H
