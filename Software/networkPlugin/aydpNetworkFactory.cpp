#include "aydpNetworkFactory.h"
#include "aydpNetwork.h"

Q_EXPORT_PLUGIN2(aydpNetworkFactory, aydpNetworkFactory);

aydpNetworkFactory::aydpNetworkFactory(QObject *parent) : QObject(parent){
}

QString aydpNetworkFactory::pluginName(){
  return QString("AYDP Network");
}

QString aydpNetworkFactory::pluginDescription(){
  return QString("Allows communication to all AYDP systems.");
}

networkInterface* aydpNetworkFactory::createNewInstance(){
  return new aydpNetwork();
}
