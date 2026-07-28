# SOLAR ASW (Application Software)

This project contains ASW for SOLAR modem. It convert TCP packet comming to ethernet interface into SPI data flow, also it converts SPI data into TCP packets delivered through ethernet interface.

## How to build?

```
host$ cd <project root>
host$ ./build.sh
```

Result will be availble in ```<project root>/build```.

In case iteractive shell is needed ```build.sh``` offers positional argument ```interactive```. By giving ```y``` value and interactive shell is started in which user can manage building process, step by step, by hand.

```
host$ cd <project root>
host$ ./build.sh y
docker$ make clean
docker$ make all
docker$ ls ./build
...
docker$ file ./build/main
...
docker$ exit
host$ ls ./build
...
host$ file ./build/main
...
```

## How to package binaries?
TBW

## How to deploy binaries?
TBW
