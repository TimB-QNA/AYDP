#ifndef aydpNetworkFactory_H
  #define aydpNetworkFactory_H

#include <QObject>
#include <QtPlugin>
#include <QtNetwork>
#include <pluginInterfaces.h>

class aydpNetworkFactory : public QObject, public networkInterfaceFactory
{
  Q_OBJECT
  Q_INTERFACES(networkInterfaceFactory)
  
  public:
    aydpNetworkFactory(QObject *parent=0);
    QString pluginName();
    QString pluginDescription();
    networkInterface* createNewInstance();
};
#endif