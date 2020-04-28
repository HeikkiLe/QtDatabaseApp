#ifndef DATABASEAPP_H
#define DATABASEAPP_H

#include "chart.h"

#include <QMainWindow>

const uint16_t MEASUREMENT_DATA_AMOUNT = 16;

QT_BEGIN_NAMESPACE
namespace Ui { class DatabaseApp; }
QT_END_NAMESPACE


class DatabaseApp : public QMainWindow
{
    Q_OBJECT

public:
    DatabaseApp(QWidget *parent = nullptr);
    ~DatabaseApp();

    void paint(QPainter *painter, QPaintEvent *event, int elapsed);

private slots:
    void on_actionOpen_Connection_triggered();

    void on_actionExit_triggered();

    void on_actionPrint_Data_To_Screen_triggered();

    void on_actionCustom_Query_triggered();

signals:
    void onValueChanged(float value);

private:
    Ui::DatabaseApp *ui;

    Chart *chart;
    QChartView *chartView;

    void readToDatabase(std::array<float, MEASUREMENT_DATA_AMOUNT> &data);

    void readToChart();

};
#endif // DATABASEAPP_H
