#include "registeruser.h"
#include "ui_registeruser.h"
#include "mainwindow.h"

RegisterUser::RegisterUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterUser)
{
    ui->setupUi(this);
    //ui->dateEdit->setDate(QDate::currentDate());
    ui->comboBox_package->currentText();
    ui->dateEdit_Start->setDate(QDate::currentDate());

    phoneValidator = new PhoneValidator();
    emailValidator = new EmailValidator();

    ui->lineEdit_Phone->setValidator(phoneValidator);
    ui->lineEdit_Email->setValidator(emailValidator);

    connect(this, SIGNAL(insertClimber(Climber*&)),
            static_cast<QMainWindow*>(parent), SLOT(insertClimber(Climber*&)), Qt::UniqueConnection);
}

RegisterUser::~RegisterUser()
{
    delete phoneValidator;
    delete emailValidator;
    delete ui;
}

void RegisterUser::on_buttonBox_rejected()
{
    delete this;
}


void RegisterUser::on_buttonBox_accepted()
{
    QString name, phone, address, email, status, observations, package;
    QDate expirationDate, startDate;
    email = ui->lineEdit_Email->text();
    //Validate Email
    if (!EmailValidator::isValid(email))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Email invalido!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        //Validate Phone
        phone = ui->lineEdit_Phone->text();
        if (!PhoneValidator::isValid(phone))
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("Telefone invalido!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
        else
        {
            name = ui->lineEdit_Name->text();
            address = ui->lineEdit_Addr->text();
            observations = ui->observationsTextEdit->toPlainText();

            //expirationDate = ui->dateEdit->date();
            //TODO add combo_box-package
            startDate = ui->dateEdit_Start->date();
            int comboIdx = ui->comboBox->currentIndex();
            if (!comboIdx)
                status = "A";
            else
                status = "D";
            int hasPackage = ui->comboBox_package->currentIndex();
            if(!hasPackage)
                package = "teste";
            else
                package = "";
            Climber *c = new Climber(name, phone, address, email, expirationDate, startDate, status, observations, package);
            emit insertClimber(c);
            delete this;
        }
    }
}

void RegisterUser::editaccept()
{
    emit editsave();
}
