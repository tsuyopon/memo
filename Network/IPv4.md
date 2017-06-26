# Overview 
This markdown is about IPv4 Header Details

# IPv4 Packet Structure

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
  - 0: Not used
  - 1: forbid divide(1), allow divide(0)
  - 2: continue fragment(1), last fragment(0)
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
  - It is added as optional function. There are a lot of Options not only below.
    - Security
    - Loose Source Routing
    - Record Route
    - Internet Timestamp
- Padding
  - "Options" must set each 32bit unit and variable length. If we lack of each 32bit unit, we add zero padding to the packet.


Type Of Services(8bit) is re-designed to this. But, still not used at all.
- Differentiated Services Code Point (DSCP) (6bits)
- Explicit Congestion Notification (ECN) Field (2 bits) 

These three parameters(Identification, Flagment Offset, Flags) are used as packet divide purpose.

**TODO**
- check sequence using Identification, Flags, Flagment Offset 
- Check caliculating Header Checksum 

## How to culculate IPv4 Checksum?
Try it later!
- http://qiita.com/h-sh/items/9e16b55adec787b82f52
- http://www.erg.abdn.ac.uk/users/gorry/course/inet-pages/ip-cksum.html

### I want to know more about "Options" fileds.
See 
- http://www.wata-lab.meijo-u.ac.jp/file/seminar/2003/2003-Semi1-Naoki_Kato.pdf

## Preparation Address List
- https://ja.wikipedia.org/wiki/IPv4

### MTU


### IP Packet Processing Diagram
See
- http://www.erg.abdn.ac.uk/users/gorry/course/inet-pages/ip-processing.html


### Operation of a Router
See
- http://www.erg.abdn.ac.uk/users/gorry/course/inet-pages/router-opn.html

# MEMO
- What are SRE and SLE?
  - https://ask.wireshark.org/questions/1389/what-are-sre-and-sle
- TCP Selective Acknowledgment Options
  - https://tools.ietf.org/html/rfc2018

# Diagrams 
- https://en.wikipedia.org/wiki/Transmission_Control_Protocol
- http://www.medianet.kent.edu/techreports/TR2005-07-22-tcp-EFSM.pdf
