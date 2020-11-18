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
	int rc = sqlite3_open(DATABASE_LOC, &db);
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
	sqlite3_stmt *res, *res2;

	content_data_gps gps_push;
	int rc =sqlite3_open(DATABASE_LOC, &db);

	printf("baca dari dataabse \n");
	if (rc!=SQLITE_OK){
		fprintf(stderr, "Database tidak bisa dibuka %s\n", sqlite3_errmsg(db));
		log_error("Database tidak bisa dibuka.", __FILE__, __LINE__);
		sqlite3_close(db);
		//		return 1:
	} else {
		printf("database ok\n");
		char *sql="SELECT * from  GPS_data WHERE flag=0";

		//rc = sqlite3_exec(db, sql, callback_update, 0, &err_msg);
		/*
		   if (rc!=SQLITE_OK){
		   fprintf(stderr, "gak bisa eksekusi statment di read dataabse: %s\n", err_msg);
		   log_error("Statement tidak bisa dieksekusi", __FILE__, __LINE__);
		   sqlite3_free(err_msg);
		   sqlite3_close(db);
		   }
		   */

		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if (rc==SQLITE_OK){
			int step=sqlite3_step(res);
			if(step==SQLITE_ROW) {
				int id_nomer;
				int flag_status;
				content_data_gps gps_push;
				char * pointer;

				printf("callab\n");

				id_nomer = sqlite3_column_int(res, 0);
				gps_push.online=sqlite3_column_double(res, 1);
				gps_push.status=sqlite3_column_double(res, 2);
				gps_push.sateliteUsed=sqlite3_column_double(res, 3);
				gps_push.mode=sqlite3_column_double(res, 4);
				gps_push.time_stamp=sqlite3_column_double(res, 5);
				gps_push.latitude=sqlite3_column_double(res, 6);
				gps_push.longitude=sqlite3_column_double(res, 7);
				gps_push.altitude=sqlite3_column_double(res, 8);
				gps_push.speed=sqlite3_column_double(res, 9);
				gps_push.track=sqlite3_column_double(res, 10);
				gps_push.pdop=sqlite3_column_double(res, 11);
				flag_status=sqlite3_column_int(res, 12);

				/* push to server */
				client_push(gps_push);

				/* update flag */
				char *sql_flag="UPDATE GPS_Data SET flag=1 where Id=@id";
				int rc2 = sqlite3_prepare_v2(db, sql_flag, -1, &res2, 0);

				if (rc2!=SQLITE_OK){
				printf("notok\n");
				log_error("notoke sqlite flag", __FILE__, __LINE__);
				

				} else {

					printf("OK\n");
					int id_ID = sqlite3_bind_parameter_index(res2, "@id");
					sqlite3_bind_int(res2, id_ID, id_nomer);
					printf("saved. Harusnya, id nomer :%d \n", id_nomer);

					sqlite3_step(res2);
					sqlite3_finalize(res2);
				
				}



			} else {
				printf("Database kosong\n");
				
			}
			sqlite3_finalize(res);

		} else {
			printf("gal pl\n");
		}

	}


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
	int rc = sqlite3_open(DATABASE_LOC, &db);

	if(rc != SQLITE_OK ){
		/* check apakah database bisa dibukak */
		fprintf(stderr, "Tidak bisa membuka database: %s\n", sqlite3_errmsg(db));
		log_error("Database tidak bisa dibuka pada saat init\n", __FILE__, __LINE__);
		sqlite3_close(db);

	}

	char *sql="CREATE TABLE IF NOT EXISTS GPS_data"
		"("
		"Id INTEGER PRIMARY KEY AUTOINCREMENT, " 
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
		fprintf(stderr, "Gabisa inisiasi table : %s\n", err_msg);
		log_error("gakbisa inisiasi table . \n", __FILE__, __LINE__);
		sqlite3_free(err_msg);
		sqlite3_close(db);
		/* exekusi error */
	}



	/* close database */
	return x;
}
/* */

int callback_update(void *NotUsed, int argc, char **argv, char **azColName){


	delay(10000);
	NotUsed=0;
	int id_nomer;
	int flag_status;
	content_data_gps gps_push;
	char * pointer;

	printf("callab\n");

	id_nomer = atoi(argv[0]);
	gps_push.online=strtod(argv[1], NULL);
	gps_push.status=strtod(argv[2], NULL);
	gps_push.sateliteUsed=strtod(argv[3], NULL);
	gps_push.mode=strtod(argv[4], NULL);
	gps_push.time_stamp=strtod(argv[5], NULL);
	gps_push.latitude=strtod(argv[6], NULL);
	gps_push.longitude=strtod(argv[7], NULL);
	gps_push.altitude=strtod(argv[8], NULL);
	gps_push.speed=strtod(argv[9], NULL);
	gps_push.track=strtod(argv[10], NULL);
	gps_push.pdop=strtod(argv[11], NULL);
	flag_status=atoi(argv[12]);

	/* push to server */
	client_push(gps_push);

	/* update flag */
	printf("sebelum update flag localdb id nomer %d : status %d, speed :%f \n", id_nomer, update_flag_localdb(id_nomer), gps_push.speed);
}

/* This code use to insert gps data to gps db */
int insert_gps_to_localdb(float longitude, float latitude){

	/* variable for localdatabse */
	sqlite3 *db;
	char *err_msg=0;
	int x = 0;
	int rc = sqlite3_open(DATABASE_LOC, &db);

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

	/* variable to buffer database */
	char *err_msg_flag = 0; // for error message
	sqlite3 *db;
	sqlite3_stmt *res;

	int rc = sqlite3_open(DATABASE_LOC, &db);


	if(rc!=SQLITE_OK){
		fprintf(stderr, "tidak bisa membuka databasei update. %s\n", sqlite3_errmsg(db));

		sqlite3_close(db);

	}

	/* prepare update flag in table */  
	char *sql="UPDATE GPS_data SET flag = 1 WHERE Id = @id";

	rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

	if(rc!=SQLITE_OK){
		fprintf(stderr, "tidak bisa mengupdate flag\n");
		log_error("tidak bsia mengupdate flag.", __FILE__, __LINE__);
//		sqlite3_free(err_msg);
	} else {
		fprintf(stdout, "Status flag updated.\n");

		printf("update index ke %d \n", num_id);

		int id_Id = sqlite3_bind_parameter_index(res, "@id");

		sqlite3_bind_int(res, id_Id, num_id);

		printf("sumpah keeksekusi\n");


	}


	sqlite3_step(res);
	printf("benarkah keeksekusi\n");
	sqlite3_finalize(res);
	sqlite3_close(db);

	printf("keeksuekrere\n");
	int x =1;
	return x;
}
