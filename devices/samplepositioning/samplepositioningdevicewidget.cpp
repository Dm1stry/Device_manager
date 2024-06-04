#include "samplepositioningdevicewidget.hpp"
#include "ui_samplepositioningdevicewidget.h"
#include <QDebug>
#include <QEvent>
#include <QTime>
#include <cmath>
#include <QMessageBox>


SPDeviceWidget::SPDeviceWidget(QWidget *parent, int step, int nInterval, QByteArray adr)
    : BaseDeviceWidget("Уст-во поз-я", parent),
      step_(step),
      nsteps_(0),
      pos_(0),
      npos_(0),
      velocity_(0),
      munit_(1e4),
      anw_args_(5,0),
      req_args_(6,0),
      adr_(adr),
      nInterval_(nInterval),
      ui(new Ui::SPDeviceWidget)
{
    ui->setupUi(this);
    ui->horizontalSlider->installEventFilter(this);
    emit(ui->nsteps_spinBox->editingFinished());

    // Создаем команды устройства
    setCommand("req", adr_[0], {1,1,1,3,2,16});

    startTimer(nInterval_);    // интервал в милисекундах
}

// Возвращает данные о состоянии в виде вектора состояния
json SPDeviceWidget::getStateToSave()
{
    return json();  // Placeholder. TODO add normal realization
}


// Восстанавливает состояние класса из вектора состояния
bool SPDeviceWidget::restoreState(json state)
{
    return true;  // Placeholder. TODO add normal realization
}


SPDeviceWidget::~SPDeviceWidget()
{
    delete ui;
}


void SPDeviceWidget::processData(QByteArray data)
{
    if((int)data[1] == (int)adr_[0]){

        QByteArray anw;
        for(int i = 1; i < 2*4; i += 2)
            anw += data[i];

        QDataStream ds(anw);
        quint32 num;
        ds >> num;

        anw_args_[0] = (num >> 23) & 1;              // DONE
        anw_args_[1] = (num >> 22) & 1;              // ERR
        anw_args_[2] = (num >> 21) & 1;              // WORK
        anw_args_[3] = (num >> 20) & 1;              // HOME
        anw_args_[4] = num & ((1 << 16) - 1);        // STEPS

        npos_ = anw_args_[4];                        // [кол-во шагов от позиции HOME], переданное устройством
        pos_ = (float)anw_args_[4] * step_ * 1e-4;   // позиция [см], переданная устройством

        // если текущая команда исполнена, то кнопка стоп отжимается
        if(anw_args_[0]){
            ui->stop->setChecked(false);
            setStatus("ожидание");
        } else
            setStatus("<font color='green'>активный</font>");

        // обработка ошибки системы привода
        if(anw_args_[1]){
            // QMessageBox::warning(this, "Warning", "Ошибка системы привода");
        }


        ui->done_value->setText(QString::number(anw_args_[0]));
        ui->err_value->setText(QString::number(anw_args_[1]));
        ui->work_value->setText(QString::number(anw_args_[2]));
        ui->home_value->setText(QString::number(anw_args_[3]));
        ui->anw_steps->setText(QString::number(anw_args_[4]));
        ui->fromhome_value->setText(QString::number(npos_));
        ui->anw_pos->setText(QString::number(pos_));
        ui->current_pos_value->setText(QString::number(ceil(pos_ * 10) / 10)); // отображение текущей позициии
        ui->horizontalSlider->setValue(ceil(pos_ * 10) / 10); // отображение только через целое число [см]
        ui->spdPlainText->appendPlainText("ANSWER: anw { 0x" + anw.toHex().toUpper() + " }");
    }
}

// Фильтр взаимодействия со слайдером
bool SPDeviceWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->horizontalSlider && event->type() == QEvent::MouseButtonPress)
        return true;
    if(watched == ui->horizontalSlider && event->type() == QEvent::MouseButtonDblClick)
        return true;
    if(watched == ui->horizontalSlider && event->type() == QEvent::Wheel)
        return true;
    if(watched == ui->horizontalSlider && event->type() == QEvent::KeyPress)
        return true;
    return false;
}


void SPDeviceWidget::setStatus(QString status)
{
    ui->status_value->setText(status);
}

// опрашивает устройство каждые nInterval_ [мс]
void SPDeviceWidget::timerEvent(QTimerEvent *)
{
    emit newRequest(adr_);
}


void SPDeviceWidget::set_req_args(int direction, int permission, int ss, int steps)
{
    req_args_[0] = direction;
    req_args_[1] = permission;
    req_args_[2] = ss;
    req_args_[3] = velocity_;
    req_args_[4] = 0;
    req_args_[5] = steps;
}


void SPDeviceWidget::on_stepLeft_clicked()
{   
    int tmp = npos_ - nsteps_;

    if(tmp >= ui->horizontalSlider->minimum()){
        set_req_args(CW, ABUS, START, (nsteps_ >= 0xF ? nsteps_ - vn[velocity_] : nsteps_ / 2));
        executeCommand("req", req_args_);
        ui->spdPlainText->appendPlainText("REQUEST: req { 0x" + getCommand("req", req_args_).toHex().toUpper() + " }");
    } else
        ui->spdPlainText->appendPlainText("ERROR: position out of range");

    ui->fromhome_value->setText(QString::number(npos_));
    // qDebug() << "pos = " << ceil(pos_ * 10) / 10;
}


void SPDeviceWidget::on_stepRight_clicked()
{
    int tmp = npos_ + nsteps_;

    if(tmp <= ui->horizontalSlider->maximum() * 1e4 / step_){
        set_req_args(CCW, ABUS, START, (nsteps_ >= 0xF ? nsteps_ - vn[velocity_] : nsteps_ / 2));
        executeCommand("req", req_args_);
        ui->spdPlainText->appendPlainText("REQUEST: req { 0x" + getCommand("req", req_args_).toHex().toUpper() + " }");
    } else
        ui->spdPlainText->appendPlainText("ERROR: position out of range");

    ui->fromhome_value->setText(QString::number(npos_));
    // qDebug() << "pos = " << ceil(pos_ * 10) / 10;
}

//for visualization - TO DELETE
void delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(500);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
//

void SPDeviceWidget::on_farRight_toggled(bool checked)
{
    if(checked){
        ui->farLeft->setChecked(false);
        ui->stepLeft->setEnabled(false);
        ui->stepRight->setEnabled(false);
        ui->stop->setEnabled(false);
        ui->farLeft->setEnabled(false);
        while(ui->farRight->isChecked() && ui->horizontalSlider->value() != ui->horizontalSlider->maximum()){
            emit ui->stepRight->clicked();
            delay(); // <- delete
        }
    } else {
        ui->stepLeft->setEnabled(true);
        ui->stepRight->setEnabled(true);
        ui->stop->setEnabled(true);
        ui->farLeft->setEnabled(true);
    }
}


void SPDeviceWidget::on_farLeft_toggled(bool checked)
{
    if(checked){
        ui->farRight->setChecked(false);
        ui->stepLeft->setEnabled(false);
        ui->stepRight->setEnabled(false);
        ui->stop->setEnabled(false);
        ui->farRight->setEnabled(false);
        while(ui->farLeft->isChecked() && ui->horizontalSlider->value() != ui->horizontalSlider->minimum()){
            emit ui->stepLeft->clicked();
            delay(); // <- delete
        }
    } else {
        ui->stepLeft->setEnabled(true);
        ui->stepRight->setEnabled(true);
        ui->stop->setEnabled(true);
        ui->farRight->setEnabled(true);
    }
}


void SPDeviceWidget::on_stop_toggled(bool checked){
    if(checked){
        ui->stepLeft->setEnabled(false);
        ui->stepRight->setEnabled(false);
        ui->farLeft->setEnabled(false);
        ui->farRight->setEnabled(false);

        int go_to = ui->set_pos_spnBox->value() * munit_ / step_ - npos_;
        if(go_to > 0){
            go_to = (go_to >= 0xF ? go_to - vn[velocity_] : go_to / 2);
            set_req_args(CCW, ABUS, START, go_to);
        } else {
            go_to *= -1;
            go_to = (go_to >= 0xF ? go_to - vn[velocity_] : go_to / 2);
            set_req_args(CW, ABUS, START, go_to);
        }
        executeCommand("req", req_args_);
        ui->spdPlainText->appendPlainText("REQUEST: req { 0x" + getCommand("req", req_args_).toHex().toUpper() + " }");
    } else {
        ui->farRight->setChecked(false);
        ui->farLeft->setChecked(false);
        ui->stepLeft->setEnabled(true);
        ui->stepRight->setEnabled(true);
        ui->farLeft->setEnabled(true);
        ui->farRight->setEnabled(true);
    }

}


void SPDeviceWidget::on_nsteps_spinBox_editingFinished()
{
    nsteps_ = ui->nsteps_spinBox->value() * munit_ / step_;
    // qDebug() << "nsteps = " << nsteps_;
}


void SPDeviceWidget::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
        case 0:
            munit_ = 1e4;
            ui->nsteps_spinBox->setMaximum(ui->horizontalSlider->maximum() / 2);
            break;
        case 1:
            munit_ = 1e3;
            ui->nsteps_spinBox->setMaximum(ui->horizontalSlider->maximum() * 10 / 2);
            break;
    }
    emit(ui->nsteps_spinBox->editingFinished());
}


void SPDeviceWidget::on_zone_spinBox_editingFinished()
{
    if(npos_ <= ui->zone_spinBox->value() * 1e4 / step_){
        ui->horizontalSlider->setMaximum(ui->zone_spinBox->value());
        ui->set_pos_spnBox->setMaximum(ui->zone_spinBox->value());
        ui->nsteps_spinBox->setMaximum(ui->zone_spinBox->value() / 2 * (1e4 / munit_));
        emit(ui->nsteps_spinBox->editingFinished());
    } else
         ui->spdPlainText->appendPlainText("ERROR: current position out of zone");
}


void SPDeviceWidget::on_velocity_spinBox_valueChanged(int arg1)
{
    velocity_ = arg1;
}


void SPDeviceWidget::on_home_PushButton_clicked()
{
    int ntmp = (npos_ >= 0xF ? npos_ - vn[velocity_] : npos_ / 2);
    set_req_args(CW, ABUS, START, ntmp);
    executeCommand("req", req_args_);
    ui->spdPlainText->appendPlainText("REQUEST: req { 0x" + getCommand("req", req_args_).toHex().toUpper() + " }");
}


void SPDeviceWidget::on_work_PushButton_clicked()
{
    int steps = ui->horizontalSlider->maximum() * 1e4 / step_ - npos_;
    int ntmp = (steps >= 0xF ? steps - vn[velocity_] : steps / 2);
    set_req_args(CCW, ABUS, START, ntmp);
    executeCommand("req", req_args_);
    ui->spdPlainText->appendPlainText("REQUEST: req { 0x" + getCommand("req", req_args_).toHex().toUpper() + " }");
}

