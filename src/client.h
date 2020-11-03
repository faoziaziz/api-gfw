/*
  username : Aziz Amerul Faozi
  filename : client.h
  description : This cool stuff for header client api.
*/

#ifndef __client_h
#define __client_h


/* this code for include file */
#include <stdio.h>
#include <curl/curl.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <uuid/uuid.h>

/* configuration for gps */
#include <unistd.h>
#include <math.h>
#include <errno.h>
#include <gps.h>
#include <time.h>
/* untuk nambahin methode json */
#include <json-c/json.h>
/* include configuration mode */
#include "conf.h"

/* for data gps */
typedef struct cdg {
  double online;
  double status;
  double sateliteUsed;
  double mode;
  double time_stamp;
  double latitude;
  double longitude;
  double altitude;
  double speed;
  double track;
  double pdop;
} content_data_gps;

/* untuk push data gps */
void client_push(content_data_gps cont_gps); /* just for testing */


void client_tester();
int sqlite3_tester();
int test_parameterized();
int insert_tester();
int gps_tester();
int tester_json();
void tester_json2();
int retreive_sql_tester();
int callback(void *, int, char **, char **);
void log_error(char *msq, char *file,  int line);
char * setData();
void get_data_gps(content_data_gps *cont_gps);
/* for implementing */

void accgps(void);
/* database access */

int db_init();
void save_to_database(content_data_gps cont_gps);




#endif
