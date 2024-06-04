#include "customlistwidget.hpp"

CustomListWidget::CustomListWidget(unsigned int displayable /*= 4*/, QWidget * parent /*= nullptr*/)
  : QWidget(parent),
    scrollable_layout_(new QVBoxLayout),
    scroll_bar_(new QScrollBar),
    current_index_(0),
    items_in_layout_(displayable)
    //central_widget_(new QWidget(this)),
    //central_layout_(new QVBoxLayout(this))
{
    layoutSetup();
    scroll_bar_->setMaximum(0);
    connect(scroll_bar_, &QScrollBar::valueChanged, [=](int value) {
        displayAt(value);
    });
}

inline void CustomListWidget::layoutSetup()
{
    QHBoxLayout * main_layout = new QHBoxLayout(this);

    main_layout->addLayout(scrollable_layout_);
    main_layout->addWidget(scroll_bar_);

    this->setLayout(main_layout);
}

void CustomListWidget::displayAt(int index)
{
    if(index >= widgets_.size() - items_in_layout_)
    {
        index = widgets_.size() - items_in_layout_;
    }
    if(index <= 0)
    {
        index = 0;
    }

    current_index_ = index;

    for(int i = 0; i < widgets_.size(); ++i)
    {
        if(i >= index && i < index + items_in_layout_)
        {
            widgets_[i]->show(); 
        }
        else
        {
            widgets_[i]->hide();
        }
    }
}

void CustomListWidget::addWidget(QWidget * widget)
{
    widgets_.push_back(widget);
    scrollable_layout_->addWidget(widget);
    int maximum_scrollbar_value = widgets_.size() -  items_in_layout_;
    if(maximum_scrollbar_value >= 0)
        scroll_bar_->setMaximum(maximum_scrollbar_value);
    scroll_bar_->setValue(scroll_bar_->maximum());
}

void CustomListWidget::removeWidget(int index)
{
    scrollable_layout_->takeAt(index);
    scrollable_layout_->update();
    auto deleted_widget = widgets_.takeAt(index);
    delete deleted_widget;
    
    if(index >= current_index_ && index < current_index_ + items_in_layout_)
    {
        displayAt(current_index_);
    }
    
    int maximum_scrollbar_value = widgets_.size() -  items_in_layout_;
    if(maximum_scrollbar_value >= 0)
    {
        scroll_bar_->setMaximum(maximum_scrollbar_value);
    }

    this->update();
}

void CustomListWidget::removeWidget(QWidget * widget)
{ 
    for(int i = 0; i < widgets_.size(); ++i)
    {
        if(widgets_[i] == widget)
        {
            removeWidget(i);
            break;
        }
    }
}

void CustomListWidget::setDisplayableWidgetsAmount(unsigned int amount)
{
    items_in_layout_ = amount;
}

void CustomListWidget::wheelEvent(QWheelEvent * event)
{
    QPoint movement = event->angleDelta();
    if(!movement.isNull())
    {
        scroll_bar_->setValue(scroll_bar_->value() - movement.y() / 120);
    }
    else
    {
        movement = event->pixelDelta();
        scroll_bar_->setValue(scroll_bar_->value() + movement.y() / 2);
    }
    
}