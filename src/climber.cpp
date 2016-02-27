#include "climber.h"

Climber::Climber()
{
}

Climber::Climber(QString &name, QString &phone, QString &address, QString &email, QDate &expirationDate, QDate &startDate, QString &status, QString &observations, QString &package)
{
    this->name = name;
    this->phone = phone;
    this->address = address;
    this->email = email;
    this->expirationDate = expirationDate;
    this->startDate = startDate;
    this->status = status;
    this->observations = observations;
    this->package = package;
}
