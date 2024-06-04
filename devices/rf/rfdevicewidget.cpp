#include "rfdevicewidget.hpp"
#include <QDebug>

#ifndef __linux__
#include <corecrt_math_defines.h>
#endif

RFDeviceWidget::RFDeviceWidget(QWidget * parent /*= nullptr*/)
  : BaseDeviceWidget("РЧ генератор", parent),
  channel_(0),
  freq_(0),
  duration_(0),
  phase_(0),
  setfreq_btn_(new QPushButton("Установить")),
  rfp_dur_ln_(new QLineEdit),
  rfp_ph_ln_(new QLineEdit),
  rfp_btn_(new QPushButton("Запуск")),
  rf_chat_(new QPlainTextEdit)

{
    layoutSetup();
    rf_chat_->setReadOnly(true);

    // Создаем две команды устройства
    setCommand("setfreq", 0xDC, {2, 22});
    commands_["setfreq"]->setArgumentNames({"rfch", "freq"});
    commands_["setfreq"]->setTransformFunction(1,"(2^22)*freq/250");

    setCommand("rfp", 0xDE, {2, 6, 16});
    commands_["rfp"]->setArgumentNames({"rfch", "ph", "dur"});
    commands_["rfp"]->setTransformFunction(1,"(2^6)*ph/(2*pi)");
    commands_["rfp"]->setTransformFunction(2,"10*dur");

    //setChannel
    // [=] → [=,  this]: local variables by value, class members by reference
    // [=] → [=, *this]: everything by value
    // [&] → [&,  this]: everything by reference
    // [&] → [&, *this]: (this would be unusual)
    connect(&ch_spnbox[0], &QSpinBox::textChanged, [=, this](){setChannel(0);}); 
    connect(&ch_spnbox[1], &QSpinBox::textChanged, [=, this](){setChannel(1);});
    connect(&ch_spnbox[2], &QSpinBox::textChanged, [=, this](){setChannel(2);});
    connect(&ch_spnbox[3], &QSpinBox::textChanged, [=, this](){setChannel(3);});

    //setFreq
    connect(setfreq_btn_, &QPushButton::clicked, this, &RFDeviceWidget::setFreq);
    
    //setPulseChannel
    connect(&pls_channel_, &QSpinBox::textChanged, [=, this](){setPulseChannel();}); 

    //setDuration
    connect(rfp_dur_ln_, &QLineEdit::returnPressed, this, &RFDeviceWidget::setDuration);
    connect(rfp_dur_ln_, &QLineEdit::textChanged, this, &RFDeviceWidget::setDuration);

    //setPhase
    connect(rfp_ph_ln_, &QLineEdit::returnPressed, this, &RFDeviceWidget::setPhase);
    connect(rfp_ph_ln_, &QLineEdit::textChanged, this, &RFDeviceWidget::setPhase);

    //startPulse
    connect(rfp_btn_, &QPushButton::clicked, this, &RFDeviceWidget::startPulse);
}

void RFDeviceWidget::processData(QByteArray data)
{}

// Возвращает данные о состоянии в виде вектора состояния
json RFDeviceWidget::getStateToSave()
{
    return json();  // Placeholder. TODO add normal realization
}

// Восстанавливает состояние класса из вектора состояния
bool RFDeviceWidget::restoreState(json state)
{
    return true;  // Placeholder. TODO add normal realization
}

void RFDeviceWidget::setChannel(int n){
    QSet<int> selectedValues;
    int left = 0;
    //добавление всех каналов в множество после изменения
    for (int i = 0; i < 4; i++)
        selectedValues.insert(ch_spnbox[i].value());
    //поиск забытого канала
    for (int i = 0; i < 4; i++)
        if(!selectedValues.contains(i + 1))
            left = i + 1;
    //установка неповторяющихся значений каналов
    for(int i = 0; i < 4; i++){
        for (int j = i + 1; j < 4; j++)
            if (ch_spnbox[i].value() == ch_spnbox[j].value()){
                if (i != n)
                    ch_spnbox[i].setValue(left);
                else
                    ch_spnbox[j].setValue(left);
                break;
            }
    }
}

void RFDeviceWidget::setPulseChannel()
{
    channel_ = pls_channel_.value() - 1;
}

void RFDeviceWidget::setFreq()
{   
    //cmd[31:0] = {adr[31:24], data[23:0]} - basis command pattern
    //setfreq[31:0] = {adr[31:24], rfch[23:22], freq[21:0]}
    double chanel;
    double freq;
    for (int i = 0; i < 4; i++)
    {   
        chanel = ch_spnbox[i].value() - 1;
        freq = setfreq_ln[i].text().toDouble();
        emit newCommand(commands_["setfreq"]->buildCommand({chanel, freq}));
        rf_chat_->appendPlainText("Frequency set with command: setfreq { 0x" + getCommand("setfreq", {chanel, freq}).toHex().toUpper() + " }");
    }
}

void RFDeviceWidget::setDuration()
{
    duration_ = (rfp_dur_ln_->text().toDouble());
}

void RFDeviceWidget::setPhase()
{   
    // float f_phase = (rfp_ph_ln_->text().toFloat()) * (1 << 5) / (M_PI);
    // phase_ = static_cast<unsigned>(f_phase);
    phase_ = rfp_ph_ln_->text().toDouble();
}

void RFDeviceWidget::startPulse()
{
    //cmd[31:0] = {adr[7:0], rfch[23:22], ph[21:16], dur[15:0]}
    //executeCommand("rfp", arguments);
    emit newCommand(commands_["rfp"]->buildCommand({channel_, phase_, duration_}));
    rf_chat_->appendPlainText("Pulse command: rfp { 0x" + getCommand("rfp", {channel_, phase_, duration_}).toHex().toUpper() + " }");
}


inline void RFDeviceWidget::layoutSetup()
{
    QGridLayout * rfch_pgrdLayout = new QGridLayout;
    QLabel * ch_lbl = new QLabel("№ РЧ-канал");
    for (int i = 0; i < 4; i++){
        ch_spnbox[i].setRange(1, 4);
        ch_spnbox[i].setValue(i + 1);
        rfch_pgrdLayout->addWidget(&ch_spnbox[i], i + 1, 0);
        rfch_pgrdLayout->addWidget(&setfreq_ln[i], i + 1, 1);
    }

    QLabel * setfreq_lbl = new QLabel("Частота (МГц)");

    rfch_pgrdLayout->setContentsMargins(5,5,5,5);
    rfch_pgrdLayout->addWidget(ch_lbl, 0, 0);
    rfch_pgrdLayout->addWidget(setfreq_lbl, 0, 1);
    rfch_pgrdLayout->addWidget(setfreq_btn_, 4, 2);
    setfreq_btn_->setMinimumSize(90, 0);

    QFrame * separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    separator->setLineWidth(1);

    QLabel * rfp_ch_lbl = new QLabel("Канал:");
    pls_channel_.setRange(1, 4);
    QLabel * rfp_dur_lbl = new QLabel("Длительность (мкс):");
    QLabel * rfp_ph_lbl = new QLabel("Фаза (рад):");
    QGridLayout * rfp_pgrdLayout = new QGridLayout;

    rfp_pgrdLayout->setContentsMargins(5,5,5,5);

    rfp_pgrdLayout->addWidget(rfp_ch_lbl, 0, 0);
    rfp_pgrdLayout->addWidget(&pls_channel_, 0, 1);

    rfp_pgrdLayout->addWidget(rfp_ph_lbl, 1, 0);
    rfp_pgrdLayout->addWidget(rfp_ph_ln_, 1, 1);

    rfp_pgrdLayout->addWidget(rfp_dur_lbl, 2, 0);
    rfp_pgrdLayout->addWidget(rfp_dur_ln_, 2, 1);

    rfp_pgrdLayout->addWidget(rfp_btn_, 1, 2);
    rfp_btn_->setMinimumSize(90, 0);

    rf_chat_->setContentsMargins(5,5,5,5);

    QVBoxLayout * vbl = new QVBoxLayout;

    vbl->addLayout(rfch_pgrdLayout);
    vbl->addWidget(separator);
    vbl->addLayout(rfp_pgrdLayout);
    vbl->addWidget(rf_chat_);

    this->setLayout(vbl);
}
