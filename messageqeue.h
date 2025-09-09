#ifndef MESSAGEQEUE_H
#define MESSAGEQEUE_H

#include <QString>
#include <QList>
#include <QObject>
#include <qstringlist.h>

/** @addtogroup main_connection */
/*@{*/
class IPS{
public:

    IPS(){localid = -1;}

    QString sidi;
    QString ip;
    QString city;
    QString countryiso;
    QString country;
    QString region;
    QString regionfull;
    QString serverid(){return sidi;}
    void setserverid(QString idi){

        sidi = idi;
    }
    QString available;
    QString speed;
    QString countryImg;
    int localid;
};

struct Msg
{
	QString msg;
	QString det;
};

class MessageQeue : public QObject
{
     Q_OBJECT
public:
    MessageQeue();

    QList<Msg> __msgs;
    QList<QString> listmsg;
    QStringList msgLst;

public slots:
    /**
     *@brief new message from Tuxler server arrived
    */
    void NewMessage();
};
/*@}*/
#endif // MESSAGEQEUE_H
