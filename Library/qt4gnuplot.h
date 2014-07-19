/*
    Description: Provide Gnuplot graphs for QT4 (Class Header)
         Author: Tim Brocklehurst
        Version: 0.1.0
           Date: 23 October 2008
        License: GPLv3
*/

#ifndef qt4gnuplot_H
  #define qt4gnuplot_H

#include <QtGui>
#include <QtDesigner/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT qt4gnuplot : public QWidget
{
   Q_OBJECT
   Q_PROPERTY(QString Title READ title WRITE setTitle)
   Q_PROPERTY(QString X_Label READ xLabel WRITE setXLabel)
   Q_PROPERTY(QString Y_Label READ yLabel WRITE setYLabel)
   Q_PROPERTY(QString Z_Label READ zLabel WRITE setZLabel)
   Q_PROPERTY(bool    Grid    READ hasGrid WRITE setGrid)

  public:
    QStringList script;
    QImage image;
    qt4gnuplot(QWidget *parent=0);
    bool forceYRange, forceXRange;
    double yMax, yMin, xMin, xMax;

    QImage graph(QStringList data, QRect geom);

  public slots:
    void plotgraph(QStringList data);
    void plotgraph();

    void setTitle(QString data);
    QString title();

    void setXLabel(QString data);
    QString xLabel();

    void setYLabel(QString data);
    QString yLabel();

    void setZLabel(QString data);
    QString zLabel();

    void setGrid(bool yesno);
    bool hasGrid();

  private slots:
    void plotComplete(int exitCode, QProcess::ExitStatus exitStatus);

  private:
    QString titl, xlab, ylab, zlab;
    bool bk, grid;
    QColor bg;
    QProcess gnuplot;
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

};

#endif

