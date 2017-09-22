# 概要
wiresharkについて主にフィルタリング方法についてまとめる。 コマンドライン版のtsharkも使うことができる

yumが利用できるならばtsharkも含めて以下のコマンドでインストールすることができる。
```
$ sudo yum install wireshark
```

MACなどではウェブサイトからdmgをダウンロードしてインストールするのが簡単だろう。


# フィルタ

### フィルタリングに入力されるとサジェストされる一覧
次の文字列まで入力するとwiresharkのfiltering部分でsuggestされるので、該当名称がよくわからない時などに便利
```
eth
vlan
ip
ipv6
arp
tcp
udp
icmp
icmpv6
fr
ppp
rip
bgp
mpls
dtp
vtp
http
```

### フィルタリング用オペレータ
```
eq   ==
ne   !=
gt   >
lt   <
ge   >=
le   <=
contains
matches        ~
bitwise_and    &
```

ロジック関連
```
and  &&
or   ||
xor  ^^
not  !
[n]        // substring
```

- See
  - https://www.wireshark.org/docs/wsug_html_chunked/ChWorkBuildDisplayFilterSection.html

### IPアドレスを抽出する
```
ip.addr == 192.168.3.1
or
ip.addr eq 192.168.3.1
```

そのIPアドレスを除く場合
```
ip.addr != 192.168.3.1
or
ip.addr ne 192.168.3.1
```

### ネットワークで絞る
```
ip.addr == 192.168.3.0/24
```

### 送信元IPで絞る
```
ip.src == 192.168.3.1
```

### 宛先IPで絞る
```
ip.dst == 192.168.3.1
```

### ポート番号で絞る
```
tcp.port == 80   // TCP
udp.port == 53   // UDP
```

宛先のポートで絞ることも可能
```
tcp.dstport == 80   // TCP
udp.dstport == 53   // UDP
```

送信元のポート番号で絞ることも可能
```
tcp.srcport == 80   // TCP
ucp.srcport == 53   // UDP
```

### プロトコルで絞る
つぎのプロトコル名を入れるだけで絞ることができる。
```
icmp
tcp
udp
http
arp
ssl
```

たとえば、SSLのハンドシェイクを見たい場合には次のような感じで指定すればOK
```
ip.addr == 192.168.1.1 and tcp.port == 443 and ssl
```

### HTTPドメインで絞る
```
http.host matches "acme\.(org|com|net)"
```

### HTTPSドメインで絞りたい
HTTPSの場合だとSSLよりも上位層なのでHTTPヘッダやHTTPボディなどは全てencryptedされている。
そのため、http.hostなどで確認することができないようだ。

参考この辺??
- https://security.stackexchange.com/questions/80991/can-someone-using-wireshark-obtain-the-full-url-if-my-program-uses-https

### 複合指定(AND, OR)する
AND指定やNOTなどを組み合わせることができる。&&でも代用可能です。
```
ip.addr == 192.168.3.1 and not tcp.port == 80
or
ip.addr == 192.168.3.1 and !(tcp.port == 80)
or
http && ip.src==192.168.1.3
```

もちろん、OR指定も可能です。||でも代用可能です。
```
ip.addr == 192.168.31.1 and tcp.port == 80
http||arp
```

カッコ()をつかって複数の条件をつけることも可能です。
```
(ip.src==192.168.1.2 && ip.dst==192.168.1.3) || (ip.src==192.168.1.4 && ip.dst==192.168.1.5)
```

### パケット周りのちょっとマニアックなフィルタ

``` パケットの分割を禁止するDFフラグ（Don’t Fragment）が有効であるパケットを表示
ip.flags.df == 1
```

- tcpで通信の正常終了が行われる時に付与されるFINフラグが有効であるパケットを表示
```
tcp.flags.fin == 1
```

- tcpで通信の強制終了を行う場合に付与するRSTフラグが有効であるパケットを表示
```
tcp.flags.reset == 1
```

- tcpで通信のsynであるパケットを表示
```
tcp.flags.syn
```

- tcpで通信のackであるパケットを表示
```
tcp.flags.ack
```

### 特定のバイト列を含むパケットをフィルタリングする
00 00 01 バイトシーケンスを組む場合
```
tcp contains 00:00:01
```

### 何バイトまでを無視して、それ以外でのフィルタリングをする

```
udp[8:3]==81:60:03        // UDPヘッダ先頭8byteを無視して(バイトであることに注意)、3ビットでフィルタリングする

eth.addr[0:3]==00:06:5B   // MACアドレスのvendorパートでフィルタリングしたい場合
```

- see 6.4.4
  - https://www.wireshark.org/docs/wsug_html_chunked/ChWorkBuildDisplayFilterSection.html

### 複数の値でフィルタリングしたい場合
いくつかのポート番号でフィルタリングしたい場合には次のようにできます。
```
tcp.port in {80 443 8080}
```

上記フィルタリングは次の表現と等しい
```
tcp.port == 80 || tcp.port == 443 || tcp.port == 8080
```

### 特定の箇所をツリー状にすべてコピーしたい
wiresharkで表示される特定のパケット情報をASCIIテキスト形式として取得したい場合がある。その場合には次のようにする。
- 特定のパケットを選択する -> コピーしたい部分を予め展開しておく -> 右クリック -> コピー -> 「すべての見えている項目」

「特定のパケットを選択する」とはパケットの情報が表示されている部分を指す。たとえば、「Hypertext Transfer Protocol」などの箇所で右クリックすること  
たとえば、「Online Certificate Status Protocol」を展開していないと次のようにそのプロトコル情報は表示されなくなる。展開するとそのプロトコルの情報が詳細に表示された状態でコピーされるようになる。
```
Frame 4409: 924 bytes on wire (7392 bits), 924 bytes captured (7392 bits) on interface 0
Ethernet II, Src: HonHaiPr_25:44:f6 (c0:cb:38:25:44:f6), Dst: Apple_de:96:39 (7c:d1:c3:de:96:39)
Internet Protocol Version 4, Src: 178.255.83.1, Dst: 192.168.3.2
Transmission Control Protocol, Src Port: 80, Dst Port: 56424, Seq: 1, Ack: 455, Len: 858
Hypertext Transfer Protocol
    HTTP/1.1 200 OK\r\n
        [Expert Info (Chat/Sequence): HTTP/1.1 200 OK\r\n]
            [HTTP/1.1 200 OK\r\n]
            [Severity level: Chat]
            [Group: Sequence]
        Request Version: HTTP/1.1
        Status Code: 200
        Response Phrase: OK
    Date: Fri, 22 Sep 2017 08:25:34 GMT\r\n
    Server: Apache\r\n
    Last-Modified: Thu, 21 Sep 2017 02:10:06 GMT\r\n
    Expires: Thu, 28 Sep 2017 02:10:06 GMT\r\n
    ETag: 4A931A0BEA14CC25FD804AD7B3BC9EA50B85E6A4\r\n
    Cache-Control: max-age=495271,public,no-transform,must-revalidate\r\n
    X-OCSP-Reponder-ID: fsedcaocsp5\r\n
    Content-Length: 471\r\n
    Connection: close\r\n
    Content-Type: application/ocsp-response\r\n
    \r\n
    [HTTP response 1/1]
    [Time since request: 0.182933000 seconds]
    [Request in frame: 4330]
    File Data: 471 bytes
Online Certificate Status Protocol
```

### wiresharkの各行の色付けルール設定とその確認方法について
wiresharkの「表示」->「色付けルール」を選択するどのようなルールで何色に色付けされているのかを確認することが出来ます。ここで設定することもできます。

- 参考
  - http://kihon2nanimo.blog.fc2.com/blog-entry-6.html

# trace-cmd+kernelshark 
```
$ trace-cmd -record -p function_graph <command>
$ trace-cmd report > [file]
$ kernelshark
```

# TODO
- tsharkをつかってみる

# 参考URL
- wiresharkのfilterlingのCheatseat。どのようなオプションを知るかを俯瞰するのにすごい便利
  - http://packetlife.net/blog/2008/oct/18/cheat-sheets-tcpdump-and-wireshark/
    - 以下のユーザーガイドの一部
    - https://www.wireshark.org/docs/wsug_html_chunked/index.html
- wiresharkのフィルタリング表現方法について
  - https://www.wireshark.org/docs/wsug_html_chunked/ChWorkBuildDisplayFilterSection.html
- SSLをみる
  - http://zentoo.hatenablog.com/entry/2015/11/29/145906

