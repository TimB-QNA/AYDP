#ifndef TYPEDEF_H
#define TYPEDEF_H

#ifndef x86
  #define arduino
#endif

#ifdef arduino
  struct timeval{
    long long int tv_sec;
    unsigned long long int tv_usec;
  };
#else
  #include <sys/time.h>
#endif


#endif
