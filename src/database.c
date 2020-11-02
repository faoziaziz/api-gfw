#include "client.h"

/*
 * 	@author: Aziz Amerul Faozi
 *	@name: save_to_database
 *	@desc: untuk mengesave data gps ke sqlite3
 *
 * */
void save_to_database(){
	/* ada beberapa hal yang perlu diperhatikan beberapa
	 * struct gps yang harus di save
	 *
	 *
	 * */ 

	sqlite3 *db;
	/* open file database */
	int rc = sqlite3_open("/opt/gfw/gps_client.db", &db);
	/* for checking connection */
	if (rc != SQLITE_OK){
		fprintf(stderr, "Database tidak bisa dibuka : %s\n", sqlite3_errmsg(db));
		log_error("Database tidak bisa dibuka pada saat init.\n", __FILE__, __LINE__);
		sqlite3_close(db);
	}




}

/*
 *	@author : Aziz Amerul Faozi
 *	@name : db_init()
 *	@desc : initialization database;
 * */
int db_init(){

	/* gunakan ini sekali ketika inisiasi untuk create table */
	sqlite3 *db;
	char *err_msg=0;

	/* x adalah nilai balikan untuk mengeinformasikan status*/
	int x=0; 
	int rc = sqlite3_open("/opt/gfw/gps_client.db", &db);

	if(rc != SQLITE_OK ){
		/* check apakah database bisa dibukak */
		fprintf(stderr, "Tidak bisa membuka database: %s\n", sqlite3_errmsg(db));
		log_error("Database tidak bisa dibuka pada saat init\n", __FILE__, __LINE__);
		sqlite3_close(db);

	}

	char *sql="CREATE TABLE IF NOT EXISTS GPS_data"
		"("
		"Id INT AUTO_INCREMENT, " 
		"online FLOAT, "
		"status FLOAT, "
		"sateliteUsed FLOAT, "
		"mode FLOAT, "
		"time_stamp FLOAT, "
		"latitude FLOAT, "
		"longitude FLOAT, "
		"altitude FLOAT, "
		"speed FLOAT, "
		"track FLOAT, "
		"pdop FLOAT "
		");";

	rc =sqlite3_exec(db,sql, 0,0,&err_msg);

	if(rc!=SQLITE_OK){
		/* sqlite3 */
		fprintf(stderr, "SQL eksekusi error : %s\n", err_msg);
		log_error("Eksekusi sql errror . \n", __FILE__, __LINE__);
		sqlite3_free(err_msg);
		sqlite3_close(db);
		/* exekusi error */
	}

	/* close database */
	return x;
}

/* This code use to insert gps data to gps db */
int insert_gps_to_localdb(float longitude, float latitude){

	sqlite3 *db;
	char *err_msg=0;
	int x = 0;

	int rc = sqlite3_open("/opt/gfw/gps_client.db", &db);

	if(rc !=SQLITE_OK){
		fprintf(stderr, "Tidak bisa membuka database. %s\n",sqlite3_errmsg(db) );
		sqlite3_close(db);

		x+=1;
	}

	/* 
	   This code use for insert GPS_data to Longitude and Latitude 
	   */
	char *sql = "INSERT INTO GPS_data(Longitude, Latitude)values(6969.6969, 123.1231)";

	rc= sqlite3_exec(db, sql, 0, 0, &err_msg);

	if(rc!=SQLITE_OK){
		fprintf(stderr, "Tidak berhasil menginsert ke table.\n");
		sqlite3_free(err_msg);
		x+=1;
	} else {
		fprintf(stdout, "Insert berhasil");
	}


	int last_id = sqlite3_last_insert_rowid(db);
	printf("Index terakhir yang diinsert %d\n", last_id);

	sqlite3_close(db);
	return x;

}


/*
   @desc : this function use to update the local database after getted 
   @input : index 
   @output : status flag
   */
int update_flag_localdb(int num_id){
	/* 
	   integer status 
0 : All clear
1 : Gak bisa membuka database 
2 : sql tidak bisa dieksekusi

*/
	int x=0;
	/* variable to buffer database */
	char *err_msg = 0; // for error message
	sqlite3 *db;

	int rc = sqlite3_open("/opt/gfw/gps_client.db", &db);


	if(rc!=SQLITE_OK){
		fprintf(stderr, "tidak bisa membuka database. %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		x+=1;
	}

	/* prepare update flag in table */  
	char *sql="UPDATE flag in table if id = id";

	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	if(rc!=SQLITE_OK){
		fprintf(stderr, "tidak bisa mengekseskusi query \n");
		sqlite3_free(err_msg);
		x+=1;
	} else {
		fprintf(stdout, "Status flag updated.\n");

	}

	int last_id = sqlite3_last_insert_rowid(db);
	printf("Index terakhir yang diupdate %d\n", last_id);
	sqlite3_close(db);


	return x;
}
