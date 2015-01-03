TEMPLATE = lib
LANGUAGE = C++

CONFIG  += qt warn_on release plugin
QMAKE_CXXFLAGS += -Wno-deprecated
QT += xml network

MAIN_PROG_DIR=/home/timb/Aircraft/Software/AeroTelemetry/src/groundSoftware

DEFINES += VERSION=QString\\\(\\\"1.0-0\\\"\\\) x86 TOLERANCE=1e-9

HEADERS += $$MAIN_PROG_DIR/pluginInterfaces.h \
           $$MAIN_PROG_DIR/telemetryDataPoint.h \
           $$MAIN_PROG_DIR/odPoint.h \
           aydpPlugin.h \
           aydpSettings.h \
           aydpPluginFactory.h \
           aydpDockWidget.h \
           ../Vessel/src/dataStore.h

SOURCES += $$MAIN_PROG_DIR/telemetryDataPoint.cpp \
           $$MAIN_PROG_DIR/odPoint.cpp \
           aydpPlugin.cpp \
           aydpSettings.cpp \
           aydpPluginFactory.cpp \
           aydpDockWidget.cpp \
           ../Vessel/src/dataStore.cpp

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
!build_pass:system("make -C doc/latex > /dev/null")
!build_pass:system("cp doc/latex/refman.pdf .")
!build_pass:message("Documentation is available in refman.pdf")
