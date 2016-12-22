#ifndef aydpNetwork_H
  #define aydpNetwork_H

#include <QObject>
#include <QtPlugin>
#include <QtNetwork>
#include <pluginInterfaces.h>
#include "aydpSettings.h"
#include "../Library/aydpCommsProtocol.h"

class aydpNetwork : public QObject, public networkInterface
{
  Q_OBJECT
  
  public:
    aydpNetwork(QObject *parent=0);
    QObject* asQObject();
    QString pluginName();
    QString pluginDescription();
    QString xmlRootTag();
    void readXML(QDomNode root);
    QStringList writeXML();
    QWidget* statusIndicator();
    QWidget* settingsPanel();
    void storeSettings();

  public slots:
     virtual void connectToPeer();
     virtual void disconnectFromPeer();
     
  signals:
    void pluginRunning();
    
  private:
    aydpSettings settings;
    QLabel *statIndicator;
    QString statText;
    QByteArray buffer;
    QTimer *connTimer;
    
    QSocketNotifier *socketNotify;

    aydpCommsProtocol protocol;
    
    // Bluetooth stuff
//    vector<unsigned char> bt_buffer;
    int bt_devId, bt_socket;
    QStringList bt_deviceAddressList, bt_deviceNameList;
    
    bool connectBluetooth();
    
  private slots:
    void readData(int sckId);
};
#endif