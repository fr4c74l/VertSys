#pragma once

#include <QSqlRelationalTableModel>
#include "package.h"

class PackagesModel : public QSqlRelationalTableModel
{
public:
    PackagesModel(QObject *parent);
    bool insertPackage(Package &package, bool isNew);
    bool removePackage(int row);
};
