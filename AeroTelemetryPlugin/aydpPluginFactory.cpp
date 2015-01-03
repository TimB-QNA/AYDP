#include "aydpPluginFactory.h"
#include "aydpPlugin.h"

Q_EXPORT_PLUGIN2(aydpPluginFactory, aydpPluginFactory);

aydpPluginFactory::aydpPluginFactory(QObject *parent) : QObject(parent){
}

QString aydpPluginFactory::pluginName(){
  return QString("AYDP Plugin");
}

QString aydpPluginFactory::pluginDescription(){
  return QString("Allows communication to all AYDP systems.");
}

baseStationInterface* aydpPluginFactory::createNewInstance(){
  return new aydpPlugin();
}
