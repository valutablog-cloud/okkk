#include "mainwindow.h"
#include "tuxlerapp.h"

#include <iostream>
#include <fstream>
#include <QCloseEvent>
#include <QEvent>
#include <QMouseEvent>
#include <QUuid>

//#define HIDE_BUTTON_MENU
#define DISABLE_MENU_TEXT

TuxlerApp * MainWindow::__instance = NULL;

#ifdef Q_OS_WIN32
extern "C"
{
    typedef HRESULT (WINAPI *t_DwmIsCompositionEnabled)(BOOL *pfEnabled);
}

bool DwmIsCompositionEnabled() {
    HMODULE shell;

    shell = LoadLibrary(L"dwmapi.dll");
    if (shell) {
        BOOL enabled;
        t_DwmIsCompositionEnabled is_composition_enabled = \
              reinterpret_cast<t_DwmIsCompositionEnabled>(
                  GetProcAddress (shell, "DwmIsCompositionEnabled")
                  );
        is_composition_enabled(&enabled);

        FreeLibrary (shell);

        if ( enabled ) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}
#endif

MainWindow::MainWindow() :
    __isResize(false),
    __maximized(false),
    __lastPos(-1, -1),
    __lastPosMove(-1, -1),
    ignoreShow(false),
    __isMove(false),
    QMainWindow(NULL),
    __isHover(false),
    resizeimg(":/gui/resize.png"),
    ui(new Ui::MainWindow),
    toolbar(":/gui/titlebarbig.png"),
    buttons(":/gui/buttons.png"),
    buttonsb(":/gui/titlebarbig.png"),
    buttonshover(":/gui/buttonshover.png"),
    minimize(":/gui/minimize.png"),
    minimizec(":/gui/minimizec.png"),
    minimizeh(":/gui/minimizeh.png"),
    maximize(":/gui/maximize.png"),
    maximizec(":/gui/maximizec.png"),
    maximizeh(":/gui/maximizeh.png"),
    closeIMG(":/gui/button.png"),
    closec(":/gui/button-clicked.png"),
    closeh(":/gui/button-hover.png"),
    buttonmenu(":/gui/button-menu.png"),
    buttonmenuhover(":/gui/button-menu-hover.png"),
#ifndef DISABLE_MENU_TEXT
    buttonmenutext(":/gui/tuxler.png"),
#endif
    bck(":/images/backgroundmask.png"),
    lefttool(":/gui/lefttool.png"),
    righttool(":/gui/righttool.png"),
    middletool(":/gui/middletool.png"),
    restoreOnShow(false)
	{

	QSettings settings(SETTINGS_NAME, SETTINGS_NAME);
	settings.setValue("STARTUP_COUNTER", settings.value("STARTUP_COUNTER", 0).toInt()+1);

	QString current_id = settings.value("RANDOM_USER_ID", "").toString();

	if (current_id.isEmpty())
	{
		QString rand = QUuid::createUuid().toString();
		settings.setValue("RANDOM_USER_ID", rand);
	}

    toolbar = middletool;
    buttonsb = righttool;


    ui->setupUi(this);

    ui->lefttool->resize(lefttool.size());
    ui->lefttool->setPixmap(QPixmap::fromImage(lefttool));
    ui->lefttool->lower();
    ui->labelbuttons->lower();
    ui->label->lower();
    ui->close->raise();
    ui->labelbuttons->resize(buttons.size());
    ui->close->resize(closeIMG.size());
    ui->maximize->resize(maximize.size());
    ui->minimize->resize(minimize.size());
    ui->close->installEventFilter(this);
    ui->maximize->installEventFilter(this);
    ui->minimize->installEventFilter(this);
    ui->close->setPixmap(QPixmap::fromImage(closeIMG));
    ui->maximize->setPixmap(QPixmap::fromImage(maximize));
    ui->minimize->setPixmap(QPixmap::fromImage(minimize));

#ifdef IPSHARKK
    this->setWindowTitle("IPSharkk");
#endif


    ui->label->resize(ui->label->width(), toolbar.height());
    ui->labelbuttons->resize(righttool.width(), toolbar.height());



    bool closevisible = true;
    bool minimizevisible = false;
    bool maximizevisible = false;

#ifdef Q_OS_MAC
    onleft = false;
#else
    onleft = false;
#endif

    margin = 10;
    marginright = 10;
    spacing = 10;

    ui->menubutton->resize(buttonmenu.size());
    ui->menubutton->setPixmap(QPixmap::fromImage(buttonmenu));

    ui->menutext->resize(buttonmenutext.size());
    ui->menutext->setPixmap(QPixmap::fromImage(buttonmenutext));

    int marginmenu = 20;

#ifndef DISABLE_MENU_TEXT
	int spacingmenu = 15;
#else
	int spacingmenu = 25;
#endif

#ifndef DISABLE_MENU_TEXT
    ui->menutext->move(marginmenu, ui->menubutton->height()/2-ui->menutext->height()/2);
#endif

    ui->menubutton->move(

#ifndef DISABLE_MENU_TEXT
		marginmenu+ui->menutext->width()+
#endif

		spacingmenu, 0);

    if(!minimizevisible) ui->minimize->hide();
    else __buttons.append(ui->minimize);
    if(!maximizevisible) ui->maximize->hide();
    else __buttons.append(ui->maximize);
    if(!closevisible) ui->close->hide();
    else __buttons.append(ui->close);

#ifdef Q_OS_MAC
    __buttons.clear();

    if(!closevisible) ui->close->hide();
    else __buttons.append(ui->close);
    if(!minimizevisible) ui->minimize->hide();
    else __buttons.append(ui->minimize);
    if(!maximizevisible) ui->maximize->hide();
    else __buttons.append(ui->maximize);
#endif

    setWindowFlags(Qt::FramelessWindowHint);

    QFile f(
#ifndef IPSHARKK
                ":/gui/index.html"
#else
                ":/gui/gui.html"
#endif
                );

    f.open(QFile::ReadOnly);

    QString html = f.readAll();
    f.close();

    ui->webView->setContextMenuPolicy( Qt::PreventContextMenu );
    ui->webView->page()->mainFrame()->setHtml(html);
    myCursor.setShape(Qt::ArrowCursor);
    ui->webView->setCursor(myCursor);

#ifdef Q_OS_WIN32
    if(DwmIsCompositionEnabled())
#endif
		this->setAttribute(Qt::WA_TranslucentBackground ,true );

    this->setAttribute(Qt::WA_QuitOnClose ,true );

    ui->resize->setPixmap(QPixmap::fromImage(resizeimg));
    ui->resize->resize(resizeimg.size());
    ui->resize->setCursor(Qt::SizeFDiagCursor);
    ui->resize->installEventFilter(this);
    ui->resize->raise();
    ui->menubutton->installEventFilter(this);

#ifndef DISABLE_MENU_TEXT
    ui->menutext->installEventFilter(this);
#endif

    ui->label->installEventFilter(this);
    ui->labelbuttons->installEventFilter(this);

    QPoint pos = settings.value("pos", QPoint(-1, -1)).toPoint();
    //QSize size = settings.value("size", QSize(-1, -1)).toSize();

    //if(size.width() > 0) resize(size);
    if(pos.x() >= 0)move(pos);

	ui->resize->hide();

#ifdef HIDE_BUTTON_MENU
	ui->menubutton->hide();
	ui->menutext->hide();
#endif

#ifdef HIDE_MENU_TEXT
ui->menutext->hide();
#endif
}

void MainWindow::ResetButtonHover(QAction *action){

    ui->menubutton->setPixmap(QPixmap::fromImage(buttonmenu));
}

void MainWindow::showEvent(QShowEvent *event){

    if(!ignoreShow) __instance->__suspressNotifications = false;

    if(restoreOnShow){

        restoreOnShow = false;

        move(oldPos);
    }
}

void MainWindow::closeEvent(QCloseEvent* event){

#ifndef Q_OS_LINUX
    __instance->sys->hide();
    __instance->sys->deleteLater();
#endif

    __instance->systemProxy.RestoreProxy();

    saveWindowSizePos();

    if(event != NULL) 
		event->accept();
}

void MainWindow::saveWindowSizePos(){

    QSettings settings(SETTINGS_NAME, SETTINGS_NAME);
    settings.setValue("pos", pos());
    //settings.setValue("size", size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectionChanged(){

    ui->webView->findText("");
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);

   QPixmap pixmap(size());
   QPainter painter1(&pixmap);
   painter1.fillRect(pixmap.rect(), Qt::white);
   painter1.setBrush(Qt::black);

#ifdef Q_OS_UNIX
   int rad = 23;
#else
   int rad = 21;
#endif

   painter1.setRenderHint(QPainter::HighQualityAntialiasing);
   painter1.drawRoundedRect(pixmap.rect(), rad, rad);
   setMask(pixmap.createMaskFromColor(Qt::white));

   ui->webView->resize(ui->centralWidget->width(), ui->centralWidget->height()-ui->label->height());
   ui->webView->move(ui->webView->pos().x(), ui->label->height());

   ui->lefttool->move(0, 0);
   ui->label->resize(ui->centralWidget->width() - ui->labelbuttons->width() - lefttool.width(), ui->label->height());
   ui->label->move(onleft ? ui->labelbuttons->width() : lefttool.width(), ui->label->pos().y());

   ui->labelbuttons->move(onleft ? 0 : ui->centralWidget->width()-ui->labelbuttons->width(), ui->labelbuttons->pos().y());

   ui->resize->move(ui->centralWidget->width()-ui->resize->width()-8, ui->centralWidget->height()-ui->resize->height()-8);

   UpdateButtons();
   UpdateNavBox();
}

void MainWindow::UpdateButtons(){

    QSize size(ui->centralWidget->width(), ui->label->height());

    bar = toolbar.copy();

    bar = bar.scaled(size);

    ui->label->setPixmap(QPixmap::fromImage(bar));
    ui->labelbuttons->setPixmap(QPixmap::fromImage(buttonsb));
}

void MainWindow::UpdateNavBox(){

    bool first = true;

    __regionsx.clear();

    for(QList<QLabel*>::iterator it = __buttons.begin(); it != __buttons.end(); it++){

            QLabel &label = *(*it);

            int rx;

            label.move((rx = (first ?

                                  (ui->labelbuttons->pos().x()+ (onleft ? margin : (marginright*-1))) :
                                  ((*(*(it-1))).pos().x()+(*(*(it-1))).width()+spacing))),

                       ui->labelbuttons->height()/2-label.height()/2);

            __regionsx.append(rx);

            first = false;
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
	bool pressed = false;

	QLabel * lb = dynamic_cast<QLabel*>(object);

	if (lb == ui->menubutton && event->type() == QEvent::MouseButtonRelease)
	{
		ResetButtonHover(NULL);
		__instance->myMenu->popup(static_cast<QMouseEvent*>(event)->globalPos());
	}


	if (lb == ui->minimize || lb == ui->maximize || lb == ui->close 
		
#ifndef HIDE_BUTTON_MENU
		|| lb == ui->menubutton
		
#ifndef DISABLE_MENU_TEXT
		|| lb == ui->menutext
#endif

#endif
		) {

		if ((pressed = (event->type() == QEvent::MouseButtonRelease)) || ((event->type() == QEvent::Enter)))
			lb->setPixmap(QPixmap::fromImage(lb == ui->minimize ? minimizeh : (lb == ui->maximize ? maximizeh : (lb == ui->close ? closeh : (lb == ui->menubutton ? buttonmenuhover : buttonmenutext)))));
		else if (event->type() == QEvent::MouseButtonPress)
			lb->setPixmap(QPixmap::fromImage(lb == ui->minimize ? minimizec : (lb == ui->maximize ? maximizec : (lb == ui->close ? closec : (lb == ui->menubutton ? buttonmenu : buttonmenutext)))));
		else if (event->type() == QEvent::Leave)
			lb->setPixmap(QPixmap::fromImage(lb == ui->minimize ? minimize : (lb == ui->maximize ? maximize : (lb == ui->close ? closeIMG : (lb == ui->menubutton ? buttonmenu : buttonmenutext)))));
	}

	if (object == ui->label)
	{
		bool released = false;

		if (event->type() == QEvent::MouseButtonPress)
		{
			__lastPosMove = this->pos();
			__lastPosMoveMouse = static_cast<QMouseEvent*>(event)->globalPos();
			__isMove = true;
		}
		else if (((released = (event->type() == QEvent::MouseButtonRelease))) || event->type() == QEvent::MouseMove)
		{
			move(__lastPosMove.x() - __lastPosMoveMouse.x() + static_cast<QMouseEvent*>(event)->globalPos().x(),
				__lastPosMove.y() - __lastPosMoveMouse.y() + static_cast<QMouseEvent*>(event)->globalPos().y());

			if (released)
				__isMove = false;
		}
	}
	else if (object == ui->resize)
	{
		bool released = false;

		if (event->type() == QEvent::MouseButtonPress)
		{
			__lastPos = static_cast<QMouseEvent*>(event)->pos();
			__isResize = true;
		}
		else if (((released = (event->type() == QEvent::MouseButtonRelease))) || event->type() == QEvent::MouseMove)
		{
			resize(width() + (static_cast<QMouseEvent*>(event)->pos().x() - __lastPos.x()), height() + (static_cast<QMouseEvent*>(event)->pos().y() - __lastPos.y()));

			if (released)
				__isResize = false;
		}
	}
	else if (object == ui->labelbuttons && ((__isHover = (event->type() == QEvent::Enter)) || event->type() == QEvent::Leave))
		UpdateButtons();

	int idxin;

	if (pressed && (idxin = __buttons.indexOf(lb)) != -1)
	{
		QRegion region(__regionsx[idxin], lb->pos().y(), lb->width(), lb->height());

		QPoint point = static_cast<QMouseEvent*>(event)->pos();

		point.setX(__regionsx[idxin] + point.x());

		if (region.contains(point))
		{
			if (lb == ui->close)
			{
#ifndef IPSHARKK
				QString body = "\nTuxler VPN will keep running in the system tray.\n\nTo terminate the program, choose \"Exit\"\nin the context menu of the system tray entry.";
#else
				QString body = "\nIPSharkk will keep running in the system tray.\n\nTo terminate the program, choose \"Exit\"\nin the context menu of the system tray entry.";
#endif

				QSettings settings(SETTINGS_NAME, SETTINGS_NAME);

				bool show = settings.value("ShowTrayInfo", true).toBool();

				settings.setValue("ShowTrayInfo", false);

#ifdef Q_OS_LINUX
				MainWindow::__instance->Exit();
				return false;
#else
				if (show)
					__instance->ShowToolBarWindow(__instance->TuxlerInfoText, body, 7000);

				hide();
#endif
			}
			else if (ui->minimize == lb)
			{

#ifdef Q_OS_MAC
				hide();
#else
				showMinimized();
#endif
			}
			else if (ui->maximize == lb)
			{
				if (__maximized)
				{
					AnimateTo(SizeBeforeMax);

					__maximized = false;
				}
				else
				{
					__maximized = true;

					SizeBeforeMax = size();

					QSize stmp = maximumSize();

					AnimateTo(stmp);
				}
			}
	}
}

	return false;
}

void MainWindow::AnimateTo(QSize &size){

    resize(size);
    return;
}

void MainWindow::Restore(){

    ui->maximize->setPixmap(QPixmap::fromImage(maximize));
    ui->minimize->setPixmap(QPixmap::fromImage(minimize));
    ui->close->setPixmap(QPixmap::fromImage(closeIMG));

    show();
}

bool MainWindow::event(QEvent *event)
{
    if (event->type() == (QEvent::Type) IDB_CHECK_FOR_UPDATES_ID)
    {
#ifdef Q_OS_WIN32
#ifndef NO_WINSPARKLE
        win_sparkle_check_update_with_ui();
#endif
#endif
        return true;
    }

    return QMainWindow::event(event);
}

