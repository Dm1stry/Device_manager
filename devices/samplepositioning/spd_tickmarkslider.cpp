#include "spd_tickmarkslider.hpp"
#include <QPainter>
#include <QStyleOptionSlider>
#include <QStyle>
#include <QDebug>
#include <QStylePainter>
#include <cmath>


void spd_tickmarkslider::paintEvent(QPaintEvent *e)
{
    if (tickPosition() == NoTicks)
    {
        QSlider::paintEvent(e);
        return;
    }

    QStylePainter p(this);
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    // draw the slider (this is basically copy/pasted from QSlider::paintEvent)
    opt.subControls = QStyle::SC_SliderTickmarks;
    p.drawComplexControl(QStyle::CC_Slider, opt);

    opt.subControls = QStyle::SC_SliderGroove;
    p.drawComplexControl(QStyle::CC_Slider, opt);

    // draw the slider handle
    opt.subControls = QStyle::SC_SliderHandle;
    p.drawComplexControl(QStyle::CC_Slider, opt);

    QRect rr;
    p.drawText(rect(), Qt::TextDontPrint, QString::number(9999), &rr);

    double scale = (double)(this->width() - 50) / this->maximum(); // scale factor for drawing ticks and marks
    
    for (int v = this->minimum(); v <= this->maximum(); v += tickInterval()) {
        //ticks
        int x = v * scale + 25;
        int h = 7;
        p.setPen(QColor("#a5a294"));
        if (tickPosition() == TicksBothSides || tickPosition() == TicksAbove)
        {
            int y = this->rect().top();
            p.drawLine(x, y, x, y + h);
            for(int i = 0; i < 10 && v != this->maximum(); i++)
                p.drawLine(x + i * scale, y, x + i * scale, y + h - 4);
        }
        if (tickPosition() == TicksBothSides || tickPosition() == TicksBelow)
        {
            int y = this->rect().bottom();
            p.drawLine(x, y, x, y - h);
            for(int i = 0; i < 9; i++)
                p.drawLine(x, y, x, y - h + 2);
        }
        //marks
        QStyleOptionSlider slider;
        slider.init(this);
        slider.orientation = orientation();
        QString vs = QString("%L1").arg(v);
        QPoint pos(v * scale + 15, rect().bottom());
        QRect r;
        rr.setX(pos.x());
        rr.setY(pos.y());
        p.drawText(rr, Qt::TextDontPrint, vs, &r);
        p.drawText(pos, vs);
    }
}
