#include "device_editor.hpp"

DeviceEditor::DeviceEditor(QWidget* parent):QWidget(parent)
{
    layoutSetup();
    setConnections();
}

DeviceEditor::~DeviceEditor()
{
    
}

void DeviceEditor::layoutSetup()
{
    QHBoxLayout* main_layout = new QHBoxLayout();

    QScrollArea* left_area = new QScrollArea();
    left_area->setWidgetResizable(true);

    QScrollArea* right_area = new QScrollArea();
    QVBoxLayout* right_layout = new QVBoxLayout();

    QWidget *scrollWidget = new QWidget();
    QVBoxLayout* left_layout = new QVBoxLayout(scrollWidget);
    left_layout->setAlignment(Qt::AlignTop);
    left_area->setWidget(scrollWidget);
    scrollWidget->setLayout(left_layout);

    block_list_ = new QListWidget();

    blocks_.append(new CommandBlockEditor(1, "1", block_list_));
    connect(blocks_.back(), SIGNAL(addNewCommandSignal()), this, SLOT(updateDeviceList()));
    left_layout->addWidget(blocks_.back());

    blocks_.append(new CommandBlockEditor(2, "2", block_list_));
    connect(blocks_.back(), SIGNAL(addNewCommandSignal()), this, SLOT(updateDeviceList()));
    left_layout->addWidget(blocks_.back());

    main_layout->addWidget(left_area);
    main_layout->addWidget(right_area);
    main_layout->setStretch(0,3);
    main_layout->setStretch(1,1);

    this->setLayout(main_layout);
}

void DeviceEditor::setConnections()
{

}

// ------------------------------------------------- Методы



// ------------------------------------------------- Слоты

void DeviceEditor::updateDeviceList()
{
    // for(int i = 0; i < block_list_->count(); i++)
    // {
    //     // QListWidgetItem* item = block_list_->item(i);
    //     // QWidget* widget = block_list_->itemWidget(item);
    //     // block_list_->setItemWidget(item, widget);
    // }
}
