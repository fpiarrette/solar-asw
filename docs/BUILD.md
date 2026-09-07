# Building SOLAR ASW (Application Software)

Before building the SOLAR ASW artifact, review the [README.md](../README.md) for anthe project's general concepts.

Before going deeper, two platforms are supported (host and xt_atto_lxl) and two kind of builds are supported (debug and release). Shell script support `-h` to present a full list of building arguments and configurations.

## General build process

```
host$ cd <project root>
host$ ./build.sh
```

Result will be availble in `<project root>/build/xt_atto_lxl/release`, as default platform is `xt_atto_lxl` and default build type is `release`.

In case iteractive shell is needed `build.sh` offers `-i` option to run interactive mode. When Docker image is started interactively, shell is allows to `make`, and manage, step by step, by hand.

```
host$ cd <project root>
host$ ./build.sh -i
docker$ make clean
docker$ make all
docker$ ls ./build/xt_atto_lxl/release
...
docker$ file ./build/xt_atto_lxl/release/main
...
docker$ exit
...
host$ ls ./build/xt_atto_lxl
...
host$ file ./build/xt_atto_lxl/release/main
...
```

## General for HOST platform

```
host$ cd <project root>
host$ ./build.sh -p host
```

In case `debug symbols` are needed, for debugging purposes for example:

```
host$ cd <project root>
host$ ./build.sh -p host -d
```

In this case, binary artifact will be available in `./build/host/debug/main`. This artifact can be executed under HOST Linux distribution or even under `gdb` in development host.

## How to package binaries?
TBW

## How to deploy binaries on XT ATTO LXL?

A network connection is required to transfer and deploy files to the embedded board. Assuming the XT ATTO LXL board is connected to a DHCP-enabled network and has obtained an IP address, the easiest way to determine its IP address is through the router's administration interface.

### Telnet on port 23

A Telnet client, such as PuTTY, can be used to connect to the board using the default password `xt`. Once connected, a menu is available to access general settings and services. Typically, both the Telnet and SSHD services should be installed and running.

### SSH on port 22

An SSH client, such as PuTTY, can be used to connect to the board using the default credentials `admin/ak-nord`. After logging in as the `admin` user, you can switch to the `root` user by running with password `xt`:

```bash
su -
```
