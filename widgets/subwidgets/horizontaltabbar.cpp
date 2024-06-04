#include "horizontaltabbar.hpp"

HorizontalTabBar::HorizontalTabBar(QWidget* parent)
  : QTabBar(parent)
{
    setIconSize(QSize(18, 18));
}

QSize HorizontalTabBar::tabSizeHint(int) const
{
    return QSize(150, 30);
}

void HorizontalTabBar::paintEvent(QPaintEvent *)
{
    QStylePainter painter(this);
    for (int index = 0; index < count(); index++)
    {
        QStyleOptionTab tab;
        initStyleOption(&tab, index);
        QIcon tempIcon = tab.icon;
        QString tempText = tab.text;
        tab.icon = QIcon();
        tab.text = QString();
        painter.drawControl(QStyle::CE_TabBarTab, tab);
        QPainter painter;
        painter.begin(this);
        QRect tabrect = tabRect(index);
        tabrect.adjust(0, 8, 0, -8);
        painter.drawText(tabrect, Qt::AlignBottom | Qt::AlignHCenter, tempText);
        tempIcon.paint(&painter, 0, tabrect.top(), tab.iconSize.width(), tab.iconSize.height(), Qt::AlignTop | Qt::AlignHCenter);
        painter.end();
    }
}

