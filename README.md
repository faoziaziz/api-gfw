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
## Menambahkan libjson-c
```bash
wget  https://s3.amazonaws.com/json-c_releases/releases/json-c-0.15.tar.gz
tar -zxvf json-c-0.15.tar.gz
cd json-c-0.15
mkdir build &&
cd    build &&

cmake -DCMAKE_INSTALL_PREFIX=/usr \
      -DCMAKE_BUILD_TYPE=Release \
      -DBUILD_STATIC_LIBS=OFF    \
      .. &&
make && sudo make install
```
```bash
sudo gpsdctl add pds://any
gpsmon
```
## Install Ngrok
```bash
wget https://raw.githubusercontent.com/faoziaziz/api-gfw/v0.0.3/install_ngrok.sh
chmod +x install_ngrok.sh
sudo ./install_ngrok.sh <your_authtoken>
```
### Referensi 
1. [gps](https://stackoverflow.com/questions/32000328/libgps-c-code-example)
2. [sqlitec](http://zetcode.com/db/sqlitec/)
3. [gpsd](https://discuss.96boards.org/t/db820c-gps-not-working-on-linux/4449/49)
4. [libjson-c](http://www.linuxfromscratch.org/blfs/view/svn/general/json-c.html)
5. [libapi](https://json-c.github.io/json-c/json-c-current-release/doc/html/json__object_8h.html#a27bd808a022251059a43f1f6370441cd)
