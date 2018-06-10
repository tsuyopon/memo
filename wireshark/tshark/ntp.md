# 概要
ntpについて

# 詳細

### 定期的なntpの動きを確認する
```
$ sudo tshark -O ntp -Y 'udp.port==123' -V
Running as user "root" and group "root". This could be dangerous.
Capturing on 'enp0s3'
Frame 1: 90 bytes on wire (720 bits), 90 bytes captured (720 bits) on interface 0
Ethernet II, Src: CadmusCo_af:c9:96 (08:00:27:af:c9:96), Dst: RealtekU_12:35:02 (52:54:00:12:35:02)
Internet Protocol Version 4, Src: 10.0.2.15 (10.0.2.15), Dst: 139.162.66.25 (139.162.66.25)
User Datagram Protocol, Src Port: 44814 (44814), Dst Port: ntp (123)
Network Time Protocol (NTP Version 4, client)
    Flags: 0x23
        00.. .... = Leap Indicator: no warning (0)
        ..10 0... = Version number: NTP Version 4 (4)
        .... .011 = Mode: client (3)
    Peer Clock Stratum: unspecified or invalid (0)
    Peer Polling Interval: 6 (64 sec)
    Peer Clock Precision: 4294967296.000000 sec
    Root Delay:    0.0000 sec
    Root Dispersion:    0.0000 sec
    Reference ID: NULL
    Reference Timestamp: Jan  1, 1970 00:00:00.000000000 UTC
    Origin Timestamp: Jan  1, 1970 00:00:00.000000000 UTC
    Receive Timestamp: Jan  1, 1970 00:00:00.000000000 UTC
    Transmit Timestamp: Jun 28, 1998 04:13:26.964431000 UTC

Frame 2: 90 bytes on wire (720 bits), 90 bytes captured (720 bits) on interface 0
Ethernet II, Src: RealtekU_12:35:02 (52:54:00:12:35:02), Dst: CadmusCo_af:c9:96 (08:00:27:af:c9:96)
Internet Protocol Version 4, Src: 139.162.66.25 (139.162.66.25), Dst: 10.0.2.15 (10.0.2.15)
User Datagram Protocol, Src Port: ntp (123), Dst Port: 44814 (44814)
Network Time Protocol (NTP Version 4, server)
    Flags: 0x24
        00.. .... = Leap Indicator: no warning (0)
        ..10 0... = Version number: NTP Version 4 (4)
        .... .100 = Mode: server (4)
    Peer Clock Stratum: secondary reference (2)
    Peer Polling Interval: 6 (64 sec)
    Peer Clock Precision: 0.000000 sec
    Root Delay:    0.0025 sec
    Root Dispersion:    0.0352 sec
    Reference ID: 10.84.87.146
    Reference Timestamp: Jun 10, 2018 08:03:48.658583000 UTC
    Origin Timestamp: Jun 28, 1998 04:13:26.964431000 UTC
    Receive Timestamp: Jun 10, 2018 08:19:29.050540000 UTC
    Transmit Timestamp: Jun 10, 2018 08:19:29.050713000 UTC
```

