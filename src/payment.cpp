#include "payment.h"
#include "ui_payment.h"

Payment::Payment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Payment)
{
    ui->setupUi(this);
    expirationDate = ui->calendarWidget->selectedDate();
    ui->calendarWidget->setMinimumDate(expirationDate);
}

Payment::~Payment()
{
    delete ui;
}

void Payment::updateClimberInfo(Climber *&climber)
{
    name = climber->getName();
    expirationDate = climber->getExpirationDate();
    ui->calendarWidget->setSelectedDate(expirationDate);
    ui->calendarWidget->setMaximumDate(expirationDate.addYears(1));
}

void Payment::on_buttonBox_accepted()
{
    emit setExpirationDate(ui->calendarWidget->selectedDate());
    delete this;
}

void Payment::on_buttonBox_rejected()
{
    delete this;
}
void Payment::on_sliderPayment_sliderMoved(int position)
{
    ui->calendarWidget->setSelectedDate(expirationDate.addMonths(position));
}
