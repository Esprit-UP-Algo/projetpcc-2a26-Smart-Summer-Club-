#-------------------------------------------------
# Project Configuration
#-------------------------------------------------
QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 6): QT += printsupport

CONFIG += c++17
CONFIG += qt warn_on release

TEMPLATE = app
TARGET = VibraClub

#-------------------------------------------------
# Include Paths
#-------------------------------------------------
INCLUDEPATH += .

#-------------------------------------------------
# Source Files
#-------------------------------------------------
SOURCES += \
    main.cpp \
    dashboardwindow.cpp \
    membermanagement.cpp \
    activitymanagement.cpp

#-------------------------------------------------
# Header Files
#-------------------------------------------------
HEADERS += \
    dashboardwindow.h \
    membermanagement.h \
    activitymanagement.h

#-------------------------------------------------
# UI Files
#-------------------------------------------------
FORMS += \
    dashboardwindow.ui \
    membermanagement.ui \
    activitymanagement.ui

#-------------------------------------------------
# Resources
#-------------------------------------------------
RESOURCES += resources.qrc

#-------------------------------------------------
# Deployment Settings
#-------------------------------------------------
# Optionally include icons or images directory
DISTFILES += \
    icons/add.png \
    icons/edit.png \
    icons/delete.png \
    icons/list.png \
    icons/members.png \
    icons/activities.png \
    icons/statistic.png \
    icons/search.png

#-------------------------------------------------
# Compiler and Build Settings
#-------------------------------------------------
QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CXXFLAGS_RELEASE += -O2
QMAKE_CXXFLAGS_DEBUG += -g

#-------------------------------------------------
# Output Directories
#-------------------------------------------------
DESTDIR = $$PWD/bin
OBJECTS_DIR = $$PWD/build/obj
MOC_DIR = $$PWD/build/moc
RCC_DIR = $$PWD/build/rcc
UI_DIR = $$PWD/build/ui

#-------------------------------------------------
# Application Icon (optional for Windows)
#-------------------------------------------------
# RC_ICONS = icons/app.ico

#-------------------------------------------------
# Notes
#-------------------------------------------------
# • Compatible with Qt 6.5+ (tested on Qt 6.7.3 MinGW)
# • You can add SQLite later by enabling: QT += sql
# • All widgets are fully editable in Qt Designer
#-------------------------------------------------
