#include "parsemessage.h"
#include <QRegExp>

ParseMessage::ParseMessage()
{

}

bool ParseMessage::ParseMessage2(QString msg, ParsedMessage2 &mout){

    bool ret = false;

        QString re("<message>(.*)<details><type>(.*)</type><showmessage><hideifautostart>(.*)</hideifautostart><eventopenhttp>(.*)</eventopenhttp><title>(.*)</title><body>(.*)</body></showmessage></details></message>");
        QString ws = (msg);

        QRegExp rx(re);
        rx.setMinimal(true);

        if(rx.indexIn(ws) != -1){

            mout.message = rx.cap(1);
            mout.type = rx.cap(2);
            mout.hideifautostart = rx.cap(3);
            mout.eventopenhttp = rx.cap(4);
            mout.title = rx.cap(5);
            mout.body = rx.cap(6);

            ret = true;

        }else{

            QString re("<message>(.*)<details><type>(.*)</type><showmessage><hideifnotstarted>(.*)</hideifnotstarted><eventopenhttp>(.*)</eventopenhttp><title>(.*)</title><body>(.*)</body></showmessage></details></message>");
            QString ws = (msg);

            QRegExp rx(re);
            rx.setMinimal(true);

            if(rx.indexIn(ws) != -1){

                mout.message = rx.cap(1);
                mout.type = rx.cap(2);
                mout.hideifautostart = rx.cap(3);
                mout.eventopenhttp = rx.cap(4);
                mout.title = rx.cap(5);
                mout.body = rx.cap(6);

                ret = true;
            }
        }

        return ret;
}
