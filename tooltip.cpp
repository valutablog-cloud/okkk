#include "tooltip.h"

#ifndef IPSHARKK
#include "ui_tooltip.h"
#else
#include "ui_tooltipIPSHARKK.h"
#endif

#include <QPainter>
#include <QPixmap>
#include <QBitmap>
#include <QFontMetrics>
#include <QDesktopWidget>

std::string wordWrap( std::string str, size_t width = 55 ) {
    size_t curWidth = width;
    while( curWidth < str.length() ) {
        std::string::size_type spacePos = str.rfind( ' ', curWidth );
        if( spacePos == std::string::npos )
            spacePos = str.find( ' ', curWidth );
        if( spacePos != std::string::npos ) {
            str[ spacePos ] = '\n';
            curWidth = spacePos + width + 1;
        }
    }

   return str;
}

ToolTip::ToolTip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolTip),
    icon(":/images/icon_32x32.png"),
    img(1000, 1000, QImage::Format_RGB32),
    stopper(this)
{
        ui->setupUi(this);

        setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);

         QPalette* palette = new QPalette();
         QLinearGradient linearGradient(QPointF(50, 50), QPointF(200, 200));
         linearGradient.setColorAt(0, QColor::fromRgb(225, 230, 228));
         linearGradient.setColorAt(1, QColor::fromRgb(245, 247, 246));
         palette->setBrush(QPalette::Window,*(new QBrush(linearGradient)));

         setPalette(*palette);

         //icon text

         ui->icon->setPixmap(QPixmap::fromImage(icon));
         ui->icon->resize(icon.size());

         connect(&stopper, SIGNAL(timeout()), this, SLOT(animate()));

}

void ToolTip::animate(){

   int step = 9;
   int cx = pos().x();
   int tx = stop.x();
   int sx = start.x();

       if(!reverse && cx > tx){

           move(pos().x()-step, pos().y());

       }else if(!reverse && pos().x() <= stop.x()) {

           reverse = true;
           timeshow = time(NULL);

       }else if(reverse && time(NULL) - timeshow > timevis/1000){

           if(cx < sx) move(pos().x()+step, pos().y());

           else {

               hide();
               stopper.stop();
               return;
           }
       }
}

void ToolTip::showToolTip(QString title, QString text, int speed, int timevisible){

    SetText(title, text);

    timevis = timevisible;

    QDesktopWidget screen;
    QRect rct = screen.availableGeometry();
    QRect rct2 = screen.screenGeometry();

    start = QPoint(rct.width()+10, rct2.height()-rct.height());
    stop = QPoint(rct.width()-10-width(), start.y());

    timeshow = 0;
    reverse = false;

    move(start);
    show();

    stopper.setInterval(speed);
    stopper.setSingleShot(false);
    stopper.start();
}

void ToolTip::SetText(QString &title, QString &text){

    ui->title->setText(title);
    ui->title->adjustSize();
    ui->text->setText(text);
    ui->text->adjustSize();

    QFontMetrics metrics(ui->text->fontMetrics());

    QRect rc1 = metrics.boundingRect(ui->text->text());

    int ph = (5+rc1.height())*(ui->text->text().count(QLatin1Char('\n')) == 0 ? 1 : ui->text->text().count(QLatin1Char('\n')));

    QFontMetrics metricst(ui->title->fontMetrics());

    QRect rc2 =  metricst.boundingRect(ui->title->text());

    int pht = (5+rc2.height())*(ui->title->text().count(QLatin1Char('\n')));

    ph = ui->text->height();
    pht = ui->title->height();

    int nh = ph+pht;

    int mm = 20;

    if(minimumHeight() - nh < mm) nh += mm;

    int nw = 0;

    if(nw <= ui->text->width()+ui->text->pos().x()+20) nw = ui->text->width()+ui->text->pos().x() + 20;
    if(nw <= ui->title->width()+ui->title->pos().x()+20) nw = ui->title->width()+ui->title->pos().x() + 20;

    resize(QSize(nw, nh));

    ui->icon->move(ui->icon->pos().x(), height()/2-ui->icon->height()/2);
    ui->text->move(ui->text->pos().x(), (height()/2-ph/2)+(pht/2));
    ui->title->move(ui->title->pos().x(), (height()/2-pht/2)-(ph/2));
}

ToolTip::~ToolTip()
{
    delete ui;
}

void ToolTip::resizeEvent(QResizeEvent* event)
{
    QDialog::resizeEvent(event);

    QPixmap pixmap(size());
    QPainter painter1(&pixmap);
    painter1.fillRect(pixmap.rect(), Qt::white);
    painter1.setBrush(Qt::black);

    painter1.drawRoundedRect(pixmap.rect(), 15, 15);
    setMask(pixmap.createMaskFromColor(Qt::white));
}
