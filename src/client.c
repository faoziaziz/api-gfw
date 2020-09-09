#include "client.h"


void client_tester(){
  /* this code just for get tester*/
  printf("hai this is for from client_tester.\n");
  printf("sqlite versinya : %s\n", sqlite3_libversion());

}

void client_push(){
  /* just for push to the server */
#ifdef DEBUG
  if (DEBUG==1) {
    printf("Lets, pussssy .... \n");
  } else {
    printf("Debug = %d \n", DEBUG);
  }
#endif

    
}


