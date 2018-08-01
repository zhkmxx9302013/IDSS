#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T09:44:16
#
#-------------------------------------------------

QT       += core gui
QT       += quickwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DSS_Client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    util/commonutils.cpp\
    view/rulecfgdlg.cpp \
    proto-gen/clips_facts.grpc.pb.cc \
    proto-gen/clips_facts.pb.cc \
    proto-gen/comm_link.grpc.pb.cc \
    proto-gen/comm_link.pb.cc \
    proto-gen/dss.grpc.pb.cc \
    proto-gen/dss.pb.cc \
    proto-gen/flight_control.grpc.pb.cc \
    proto-gen/flight_control.pb.cc \
    service/grpcclientservice.cpp \
    proto-gen/clips_facts.grpc.pb.cc \
    proto-gen/clips_facts.pb.cc \
    proto-gen/comm_link.grpc.pb.cc \
    proto-gen/comm_link.pb.cc \
    proto-gen/dss.grpc.pb.cc \
    proto-gen/dss.pb.cc \
    proto-gen/file.grpc.pb.cc \
    proto-gen/file.pb.cc \
    proto-gen/flight_control.grpc.pb.cc \
    proto-gen/flight_control.pb.cc \
    view/knowledgecfgdlg.cpp \
    view/flightcontroldlg.cpp



HEADERS += \
        mainwindow.h \
    util/commonutils.h\
    view/rulecfgdlg.h \
    proto-gen/clips_facts.grpc.pb.h \
    proto-gen/clips_facts.pb.h \
    proto-gen/comm_link.grpc.pb.h \
    proto-gen/comm_link.pb.h \
    proto-gen/dss.grpc.pb.h \
    proto-gen/dss.pb.h \
    proto-gen/flight_control.grpc.pb.h \
    proto-gen/flight_control.pb.h \
    service/grpcclientservice.h \
    proto-gen/clips_facts.grpc.pb.h \
    proto-gen/clips_facts.pb.h \
    proto-gen/comm_link.grpc.pb.h \
    proto-gen/comm_link.pb.h \
    proto-gen/dss.grpc.pb.h \
    proto-gen/dss.pb.h \
    proto-gen/file.grpc.pb.h \
    proto-gen/file.pb.h \
    proto-gen/flight_control.grpc.pb.h \
    proto-gen/flight_control.pb.h \
    view/knowledgecfgdlg.h \
    view/flightcontroldlg.h


FORMS += \
        mainwindow.ui \
    view/rulecfgdlg.ui \
    view/knowledgecfgdlg.ui \
    view/flightcontroldlg.ui


LIBS += -L$$PWD/libs/grpc_release/ -lgpr
PRE_TARGETDEPS += $$PWD/libs/grpc_release/gpr.lib
LIBS += -L$$PWD/libs/grpc_release/ -lgrpc
PRE_TARGETDEPS += $$PWD/libs/grpc_release/grpc.lib
LIBS += -L$$PWD/libs/grpc_release/ -lgrpc++
PRE_TARGETDEPS += $$PWD/libs/grpc_release/grpc++.lib
LIBS += -L$$PWD/libs/grpc_release/ -llibprotobuf
PRE_TARGETDEPS += $$PWD/libs/grpc_release/libprotobuf.lib

LIBS += -L$$PWD/libs/grpc_release/ -lssl
PRE_TARGETDEPS += $$PWD/libs/grpc_release/ssl.lib
LIBS += -L$$PWD/libs/grpc_release/ -lcrypto
PRE_TARGETDEPS += $$PWD/libs/grpc_release/crypto.lib
LIBS += -L$$PWD/libs/grpc_release/ -ldecrepit
PRE_TARGETDEPS += $$PWD/libs/grpc_release/decrepit.lib

LIBS += -L$$PWD/libs/grpc_release/ -lzlibstatic
PRE_TARGETDEPS += $$PWD/libs/grpc_release/zlibstatic.lib
LIBS += -lWs2_32 -ladvapi32

INCLUDEPATH += $$PWD/include

DEFINES += _WIN32_WINNT=0x600

RESOURCES += \
    res.qrc
