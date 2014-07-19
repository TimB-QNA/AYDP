/*
    Description: Provide Gauges for OpenPilot (Class header)
         Author: Tim Brocklehurst
        Version: 0.2.0
           Date: 24 February 2008
        License: GPLv3

Changelog:
    09 December 2007 - v0.1.0 alpha:
        First Release
    24 February 2008 - v0.2.0
        Added two plates
        Set up foreground colour
*/

#ifndef Gauge_H
  #define Gauge_H
#include <QtGui>
#include <QtDesigner/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT gauge : public QWidget
{
   Q_OBJECT
   Q_PROPERTY(int Plate READ plateType WRITE setPlateType)
   Q_PROPERTY(int Arrow READ arrowType WRITE setArrowType)
   Q_PROPERTY(bool AntiAliased READ antialias WRITE setAntialias)
   Q_PROPERTY(bool Integer_Gauge READ integerTics WRITE setIntegerTics)
   Q_PROPERTY(double TextRadius READ textRadius WRITE setTextRadius)
   Q_PROPERTY(QColor GaugeColor READ gaugeColor WRITE setGaugeColor)
   Q_PROPERTY(double Minimum READ minimum WRITE setMinimum)
   Q_PROPERTY(double Maximum READ maximum WRITE setMaximum)
   Q_PROPERTY(double Value READ value WRITE setValue)
   Q_PROPERTY(double ScaleFactor READ dataScale() WRITE setDataScale)
   Q_PROPERTY(QString Suffix READ suffix WRITE setSuffix)
   Q_PROPERTY(QString Label READ label WRITE setLabel)
   Q_PROPERTY(int Tics READ tics WRITE setTics)
   Q_PROPERTY(int SubTics READ subTics WRITE setSubTics)
   Q_PROPERTY(double StartAngle READ startAngle WRITE setStartAngle)
   Q_PROPERTY(double EndAngle READ endAngle WRITE setEndAngle)
   Q_PROPERTY(int ChevronWidth READ chevronWidth WRITE setChevronWidth)
   Q_PROPERTY(int Border READ border WRITE setBorder)
   Q_PROPERTY(bool ShowRanges READ showRanges WRITE setShowRanges)
   Q_PROPERTY(double Safe_Min READ safeMin() WRITE setSafeMin)
   Q_PROPERTY(double Safe_Max READ safeMax() WRITE setSafeMax)
   Q_PROPERTY(double Warn_Min READ warnMin() WRITE setWarnMin)
   Q_PROPERTY(double Warn_Max READ warnMax() WRITE setWarnMax)
   Q_PROPERTY(double Danger_Min READ dangerMin() WRITE setDangerMin)
   Q_PROPERTY(double Danger_Max READ dangerMax() WRITE setDangerMax)
   Q_PROPERTY(double RangeWidth READ rangeWidth() WRITE setRangeWidth)


public:
  gauge(QWidget *parent=0);
  double max, min;


public slots:
  void setPlateType(int);
  void setArrowType(int);
  int  plateType();
  int  arrowType();
  void setAntialias(bool);
  bool antialias();
  void setValue(int);
  void setValue(double);
  double value();
  int value_int();
  void setMaximum(double);
  double maximum();
  void setMinimum(double);
  double minimum();
  void setLabel(QString);
  QString label();
  void setTics(int);
  int tics();
  void setSubTics(int);
  int subTics();

  void setStartAngle(double);
  double startAngle();
  void setEndAngle(double);
  double endAngle();
  void setChevronWidth(double);
  double chevronWidth();
  void setQuality(int);
  int quality();
  void setBorder(int);
  int border();

  void setGaugeColor(QColor);
  QColor gaugeColor();

  void setIntegerTics(bool);
  bool integerTics();
  void setTextRadius(double);
  double textRadius();

  void setSuffix(QString);
  QString suffix();

  void setSafeMin(double);
  void setSafeMax(double);
  void setWarnMin(double);
  void setWarnMax(double);
  void setDangerMin(double);
  void setDangerMax(double);

  double safeMin();
  double safeMax();
  double warnMin();
  double warnMax();
  double dangerMin();
  double dangerMax();

  void setRangeWidth(double);
  double rangeWidth();

  void setShowRanges(bool);
  bool showRanges();

  void setDataScale(double);
  double dataScale();

signals:
  void changed();
  void safe();
  void warn();
  void danger();

private:
  void paintEvent(QPaintEvent *event);
  void draw_Ranges();
  void draw_Plate0();
  void draw_Plate1();
  void draw_Plate2();

  void draw_Plate100();
  void draw_Plate101();
  void draw_Plate102();
  void draw_Plate103();

  void draw_Arrow0();
  void translate(QPointF pt[], int n);
  void rotate(QPointF pt[], int n, double theta);

  int g_type, a_type, g_border;
  int s_tics, s_subtics;
  int x0, y0, r, g_quality;
  QPointF centre;
  QColor g_color;
  double g_value, chev_width, g_textRad;
  double smin, smax, wmin, wmax, dmin, dmax;
  double swdwidth, datScale;
  bool g_antialias, s_int, g_showRanges;
  double startAng, endAng, PI;
  QString name, g_suffix;
};

#endif

