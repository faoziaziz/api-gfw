#ifndef __conf_h
#define __conf_h

/* this debug setting */
#define DEBUG 1
/* url api configuration*/
#define URL_API "http://server.faozi.tech:8083/api-gfw/v1"
  
#define DEVICE "DRAGON001"
#define DATABASE_LOC "/opt/gfw/gfw_data_gps.db"
/* DELAY save to local 10 menit = 600000 milisecond. */
#define DELAY_SAVELOCAL 600000 
/* 
 * DELAY save push to server 1 second to search connection 
 * equals to 1000 milisecond 
 * */
#define DELAY_TO_PUSH 1000
#endif

