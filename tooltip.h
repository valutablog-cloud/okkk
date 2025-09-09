#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <QDialog>
#include <QImage>
#include <QLabel>
#include <QPoint>
#include <QTimer>
#include <time.h>

namespace Ui {
class ToolTip;
}

/** @addtogroup display_functions */
/*@{*/
/**
*@brief display animated tooltip window
*/
class ToolTip : public QDialog
{
    Q_OBJECT

public:
    explicit ToolTip(QWidget *parent = 0);
    ~ToolTip();

    /**
    *@brief show tooltip and animate
    *@param speed speed of window animation (miliseconds)
    *@param timevisible time in seconds the tooltip window should be visible
    */
    void showToolTip(QString title, QString text, int speed, int timevisible);

private:
    QPoint start, stop;
    QTimer stopper;
    time_t timeshow;
    int timevis;
    bool reverse;

private slots:
    void animate();

private:
    void SetText(QString &title, QString &text);

    void resizeEvent(QResizeEvent* event);
    Ui::ToolTip *ui;
    QImage icon;
    QImage img;
};
/*@}*/
#endif // TOOLTIP_H
