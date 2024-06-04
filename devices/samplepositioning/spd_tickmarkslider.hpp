#ifndef SPD_TICKMARKSLIDER_HPP
#define SPD_TICKMARKSLIDER_HPP

#include <QSlider>
/*
*  Реимплеметация отрисовки засечек и их соответствующего символ-значения. 
*/

class spd_tickmarkslider : public QSlider
{
   Q_OBJECT

public:
     explicit spd_tickmarkslider(QWidget *parent) : QSlider(parent) {};
    ~spd_tickmarkslider() {};

private:
   void paintEvent(QPaintEvent *e);

private:
   int m_firstWidth = 0;
};

#endif // SPD_TICKMARKSLIDER_HPP
