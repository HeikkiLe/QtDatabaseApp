#include "databaseapp.h"
#include "ui_databaseapp.h"
#include "serial.h"
#include "database.h"
#include "chart.h"

#include <QMessageBox>
#include <QtConcurrent>
#include <QThread>
#include <QInputDialog>


DatabaseApp::DatabaseApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DatabaseApp)
{
    ui->setupUi(this);

    chart = new Chart();

    chartView = new QChartView(chart->printChart());
    chartView->setRenderHint(QPainter::Antialiasing);

    this->setCentralWidget(chartView);

    QObject::connect(this, &DatabaseApp::onValueChanged, chart, &Chart::onValueChanged);
}

DatabaseApp::~DatabaseApp()
{
    delete chart;
    delete chartView;
    delete ui;
}

void DatabaseApp::on_actionOpen_Connection_triggered()
{
    std::array<float, MEASUREMENT_DATA_AMOUNT> finalData;

    std::unique_ptr<Database> database = std::make_unique<Database>();

    //QFuture<void> future = QtConcurrent::run(this, &DatabaseApp::readToDatabase, &finalData);
    readToDatabase(finalData);

    try
    {
        database->WriteData(finalData);
    }
    catch (std::exception e)
    {
        QString message = "Error! ";
        message += e.what();
        QMessageBox::critical(this, "Error", message);
    }

    //database->ReadData();
}

void DatabaseApp::on_actionPrint_Data_To_Screen_triggered()
{
    // read COM port in a separate thread to prevent GUI blocking
    QFuture<void> future = QtConcurrent::run(this, &DatabaseApp::readToChart);
}

void DatabaseApp::on_actionCustom_Query_triggered()
{
    bool ok;
    QString query = QInputDialog::getText(this, tr("Custom Query"),
                                          tr("Give query or leave empty for default:"), QLineEdit::Normal,
                                          "query", &ok);

    if(ok)
    {
        std::unique_ptr<Database> database = std::make_unique<Database>();
        try
        {
            database->ReadData(query);
        }
        catch (std::exception e)
        {
            QString message = "Error! ";
            message += e.what();
            QMessageBox::critical(this, "Error", message);
        }
    }
}

void DatabaseApp::on_actionExit_triggered()
{
    QApplication::quit();
}

void DatabaseApp::readToDatabase(std::array<float, MEASUREMENT_DATA_AMOUNT> &data)
{
    std::unique_ptr<Serial> SP(new Serial(L"COM3"));

    char incomingData[256] = "";

    int dataLength = 256;
    int readResult = 0;
    int validDataAmount = 0;

    float temp = 0.f;

    while(validDataAmount < MEASUREMENT_DATA_AMOUNT)
    {
        readResult = SP->ReadData(incomingData, dataLength);

        qInfo("Bytes read: (0 means no data available) %i\n", readResult);
        incomingData[readResult] = 0;

        temp = atof(incomingData);

        try
        {
            if(incomingData[0] != '\0')
            {
                data.at(validDataAmount) = temp;

                qInfo() << "char: " << incomingData;

                ++validDataAmount;
            }
        }
        catch(std::out_of_range e)
        {
            qCritical() << "DatabaseApp::on_actionOpen_Connection_triggered : " << e.what();
        }

        Sleep(500);
    }
}

void DatabaseApp::readToChart()
{
    std::unique_ptr<Serial> SP = std::make_unique<Serial>(L"COM3");

    char incomingData[256] = "";
    char *databufferPtr = incomingData;

    unsigned int dataLength = 256;
    int readResult = 0;

    float tempValue = 0.f;

    int i = 0;
    do
    {
        readResult = SP->ReadData(incomingData, dataLength);

        qInfo("Bytes read: (0 means no data available) %i\n", readResult);
        incomingData[readResult] = 0;

        if(incomingData[0] != '\0')
        {
            qInfo() << "char: " << incomingData;

            tempValue = atof(incomingData);
        }

        //tempValue = (float)i;

        emit onValueChanged(tempValue);

        i++;

        QThread::sleep(1);
    }
    while(i < 15);
}
