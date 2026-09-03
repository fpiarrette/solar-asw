# SOLAR ASW (Application Software)

This project contains the ASW for the SOLAR modem. Its main purpose is to bridge TCP/IP communication over Ethernet with an SPI-based interface. Incoming TCP packets received through the Ethernet interface are converted into an SPI data flow, while incoming SPI data is encapsulated and delivered as TCP packets through the Ethernet interface.

For [building, packaging and deploying](./docs/BUILD.md) shell scripts is provided. These scripts are designed to run inside a Docker container, ensuring a reproducible and controlled build environment. In addition, both CROSS and HOST platforms are supported for development and testing purposes. For further details, please refer to [./docs/BUILD.md](./docs/BUILD.md).

Once the binary artifacts have been generated, there are at least two available options to [launch and test](./docs/LAUNCH.md) the SOLAR ASW. The recommended workflow depends on the target platform and the testing scenario being executed. Additional information can be found in [./docs/LAUNCH.md](./docs/LAUNCH.md).

Finally, if you would like to explore the implementation details, [./docs/DESIGN.md](./docs/DESIGN.md) describes the main architectural concepts, software components, technological decisions adopted throughout the project. In addition, changes and [TODO](./docs/TODO.md) item list is available [here](./docs/TODO.md).
