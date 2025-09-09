#ifdef Q_OS_WIN32
#pragma once

/*
 * Copyright (c) 2011, Psiphon Inc.
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

#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <tchar.h>
#include <windows.h>

using namespace std;


#ifdef _UNICODE
#define tstring wstring
#define tistringstream wistringstream
#define tregex wregex
#else
#define tstring string
#define tistringstream istringstream
#ifdef _MSC_VER
#define tregex regex
#endif
#endif



typedef basic_stringstream<TCHAR> tstringstream;

static tstring NarrowToTString(const string& narrowString)
{
#ifdef _UNICODE
    wstring wideString(narrowString.length(), L' ');
    std::copy(narrowString.begin(), narrowString.end(), wideString.begin());
    return wideString;
#else
    return narrowString;
#endif
}

static string TStringToNarrow(const tstring& tString)
{
#ifdef _UNICODE
    return string(tString.begin(), tString.end());
#else
    return tString;
#endif
}

#ifdef UNICODE
    #define WIDEN2(x) L##x
    #define WIDEN(x) WIDEN2(x)
    #define __WFILE__ WIDEN(__FILE__)
    #define __WFUNCTION__ WIDEN(__FUNCTION__)
    #define __TFILE__ __WFILE__
    #define __TFUNCTION__ __WFUNCTION__
#else
    #define __TFILE__ __FILE__
    #define __TFILE__ __FUNCTION__
#endif

#include <vector>

using namespace std;

struct connection_proxy;


class SystemProxySettings
{
public:
    SystemProxySettings();
    virtual ~SystemProxySettings();

    //
    // The Set*ProxyPort functions do *not* apply the setting -- they only set
    // a member variable that will be used when Apply is called to actually
    // make the settings take effect.
    void SetHttpProxyPort(int port);
    void SetHttpsProxyPort(int port);
    void SetSocksProxyPort(int port);
    bool Apply();

    bool Revert();

    bool GetUserLanProxy(tstring& proxyType, tstring& proxyHost, int& proxyPort);

private:
    typedef vector<connection_proxy>::iterator connection_proxy_iter;

    void PreviousCrashCheckHack(connection_proxy& proxySettings);
    bool Save(const vector<connection_proxy>& proxyInfo);
    bool SetConnectionsProxies(const vector<tstring>& connections, const tstring& proxyAddress);
    tstring MakeProxySettingString();

    bool m_settingsApplied;
    vector<connection_proxy> m_originalSettings;

    int m_httpProxyPort;
    int m_httpsProxyPort;
    int m_socksProxyPort;
};

#endif
