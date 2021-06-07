QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

LIBS+=\
    -L/usr/local/lib -lprotobuf


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    src/home.ui

DISTFILES += \
    include/proto/compile.sh \
    include/proto/grSim_Commands.proto \
    include/proto/grSim_Packet.proto \
    include/proto/grSim_Replacement.proto

HEADERS += \
    include/grSim_Commands.pb.h \
    include/grSim_Packet.pb.h \
    include/grSim_Replacement.pb.h \
    src/grsimcomm.h \
    src/home.h \
    src/packet.h

SOURCES += \
    include/grSim_Commands.pb.cc \
    include/grSim_Packet.pb.cc \
    include/grSim_Replacement.pb.cc \
    src/grsimcomm.cpp \
    src/home.cpp \
    src/main.cpp
