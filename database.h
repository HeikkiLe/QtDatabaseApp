#ifndef DATABASE_H
#define DATABASE_H

#include <array>

#include <QtSql>
#include <QDate>


const uint16_t MEASUREMENT_DATA = 16;

class Database
{
public:
    Database();

    void ReadData();

    void WriteData(const std::array<float, MEASUREMENT_DATA> input);

    int getLastId();

    uint16_t getMeasurementDataAmount();

private:
    const QString connectionString = "Driver={SQL Server Native Client 11.0};"
            "Server=(localdb)\\MSSQLLocalDB;"
            "Database=C:\\Users\\Hese\\source\\repos\\WindowsFormsApp1\\WindowsFormsApp1\\Lukkari_local.mdf";

};

#endif // DATABASE_H
