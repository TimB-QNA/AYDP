TEMPLATE        = lib
LANGUAGE        = C++

CONFIG  = warn_on release static


HEADERS += RTFusionKalman4.h \
           RTFusionRTQF.h \
           RTIMUGD20M303DLHC.h \
           RTIMUMPU9150.h \
           RTIMU.h \
           RTMath.h \
           RTFusion.h \
           RTIMUGD20HM303D.h \
           RTIMUHal.h \
           RTIMULSM9DS0.h \
           RTIMUNull.h \
           RTIMUSettings.h

SOURCES += RTFusionKalman4.cpp \
           RTFusionRTQF.cpp \
           RTIMUGD20M303DLHC.cpp \
           RTIMUMPU9150.cpp \
           RTIMU.cpp \
           RTMath.cpp \
           RTFusion.cpp \
           RTIMUGD20HM303D.cpp \
           RTIMUHal.cpp \
           RTIMULSM9DS0.cpp \
           RTIMUNull.cpp \
           RTIMUSettings.cpp

unix{
  ARCH  = $$system("uname -m")
  OPSYS = $$system("uname")
}

win32{
  DEFINES += _SECURE_SCL=0 _HAS_ITERATOR_DEBUGGING=0 _CRT_SECURE_NO_WARNINGS
  ARCH     = $$(PROCESSOR_ARCHITECTURE)
  OPSYS    = $$(OS)
}

DESTDIR     = lib-$$OPSYS-$$ARCH/
UI_DIR      = .$$OPSYS-$$ARCH/ui
MOC_DIR     = .$$OPSYS-$$ARCH/moc
OBJECTS_DIR = .$$OPSYS-$$ARCH/obj 
