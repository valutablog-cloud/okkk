/*
 * Copyright (c) 2013, Psiphon Inc.
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <QObject>

#ifdef Q_OS_WIN32
#include "proxysettings.h"
#include "config.h"
#include "functions.h"
#include <wininet.h>
#include <ras.h>
#include <raserror.h>

#ifdef _MSC_VER
#include <regex>
#endif

#include <qsettings.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>

#pragma comment(lib, "Rasapi32.lib")

void AddOriginalProxyInfo(const connection_proxy& proxyInfo);
bool GetConnectionsAndProxyInfo(vector<string>& connections, vector<connection_proxy>& proxyInfo);
bool SetConnectionProxy(const connection_proxy& setting);
bool GetConnectionProxy(connection_proxy& setting);


static const TCHAR* SYSTEM_PROXY_SETTINGS_PROXY_BYPASS = _T("<local>");
static const int INTERNET_OPTIONS_NUMBER = 3;


template <typename charT>
vector<basic_string<charT> >& split(const basic_string<charT> &s, charT delim, std::vector<basic_string<charT> > &elems) {
    basic_stringstream<charT> ss(s);
    basic_string<charT> item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

template <typename charT>
std::vector<basic_string<charT> > split(const basic_string<charT> &s, charT delim) {
    vector<basic_string<charT> > elems;
    return split(s, delim, elems);
}

struct connection_proxy
{
    tstring name;
    DWORD flags;
    tstring proxy;
    tstring bypass;

    bool operator==(const connection_proxy& rhs)
    {
        return
            this->name == rhs.name &&
            this->flags == rhs.flags &&
            this->proxy == rhs.proxy &&
            this->bypass == rhs.bypass;
    }

    bool operator!=(const connection_proxy& rhs)
    {
        return !(*this == rhs);
    }
};


SystemProxySettings::SystemProxySettings()
    : m_settingsApplied(false)
{
    m_originalSettings.clear();
    SetHttpProxyPort(0);
    SetHttpsProxyPort(0);
    SetSocksProxyPort(0);

	QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

	QString set = settings.value("proxySettingsJSON", "").toString();

	if(set.length() > 0){
		
	m_settingsApplied = true;

	QJsonDocument jsonResponse = QJsonDocument::fromJson(set.toUtf8());   

	QJsonObject obj = jsonResponse.object();

	QStringList lst = obj.keys();

	foreach(QString key, lst){

	QJsonArray proxiesarr = obj[key].toArray();

	foreach(QJsonValue val, proxiesarr){

		QJsonObject obj = val.toObject();

		connection_proxy proxy;

		proxy.bypass = toStdString(obj["bypass"].toString());
		proxy.name = toStdString(obj["name"].toString());
		proxy.flags = obj["flags"].toInt();
		proxy.proxy = toStdString(obj["proxy"].toString());

		m_originalSettings.push_back(proxy);
	}	
	}
	}
}

SystemProxySettings::~SystemProxySettings()
{
    //Revert();
}

void SystemProxySettings::SetHttpProxyPort(int port)
{
    m_httpProxyPort = port;
}
void SystemProxySettings::SetHttpsProxyPort(int port)
{
    m_httpsProxyPort = port;
}
void SystemProxySettings::SetSocksProxyPort(int port)
{
    m_socksProxyPort = port;
}

bool SystemProxySettings::Apply()
{

    // Configure Windows Internet Settings to use our HTTP Proxy
    // This affects IE, Chrome, Safari and recent Firefox builds

    tstring proxyAddress = MakeProxySettingString();
    if(proxyAddress.length() == 0)
    {
        return false;
    }

    m_settingsApplied = true;

    vector<tstring> connections;
    vector<connection_proxy> proxyInfo;
    if (!GetConnectionsAndProxyInfo(connections, proxyInfo))
    {
        return false;
    }

    if (!Save(proxyInfo))
    {
        return false;
    }

    if (!SetConnectionsProxies(connections, proxyAddress))
    {
        return false;
    }

    return true;
}

tstring SystemProxySettings::MakeProxySettingString()
{
    // This string is passed to InternetSetOption to set the proxy address for each protocol.
    // NOTE that we do not include a proxy setting for FTP, since Polipo does not support
    // proxying FTP, so FTP will not be proxied.

    tstringstream proxySetting;

    if (m_httpProxyPort > 0)
    {
        if (proxySetting.str().length() > 0) proxySetting << _T(";");
        //proxySetting << _T("http=127.0.0.1:") << m_httpProxyPort;
    }

    if (m_httpsProxyPort > 0)
    {
        if (proxySetting.str().length() > 0) proxySetting << _T(";");
        //proxySetting << _T("https=127.0.0.1:") << m_httpsProxyPort;
    }

    if (m_socksProxyPort > 0)
    {
        if (proxySetting.str().length() > 0) proxySetting << _T(";");
        proxySetting << _T("socks=127.0.0.1:") << m_socksProxyPort;
    }

    return proxySetting.str();
}

bool SystemProxySettings::Revert()
{
    // Revert Windows Internet Settings back to user's original configuration

    if (!m_settingsApplied)
    {
        return true;
    }

    bool success = true;

    for (connection_proxy_iter ii = m_originalSettings.begin();
         ii != m_originalSettings.end();
         ++ii)
    {
        if (!SetConnectionProxy(*ii))
        {
            success = false;
            break;
        }
    }

    if (success)
    {
        m_originalSettings.clear();

		QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

		settings.setValue("proxySettingsJSON", QString(""));
    }

    return success;
}

// TODO: do this properly.
// ie. Save original proxy settings to a file, and remove the file on restoring settings.
// If the file exists when saving original settings, use the file's contents and don't save
// the existing settings.
void SystemProxySettings::PreviousCrashCheckHack(connection_proxy& proxySettings)
{
    tstring proxyAddress = MakeProxySettingString();

    // Don't save settings that are the same as we will be setting.
    // Instead, save default (no proxy) settings.
    if (   (proxySettings.flags == PROXY_TYPE_PROXY)
        && (proxySettings.proxy == proxyAddress)
        && (proxySettings.bypass == SYSTEM_PROXY_SETTINGS_PROXY_BYPASS))
    {
        proxySettings.flags = PROXY_TYPE_DIRECT;
        proxySettings.proxy = "";
        proxySettings.bypass = "";
    }
}

bool SystemProxySettings::Save(const vector<connection_proxy>& proxyInfo)
{
    if (!m_originalSettings.empty())
    {
        return false;
    }

    connection_proxy proxySettings;

	QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

	QString json = "{";

	int i = 0;

    for (vector<connection_proxy>::const_iterator ii = proxyInfo.begin();
         ii != proxyInfo.end();
         ++ii)
    {

        connection_proxy proxySettings = *ii;

		json += "\""+QString::number(i) + "\":[{\"name\":\"" + QString(proxySettings.name.c_str()) + "\",\"bypass\":\""+QString(proxySettings.bypass.c_str())+"\",\"flags\":"+QString::number(proxySettings.flags)+",\"proxy\":\""+QString(proxySettings.proxy.c_str())+"\"}]";

		if(!(proxyInfo.end() - ii == 1)) json += ",";

		i++;

        PreviousCrashCheckHack(proxySettings);
        m_originalSettings.push_back(proxySettings);
    }

	json += "}";

	settings.setValue("proxySettingsJSON", json);

    return true;
}

bool SystemProxySettings::SetConnectionsProxies(const vector<tstring>& connections, const tstring& proxyAddress)
{
    bool success = true;
    bool failedToVerify = false;

    for (vector<tstring>::const_iterator ii = connections.begin();
         ii != connections.end();
         ++ii)
    {
        connection_proxy proxySettings;
        // These are the new proxy settings we want to use
        proxySettings.name = *ii;
        proxySettings.flags = PROXY_TYPE_PROXY;
        proxySettings.proxy = proxyAddress;
        proxySettings.bypass = SYSTEM_PROXY_SETTINGS_PROXY_BYPASS;

        if (!SetConnectionProxy(proxySettings))
        {
            success = false;
            break;
        }

        // Read back the settings to verify that they have been applied
        connection_proxy entry;
        entry.name = proxySettings.name;
        if (!GetConnectionProxy(entry) ||
            entry != proxySettings)
        {
            failedToVerify = true;

            if (entry.name.empty())
            {

                success = false;
                break;
            }
            else
            {

            }
        }
    }

    if (failedToVerify)
    {

    }

    return success;
}


/**********************************************************
*
* Proxy settings helpers
*
**********************************************************/

static DWORD GetRasEntries(LPRASENTRYNAMEA& rasEntryNames, DWORD& bufferSize, DWORD& entries)
{
    if (rasEntryNames)
    {
        // Deallocate memory for the entries buffer
        HeapFree(GetProcessHeap(), 0, rasEntryNames);
        rasEntryNames = 0;
    }

    rasEntryNames = (LPRASENTRYNAMEA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, bufferSize);

    if (!rasEntryNames)
    {
        //my_print(NOT_SENSITIVE, false, _T("HeapAlloc failed when trying to enumerate RAS connections"));
        return 0;
    }

    // The first RASENTRYNAME structure in the array must contain the structure size
    rasEntryNames[0].dwSize = sizeof(RASENTRYNAME);

    // Call RasEnumEntries to enumerate all RAS entry names
    return RasEnumEntriesA(0, 0, rasEntryNames, &bufferSize, &entries);
}


vector<tstring> GetRasConnectionNames()
{
    vector<tstring> connections;
    LPRASENTRYNAMEA rasEntryNames = 0;
    // The RasEnumEntries API requires that we pass in a buffer first
    // and if the buffer is too small, it tells us how big a buffer it needs.
    // For the first call we will pass in a single RASENTRYNAME struct.
    DWORD bufferSize = sizeof(RASENTRYNAME);
    DWORD entries = 0;
    DWORD returnCode = ERROR_SUCCESS;

    try
    {
        returnCode = GetRasEntries(rasEntryNames, bufferSize, entries);

        if (ERROR_BUFFER_TOO_SMALL == returnCode)
        {
            returnCode = GetRasEntries(rasEntryNames, bufferSize, entries);
        }

        if (ERROR_SUCCESS != returnCode)
        {
            //my_print(NOT_SENSITIVE, false, _T("failed to enumerate RAS connections (%d)"), returnCode);
            return connections;
        }

        for (DWORD i = 0; i < entries; i++)
        {
            connections.push_back(rasEntryNames[i].szEntryName);
        }
    }
    catch (...)
    {
    }
    // TODO: Don't throw 0.  Throw and catch a std::exception.
    // Maybe put the error message in the exception.

    // Clean up

    if (rasEntryNames)
    {
        //Deallocate memory for the entries buffer
        HeapFree(GetProcessHeap(), 0, rasEntryNames);
        rasEntryNames = 0;
    }

    return connections;
}


bool SetConnectionProxy(const connection_proxy& setting)
{
    INTERNET_PER_CONN_OPTION_LISTA list;
    INTERNET_PER_CONN_OPTIONA options[INTERNET_OPTIONS_NUMBER];
    list.dwSize = sizeof(list);
    // Pointer to a string that contains the name of the RAS connection
    // or NULL, which indicates the default or LAN connection, to set or query options on.
    list.pszConnection = setting.name.length() ? const_cast<TCHAR*>(setting.name.c_str()) : 0;
    list.dwOptionCount = sizeof(options)/sizeof(INTERNET_PER_CONN_OPTIONA);
    list.pOptions = options;

    list.pOptions[0].dwOption = INTERNET_PER_CONN_FLAGS;
    list.pOptions[0].Value.dwValue = setting.flags;

    list.pOptions[1].dwOption = INTERNET_PER_CONN_PROXY_SERVER;
    list.pOptions[1].Value.pszValue = const_cast<TCHAR*>(setting.proxy.c_str());

    list.pOptions[2].dwOption = INTERNET_PER_CONN_PROXY_BYPASS;
    list.pOptions[2].Value.pszValue = const_cast<TCHAR*>(setting.bypass.c_str());

    bool success = (0 != InternetSetOptionA(0, INTERNET_OPTION_PER_CONNECTION_OPTION, &list, list.dwSize)) &&
                   (0 != InternetSetOptionA(NULL, INTERNET_OPTION_SETTINGS_CHANGED, NULL, 0)) &&
                   (0 != InternetSetOptionA(NULL, INTERNET_OPTION_REFRESH , NULL, 0));

    if (!success)
    {
        //my_print(NOT_SENSITIVE, false, _T("InternetSetOption error: %d"), GetLastError());
        // NOTE: We are calling the Unicode version of InternetSetOption.
        // In Microsoft Internet Explorer 5, only the ANSI versions of InternetQueryOption and InternetSetOption
        // will work with the INTERNET_PER_CONN_OPTION_LIST structure.
    }

    return success;
}

bool GetConnectionProxy(connection_proxy& setting)
{
    INTERNET_PER_CONN_OPTION_LISTA list;
    INTERNET_PER_CONN_OPTIONA options[INTERNET_OPTIONS_NUMBER];
    unsigned long length = sizeof(list);
    list.dwSize = length;
    // Pointer to a string that contains the name of the RAS connection
    // or NULL, which indicates the default or LAN connection, to set or query options on.
    list.pszConnection = setting.name.length() ? const_cast<TCHAR*>(setting.name.c_str()) : 0;
    list.dwOptionCount = sizeof(options)/sizeof(INTERNET_PER_CONN_OPTIONA);
    list.pOptions = options;

    options[0].dwOption = INTERNET_PER_CONN_FLAGS;
    options[1].dwOption = INTERNET_PER_CONN_PROXY_SERVER;
    options[2].dwOption = INTERNET_PER_CONN_PROXY_BYPASS;

    if (0 == InternetQueryOptionA(0, INTERNET_OPTION_PER_CONNECTION_OPTION, &list, &length))
    {
        //my_print(NOT_SENSITIVE, false, _T("InternetQueryOption error: %d"), GetLastError());
        // NOTE: We are calling the Unicode version of InternetQueryOption.
        // In Microsoft Internet Explorer 5, only the ANSI versions of InternetQueryOption and InternetSetOption
        // will work with the INTERNET_PER_CONN_OPTION_LIST structure.
        return false;
    }

    setting.flags = options[0].Value.dwValue;
    setting.proxy = options[1].Value.pszValue ? options[1].Value.pszValue : _T("");
    setting.bypass = options[2].Value.pszValue ? options[2].Value.pszValue : _T("");

    // Cleanup
    if (options[1].Value.pszValue)
    {
        GlobalFree(options[1].Value.pszValue);
    }
    if (options[2].Value.pszValue)
    {
        GlobalFree(options[2].Value.pszValue);
    }

    return true;
}


bool GetConnectionsAndProxyInfo(vector<string>& connections, vector<connection_proxy>& proxyInfo)
{
    connections.clear();
    proxyInfo.clear();

    // Get a list of connections, starting with the dial-up connections
    connections = GetRasConnectionNames();

    // NULL indicates the default or LAN connection
    connections.push_back(_T(""));

    for (vector<tstring>::const_iterator ii = connections.begin();
         ii != connections.end();
         ++ii)
    {
        connection_proxy entry;

        entry.name = *ii;
        if (GetConnectionProxy(entry))
        {
            proxyInfo.push_back(entry);
            AddOriginalProxyInfo(entry);
        }
        else
        {
            connections.clear();
            proxyInfo.clear();

            return false;
        }
    }

    return true;
}


/**********************************************************
*
* Original proxy info for use with diagnostic feedback info
*
**********************************************************/

HANDLE g_originalProxyInfoMutex = CreateMutex(NULL, FALSE, 0);
vector<connection_proxy> g_originalProxyInfo;



void AddOriginalProxyInfo(const connection_proxy& proxyInfo)
{

    vector<connection_proxy>::iterator match = find(g_originalProxyInfo.begin(), g_originalProxyInfo.end(), proxyInfo);
    if (match == g_originalProxyInfo.end())
    {
        // Entry doesn't already exist in vector
        g_originalProxyInfo.push_back(proxyInfo);
    }
}

bool SystemProxySettings::GetUserLanProxy(tstring& proxyType, tstring& proxyHost, int& proxyPort)
{
    connection_proxy setting;
    setting.name = _T("");

    if(!GetConnectionProxy(setting))
    {
        return false;
    }

    if( setting.flags & PROXY_TYPE_PROXY)
    {
        tstring proxy_str = setting.proxy;
        std::size_t colon_pos;
        std::size_t equal_pos;
        map<tstring, tstring> Proxies;

        colon_pos = proxy_str.find(':');
        /*
        case 1: no ':' in the proxy_str
        ""
        proxy host and port are not set
        */
        if(tstring::npos == colon_pos)
            return false;

        /*
        case 2: '=' protocol identifier not found in the proxy_str
        "host:port"
        same proxy used for all protocols
        */
        equal_pos = proxy_str.find('=');
        if(tstring::npos == equal_pos)
        {
            //store it
            Proxies.insert(pair<tstring, tstring>(_T("https"), proxy_str));
        }

        /*
        case 3: '=' protocol identifier found in the proxy_str,
        "http=host:port;https=host:port;ftp=host:port;socks=host:port"
        loop through proxy types, pick  https or socks in that order
        */

        //split by protocol
        std::size_t prev = 0, pos;
        tstring protocol, proxy;
        while ((pos = proxy_str.find('=', prev)) != tstring::npos)
        {
            if (pos > prev)
            {
                protocol = (proxy_str.substr(prev, pos-prev));
            }
            prev = pos+1;

            pos = proxy_str.find(';', prev);

            if(pos == tstring::npos)
            {
                proxy = (proxy_str.substr(prev, tstring::npos));
            }
            else if(pos >= prev)
            {
                proxy =  (proxy_str.substr(prev, pos-prev));
                prev = pos+1;
            }

            Proxies.insert(pair<tstring, tstring>(protocol, proxy));
        }

        map<tstring, tstring>::iterator it = Proxies.find(_T("https"));
        if(it != Proxies.end())
        {
            proxyType = _T("https");
        }
        else
        {
            it = Proxies.find(_T("socks"));

            if(it == Proxies.end())
            {
                //no usable proxies
                return false;
            }

            proxyType = _T("socks");
        }

        proxy_str = it->second;

        colon_pos = proxy_str.find(':');

        if(colon_pos == tstring::npos)
        {
            return false;
        }

        tstring port_str = proxy_str.substr(colon_pos+1);
        proxyPort = atoi(port_str.c_str());

        if(proxyPort <= 0 || proxyPort > 65536) //check if port is valid
        {
            return false;
        }

        proxyHost = proxy_str.substr(0,colon_pos);
        return true;
    }
    return false;
}
#endif
