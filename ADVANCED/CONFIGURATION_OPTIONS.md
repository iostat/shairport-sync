Under Construction
=====

Configuration Flags
===
Configuration flags determine the features of Shairport Sync that are included. The idea is to have a compact core set of features, so that Shairport Sync can be installed in low-capacity devices. Extra features that take up extra space can be added using configuration flags.

Back Ends
---
 | Configuration Flag | Brief Explanation |
 | --- | --- |
 |  `--with-alsa` | Choose ALSA API support (GNU/Linux only) |
 |  `--with-pa` | Choose PulseAudio support. |
 |  `--with-sndio` | Choose SNDIO API support |
 |  `--with-jack` | Include a Jack Audio Connection Kit (jack) backend |
 |  `--with-stdout` | Include the stdout audio back end |
 |  `--with-pipe` | Include the pipe audio back end |
 |  `--with-dummy` | Include the dummy audio back end |
 |  `--with-ao` | Choose AO (Audio Output?) API support. |
 |  `--with-soundio` | Choose soundio API support. |
 
Operating System Support
---
 | Configuration Flag | Brief Explanation |
 | --- | --- |
 | `--with-os=OSType` | Specify the distribution to target: One of `linux`, `freebsd` or `darwin`. |

Installation Support
---
 | Configuration Flag | Brief Explanation |
 | --- | --- |
 |  `--with-systemv` | Install a System V startup script during a make install |
 |  `--with-systemd` | Install a systemd startup script during a make install |
 |  `--with-freebsd-service` | Install a FreeBSD startup script during a make install |
 |  `--with-cygwin-service` | Install a CYGWIN config script during a make install |
 |  `--with-configfiles` | Install configuration files during a make install |

Zeroconf/Bonjour Support
---
 | Configuration Flag | Brief Explanation |
 | --- | --- |
 |  `--with-external-mdns` | Support the use of `avahi-publish-service` or `mDNSPublish` to advertise the serviceon Bonjour/ZeroConf |
 |  `--with-avahi` | Choose Avahi-based mDNS support |
 |  `--with-tinysvcmdns` | Choose tinysvcmdns-based mDNS support |
 |  `--with-dns_sd` | Choose `dns_sd` mDNS support |

Interprocess Communication
---
 | Configuration Flag | Brief Explanation |
 | --- | --- |
 |  `--with-dbus-interface` | Include support for the native Shairport Sync D-Bus interface |
 |  `--with-dbus-test-client` | Compile dbus test client |
 |  `--with-mpris-interface` | Include support for a D-Bus interface conforming to the MPRIS standard |
 |  `--with-mpris-test-client` | Compile an MPRIS test client |
 |  `--with-mqtt-client` | Include a client for the Message Queuing Telemetry Transport (MQTT) protocol |

Audio Features
---
 | Configuration Flag | Brief Explanation |
 | --- | --- |
 |  `--with-apple-alac` | Include support for the Apple ALAC decoder |
 |  `--with-soxr` | Choose `libsoxr` for high-quality interpolation |
 |  `--with-convolution` | Choose audio DSP convolution support |


General
---
 | Configuration Flag | Brief Explanation |
 | --- | --- |
 |  `--with-pkg-config` | Use pkg-config to find libraries |
 |  `--with-libdaemon` | Include support for daemonising in older non-systemd systems |
 |  `--with-piddir=<pathname>` | Specify a pathname to a directory in which to write the PID file.
 |  `--with-ssl=<library>` | Choose `--with-ssl=openssl`, `--with-ssl=mbedtls` or `--with-ssl=polarssl` (deprecated) for encryption services. |
 |  `--with-metadata` | Include support for a metadata feed |
 |  `--with-systemdsystemunitdir=DIR` | Specify the directory for `systemd` service files |
 |  `--with-airplay-2` | Enable experimental Airplay 2 support |

