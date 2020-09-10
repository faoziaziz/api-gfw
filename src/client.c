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


/* insert tester */
int insert_tester(){
  /* insert tester for test the localdatabase*/


    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("test.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }
    
    char *sql = "DROP TABLE IF EXISTS Cars;" 
                "CREATE TABLE Cars(Id INT, Name TEXT, Price INT);" 
                "INSERT INTO Cars VALUES(1, 'Audi', 52642);" 
                "INSERT INTO Cars VALUES(2, 'Mercedes', 57127);" 
                "INSERT INTO Cars VALUES(3, 'Skoda', 9000);" 
                "INSERT INTO Cars VALUES(4, 'Volvo', 29000);" 
                "INSERT INTO Cars VALUES(5, 'Bentley', 350000);" 
                "INSERT INTO Cars VALUES(6, 'Citroen', 21000);" 
                "INSERT INTO Cars VALUES(7, 'Hummer', 41400);" 
                "INSERT INTO Cars VALUES(8, 'Volkswagen', 21600);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    } 
    
    sqlite3_close(db);
    
    return 0;
   

  
}

/* test with gps testing */
int gps_tester(){
  int rc;
//struct timeval tv;
struct gps_data_t gps_data;

if ((gps_open(GPSD_SHARED_MEMORY, NULL, &gps_data)) == -1) {
    printf("code: %d, reason: %s\n", errno, gps_errstr(errno));
    return EXIT_FAILURE;
}

for(int i=0; i<10; i++) {
        /* read data */
        if ((gps_read(&gps_data,NULL,0)) == -1) {
            printf("error occured reading gps data. code: %d, reason: %s\n", errno, gps_errstr(errno));
        } else {
            /* Display data from the GPS receiver. */
            if ((gps_data.status == STATUS_FIX) && 
                (gps_data.fix.mode == MODE_2D || gps_data.fix.mode == MODE_3D) &&
                !isnan(gps_data.fix.latitude) && 
                !isnan(gps_data.fix.longitude)) {
                    printf("latitude: %f, longitude: %f, speed: %f, timestamp: %lf\n", gps_data.fix.latitude, gps_data.fix.longitude, gps_data.fix.speed, gps_data.fix.time);
            } else {
                printf("no GPS data available\n");
            }
        }

    sleep(3);
}

/* When you are done... */
gps_close (&gps_data);
return 0;  
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

  printf("this for end check sqlite\n");

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


