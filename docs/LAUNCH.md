# Launching SOLAR ASW (Application Software)

Before launching the SOLAR ASW, a binary artifact must be [created](./BUILD.md). For additional information please read [./BUILD.md](./BUILD.md).

## In representative embedded platform

```
host$ cd <project root>
host$ . ./config/prepare_xt_atto_lxl.sh -d
host$ ./tools/compiler/compile.sh
host$ ./tools/net/run.sh
```

For killing SOLAR ASW:

```
host$ cd <project root>
host$ . ./config/prepare_xt_atto_lxl.sh -d
host$ ./tools/net/kill.sh
```

### Dependencies in host

To be descrived: sshpass

## In host platform

```
host$ cd <project root>
host$ . ./config/prepare_host.sh -d
host$ ./tools/compiler/compile.sh
host$ ./tools/net/run.sh
```

For killing SOLAR ASW:

```
host$ cd <project root>
host$ . ./config/prepare_host.sh -d
host$ ./tools/net/kill.sh
```

In order to get a full list of execution options:

```
host$ cd <project root>
host$ ./build/host/debug/solar-asw -h
```

In order to request the process to send data to MODEM:

```
host$ cd <project root>
host$ ./build/host/debug/solar-asw -l 1 -u
```

In order to request the process to receive data from MODEM:

```
host$ cd <project root>
host$ ./build/host/debug/solar-asw -l 1 -d
```

The option `-l 1` is to get a sufficient logging level.
