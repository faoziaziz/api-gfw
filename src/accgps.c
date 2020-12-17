#include "client.h"

void get_data_gps(content_data_gps *cont_gps){
	cont_gps->online=1.2;
	cont_gps->status=2.1;
	cont_gps->sateliteUsed=3.1;
	cont_gps->mode=4.1;
	cont_gps->time_stamp=5.1;
	cont_gps->latitude=6.9;
	cont_gps->longitude=7.1;
	cont_gps->altitude=8.1;
	cont_gps->speed=9.9;
	cont_gps->track=10.1;
	cont_gps->pdop=11.1;
}

void accgps(content_data_gps *cont_gps)
{
       int ret;
        struct gps_data_t gps_data;
	int make_true;
	

        ret = gps_open("localhost", "2947", &gps_data);
        (void)gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);

	make_true=69;
        while (make_true==69) {

                /* Put this in a loop with a call to a high resolution sleep () in it. */
                if (gps_waiting(&gps_data, 500)) {
                        errno = 0;
                        if (gps_read(&gps_data, NULL, 0) == -1) {
                                printf("Read error\n");
                                exit(1);
                        } else {
                                if (gps_data.set) { 
					if( gps_data.online.tv_nsec==gps_data.online.tv_nsec
							&&gps_data.status==gps_data.status
							&&gps_data.satellites_used==gps_data.satellites_used
							&&gps_data.satellites_used>=3
							&&gps_data.fix.mode==gps_data.fix.mode
							&&gps_data.fix.time.tv_nsec==gps_data.fix.time.tv_nsec
							&&gps_data.fix.latitude==gps_data.fix.latitude
							&&gps_data.fix.longitude==gps_data.fix.longitude
							&&gps_data.fix.altitude==gps_data.fix.altitude
							&&gps_data.fix.speed==gps_data.fix.speed
							&&gps_data.fix.track==gps_data.fix.track
							&&gps_data.dop.pdop==gps_data.dop.pdop){
                                        
                                        cont_gps->online=gps_data.online.tv_nsec;
                                        cont_gps->status=(double)gps_data.status;
					
                                        cont_gps->sateliteUsed=(double)gps_data.satellites_used;
					printf("sateliteUsed : %f", (double)gps_data.satellites_used);
                                        cont_gps->mode=(double)gps_data.fix.mode;
                                       	cont_gps->time_stamp= gps_data.fix.time.tv_nsec;
                                        cont_gps->latitude=gps_data.fix.latitude;
                                        cont_gps->longitude=gps_data.fix.longitude;
                                        cont_gps->altitude=gps_data.fix.altitude;
                                        cont_gps->speed=gps_data.fix.speed;
                                        cont_gps->track=gps_data.fix.track;
                                        cont_gps->pdop=gps_data.dop.pdop;
					make_true=70;
					}
					
                                }
                        }
                }
		

        }
	make_true=69;
 
}

