TEMPLATE        = app
LANGUAGE        = C++

QT -= gui
QT += xml network
CONFIG  += qt warn_on release
DEFINES += x86

HEADERS += dataStore.h \
           imuReader.h \
           dataCollector.h \
           logOutput.h \
           maestro.h \
           calibration.h \
           pidControl.h \
           ../../Library/SerialIO_linux.h \
           nmea.h \
           commsLink.h \
           display.h \
           eventLoop.h \
           route.h \
           point.h

SOURCES += main.cpp \
           dataStore.cpp \
           imuReader.cpp \
           dataCollector.cpp \
           logOutput.cpp \
           maestro.cpp \
           calibration.cpp \
           pidControl.cpp \
           ../../Library/SerialIO_linux.cpp \
           nmea.cpp \
           commsLink.cpp \
           display.cpp \
           eventLoop.cpp \
           route.cpp \
           point.cpp

unix{
  ARCH  = $$system("uname -m")
  OPSYS = $$system("uname")
}

win32{
  DEFINES += _SECURE_SCL=0 _HAS_ITERATOR_DEBUGGING=0 _CRT_SECURE_NO_WARNINGS
  ARCH     = $$(PROCESSOR_ARCHITECTURE)
  OPSYS    = $$(OS)
}

#RTIMU library elements...
INCLUDEPATH += ../RTIMULib/RTIMULib
LIBS += ../RTIMULib/RTIMULib/lib-$$OPSYS-$$ARCH/librtimu.a

#Maestro servo controller support
LIBS += -lusb-1.0

DESTDIR     = bin-$$OPSYS-$$ARCH/
UI_DIR      = .$$OPSYS-$$ARCH/ui
MOC_DIR     = .$$OPSYS-$$ARCH/moc
OBJECTS_DIR = .$$OPSYS-$$ARCH/obj 
