TEMPLATE = app
QT +=xml
CONFIG += debug

VERSION = pre-1.0-0

DEFINES += TOLERANCE=1e-9 VERSION=QString\\\(\\\"$$VERSION\\\"\\\) x86

HEADERS += mainWindow.h \
           windData.h \
           ../Library/gauge.h \
           ../Library/SerialIO_linux.h \
           ../Library/aydpCommsProtocol.h \
           ../Library/aydpTime.h \
           ../Library/qt4gnuplot.h

SOURCES += main.cpp \
           mainWindow.cpp \
           windData.cpp \
           ../Library/gauge.cpp \
           ../Library/SerialIO_linux.cpp \
           ../Library/aydpCommsProtocol.cpp \
           ../Library/aydpTime.cpp \
           ../Library/qt4gnuplot.cpp

ALLFILES =
# $$SOURCES $$HEADERS

ARCH  = $$system("uname -m")
OPSYS = $$system("uname")
DESTDIR = bin-$$ARCH/

UI_DIR = .$$OPSYS-$$ARCH/ui
MOC_DIR = .$$OPSYS-$$ARCH/moc
OBJECTS_DIR = .$$OPSYS-$$ARCH/obj

!build_pass:message("Generating source for documentation")
!build_pass:system("cp doxygen.tmpl doxygen.conf")
!build_pass:system("sed -i s/XX_VERSION_XX/$$VERSION/ doxygen.conf")
!build_pass:system("sed -i s/XX_INPUTFILES_XX/$$ALLFILES/ doxygen.conf")
!build_pass:system("doxygen doxygen.conf > /dev/null")
!build_pass:message("Building documentation")
!build_pass:system("make -C doc/latex > /dev/null")
!build_pass:system("cp doc/latex/refman.pdf .")
!build_pass:message("Documentation is available in refman.pdf")
