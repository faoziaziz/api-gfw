/*
  author : Aziz Amerul Faozi
  descrip : This code use for user accusition
*/


#include "client.h"

/* client tester */
void client_tester(){
  /* this code just for get tester */
  printf("hai this is for from client_tester.\n");
  printf("sqlite versinya : %s\n", sqlite3_libversion());

  

}

/* try check with sqlite3 */
int sqlite3_tester(){
  /* this function just check the sqlite in general */

  sqlite3 *db;
  sqlite3_stmt *res;

  int rc=sqlite3_open(":memory:", &db);

  printf("this will start test sqlite\n");
  if(rc!=SQLITE_OK){
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    return 1;

  }

  rc = sqlite3_prepare_v2(db, "SELECT SQLITE_VERSION()", -1, &res, 0);

  if(rc==SQLITE_ROW){
    printf("%s\n", sqlite3_column_text(res, 0));
  }

  sqlite3_finalize(res);
  sqlite3_close(db);

  printf("this for end check sqlite");

  return 2;

}

/* try push to the server */
void client_push(){
  /* deklarasi untuk definisi variable */
  char loc_post[] = "/locations";
  int url_length;
  char *url_complete;
  
  /* this code will curl */
  CURL *curl;
  CURLcode res;
  

  /* just for push to the server */
#ifdef DEBUG
  if (DEBUG==1) {
    printf("Lets, push .... \n");
    printf("URL api %s .\n", URL_API);
    printf("Panjang URL : %zu, \n", strlen(URL_API));
    
  } else {
    printf("Debug = %d \n", DEBUG);
    
  }
#endif

  /* get url lengt to alloction memory for url api*/
  url_length = strlen(URL_API)+strlen(loc_post);
  
  /* this will post to the server */
  url_complete = (char *) malloc(url_length + 1*sizeof(char));
  strcpy(url_complete, URL_API);
  strcat(url_complete, loc_post);

#ifdef DEBUG
  if(DEBUG==1){
    printf("URL Complete : %s ,\n", url_complete);
  }
#endif

  /*
    lets post to the server 
   */

  /* 1. We should create socket for connection. */
  curl_global_init(CURL_GLOBAL_ALL);
  
  /* 2. Get a curl handle.*/
  curl = curl_easy_init();
  
  if(curl){
    /* if the curl handle success */
    /* 3. set url to receive our post ^x^*/
    curl_easy_setopt(curl, CURLOPT_URL, url_complete);
    /* 4. set the content postfields */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");
    /* 5. perform the request untuk bisa mendapatkan response */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res!=CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

    }
    curl_easy_cleanup(curl);
   

  }

  printf("\n");

  /* lets free */
  free(url_complete); //release memory for url completed
  curl_global_cleanup();
  
}


