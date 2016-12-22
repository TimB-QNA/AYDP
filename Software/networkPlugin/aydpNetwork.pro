TEMPLATE = lib
LANGUAGE = C++

CONFIG  += qt warn_on release plugin
QMAKE_CXXFLAGS += -Wno-deprecated
QT += xml network

MAIN_PROG_DIR=/home/timb/Aircraft/Software/AeroTelemetry/src/groundSoftware

DEFINES += VERSION=QString\\\(\\\"1.0-0\\\"\\\) x86

HEADERS += $$MAIN_PROG_DIR/pluginInterfaces.h \
           aydpNetwork.h \
           aydpSettings.h \
           aydpNetworkFactory.h \
           ../Library/aydpCommsProtocol.h

SOURCES += aydpNetwork.cpp \
           aydpSettings.cpp \
           aydpNetworkFactory.cpp \
           ../Library/aydpCommsProtocol.cpp

ARCH  = $$system("uname -m")
OPSYS = $$system("uname")
DESTDIR = $$MAIN_PROG_DIR/plugins
INCLUDEPATH = $$MAIN_PROG_DIR
LIBS += -lbluetooth

UI_DIR = .$$OPSYS-$$ARCH/ui
MOC_DIR = .$$OPSYS-$$ARCH/moc
OBJECTS_DIR = .$$OPSYS-$$ARCH/obj

!build_pass:message("Generating source for documentation")
!build_pass:system("doxygen doxygen.conf > /dev/null")
!build_pass:message("Building documentation")
#!build_pass:system("make -C doc/latex > /dev/null")
!build_pass:system("cp doc/latex/refman.pdf .")
!build_pass:message("Documentation is available in refman.pdf")
