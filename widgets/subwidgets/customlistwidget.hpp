#ifndef CUSTOM_LIST_WIDGET
#define CUSTOM_LIST_WIDGET

#include <QListWidget>
#include <QScrollBar>
//#include <QScrollArea>
#include <QVBoxLayout>
#include <QDebug>
#include <QPlainTextEdit>

class CustomListWidget : public QWidget
{
Q_OBJECT
public:
    CustomListWidget(unsigned int displayable = 4, QWidget * parent = nullptr);
public slots:
    void addWidget(QWidget * widget);
    void removeWidget(int index);
    void removeWidget(QWidget * widget);
    void setDisplayableWidgetsAmount(unsigned int amount);
protected:
    void wheelEvent(QWheelEvent * event);
private:
    inline void layoutSetup();
    void displayAt(int index);

    //QWidget * central_widget_;
    QVector<QWidget*> widgets_;
    QVBoxLayout * scrollable_layout_;
    QScrollBar * scroll_bar_;

    unsigned int current_index_;
    unsigned int items_in_layout_;
};

#endif