TEMPLATE        = app
LANGUAGE        = C++

QT -= gui
QT += xml network
CONFIG  += qt warn_on debug
DEFINES += x86

HEADERS += ../../Vessel/src/controlLoop.h \
           ../../Vessel/src/pidControl.h \
           ../../Vessel/src/logOutput.h


SOURCES += main.cpp \
           ../../Vessel/src/controlLoop.cpp \
           ../../Vessel/src/pidControl.cpp \
           ../../Vessel/src/logOutput.cpp

unix{
  ARCH  = $$system("uname -m")
  OPSYS = $$system("uname")
}

win32{
  DEFINES += _SECURE_SCL=0 _HAS_ITERATOR_DEBUGGING=0 _CRT_SECURE_NO_WARNINGS
  ARCH     = $$(PROCESSOR_ARCHITECTURE)
  OPSYS    = $$(OS)
}

DESTDIR     = bin-$$OPSYS-$$ARCH/
UI_DIR      = .$$OPSYS-$$ARCH/ui
MOC_DIR     = .$$OPSYS-$$ARCH/moc
OBJECTS_DIR = .$$OPSYS-$$ARCH/obj 
