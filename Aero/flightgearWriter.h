#ifndef FLIGHTGEARWRITER_H
  #define FLIGHTGEARWRITER_H
 
  #include <QtNetwork>
  #include <QtXml>
    
class flightgearWriter : public QObject
{
  Q_OBJECT
  
  public:
    flightgearWriter(QObject *parent=0);   
    void readSettings(QDomNode root);
    
  public slots:
    void orderPosition(int ch, float controlValue);

  private:
    int port;
    float channel[5];
    QDateTime sampleTime;
    QTcpSocket* cSkt;
    QTimer *connTimer;
    QTimer *outputTimer;
    
  private slots:
    void connToServer();
    void writeTCPData();
};

#endif
