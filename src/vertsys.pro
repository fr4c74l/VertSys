#-------------------------------------------------
#
# Project created by QtCreator 2014-09-27T10:38:26
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vertsys
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
    registeruser.cpp \
    dbmanager.cpp \
    tabwidget.cpp \
    climber.cpp \
    phonevalidator.cpp \
    emailvalidator.cpp \
    climbermodel.cpp \
    paymentmodel.cpp \
    paymentwindow.cpp \
    payment.cpp \
    edituser.cpp \
    reportwindow.cpp \
    datesortfilterproxymodel.cpp \
    dateformatdelegate.cpp \
    packagesmodel.cpp \
    packageswindow.cpp \
    package.cpp

HEADERS  += mainwindow.h \
    registeruser.h \
    dbmanager.h \
    tabwidget.h \
    phonevalidator.h \
    emailvalidator.h \
    climber.h \
    climbermodel.h \
    paymentmodel.h \
    paymentwindow.h \
    payment.h \
    vertsys.h \
    edituser.h \
    reportwindow.h \
    datesortfilterproxymodel.h \
    dateformatdelegate.h \
    packagesmodel.h \
    packageswindow.h \
    package.h

FORMS    += mainwindow.ui \
    registeruser.ui \
    payment.ui \
    edituser.ui \
    report.ui \
    packages.ui

RESOURCES += \
    icons.qrc

OTHER_FILES +=

DISTFILES +=
