/***************************************************************************
 * author : Aziz Amerul Faozi
 * description : this code will 
 */

#include "client.h"


int main(int argc, char **argv)
{
	/* hanya untuk inisiasi struct content gps */
	content_data_gps cont_gps;
	/* inisiasi database */
	db_init();	
	
	//get_data_gps(&cont_gps);
	
	accgps(&cont_gps);
	save_to_database(cont_gps);
	client_push(cont_gps);
//	read_from_database(&cont_gps);
	/* send log error */
	log_error("errrod\n", __FILE__, __LINE__);

	return 0;
}
