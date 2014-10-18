#include <QBrush>
#include <QtDebug>
#include <QSqlRecord>
#include <QTimer>
#include "model.h"

MyModel::MyModel(QObject *parent) :
    QSqlTableModel(parent)
{

}

void MyModel::update()
{
    qDebug() << "Updating..." << endl;
    emit layoutChanged();
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (index.column() == 4)
    {
        QDate value = QDate::fromString(QSqlQueryModel::data(index, Qt::DisplayRole).toString(), "yyyy-MM-dd");
        switch(role)
        {
            case Qt::DisplayRole:
                return value;

            case Qt::BackgroundRole:
                QDate today = QDate::currentDate();
                if (today >= value)
                {
                    QBrush redBackground(Qt::red);
                    return redBackground;
                }
                break;
        }
    }
    if (role == Qt::DisplayRole)
        return QSqlTableModel::data(index,role);
    return QVariant();
}

bool MyModel::insertClimber(Climber *&climber)
{
    emit layoutAboutToBeChanged();
    QSqlRecord rec = record();
    rec.setValue("name", climber->getName());
    rec.setValue("phone", climber->getPhone());
    rec.setValue("address", climber->getAddress());
    rec.setValue("email", climber->getEmail());
    rec.setValue("expirationDate", climber->getExpirationDate());
    rec.setValue("startDate", climber->getStartDate());
    rec.setValue("status", climber->getStatus());
    bool ret = insertRowIntoTable(rec);
    qDebug() << "INSERTED: " << ret << endl;
    emit layoutChanged();
    return ret;
}
