#ifndef IPLIST_H
#define IPLIST_H

#include "messageqeue.h"
#include <QString>
#include <QList>
#include <qset.h>
#include <qmap.h>

struct country_city_item
{
	bool operator<(const country_city_item& other) const
	{
		return country < other.country; 
	}

	QString country;
	QString countryISO;
	QString countryImg;
	QList<QString> cities;
};

class IPList
{
public:
    IPList();

	QList<country_city_item> residential_list;
	QList<country_city_item> server_list;
   
    bool __ipListLoaded;

    /**
     *@brief parse IP list from Tuxler server -> propagate to GUI and update IPList::CurrentIpList list
     */
    void ParseIpList(QString& string);

	QList<country_city_item> parseJsonList(QJsonObject &list);

	QString GetJsonCountry(QList<country_city_item>&);

	void updateGUIListCache();
};

#endif // IPLIST_H
