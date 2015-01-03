#ifndef aydpNetwork_H
  #define aydpNetwork_H

#include <QObject>
#include <QtPlugin>
#include <QtNetwork>
#include <pluginInterfaces.h>
#include <telemetryDataPoint.h>
#include "aydpSettings.h"
#include "aydpDockWidget.h"

class aydpPlugin : public QObject, public baseStationInterface
{
  Q_OBJECT
  
  public:
    aydpPlugin(QObject *parent=0);
    QObject* asQObject();
    QString pluginName();
    QString pluginDescription();
    QString xmlRootTag();
    void readXML(QDomNode root);
    QStringList writeXML();
    QWidget* statusIndicator();
    QWidget* settingsPanel();
    QWidget* dockWidget();
    void storeSettings();

  public slots:
     virtual void connectToPeer();
     virtual void disconnectFromPeer();
     
  signals:
    void pluginRunning();
    void newTelemetryDataPoint(telemetryDataPoint);
    
  private:
    aydpSettings settings;
    aydpDockWidget *m_dockWidget;
    QLabel *statIndicator;
    QString statText;
    QByteArray buffer;
    QTimer *connTimer;
    dataStore vData;
      
    QTcpSocket *TCPClient;
    QSocketNotifier *socketNotify;

    // Bluetooth stuff
//    vector<unsigned char> bt_buffer;
    int bt_devId, bt_socket;
    QStringList bt_deviceAddressList, bt_deviceNameList;
    
    bool connectBluetooth();
    bool connectTCPIP();
    unsigned char createChecksum(unsigned char msg[], int msglen, int offset);
    
  private slots:
    void readTCPData();
    void readData(int sckId);
    void disconnected();
};
#endif