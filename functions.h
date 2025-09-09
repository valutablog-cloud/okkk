#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>
#include <iostream>

/** @addtogroup common_functions_classes */
/*@{*/

void NextIP(bool first, bool next);
void SendMessageToServer(QString &msg);

QString getTag(QString tag_, QString &search);

std::string toStdString(QString s);

/**
 *@brief return true if string is number
 */
bool is_numeric(QString s);

/**
 *@brief check if app was run with CMD debug flag
 */
bool __DEBUG();

#define __DEBUG__ __DEBUG()

#ifdef Q_OS_WIN32
/**
 *@brief check if OS is Windows 8
 */
bool isWin8();
#endif
/*@}*/
#endif // FUNCTIONS_H
