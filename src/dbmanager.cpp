/* CHANGES IN DB
 * enriquefynn: First model                     -v0
 * thadeuk: Added payment table                 -v1
 * enriquefynn: Added observations in climber   -v2
 * rodrigoQSaramago: Added package table        -v3
 * rodrigoQSaramago: Added package column on climber table -v4
 */

#include <QStringList>

#include "dbmanager.h"

bool DBManager::openDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QFileInfo fileInfo("vertsys.db");
    db.setDatabaseName(fileInfo.absoluteFilePath());
    bool status;
    if (!fileInfo.exists())
    {
        status = db.open();
        QSqlQuery query(db);
        qDebug() << "Creating tables" << endl;
        query.exec("CREATE TABLE climber (name VARCHAR(32), phone VARCHAR(16), address VARCHAR(40),\
                   email VARCHAR(50), expirationDate DATE, startDate DATE, status CHAR(1), observations TEXT, PRIMARY KEY (email),\
                   packageName TEXT, FOREIGN KEY(packageName) REFERENCES package(name))");
        query.exec("CREATE TABLE payment (id INTEGER PRIMARY KEY, email TEXT, paymentDate DATE, expirationDate DATE, value NUMERIC, FOREIGN KEY(email) REFERENCES climber(email))");
        query.exec("CREATE TABLE package (id INTEGER PRIMARY KEY, name UNIQUE TEXT, days NUMERIC, validity DATE, details TEXT)");
    }
    else
    {
        status = db.open();
        //Check if db is not v1
        if (!db.tables().contains("payment"))
        {
            qDebug() << "Updating to DB v1" << endl;
            QSqlQuery query(db);
            query.exec("CREATE TABLE payment (id INTEGER PRIMARY KEY, email TEXT, paymentDate DATE, expirationDate DATE, value NUMERIC, FOREIGN KEY(email) REFERENCES climber(email))");
        }
        //Check if db is not v2
        if (db.record("climber").indexOf("observations") == -1)
        {
            qDebug() << "Updating to DB v2" << endl;
            QSqlQuery query(db);
            query.exec("ALTER TABLE climber ADD COLUMN observations TEXT");
        }
        //Check if db is not v3
        if (!db.tables().contains("package"))
        {
            qDebug() << "Updating to DB v3" << endl;
            db.transaction();
            QSqlQuery query(db);
            query.exec("CREATE TABLE package (id INTEGER PRIMARY KEY, name UNIQUE TEXT, days NUMERIC, validity DATE, details TEXT)");
            query.exec("CREATE TABLE climber_package (id INTEGER PRIMARY KEY, package INTEGER, climber VARCHAR(50), days_spent INTEGER, purchase_date DATE,"
                       " FOREIGN KEY(climber) REFERENCES climber(email), FOREIGN KEY(package) REFERENCES package(id))");
            db.commit();
        }
    }
    return status;
}

QSqlError DBManager::lastError()
{
    return db.lastError();
}

DBManager::~DBManager()
{
    db.close();
}
