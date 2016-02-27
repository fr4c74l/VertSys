#include <QSqlRecord>
#include <QSqlTableModel>
#include <QDebug>
#include "packagesmodel.h"

PackagesModel::PackagesModel(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    setEditStrategy(QSqlTableModel::OnFieldChange);
}

bool PackagesModel::insertPackage(Package &package, bool isNew)
{
    QSqlRecord rec = record();
    rec.setValue("name", package.getName());
    rec.setValue("days", package.getNumberOfDays());
    rec.setValue("validity", package.getExpirationDate());
    rec.setValue("details", package.getDetails());

    bool ret = insertRecord(-1, rec);
    qDebug() << "Package inserted: " << package.getName() << endl;
    submitAll();

    return ret;
}

bool PackagesModel::removePackage(int row)
{
    bool ret = removeRows(row, 1);
    submitAll();
    return ret;
}
