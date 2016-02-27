#include "packageswindow.h"
#include "packagesmodel.h"
#include "ui_packages.h"

PackagesWindow::PackagesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Packages)
{
    ui->setupUi(this);

    int days = 1;
    int validity = 1;

    ui->packageValidity->setMinimum(1);
    ui->packageDays->setMinimum(1);
}

PackagesWindow::~PackagesWindow()
{
    delete ui;
}

void PackagesWindow::on_buttonBox_accepted()
{
    QString name, details;
    int days, validity;;

    name = ui->packageName->text();
    days = ui->packageDays->value();
    details = ui->packageDetails->toPlainText();
    validity = ui->packageValidity->value();

    if (name == "")
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("O pacote precisa de um nome!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    } else {
        emit setPackage(name, days, validity, details, true);
    }
    delete this;
}
