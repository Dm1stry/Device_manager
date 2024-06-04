 #include "graphics.hpp"

/*
    У графики странная особенность динамеческого изменения размеров айтемов
    поэтому в некоторых местах айтем удаляется со сцены и добавляется обратно
*/

Graphics::Graphics(QWidget* parent) : QWidget(parent) 
{
    scene_ = new QGraphicsScene(QRectF(0, 0, 2500, 750));
    view_ = new MyGraphicsView(scene_);

    connect(view_, SIGNAL(clickedOut()), this, SIGNAL(deleteGroupCommandsSignal()));

    scene_->setSceneRect(QRectF(0, 0, 2700, 900));
    view_->centerOn(0, 0);

    view_->setInteractive(true);
    view_->setMouseTracking(true);
    view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    view_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    interval_command_ = new Command("Интервал", 0x01, {24}, 4);
    //interval_command_->setArgumentsSignEncoding(Command::COMPLEMENT);
    interval_command_->setArgumentNames({"t"});
    interval_command_->setTransformFunction(0,"10 * t");
}

// -------------------------------------------------------------- Методы

void Graphics::debugEvents()
{
    qDebug() << events_.size();
    for (int i = 0; i < events_.size(); ++i){
        qDebug() << events_[i]->getID();
    }
}

void Graphics::setDevices(QVector<BaseSyncDevice*> devices)
{
    devices_ = devices;
}

// -------------------------------------------------------------- Слоты

void Graphics::addNewTimeline(QString name, quint8 address)
{
    //timelines_number_++;
    timelines_.append(new Axes(name, address, timelines_.size()));
    //connect(timelines_.back(), SIGNAL(clicked()), this, SIGNAL(deleteGroupCommandsSignal()));
    scene_->addItem(timelines_.back());
    for(int i = 0; i < events_.size(); ++i)
    {
        events_[i]->addNewTimeline(address);
    }
}

void Graphics::removeTimeline(quint8 address)
{
    for(int i = 0; i < timelines_.size(); ++i)
    {   
        if (address == timelines_[i]->getAddress())
        {
            scene_->removeItem(timelines_[i]);
            delete timelines_[i];
            timelines_[i] = nullptr;
            timelines_.remove(i);
            if (timelines_.size() != 0)
            {
                for (int j = 0; j < timelines_.size(); ++j)
                {
                    timelines_[j]->setPosition(j);
                }
                for(int j = 0; j < events_.size(); ++j)
                {
                    events_[j]->removeTimeline(address);
                    // Добавить удаление ОПРЕДЕЛЕННОГО таймлайна внутри
                }
                scene_->update();
                break;
            } else 
            {
                int n = events_.size();
                while (events_.count())
                {
                    events_.back()->removeThis();
                    delete events_.back();
                    events_.back() = nullptr;
                    events_.pop_back();
                }
                scene_->update();
                break;
            }
        }
    }
}

void Graphics::addNewInterval()
{   
    if (timelines_.size() != 0)
    {
        total_number_++;

        if (events_.size() == 0)
        {
            events_.append(new Interval(scene_, interval_command_, total_number_-1, timelines_, 100, 0));
        }
        else{
            events_.append(new Interval(scene_, interval_command_, total_number_-1, timelines_, 100, events_[events_.size()-1]->getRight()-8));
        }

        // debugEvents();

        connect(events_.back(), SIGNAL(widthChanged(int)), this, SLOT(moveEvents(int)));
        connect(events_.back(), SIGNAL(closeThis(int)), this, SLOT(removeInterval(int)));
        connect(events_.back(), SIGNAL(selectGroupCommandsSignal(int, CommandArea*)), this, SIGNAL(selectGroupCommandsSignal(int, CommandArea*)));
        connect(events_.back(), SIGNAL(deleteGroupCommandsSignal()), this, SIGNAL(deleteGroupCommandsSignal()));
        connect(events_.back(), SIGNAL(addLeft(int, int)), this, SLOT(addLeftInterval(int, int)));
        connect(events_.back(), SIGNAL(addRight(int, int)), this, SLOT(addRightInterval(int, int)));

    }
}

void Graphics::addLeftInterval(int id, int mode)
{
    for (int i = 0; i < events_.size(); ++i)
    {
        if (events_[i]->getID() == id)
        {
            total_number_++;
            if (i == 0)
            {
                events_.insert(i, new Interval(scene_, interval_command_, total_number_-1, timelines_, 100, 0));
            }
            else
            {
                events_.insert(i, new Interval(scene_, interval_command_, total_number_-1, timelines_, 100, events_[i-1]->getRight()-8));
            }
            connect(events_[i], SIGNAL(widthChanged(int)), this, SLOT(moveEvents(int)));
            connect(events_[i], SIGNAL(closeThis(int)), this, SLOT(removeInterval(int)));
            connect(events_[i], SIGNAL(selectGroupCommandsSignal(int, CommandArea*)), this, SIGNAL(selectGroupCommandsSignal(int, CommandArea*)));
            connect(events_[i], SIGNAL(deleteGroupCommandsSignal()), this, SIGNAL(deleteGroupCommandsSignal()));
            connect(events_[i], SIGNAL(addLeft(int, int)), this, SLOT(addLeftInterval(int, int)));
            connect(events_[i], SIGNAL(addRight(int, int)), this, SLOT(addRightInterval(int, int)));

            moveEvents(total_number_-1);
            break;
        }
    }
}

void Graphics::addRightInterval(int id, int mode)
{
    for (int i = 0; i < events_.size(); ++i)
    {
        if (events_[i]->getID() == id)
        {
            total_number_++;

            events_.insert(i+1, new Interval(scene_, interval_command_, total_number_-1, timelines_, 100, events_[i]->getRight()-8));

            connect(events_[i+1], SIGNAL(widthChanged(int)), this, SLOT(moveEvents(int)));
            connect(events_[i+1], SIGNAL(closeThis(int)), this, SLOT(removeInterval(int)));
            connect(events_[i+1], SIGNAL(selectGroupCommandsSignal(int, CommandArea*)), this, SIGNAL(selectGroupCommandsSignal(int, CommandArea*)));
            connect(events_[i+1], SIGNAL(deleteGroupCommandsSignal()), this, SIGNAL(deleteGroupCommandsSignal()));
            connect(events_[i+1], SIGNAL(addLeft(int, int)), this, SLOT(addLeftInterval(int, int)));
            connect(events_[i+1], SIGNAL(addRight(int, int)), this, SLOT(addRightInterval(int, int)));

            moveEvents(total_number_-1);
            break;
        }
    }
}

void Graphics::removeInterval(int id)
{   
    for(int i = 0; i < events_.size(); ++i){
        if(events_[i]->getID() == id){
            events_[i]->removeThis();
            delete events_[i];
            events_[i] = nullptr;
            //events_number_--;
            if((i==0) && (events_.size() != 1)){
                events_[i+1]->setX(LEFT_OFFSET);
            }
            events_.remove(i);
            scene_->update();
            break;
        }
    }
    moveEvents(id);

    // debugEvents();
}

void Graphics::moveEvents(int id)
{
    if(events_.size() > 1)
    {
        for(int i = 1; i < events_.size(); ++i)
        {
            if(events_[i]->getID() != id){
                events_[i]->setX(events_[i-1]->getRight()+2);
            }
        }
    }  

    // debugEvents();
}

QByteArray Graphics::buildSequence()
{
    QByteArray sequence = QByteArray();
    for (int i = 0; i < events_.size(); ++i)
    {
        sequence.append(events_[i]->buildCommand());
    }
    return sequence;
}

QVector<unsigned long> Graphics::getTimeIntervals()
{
    QVector<unsigned long> times;
    for (int i = 0; i < events_.size(); ++i)
    {
        times.append(events_[i]->getTime());
    }
    return times;
}