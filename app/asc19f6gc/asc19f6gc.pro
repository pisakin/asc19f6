QT      += core
QT      += gui
QT      += xml
QT      += printsupport
QT      += charts

linux: {
greaterThan(QT_VERSION, 5.12.0): {
    QT += webenginewidgets
    QT += webkit
    QT += webkitwidgets
    message("Use at least Qt version 5.12.0")
}
}

greaterThan(QT_MAJOR_VERSION, 4) {
  QT += widgets serialport serialbus
  DEFINES += HAVE_QT5
  CONFIG += c++11

# customplot
  linux: {
  DEFINES += QCUSTOMPLOT_USE_LIBRARY
  DEFINES += QCUSTOMPLOT_USE_OPENGL
  LIBS += -lQCustomPlot
  #include($$PWD/../../qcustomplot/qcustomplot.pri)
  }

  mac: {
#    DEFINES += QCUSTOMPLOT_USE_LIBRARY
#    DEFINES += QCUSTOMPLOT_USE_OPENGL
#    LIBS += -framework customplot
  }
  windows: {
    DEFINES += QCUSTOMPLOT_USE_COMPILE
    include($$PWD/../../qcustomplot/qcustomplot.pri)
  }

} else {
  QMAKE_CXXFLAGS += -std=c++11
#  include($$PWD/qtserialport/src/serialport/qt4support/serialport.prf)
  CONFIG += serialport
  LIBS += -lserialport
}

#qwt
  linux: {
  CONFIG += qwt
#  LIBS += -lqwt
#  LIBS += -L$${QWT_LOCATION}/lib/qwt
#  LIBS += -L$${QWT_LOCATION}/lib/libqwt

}
#mac: { LIBS += -framework qwt }

mac: {
#INCLUDEPATH += /opt/homebrew/include
#LIBS += -L/opt/homebrew/lib
}

CONFIG -= qml_debug

TARGET = asc19f6gc
TEMPLATE = app

#CONFIG += precompile_header
#PRECOMPILED_HEADER = precompiled.h

#CONFIG += precompile_header
#PRECOMPILED_HEADER = precompiled.h

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include($$PWD/../../src/asc19f6gc.pri)
#SOURCES += $$PWD/app/ascgbmcustom/main.cpp
SOURCES += main.cpp
#RESOURCES += $$PWD/../../res/ascem.qrc

# Определение каталогов для версии Debug
CONFIG(debug, debug|release){
        message(***** Debug bulid!!! *****)
        unix: {
            MOC_DIR =           ./build/asc19f6gc/debug/unix/moc
            OBJECTS_DIR =       ./build/asc19f6gc/debug/unix/obj
            RCC_DIR =           ./build/asc19f6gc/debug/unix/res
            UI_HEADERS_DIR =    ./build/asc19f6gc/debug/unix/ui
            DESTDIR =           ./bin/debug/unix
        } linux: {
            MOC_DIR =           ./build/asc19f6gc/debug/unix/moc
            OBJECTS_DIR =       ./build/asc19f6gc/debug/unix/obj
            RCC_DIR =           ./build/asc19f6gc/debug/unix/res
            UI_HEADERS_DIR =    ./build/asc19f6gc/debug/unix/ui
            DESTDIR =           ./bin/debug/unix
        } windows: {
            MOC_DIR =           ./build/asc19f6gc/debug/windows/moc
            OBJECTS_DIR =       ./build/asc19f6gc/debug/windows/obj
            RCC_DIR =           ./build/asc19f6gc/debug/windows/res
            UI_HEADERS_DIR =    ./build/asc19f6gc/debug/windows/ui
            DESTDIR =           ./bin/debug/windows
        } else: {
            MOC_DIR =           ./build/asc19f6gc/debug/os/moc
            OBJECTS_DIR =       ./build/asc19f6gc/debug/os/obj
            RCC_DIR =           ./build/asc19f6gc/debug/os/res
            UI_HEADERS_DIR =    ./build/asc19f6gc/debug/os/ui
            DESTDIR =           ./bin/debug/os
        }
}

# Определение каталогов для версии Release
CONFIG(release, debug|release){
        message(***** Release build!!! *****)
        unix: {
            MOC_DIR =           ./build/asc19f6gc/release/unix/moc
            OBJECTS_DIR =       ./build/asc19f6gc/release/unix/obj
            RCC_DIR =           ./build/asc19f6gc/release/unix/res
            UI_HEADERS_DIR =    ./build/asc19f6gc/release/unix/ui
            DESTDIR =           ./bin/release/unix
        } else: {
            MOC_DIR =           ./build/asc19f6gc/release/windows/moc
            OBJECTS_DIR =       ./build/asc19f6gc/release/windows/obj
            RCC_DIR =           ./build/asc19f6gc/release/windows/res
            UI_HEADERS_DIR =    ./build/asc19f6gc/release/windows/ui
            DESTDIR =           ./bin/release/windows
        }
}


DISTFILES +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


windows: {
QMAKE_TARGET_COMPANY = Signal
QMAKE_TARGET_PRODUCT = asc19f6gc Custom
QMAKE_TARGET_DESCRIPTION = Does fancy stuff
QMAKE_TARGET_COPYRIGHT = 2023
DEFINES += COPYRIGHT_STRING="\"$${QMAKE_TARGET_COPYRIGHT}\""
DEFINES += VERSION_STRING="\"$${VERSION}\""
DEFINES += LATEST_DECODABLE_ESF_VERSION="\"3.4\""
#RC_FILE = $$PWD/../../res/ascvn.qrc
win32: RC_ICONS = $$PWD/../../res/logo/favicon.ico
}
