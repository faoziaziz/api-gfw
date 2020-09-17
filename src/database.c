#include "database.h"

int db_init(){

    /* gunakan ini sekali ketika inisiasi untuk create table */
    sqlite3 *db;
    char *err_msg=0;

    /* x adalah nilai balikan untuk mengeinformasikan status*/
    int x=0; 
    int rc = sqlite3_open("gps_client.db", &db);

    if(rc != SQLITE_OK ){
        /* check apakah database bisa dibukak */
        fprintf(stderr, "Tidak bisa membuka database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        /* x=1 merupakan makna dimana database tidak dapat dibuka */
        x=1;
    }

    /* 
        Membuat sebuah table, jika table belum tersedia  
        tabelnya bernama gps_data 
        terdiri dari 4 kolom :
        1. Index.
        2. Timestamp.
        3. Longitude.
        4. Latitude.
    
    */
    
    char *sql="CREATE TABLE IF NOT EXISTS GPS_data(Id INT, Timestamp TIMESTAMP, Longitude FLOAT, Latitude FLOAT);";
    rc =sqlite3_exec(db,sql, 0,0,&err_msg);

    if(rc!=SQLITE_OK){
        fprintf(stderr, "SQL eksekusi error : %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        /* exekusi error */
        x =3;
    }

    /* close database */

    return x;
}