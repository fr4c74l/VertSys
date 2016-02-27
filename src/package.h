#pragma once

#include <QDate>

namespace PackageFields
{
    const int name = 1;
    const int days = 2;
    const int validity = 3;
    const int details = 4;
}

class Package
{
    QString name;
    int days;
    int validity;
    QString details;

public:
    Package(QString name, int days, int validity, QString details);
    inline QString getName() {return name;}
    inline int getNumberOfDays() {return days;}
    inline int getPackageValidity() { return validity;}
    inline QString getDetails() {return details;}
};
