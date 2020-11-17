
/*
  author : Aziz Amerul Faozi
  descrip : This code use for user accusition
*/
#include "client.h"

/* client tester */
/* try push to the server */
void client_push(content_data_gps cont_gps){

  /* deklarasi untuk definisi variable */
  char loc_post[] = "/add";
  int url_length;
  char *url_complete;
  
  /* Get data from sqlite3 */
  char * jsonFormat[2000];
  struct json_object *jobj;
  uuid_t uuid;
  char uuid_str[37]; // bagian id diupdate dengan uuid
  

  
  
  const char *datestamp="dada";
  struct curl_slist *headers = NULL;
  CURL *curl;
  CURLcode res;
  int ret;
  // setting time
  time_t now = time(&now);
  struct tm *ptm = gmtime(&now);
  
  // get uuid
  uuid_generate_time_safe(uuid);
  uuid_unparse_lower(uuid, uuid_str);

  if (now == -1) {     
    puts("The time() function failed");
  }
    
  if (ptm == NULL) {
        
    puts("The gmtime() function failed");
  }    
    
  printf("UTC time: %s", asctime(ptm));
  printf("Satelite used : %f\n", cont_gps.sateliteUsed );
  //cont_gps.sateliteUsed = 1000.0;
  /* set json object */
  jobj=json_object_new_object();
  json_object_object_add(jobj, "id", json_object_new_string(uuid_str));
  json_object_object_add(jobj, "online", json_object_new_double(cont_gps.online));
  json_object_object_add(jobj, "sateliteUsed", json_object_new_double(cont_gps.sateliteUsed));
  json_object_object_add(jobj, "status", json_object_new_double(cont_gps.status));
  json_object_object_add(jobj, "mode", json_object_new_double(cont_gps.mode));
  json_object_object_add(jobj, "time", json_object_new_double(cont_gps.time_stamp));
  json_object_object_add(jobj, "altitude", json_object_new_double(cont_gps.altitude));
  json_object_object_add(jobj, "speed", json_object_new_double(cont_gps.speed));
  json_object_object_add(jobj, "track", json_object_new_double(cont_gps.track));
  json_object_object_add(jobj, "pdop", json_object_new_double(cont_gps.pdop));
  json_object_object_add(jobj, "longitude", json_object_new_double(cont_gps.longitude));
  json_object_object_add(jobj, "latitude", json_object_new_double(cont_gps.latitude));
  
  /* string */
  json_object_object_add(jobj, "dateStamp", json_object_new_string(asctime(ptm)));
  json_object_object_add(jobj, "device", json_object_new_string(DEVICE));
  /* float */


  
  printf("JSONNYA adalah : \n%s\n", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_SPACED|JSON_C_TO_STRING_PRETTY));

  /* just for push to the server */

  /* Headers untuk melakukan akses ke API */
  headers = curl_slist_append(headers, "Accept: application/json");
  headers = curl_slist_append(headers, "Content-Type: application/json");
  headers = curl_slist_append(headers, "charset: utf-8");
  /* get url lengt to alloction memory for url api */
  url_length = strlen(URL_API)+strlen(loc_post);
  
  /* this will post to the server */
  url_complete = (char *) malloc(url_length + 1*sizeof(char));
  strcpy(url_complete, URL_API);
  strcat(url_complete, loc_post);

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  
  if(curl){
    curl_easy_setopt(curl, CURLOPT_URL, url_complete);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_SPACED|JSON_C_TO_STRING_PRETTY));
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res!=CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

    }
    curl_easy_cleanup(curl);
  }

  printf("Panjang Jsonnya adalah : %d", strlen(json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_SPACED|JSON_C_TO_STRING_PRETTY)));
  /* release json object */
  json_object_put(jobj); 
  /* lets free */
  free(url_complete);
  // release memory for url completed
  curl_global_cleanup();
  uuid_clear(uuid);
}
