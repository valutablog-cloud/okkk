//
//  ISO.h
//  Tuxler
//
//  Created by Jaroslaw Lazar on 17.10.2013.
//  Copyright (c) 2013 JATAR. All rights reserved.
//

#ifndef __Tuxler__ISO__
#define __Tuxler__ISO__

#include <iostream>
#include <vector>
#include <QList>
#include <QString>
#include <QObject>

/**
 *@brief Holds region ISO and region full name translation
 */
struct Region{

    QString regioniso;
    QString regionfull;
};


/** @addtogroup main_connection_parse */
/*@{*/

class Translator{

private:
    /**
     *@brief ISO list of countries and full names
     */
    QList<QString> lst;

    /**
     *@brief ISO list of regions and full names
     */
    QList<QString> lstreg;

public:
    /**
     *@brief translate country ISO to full name or full name to ISO
     *@param country if ISO then toiso must be false otherwise true
     *@param toiso change to true if country is full name
     *@return QString ISO/full name - if there is no such country in the list then returns empty string
     */
    QString GetCountryISO(QString &country, bool toiso = false);

    /**
     *@brief try get region full name
     *@param regionisoutf8 region ISO name UTF8 encoded
     *@param countryisoutf8 country ISO name UTF8 encoded
     *@return QString region full name UTF8 encoded if there is no such region in the list then returns empty string
     */
    QString TryGetFullRegion(QString &regionisoutf8, QString &countryisoutf8);

    /**
     *@brief try get regions list
     *@param countryisoutf8 country ISO name UTF8 encoded
     *@return QList<Region> Region list for country ISO - if no regions in the list then an empty list is returned
     */
    QList<Region> TryGetRegions(QString &countryisoutf8);

    Translator();
    ~Translator();

};
/*@}*/
#endif /* defined(__Tuxler__ISO__) */
