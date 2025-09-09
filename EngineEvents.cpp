//
//  EngineEvents.cpp
//  Tuxler
//
//  Created by Jaroslaw Lazar on 03/02/2018.
//  Copyright © 2018 Tuxler. All rights reserved.
//

#include <stdio.h>
#include <iostream>

#ifndef _DESKTOP
#include "Settings.hpp"
#endif

#include "TuxlerApp.h"

std::vector<QString> messages_to_server;

bool last_connected_state = false;

void NextIP(bool first, bool next)
{
	QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

	QString selected_country_iso = settings.value(QString("selected_country_iso"), QString("ANY")).toString();
	QString selected_city = settings.value(QString("selected_city"), QString("Any")).toString();

	if (!TuxlerApp::__instance->enabledPreferredCitySelection)
		selected_city = "Any";

	QString msg;

	bool is_residential = settings.value(QString("is_residential"), false).toBool();

	if (is_residential)
		 msg = "<message>CHANGE_IP_COUNTRY_CITY<details>next_nearby:" + QString(next ? "1" : "0") + ";country:" + selected_country_iso + ";city:" + QUrl::toPercentEncoding(selected_city) + ";</details></message>";
	else
		msg = "<message>CHANGE_IP_COUNTRY_CITY_NEW_TYPE<details>next_nearby:" + QString(next ? "1" : "0") + ";country:" + selected_country_iso + ";city:" + QUrl::toPercentEncoding(selected_city) + ";</details></message>";

	SendMessageToServer(msg);
}

void LogIn()
{
	Lock();
	auto email = TuxlerApp::__instance->email_global.toStdString();
	auto password = TuxlerApp::__instance->password_global.toStdString();
	UnLock();

	std::string tmp = "<message>LOGIN<details>LOGIN:" + email + ";NAME:" + ";PASSWORD:" + password + ";" + ";SYSINFO:" + "" + ";VERSION:8;</details></message>";
	QString send = QString::fromStdString(tmp);

	SendMessageToServer(send);
}

void SendMessageToServer(QString &msg)
{
	Lock();
	messages_to_server.push_back(msg);
	UnLock();
}

std::string getEmail()
{
	Lock();
	auto tmp = TuxlerApp::__instance->email_global;
	std::string ret = tmp.toStdString();
	UnLock();

	return ret;
}

std::string getPassword()
{
	Lock();
	auto tmp = TuxlerApp::__instance->password_global;
	std::string ret = tmp.toStdString();
	UnLock();

	return ret;
}

void ConnectionStateChanged(bool connected) {

	if (!last_connected_state && connected)
	{
		qDebug() << "server reconnected";

		TuxlerApp::__instance->NewReconnected();
		TuxlerApp::__instance->connector->SetEvent();
	}
	else if (last_connected_state && !connected)
	{
		TuxlerApp::__instance->NewDisconnected();
		TuxlerApp::__instance->connector->SetEvent();
	}

	last_connected_state = connected;

	if(last_connected_state)
		LogIn();
}

void NewMessage(std::pair<std::string, std::string> &m) {

	std::string tmpm = "<message>" + m.first + "<details>" + m.second + "</details></message>";

	if (!m.first.empty())
	{
		TuxlerApp::__instance->NewMessage(m);
		TuxlerApp::__instance->connector->SetEvent();
	}
}
