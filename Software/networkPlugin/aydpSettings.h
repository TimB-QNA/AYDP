#ifndef sampleSettings_H
  #define sampleSettings_H

#include <QtGui>
#include <QtXml>

class aydpSettings
{
  public:
    enum connDeviceType { network=0, serial, bluetooth };
    
    aydpSettings();
    void readXML(QDomNode root);
    QStringList writeXML();    
    void storeGUIValues();
    
    connDeviceType deviceType;
    QString host;
    int port;
    int reconnectRate;
    int connectTimeout;
    int messageTimeout;
    bool autoReconnect;
    
    QWidget *guiPanel;
    
  private:
    QLabel *hardwareLabel;
    QComboBox *hardwareCombo;
    QLabel *hostLabel;
    QLabel *portLabel;
    QLineEdit *hostEdit;
    QSpinBox *portSpin;
    QLabel *reconnectLabel;  
    QSpinBox *reconnectSpin;
    QLabel *connTimeoutLabel;
    QSpinBox *connTimeoutSpin;
};

#endif

