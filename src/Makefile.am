# AM_* rules are common to all programs
AM_CPPFLAGS = -g -O2 -Wall
AM_LDFLAGS = -lm -lcurl -lpthread ../libgps/build/libgps.a

bin_PROGRAMS = api-gfw-client

api_gfw_client_SOURCES = main.c client.c
#api_gfw_client_HEADERS = client.h
# Program specific rules
# example_CPPFLAGS = -I../inc
# example_LDADD = 
include_HEADERS = client.h conf.h
