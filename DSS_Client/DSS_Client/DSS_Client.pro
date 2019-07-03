#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T09:44:16
#
#-------------------------------------------------

QT       += core gui
QT       += quickwidgets
QT       += network
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DSS_Client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
########################
### DEFINE PART
########################

DEFINES += _WIN32_WINNT=0x600
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
UI_DIR = ./.build/ui
MOC_DIR = ./.build/moc
OBJECTS_DIR = ./.build/obj
RCC_DIR = ./.build/rcc


########################
### PLATFORM PART
########################
win32:msvc{
    CONFIG +=c++11
}else{
    QMAKE_CXXFLAGS += -std=c++11
}

########################
### SRC PART
########################
SOURCES += \
        main.cpp \
        mainwindow.cpp \
    util/commonutils.cpp\
    view/rulecfgdlg.cpp \
    service/grpcclientservice.cpp \
    view/knowledgecfgdlg.cpp \
    view/flightcontroldlg.cpp \
    view/dashboard.cpp \
    proto-gen/lstm_prediction.grpc.pb.cc \
    proto-gen/lstm_prediction.pb.cc \
    view/chartdlg.cpp \
    service/flightcontrolservice.cpp \
    service/flightcontrolservice.cpp \
    service/grpcclientservice.cpp \
    util/commonutils.cpp \
    view/chartdlg.cpp \
    view/dashboard.cpp \
    view/flightcontroldlg.cpp \
    view/knowledgecfgdlg.cpp \
    view/rulecfgdlg.cpp \
    main.cpp \
    mainwindow.cpp \
    service/flightcontrolservice.cpp \
    service/grpcclientservice.cpp \
    util/commonutils.cpp \
    view/chartdlg.cpp \
    view/dashboard.cpp \
    view/flightcontroldlg.cpp \
    view/knowledgecfgdlg.cpp \
    view/rulecfgdlg.cpp \
    main.cpp \
    mainwindow.cpp \
    data/clipsstruct.cpp

# protobufs::


HEADERS += \
    ttkglobaldefine.h \
    ttkwidgettools.h \
        mainwindow.h \
    util/commonutils.h\
    view/rulecfgdlg.h \
    view/knowledgecfgdlg.h \
    view/flightcontroldlg.h \
    view/dashboard.h \
    proto-gen/lstm_prediction.grpc.pb.h \
    proto-gen/lstm_prediction.pb.h \
    view/chartdlg.h \
    service/flightcontrolservice.h \
    service/flightcontrolservice.h \
    service/grpcclientservice.h \
    util/commonutils.h \
    view/chartdlg.h \
    view/dashboard.h \
    view/flightcontroldlg.h \
    view/knowledgecfgdlg.h \
    view/rulecfgdlg.h \
    mainwindow.h \
    ttkglobaldefine.h \
    ttkwidgettools.h\
    service/flightcontrolservice.h \
    service/grpcclientservice.h \
    util/commonutils.h \
    view/chartdlg.h \
    view/dashboard.h \
    view/flightcontroldlg.h \
    view/knowledgecfgdlg.h \
    view/rulecfgdlg.h \
    mainwindow.h \
    ttkglobaldefine.h \
    ttkwidgettools.h \
    data/clipsstruct.h
# protobufs::.h


FORMS += \
        mainwindow.ui \
    view/rulecfgdlg.ui \
    view/knowledgecfgdlg.ui \
    view/flightcontroldlg.ui \
    view/dashboard.ui \
    view/chartdlg.ui


RESOURCES += \
    res.qrc
########################
### LIBS PART
########################
# ensure one "debug_and_release" in CONFIG, for clarity...
debug_and_release {
    CONFIG -= debug_and_release
    CONFIG += debug_and_release
}

# GRPC v1.15.1 MSVC2015 编译
CONFIG(debug, debug|release) {
    CONFIG -= debug release
    CONFIG += debug

    LIBS += -L$$PWD/libs/grpc_debug/ -lgpr
    PRE_TARGETDEPS += $$PWD/libs/grpc_debug/gpr.lib
    LIBS += -L$$PWD/libs/grpc_debug/ -lgrpc
    PRE_TARGETDEPS += $$PWD/libs/grpc_debug/grpc.lib
    LIBS += -L$$PWD/libs/grpc_debug/ -lgrpc++
    PRE_TARGETDEPS += $$PWD/libs/grpc_debug/grpc++.lib
    LIBS += -L$$PWD/libs/grpc_debug/ -llibprotobufd
    PRE_TARGETDEPS += $$PWD/libs/grpc_debug/libprotobufd.lib
    LIBS += -L$$PWD/libs/grpc_debug/ -laddress_sorting
    PRE_TARGETDEPS += $$PWD/libs/grpc_debug/address_sorting.lib
    LIBS += -L$$PWD/libs/grpc_debug/ -lcares
    PRE_TARGETDEPS += $$PWD/libs/grpc_debug/cares.lib
    LIBS += -L$$PWD/libs/grpc_debug/ -lssl
    PRE_TARGETDEPS += $$PWD/libs/grpc_debug/ssl.lib
    LIBS += -L$$PWD/libs/grpc_debug/ -lcrypto
    PRE_TARGETDEPS += $$PWD/libs/grpc_debug/crypto.lib
    LIBS += -L$$PWD/libs/grpc_debug/ -lzlibd
    PRE_TARGETDEPS += $$PWD/libs/grpc_debug/zlibd.lib

    LIBS += -L$$PWD/libs/grpc_debug/ -lzlibstaticd
    PRE_TARGETDEPS += $$PWD/libs/grpc_debug/zlibstaticd.lib
    LIBS += -lWs2_32 -ladvapi32

    INCLUDEPATH += $$PWD/include
}
CONFIG(release, debug|release) {
    CONFIG -= debug release
    CONFIG += release

    LIBS += -L$$PWD/libs/grpc_release/ -lgpr
    PRE_TARGETDEPS += $$PWD/libs/grpc_release/gpr.lib
    LIBS += -L$$PWD/libs/grpc_release/ -lgrpc
    PRE_TARGETDEPS += $$PWD/libs/grpc_release/grpc.lib
    LIBS += -L$$PWD/libs/grpc_release/ -lgrpc++
    PRE_TARGETDEPS += $$PWD/libs/grpc_release/grpc++.lib
    LIBS += -L$$PWD/libs/grpc_release/ -llibprotobuf
    PRE_TARGETDEPS += $$PWD/libs/grpc_release/libprotobuf.lib
    LIBS += -L$$PWD/libs/grpc_release/ -laddress_sorting
    PRE_TARGETDEPS += $$PWD/libs/grpc_release/address_sorting.lib
    LIBS += -L$$PWD/libs/grpc_release/ -lcares
    PRE_TARGETDEPS += $$PWD/libs/grpc_release/cares.lib
    LIBS += -L$$PWD/libs/grpc_release/ -lssl
    PRE_TARGETDEPS += $$PWD/libs/grpc_release/ssl.lib
    LIBS += -L$$PWD/libs/grpc_release/ -lcrypto
    PRE_TARGETDEPS += $$PWD/libs/grpc_release/crypto.lib
    LIBS += -L$$PWD/libs/grpc_release/ -lzlibstatic
    LIBS += -L$$PWD/libs/grpc_release/ -lzlib
    PRE_TARGETDEPS += $$PWD/libs/grpc_release/zlib.lib
    PRE_TARGETDEPS += $$PWD/libs/grpc_release/zlibstatic.lib
    LIBS += -lWs2_32 -ladvapi32


    INCLUDEPATH += $$PWD/include
}




include(Meter/Meter.pri)


########################
### INSTALL PART
########################
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/statemachine/trafficlight  # indicator change state machine @ref http://doc.qt.io/qt-5/qtwidgets-statemachine-trafficlight-trafficlight-pro.html
target.path = $$[QT_INSTALL_EXAMPLES]/charts/linechart
INSTALLS += target
