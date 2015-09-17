#include "guiDataStore.h"

guiDataStore::guiDataStore(dataStore *ds, QWidget *parent) : QWidget(parent){
  QGridLayout *gridLayout = new QGridLayout();
  cds=ds;
  frontLabel = new QLabel(); gridLayout->addWidget(frontLabel,0,0);
  updateFrontLabel();
//  connect(this, SIGNAL(control(int, float)), this, SLOT(updateFrontLabel()));
  setLayout(gridLayout);
  updateTimer = new QTimer();
  updateTimer->setInterval(100);
  updateTimer->start();
  connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateFrontLabel()));
  setMinimumWidth(200);
  setMinimumHeight(375);
}

void guiDataStore::updateFrontLabel(){
  char line[40];
  QString text;
  text ="<html>";
  text+=  "<table>";  
  sprintf(line,"<tr><th>Attitude</th><td></td></tr>"); text+=line;
  sprintf(line,"<tr><th>Roll</th><td>%0.3f</td></tr>",cds->roll); text+=line;
  sprintf(line,"<tr><th>Pitch</th><td>%0.3f</td></tr>",cds->pitch); text+=line;
  sprintf(line,"<tr><th>Heading</th><td>%0.3f</td></tr>",cds->heading); text+=line;
  sprintf(line,"<tr><th>Roll Rate</th><td>%0.3f</td></tr>",cds->rollRate); text+=line;
  sprintf(line,"<tr><th>Pitch Rate</th><td>%0.3f</td></tr>",cds->pitchRate); text+=line;
  sprintf(line,"<tr><th>Heading Rate</th><td>%0.3f</td></tr>",cds->headingRate); text+=line;
  sprintf(line,"<tr><th>GPS</th><td></td></tr>"); text+=line;
  sprintf(line,"<tr><th>Latitude</th><td>%0.3f</td></tr>",cds->latitude); text+=line;
  sprintf(line,"<tr><th>Longitude</th><td>%0.3f</td></tr>",cds->longitude); text+=line;
  sprintf(line,"<tr><th>Track</th><td>%0.3f</td></tr>",cds->track); text+=line;
  sprintf(line,"<tr><th>SOG</th><td>%0.3f</td></tr>",cds->speedOverGround); text+=line;
  sprintf(line,"<tr><th>Fix Type</th><td>%i</td></tr>",cds->fixType); text+=line;
  sprintf(line,"<tr><th>Active Sats</th><td>%i</td></tr>",cds->actSats); text+=line;
  sprintf(line,"<tr><th>Mean DOP</th><td>%0.3f</td></tr>",cds->mdop); text+=line;
  sprintf(line,"<tr><th>Horiz DOP</th><td>%0.3f</td></tr>",cds->hdop); text+=line;
  sprintf(line,"<tr><th>Vertical DOP</th><td>%0.3f</td></tr>",cds->vdop); text+=line;
  sprintf(line,"<tr><th>Aero</th><td></td></tr>"); text+=line;
  sprintf(line,"<tr><th>Altitude</th><td>%0.3f</td></tr>",cds->altitude); text+=line;
  sprintf(line,"<tr><th>Airspeed</th><td>%0.3f</td></tr>",cds->airspeed); text+=line;
  sprintf(line,"<tr><th>General</th><td></td></tr>"); text+=line;
  sprintf(line,"<tr><th>Temperature</th><td>%0.3f</td></tr>",cds->temperature); text+=line; 
  text+=  "</table>";
  text+=  "</html>";
  frontLabel->setText(text);
}

void guiDataStore::paintEvent(QPaintEvent *event){
  QPainter painter(this);
  
  painter.drawRect(0, 0, width()-1, height()-1);
}
