## About

A ready to use C template project set up with Autotools build system.

## Requirements

GNU build system (autoconf, automake, libtool)

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

```sh
sudo apt-get install libcurl4-openssl-dev
sudo apt-get install pthread
```
