#include "interval_header.hpp"

IntervalHeader::IntervalHeader(QFrame* parent):
QFrame(parent)
{
    this->layoutSetup();
    this->connectionSetup();
}

IntervalHeader::~IntervalHeader()
{

}

void IntervalHeader::layoutSetup()
{
    this->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    this->setStyleSheet("background-color:rgb(240,240,240)");

    QHBoxLayout* main_layout = new QHBoxLayout();

    // -------------------------------------------------------------- Label

    label_ = new QLineEdit("t = ");
    label_->setMaximumWidth(30);

    QFont font1 = label_->font();     // Создание шрифта
    font1.setPixelSize(TEXT_FONT_SIZE_INTERVAL);           // Высота шрифта
    label_->setFont(font1);           // Задание шрифта

    label_->setReadOnly(true);
    label_->setFrame(false);
    label_->setContextMenuPolicy(Qt::PreventContextMenu);

    QPalette palette1 = label_->palette();
    palette1.setColor(QPalette::Base, COLOR_GRAY);
    label_->setAutoFillBackground(true);
    label_->setPalette(palette1);

    main_layout->addWidget(label_);
    main_layout->addSpacing(-15);

    // -------------------------------------------------------------- LineEdit

    lineEdit_ = new QLineEdit;
    lineEdit_->setValidator(new QIntValidator(1, 100000000, this));
    lineEdit_->setMaximumWidth(85);

    QFont font2 = lineEdit_->font();                // Создание шрифта
    font2.setPixelSize(TEXT_FONT_SIZE_INTERVAL);    // Высота шрифта
    lineEdit_->setFont(font2);                      // Задание шрифта

    lineEdit_->setText("100");
    lineEdit_->setFrame(false);
    lineEdit_->setContextMenuPolicy(Qt::PreventContextMenu);

    QPalette palette2 = lineEdit_->palette();
    palette2.setColor(QPalette::Base, COLOR_GRAY);
    lineEdit_->setPalette(palette2);

    main_layout->addWidget(lineEdit_);
    main_layout->addStretch(1);

    // -------------------------------------------------------------- Button

    QPixmap pixmap(":/programmerdevice/interval/dots-horizontal.svg");
    QIcon ButtonIcon(pixmap);
    menuButton_ = new QPushButton();
    menuButton_->setIcon(ButtonIcon);
    menuButton_->setIconSize(QSize(19,15));
    menuButton_->setMaximumSize(19,15);
    menuButton_->setStyleSheet("QPushButton{background: rgb(240,240,240); border-radius: 5px; border:none;}"
                          "QPushButton:hover{background: rgb(210,210,210); border-radius: 5px; border:none;}"); 

    main_layout->addWidget(menuButton_);
    main_layout->setContentsMargins(1,1,3,1);
    main_layout->setAlignment(Qt::AlignLeft);
    this->setLayout(main_layout);


    label_->installEventFilter(this);
    lineEdit_->installEventFilter(this);
    menuButton_->installEventFilter(this);
    this->installEventFilter(this);
}

void IntervalHeader::connectionSetup()
{
    connect(lineEdit_, SIGNAL(editingFinished()), this, SLOT(setTimeInterval()));
    //connect(menuButton_, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));
    connect(menuButton_, SIGNAL(clicked()), this, SLOT(showMenu()));
}

// -------------------------------------------------------------- Методы

void IntervalHeader::setWidth(int width)
{
    this->setFixedSize(width-1,HEIGHT_HEADER_INTERVAL-1);
}

// -------------------------------------------------------------- Слоты

void IntervalHeader::setTimeInterval()
{
    emit setTimeIntervalSignal(lineEdit_->text().toULong());
}

void IntervalHeader::showMenu()
{
    QMenu main_menu = QMenu();
    main_menu.setStyleSheet("QMenu{color: black; background: rgb(240,240,240); border-radius: 5px; }"
                           "QMenu::item:selected {color: white; background: rgb(0,120,215);}");

    // ----------------------------------------------------

    QMenu add_left_menu = QMenu("Добавить слева", &main_menu);
    add_left_menu.setStyleSheet("QMenu{color: black; background: rgb(240,240,240); border-radius: 5px; }"
                            "QMenu::item:selected {color: white; background: rgb(0,120,215);}");
    add_left_menu.setIcon(QIcon(QPixmap(":/programmerdevice/interval/menu/corner-left-down.svg")));                        


    QAction left_interval = QAction("Интервал", &add_left_menu);

    QAction left_loop = QAction("Цикл", &add_left_menu);

    QAction left_macro = QAction("Макрос", &add_left_menu);

    add_left_menu.addAction(&left_interval);
    add_left_menu.addAction(&left_loop);
    add_left_menu.addAction(&left_macro);

    // ----------------------------------------------------
    
    QMenu add_right_menu = QMenu("Добавить справа", &main_menu);
    add_right_menu.setStyleSheet("QMenu{color: black; background: rgb(240,240,240); border-radius: 5px; }"
                            "QMenu::item:selected {color: white; background: rgb(0,120,215);}");
    add_right_menu.setIcon(QIcon(QPixmap(":/programmerdevice/interval/menu/corner-right-down.svg")));                        


    QAction right_interval = QAction("Интервал", &add_right_menu);

    QAction right_loop = QAction("Цикл", &add_right_menu);

    QAction right_macro = QAction("Макрос", &add_right_menu);

    add_right_menu.addAction(&right_interval);
    add_right_menu.addAction(&right_loop);
    add_right_menu.addAction(&right_macro);

    // ----------------------------------------------------

    QAction close = QAction("Удалить");
    close.setIcon(QIcon(QPixmap(":/programmerdevice/interval/menu/trash-alt.svg")));

    main_menu.addMenu(&add_left_menu);
    main_menu.addMenu(&add_right_menu);
    main_menu.addAction(&close);

    //connect(item1, &QAction::triggered, this, &ContextMenu::slotItem1);
    //connect(item2, &QAction::triggered, this, &ContextMenu::slotItem2);

    connect(&right_interval, &QAction::triggered, this, &IntervalHeader::addRightIntervalClicked);
    connect(&left_interval, &QAction::triggered, this, &IntervalHeader::addLeftIntervalClicked);
    connect(&close, &QAction::triggered, this, &IntervalHeader::closeButtonClicked);

    main_menu.exec(mapToGlobal(QPoint(menuButton_->geometry().bottomLeft().x(), menuButton_->geometry().bottomLeft().y()+1)));

}

void IntervalHeader::closeButtonClicked()
{
    emit closeButtonClickedSignal();
}

void IntervalHeader::addLeftIntervalClicked()
{
    emit addLeftIntervalClickedSignal();
}

void IntervalHeader::addRightIntervalClicked()
{
    emit addRightIntervalClickedSignal();
}

// -------------------------------------------------------------- Ивенты

bool IntervalHeader::eventFilter(QObject* object, QEvent* event)
{
    if((object == lineEdit_ || object==label_ || object==menuButton_ || object==this) && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *k = static_cast<QMouseEvent *> (event);
        if( k->button() == Qt::MiddleButton) {
            emit closeButtonClickedSignal();
            return true;
        }
    }
    return false;
}