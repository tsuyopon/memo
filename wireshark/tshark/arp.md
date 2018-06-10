# 概要
ARPリクエストについて

# 詳細

### ARP要求やARP応答パケットを抽出する
- ARP要求
```
$ sudo tshark -Y 'arp.opcode==1' 
Running as user "root" and group "root". This could be dangerous.
Capturing on 'enp0s3'
 29 54.185956147 CadmusCo_af:c9:96 -> RealtekU_12:35:02 ARP 42 Who has 10.0.2.2?  Tell 10.0.2.15
 84 64.925453476 CadmusCo_af:c9:96 -> Broadcast    ARP 42 Who has 127.0.0.1?  Tell 10.0.2.15
 90 65.925949742 CadmusCo_af:c9:96 -> Broadcast    ARP 42 Who has 127.0.0.1?  Tell 10.0.2.15
 93 66.926552540 CadmusCo_af:c9:96 -> Broadcast    ARP 42 Who has 127.0.0.1?  Tell 10.0.2.15
```
- ARP応答パケットを抽出する
```
$ sudo tshark -Y 'arp.opcode==2' 
Running as user "root" and group "root". This could be dangerous.
Capturing on 'enp0s3'
183 43.235061029 RealtekU_12:35:02 -> CadmusCo_af:c9:96 ARP 60 10.0.2.2 is at 52:54:00:12:35:02
190 44.234932883 RealtekU_12:35:02 -> CadmusCo_af:c9:96 ARP 60 10.0.2.2 is at 52:54:00:12:35:02
196 45.234979325 RealtekU_12:35:02 -> CadmusCo_af:c9:96 ARP 60 10.0.2.2 is at 52:54:00:12:35:02
202 46.235034758 RealtekU_12:35:02 -> CadmusCo_af:c9:96 ARP 60 10.0.2.2 is at 52:54:00:12:35:02
```

### arp応答パケット詳細を確認する
```
$ sudo tshark -i en0 -V -Y arp -O arp
Capturing on 'Wi-Fi'
Frame 15604: 60 bytes on wire (480 bits), 60 bytes captured (480 bits) on interface 0
Ethernet II, Src: HonHaiPr_25:44:f6 (c0:cb:38:25:44:f6), Dst: Apple_de:96:39 (7c:d1:c3:de:96:39)
Address Resolution Protocol (request)
    Hardware type: Ethernet (1)
    Protocol type: IPv4 (0x0800)
    Hardware size: 6
    Protocol size: 4
    Opcode: request (1)
    Sender MAC address: HonHaiPr_25:44:f6 (c0:cb:38:25:44:f6)
    Sender IP address: 192.168.3.1
    Target MAC address: 00:00:00_00:00:00 (00:00:00:00:00:00)
    Target IP address: 192.168.3.2

Frame 15605: 42 bytes on wire (336 bits), 42 bytes captured (336 bits) on interface 0
Ethernet II, Src: Apple_de:96:39 (7c:d1:c3:de:96:39), Dst: HonHaiPr_25:44:f6 (c0:cb:38:25:44:f6)
Address Resolution Protocol (reply)
    Hardware type: Ethernet (1)
    Protocol type: IPv4 (0x0800)
    Hardware size: 6
    Protocol size: 4
    Opcode: reply (2)
    Sender MAC address: Apple_de:96:39 (7c:d1:c3:de:96:39)
    Sender IP address: 192.168.3.2
    Target MAC address: HonHaiPr_25:44:f6 (c0:cb:38:25:44:f6)
    Target IP address: 192.168.3.1
```
