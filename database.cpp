#include "database.h"


Database::Database()
{

}

void Database::ReadData()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName(connectionString);
    if(db.open())
    {
        QSqlQuery selectAll("SELECT CompanyName FROM Customers");
        while(selectAll.next())
        {
            QString CompanyName = selectAll.value(0).toString();
            qInfo() << "Value: " << CompanyName << endl;
        }
    }
    else
    {
        QString message = db.lastError().text();
        throw message;
    }

    db.close();
}

void Database::WriteData(std::array<float, MEASUREMENT_DATA> input)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName(connectionString);

    db.open();

    QSqlQuery query;
    query.prepare("INSERT INTO Temperatures (Id, Temperature, TimeOfMeasurement) VALUES (?, ?, ?)");

    if(db.isOpen())
    {
        int id = getLastId();

        for(auto &i: input)
        {
            query.addBindValue(id);

            QString s = QString::number(i);
            query.addBindValue(s);

            QDate date = QDate::currentDate();
            query.addBindValue(date);

            query.exec();

            ++id;
        }
    }
    else
    {
        QString message = query.lastError().text();
        throw message;
    }

    db.close();
}

int Database::getLastId()
{
    QSqlQuery getHighestId("SELECT MAX(Id) AS Id_MAX FROM Temperatures");

    QString id_MAX = "";
    while(getHighestId.next())
        id_MAX = getHighestId.value(0).toString();

    int id = id_MAX.toInt();
    if(id != 0)
        id += 1;

    return id;
}
