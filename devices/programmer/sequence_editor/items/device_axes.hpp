#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>
#include <QtWidgets>
#include "../coordinates.hpp"
using namespace Coordinates;

/*
    Класс временных осей для каждого устройства в редакторе последовательности
*/

class Axes : public QObject, public QGraphicsItem 
{
    Q_OBJECT 
    Q_INTERFACES(QGraphicsItem)
public: 
    explicit Axes(QString name, quint8 address, int position, QObject* parent = nullptr);
    ~Axes();

    quint8 getAddress();
    int getPosition(); 
    void setPosition(int position);

private:
    QString name_;
    quint8 address_;
    int position_;

    int x_ = LEFT_OFFSET, y_ = UP_OFFSET;
    int length_ = MINIMAL_WEIGHT_AXES;

    int total_interval_length = 0;
    int interval_numbers_ = 0;

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* ppainter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    //Q_SIGNAL void clicked();

public slots:

};
#endif