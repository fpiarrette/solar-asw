# Building SOLAR ASW (Application Software)

Before building the SOLAR ASW artifact, review the [README.md](../README.md) for anthe project's general concepts.

Before going deeper, two platforms are supported (host and xt_atto_lxl) and two kind of builds are supported (debug and release). Shell script support `-h` to present a full list of building arguments and configurations.

This project count with general scripts the depends and environment variable values like `$PLATFORM`, `$DEBUG`, `$OUTPUT_DIR`, `$BINARY_NAME`, and many more. These varaibles contains specific and different values depending on the platform. For example, is not the same Docker iamge name for `host` platform than for `xt_atto_lxl` platform. In addition, it's not the same executing SOLAR ASW for `host` platform than for `xt_atto_lxl` platform. In `host` case SOLAR ASW binary is executed inside a Docker container while in the other it's executed in an evaluation board. In order to simplify all these particularities this project offer two different scripts that should be sourced at the beggingning. After calling these configuration scripts, it is no needed to specify anything more.

```
# for HOST
host$ . ./config/prepare_host.sh
...
# for XT ATTO LXL
host$ . ./config/prepare_xt_atto_lxl.sh
```

In case `debug` version is needed `-d` switch can be included on previous call.

## General build process

```
host$ cd <project root>
host$ . ./config/prepare_xt_atto_lxl.sh
host$ ./tools/compiler/compile.sh
```

Result will be availble in `<project root>/build/xt_atto_lxl/release`. For `debug` version use the following:

```
host$ cd <project root>
host$ . ./config/prepare_xt_atto_lxl.sh -d
host$ ./tools/compiler/compile.sh
```

In case iteractive shell is needed `build.sh` offers `-i` option to run interactive mode. When Docker image is started interactively, shell is allows to `make`, and manage, step by step, by hand.

```
host$ cd <project root>
host$ . ./config/prepare_xt_atto_lxl.sh -d
host$ ./tools/compiler/compile.sh -i
docker$ make clean
docker$ make all
docker$ ls ./build/xt_atto_lxl/release
...
docker$ file ./build/xt_atto_lxl/release/solar-asw
...
docker$ exit
...
host$ ls ./build/xt_atto_lxl
...
host$ file ./build/xt_atto_lxl/release/solar-asw
...
```

## General for HOST platform

```
host$ cd <project root>
host$ . ./config/prepare_host.sh
host$ ./tools/compiler/compile.sh
```

In case `debug symbols` are needed, for debugging purposes for example:

```
host$ cd <project root>
host$ . ./config/prepare_host.sh -d
host$ ./tools/compiler/compile.sh
```

In this case, binary artifact will be available in `./build/host/debug/solar-asw`. This artifact can be executed under HOST Linux distribution or even under `gdb` in development host. It's assumed that binary dependencies are satisfied. For this purpose an specific script is able to launch host binary inside a Docker container in addition to all required dependenceis.

```
host$ cd <project root>
host$ . ./config/prepare_host.sh -d
host$ ./tools/launcher/launch.sh
```

For killing SOLAR ASW another script is available, and should be launched from a differente terminal.

```
host$ cd <project root>
host$ . ./config/prepare_host.sh -d
host$ ./tools/net/kill.sh
```

## How to package binaries?
TBW

## How to deploy binaries on XT ATTO LXL?

A network connection is required to transfer and deploy files to the embedded board. Assuming the XT ATTO LXL board is connected to a DHCP-enabled network and has obtained an IP address, the easiest way to determine its IP address is through the router's administration interface.

```
host$ cd <project root>
host$ . ./config/prepare_xt_atto_lxl.sh -d
host$ ./tools/net/run.sh
```

For killing SOLAR ASW:

```
host$ cd <project root>
host$ . ./config/prepare_xt_atto_lxl.sh -d
host$ ./tools/net/kill.sh
```

### Telnet on port 23

A Telnet client, such as PuTTY, can be used to connect to the board using the default password `xt`. Once connected, a menu is available to access general settings and services. Typically, both the Telnet and SSHD services should be installed and running.

### SSH on port 22

An SSH client, such as PuTTY, can be used to connect to the board using the default credentials `admin/ak-nord`. After logging in as the `admin` user, you can switch to the `root` user by running with password `xt`:

```bash
su -
```
