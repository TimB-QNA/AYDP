TEMPLATE        = app
LANGUAGE        = C++

QT += xml network
CONFIG  += qt warn_on debug
DEFINES += x86

HEADERS += ../Vessel/src/dataStore.h \
           ../Vessel/src/dataCollector.h \
           ../Vessel/src/logOutput.h \
           ../Vessel/src/pidControl.h \
           ../Vessel/src/display.h \
           mainWindow.h \
           flightgearReader.h \
           flightgearWriter.h \
           joystick.h \
           joystickStatusDock.h \
           guiPidLoop.h \
           designPanel.h \
           guiDataStore.h

SOURCES += main.cpp \
           ../Vessel/src/dataStore.cpp \
           ../Vessel/src/dataCollector.cpp \
           ../Vessel/src/logOutput.cpp \
           ../Vessel/src/pidControl.cpp \
           ../Vessel/src/display.cpp \
           mainWindow.cpp \
           flightgearReader.cpp \
           flightgearWriter.cpp \
           joystick.cpp \
           joystickStatusDock.cpp \
           guiPidLoop.cpp \
           designPanel.cpp \
           guiDataStore.cpp

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
