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

- Version(4bit)
  - if we use ipv4, this fields always set to the value 4.
- IHL(Ip Header Length)(4bit)
  - This number indicates the number of 32-bit words. Minimum number of this field is 5 which indicates...
  - 5 * 32 = 160bits = 20bytes
  - Maximum Length is number 15. 15 * 32 = 480bits = 60bytes.
- Type of Service!(8bit)
  - For QoS processing. But this field is not used at all now.
- Total Length(16bit)
  - all packet length that includes IP Header Length.
- Identification(16bit)
  - It is used as packet identifier.
  - If packet divided into some packets, we can ackowledge the original packet.
- Flags(3bit)
  - 0: It it a final packaet that is divided packet.
  - 1: forbid packet divide.
  - 2: continue to send divided packet.
- Fragment Offset(13bit)
  - This flagment is used by to reconstruct fragmented-datagram.
- Time to Live(8bit)
  - This number indicates how many routers can we pass. ie. Max Hop Count.
  - This fields used by traceroute command.
- Protocol(8bit)
  - Protocol number
- Header Checksum(16bit)
  - This is flags to check 
- Source Addrress(32bit)
  - send source address
- Destination Addrress(32bit)
  - recv source address
- Options(variable length)
  - variable length.
- Padding
  - "Options" must set each 32bit unit and variable length. If we lack of each 32bit unit, we add zero padding to the packet.


These three parameters(Identification, Flagment Offset, Flags) are used as packet divide purpose.

**TODO**
- check sequence using Identification, Flags, Flagment Offset 
- Check caliculating Header Checksum 
- Check Options.

## How to culculate IPv4 Checksum?
Try it later!
- http://qiita.com/h-sh/items/9e16b55adec787b82f52

## Preparation Address List
- https://ja.wikipedia.org/wiki/IPv4

# MEMO
- What are SRE and SLE?
  - https://ask.wireshark.org/questions/1389/what-are-sre-and-sle
- TCP Selective Acknowledgment Options
  - https://tools.ietf.org/html/rfc2018

# Diagrams 
- https://en.wikipedia.org/wiki/Transmission_Control_Protocol
- http://www.medianet.kent.edu/techreports/TR2005-07-22-tcp-EFSM.pdf
