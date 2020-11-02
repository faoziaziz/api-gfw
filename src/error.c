#include "client.h"


#define BUFFER_TEXT 1000

/*
 * @author : Aziz Amerul Faozi
 * @desc : this for error log
 * */
void log_error(char * msg, char* file, int line){
	
	FILE *pLog;
	/* for date log */
	time_t now= time(&now);
	struct tm *ptm =gmtime(&now);
	char buffer[BUFFER_TEXT];

	pLog = fopen("/opt/gfw/error.log", "a+");
	fprintf(pLog, "%s FILE: %s LINE: %d : %s\n", asctime(ptm),file, line, msg);
	fclose(pLog);
}
