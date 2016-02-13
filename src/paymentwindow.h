#pragma once

#include <QDialog>
#include <QDate>
#include <QDebug>
#include <QMessageBox>
#include <QMainWindow>

#include "climber.h"

namespace Ui {
class Payment;
}

class PaymentWindow : public QDialog
{
    Q_OBJECT

public slots:
    void updateClimberInfo(Climber *&climber, bool isNewClimber);

public:
    explicit PaymentWindow(QWidget *parent = 0);
    ~PaymentWindow();
    
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_sliderPayment_valueChanged(int value);

signals:
    void setPayment(QDate date, double value);
    void setPaymentByEmail(QDate date, double value, QString email);

private:
    Ui::Payment *ui;
    QString name;
    QString email;
    bool isNew;
    QDate expirationDate;
};
