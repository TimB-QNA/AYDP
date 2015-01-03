// Sample Gauges main program
// QT4 - Experimental stage!!

#include <QtGui>

#include "aydpDockWidget.h"

aydpDockWidget::aydpDockWidget(QWidget *parent, dataStore *vData) : QWidget(parent) {
  QGridLayout *layout = new QGridLayout();

  vessel=vData;
}
