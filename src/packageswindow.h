#pragma once

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QMainWindow>

#include "package.h"

namespace Ui {
class Packages;
}

class PackagesWindow : public QDialog
{
    Q_OBJECT
public:
    explicit PackagesWindow(QWidget *parent = 0);
    ~PackagesWindow();

signals:
    void setPackage(QString name, int days, QDate validity, QString details, bool isNew);

public slots:

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Packages *ui;
};
