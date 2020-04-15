#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Chart : public QChart /*public QWidget*/
{
    Q_OBJECT

public:
    Chart();
    virtual ~Chart();

    QChart *printChart();

public slots:
    void onValueChanged(float value);

private:
    int seriesValues;

    QChart *chart;

    QLineSeries *series;
    QValueAxis *xAxis;
    QValueAxis *yAxis;

};

#endif // CHART_H
