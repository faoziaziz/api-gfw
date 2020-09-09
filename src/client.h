/*
  username : Aziz Amerul Faozi
  filename : client.h
  description : This cool stuff for header client api.
*/

#ifndef __client_h
#define __client_h



#include <stdio.h>
#include <curl/curl.h>
#include <sqlite3.h>

/* include configuration mode */
#include "conf.h"

/* just for testing */
void client_tester();

/* for implementing */
void client_push();

#endif
