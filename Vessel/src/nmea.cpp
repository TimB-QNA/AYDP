/*
    Description: Provide Serial data input for OpenPilot
         Author: Tim Brocklehurst
        Version: 0.1.0
           Date: 23 February 2008
        License: GPLv3

Changelog:
    23 February 2008 - v0.1.0 alpha:
        First Release
*/


#include <QtCore>
#include <QLatin1String>
#include <qdom.h>
#include <QFile>
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include "nmea.h"

NMEA::NMEA(QThread *parent, dataStore *vData) : dataCollector(parent, vData)
{
  printf("Creating nmeaReader\n");
  setObjectName("nmeaReader");
  
}

void NMEA::run(){
  dataInterface = new SerialIO();
  dataInterface->setDevice("/dev/serial/by-id/usb-MTK_GPS_Receiver-if01");
  connect(dataInterface, SIGNAL(rawString(QString)), this, SLOT(parseData(QString)));
  dataInterface->open();
  exec();
}

void NMEA::readSettings(QDomNode root){
  QDomNode node;
  QDomElement element;
  
  if (root.toElement().tagName().toLower()!=objectName().toLower()) return;
  
  node = root.firstChild();
  while (!node.isNull()){
    element=node.toElement();
    if (element.tagName().toLower()=="interface" && element.attribute("type").toLower()=="serial"){
//      dataInterface->readSettings(node);
    }
    node=node.nextSibling();
  }
}

void NMEA::parseData(QString input){
  int i, nAct;
  double lat, lon, ldeg, lmin, spd, trk, alt;
  bool handled=false;
  QString DOP;
  QStringList sentence;
  // Handle everything in upper case regardless.
  // This is a workaround for a bug in SerialIO where lower-case sentences are exported.
  // This doesn't hurt any other functionality.
  input=input.toUpper();

  sentence=input.split("*", QString::KeepEmptyParts);
  if (sentence.size()<=1) return;
/*  if (sentence.at(1)!=checksum(input)){
    printf("OpenPilot::NMEA - Invalid Checksum\n");
    printf("OpenPilot::NMEA - %s\n",input.toAscii().data());
    if (invalid<10){
      invalid++;
    }else{
      printf("OpenPilot::NMEA - The last 10 sentences were invalid. Attempting to refresh port.\n");
      printf("OpenPilot::NMEA - This will only work if the NMEA widget open/close signals have been\n");
      printf("OpenPilot::NMEA - connected to the IO widget.\n");
      emit closePort();
      emit openPort();
      invalid=0;
    }
    return;
  }
*/
  sentence=sentence.at(0).split(",", QString::KeepEmptyParts);

  /// Standard NMEA0183 support

  if (sentence.at(0)=="GPGLL"){
    /*!
     * $GPGLL - Defines the current latitude and longitude
     */
    if (sentence.size()<4) return;
    lat=sentence.at(1).toDouble();
    lon=sentence.at(3).toDouble();
    if (sentence.at(2).toLower()=="s") lat=-lat; if (sentence.at(4).toLower()=="w") lon=-lon;
    ldeg=(int)(lat/100.);
    lmin=(lat-ldeg*100.)/60.;
    lat=ldeg+lmin;

    ldeg=(int)(lon/100.);
    lmin=(lon-ldeg*100.)/60.;
    lon=ldeg+lmin;
//    printf("$GPGLL :: Lat=%lf   Lon=%lf\n",lat,lon);
//    emit location(QPointF(lon,lat));
    handled=true;
  }

  if (sentence.at(0)=="GPGSV"){
    /*!
     * $GPGSV - Details on GPS Satellites in View
     */
    if (sentence.size()<20) return;
    emit sat_in_view(sentence.at(4).toInt(),  sentence.at(5).toInt(),  sentence.at(6).toInt(),  sentence.at(7).toInt());
    emit sat_in_view(sentence.at(8).toInt(),  sentence.at(9).toInt(),  sentence.at(10).toInt(), sentence.at(11).toInt());
    emit sat_in_view(sentence.at(12).toInt(), sentence.at(13).toInt(), sentence.at(14).toInt(), sentence.at(15).toInt());
    emit sat_in_view(sentence.at(16).toInt(), sentence.at(17).toInt(), sentence.at(18).toInt(), sentence.at(19).toInt());
    handled=true;
  }

  if (sentence.at(0)=="GPGSA"){
  /*!
   *  $GPGSA - GPS Satellites used for position fix, and information regaring precision
   *  - 1. Mode
   *   - M = Manual, forced to operate in 2D or 3D
   *   - A = Automatic, 3D/2D
   *  - 2. Fix Type
   *   -# Fix not available
   *   -# 2D
   *   -# 3D
   *  - 3 to 14. IDs of SV used in position fix (null for unused fields)
   *  - 15. Mean Dilution of precision
   *  - 16. Horizontal Dilution of precision
   *  - 17. Vertical Dilution of precision
   */
    if (sentence.size()<18) return;
    emit fix(sentence.at(2).toInt());
    nAct=0;
    for (i=3;i<=14;i++){
      if (sentence.at(i).toInt()>0) nAct++;
      emit sat_active(sentence.at(i).toInt());
    }
    emit numActiveSats(nAct);
    emit meanDOP(sentence.at(15).toDouble());
    emit horizontalDOP(sentence.at(16).toDouble());
    DOP=sentence.at(17);
    DOP.chop(3);
    emit verticalDOP(DOP.toDouble());
    
    vesselData->fixType=sentence.at(2).toInt();
    vesselData->actSats=nAct;
    vesselData->mdop=sentence.at(15).toDouble();
    vesselData->hdop=sentence.at(16).toDouble();
    vesselData->vdop=DOP.toDouble();
    printf("Sats -- %i %i %lf %lf %lf\n",vesselData->fixType, vesselData->actSats, vesselData->mdop, vesselData->hdop, vesselData->vdop);
    handled=true;
  }

  if (sentence.at(0)=="GPGGA"){
    /*!
     * $GPGGA - Position and altitude data.
     */
    if (sentence.size()<11) return;
    lat=sentence.at(2).toDouble();
    lon=sentence.at(4).toDouble();
    alt=sentence.at(9).toDouble();
    if (sentence.at(3).toLower()=="s") lat=-lat;
    if (sentence.at(5).toLower()=="w") lon=-lon;
    if (sentence.at(10).toLower()=="f") alt*=0.3048;
    ldeg=(int)(lat/100.);
    lmin=(lat-ldeg*100.)/60.;
    lat=ldeg+lmin;

    ldeg=(int)(lon/100.);
    lmin=(lon-ldeg*100.)/60.;
    lon=ldeg+lmin;
 //   printf("%s\n",input.toAscii().data());
 //   printf("$GPGGA :: Lat=%lf   Lon=%lf\n",lat,lon);
//    emit location(QPointF(lon,lat));
    emit altitude(alt);
    handled=true;
  }

  if (sentence.at(0)=="GPRMC" || sentence.at(0)=="GPRM"){
   /*!
    * $GPRMC (official) & $GPRM (accepted)
    * - Minimum recommended transit information
    */
    if (sentence.size()<9 || sentence.at(2)!="A") return;
    lat=sentence.at(3).toDouble();
    lon=sentence.at(5).toDouble();
    spd=sentence.at(7).toDouble();
    trk=sentence.at(8).toDouble();
    // Recommended Minimum Specific GPS/TRANSIT Data
//    sscanf(buffer,"%*s %*f %*c %lf %c %lf %c %lf %lf",&lat,&ns,&lon,&ew,&spd,&trk);
    if (sentence.at(4).toLower()=="s") lat=-lat; if (sentence.at(6).toLower()=="w") lon=-lon;
    ldeg=(int)(lat/100.);
    lmin=(lat-ldeg*100.)/60.;
    lat=ldeg+lmin;

    ldeg=(int)(lon/100.);
    lmin=(lon-ldeg*100.)/60.;
    lon=ldeg+lmin;
  //  printf("%s\n",input.toAscii().data());
  //  printf("$GPRMC :: Lat=%lf   Lon=%lf\n",lat,lon);
    emit location(QPointF(lon,lat));
    emit speed(spd);
    emit track(trk);

    vesselData->latitude=lat;
    vesselData->longitude=lon;
    vesselData->track=trk;
    vesselData->speedOverGround=spd;
    printf("GPS -- %lf %lf %lf %lf\n",vesselData->latitude, vesselData->longitude, vesselData->track, vesselData->speedOverGround);
    handled=true;
  }

  if (sentence.at(0)=="GPVTG"){
   /*!
    * $GPVTG - Track made good and ground speed
    * eg. $GPVTG,360.0,T,348.7,M,000.0,N,000.0,K*43
    * -# Track made good
    * -# Fixed text 'T' indicates that track made good is relative to true north
    * -# not used
    * -# not used
    * -# Speed over ground in knots
    * -# Fixed text 'N' indicates that speed over ground in in knots
    * -# Speed over ground in kilometers/hour
    * -# Fixed text 'K' indicates that speed over ground is in kilometers/hour
    *
    * This sentence may provide more regularly updated data through VTGspeed(double).
    */
    spd=sentence.at(5).toDouble();
    trk=sentence.at(1).toDouble();
    emit VTGspeed(spd);
    emit VTGtrack(trk);
    handled=true;
  }



  /// Magellan specific strings:
  if (sentence.at(0)=="PGSV"){
   /*!
    *$GPGSV is ignored
    */
    handled=true;
  }
  if (sentence.at(0)=="PMGNCSM"){
    // See THALES Data transmission protocol for Magellan Products
  }
  if (sentence.at(0)=="PMGNRTE"){
  }
  if (sentence.at(0)=="PMGNTRK"){
  }
  if (sentence.at(0)=="PMGNVER"){
  }
  if (sentence.at(0)=="PMGNWPL"){
  }
  if (sentence.at(0)=="PMGNALM"){
  }
  if (sentence.at(0)=="PMGNMPH"){
  }
  if (sentence.at(0)=="PMGNPIH"){
  }
  if (sentence.at(0)=="PMGNST"){
   /*!
    * $PMGNST,02.12,3,T,534,05.0,+03327,00*40
    * - ST      status information
    * - 02.12   Version number?
    * - 3       2D or 3D
    * - T       True if we have a fix False otherwise
    * - 534     numbers change - unknown
    * - 05.0    time left on the gps battery in hours
    * - +03327  numbers change (freq. compensation?)
    * - 00      PRN number receiving current focus
    * - *40    checksum
    */
    if (sentence.size()<5) return;
    if (sentence.at(3).toLower()=="f") emit fix(4);
    if (sentence.at(3).toLower()=="t") emit fix(sentence.at(2).toInt());
    handled=true;
  }

  /// Tactic support
  if (sentence.at(0)=="IIHDG"){
    /*! $IIHDG,309,,,,*5D
     *  - Heading, 309 deg magnetic
     */
    if (sentence.size()<2) return;
    emit heading(sentence.at(1).toDouble());
    handled=true;
  }
  if (sentence.at(0)=="IIMTW"){
    /*! $IIMTW,+08.0,C*30
     * - Mean water temperature, 8 deg C
     */
    if (sentence.size()<2) return;
    emit temp_sea_water(sentence.at(1).toDouble());
    handled=true;
  }
  if (sentence.at(0)=="IIMWV"){
    /*!
     * $IIMWV,251,R,13.4,N,A*13
     * - Wind speed and angle, 13.4 kt @ 251 deg Relative
     * $IIMWV,253,T,14.2,N,A*16
     * - Apparent wind speed, 14.2 kt @ 253 deg True
     */
    if (sentence.size()<4) return;
    if (sentence.at(2).toLower()=="r"){
      emit wind_speed_relative(sentence.at(1).toDouble());
      emit wind_angle_relative(sentence.at(3).toDouble());
      handled=true;
    }
    if (sentence.at(2).toLower()=="t"){
      emit wind_speed(sentence.at(1).toDouble());
      emit wind_angle(sentence.at(3).toDouble());
      handled=true;
    }
  }
  if (sentence.at(0)=="IIVHW"){
    /*! $IIVHW,,,309,M,00.0,N,,*6E
     * - Water speed & magnetic heading, 0.0 kt @ 309 deg magnetic
     */
    if (sentence.size()<6) return;
    emit speed_water(sentence.at(5).toDouble());
    emit heading(sentence.at(3).toDouble());
    handled=true;
  }
  if (sentence.at(0)=="IIVLW"){
    /*! $IIVLW,00062,N,000.0,N*57
     * - Distance traveled through water, 62 nmi total, 0.0 nmi trip
     */
    if (sentence.size()<4) return;
    emit dist_total(sentence.at(1).toDouble());
    emit dist_trip(sentence.at(3).toDouble());
    handled=true;
  }
  if (sentence.at(0)=="IIVWR"){
    /*! $IIVWR,110,L,13.5,N,,,,*78
     * - Relative wind speed & angle, 13.5 kt @ 110 deg port of bow
     */
    if (sentence.size()<4) return;
    emit wind_speed_relative(sentence.at(3).toDouble());
    if (sentence.at(2)=="l") emit wind_angle_relative(-sentence.at(3).toDouble());
    if (sentence.at(2)=="r") emit wind_angle_relative(sentence.at(3).toDouble());
    handled=true;
  }
  if (sentence.at(0)=="IIDPT"){
    /*! $IIDPT - Tactic depth sounder information
     * $IIDPT,007.0,-1.0,*47
     * - Depth of water, 7.0 meters, 1 meter transducer to keel
     * \todo $IIDPT needs to be checked to make sure I've interpreted the depth below keel correctly.
     */
    if (sentence.size()<3) return;
    emit depth_offset(sentence.at(2).toDouble());
    emit depth_keel(sentence.at(1).toDouble()+sentence.at(2).toDouble());
    emit depth_transducer(sentence.at(1).toDouble());
    handled=true;
  }

/// AIS Data Extraction
  if (sentence.at(0)=="AIVDM"){
    /*!
     * Standard AIS data sentence
     * The message data is passed to the AISParser widget for processing
     */
    if (sentence.size()<6) return;
    emit aisString(sentence.at(5));
    handled=true;
  }
  
  if (!handled){
    printf("Un-handled Sentence Construction\n  %s",input.toAscii().data());
    for (i=0;i<sentence.size();i++) printf("%i - %s\n",i,sentence.at(i).toAscii().data());
  }
}

/*!
 * This routine calculates the NMEA checksum. This is an XOR of all the ascii values of the
 * characters between $ and * in an NMEA0183 sentence.
 */
QString NMEA::checksum(QString sentence){
  int i, csum=0;
  QString CS;
  char temp[3];
  if (sentence.size()<=1) return QString();
  for (i=0;i<sentence.size();i++){
    if (sentence.at(i)==QChar('*')) break;
    if (sentence.at(i)!=QChar('$')){
      if (csum==0){
        csum=sentence.at(i).toAscii();
      }else{
        csum^=sentence.at(i).toAscii();
      }
    }
  }
  sprintf(temp,"%02X",csum); CS=QString(temp);
  return CS;
}