#include "iplist.h"
#include "mainwindow.h"
#include "tuxlerapp.h"
#include "config.h"

IPList::IPList() : __ipListLoaded(false)
{

}


QString IPList::GetJsonCountry(QList<country_city_item> &l) 
{
	QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

	QString selected_country = settings.value(QString("selected_country"), QString("Any")).toString();
	QString selected_country_iso = settings.value(QString("selected_country_iso"), QString("ANY")).toString();
	QString selected_city = settings.value(QString("selected_city"), QString("Any")).toString();

	Lock();
	int selected_country_ = 0;
	int selected_city_ = 0;

	bool was_country = false;
	bool was_city = false;

	for (auto it = l.begin(); it != l.end(); it++)
	{
		if ((*it).countryISO == selected_country_iso)
		{
			was_country = true;

			for (auto it2 = (*it).cities.begin(); it2 != (*it).cities.end(); it2++)
			{
				if ((*it2) == selected_city)
				{
					was_city = true;
					break;
				}

				if (MainWindow::__instance->enabledPreferredCitySelection)
					selected_city_++;
			}

			break;
		}

		if (MainWindow::__instance->enabledPreferredCountrySelection)
			selected_country_++;
	}
	UnLock();

	if (!was_country)
	{
		selected_country_ = 0;
		selected_city_ = 0;
	}
	else if (!was_city)
		selected_city_ = 0;

	QString ret = "[{";

	ret += "\"country_selected_index\": " + QString::number(selected_country_) + ", \"city_selected_index\": " + QString::number(selected_city_) + ", \"list\":[";

	for (auto i = l.begin(); i != l.end(); i++)
	{
		ret += "{\"iso\":\"" + (*i).countryISO + "\",";
		ret += "\"full\":\"" + (*i).country + "\",";
		ret += "\"img\":\"" + (*i).countryImg + "\",";
		ret += "\"cities\":[";

		for (auto i2 = (*i).cities.begin(); i2 != (*i).cities.end(); i2++)
			ret += "\"" + (*i2) + "\"" + (!(i2 == (*i).cities.end() - 1) ? "," : "");;

		ret += QString("]}") + ((!(i == l.end() - 1)) ? "," : "");
	}

	ret += "]}]";

	return ret;
}

QList<country_city_item> IPList::parseJsonList(QJsonObject &list)
{
	QList<country_city_item> ret;

	country_city_item tmp;
	
	foreach(const QString& key, list.keys())
	{
		QJsonObject value = list.value(key).toObject();

		auto c_full = value["country_full"].toString();

		if (c_full.isEmpty() || key.isEmpty())
			continue;

		tmp.country = c_full;
		tmp.countryISO = key;

		auto cities = value["cities"];
		QJsonArray arr;

		tmp.countryImg = key;

		if (!QFile::exists(":/img/flags/img/flags/" + tmp.countryImg.toLower() + ".png")) 
			tmp.countryImg = "_unknown";

		tmp.cities.clear();

		if (!cities.isNull() && cities.isArray() && !(arr = cities.toArray()).isEmpty())
		{
			foreach(const QJsonValue & value, arr)
			{
				QJsonObject obj = value.toObject();

				if (obj.isEmpty())
					continue;

				auto city = obj["city"].toString();
				auto r_full = obj["regionfull"].toString();

				if (!tmp.cities.contains(city))
					tmp.cities.append(city);
			}
		}

		std::sort(tmp.cities.begin(), tmp.cities.end());
		tmp.cities.prepend("Any");
		
		ret.append(tmp);
	}
	
	std::sort(ret.begin(), ret.end());

	tmp.cities.clear();
	tmp.cities.append("Any");
	tmp.country = "Any";
	tmp.countryISO = "ANY";
	tmp.countryImg = "_unknown";

	ret.prepend(tmp);

	return ret;
}

void IPList::ParseIpList(QString &iplistm2)
{
	if (iplistm2.isEmpty())
		return;

	QJsonDocument jsonResponse = QJsonDocument::fromJson(iplistm2.toUtf8());

	QJsonObject jsonObject = jsonResponse.object();

	QJsonObject residential = jsonObject["residential"].toObject();
	QJsonObject server = jsonObject["server"].toObject();

	if (residential.isEmpty() || server.isEmpty())
		return;

	QList<country_city_item> residential_list_;
	QList<country_city_item> server_list_;

	residential_list_ = parseJsonList(residential);
	server_list_ = parseJsonList(server);

	Lock();
	residential_list = residential_list_;
	server_list = server_list_;
	UnLock();

	static time_t last_update = time(NULL);

	if(time(NULL) >= last_update)
		updateGUIListCache();

	if (residential_list_.count() > 5 && server_list_.count() > 5)
		last_update += 60 * 60;
}

void IPList::updateGUIListCache()
{
	Lock();
	QList<country_city_item> residential_list_ = residential_list;
	QList<country_city_item> server_list_ = server_list;
	UnLock();

	QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

	bool is_residential = settings.value(QString("is_residential"), false).toBool();

	QString json_ = GetJsonCountry(is_residential ? residential_list_ : server_list_);
	QString js_ = "<message>COUNTRY_CITY_LIST</message><details>" + json_ + "</details>";

	emit MainWindow::__instance->SendNewGuiEvent(js_);
}