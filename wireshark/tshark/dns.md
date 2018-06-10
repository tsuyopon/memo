# 概要
DNSに関するパケットを取得する。
DNSは通常UDP:53ですが、レスポンスサイズが大きいとTCP:53が使われる可能性があります。このため、指定はport 53としています。

# 詳細

### DNSのクエリ情報及びそのレスポンス情報を表示する
```
$ sudo tshark -f "src port 53" -n -T fields -e frame.time -e ip.src -e ip.dst -e dns.qry.name -e dns.resp.addr
Running as user "root" and group "root". This could be dangerous.
Capturing on 'enp0s3'
"Jun 10, 2018 18:47:06.435343763 JST"	192.168.3.1	10.0.2.15	www.yahoo.co.jp	183.79.250.123,118.151.254.148,124.83.255.100
"Jun 10, 2018 18:47:06.435370766 JST"	192.168.3.1	10.0.2.15	www.yahoo.co.jp	
"Jun 10, 2018 18:47:20.251914550 JST"	192.168.3.1	10.0.2.15	google.com	216.58.221.174,216.239.32.10,216.239.34.10,216.239.36.10,216.239.38.10
"Jun 10, 2018 18:47:20.251953073 JST"	192.168.3.1	10.0.2.15	google.com	216.239.32.10,216.239.34.10,216.239.36.10,216.239.38.10
"Jun 10, 2018 18:47:20.551763378 JST"	192.168.3.1	10.0.2.15	www.google.com	172.217.26.4,216.239.32.10,216.239.34.10,216.239.36.10,216.239.38.10
"Jun 10, 2018 18:47:20.551789492 JST"	192.168.3.1	10.0.2.15	www.google.com	216.239.32.10,216.239.34.10,216.239.36.10,216.239.38.10
"Jun 10, 2018 18:47:23.855104125 JST"	192.168.3.1	10.0.2.15	yahoo.com	72.30.35.9,98.137.246.8,72.30.35.10,98.138.219.231,98.137.246.7,98.138.219.232,68.180.131.16,68.142.255.16,203.84.221.53,98.138.11.157,119.160.253.83
"Jun 10, 2018 18:47:23.855149192 JST"	192.168.3.1	10.0.2.15	yahoo.com	68.180.131.16,68.142.255.16,203.84.221.53,98.138.11.157,119.160.253.83
"Jun 10, 2018 18:47:24.455713498 JST"	192.168.3.1	10.0.2.15	www.yahoo.com	124.108.103.104,124.108.103.103,68.142.254.15,68.180.130.15,68.142.254.15,68.142.254.15
"Jun 10, 2018 18:47:24.556067464 JST"	192.168.3.1	10.0.2.15	www.yahoo.com	68.142.254.15,68.180.130.15,68.142.254.15,68.142.254.15
```

### 単純なサンプル
次のサンプルはwww.yahoo.co.jpでブラウザからリクエストした時のクエリ及びクエリ応答です。
```
$ sudo tshark  -V -f 'port 53' -O dns
Capturing on 'Wi-Fi'
Frame 1: 75 bytes on wire (600 bits), 75 bytes captured (600 bits) on interface 0
Ethernet II, Src: Apple_de:96:39 (7c:d1:c3:de:96:39), Dst: HonHaiPr_25:44:f6 (c0:cb:38:25:44:f6)
Internet Protocol Version 4, Src: 192.168.3.2, Dst: 192.168.3.1
User Datagram Protocol, Src Port: 45731, Dst Port: 53
Domain Name System (query)
    Transaction ID: 0x37df
    Flags: 0x0100 Standard query
        0... .... .... .... = Response: Message is a query
        .000 0... .... .... = Opcode: Standard query (0)
        .... ..0. .... .... = Truncated: Message is not truncated
        .... ...1 .... .... = Recursion desired: Do query recursively
        .... .... .0.. .... = Z: reserved (0)
        .... .... ...0 .... = Non-authenticated data: Unacceptable
    Questions: 1
    Answer RRs: 0
    Authority RRs: 0
    Additional RRs: 0
    Queries
        www.yahoo.co.jp: type A, class IN
            Name: www.yahoo.co.jp
            [Name Length: 15]
            [Label Count: 4]
            Type: A (Host Address) (1)
            Class: IN (0x0001)

Frame 2: 189 bytes on wire (1512 bits), 189 bytes captured (1512 bits) on interface 0
Ethernet II, Src: HonHaiPr_25:44:f6 (c0:cb:38:25:44:f6), Dst: Apple_de:96:39 (7c:d1:c3:de:96:39)
Internet Protocol Version 4, Src: 192.168.3.1, Dst: 192.168.3.2
User Datagram Protocol, Src Port: 53, Dst Port: 45731
Domain Name System (response)
    Transaction ID: 0x37df
    Flags: 0x8180 Standard query response, No error
        1... .... .... .... = Response: Message is a response
        .000 0... .... .... = Opcode: Standard query (0)
        .... .0.. .... .... = Authoritative: Server is not an authority for domain
        .... ..0. .... .... = Truncated: Message is not truncated
        .... ...1 .... .... = Recursion desired: Do query recursively
        .... .... 1... .... = Recursion available: Server can do recursive queries
        .... .... .0.. .... = Z: reserved (0)
        .... .... ..0. .... = Answer authenticated: Answer/authority portion was not authenticated by the server
        .... .... ...0 .... = Non-authenticated data: Unacceptable
        .... .... .... 0000 = Reply code: No error (0)
    Questions: 1
    Answer RRs: 2
    Authority RRs: 2
    Additional RRs: 2
    Queries
        www.yahoo.co.jp: type A, class IN
            Name: www.yahoo.co.jp
            [Name Length: 15]
            [Label Count: 4]
            Type: A (Host Address) (1)
            Class: IN (0x0001)
    Answers
        www.yahoo.co.jp: type CNAME, class IN, cname edge.g.yimg.jp
            Name: www.yahoo.co.jp
            Type: CNAME (Canonical NAME for an alias) (5)
            Class: IN (0x0001)
            Time to live: 55
            Data length: 14
            CNAME: edge.g.yimg.jp
        edge.g.yimg.jp: type A, class IN, addr 182.22.24.252
            Name: edge.g.yimg.jp
            Type: A (Host Address) (1)
            Class: IN (0x0001)
            Time to live: 11
            Data length: 4
            Address: 182.22.24.252
    Authoritative nameservers
        g.yimg.jp: type NS, class IN, ns gns12.yahoo.co.jp
            Name: g.yimg.jp
            Type: NS (authoritative Name Server) (2)
            Class: IN (0x0001)
            Time to live: 191
            Data length: 8
            Name Server: gns12.yahoo.co.jp
        g.yimg.jp: type NS, class IN, ns gns02.yahoo.co.jp
            Name: g.yimg.jp
            Type: NS (authoritative Name Server) (2)
            Class: IN (0x0001)
            Time to live: 191
            Data length: 8
            Name Server: gns02.yahoo.co.jp
    Additional records
        gns02.yahoo.co.jp: type A, class IN, addr 118.151.254.148
            Name: gns02.yahoo.co.jp
            Type: A (Host Address) (1)
            Class: IN (0x0001)
            Time to live: 763
            Data length: 4
            Address: 118.151.254.148
        gns12.yahoo.co.jp: type A, class IN, addr 124.83.255.100
            Name: gns12.yahoo.co.jp
            Type: A (Host Address) (1)
            Class: IN (0x0001)
            Time to live: 753
            Data length: 4
            Address: 124.83.255.100
    [Request In: 1]
    [Time: 0.016158000 seconds]
```
