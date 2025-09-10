#include "tuxlerapp.h"
#include "config.h"

#include <QApplication>
#include <QProxyStyle>
#include <QTextEdit>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QSharedMemory>
#include <QDesktopWidget>
#include <quuid.h>
#include <assert.h>
#include <Shlwapi.h>

#include <thread>

std::vector<std::string> get_all_files_names_within_folder(std::string folder);
std::string GetDmpDirPath();
std::string getDmpFilePath(std::string path_);
std::string GetExtAppPath(std::string *path_, std::string app_name);
std::string getFileVersion(std::string &appPath);
std::string getFileVersion(std::string &appPath);
std::string GetExeFolder();
void UploadCrashDump(std::string filename, std::string file_path);

QSharedMemory sharedMemory;

MainWindow * _wndPtr = NULL;
bool is_app_quitting = false;
std::string UNIQUE_ID = "";
std::string UNIQUE_ID_APP = "";

#ifndef GWL_WNDPROC
#define GWL_WNDPROC (-4) 
#endif

#ifndef QT_SHARED
    #include <QtPlugin>

    Q_IMPORT_PLUGIN(qico)
    Q_IMPORT_PLUGIN(qcncodecs)
    Q_IMPORT_PLUGIN(qjpcodecs)
    Q_IMPORT_PLUGIN(qkrcodecs)
    Q_IMPORT_PLUGIN(qtwcodecs)
#endif

#ifdef Q_OS_WIN32
#include <windows.h>
#ifndef NO_WINSPARKLE
#include "winsparkle/include/winsparkle.h"
#endif

#define IDB_CHECK_FOR_UPDATES   100

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
    #define VC_EXTRALEAN
#include <windows.h>
#endif

#include <dbt.h>

WNDPROC OldWinProc = NULL;
int DeviceArrival = 0;
int DeviceRemoval = 0;
MainWindow* Window = NULL;

int override_window_procedure(HWND & hWnd);
void SetExceptionHandler();

LRESULT CALLBACK NewWndProc(HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
);
#endif

#ifdef Q_OS_WIN32

void Console()
{
    AllocConsole();
    FILE *pFileCon = NULL;
    pFileCon = freopen("CONOUT$", "w", stdout);

    COORD coordInfo;
    coordInfo.X = 130;
    coordInfo.Y = 9000;

    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coordInfo);
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE),ENABLE_QUICK_EDIT_MODE| ENABLE_EXTENDED_FLAGS);
}

#endif

LONG WINAPI ExceptionHandler(PEXCEPTION_POINTERS pExceptionInfo)
{
	TerminateProcess(GetCurrentProcess(), 0);
	return EXCEPTION_EXECUTE_HANDLER;
}

void SetExceptionHandler()
{
	SetUnhandledExceptionFilter(ExceptionHandler);
}

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN32
	SetExceptionHandler();
	SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
#endif

#ifndef QT_SHARED
    Q_INIT_RESOURCE(WebCore);
    Q_INIT_RESOURCE(WebKit);

#ifdef QTWEBKIT_23
    Q_INIT_RESOURCE(InspectorBackendCommands);
#else
    Q_INIT_RESOURCE(InspectorBackendStub);
#endif
#endif

    QApplication a(argc, argv);

    sharedMemory.setKey(UNIQUEID_SINGLE_APP);
    sharedMemory.attach();

#ifdef Q_OS_WIN32

    if(__DEBUG__){

        Console();
    }

#endif

	{
		QSettings settings(SETTINGS_NAME, SETTINGS_NAME);
		settings.setValue("size", QSize(-1, -1));

		QStringList cmdline_args = QCoreApplication::arguments();

		foreach(QString a_, cmdline_args)
		{
			std::string a = a_.toStdString();
			std::string s = "--UNIQUE_ID=";
			int idx = a.find(s);

			if (idx != -1)
			{
				std::string tmp = a.substr(idx + s.length());

				if (!tmp.empty())
				{
					if (tmp[0] == '"')
					{
						tmp = tmp.substr(1);

						if (!tmp.empty())
						{
							if (tmp[tmp.length() - 1] == '"')
								s = tmp.substr(0, tmp.length()-1);
						}
					}
					else
						s = tmp;
				}

				if (!s.empty())
				{
					std::string tmp = s;
					char* filepart = PathFindFileNameA(tmp.c_str());
					PathRemoveExtensionA(filepart);

					s = filepart;

					if (!s.empty())
					{
						idx = s.find("___");

						if (idx != -1)
						{
							s = s.substr(idx+3);

							if (!s.empty())
							{
								idx = s.rfind("___");

								if (idx != -1)
								{
									UNIQUE_ID = s.substr(0, idx);

									QString tmp = QString::fromStdString(UNIQUE_ID);

									if (!UNIQUE_ID.empty())
									{
										settings.setValue("UNIQUE_ID", tmp);
										settings.sync();
									}
								}
							}
						}
					}
				}

				break;
			}
		}

		QString UNIQUE_ID_ = settings.value("UNIQUE_ID", "").toString();
		UNIQUE_ID = UNIQUE_ID_.toStdString();

		QString UNIQUE_ID_APP_ = settings.value("UNIQUE_ID_APP", "").toString();

		if (UNIQUE_ID_APP_.isEmpty())
		{
			QUuid uid = QUuid::createUuid();
			QString id = uid.toString();

			settings.setValue("UNIQUE_ID_APP", id);
			settings.sync();

			UNIQUE_ID_APP = id.toStdString();
		}
		else
			UNIQUE_ID_APP = UNIQUE_ID_APP_.toStdString();
	}

    if(TuxlerApp::HasCMDLineArgument("--uninstall")){

        QSettings settings(SETTINGS_NAME, SETTINGS_NAME);
        settings.clear();

        return 0;
    }

    if(TuxlerApp::HasCMDLineArgument("--uninstall-close")){

        InstanceCommunication::Send("QUIT\n");

        if(__DEBUG__)std::cout << "Another instance is already running;";

        return 0;
    }

    if (!sharedMemory.create(1) && !(TuxlerApp::HasCMDLineArgument("--enable-multiple-instances"))) {

        InstanceCommunication::Send("SHOW\n");

        if(__DEBUG__)std::cout << "Another instance is already running;";

        return 0;
    }

    TuxlerApp w;

    MainWindow::__instance = &w;

    _wndPtr = &w;

    if(!QSslSocket::supportsSsl()) {

       QMessageBox(QMessageBox::Information, "OpenSSL error", "Please install OpenSSL library: http://www.openssl.org/").exec();

       return 0;
    }

#ifdef Q_OS_WIN32
    Window = &w;
#endif

    if(TuxlerApp::HasCMDLineArgument(AUTO_START_ARG))
    {
        w.oldPos = w.pos();
        QSize oldSize = w.size();

        w.ignoreShow = true;
        w.move(0-10000-oldSize.width(), 0-100000-oldSize.height());
        w.show();
        w.hide();

        w.ignoreShow = false;
        w.restoreOnShow = true;

    }
	else 
		w.show();


#ifdef Q_OS_WIN32

    bool deinit = false;

        HWND hwnd = (HWND)w.effectiveWinId();

        if(override_window_procedure(hwnd))
        {
#ifndef NO_WINSPARKLE
            win_sparkle_init();
#endif
            deinit = true;
        }
#endif

	MainWindow::__instance->StartHelperProcess(&a);

    int ret = a.exec();

#ifdef Q_OS_WIN32
#ifndef NO_WINSPARKLE
    if(deinit) 
		win_sparkle_cleanup();
#endif
#endif

    _wndPtr = NULL;

    return ret;
}

#ifdef Q_OS_WIN32

LRESULT CALLBACK NewWndProc(HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    if (uMsg == WM_COMMAND && Window)
    {
        switch (wParam){

        case IDB_CHECK_FOR_UPDATES:
        {
            QEvent event((QEvent::Type)IDB_CHECK_FOR_UPDATES_ID);
            QCoreApplication::sendEvent(Window, &event);
            break;
        }

        };
    }
	else if(WM_QUIT == uMsg || uMsg == WM_DESTROY)
	{
		is_app_quitting = true;

        if(_wndPtr != NULL)
             _wndPtr->__instance->quitTimer.start();
    }
	else if (WM_QUERYENDSESSION == uMsg)
	{
		is_app_quitting = true;
		return TRUE;
	}
    else if(WM_ENDSESSION == uMsg)
	{
		is_app_quitting = true;

        if(_wndPtr != NULL)
		{
             _wndPtr->__instance->quitTimer.start();
             PostQuitMessage(0);
        }

        return FALSE;

    }
	else if(WM_POWERBROADCAST == uMsg)
	{
        switch(wParam) 
		{
            case PBT_APMQUERYSUSPEND:

                return TRUE;

                break;

            case PBT_APMQUERYSUSPENDFAILED:

            if(_wndPtr != NULL)
                 _wndPtr->__instance->connectTimer.start();

                break;

            case PBT_APMBATTERYLOW:

                break;

            case PBT_APMSUSPEND:

                break;


            case PBT_APMRESUMESUSPEND:

            if(_wndPtr != NULL)
                 _wndPtr->__instance->connectTimer.start();

                break;
        }
    }

    return CallWindowProc(OldWinProc,hwnd,uMsg,wParam,lParam);
}

int override_window_procedure(HWND & hWnd)
{
    OldWinProc = (WNDPROC)GetWindowLong(hWnd,GWL_WNDPROC);

    if(!OldWinProc) 
		return (int)OldWinProc;

    return SetWindowLong(hWnd,GWL_WNDPROC,(LONG)(WNDPROC)NewWndProc);
}
#endif


