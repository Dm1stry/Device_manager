#include "adcdevicewidget.hpp"
#include "ui_adcdevicewidget.h"
#include <QDebug>
#include <QEvent>
#include <QTime>

//for visualization - TO DELETE
// Function to generate Gaussian noise
double gaussianNoise() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::normal_distribution<double> dist(0, 0.02); // Mean = 0, Standard deviation = 0.1
    return dist(gen);
}


void plot_delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(500);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void ADCDeviceWidget::signal_imitation(){
    const int numPoints = 3e3;
    const int range = 3e7;
    const double accelerationFrequency = 20;

    QVector<double> X(numPoints);
    QVector<double> Y(numPoints);

    // Generate X values
    for (int i = 0; i < numPoints; ++i) {
        X[i] = (double)i * range / numPoints;
    }

    // Generate Y values according to the formula Y = 0.3 * exp(-X/3000000) + 0.7 * exp(-X/7000000) + gaussianNoise()
    for (int i = 0; i < numPoints; ++i) {
        Y[i] = cos(X[i] / 10e6 * 2 * M_PI * accelerationFrequency)*(0.3 * exp(-X[i] / 3000000) + 0.7 * exp(-X[i] / 7000000)) + gaussianNoise();
    }

    ui->plotter->graph(0)->setData(X, Y);
}
//



ADCDeviceWidget::ADCDeviceWidget(QWidget *parent)
    : BaseDeviceWidget("АЦП", parent), ui(new Ui::ADCDeviceWidget)
{
    ui->setupUi(this);

    ui->plotter->addGraph();
    ui->plotter->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plotter->graph()->setLineStyle(QCPGraph::lsLine);
    ui->plotter->xAxis->setLabel("Time, [mks]");
    ui->plotter->yAxis->setLabel("Signal Amplitude, [a.u.]");
    ui->plotter->xAxis->setRange(-1e3, 3e7);
    ui->plotter->yAxis->setRange(-1.1, 1.1);

    // Интерактивность графического окна
    ui->plotter->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}


ADCDeviceWidget::~ADCDeviceWidget()
{
    delete ui;
}

void ADCDeviceWidget::setOperator(Operator *op)
{
    BaseDeviceWidget::setOperator(op);
    connection_ = op->getConnection()->clone();
    connection_->setParameter(UDPConnection::DESTINATION_PORT, QVariant(8081));
    connection_->setParameter(UDPConnection::SOURCE_PORT, QVariant(8081));
    connection_->startConnection();
}

// Возвращает данные о состоянии в виде вектора состояния
json ADCDeviceWidget::getStateToSave()
{
    return json();  // Placeholder. TODO add normal realization
}

// Восстанавливает состояние класса из вектора состояния
bool ADCDeviceWidget::restoreState(json state)
{
    return true;  // Placeholder. TODO add normal realization
}


void ADCDeviceWidget::on_plot_clicked()
{
    signal_imitation();
    ui->plotter->replot();
    ui->plotter->update();
}


void ADCDeviceWidget::on_clear_clicked()
{
    ui->plotter->graph(0)->data()->clear();
    ui->plotter->replot();
    ui->plotter->update();
}

void ADCDeviceWidget::on_start_toggled(bool checked)
{
    if(checked)
        while(ui->start->isChecked()){
            signal_imitation();
            ui->plotter->replot();
            ui->plotter->update();
            plot_delay();
            ui->plotter->graph(0)->data()->clear();
        }
    else
        emit ui->plot->clicked();
}

