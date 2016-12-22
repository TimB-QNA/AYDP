TEMPLATE        = app
LANGUAGE        = C++

QT -= gui
QT += xml network
CONFIG  += qt warn_on release
DEFINES += x86

HEADERS += ../dataStore.h \
           ../dataCollector.h \
           ../logOutput.h \
           eventLoop.h \
           ../gpsReader.h

SOURCES += main.cpp \
           ../dataStore.cpp \
           ../dataCollector.cpp \
           ../logOutput.cpp \
           ../gpsReader.cpp \
           eventLoop.cpp

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
