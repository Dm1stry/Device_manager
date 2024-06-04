#ifndef HORIZONTAL_TAB_BAR_HPP
#define HORIZONTAL_TAB_BAR_HPP

#include <QTabBar>
#include <QStylePainter>
#include <QStyleOptionTabV3>
#include <QPainter>
#include <QIcon>
#include <QString>

class HorizontalTabBar : public QTabBar
{
Q_OBJECT
public:
    explicit HorizontalTabBar(QWidget* parent = nullptr);

protected:
    QSize tabSizeHint(int) const;
    void paintEvent(QPaintEvent *);

};

#endif