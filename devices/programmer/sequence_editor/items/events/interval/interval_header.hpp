#ifndef HEADER_INTERVAL_HPP
#define HEADER_INTERVAL_HPP

#include <QWidget>
#include <QtWidgets>
#include "../../../coordinates.hpp"
using namespace Coordinates;

/*
Класс виджета, отображаемого в программаторе, для управления синхронным устройством. 
*/
class IntervalHeader : public QFrame
{
Q_OBJECT
public:
    IntervalHeader(QFrame* parent = nullptr);
    ~IntervalHeader();

    void layoutSetup();         // Создание внешнего вида
    void connectionSetup();     // Настройка connect-ов

    void setWidth(int width);

private:
    QLineEdit* label_;                      // Виджет вывода t=
    QLineEdit* lineEdit_;                   // Виджет ввода числа
    QPushButton* menuButton_;               // Виджет кнопки закрытия

    bool eventFilter(QObject* object, QEvent* event);

public slots:

private slots:
    void setTimeInterval();
    void closeButtonClicked();
    void showMenu();
    void addLeftIntervalClicked();
    void addRightIntervalClicked();

signals:
    Q_SIGNAL void setTimeIntervalSignal(unsigned long time);    // Сигнал установки интервала времени
    Q_SIGNAL void closeButtonClickedSignal();                   // Сигнал удаления интервала
    Q_SIGNAL void addLeftIntervalClickedSignal();               // Сигнал удаления интервала
    Q_SIGNAL void addRightIntervalClickedSignal();               // Сигнал удаления интервала

protected:

};

#endif