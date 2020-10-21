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

/* configuration for gps */
#include <unistd.h>
#include <math.h>
#include <errno.h>
#include <gps.h>
/* untuk nambahin methode json */
#include <json-c/json.h>
/* include configuration mode */
#include "conf.h"

/* just for testing */
void client_tester();
int sqlite3_tester();
int test_parameterized();
int insert_tester();
int gps_tester();
int tester_json();
void tester_json2();
int retreive_sql_tester();
int callback(void *, int, char **, char **);

char * setData();

/* for implementing */
void client_push();
void accgps(void);

/* for data gps */
struct content_data_gps {
  double online;
  double status;
  double statelite_used;
  double mode;
  double time;
  double latitude;
  double longitude;
  double altitude;
  double speed;
  double track;
  double pdop;
};

/* extern unutuk data gps */
extern struct content_data_gps cont_gps;

#endif
