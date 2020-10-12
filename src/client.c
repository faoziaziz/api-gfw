
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
  /* insert tester for test the local database */
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

/* test parameterized */
int test_parameterized(){

  /* database */
  sqlite3 *db;
  char *err_msg = 0;
  sqlite3_stmt *res;
    
  int rc = sqlite3_open("test.db", &db);
    
  if (rc != SQLITE_OK) {
        
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
        
    return 1;
  }
    
  char *sql = "SELECT Id, Name FROM Cars WHERE Id = ?";
        
  rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    
  if (rc == SQLITE_OK) {
        
    sqlite3_bind_int(res, 1, 3);
  } else {
        
    fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
  }
    
  int step = sqlite3_step(res);
    
  if (step == SQLITE_ROW) {
        
    printf("%s: ", sqlite3_column_text(res, 0));
    printf("%s\n", sqlite3_column_text(res, 1));
        
  } 

  sqlite3_finalize(res);
  sqlite3_close(db);
    
  return 0;
}

/* retrevie and callback sqlite. */
int retreive_sql_tester(){
  sqlite3 *db;
  char *err_msg = 0;
    
  int rc = sqlite3_open("test.db", &db);
    
  if (rc != SQLITE_OK) {
        
    fprintf(stderr, "Cannot open database: %s\n", 
	    sqlite3_errmsg(db));
    sqlite3_close(db);
        
    return 1;
  }
    
  char *sql = "SELECT * FROM Cars";
        
  rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    
  if (rc != SQLITE_OK ) {
        
    fprintf(stderr, "Failed to select data\n");
    fprintf(stderr, "SQL error: %s\n", err_msg);

    sqlite3_free(err_msg);
    sqlite3_close(db);
        
    return 1;
  } 
    
  sqlite3_close(db);
    
  return 0;
}

int callback(void *NotUsed, int argc, char **argv, 
	     char **azColName) {
    
  NotUsed = 0;
    
  for (int i = 0; i < argc; i++) {

    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
    
  printf("\n");
    
  return 0;
}

/* try push to the server */
void client_push(){

  /* deklarasi untuk definisi variable */
  char loc_post[] = "/add";
  int url_length;
  char *url_complete;

  /* add json object */
  // ini untuk variable object json
  char* jsonObj =setData();
  
  struct curl_slist *headers = NULL;

  
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

#ifdef DEBUG
  if(DEBUG==1){
    printf("URL Complete : %s ,\n", url_complete);
  }
#endif
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  
  if(curl){
    curl_easy_setopt(curl, CURLOPT_URL, url_complete);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonObj);
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res!=CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

    }
    curl_easy_cleanup(curl);
  }

  printf("\n");

  /* lets free */
  free(url_complete);
  // release memory for url completed
  curl_global_cleanup();
  
}


/*
  @author : Aziz Amerul Faozi
  @desc : this code use for convert data to json format before post to api
*/

int convert_to_json(){
  int x=0;

  struct json_object *jobj;
  const char *question= "ini string question";
  const char * answer = "javaban";

  jobj = json_object_new_object();
  json_object_object_add(jobj, "question", json_object_new_string(question));
  json_object_object_add(jobj, "answer", json_object_new_string(answer));

  printf("\n=======JSONnya \n%s\n=====\n",
	 json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_PRETTY));

  /* untuk testing delete json object */
  json_object_put(jobj);

  return x;

}


/*
  @author: Aziz Amerul Faozi
  @desc : client function before push to server 
*/
char * setData(){

  /* Get data from sqlite3 */
  char * jsonFormat="{\"id\":\"Client123421994\", \"device\": \"dev112\", \"longitude\": 123.321, \"latitude\": 321.12, \"DateStamp\": \"darilabseni\"}";
  

  /* then convert to json */
  return jsonFormat;
  

}

int tester_json(){

  /* tester json 1 */

  
  struct json_object *jobj;
  const char *question = "Mum, clouds hide alien spaceships don't they ?";
  const char *answer = "Of course not! (\"sigh\")";

  int i;

  struct {
    int flag;
    const char *flag_str;
  } json_flags[] = {
		    { JSON_C_TO_STRING_PLAIN, "JSON_C_TO_STRING_PLAIN" },
		    { JSON_C_TO_STRING_SPACED, "JSON_C_TO_STRING_SPACED" },
		    { JSON_C_TO_STRING_PRETTY, "JSON_C_TO_STRING_PRETTY" },
		    { JSON_C_TO_STRING_NOZERO, "JSON_C_TO_STRING_NOZERO" },
		    { JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY, "JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY" },
		    { -1, NULL }
  }; // Create an anonymous struct, instanciate an array and fill it
 
  printf("Using printf(): \"%s\", \"%s\"\n\n", question, answer);
  printf("Using json_object_to_json_string_ext():\n");
 
  /*
   * The following create an object and add the question and answer to it.
   */
  jobj = json_object_new_object();
  json_object_object_add(jobj, "question", json_object_new_string(question));
  json_object_object_add(jobj, "answer", json_object_new_string(answer));
 
  for (i = 0; json_flags[i].flag_str != NULL; i++) {
    printf("\nFlag %s:\n---x-x-x-xx\n", json_flags[i].flag_str);
    printf("%s\n---x-x-x-x\n", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_PRETTY));
  }
 
  json_object_put(jobj); // Delete the json object
 
  return 0;

}

