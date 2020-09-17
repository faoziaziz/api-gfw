/***************************************************************************
 * author : Aziz Amerul Faozi
 * description : this code will 
 */

#include "client.h"
#include "database.h"

int main(int argc, char **argv)
{
    int check;
  /* tester checker */
  client_tester();
  client_push();
  /* for localdatabase */
  sqlite3_tester();
  insert_tester();
  test_parameterized();
  db_init();




  return 0;
}
