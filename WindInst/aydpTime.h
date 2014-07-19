#ifndef AYDPTIME_H
#define AYDPTIME_H

#ifndef x86
  #define arduino
#endif


class aydpTime {
  public:
#ifdef arduino
    unsigned long int micro;                  /* micro-seconds */
#endif
#ifdef x86
    unsigned int micro;                  /* micro-seconds */
#endif
    unsigned short int sec;                   /* Seconds.     [0-60] (1 leap second) */
    unsigned short int min;                   /* Minutes.     [0-59] */
    unsigned short int hour;                  /* Hours.       [0-23] */
    unsigned short int day;                   /* Days in year.[0-365] */
    int year;                                 /* Year - 1900. (Ok to 2255) */
    
    aydpTime();
    void resetArduinoTime(unsigned long currentMicros);
    void incrementByMicros(unsigned long currentMicros);
  
  private:
    unsigned long int deltaMicros;
    unsigned long int lastMicros;
};

#endif
