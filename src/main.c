/***************************************************************************
 * author : Aziz Amerul Faozi
 * description : this code will 
 */

#include "client.h"
#include "database.h"



int main(int argc, char **argv)
{
	int check;
	content_data_gps cont_gps;
	/* tester checker */
	// client_tester();
	client_push(cont_gps);
	/* for localdatabase */
	//accgps();
	//sqlite3_tester();
	//insert_tester();
	//test_parameterized();
	//tester_json2();
	//db_init();
	//insert_gps_to_localdb(12.31, 1231.21);

	return 0;
}
