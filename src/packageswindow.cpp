#include "packageswindow.h"
#include "packagesmodel.h"
#include "ui_packages.h"

PackagesWindow::PackagesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Packages)
{
    ui->setupUi(this);

    int days = 1;
    QDate validity = QDate::currentDate();

    ui->packageValidity->setDate(validity);
    ui->packageDays->setMinimum(1);
}

PackagesWindow::~PackagesWindow()
{
    delete ui;
}

void PackagesWindow::on_buttonBox_accepted()
{
    QString name, details;
    QDate validity;
    int days;

    name = ui->packageName->text();
    days = ui->packageDays->value();
    details = ui->packageDetails->toPlainText();
    validity = ui->packageValidity->date();

    emit setPackage(name, days, validity, details, true);

    delete this;
}
