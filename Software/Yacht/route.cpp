#include "route.h"
#include <QtXml>

route::route(QObject *parent) : QObject(parent)
{
  routeSegment=-1;
  targetRadius=10;
}

void route::setDataStore(dataStore *ds){
  cds=ds;
}

void route::loadRouteFromKML(QString fileName, QString routeName){
  // Read settings file...
  int i;
  int erl, erc;
  QDomNode node, node2;
  QDomElement root, element, element2;
  QString errMsg;
  QFile file;
  
  file.setFileName(fileName);
  if (!file.open( QIODevice::ReadOnly )){
    printf("Could not open KML file - %s\n",fileName.toLatin1().data());
    return;
  }

  QDomDocument doc( "kmlFile" );
  if (!doc.setContent( &file, false, &errMsg, &erl, &erc)){
    printf("Error at line %i, Column %i - %s\n", erl, erc,errMsg.toLatin1().data());
    file.close();
    return;
  }
  file.close();

  root=doc.documentElement();
  if (root.tagName().toLower() != "kml"){
    printf("This is not a KML file\n");
    return;
  }

  node=root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    printf("Found \"%s\"\n",element.tagName().toLatin1().data());
    if (element.tagName().toLower()=="document"){
      node=node.firstChild();
      continue;
    }
    if (element.tagName().toLower()=="folder"){
      node=node.firstChild();
      continue;
    }
    if (element.tagName().toLower()=="placemark") readPlaceMark(node, routeName);
    node=node.nextSibling();
  }
  printWaypoints();
}

void route::readPlaceMark(QDomNode root, QString routeName){
  int i;
  QDomNode node, subNode;
  QDomElement element, subElement;
  QStringList coordinates, dat;
  printf("Reading Placemark\n");
  
  node=root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    printf("Found \"%s\"\n",element.tagName().toLatin1().data());
    if (element.tagName().toLower()=="name"){
      if (!routeName.isEmpty() && element.text()!=routeName){
	printf("Ignoring route \"%s\"\n",element.text().toLatin1().data());
	continue;
      }
    }
    if (element.tagName().toLower()=="linestring"){
      subNode=node.firstChild();
      while (!subNode.isNull()){
	subElement=subNode.toElement();
	printf("  Found \"%s\"\n",subElement.tagName().toLatin1().data());
	if (subElement.tagName().toLower()=="coordinates"){
	  coordinates=subElement.text().split(" ");
	  for (i=0;i<coordinates.count();i++){
	    dat=coordinates[i].split(",");
	    if (dat.count()==3){
	      // We expect Lon,Lat,Alt data...
	      routePoint.append(point(dat[0].toDouble(), dat[1].toDouble()));
	    }
	  }
	}
	subNode=subNode.nextSibling();
      }
    }
    node=node.nextSibling();
  }
}

void route::update(){
  double targetHeading;
  double pi=4.*atan(1);
  point current=point(cds->longitude, cds->latitude);
  point d;
  calculateDistances(cds->longitude, cds->latitude);
  
  printf("Target Waypoint = %i",routeSegment+1);
  if (routePoint.count()>routeSegment+1){
    distToNext=greatCircleDistance(current, routePoint[routeSegment+1]);
    headingToNext=greatCircleHeading(current, routePoint[routeSegment+1]);
    printf(" -- %lf m\t%lf deg\n", distToNext, headingToNext); 
  }else{
    printf(" No  waypoint available - returning to initial waypoint\n"); 
    routeSegment=-1;
  }
//  printf("Target Heading = %lf deg\n",greatCircleHeading(current, routePoint[routeSegment+1]));
//  printf("Current Track  = %lf deg\n",cds->track);
  
}

void route::printWaypoints(){
  int i;
  printf("Route Waypoints\n");
  for (i=0;i<routePoint.count();i++){
    printf("  %lf\t%lf\n", routePoint[i].x, routePoint[i].y);
  }
}

void route::calculateDistances(double longitude, double latitude){
  int i;
  point location(longitude, latitude);
  double pi=4.*atan(1.);
  double r=6371.*1000.; // Approx earth radius in meters
  double d;
//  printf("Position %lf\t%lf\n", longitude, latitude);
// We actually only need to query the next waypoint...
//  for (i=0;i<routePoint.count();i++){
    i=routeSegment+1;
//    d=(location-routePoint[i]).mag()*1./360.*pi*2*r;
    d=greatCircleDistance(location, routePoint[i]);
//    printf("Point %i - %lf deg \t approx %lf m\n", i, (location-routePoint[i]).mag(), d);
    if (d<targetRadius) routeSegment++;
//  }
}


double route::greatCircleDistance(point p1, point p2){
  double pi=4.*atan(1.);
  double R = 6371000; // metres
  double phi1 = p1.y * pi/180.;
  double phi2 = p2.y * pi/180.;
  double deltaPhi = (p2.y-p1.y) * pi/180.;
  double deltaLambda = (p2.x-p1.x) * pi/180.;

  double a = pow(sin(deltaPhi/2),2) +
             cos(phi1) * cos(phi2) *
             pow(sin(deltaLambda/2),2);
  double c = 2 * atan2(sqrt(a), sqrt(1-a));

  return R * c;
}

double route::greatCircleHeading(point p1, point p2){
  double pi=4.*atan(1.);
  double phi1 = p1.y * pi/180.;
  double phi2 = p2.y * pi/180.;
  double lambda1 = p1.x * pi/180.;
  double lambda2 = p2.x * pi/180.;
  
  double y = sin(lambda2-lambda1) * cos(phi2);
  double x = cos(phi1)*sin(phi2) - sin(phi1)*cos(phi2)*cos(lambda2-lambda1);
  double heading = atan2(y, x) * 180./pi;
  if (heading<0) heading+=360.;
  return heading;
}

double route::pythagoreanDistance(point p1, point p2){
  double pi=4.*atan(1.);
  double r=6371.*1000.; // Approx earth radius in meters
  return (p1-p2).mag() * 1./360.*pi*r;
}