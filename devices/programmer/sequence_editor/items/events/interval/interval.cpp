#include "interval.hpp"
#include <QDebug>

Interval::Interval(QGraphicsScene* scene, Command* interval_command, int id, QVector<Axes*> devices, unsigned long t_interval, int x, int y, QObject* parent) :
interval_command_(interval_command),
BaseEvent(scene, id, x, y, parent)
{  
    /*
        Создание виджета для настройки интервала времени
        Создание необходимых обеъктов для отображения и перемещения виджета
    */

    header_x = x_ + X_WIDGET_HEADER_INTERVAL;
    header_y = y_ + Y_WIDGET_HEADER_INTERVAL;

    this->headerSetup();  // Создание шапки интервала

    header_->setWidth(MINIMAL_WEIGHT_EVENT);

    this->setHeight(devices.size());    // Установка высоты

    scene_->addItem(this);

    for (int i = 0; i < devices.size(); ++i){
        devices_.append(new CommandArea(scene_, devices[i]->getAddress(), x_, i+1));
        scene_->addItem(devices_.back());
        connect(devices_.back(), SIGNAL(selected(CommandArea*)), this, SLOT(selectGroupCommands(CommandArea*)));
        connect(devices_.back(), SIGNAL(deleted()), this, SIGNAL(deleteGroupCommandsSignal()));
    }

    qDebug() << device_number_;

    scene_->update();

    this->setCursor(Qt::PointingHandCursor);

    this->setAcceptHoverEvents(true); // Разрешение на hover event
}

Interval::~Interval()
{

}

QRectF Interval::boundingRect() const
{ 
    return QRectF(x_,y_,width_+2,height_);
}

void Interval::paint(QPainter* ppainter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    /*
        Отрисовка интервала
    */
    ppainter->setPen(QPen(Qt::black, 1, Qt::DashLine));
    ppainter->drawLine(x_+width_, y_ + HEIGHT_HEADER_INTERVAL, x_+width_, y_ + height_);

    ppainter->setPen(QPen(Qt::black, 1));
    ppainter->setBrush(QBrush(COLOR_GRAY));
    ppainter->drawRect(QRect(x_, y_, width_, HEIGHT_HEADER_INTERVAL));

    ppainter->restore();

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Interval::headerSetup()
{
    header_ = new IntervalHeader();
    
    proxyHeader_ = scene_->addWidget(header_);
    proxyHeader_->setZValue(1);

    transformHeader_ = proxyHeader_->transform();

    transformHeader_.translate(header_x, header_y);
    proxyHeader_->setTransform(transformHeader_);

    connect(header_, SIGNAL(setTimeIntervalSignal(unsigned long)), this, SLOT(setTimeInterval(unsigned long)));
    connect(header_, SIGNAL(closeButtonClickedSignal()), this, SLOT(closeButtonClicked()));
    connect(header_, SIGNAL(addLeftIntervalClickedSignal()), this, SLOT(addLeftInterval()));
    connect(header_, SIGNAL(addRightIntervalClickedSignal()), this, SLOT(addRightInterval()));

    this->setParent(proxyHeader_);
}

// -------------------------------------------------------------- Методы

void Interval::removeThis()
{
    scene_->removeItem(proxyHeader_);
    //delete proxyEdit_; 
    //scene_->removeItem(this);
    //pWidget_ = nullptr;
    //LineEdit_ = nullptr;
    //scene_->removeItem(this);
    while(devices_.count())
    {
        devices_.back()->removeThis();
        delete devices_.back();
        devices_.back() = nullptr;
        devices_.pop_back();
    }
    scene_->update();
}

void Interval::setX(int x)
{
    transformHeader_.translate(x-x_, 0);
    proxyHeader_->setTransform(transformHeader_);

    x_ = x;
    this->updateThis();
    for (int i = 0; i < devices_.size(); ++i)
    {
        devices_[i]->setX(x);
    }
}

void Interval::setWidth(int new_width)
{
    if (new_width > MINIMAL_WEIGHT_EVENT){
        header_->setWidth(new_width);

        width_ = new_width;
        scene_->update();
        for (int i = 0; i < devices_.size(); ++i)
        {
            devices_[i]->setWidth(new_width-2);
        }

    }
}

void Interval::setTimeInterval(unsigned long time)
{
    t_interval_=time;
}

QVector<unsigned long> Interval::getTime() // для 
{
    return {t_interval_};
}

void Interval::addNewTimeline(quint8 address)
{ 
    device_number_++;
    this->setHeight(device_number_);
    qDebug() << device_number_;
    devices_.append(new CommandArea(scene_, address, x_, device_number_));
    devices_.back()->setWidth(width_-2);

    connect(devices_.back(), SIGNAL(selected(CommandArea*)), this, SLOT(selectGroupCommands(CommandArea*)));
    connect(devices_.back(), SIGNAL(deleted()), this, SIGNAL(deleteGroupCommandsSignal()));

    scene_->addItem(devices_.back());
    scene_->update();
}

void Interval::removeTimeline(quint8 address)
{
    device_number_--;
    this->setHeight(device_number_);
    for (int i = 0; i < devices_.size(); ++i)
    {
        if (devices_[i]->getAddress() == address)
        {
            devices_[i]->removeThis();
            delete devices_[i];
            devices_[i] = nullptr;
            devices_.remove(i);
            for (int j = 0; j < devices_.size(); ++j)
            {
                devices_[j]->setPosition(j+1);
                devices_[j]->updateThis();
            }
            scene_->update();
            break;
        }
    }
}

// -------------------------------------------------------------- Слоты

void Interval::selectGroupCommands(CommandArea* area)
{
    emit selectGroupCommandsSignal(id_, area);
}

void Interval::addLeftInterval()
{
    emit addLeft(id_, 0);
}

void Interval::addRightInterval()
{
    emit addRight(id_, 0);
}

QByteArray Interval::buildCommand()
{   
    //qDebug() << "Интервал";
    QByteArray interval_commands = QByteArray();
    interval_commands.append(interval_command_->buildCommand({(double)t_interval_}));
    for (int i = 0; i < devices_.size(); ++i)
    {
        interval_commands.append(devices_[i]->buildCommand());
    }
    return interval_commands;
}