# API-GFW-Client


## About

This is just client api with thread and curl

## Requirements

1. GNU build system (autoconf, automake, libtool)
2. Curl
3. pthread
4. sqlite3

## Pipeline

To generate the project Makefiles for the first time:

```
autoreconf --install
mkdir build
cd build
../configure
```

Then just compile the project:

```
make
```
## Dependency
Some dependency should be installed like :
1. curl.
2. pthread.
berikut ini adalah cara installasi untuk distro linaro debian, sudah di test
di dragonboard 

```sh
sudo apt-get install libcurl4-openssl-dev
sudo apt-get install libgps-dev libsqlite3-dev
sudo apt-get install qdsp-start
```
### Referensi 
1. [gps](https://stackoverflow.com/questions/32000328/libgps-c-code-example)
2. [sqlitec](http://zetcode.com/db/sqlitec/)
3. [gpsd](https://discuss.96boards.org/t/db820c-gps-not-working-on-linux/4449/49)