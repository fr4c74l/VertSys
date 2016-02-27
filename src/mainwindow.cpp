#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(updateFilter(QString)),
        ui->tabWidget, SLOT(updateFilter(QString)), Qt::UniqueConnection);

    connect(this, SIGNAL(insertClimberInDB(Climber *&)),
        ui->tabWidget, SLOT(insertClimberInDB(Climber *&)), Qt::UniqueConnection);

    connect(this, SIGNAL(editClimberInDB(int, Climber *&)),
        ui->tabWidget, SLOT(editClimberInDB(int, Climber *&)), Qt::UniqueConnection);

    connect(this, SIGNAL(removeClimber()),
        ui->tabWidget, SLOT(removeClimber()), Qt::UniqueConnection);

    connect(this, SIGNAL(toggleActivity()),
        ui->tabWidget, SLOT(toggleActivity()), Qt::UniqueConnection);

    connect(this, SIGNAL(updateClimberInfo()),
        ui->tabWidget, SLOT(updateClimberInfo()), Qt::UniqueConnection);        

    connect(this, SIGNAL(exportEmails()),
        ui->tabWidget, SLOT(exportClimbersEmails()), Qt::UniqueConnection);

    connect(this, SIGNAL(getClimberByEmail(QString)),
        ui->tabWidget, SLOT(getClimberByEmail(QString)), Qt::UniqueConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Climber_triggered()
{
    ru = new RegisterUser(this);
    ru->show();
}

void MainWindow::on_lineEdit_search_textChanged(const QString &str)
{
    emit updateFilter(str);
}

void MainWindow::insertClimber(Climber *&climber)
{
    emit insertClimberInDB(climber);
}

void MainWindow::editClimber(int row, Climber *&climber)
{
    emit editClimberInDB(row, climber);
}

void MainWindow::displayClimberInfo(int row, Climber* climber)
{
    eu = new EditUser(row, climber, this);
    eu->show();
}

void MainWindow::on_actionRemove_Climber_triggered()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText("Deseja realmente apagar o escalador?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes)
        emit removeClimber();
}

void MainWindow::rowSelected(QModelIndex x, QModelIndex y)
{
    Q_UNUSED(y);
    if (x.isValid())
        ui->actionRemove_Climber->setEnabled(true);
    else
        ui->actionRemove_Climber->setEnabled(false);
}

void MainWindow::on_actionToggleActivity_Climber_triggered()
{
    emit toggleActivity();
}

void MainWindow::on_actionPay_Climber_triggered()
{
    payment = new PaymentWindow(this);

    connect(this, SIGNAL(updateClimberInfo(Climber *&, bool)),
            payment, SLOT(updateClimberInfo(Climber *&, bool)), Qt::UniqueConnection);

    connect(payment, SIGNAL(setPayment(QDate, double)),
            ui->tabWidget, SLOT(setPayment(QDate, double)), Qt::UniqueConnection);

    emit updateClimberInfo();
    payment->show();
}

void MainWindow::setPaymentNewClimber(Climber *&c)
{
    payment = new PaymentWindow(this);

    connect(this, SIGNAL(updateClimberInfo(Climber *&, bool)),
            payment, SLOT(updateClimberInfo(Climber *&, bool)), Qt::UniqueConnection);

    connect(payment, SIGNAL(setPaymentByEmail(QDate, double, QString)),
            ui->tabWidget, SLOT(setPaymentByEmail(QDate, double, QString)), Qt::UniqueConnection);

    emit updateClimberInfo(c, true);
    payment->show();
}

void MainWindow::recvClimberInfo(Climber *&climber)
{
    emit updateClimberInfo(climber, false);
}

void MainWindow::updateActivateOption(int idx)
{
    ui->actionToggleActivity_Climber->setEnabled(true);
    if (idx == 0)
        ui->actionToggleActivity_Climber->setText(tr("Inativar"));
    else if (idx == 1)
        ui->actionToggleActivity_Climber->setEnabled(false);
    else
        ui->actionToggleActivity_Climber->setText(tr("Ativar"));
}

void MainWindow::on_actionExport_triggered()
{
    QString DBName = QFileDialog::getSaveFileName(this, tr("Salvar como..."), QString(), tr("DB (*.db)"));
    if (DBName == NULL)
        return;
    if (!(DBName.endsWith(".db", Qt::CaseInsensitive)))
            DBName += ".db";
    QMessageBox msgBox;
    if (QFile::copy("vertsys.db", DBName))
    {
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Banco de dados exportado com sucesso!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
    }
    else
    {
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Nao foi possivel exportar o banco de dados!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
    }
    msgBox.exec();
}

void MainWindow::on_actionImport_triggered()
{
    QString DBName = QFileDialog::getOpenFileName(this, tr("Abrir"), QString(), tr("DB (*.db)"));
    if (DBName == NULL)
        return;
    QString DBPath = QDir::currentPath() + "/vertsys.db";
    if (DBName == DBPath)
        return;

    if (!(DBName.endsWith(".db", Qt::CaseInsensitive)))
            DBName += ".db";
    QMessageBox msgBox;

    QFile::remove(DBPath);
    if (QFile::copy(DBName, DBPath))
    {
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Banco de dados importado com sucesso!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        qApp->exit(MainWindow::EXIT_CODE_REBOOT);
    }
    else
    {
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Nao foi possivel importar o banco de dados!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
    }
    msgBox.exec();
}

// FIXME: When remove a climber don't remove his payment information
void MainWindow::on_actionMake_Report_triggered()
{
    report = new ReportWindow(this);
    report->show();
}

void MainWindow::on_actionExportEmail_triggered()
{
    emit exportEmails();
}

void MainWindow::on_actionPackages_triggered()
{
    packages = new PackagesWindow(this);

    connect(packages, SIGNAL(setPackage(QString, int, QDate, QString,bool)),
            ui->tabWidget, SLOT(setPackage(QString, int, QDate, QString,bool)), Qt::UniqueConnection);

    packages->show();
}
