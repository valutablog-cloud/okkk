#ifndef PARSEMESSAGE_H
#define PARSEMESSAGE_H

#include <QString>
/** @addtogroup main_connection_parse */
/*@{*/
struct ParsedMessage2
{
    QString message;
    QString type;
    QString hideifautostart;
    QString eventopenhttp;
    QString title;
    QString body;
    QString hideifnotstarted;
};


class ParseMessage
{

public:
    ParseMessage();

    /**
     *@brief parses message string into struct ParsedMessage2
     *@details used to parse DISPLAY messages from server
     *@returns true if message valid false otherwise
     *@param message message string
     *@param mout this struct will be filled with parsed data ParsedMessage2
     */
    bool ParseMessage2(QString message, ParsedMessage2&mout);
};
/*@}*/
#endif // PARSEMESSAGE_H
