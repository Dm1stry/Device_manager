#include "programmerdevicewidget.hpp"

/*
    Пока что это все радактируется
*/

ProgrammerDeviceWidget::ProgrammerDeviceWidget(QWidget * parent)
  : BaseDeviceWidget("Программатор", parent)
{
    layoutSetup();
    setDevice();
    setConnections();
}

void ProgrammerDeviceWidget::layoutSetup()
{
    QHBoxLayout* pMain_layout = new QHBoxLayout();
    QVBoxLayout* pRight_layout = new QVBoxLayout();
    QVBoxLayout* pLeft_layout = new QVBoxLayout();
    QHBoxLayout* pUp_layout = new QHBoxLayout();
    QHBoxLayout* pDown_layout = new QHBoxLayout();
    
    pMain_layout->addLayout(pLeft_layout);
    pMain_layout->addLayout(pRight_layout);

    pMain_layout->setStretch(0,2);
    pMain_layout->setStretch(1,15);

    // ------------------------------------------------- Правая часть

    graph_ = new Graphics();

    pRight_layout->addLayout(pUp_layout);

    pRight_layout->addWidget(graph_->view_);
        
    pRight_layout->setAlignment(Qt::AlignTop);

    pRight_layout->setStretch(0,1);
    pRight_layout->setStretch(1,8);

    // ------------------------------------------------- Нижняя часть

    //////////// Временно
    test_ = new QLineEdit();
    test_button_ = new QPushButton("Тест");
    connect(test_button_, SIGNAL(clicked()), this, SLOT(settingsDevice()));
   
    //arguments_settings_ = new QListWidget();
    //ArgumentSettings* testttt = new ArgumentSettings("Test", arguments_settings_);
    command_settings_ = new BlockSettings("");

    pDown_layout->addWidget(command_settings_);
    // pDown_layout->addWidget(test_);
    // pDown_layout->addWidget(test_button_);

    pRight_layout->addLayout(pDown_layout);
    ////////////
    
    // ------------------------------------------------- Строка ивентов и команд
   
    button_add_interval_ = new QPushButton("Интервал");
    button_add_interval_->setMaximumHeight(30);

    button_add_loop_ = new QPushButton("Цикл");
    button_add_loop_->setMaximumHeight(30);

    button_add_macros_ = new QPushButton("Макрос");
    button_add_macros_->setMaximumHeight(30);

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Plain);
    line->setStyleSheet("color:gray");
    line->setMaximumHeight(30);

    QLabel* command_block_label = new QLabel("Блок: ");
    combobox_select_block_ = new QComboBox();
    button_add_command_ = new QPushButton("Добавить");
    button_remove_command_ = new QPushButton("Удалить");

    button_start_sequence_ = new QPushButton("Старт");
    button_stop_sequence_ = new QPushButton("Стоп");

    pUp_layout->addWidget(button_add_interval_);
    pUp_layout->addWidget(button_add_loop_);
    pUp_layout->addWidget(button_add_macros_);
    pUp_layout->addWidget(line);

    pUp_layout->addWidget(command_block_label);
    pUp_layout->addWidget(combobox_select_block_);
    pUp_layout->addWidget(button_add_command_);
    pUp_layout->addWidget(button_remove_command_);
    pUp_layout->addStretch(1);
    pUp_layout->addWidget(button_start_sequence_);
    pUp_layout->addWidget(button_stop_sequence_);

    pUp_layout->setAlignment(Qt::AlignLeft);

    // ------------------------------------------------- Левая часть

    QLabel* main_label = new QLabel("Синхронные\nустройтва");
    QFont font = main_label->font();
    font.setPixelSize(16);
    main_label->setFont(font);
    main_label->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    list_devices_ = new QListWidget();

    qDebug() << list_devices_->count();
    graph_->setDevices(devices_);

    pLeft_layout->addWidget(main_label);
    pLeft_layout->addWidget(list_devices_);
    pLeft_layout->setAlignment(Qt::AlignTop);

    this->setLayout(pMain_layout);
}

void ProgrammerDeviceWidget::setConnections()
{
    connect(button_add_interval_, SIGNAL(clicked()), graph_, SLOT(addNewInterval()));

    connect(button_add_command_, SIGNAL(clicked()), this, SLOT(addCommandToArea()));
    connect(button_remove_command_, SIGNAL(clicked()), this, SLOT(removeCommandFromArea()));

    connect(button_start_sequence_, SIGNAL(clicked()), this, SLOT(startSequence()));
    connect(button_stop_sequence_, SIGNAL(clicked()), this, SLOT(stopSequence()));

    for(int i = 0; i < devices_.size(); ++i)
    {
        connect(devices_[i]->getWidget(), SIGNAL(addDevice(QString, quint8)),graph_, SLOT(addNewTimeline(QString, quint8)));
        connect(devices_[i]->getWidget(), SIGNAL(removeDevice(quint8)),graph_, SLOT(removeTimeline(quint8)));
    }

    connect(graph_, SIGNAL(selectGroupCommandsSignal(int, CommandArea*)), this, SLOT(selectGroupCommands(int, CommandArea*)));   
    connect(graph_, SIGNAL(deleteGroupCommandsSignal()), this, SLOT(deleteGroupCommands())); 
    
    connect(command_settings_, SIGNAL(argumentChanged(QString, QString, double)), this, SLOT(updateCommandBlockArguments(QString, QString, double)));  
}

void ProgrammerDeviceWidget::setDevice()
{
    programmer_ = new Command("programmer", 0x01, {8}, 4);

    // ------------------------------------------------------------------

    QVector<Command*> impulse;
    impulse.append(new Command("rfp", 0xDE, {2,6,16}, 4));
    impulse.back()->setArgumentNames({"rfch", "ph", "dur"});
    impulse.back()->setTransformFunction(1,"(2^6)*ph/(2*pi)");
    impulse.back()->setTransformFunction(2,"10*dur");

    QVector<Command*> set_freq;
    set_freq.append(new Command("setfreq", 0xDC, {2,22}, 4));
    set_freq.back()->setArgumentNames({"rfch", "freq"});
    set_freq.back()->setTransformFunction(1,"(2^22)*freq/250");

    devices_.append(new BaseSyncDevice("RF gen", 0x00, list_devices_));
    devices_.back()->addCommandBlock(new CommandBlock("РЧ импульс", impulse, 0));
    devices_.back()->addCommandBlock(new CommandBlock("Частота", set_freq, 1));
    
    // ------------------------------------------------------------------

    QVector<Command*> adc;
    adc.append(new Command("adc", 0xAD, {2,2,4}, 4));
    adc.back()->setArgumentNames({"adch", "flr", "ena"});

    devices_.append(new BaseSyncDevice("ADC", 0x01, list_devices_));
    devices_.back()->addCommandBlock(new CommandBlock("Окно", adc, 1));
    
    // ------------------------------------------------------------------

    QVector<Command*> ret;
    ret.append(new Command("ret", 0x08, {12,12}, 4));
    ret.back()->setArgumentNames({"---", "adr"});

    devices_.append(new BaseSyncDevice("RET", 0x08, list_devices_));
    devices_.back()->addCommandBlock(new CommandBlock("Возврат", ret, 1));
}

// ---------------------------------------- Методы

void ProgrammerDeviceWidget::processData(QByteArray data)
{

}

// Возвращает данные о состоянии в виде вектора состояния
json ProgrammerDeviceWidget::getStateToSave()
{
    return json();  // Placeholder. TODO add normal realization
}

// Восстанавливает состояние класса из вектора состояния
bool ProgrammerDeviceWidget::restoreState(json state)
{
    return true;  // Placeholder. TODO add normal realization
}

// ---------------------------------------- Слоты

void ProgrammerDeviceWidget::selectGroupCommands(int id, CommandArea* area)
{
    test_->setText(QString::number(id) + " "+ QString::number(area->getAddress(),16));
    selected_command_ = area;
    combobox_select_block_->clear();
    for (int i = 0; i < devices_.size(); ++i)
    {
        if (devices_[i]->getAddress() == selected_command_->getAddress())
        {
            for (int j = 0; j < devices_[i]->getCommandBlockCount(); ++j)
            {
                combobox_select_block_->addItem(devices_[i]->getCommandBlock(j)->getName());
            }
        }
    }
    updateBlockSettings();
}

void ProgrammerDeviceWidget::deleteGroupCommands()
{
    selected_command_ = nullptr;
    combobox_select_block_->clear();
    updateBlockSettings();
}

void ProgrammerDeviceWidget::addCommandToArea()
{
    for (int i = 0; i < devices_.size(); ++i)
    {
        if ((selected_command_ != nullptr) && (devices_[i]->getAddress() == selected_command_->getAddress()))
        {
            selected_command_->setCommandBlock(devices_[i]->getCommandBlock(combobox_select_block_->currentIndex())->getBlockDataCopy());
        }
    }
    updateBlockSettings();
}

void ProgrammerDeviceWidget::removeCommandFromArea()
{
    if (selected_command_ != nullptr)
    {
        selected_command_->removeCommandBlock();
    }
    updateBlockSettings();
}

void ProgrammerDeviceWidget::updateBlockSettings()
{
    if (selected_command_ != nullptr && selected_command_->getState())
    {
        QVector<QString> arguments_commands_names = selected_command_->getBlockData()->getCommandsName();
        QVector<QString> arguments_names = selected_command_->getBlockData()->getArgumentsName();
        QVector<double> arguments_value = selected_command_->getBlockData()->getArgumentsValue();
        command_settings_->setArgumentsLines(selected_command_->getBlockData()->getName(), arguments_commands_names, arguments_names, arguments_value);
    }
    else 
    {
        command_settings_->clearList();
    }
}

void ProgrammerDeviceWidget::updateCommandBlockArguments(QString command_name, QString name, double value)
{
    selected_command_->getBlockData()->setArgumentValue(command_name, name, value);
}

void ProgrammerDeviceWidget::startSequence()
{
    QByteArray Idle = programmer_->buildCommand({0});
    QByteArray Load = programmer_->buildCommand({76});
    QByteArray Start = programmer_->buildCommand({83});
    
    emit newCommand(Idle); // Idle
    qDebug() << Idle.toHex();
    QThread::usleep(10);

    emit newCommand(Load); // Load
    qDebug() << Load.toHex();
    QThread::usleep(10);

    QByteArray sequence = QByteArray();
    sequence.append((char)0x02);
    sequence.append(graph_->buildSequence());
    // sequence.append((char)0x80);
    // sequence.append((char)0xFF);
    // sequence.append((char)0xF7);
    // sequence.append((char)0xFF);
    qDebug() << sequence.toHex();
    emit newCommand(sequence);
    QThread::usleep(10);

    emit newCommand(Start); // Start
    qDebug() << Start.toHex();
    QThread::usleep(10);

    // QVector<unsigned long> intervals;
    // intervals.append(graph_->getTimeIntervals());
    // qDebug() << intervals;

    // emit newBroadcast("Sequence_start", {1});
}

void ProgrammerDeviceWidget::stopSequence()
{
    emit newCommand(programmer_->buildCommand({53})); // Stop
    //emit newBroadcast("Sequence_stop", {1});
}

void ProgrammerDeviceWidget::settingsDevice()
{
    //////////////////////// Временные тесты
    DeviceEditor* deviceNew = new DeviceEditor();
    deviceNew->resize(WINDOW_WIDTH,WINDOW_HEIGHT);
    deviceNew->setWindowTitle("Настройки");
    deviceNew->show();
}

