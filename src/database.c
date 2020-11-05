#include "client.h"

/*
 * 	@author: Aziz Amerul Faozi
 *	@name: save_to_database
 *	@desc: untuk mengesave data gps ke sqlite3
 *
 * */
void save_to_database(content_data_gps cont_gps){
	/* ada beberapa hal yang perlu diperhatikan beberapa
	 * struct gps yang harus di save
	 *
	 *
	 * */ 

	sqlite3 *db;
	sqlite3_stmt *res;
	int flag=0;

	/* some variable */

	/* open file database */
	int rc = sqlite3_open("/opt/gfw/gps_client.db", &db);
	/* for checking connection */
	if (rc != SQLITE_OK){
		fprintf(stderr, "Database tidak bisa dibuka : %s\n", sqlite3_errmsg(db));
		log_error("Database tidak bisa dibuka pada saat init.\n", __FILE__, __LINE__);
		sqlite3_close(db);
	}

	/* insrting query */

	char *sql = "INSERT INTO GPS_data("
		"online, "
		"status, "
		"sateliteUsed, "
		"mode, "
		"time_stamp, "
		"latitude, "
		"longitude, "
		"altitude, "
		"speed, "
		"track, "
		"pdop, " 
		"flag"
		") values ("
		"@online, "
		"@status, "
		"@sateliteUsed, "
		"@mode, "
		"@time_stamp, "
		"@latitude, "
		"@longitude, "
		"@altitude, "
		"@speed, "
		"@track, "
		"@pdop, "
		"@flag "
		")";
	rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);


	if (rc==SQLITE_OK){
		/* getting location index on sql */
		int id_online = sqlite3_bind_parameter_index(res, "@online");
		int id_status = sqlite3_bind_parameter_index(res, "@status");
		int id_sateliteUsed = sqlite3_bind_parameter_index(res, "@sateliteUsed");
		int id_mode = sqlite3_bind_parameter_index(res, "@mode");
		int id_time_stamp = sqlite3_bind_parameter_index(res, "@time_stamp");
		int id_latitude = sqlite3_bind_parameter_index(res, "@latitude");
		int id_longitude = sqlite3_bind_parameter_index(res, "@longitude");
		int id_altitude = sqlite3_bind_parameter_index(res, "@altitude");
		int id_speed = sqlite3_bind_parameter_index(res, "@speed");
		int id_track = sqlite3_bind_parameter_index(res, "@track");
		int id_pdop = sqlite3_bind_parameter_index(res, "@pdop");
		int id_flag = sqlite3_bind_parameter_index(res, "@flag");

		/* binding double float  */
		sqlite3_bind_double(res, id_online, cont_gps.online);
		sqlite3_bind_double(res, id_status, cont_gps.status);
		sqlite3_bind_double(res, id_sateliteUsed, cont_gps.sateliteUsed);
		sqlite3_bind_double(res, id_mode, cont_gps.mode);
		sqlite3_bind_double(res, id_time_stamp, cont_gps.time_stamp);
		sqlite3_bind_double(res, id_latitude, cont_gps.latitude);
		sqlite3_bind_double(res, id_longitude, cont_gps.longitude);
		sqlite3_bind_double(res, id_altitude, cont_gps.altitude);
		sqlite3_bind_double(res, id_speed, cont_gps.speed);
		sqlite3_bind_double(res, id_track, cont_gps.track);
		sqlite3_bind_double(res, id_pdop, cont_gps.pdop);
		sqlite3_bind_int(res, id_flag, flag);

	} else {
		fprintf(stderr, "Failed to execute statement : %s", sqlite3_errmsg(db));
		log_error("Statement gak bisa dieksekusi\n", __FILE__, __LINE__);

	}
	printf("database saved.\n");
	sqlite3_step(res);
	sqlite3_finalize(res);
	sqlite3_close(db);

}

/* fungsi ini digunakan untuk membaca data dari sqlite*/
void read_from_database (content_data_gps *cont_gps){
	sqlite3 *db;
	char *err_msg=0;
	sqlite3_stmt *res;

	int rc =sqlite3_open("/opt/gfw/gps_client.db", &db);
	printf(" Sqlite go to run.\n");
	if (rc!=SQLITE_OK){
		fprintf(stderr, "Database tidak bisa dibuka %s\n", sqlite3_errmsg(db));
		log_error("Database tidak bisa dibuka.", __FILE__, __LINE__);
		sqlite3_close(db);
		return 1;
	} 

	
	char *sql="SELECT * from  GPS_data WHERE flag=0";
	
	rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

	if (rc==SQLITE_OK){
		sqlite3_bind_int(res, 1, 3);
	} else {
		fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
		log_error("Statement tidak bisa dieksekusi", __FILE__, __LINE__);
	}
	
	while(sqlite3_step(res)!=SQLITE_DONE){
		int i;
		int num_cols = sqlite3_column_count(res);

		for (i=0; i<num_cols; i++){
			switch(sqlite3_column_type(res, i))
			{
				case (SQLITE3_TEXT):
					printf("%s, ", sqlite3_column_text(res, i));
					break;
				case (SQLITE_INTEGER):
					printf("%d, ", sqlite3_column_int(res, i));
					break;
				case (SQLITE_FLOAT):
					printf("%g, ", sqlite3_column_double(res, i));
					break;
				defalut:
					break;
			}
		}
	
		printf("\n %g \n contol", sqlite3_column_double(res, 5));
	
	}	

	sqlite3_finalize(res);
	sqlite3_close(db);
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
		"pdop FLOAT, "
		"flag INTEGER "
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

	/* variable for localdatabse */
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
