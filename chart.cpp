#include "chart.h"


Chart::Chart() :
    xAxis(new QValueAxis()),
    yAxis(new QValueAxis())
{
    series = new QLineSeries();

    chart = new QChart();
}

Chart::~Chart()
{
    delete series;

    delete chart;
}

QChart *Chart::printChart()
{
    chart->legend()->hide();
    chart->addSeries(series);
    chart->addAxis(xAxis, Qt::AlignBottom);
    chart->addAxis(yAxis, Qt::AlignLeft);

    series->attachAxis(xAxis);
    series->attachAxis(yAxis);

    yAxis->setRange(-25, 35);
    xAxis->setMin(0);
    xAxis->setTickType(QValueAxis::TickType::TicksFixed);
    xAxis->setTickCount(5);
    //chart->createDefaultAxes();
    chart->setTitle("Temperatures");
    chart->setAnimationOptions(QChart::AllAnimations);

    return chart;
}

void Chart::onValueChanged(float value)
{
    series->append(seriesValues, value);

    qreal xScrollAmount = chart->plotArea().width() / xAxis->tickCount();

    chart->scroll(xScrollAmount, 0);

    seriesValues += 1;
}
