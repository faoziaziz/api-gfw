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

void accgps(void)
{
        struct gps_data_t gps_data;

        int ret;
        

        ret = gps_open("localhost", "2947", &gps_data);
        (void)gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);

        
                /* Put this in a loop with a call to a high resolution sleep () in it. */
                if (gps_waiting(&gps_data, 500)) {
                        errno = 0;
                        if (gps_read(&gps_data) == -1) {
                                printf("Read error\n");
                                exit(1);
                        } else {
                                if (gps_data.set) {
                                        printf("\n--- GPS ---\n");
                                        printf("gps_data.online:           %10.0f\n", gps_data.online);
					// cont_gps.online=gps_data.online;
                                        printf("gps_data.status:           %d\n", gps_data.status);
					// cont_gps.status=gps_data.status;
                                        printf("gps_data.satellites_used:  %d\n", gps_data.satellites_used);
                                        // cont_gps.statelite_used=gps_data.satellites_used;
                                        printf("gps_data.fix.mode:         %d\n", gps_data.fix.mode);
                                        // cont_gps.mode=gps_data.fix.mode;
                                        printf("gps_data.fix.time:         %10.0f\n", gps_data.fix.time);
                                        // cont_gps.time=gps_data.fix.time;
                                        printf("gps_data.fix.latitude:     %f\n", gps_data.fix.latitude);
                                        //cont_gps.latitude=gps_data.fix.latitude;
                                        printf("gps_data.fix.longitude:    %f\n", gps_data.fix.longitude);
                                        //cont_gps.longitude=gps_data.fix.longitude;
                                        printf("gps_data.fix.altitude:     %f\n", gps_data.fix.altitude);
                                        //cont_gps.altitude=gps_data.fix.altitude;
                                        printf("gps_data.fix.speed:        %f\n", gps_data.fix.speed);
                                        //cont_gps.speed=gps_data.fix.speed;
                                        printf("gps_data.fix.track:        %f\n", gps_data.fix.track);
                                        //cont_gps.track=gps_data.fix.track;
                                        printf("gps_data.dop.pdop:         %f\n", gps_data.dop.pdop);
                                        //cont_gps.pdop=gps_data.dop.pdop;
                                }
                        }
                }
        
}

