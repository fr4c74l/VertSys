#include "paymentwindow.h"
#include "ui_payment.h"

PaymentWindow::PaymentWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Payment)
{
    ui->setupUi(this);
    expirationDate = ui->calendarWidget->selectedDate();
    ui->calendarWidget->setMinimumDate(expirationDate);
}

PaymentWindow::~PaymentWindow()
{
    delete ui;
}

void PaymentWindow::updateClimberInfo(Climber *&climber, bool isNewClimber)
{
    //TODO: get climber row here?
    name = climber->getName();
    email = climber->getEmail();
    isNew = isNewClimber;
    expirationDate = climber->getExpirationDate();
    ui->calendarWidget->setSelectedDate(expirationDate);
    ui->calendarWidget->setMaximumDate(expirationDate.addYears(1));
}

void PaymentWindow::on_buttonBox_accepted()
{
    qDebug() << "Make payment to: " << email << " and isNew: " << isNew << endl;
    if (isNew)
        emit setPaymentByEmail(ui->calendarWidget->selectedDate(), ui->valueSpin->value(), email);
    else
        emit setPayment(ui->calendarWidget->selectedDate(), ui->valueSpin->value());
    delete this;
}

void PaymentWindow::on_buttonBox_rejected()
{
    delete this;
}

void PaymentWindow::on_sliderPayment_valueChanged(int position)
{
     ui->calendarWidget->setSelectedDate(expirationDate.addMonths(position));
}
