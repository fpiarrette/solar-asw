# Launching SOLAR ASW (Application Software)

Before launching the SOLAR ASW, a binary artifact must be [created](./BUILD.md). For additional information please read [./BUILD.md](./BUILD.md).

## In representative embedded platform

### Dependencies in host

To be descrived: sshpass

## In host platform

In order to get a full list of execution options:

```
host$ cd <project root>
host$ ./build/host/debug/main -h
```

In order to check the process to send data to MODEM:

```
host$ cd <project root>
host$ ./build/host/debug/main -l 1 -u
```

In order to check the process to receive data from MODEM:

```
host$ cd <project root>
host$ ./build/host/debug/main -l 1 -d
```

The option `-l 1` is to get a sufficient logging level.
