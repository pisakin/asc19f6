QT      += core
QT      += gui
QT      += xml
QT      += printsupport
QT      += charts


#!versionAtLeast(QT_VERSION, 5.12.0): {
#    QT += webenginewidgets
#    QT += webkit
#    QT += webkitwidgets
#    error("Use at least Qt version 5.11.2")
#}


greaterThan(QT_MAJOR_VERSION, 4) {
  QT += widgets
  DEFINES += HAVE_QT5
  CONFIG += c++11
} else {
  QMAKE_CXXFLAGS += -std=c++11
#  include($$PWD/qtserialport/src/serialport/qt4support/serialport.prf)
  CONFIG += serialport
  LIBS += -lserialport
}


CONFIG -= qml_debug

TARGET = ascem
TEMPLATE = app

VERSION = 0.0.1

windows: {
QMAKE_TARGET_COMPANY = Signal

QMAKE_TARGET_PRODUCT = ASCEM

QMAKE_TARGET_DESCRIPTION = Does fancy stuff

QMAKE_TARGET_COPYRIGHT = 2018

DEFINES += COPYRIGHT_STRING="\"$${QMAKE_TARGET_COPYRIGHT}\""

DEFINES += VERSION_STRING="\"$${VERSION}\""

DEFINES += LATEST_DECODABLE_ESF_VERSION="\"3.4\""
}
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../../src/ascemchart.pri)
SOURCES += main.cpp

#RESOURCES += ../../res/ascem.qrc
#RESOURCES = src/res/res.qrc
# Определение каталогов для версии Debug
CONFIG(debug, debug|release){
        message(***** Debug bulid!!! *****)
        unix: {
            MOC_DIR =           ./build/ascemchart/debug/unix/moc
            OBJECTS_DIR =       ./build/ascemchart/debug/unix/obj
            RCC_DIR =           ./build/ascemchart/debug/unix/res
            UI_HEADERS_DIR =    ./build/ascemchart/debug/unix/ui
            DESTDIR =           ./bin/debug/unix
        }
        linux: {
            MOC_DIR =           ./build/ascemchart/debug/unix/moc
            OBJECTS_DIR =       ./build/ascemchart/debug/unix/obj
            RCC_DIR =           ./build/ascemchart/debug/unix/res
            UI_HEADERS_DIR =    ./build/ascemchart/debug/unix/ui
            DESTDIR =           ./bin/debug/unix
        }
        windows: {
            MOC_DIR =           ./build/ascemchart/debug/windows/moc
            OBJECTS_DIR =       ./build/ascemchart/debug/windows/obj
            RCC_DIR =           ./build/ascemchart/debug/windows/res
            UI_HEADERS_DIR =    ./build/ascemchart/debug/windows/ui
            DESTDIR =           ./bin/debug/windows
        }
        else: {
            MOC_DIR =           ./build/ascemchart/debug/os/moc
            OBJECTS_DIR =       ./build/ascemchart/debug/os/obj
            RCC_DIR =           ./build/ascemchart/debug/os/res
            UI_HEADERS_DIR =    ./build/ascemchart/debug/os/ui
            DESTDIR =           ./bin/debug/os
        }
}

# Определение каталогов для версии Release
CONFIG(release, debug|release){
        message(***** Release build!!! *****)
        unix: {
            MOC_DIR =		./build/ascemdevice/release/unix/moc
            OBJECTS_DIR =	./build/ascemdevice/release/unix/obj
            RCC_DIR =		./build/ascemdevice/release/unix/res
            UI_HEADERS_DIR= ./build/ascemdevice/release/unix/ui
            DESTDIR =		./bin/release/unix
        }
        else: {
            MOC_DIR =		./build/ascemdevice/release/windows/moc
            OBJECTS_DIR =	./build/ascemdevice/release/windows/obj
            RCC_DIR =		./build/ascemdevice/release/windows/res
            UI_HEADERS_DIR= ./build/ascemdevice/release/windows/ui
            DESTDIR =		./bin/release/windows
        }
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

