#include "datatable.h"

#include <QtWidgets>
#include <QtSql>

//DataTable::DataTable(const QString &tableName, QWidget *parent)
//    : QWidget(parent)
//{
//    model = new QSqlTableModel(this);
//    model->setTable(tableName);
//    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    model->select();

//    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
//    model->setHeaderData(1, Qt::Horizontal, tr("First name"));
//    model->setHeaderData(2, Qt::Horizontal, tr("Last name"));

////! [0] //! [1]
//    QTableView *view = new QTableView;
//    view->setModel(model);
//    view->resizeColumnsToContents();
////! [1]

////! [2]
//    submitButton = new QPushButton(tr("Submit"));
//    submitButton->setDefault(true);
//    revertButton = new QPushButton(tr("&Revert"));
//    quitButton = new QPushButton(tr("Quit"));

//    buttonBox = new QDialogButtonBox(Qt::Vertical);
//    buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
//    buttonBox->addButton(revertButton, QDialogButtonBox::ActionRole);
//    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);
////! [2]

////! [3]
//    connect(submitButton, &QPushButton::clicked, this, &TableEditor::submit);
//    connect(revertButton, &QPushButton::clicked,  model, &QSqlTableModel::revertAll);
//    connect(quitButton, &QPushButton::clicked, this, &TableEditor::close);
////! [3]

////! [4]
//    QHBoxLayout *mainLayout = new QHBoxLayout;
//    mainLayout->addWidget(view);
//    mainLayout->addWidget(buttonBox);
//    setLayout(mainLayout);

//    setWindowTitle(tr("Cached Table"));
//}
////! [4]

////! [5]
//void DataTable::submit()
//{
//    model->database().transaction();
//    if (model->submitAll()) {
//        model->database().commit();
//    } else {
//        model->database().rollback();
//        QMessageBox::warning(this, tr("Cached Table"),
//                             tr("The database reported an error: %1")
//                             .arg(model->lastError().text()));
//    }
//}
