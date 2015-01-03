#ifndef aydpPluginFactory_H
  #define aydpPluginFactory_H

#include <QObject>
#include <QtPlugin>
#include <QtNetwork>
#include <pluginInterfaces.h>

class aydpPluginFactory : public QObject, public baseStationInterfaceFactory
{
  Q_OBJECT
  Q_INTERFACES(baseStationInterfaceFactory)
  
  public:
    aydpPluginFactory(QObject *parent=0);
    QString pluginName();
    QString pluginDescription();
    baseStationInterface* createNewInstance();
};
#endif