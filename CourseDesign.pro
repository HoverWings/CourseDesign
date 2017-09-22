QT  += core gui
QT  += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CourseDesign
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    newRoute.cpp \
    PersonalTrip.cpp \
    newDayInfo.cpp \
    newDayEXPInfo.cpp

HEADERS += \
        mainwindow.h \
    newRoute.h \
    Personaltrip.h \
    newDayInfo.h \
    newDayEXPInfo.h

FORMS += \
        mainwindow.ui \
    newRoute.ui \
    newDayInfo.ui \
    newDayEXPInfo.ui



