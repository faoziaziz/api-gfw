/***************************************************************************
 * author : Aziz Amerul Faozi
 * description : this code will 
 */

#include "client.h"


void *save_to_lokal(void *ptr_local);
void *save_to_server(void *ptr_server);
void delay(int miliseconds);

int check_ready();

int main(int argc, char **argv)
{
  /* hanya untuk inisiasi struct content gps */
 
  pthread_t thread_lokal, thread_server;
  int lokal_ret, server_ret;

  /* inisiasi database */
  db_init();
  
  lokal_ret = pthread_create(&thread_lokal, NULL, save_to_lokal, NULL);
  server_ret = pthread_create(&thread_server, NULL, save_to_server, NULL);

  pthread_join(thread_lokal, NULL);
  pthread_join(thread_server, NULL);

 
	
  //get_data_gps(&cont_gps);
	
  
  
  /* send log error */
  //log_error("errrod\n", __FILE__, __LINE__);

  return 0;
}

/* save to lokal */
void *save_to_lokal(void *ptr_local){
   content_data_gps cont_gps_1;


  /* tugasnya hanya ngesave ke sqlite3 tiap sepuluh menit */

  printf("Save to lokal thread, \n");
  

  while(1) {

    printf("Lokal kontol : %d \n", count);
    /* delay 10 menit*/
    delay(600000);
    /* access the function */
    accgps(&cont_gps_1);
    save_to_database(cont_gps_1);
    /* save to sqlite */
    
  }
  

  

}
/* save to server */
void *save_to_server(void *ptr_server){
   content_data_gps cont_gps_2;
  /* tugasnya hanya ngepost ke server */
  printf("Save to server thread. \n");
  /* first must check the connection if ready just go to post */

  /*read from sqlite then post after that update the flag */
  read_from_database(&cont_gps_2);
  client_push(cont_gps_2);

}

/* delay dalam milisecond 
   kalau mau 10 menit berarti
   10*60*1000;
*/
void delay(int milliseconds)
{
  long pause;
  clock_t now,then;

  pause = milliseconds*(CLOCKS_PER_SEC/1000);
  now = then = clock();
  while( (now-then) < pause )
    now = clock();
}


/* check ready to post the server */
int check_ready(){
  int status;

  /* ready checker */
  /*first check sqlite that has 0 flag, then check the post reply */
  return status;

}
