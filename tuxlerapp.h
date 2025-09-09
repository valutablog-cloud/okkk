#ifndef TUXLERAPP_H
#define TUXLERAPP_H

#include <QObject>
#include "mainwindow.h"
#include "newipengineconnector.h"
#include "config.h"

void Lock();
void UnLock();

class TuxlerApp : public MainWindow
{
    Q_OBJECT
public:
    TuxlerApp();

    SystemProxy systemProxy;

	QAction *actionUpgrade, *accountInfo, *support, *reseller, *userGuide, *about, *actionLogIn, *actionExit, *actionShow, *actionHide, *actionUpdates;

	void showMenuLoading();
	void ShowMenuFree();
	void ShowMenuPremium();

#ifndef Q_OS_LINUX
    QSystemTrayIcon * sys;
#endif

	NewIPEngineConnector *connector;

	QTimer *show_connecting_timer;

	int local_helper_session_id;
	QString email_global, password_global;
    QMenu *myMenu;
    std::vector<int> connect_list;
    QTimer connectTimer;
    QTimer quitTimer;
    IPS myIP, currentIP;
    int PortIfFail;
    bool __isPremium;
    bool __suspressNotificationsForce;
    bool __suspressNotifications;
    char * TuxlerInfoText;
	bool enabledReloadToNextNearbyLocation;
	bool enabledPreferredCountrySelection;
	bool enabledPreferredCitySelection;
	int ipLocationPoolLimit;
	int ipLocationChangesLimit;
	int bandwidthLimit;
	int currentIPLocationPool;
	int currentIPLocationChanges;
	int currentBandwidth;

    SettingsManager settingsManager;
    Translator translator;
    IPList ipList;
    MessageQeue messageQeue;

	void UpdatePremiumStats();
    void ReceivedAccountInfo(QString &email, QString &password, bool isok, bool ispremium);
	QDateTime toLocalTimeZone(QDateTime date);
	void FreePremiumTime(QString &info);
	void ExpireInfo(QString &info);
	void LimitsInfo(QString &info);
	void AccountInfo(QString &info);
    static bool HasCMDLineArgument(QString arg);
    bool __isIpChangingActive(bool *set = NULL);
    void __isPremiumset(bool val);
	void showFreePremiumBar();

    /** @addtogroup display_functions */
    /*@{*/
    /**
    *@brief show ToolBar window
    *@param title window title
    *@param text main window text
    *@param timevisible visibility in miliseconds
    */
    void ShowToolBarWindow(char * title, QString text, int timevisible = 3000);

    /**
    *@brief show ToolBar window
    *@param title window title
    *@param text main window text
    *@param timevisible visibility in miliseconds
    */
    void ShowToolBarWindow(char * title, char* text, int timevisible = 3000);

    /**
    *@brief show ToolBar window
    *@param title window title
    *@param text main window text
    *@param timevisible visibility in miliseconds
    */
    void ShowToolBarWindow(QString title, QString text, int timevisible = 3000);

    /**
     *@brief set new displayed currently used IP address
     */
    void SetMyIp(IPS json);
    /*@}*/

	void SetCurrentIp(IPS json);
    void SendNewGuiEvent(QString);
    void StartProxy();
    void StopProxy();


#ifdef Q_OS_WIN32
    SystemProxySettings proxySettings;
#endif

private:
    InstanceCommunication instanceCommunication;
    ParseMessage parseMessage;
    //Connector * connector;

    /** @addtogroup javascript_gui */
    /*@{*/
    /**
    *@brief JavaScriptBridge instance
    */
    JavaScriptBridge bridge;
    /*@}*/

    QTimer postLaunch;

public:
    bool __isIpChangingActiveV;

private:
    QMenu *myMenuTray;
    QTimer messageDisplayTimerInterval;

    /** @addtogroup javascript_gui */
    /*@{*/
    /**
    *@brief hold messages sent from main window until WebView is initialised
    *@details when MainWindow::NewGuiEvent2 is called from js with "LOADED" message those messages are forwarder to WebView and cleared
    */
    QList<QString> __delayedMsgs;

    /**
    *@brief set to true when WebView send LOADED message
    */
    bool __guiloaded;
    /*@}*/

    QTimer deleteLater;
    time_t lastBlockedMessage;
    QList<QTcpSocket*> __deleteLater;

    /** @addtogroup display_functions */
    /*@{*/
    /**
    *@brief ToolTip object
    */
    ToolTip *tooltip;
    /*@}*/

    void TryLogin(QString &email, QString &password);
	bool reconnected_event, disconnected_event;
	QList<std::pair<std::string, std::string>> message_event;
	static bool is_helper_running;

public slots:
	void MenuSupport();
	void MenuReseller();
	void MenuUserGuide();
	void MenuAbout();
	void show_connecting_slot();
    void Exit();
	void StartHelperProcess(QObject*);
	void NewEngineEvent();
	void NewReconnected();
	void NewDisconnected();

	void NewMessage(std::pair<std::string, std::string> &m);

private slots:
    void MenuUpgrade();
    void MenuLogIn();
    void MenuShow();
    void MenuHide();

    void QuitShutDown();
    void connectTimerSlot();

    /** @addtogroup display_functions */
    /*@{*/
    /**
     *@brief Displays qeued messages with Display::ShowToolBarWindow
     */
    void DisplayMessages();
    /*@}*/

	void Reconnected();
	void Disconnected();

    void startTCPThread();
    void TrayIconAction(QSystemTrayIcon::ActivationReason reason);
    void checkForUpdates();
    void msgBoxClosed(QAbstractButton*);
    void DeleteLater();
	void ReplyFinished(QNetworkReply *reply);
    /** @addtogroup javascript_gui */
    /*@{*/
    /**
    *@brief a slot that helps process js messages asynchronously
    */
    void EventAsyncSlot(QString);

    /**
    *@brief create javascript bridge
    *@details function NewMessage in MessageReceiver.js receives messages send from c++
    */
    void mainFrame_javaScriptWindowObjectCleared();

    /**
    *@brief receives signal from js bridge and emits EventAsync to call MainWindow::NewGuiEvent2 asynchronously
    */
    void NewGuiEvent(QString);

    /**
    *@brief process message from js
    */
    void NewGuiEvent2(QString);

    /**
    *@brief process message from js - send to WebView and clear Message Qeue
    */
    void SendEventToJavaScript();
    /*@}*/

	void IncreaseIPChangeCounter();
	void checkIfDisplayRating();
	void showRating(bool update_time);
	void RatingCanceled();
	int getLocalHelperSessionId();
	static int getRand(int min, int max);
signals:

    /** @addtogroup javascript_gui */
    /*@{*/
    /**
    *@brief signal connected to JavaScriptBridge::SendNewGuiEvent
    */
    void SendEventToBridge(QString);
    /*@}*/

    void NewMessageServer();
    void NewPort(int);

    /** @addtogroup javascript_gui */
    /*@{*/
    /**
    *@brief signal helps call js message process asynchronously connected with MainWindow::EventAsyncSlot
    */
    void EventAsync(QString);
    /*@}*/

    /** @addtogroup main_connection */
    /*@{*/
    /**
    *@brief signal helps call js message process asynchronously connected with MainWindow::EventAsyncSlot
    */
    void startConnecting();
    /*@}*/
};

#endif // TUXLERAPP_H
