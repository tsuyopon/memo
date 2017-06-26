# Overview 
This markdown is about TCP/IP (mechanism)

# IPv4 Packet Structer 

## IPv4

- Refer from: https://tools.ietf.org/html/rfc791#section-3.1
```
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |Version|  IHL  |Type of Service|          Total Length         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |         Identification        |Flags|      Fragment Offset    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |  Time to Live |    Protocol   |         Header Checksum       |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                       Source Address                          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Destination Address                        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Options                    |    Padding    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                    Example Internet Datagram Header
```

- Version
  - if we use ipv4, this fields always set to the value 4.
- IHL(Ip Header Length)
  - This number indicates the number of 32-bit words. Minimum number of this field is 5 which indicates...
  - 5 * 32 = 160bits = 20bytes
  - Maximum Length is number 15. 15 * 32 = 480bits = 60bytes.
- Type of Service!
- Identification
- Flags
- Fragment Offset
- Time to Live
- Protocol
- Header Checksum
- Source Addrress
- Destination Addrress
- Options
- Padding


# MEMO
- What are SRE and SLE?
  - https://ask.wireshark.org/questions/1389/what-are-sre-and-sle
- TCP Selective Acknowledgment Options
  - https://tools.ietf.org/html/rfc2018

# Diagrams 
- https://en.wikipedia.org/wiki/Transmission_Control_Protocol
- http://www.medianet.kent.edu/techreports/TR2005-07-22-tcp-EFSM.pdf
