#ifndef SAMPLE_POSITIONING_DEVICE_WIDGET_HPP
#define SAMPLE_POSITIONING_DEVICE_WIDGET_HPP

#include "devices/base/basedevicewidget.hpp"
#include "ui_samplepositioningdevicewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SPDeviceWidget; }
QT_END_NAMESPACE

/*
*   Виджет устройства позиционирования.
*   Реализовано:
*   - Выбор максимального расстояния для перемещения относительно позиции HOME от 10 до 200 [см];
*   - Возможность перемещения на выбранную позицию в заданом диапазоне в [см];
*   - Выбор шага перемещения в [см] или [мм] в сторону позиции HOME или WORK кнопками < и >;
*   - Повторение выбранного шага перемещения кнопками << и >>;
*   - Отслеживание текущей позиции устройства, путем его опроса каждые 500 мс
*     (есть возможнось изменить значение периода опроса);
*/

class SPDeviceWidget : public BaseDeviceWidget
{
Q_OBJECT
public:
    SPDeviceWidget(QWidget * parent = nullptr, int step = 32, int nInterval = 500, QByteArray adr = QByteArray(1, 0x2A));

    ~SPDeviceWidget();
    // ---------------------------------------------------
    // Реализация метода, обрабатывающего пришедшие данные
    void processData(QByteArray data);
    // -------------------------------


    // -------------------------------------------------------------------------------------------------------------
    // BaseSavable методы, позволяющие получить данные для сохранения класса и 
    // восстановить состояние класса из сохраненных данных, 
    // необходимо для функционирования DeviceLoader
    
    // Возвращает данные о состоянии в виде вектора состояния
    json getStateToSave();
    // Восстанавливает состояние класса из вектора состояния
    bool restoreState(json state);
    // ------------------------------------------
    
	bool eventFilter(QObject * watched, QEvent *event);
	void setStatus(QString status);

protected:
    virtual void timerEvent(QTimerEvent*);


private slots:
    void set_req_args(int direction, int permission, int ss, int steps);
    void on_stepRight_clicked();
    void on_stepLeft_clicked();
    void on_farRight_toggled(bool checked);
    void on_farLeft_toggled(bool checked);
    void on_stop_toggled(bool checked);
    void on_nsteps_spinBox_editingFinished();
    void on_comboBox_currentIndexChanged(int index);
    void on_zone_spinBox_editingFinished();

    void on_velocity_spinBox_valueChanged(int arg1);
    void on_home_PushButton_clicked();
    void on_work_PushButton_clicked();

private:
    int step_;                   // шаг [мкм]
    int nsteps_;                 // [кол-во шагов]
    float pos_;                  // позиция отображения [см]
    int npos_;                   // [кол-во шагов от позиции HOME]
    int velocity_;               // режим скорости
    int munit_;                  // коэфициент перевода е. и.
    QVector<int> anw_args_;      // аргументы ответа [DONE, ERR, WORK, HOME, STEPS]
    QVector<double> req_args_;   // аргументы запроса [CW/CCW, MANUAL/ABUS, STOP/START, VELOCITY, STEPS]

    enum args {
                CW = 0,         // движение к позиции HOME
                CCW = 1,        // движение к позиции WORK
                MANUAL = 0,
                ABUS = 1,
                STOP = 0,
                START = 1
              };

    const int vn[4] = {0xD, 0xB, 0x7, 0x0};

    QByteArray adr_;             // адрес устройства
    int nInterval_;              // [мс] интервал отправки запроса
    Ui::SPDeviceWidget *ui;
};

#endif
