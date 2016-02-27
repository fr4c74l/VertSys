#include "package.h"

Package::Package(QString name, int days, QDate validity, QString details)
{
    this->name = name;
    this->days = days;
    this->validity = validity;
    this->details = details;
}
