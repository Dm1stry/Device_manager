#ifndef COORDINATES_H
#define COORDINATES_H

/*
    Пространство имен для координат и размеров элементов в редакторе последовательности
*/

namespace Coordinates
{
    const int LEFT_OFFSET = 10;   // Отступ слева
    const int RIGTH_OFFSET = 5;   // Отступ справа
    const int UP_OFFSET = 100;     // Отступ сверху
    const int DOWN_OFFSET = 5;    // Отступ снизу

    const int HEIGHT_AXES = 120;            // Высота оси таймлайна
    const int MINIMAL_WEIGHT_AXES = 2500;   // Минимальная длина оси времени таймлайна
    const int TEXT_X_AXES = 10;             // Положение названия устройства на таймлайне (х)
    const int TEXT_Y_AXES = 10;              // Положение названия устройства на таймлайне (у)
    const int TEXT_FONT_SIZE_AXES = 14;     // Размер шрифта

    const int HEIGHT_ONE_LINE = HEIGHT_AXES + 20;        // Высота одной линии (сколько отводится на одно устройство)
    const int MINIMAL_WEIGHT_EVENT = 115;   // Минимальная ширина ивента
    const int OFFSET_BETWEEN = 5;           // Расстояние между шапкой ивента и таймлайном

    const int HEIGHT_HEADER_INTERVAL = 25;      // Высота шапки интервала
    const int Y_WIDGET_HEADER_INTERVAL = 1;     // Положение (у) виджетов в шапке интервала
    const int X_WIDGET_HEADER_INTERVAL = 1;      // Положение (х) поля ввода в шапке интервала
    //const int X_BUTTON_HEADER_INTERVAL = MINIMAL_WEIGHT_EVENT - 20;   // Положение (х) кнопки в шапке интервала
    const int TEXT_FONT_SIZE_INTERVAL = 12;     // Размер шрифта в шапке интервала

    const int HEIGHT_GROUPCOMMAND = HEIGHT_AXES - 10;                   // Высота блока с командами
    const int MINIMAL_WEIGHT_GROUPCOMMAND = MINIMAL_WEIGHT_EVENT - 2;   // Минимальная ширина блока команд

    const QColor COLOR_GRAY = QColor(230, 230, 230);// Цвет фона
};

#endif