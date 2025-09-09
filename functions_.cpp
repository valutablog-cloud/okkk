#include "functions.h"
#include "sha1.h"
#include "mainwindow.h"
#include "tuxlerapp.h"

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <chrono>
#include <thread>

#include <Shlobj.h>
#include <Shlwapi.h>
#include <direct.h>
#include <TlHelp32.h>
#include <wininet.h>
#include <mutex>

#define PROCESS_CLASS NORMAL_PRIORITY_CLASS

std::recursive_mutex mmutex;

void Lock() {

	mmutex.lock();
}

void UnLock() {

	mmutex.unlock();
}

std::string GetExtAppDirPath() {

	char szPath[MAX_PATH + 100];
	szPath[0] = 0;

	std::string path = szPath;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_COMMON_APPDATA, 0, 0, szPath)))
	{
		if (!PathAppendA(szPath, "TuxlerChromeExtensionHelperApp"))
			return "";

		path = szPath;
	}

	return path;
}

std::string GetExtAppPath(std::string *path_, std::string app_name) {

	auto dir = GetExtAppDirPath();

	if (path_ != NULL)
		dir = *path_;

	char szPath[MAX_PATH + 100];
	strcpy_s(szPath, MAX_PATH + 100, dir.c_str());

	std::string path = szPath;

	if (!PathAppendA(szPath, app_name.c_str()))
		return "";

	path = szPath;

	return path;
}

std::string GetExeFolder() {

	static CHAR buf[MAX_PATH + 1];

	if (GetModuleFileNameA(NULL, buf, sizeof(buf)) == 0)
		return "";

	PathRemoveFileSpecA(buf);

	return buf;
}

bool RunApp(std::string appPath, std::string args, bool wait = true, DWORD *out = NULL, HANDLE *handle = NULL, bool show_window = false, int _wait_timeout = INFINITE) {

	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	std::string args__ = appPath;

	if (!args.empty())
		args__ += " " + args;

	if (!CreateProcessA(appPath.c_str(), ((!args.empty()) ? (char*)args__.c_str() : NULL), NULL, NULL, FALSE, (show_window ? 0 : CREATE_NO_WINDOW), NULL, NULL, &si, &pi))
	{
		std::string fatal = "CANNOT RUN EXE: " + appPath;
		std::cout << fatal;
		return false;
	}

	SetPriorityClass(pi.hProcess, PROCESS_CLASS);

	if (wait)
		WaitForSingleObject(pi.hProcess, _wait_timeout);

	if (out != NULL && handle != NULL)
	{
		*out = pi.dwProcessId;
		*handle = pi.hProcess;
	}
	else
		CloseHandle(pi.hProcess);

	CloseHandle(pi.hThread);

	return true;
}

QString getTag(QString tag, QString &search){

    QRegExp rx(tag+":(.*);");
    rx.setMinimal(true);

    QString ret;

    if(rx.indexIn(search) != -1)
        ret = rx.cap(1);

    return ret;
}

bool __DEBUG(){

    return TuxlerApp::HasCMDLineArgument("debug");
}

std::string toStdString(QString s){

    std::string res = "";

    for(QString::iterator it = s.begin(); it != s.end(); it++){

        QChar &c = (*it);

        res += c.toLatin1();
    }

    return res;
}

bool is_numeric(QString s){

    bool ok = false;
    s.toInt(&ok);

    return ok;
}

#ifdef Q_OS_WIN32
#include <windows.h>

using namespace std;

#ifdef Q_OS_WIN32
#include <TlHelp32.h>
#include <ShlObj.h>
#endif

#define BUFSIZE 256

typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);
typedef BOOL (WINAPI *PGPI)(DWORD, DWORD, DWORD, DWORD, PDWORD);

bool isWin8()
{
   OSVERSIONINFOEX osvi;
   SYSTEM_INFO si;
   PGNSI pGNSI;
   PGPI pGPI;
   BOOL bOsVersionInfoEx;
   DWORD dwType;
   bool is8 = false;

   ZeroMemory(&si, sizeof(SYSTEM_INFO));
   ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));

   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
   bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO*) &osvi);

   if( ! bOsVersionInfoEx ) return false;

   // Call GetNativeSystemInfo if supported or GetSystemInfo otherwise.

   pGNSI = (PGNSI) GetProcAddress(
      GetModuleHandle(TEXT("kernel32.dll")),
      "GetNativeSystemInfo");
   if(NULL != pGNSI)
      pGNSI(&si);
   else GetSystemInfo(&si);

   if ( VER_PLATFORM_WIN32_NT==osvi.dwPlatformId &&
        osvi.dwMajorVersion > 4 )
   {
      if ( osvi.dwMajorVersion == 6 )
      {
         if ( osvi.dwMinorVersion == 1 || osvi.dwMinorVersion == 2 )
         {
            if ( osvi.wProductType == VER_NT_WORKSTATION && osvi.dwMinorVersion == 2) is8 = true;
         }
        }
    }

   return is8;
}



#endif
