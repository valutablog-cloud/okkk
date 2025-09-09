#include <random>
#include <qhttpmultipart.h>
#include <iostream>

#include "tuxlerapp.h"
#include "config.h"
#include "version_info.h"
#include "base64.h"

void Lock();
void UnLock();
void LogIn();
void StartWebSocketClient(QObject*);

std::string getEmail();
std::string getPassword();
std::string GetExeFolder();
bool RunApp(std::string appPath, std::string args, bool wait = true, DWORD *out = NULL, HANDLE *handle = NULL, bool show_window = false, int _wait_timeout = INFINITE);
std::string GetExtAppPath(std::string *path_, std::string app_name);

bool TuxlerApp::is_helper_running = false;

TuxlerApp::TuxlerApp() :
        PortIfFail(-1),
        quitTimer(this),
        postLaunch(this),
        __guiloaded(false),
        messageDisplayTimerInterval(this),
        bridge(this),
        __suspressNotifications(false),
        deleteLater(this),
        __isIpChangingActiveV(false),
        __suspressNotificationsForce(false),
        __isPremium(false),
		enabledReloadToNextNearbyLocation(true),
		enabledPreferredCountrySelection(true),
		enabledPreferredCitySelection(true),
		ipLocationPoolLimit(-2),
		ipLocationChangesLimit(-2),
		bandwidthLimit(-2),
		currentIPLocationPool(0),
		currentIPLocationChanges(0),
		currentBandwidth(0),
	reconnected_event(false),
	disconnected_event(false),
	local_helper_session_id(0)
{
	__instance = this;

	connector = new NewIPEngineConnector(NULL);
	connector->moveToThread(connector);
	connector->start();

	show_connecting_timer = new QTimer(this);
	show_connecting_timer->setSingleShot(true);
	show_connecting_timer->setInterval(15*1000);
	show_connecting_timer->start();

	connect(show_connecting_timer, SIGNAL(timeout()), this, SLOT(show_connecting_slot()));

	connect(connector, SIGNAL(NewEngineEvent()), this, SLOT(NewEngineEvent()));

    //connector = new Connector("", "", this);
    //thread = new TCPThread();
    tooltip = new ToolTip(this);

    myMenu = new QMenu();
    myMenuTray = new QMenu();

#ifndef Q_OS_LINUX
    sys = new QSystemTrayIcon(this);
#endif

    lastBlockedMessage = 0;
    currentIP.localid = -1;
    myIP.localid = -1;
    __suspressNotifications = HasCMDLineArgument(AUTO_START_ARG);
    TuxlerInfoText = INFO_TEXT;



    QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

    quitTimer.setSingleShot(true);
    quitTimer.setInterval(500);

    connectTimer.setSingleShot(true);
    connectTimer.setInterval(0);

    deleteLater.setInterval(1000*5);
    deleteLater.setSingleShot(false);
    deleteLater.start();


    postLaunch.setSingleShot(true);
    postLaunch.setInterval(0);
    postLaunch.start();

    messageDisplayTimerInterval.start();
    messageDisplayTimerInterval.setInterval(3000);
    messageDisplayTimerInterval.setSingleShot(false);

	actionUpgrade = new QAction("&Upgrade to Premium", this);
	accountInfo = new QAction("&Account Info", this);
	support = new QAction("&Support", this);
	reseller = new QAction("&Reseller Program", this);
	userGuide = new QAction("&User Guide", this);
	about = new QAction("&About Tuxler", this);

    actionLogIn = new QAction("&Premium Login", this);
    actionExit = new QAction("&Exit", this);
    actionShow = new QAction("Show Window", this);
    actionHide = new QAction("&Hide to Taskbar", this);
    actionUpdates = new QAction("&Check for updates", this);

	accountInfo->setVisible(false);

	myMenu->addAction(actionHide);
	myMenu->addAction(actionLogIn);
	myMenu->addAction(accountInfo);
    myMenu->addAction(actionUpgrade);

#ifdef Q_OS_WIN32
    myMenu->addAction(actionUpdates);
#endif

	myMenu->addAction(support);
	myMenu->addAction(reseller);
	myMenu->addAction(userGuide);
	myMenu->addAction(about);
	myMenu->addAction(actionExit);

    myMenuTray->addAction(actionUpgrade);

#ifdef Q_OS_WIN32
    myMenuTray->addAction(actionUpdates);
#endif

    //myMenuTray->addAction(actionLogIn);
    myMenuTray->addAction(actionShow);
    myMenuTray->addAction(actionHide);
    myMenuTray->addAction(actionExit);


    connect(&deleteLater, SIGNAL(timeout()), this, SLOT(DeleteLater()));
    connect(&quitTimer, SIGNAL(timeout()), this, SLOT(QuitShutDown()));
    connect(&connectTimer, SIGNAL(timeout()), this, SLOT(connectTimerSlot()));
    connect(this, SIGNAL(EventAsync(QString)), SLOT(EventAsyncSlot(QString)), Qt::QueuedConnection);
    connect(&postLaunch, SIGNAL(timeout()), this, SLOT(startTCPThread()), Qt::QueuedConnection);
    email_global = settings.value("email", QString("")).toString();
    password_global = settings.value("password", QString("")).toString();
    //connect(connector, SIGNAL(NewMessageSignal()), &this->messageQeue, SLOT(NewMessage()), Qt::QueuedConnection);
    //connect(this, SIGNAL(startConnecting()), connector, SLOT(startConnecting()), Qt::QueuedConnection);
    //connect(connector, SIGNAL(Reconnected()), this, SLOT(Reconnected()), Qt::QueuedConnection);
    //connect(this, SIGNAL(NewPort(int)), connector, SLOT(NewPort(int)), Qt::QueuedConnection);
    //connect(this, SIGNAL(NewMessageServer()), connector, SLOT(NewMessageServer()), Qt::QueuedConnection);
    connect(&bridge, SIGNAL(NewMessage(QString)), this, SLOT(NewGuiEvent(QString)));
    connect(this, SIGNAL(SendEventToBridge(QString)), &bridge, SLOT(SendNewGuiEvent(QString)));
    connect(&bridge, SIGNAL(SendEventToJavaScript()), this, SLOT(SendEventToJavaScript()));
    connect(ui->webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(mainFrame_javaScriptWindowObjectCleared()));
    connect(&messageDisplayTimerInterval, SIGNAL(timeout()), this, SLOT(DisplayMessages()));

	connect(support, SIGNAL(triggered()), this, SLOT(MenuSupport()));
	connect(reseller, SIGNAL(triggered()), this, SLOT(MenuReseller()));
	connect(userGuide, SIGNAL(triggered()), this, SLOT(MenuUserGuide()));
	connect(about, SIGNAL(triggered()), this, SLOT(MenuAbout()));

    connect(actionUpgrade, SIGNAL(triggered()), this, SLOT(MenuUpgrade()));
	connect(actionLogIn, SIGNAL(triggered()), this, SLOT(MenuLogIn()));
	connect(accountInfo, SIGNAL(triggered()), this, SLOT(MenuLogIn()));
    connect(actionExit, SIGNAL(triggered()), this, SLOT(Exit()));
    connect(actionShow, SIGNAL(triggered()), this, SLOT(MenuShow()));
    connect(actionHide, SIGNAL(triggered()), this, SLOT(MenuHide()));
    connect(actionUpdates, SIGNAL(triggered()), this, SLOT(checkForUpdates()));
    connect(myMenu, SIGNAL(triggered(QAction*)), this, SLOT(ResetButtonHover(QAction*)));

#ifndef Q_OS_LINUX
    connect(sys, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(TrayIconAction(QSystemTrayIcon::ActivationReason)));
#endif

    emit SendNewGuiEvent(QString("<message>SETEMPASS</message><details>[{\"idx\":{\"email\":\""+email_global+"\", \"password\":\""+password_global+"\"}}]</details>"));

#ifndef Q_OS_LINUX
    sys->setContextMenu(myMenuTray);
    sys->setIcon(QIcon(":/images/app_logo.png"));
    sys->show();
#endif

    systemProxy.RestoreProxy();

	showMenuLoading();
}

void TuxlerApp::showMenuLoading()
{
	actionUpgrade->setVisible(false);
	accountInfo->setVisible(false);
	support->setVisible(false);
	reseller->setVisible(false);
	userGuide->setVisible(false);
	about->setVisible(false);
	actionLogIn->setVisible(false);
	actionExit->setVisible(true);
	actionShow->setVisible(true);
	actionHide->setVisible(true);
	actionUpdates->setVisible(false);
}

void TuxlerApp::ShowMenuFree()
{
	showMenuLoading();

	actionUpgrade->setVisible(true);
	support->setVisible(true);
	reseller->setVisible(true);
	userGuide->setVisible(true);
	about->setVisible(true);
	actionLogIn->setVisible(true);
	actionUpdates->setVisible(true);
}

void TuxlerApp::ShowMenuPremium()
{
	ShowMenuFree();

	actionUpgrade->setVisible(false);
	actionLogIn->setVisible(false);
	accountInfo->setVisible(true);
}

void TuxlerApp::NewMessage(std::pair<std::string, std::string> &m)
{
	Lock();
	message_event.append(m);
	UnLock();
}

void TuxlerApp::NewReconnected()
{
	reconnected_event = true;
	disconnected_event = false;
}

void TuxlerApp::NewDisconnected()
{
	disconnected_event = true;
	reconnected_event = false;
}

void TuxlerApp::NewEngineEvent()
{
	if (reconnected_event)
	{
		reconnected_event = false;
		Reconnected();
	}

	if (disconnected_event)
	{
		disconnected_event = false;
		Disconnected();
	}

	Lock();
	auto tmp = message_event;
	message_event.clear();
	UnLock();

	for (auto it = tmp.begin(); it != tmp.end(); it++)
	{
		Msg m;
		m.msg = QString::fromStdString((*it).first);
		m.det = QString::fromStdString((*it).second);

		messageQeue.__msgs.append(m);
		messageQeue.NewMessage();
	}
}

QDateTime TuxlerApp::toLocalTimeZone(QDateTime date) {

	QDateTime localTime(date.toLocalTime());

	return localTime;
}

void TuxlerApp::UpdatePremiumStats() {

	QString ip_location_pool, ip_location_changes, country_enabled, city_enabled, bandwidth;

	bandwidth = QString::number(currentBandwidth) + " of " + (bandwidthLimit == -2 ? "unknown" : (bandwidthLimit == -1 ? "unlimited" : QString::number(bandwidthLimit)));
	city_enabled = enabledPreferredCitySelection ? "enabled" : "disabled";
	country_enabled = enabledPreferredCountrySelection ? "enabled" : "disabled";
	ip_location_changes = QString::number(currentIPLocationChanges) + " of " + (ipLocationChangesLimit == -2 ? "unknown" : (ipLocationChangesLimit == -1 ? "unlimited" : QString::number(ipLocationChangesLimit)));
	ip_location_pool = QString::number(currentIPLocationPool) + " of " + (ipLocationPoolLimit == -2 ? "unknown" : (ipLocationPoolLimit == -1 ? "unlimited" : QString::number(ipLocationPoolLimit)));

	QString det = "{\"ip_location_pool\":\""+ ip_location_pool +"\",";
	det += "\"ip_location_changes\":\"" + ip_location_changes + "\",";
	det += "\"country_enabled\":\"" + country_enabled + "\",";
	det += "\"city_enabled\":\"" + city_enabled + "\",";
	det += "\"bandwidth\":\"" + bandwidth + "\"}";

	emit SendNewGuiEvent(QString("<message>SETPREMIUMINFO</message><details>"+det+"</details>"));
}

void TuxlerApp::AccountInfo(QString &info) {

	QJsonDocument jsonResponse = QJsonDocument::fromJson(info.toUtf8());
	QJsonObject jsonObject = jsonResponse.object();

	currentIPLocationPool = jsonObject["currentIPLocationPool"].toInt();
	currentIPLocationChanges = jsonObject["currentIPLocationChanges"].toInt();
	currentBandwidth = jsonObject["currentBandwidth"].toInt();

	UpdatePremiumStats();
}

void TuxlerApp::LimitsInfo(QString &info) {

	QJsonDocument jsonResponse = QJsonDocument::fromJson(info.toUtf8());
	QJsonObject jsonObject = jsonResponse.object();

	bool enabledReloadToNextNearbyLocation_ = jsonObject["enabledReloadToNextNearbyLocation"].toBool();
	bool enabledPreferredCountrySelection_ = jsonObject["enabledPreferredCountrySelection"].toBool();
	bool enabledPreferredCitySelection_ = jsonObject["enabledPreferredCitySelection"].toBool();

	ipLocationPoolLimit = jsonObject["ipLocationPoolLimit"].toInt();
	ipLocationChangesLimit = jsonObject["ipLocationChangesLimit"].toInt();
	bandwidthLimit = jsonObject["bandwidthLimit"].toInt();

	if ((!enabledReloadToNextNearbyLocation_ && enabledReloadToNextNearbyLocation_ != enabledReloadToNextNearbyLocation) || (!enabledPreferredCountrySelection_ && enabledPreferredCountrySelection_ != enabledPreferredCountrySelection))
	{
		emit SendNewGuiEvent(QString("<message>SETCOUNTRYANY</message><details></details>"));
		emit SendNewGuiEvent(QString("<message>SETCITYANY</message><details></details>"));
	}
	else if (!enabledPreferredCitySelection_ && enabledPreferredCitySelection_ != enabledPreferredCitySelection)
	{
		emit SendNewGuiEvent(QString("<message>SETCITYANY</message><details></details>"));
	}

	enabledReloadToNextNearbyLocation = enabledReloadToNextNearbyLocation_;
	enabledPreferredCountrySelection = enabledPreferredCountrySelection_;
	enabledPreferredCitySelection = enabledPreferredCitySelection_;

	UpdatePremiumStats();
}

void TuxlerApp::FreePremiumTime(QString &info) {

	QString info_ = info;

	int num = info_.toInt();

	if (num >= 60)
		info_ = (QString::number(static_cast<int>(num / 60))) + " minutes";
	else
		info_ += " seconds";

#ifndef IPSHARKK
	emit SendNewGuiEvent(QString("<message>SETEXPIRES</message><details>" + info_ + "</details>"));
#endif
}

void TuxlerApp::ExpireInfo(QString &info){

	QJsonDocument jsonResponse = QJsonDocument::fromJson(info.toUtf8());
	QJsonObject jsonObject = jsonResponse.object();

	QString expire = jsonObject.contains("expirationDate") ? jsonObject["expirationDate"].toString() : "";

	if(!expire.isEmpty())
	{
		QDateTime expireDate = TuxlerApp::toLocalTimeZone(QDateTime::fromString(expire, Qt::DateFormat::ISODate)), now = QDateTime::currentDateTime();

		int days_diff = now.daysTo(expireDate);

		if(days_diff > 0)
		{
#ifndef IPSHARKK
			emit SendNewGuiEvent(QString("<message>SETEXPIRES</message><details>" + QString::number(days_diff) + " days</details>"));
#else

			emit SendNewGuiEvent(QString("<message>SETEXPIRES</message><details>"+QString::number(days_diff)+"</details>"));
#endif
		}
	}
}

void TuxlerApp::QuitShutDown(){

    Exit();
}

void TuxlerApp::connectTimerSlot(){

    emit startConnecting();
}


void TuxlerApp::StartProxy(){

    //proxy->start();
}

void TuxlerApp::StopProxy(){

    //proxy->stop();
}

void TuxlerApp::checkForUpdates(){

#ifdef Q_OS_WIN32
#ifndef NO_WINSPARKLE
    win_sparkle_check_update_with_ui();
#endif
#endif
}

void TuxlerApp::msgBoxClosed(QAbstractButton*){

}

void TuxlerApp::startTCPThread(){

    //thread->__instanceConnector = connector;

    //connector->moveToThread(thread);

    //thread->start();
}

bool TuxlerApp::HasCMDLineArgument(QString arg){

    QStringList cmdline_args = QCoreApplication::arguments();

    foreach (QString a, cmdline_args) if(a == arg) return true;

    return false;
}

void TuxlerApp::TrayIconAction(QSystemTrayIcon::ActivationReason reason){

    if(__DEBUG__)std::cout << reason;
    if(reason == QSystemTrayIcon::DoubleClick) show();
}

void TuxlerApp::MenuUpgrade(){

    QString mY_url = QString::fromStdString(URL_PREMIUM);

    QUrl url = QUrl(mY_url);

    bool isURLopened = QDesktopServices::openUrl ( url );

    if(__DEBUG__)std::cout << "goto premium website:" << isURLopened;
}

void TuxlerApp::MenuLogIn(){

    if(isHidden()) 
		show();

	emit SendNewGuiEvent(QString("<message>CHANGE_VIEW</message><details>23</details>"));
}

void TuxlerApp::StartHelperProcess(QObject *parent)
{
	if (is_helper_running)
		return;

	is_helper_running = true;

#ifdef IPSHARKK
	std::string app_name = "ExtensionHelperAppHelperIPSharkk.exe";
#else
	std::string app_name = "ExtensionHelperAppHelperTuxler.exe";
#endif

	auto cd = GetExeFolder();
	auto path = GetExtAppPath(&cd, app_name);

	unsigned long mid = GetCurrentProcessId();

	std::string params = "--wait_for_parent=";
	params += to_string(mid);
	params += " --port_inc=";
	params += std::to_string(WS_PJUMP);
	params += " --port_start=";
	params += std::to_string(WS_PSTART);
	params += " --port_max=";
	params += std::to_string(WS_END);
	params += " --app-name=";
	
#ifdef IPSHARKK
	params += "ips_desktop_app_hlp";
#else
	params += "tux_desktop_app_hlp";
#endif

	std::string em = getEmail();
	std::string pas = getPassword();

	params += " --username=";
	params += base64_encode(em);

	params += " --password=";
	params += base64_encode(pas);

#ifdef _DEBUG
	path = "C:\\Users\\jarek_jarecki\\Desktop\\ExtensionHelperApp\\ExtensionHelperApp\\Debug\\ExtensionHelperApp.exe";
#endif

	bool sw = false;

#ifdef _DEBUG
	sw = true;
#endif

	if (!RunApp(path, params.c_str(), false, 0, 0, sw))
	{
		TerminateProcess(GetCurrentProcess(), 0);
	}

	StartWebSocketClient(parent);
}

void TuxlerApp::Exit(){

    closeEvent(NULL);
    close();

	TerminateProcess(GetCurrentProcess(), 0);
}

void TuxlerApp::MenuShow(){

    show();
    raise();
}

void TuxlerApp::MenuHide(){

    hide();
}

void TuxlerApp::DisplayMessages(){

    QList<QString> tmp;

    if(messageQeue.listmsg.size() > 0){

        messageQeue.listmsg = messageQeue.listmsg.toSet().toList();

        tmp = messageQeue.listmsg;

        if(messageQeue.listmsg.size() > 0) messageQeue.listmsg.erase(messageQeue.listmsg.begin());
    }

    if(tmp.size() > 0){

        QString ss = TuxlerInfoText;

        ParsedMessage2 msg;

        QString wt = (tmp[0]);

        if(parseMessage.ParseMessage2(wt, msg)){

            if (messageQeue.msgLst.indexOf(msg.type) == 13){

                ShowToolBarWindow(msg.title, msg.body);

                __isPremiumset(true);

            }else if (messageQeue.msgLst.indexOf(msg.type) == 14 || messageQeue.msgLst.indexOf(msg.type) == 15){

                    if (msg.body.length() > 100){

                        msg.body = msg.body.mid(0, 100);
                        msg.body += "...";
                    }

                    ShowToolBarWindow(msg.title, msg.body);

            }else{

                 ShowToolBarWindow(msg.title, msg.body);
            }
        }
    }
}

void TuxlerApp::__isPremiumset(bool val){

    __isPremium = val;

	if (val)
	{
		emit SendNewGuiEvent(QString("<message>SETPREMIUM</message><details></details>"));
		ShowMenuPremium();
	}
	else
	{
		emit SendNewGuiEvent(QString("<message>SETFREE</message><details></details>"));
		ShowMenuFree();
	}

    settingsManager.LoadSettings();
}

void TuxlerApp::SendNewGuiEvent(QString m){

    if(__guiloaded){

        emit SendEventToBridge(m);

    } else {

        __delayedMsgs.append(m);
    }
}

void TuxlerApp::ShowToolBarWindow(char * title, char*text, int timevisible){

    QString txt(text);

    ShowToolBarWindow(title, txt, timevisible);
}

void TuxlerApp::ShowToolBarWindow(QString title, QString text, int timevisible){

    if(__suspressNotifications || __suspressNotificationsForce) return;

    QString t(title);
    t = t.replace("\\n", "\n");
    text = text.replace("\\n", "\n");

    tooltip->showToolTip(title, text, 5, timevisible);
}

void TuxlerApp::ShowToolBarWindow(char * title, QString text, int timevisible){

    QString t(title);

    ShowToolBarWindow(t, text, timevisible);
}

void TuxlerApp::SetMyIp(IPS json){

    json.countryImg = json.countryiso;

    if(!QFile::exists(":/img/flags/img/flags/" + json.countryImg.toLower() + ".png")) json.countryImg = "_unknown";

    QString wtmp = "[{\"idx\":{\"countryCodeImg\":\""+json.countryImg+"\",\"id\":-1,\"countryCode\":\""+json.countryiso.toLower()+"\",\"countryName\":\""+json.country+"\",\"city\":\""+json.city+"\",\"region\":\"" + json.regionfull + "\"}}]";

    emit SendNewGuiEvent(QString("<message>SETMYIP</message><details>"+wtmp+"</details>"));
}

void TuxlerApp::SetCurrentIp(IPS json) {

	json.countryImg = json.countryiso;

	if (!QFile::exists(":/img/flags/img/flags/" + json.countryImg.toLower() + ".png")) json.countryImg = "_unknown";

	QString wtmp = "[{\"idx\":{\"countryCodeImg\":\"" + json.countryImg + "\",\"id\":-1,\"countryCode\":\"" + json.countryiso.toLower() + "\",\"countryName\":\"" + json.country + "\",\"city\":\"" + json.city + "\",\"region\":\"" + json.regionfull + "\"}}]";

	emit SendNewGuiEvent(QString("<message>SETCURRENTIP</message><details>" + wtmp + "</details>"));
}

void TuxlerApp::showFreePremiumBar() 
{
	if (__isPremium)
	{
		emit SendNewGuiEvent(QString("<message>SETPREMIUM</message><details></details>"));
		ShowMenuPremium();
	}
	else
	{
		emit SendNewGuiEvent(QString("<message>SETFREE</message><details></details>"));
		ShowMenuFree();
	}
}

void TuxlerApp::show_connecting_slot()
{
	showFreePremiumBar();
	emit SendNewGuiEvent(QString("<message>CHANGE_VIEW</message><details>9</details>"));
}

void TuxlerApp::Disconnected() 
{
	//emit SendNewGuiEvent(QString("<message>ENABLEDISABLELOGINBUTTON</message><details>true</details>"));
	// SendNewGuiEvent(QString("<message>HIGHLIGHT</message><details>CLEAR</details>"));

	MainWindow::__instance->ipList.__ipListLoaded = false;
	emit SendNewGuiEvent(QString("<message>CHANGE_VIEW</message><details>9</details>"));
}

void TuxlerApp::Reconnected()
{
	show_connecting_timer->stop();

	showFreePremiumBar();

	static bool check_if_show_rating = true;

	if (check_if_show_rating)
	{
		check_if_show_rating = false;
		checkIfDisplayRating();
	}

    currentIP.localid = -1;

    //emit SendNewGuiEvent(QString("<message>ENABLEDISABLELOGINBUTTON</message><details>true</details>"));
    //emit SendNewGuiEvent(QString("<message>HIGHLIGHT</message><details>CLEAR</details>"));

	emit SendNewGuiEvent(QString("<message>CHANGE_VIEW</message><details>7</details>"));
	emit SendNewGuiEvent(QString("<message>SETFREE</message><details></details>"));
	NextIP(true, false);
}

void TuxlerApp::DeleteLater(){

START:

    for(QList<QTcpSocket*>::iterator it = __deleteLater.begin(); it != __deleteLater.end(); it++){

        (*it)->deleteLater();

        __deleteLater.erase(it);

        goto START;
    }
}

void TuxlerApp::SendEventToJavaScript(){

    ui->webView->page()->mainFrame()->evaluateJavaScript("NewMessage();");

    bridge.MessageQeue.clear();
}

void TuxlerApp::ReceivedAccountInfo(QString &email, QString &password, bool isok, bool ispremium){

    if (isok){

           emit SendNewGuiEvent(QString("<message>SETLOGOUT</message><details></details>"));

           if(__DEBUG__)std::cout << "NewEmail:" << email.toStdString();

		   Lock();
		   this->password_global = password;
		   this->email_global = (email);
		   UnLock();

           __isPremiumset(false);

           if (ispremium)
              __isPremiumset(true);

           QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

           settings.setValue("email", email);
           settings.setValue("password", password);

		   LogIn();

       }else ShowToolBarWindow("Logging in unsuccessful", "Check your email and password. Login status unchanged.");
}

void TuxlerApp::TryLogin(QString &email, QString &passwordsha1){

    QString send = "<message>GET_ACCOUNT_INFO<details>email:" + email + ";password:" + passwordsha1 + ";</details></message>";

	SendMessageToServer(send);

    emit NewMessageServer();
}

void TuxlerApp::EventAsyncSlot(QString det){

    NewGuiEvent2(det);
}

void TuxlerApp::NewGuiEvent(QString event){

    emit EventAsync(event);
}

void TuxlerApp::showRating(bool update_time)
{
	QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

	if (update_time)
		settings.setValue("RATING_DISPLAYED_UNIX_TIME", time(NULL));

	settings.setValue("DID_CANCEL_RATING", false);

	emit SendNewGuiEvent(QString("<message>CHANGE_VIEW</message><details>35</details>"));
}

void TuxlerApp::checkIfDisplayRating() 
{
	QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

	int loc_change = settings.value("LOCATION_CHANGE_COUNTER", 0).toInt();

	int startup_times = settings.value("STARTUP_COUNTER", 0).toInt();
	time_t last_displayed = settings.value("RATING_DISPLAYED_UNIX_TIME", 0).toLongLong();
	bool did_cancel_raring_last_time = settings.value("DID_CANCEL_RATING", false).toBool();

	int showAfterRunNumber = SHOWAFTERRUNNUMBER;
	int displayNotOftenThanDays = DISPLAYNOTOFTENTHANDAYS;
	int showAfterLocationChangeNumber = SHOWAFTERLOCATIONCHANGENUMBER;
	int showEveryDayIfDidntFillFeedback = SHOWEVERYDAYIFDIDNTFILLFEEDBACK;
	int resetAllAfterDays = RESETALLAFTERDAYS;

	if (displayNotOftenThanDays < 1)
	{
		qDebug() << "Rating" <<  "exit";
		return;
	}

	time_t time_ = time(NULL);

	if (time_ - last_displayed < displayNotOftenThanDays * 24 * 60 * 60)
	{
		if (
			
#ifdef _DEBUG
			//true ||
#endif
			(did_cancel_raring_last_time && showEveryDayIfDidntFillFeedback != -1 && time_ - last_displayed >= showEveryDayIfDidntFillFeedback * 24 * 60 * 60))
		{
			settings.setValue("RATING_DISPLAYED_UNIX_TIME", last_displayed + (showEveryDayIfDidntFillFeedback * 24 * 60 * 60));

			qDebug() << ("Rating", "Display rating didn't fill feedback");

			showRating(false);
		}

		qDebug() << "Rating" << "ignore - too often "  << std::string(std::to_string(time_)).c_str() << "  "  << std::to_string(last_displayed).c_str();

		return;
	}

	if (
		
#ifdef _DEBUG
		//true ||
#endif

		(loc_change >= showAfterLocationChangeNumber && showAfterLocationChangeNumber != -1))
	{
		settings.setValue("LOCATION_CHANGE_COUNTER", 0);

		qDebug() << "Rating" << "Display rating location change";

		showRating(true);
	}
	else if (startup_times >= showAfterRunNumber && showAfterRunNumber != -1)
	{
		settings.setValue("STARTUP_COUNTER", 0);

		qDebug() << "Rating" << "Display rating startup";

		showRating(true);
	}
	else if (resetAllAfterDays != -1 && time_ - last_displayed >= resetAllAfterDays * 24 * 60 * 60 && last_displayed > 0)
	{
		qDebug() << "Rating" <<  "reset all";

		settings.setValue("STARTUP_COUNTER", 0);
		settings.setValue("LOCATION_CHANGE_COUNTER", 0);
		settings.setValue("RATING_DISPLAYED_UNIX_TIME", 0);
		settings.setValue("DID_CANCEL_RATING", false);
	}

	qDebug() << "Rating" << "no condition met";
}

void TuxlerApp::IncreaseIPChangeCounter()
{
	QSettings settings(SETTINGS_NAME, SETTINGS_NAME);
	
	int ip_change = settings.value("LOCATION_CHANGE_COUNTER", 0).toInt()+1;
	settings.setValue("LOCATION_CHANGE_COUNTER", ip_change);

	checkIfDisplayRating();
}

void TuxlerApp::RatingCanceled()
{
	QSettings settings(SETTINGS_NAME, SETTINGS_NAME);
	settings.setValue("DID_CANCEL_RATING", true);
}

int TuxlerApp::getRand(int min, int max)
{
	unsigned int ms = static_cast<unsigned>(QDateTime::currentMSecsSinceEpoch());
	std::mt19937 gen(ms);
	std::uniform_int_distribution<> uid(min, max);

	return uid(gen);
}

int TuxlerApp::getLocalHelperSessionId()
{
	if (local_helper_session_id == 0)
		local_helper_session_id = getRand(1, 10000);

	return local_helper_session_id;
}

void TuxlerApp::ReplyFinished(QNetworkReply *reply)
{
	int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

	if (status_code != 200)
		qDebug() << "FeedbackAppFragment" << "could not upload rating" << status_code;
}

void TuxlerApp::MenuAbout()
{
	emit SendNewGuiEvent(QString("<message>CHANGE_VIEW</message><details>14</details>"));
}

void TuxlerApp::MenuReseller()
{
	emit SendNewGuiEvent(QString("<message>CHANGE_VIEW</message><details>19</details>"));
}

void TuxlerApp::MenuUserGuide()
{
	emit SendNewGuiEvent(QString("<message>CHANGE_VIEW</message><details>21</details>"));
}

void TuxlerApp::MenuSupport()
{
	emit SendNewGuiEvent(QString("<message>CHANGE_VIEW</message><details>17</details>"));
}

void TuxlerApp::NewGuiEvent2(QString event){

    if(__DEBUG__)
		std::cout << event.toStdString();

    QRegExp rx("<message>(.*)</message><details>(.*)</details>");
    rx.setMinimal(true);

        if(rx.indexIn(event) != -1)
		{
            QString msg = rx.cap(1);
            QString det = rx.cap(2);

            bool ok = false;
            int id = 0;

			if (msg == "SHARE_OPINION_CLICKED")
			{
				QString text = det;

				QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

				QString user_uuid = settings.value("RANDOM_USER_ID", "").toString();

				if (user_uuid.isEmpty())
				{
					qDebug() << "FeedbackAppFragment" << "RANDOM_USER_ID==null";
					user_uuid = "";
				}

				QString email = settings.value("email", "").toString();
				
				if (email.isEmpty())
					email = user_uuid;

				QUrl url = QUrl("https://tuxlervpn.com/no_cache_wp_e/rating_windows.php");

				QNetworkAccessManager * mgr = new QNetworkAccessManager(this);

				connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(ReplyFinished(QNetworkReply*)));
				connect(mgr, SIGNAL(finished(QNetworkReply*)), mgr, SLOT(deleteLater()));

				QNetworkRequest request(url);

				request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

				QUrlQuery params;
				params.addQueryItem("sourceapp", "winapp");
				params.addQueryItem("type", "feedback");
				params.addQueryItem("email", email);
				params.addQueryItem("feedback", text);
				params.addQueryItem("user_uuid", user_uuid);
				params.addQueryItem("local_helper_app_id", QString::number(getLocalHelperSessionId()));

				mgr->post(request, params.query().toUtf8());
			}
			else if (msg == "RATING_CANCEL")
			{
				RatingCanceled();
			}
			else if (msg == "RATING_CLICKED")
			{
				int stars = det.toInt();

				if (stars >= STARSMINTOGOTOSTORE)
					emit SendNewGuiEvent(QString("<message>CHANGE_VIEW</message><details>36</details>"));
				else
					emit SendNewGuiEvent(QString("<message>CHANGE_VIEW</message><details>37</details>"));
			}
			else if (msg == "MENU_ITEM")
			{
				if (det == "sharefacebook")
				{
#ifndef IPSHARKK
					QString mY_url = QString::fromStdString(URL_RATING);

					QUrl url = QUrl(mY_url);

					QDesktopServices::openUrl(url);
#endif
				}
				else if (det == "minimize") 
				{
					MenuHide();
				}
				else if(det == "update")
				{
					checkForUpdates();
				}
				else if (det == "support")
				{
					MenuSupport();
				}
				else if (det == "support-click")
				{
#ifndef IPSHARKK
					QString mY_url = QString::fromStdString(URL_SUPPORT);

					QUrl url = QUrl(mY_url);

					QDesktopServices::openUrl(url);
#endif
				}
				else if (det == "reseller-click")
				{
#ifndef IPSHARKK
					QString mY_url = QString::fromStdString(URL_FREE_PREMIUM);

					QUrl url = QUrl(mY_url);

					QDesktopServices::openUrl(url);
#endif
				}
				else if (det == "guide-click")
				{
#ifndef IPSHARKK
					QString mY_url = QString::fromStdString(URL_GUIDE);

					QUrl url = QUrl(mY_url);

					QDesktopServices::openUrl(url);
#endif
				}
				else if (det == "premium")
				{
					MenuUpgrade();
				}
				else if (det == "login")
				{
					MenuLogIn();
				}
				else if (det == "ainfo")
				{
					MenuLogIn();
				}
				else if (det == "about") 
				{
					MenuAbout();
				}
				else if (det == "reseller") 
				{
					MenuReseller();
				}
				else if (det == "guide") 
				{
					MenuUserGuide();
				}
				else if (det == "exit")
				{
					Exit();
				}
			}
			else if (msg == "NEXT_NEARBY")
			{
				if (enabledReloadToNextNearbyLocation)
				{
					NextIP(false, true);
					IncreaseIPChangeCounter();
				}
				else
					ShowToolBarWindow(TuxlerInfoText, "Daily IP change limit reached. Please upgrade to premium.");
			}
			else if (msg == "COUNTRY_CHANGED")
			{
				QStringList tmp = det.split(";");

				QSettings settings(SETTINGS_NAME, SETTINGS_NAME);
				settings.setValue(QString("selected_country"), tmp[0]);
				settings.setValue(QString("selected_country_iso"), tmp[1]);
				settings.setValue(QString("selected_city"), "Any");

				if (enabledReloadToNextNearbyLocation)
				{
					NextIP(false, true);
					IncreaseIPChangeCounter();
				}
				else
				{
					ShowToolBarWindow(TuxlerInfoText, "Daily IP change limit reached. Please upgrade to premium.");
					emit SendNewGuiEvent(QString("<message>SETCOUNTRYANY</message><details></details>"));
					emit SendNewGuiEvent(QString("<message>SETCITYANY</message><details></details>"));
				}
			}
			else if (msg == "CITY_CHANGED")
			{
				QSettings settings(SETTINGS_NAME, SETTINGS_NAME);
				settings.setValue(QString("selected_city"), det);
				
				if (enabledPreferredCitySelection)
				{
					NextIP(false, true);
					IncreaseIPChangeCounter();
				}
				else
				{
					ShowToolBarWindow(TuxlerInfoText, "To select by city please upgrade to premium.");
					emit SendNewGuiEvent(QString("<message>SETCITYANY</message><details></details>"));
				}
			}
			else if (msg == "CONTROLSTATECHANGED") 
			{
					QStringList splitted = det.split(";");

					splitted[0] = splitted[0].mid(QString("CONTROLID:").length());
                    splitted[1] = splitted[1].mid(QString("CONTROLCLASS:").length());
                    splitted[2] = splitted[2].mid(QString("CURRENTSTATE:").length());

                    QString myid = splitted[0]+";"+splitted[1];

                    if(settingsManager.isDefault(myid, true))
					{
                        ShowToolBarWindow(TuxlerInfoText, "To use this option please upgrade to Premium.");
                    }

                    QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

                    settings.beginGroup("gui");

                    settings.setValue(myid, splitted.count() >= 4 ? (splitted[2]+";"+splitted[3]) : splitted[2]);

                    settings.endGroup();

                    settingsManager.LoadSettings();
            }
			else if (msg == "RESIDENTIAL_CHANGED")
			{
				bool was_set = det == "1";

				QSettings settings(SETTINGS_NAME, SETTINGS_NAME);
				settings.setValue(QString("is_residential"), was_set);

				ipList.updateGUIListCache();

				if (enabledReloadToNextNearbyLocation)
					NextIP(false, true);
			}
			else if (msg == "RESIDENTIAL_SET")
			{
				QSettings settings(SETTINGS_NAME, SETTINGS_NAME);
				bool is_residential = settings.value(QString("is_residential"), false).toBool();

				emit SendNewGuiEvent(QString("<message>SETRESIDENTIAL</message><details>"+QString(is_residential ? "1" : "0")+"</details>"));
			}
			else if(msg == "SETEMPASS")
			{
                if(__DEBUG__)
					std::cout << det.toStdString();

                QJsonDocument jsonResponse = QJsonDocument::fromJson(det.toUtf8());

                QJsonObject jsonObject = jsonResponse.object();

                QJsonValue value = jsonObject.value(QString("idx"));

                if(__DEBUG__)
					std::cout << value.toString().toStdString();

                QJsonObject data = value.toObject();

                QString email = data["email"].toString();
                QString password = data["password"].toString();


                /// calculate password SHA1 hash
                class SHA1 sha1;

                std::string tosh = toStdString(password);
                sha1.update(tosh);
                std::string SHA1_ = sha1.final();
                QString passwordsha1 = QString(SHA1_.c_str());

				emit SendNewGuiEvent(QString("<message>SETEXPIRES</message><details>hide</details>"));

                if(email.size() == 0 && password.size() == 0)
				{
                    passwordsha1.clear();
                    __isPremiumset(false);

                    QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

                    settings.setValue("email", email);
                    settings.setValue("password", passwordsha1);

                    if(__DEBUG__)std::cout << "NewEmail:" << email.toStdString();
					Lock();
					this->password_global = passwordsha1;
					this->email_global = (email);
					UnLock();

					LogIn();

                }else
                    TryLogin(email, passwordsha1);
            }
			else if(msg == "IPLISTVISIBILITY")
			{
                bool vis = det == "1" ? true : false;

                if(!ipList.__ipListLoaded && vis){

                    ShowToolBarWindow(TuxlerInfoText, "Please wait while loading...");

					emit SendNewGuiEvent(QString("<message>DEACTIVATEIPLIST</message><details></details>"));
					emit SendNewGuiEvent(QString("<message>IPLISTVISIBLE</message><details>0</details>"));

                    return;
                }

                __isIpChangingActive(&vis);

                bool isset = currentIP.localid != -1;

				if (myIP.localid != -1) 
				{
					SetMyIp(myIP);
				}
				if (__isIpChangingActive())
				{
					QSize ss = size();
					ss.setHeight(450);
					ss.setWidth(400);

					resize(ss);
				}
            }
			else if(msg == "CLICKED" && (id = det.toInt(&ok)) && ok && __isIpChangingActive())
			{
                //TryGetIp(id);
            }
			else if(msg == "LOADED")
			{
                __guiloaded = true;

                for(QList<QString>::iterator it = __delayedMsgs.begin(); it != __delayedMsgs.end(); it++) emit SendNewGuiEvent((*it));

                __delayedMsgs.clear();

                settingsManager.LoadSettings();

				emit SendNewGuiEvent(QString("<message>B_VERSION</message><details>" + QString(VER_FILEVERSION_STR) + "</details>"));
				emit SendNewGuiEvent(QString("<message>B_DATE</message><details>" + QString(__DATE__) + "</details>"));
            }
			else if (msg == "OPENFREE_PREMIUM")
			{
#ifndef IPSHARKK
				QString mY_url = QString::fromStdString(URL_FREE_PREMIUM);

				QUrl url = QUrl(mY_url);

				bool isURLopened = QDesktopServices::openUrl(url);

				if (__DEBUG__)
					std::cout << "goto free premium website:" << isURLopened;
#endif
			}
			else if(msg == "OPENPREMIUM")
			{
                QString mY_url = QString::fromStdString(URL_PREMIUM);

                QUrl url = QUrl(mY_url);

                bool isURLopened = QDesktopServices::openUrl ( url );

                if(__DEBUG__)
					std::cout << "goto premium website:" << isURLopened;
            }
        }
}

bool TuxlerApp::__isIpChangingActive(bool *set){

    bool before = __isIpChangingActiveV;

	if(set != NULL)
		__isIpChangingActiveV = *set;

    if(__isIpChangingActiveV && before != __isIpChangingActiveV)
		systemProxy.SetProxy();

    else if(__isIpChangingActiveV != before && !__isIpChangingActiveV)
            systemProxy.RestoreProxy();

    emit SendNewGuiEvent(QString("<message>IPLISTVISIBLE</message><details>") + (__isIpChangingActiveV ? "1" : "0") + QString("</details>"));
   
    return __isIpChangingActiveV;
}


void TuxlerApp::mainFrame_javaScriptWindowObjectCleared(){

    QFile f(":/gui/MessageReceiver.js");

    f.open(QFile::ReadOnly);

    QString js = f.readAll();

	f.close();

    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("ehbridge", &bridge);

    ui->webView->page()->mainFrame()->evaluateJavaScript(js);
}
