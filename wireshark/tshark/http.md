# 概要
tsharkでのhttpキャプチャについて

# 詳細

### TCPポート80のパケット補足する
- 受信したTCP:80パケットを表示する
```
$ sudo tshark -Y 'tcp.srcport==80'
Running as user "root" and group "root". This could be dangerous.
Capturing on 'enp0s3'
388 68.061498027 182.22.31.252 -> 10.0.2.15    TCP 60 http > 47134 [SYN, ACK] Seq=0 Ack=1 Win=65535 Len=0 MSS=1460
391 68.161051945 182.22.31.252 -> 10.0.2.15    TCP 60 http > 47134 [ACK] Seq=1 Ack=80 Win=65535 Len=0
392 68.161102144 182.22.31.252 -> 10.0.2.15    TCP 1462 [TCP segment of a reassembled PDU]
394 68.161221762 182.22.31.252 -> 10.0.2.15    TCP 1474 [TCP segment of a reassembled PDU]
397 68.262006517 182.22.31.252 -> 10.0.2.15    HTTP 4338 HTTP/1.1 301 Redirect  (text/html)
404 68.362557656 182.22.31.252 -> 10.0.2.15    TCP 60 http > 47134 [ACK] Seq=7113 Ack=81 Win=65535 Len=0
409 68.362879771 182.22.31.252 -> 10.0.2.15    TCP 60 http > 47134 [FIN, ACK] Seq=7113 Ack=81 Win=65535 Len=0
```

- 送信されたTCP:80パケットを表示する
```
$ sudo tshark  -Y 'tcp.dstport==80'
Running as user "root" and group "root". This could be dangerous.
Capturing on 'enp0s3'
 14 2.532911480    10.0.2.15 -> 216.230.250.154 TCP 74 59034 > http [SYN] Seq=0 Win=29200 Len=0 MSS=1460 SACK_PERM=1 TSval=288448208 TSecr=0 WS=128
 16 2.701350838    10.0.2.15 -> 216.230.250.154 TCP 54 59034 > http [ACK] Seq=1 Ack=1 Win=29200 Len=0
 18 2.709183858    10.0.2.15 -> 216.230.250.154 HTTP 130 GET / HTTP/1.1 
 22 2.901946093    10.0.2.15 -> 216.230.250.154 TCP 54 59034 > http [ACK] Seq=77 Ack=2737 Win=34080 Len=0
 25 3.002177747    10.0.2.15 -> 216.230.250.154 TCP 54 59034 > http [ACK] Seq=77 Ack=4105 Win=36920 Len=0
 29 3.002348513    10.0.2.15 -> 216.230.250.154 TCP 54 59034 > http [ACK] Seq=77 Ack=5473 Win=39672 Len=0
 31 3.002429538    10.0.2.15 -> 216.230.250.154 TCP 54 59034 > http [ACK] Seq=77 Ack=6841 Win=42408 Len=0
 33 3.002477538    10.0.2.15 -> 216.230.250.154 TCP 54 59034 > http [ACK] Seq=77 Ack=8638 Win=46860 Len=0
 34 3.002885135    10.0.2.15 -> 216.230.250.154 TCP 54 59034 > http [FIN, ACK] Seq=77 Ack=8638 Win=46860 Len=0
```

- 送信、受信の両方を含めてポート80のリクエストを表示する。
```
$ sudo tshark -Y 'tcp.port==80'
Running as user "root" and group "root". This could be dangerous.
Capturing on 'enp0s3'
 17 3.134163473    10.0.2.15 -> 182.22.25.252 TCP 74 34584 > http [SYN] Seq=0 Win=29200 Len=0 MSS=1460 SACK_PERM=1 TSval=288691042 TSecr=0 WS=128
 18 3.203921877 182.22.25.252 -> 10.0.2.15    TCP 60 http > 34584 [SYN, ACK] Seq=0 Ack=1 Win=65535 Len=0 MSS=1460
 19 3.204016386    10.0.2.15 -> 182.22.25.252 TCP 54 34584 > http [ACK] Seq=1 Ack=1 Win=29200 Len=0
 20 3.204349144    10.0.2.15 -> 182.22.25.252 HTTP 133 GET / HTTP/1.1 
 21 3.304133748 182.22.25.252 -> 10.0.2.15    TCP 60 http > 34584 [ACK] Seq=1 Ack=80 Win=65535 Len=0
 22 3.304183210 182.22.25.252 -> 10.0.2.15    TCP 1462 [TCP segment of a reassembled PDU]
 23 3.304202638    10.0.2.15 -> 182.22.25.252 TCP 54 34584 > http [ACK] Seq=80 Ack=1409 Win=30976 Len=0
 24 3.304294963 182.22.25.252 -> 10.0.2.15    TCP 1474 [TCP segment of a reassembled PDU]
 25 3.304312331    10.0.2.15 -> 182.22.25.252 TCP 54 34584 > http [ACK] Seq=80 Ack=2829 Win=34080 Len=0
 28 3.404354155 182.22.25.252 -> 10.0.2.15    HTTP 4338 HTTP/1.1 301 Redirect  (text/html)
 29 3.404417948    10.0.2.15 -> 182.22.25.252 TCP 54 34584 > http [ACK] Seq=80 Ack=7113 Win=42600 Len=0
 33 3.405222198    10.0.2.15 -> 182.22.25.252 TCP 54 34584 > http [FIN, ACK] Seq=80 Ack=7113 Win=42600 Len=0
 36 3.504977551 182.22.25.252 -> 10.0.2.15    TCP 60 http > 34584 [ACK] Seq=7113 Ack=81 Win=65535 Len=0
 41 3.505162318 182.22.25.252 -> 10.0.2.15    TCP 60 http > 34584 [FIN, ACK] Seq=7113 Ack=81 Win=65535 Len=0
 42 3.505183507    10.0.2.15 -> 182.22.25.252 TCP 54 34584 > http [ACK] Seq=81 Ack=7114 Win=42600 Len=0
```

### 送受信を確認する
HTTPが存在しないフレームは出力から除外しています
```
$ sudo tshark -i lo -O http -Y 'tcp.port==8083' -V
(snip)
Frame 60: 250 bytes on wire (2000 bits), 250 bytes captured (2000 bits) on interface 0
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: 49862 (49862), Dst Port: us-srv (8083), Seq: 1, Ack: 1, Len: 184
Hypertext Transfer Protocol
    GET /synthetic.txt HTTP/1.1\r\n
        [Expert Info (Chat/Sequence): GET /synthetic.txt HTTP/1.1\r\n]
            [Message: GET /synthetic.txt HTTP/1.1\r\n]
            [Severity level: Chat]
            [Group: Sequence]
        Request Method: GET
        Request URI: /synthetic.txt
        Request Version: HTTP/1.1
    Host: 127.0.0.1:8083\r\n
    X-Forwarded-For: 127.0.0.1\r\n
    Via: http/1.0 localhost.localdomain[5b87da56-f4f5-4e7a-8f47-5a0c9e524d88] (ApacheTrafficServer/7.1.2)\r\n
    \r\n
    [Full request URI: http://127.0.0.1:8083/synthetic.txt]
    [HTTP request 1/1]

(snip)
Frame 62: 1918 bytes on wire (15344 bits), 1918 bytes captured (15344 bits) on interface 0
Ethernet II, Src: 00:00:00_00:00:00 (00:00:00:00:00:00), Dst: 00:00:00_00:00:00 (00:00:00:00:00:00)
Internet Protocol Version 4, Src: 127.0.0.1 (127.0.0.1), Dst: 127.0.0.1 (127.0.0.1)
Transmission Control Protocol, Src Port: us-srv (8083), Dst Port: 49862 (49862), Seq: 1, Ack: 185, Len: 1852
Hypertext Transfer Protocol
    HTTP/1.0 200 OK\r\n
        [Expert Info (Chat/Sequence): HTTP/1.0 200 OK\r\n]
            [Message: HTTP/1.0 200 OK\r\n]
            [Severity level: Chat]
            [Group: Sequence]
        Request Version: HTTP/1.0
        Status Code: 200
        Response Phrase: OK
    Server: Traffic Manager\r\n
    Date: Fri, 08 Jun 2018 00:12:10 GMT\r\n
    Cache-Control: no-store\r\n
    Pragma: no-cache\r\n
    Content-type: text/plain\r\n
    Content-Length: 1680\r\n
        [Content length: 1680]
    \r\n
    [HTTP response 1/1]
    [Time since request: 0.000134632 seconds]
    [Request in frame: 60]
Line-based text data: text/plain
```


### HTTPクリエスト統計を表示する

たとえば、次の様なtsharkコマンドを実行して、その後そのホスト内から実行してみる。
```
$ curl http://rakuten.co.jp/
$ curl http://sample.co.jp/
```

その後tsharkでキャプチャー中をCtrl+Cを押下するとHTTPの統計情報が表示される。
```
$ sudo tshark -z http_req,tree
Running as user "root" and group "root". This could be dangerous.
Capturing on 'enp0s3'
  1 0.000000000     10.0.2.2 -> 10.0.2.15    SSH 94 Encrypted request packet len=40
  2 0.000320278    10.0.2.15 -> 10.0.2.2     SSH 126 Encrypted response packet len=72
  3 0.000510539     10.0.2.2 -> 10.0.2.15    TCP 60 61800 > ssh [ACK] Seq=41 Ack=73 Win=65535 Len=0
  4 0.269556070    10.0.2.15 -> 10.0.2.2     SSH 366 Encrypted response packet len=312
  5 0.269854269     10.0.2.2 -> 10.0.2.15    TCP 60 61798 > ssh [ACK] Seq=1 Ack=313 Win=65535 Len=0
...
253 15.059133598     10.0.2.2 -> 10.0.2.15    TCP 60 61798 > ssh [ACK] Seq=41 Ack=25265 Win=65535 Len=0     ## ここでCtrl+Cを押す
1 packet dropped
253 packets captured

===================================================================
 HTTP/Requests                     value	        rate	     percent
-------------------------------------------------------------------
 HTTP Requests by HTTP Host           2       0.000225                
  rakuten.co.jp                        1       0.000112          50.00%
   /                                    1       0.000112         100.00%
  sample.co.jp                         1       0.000112          50.00%
   /                                    1       0.000112         100.00%

===================================================================
```

### Hostヘッダ、User-Agentを抽出する
以下はtsharkでdumpしながらcurlやwgetを実行した時の出力結果
```
$ sudo tshark -Y http.request -T fields -e http.host -e http.user_agent
Running as user "root" and group "root". This could be dangerous.
Capturing on 'enp0s3'
www.google.com	curl/7.29.0
www.yahoo.co.jp	Wget/1.14 (linux-gnu)
```

### Hostヘッダ、リクエストIPアドレス、リクエストURLなどを抽出する
以下はtsharkでdumpしながらcurlでuriを変化して何度か叩いた際の結果
```
$ sudo tshark -Y http.request -T fields -e http.host -e ip.dst -e http.request.full_uri
Running as user "root" and group "root". This could be dangerous.
Capturing on 'enp0s3'
www.google.com	216.58.200.164	http://www.google.com/
www.google.com	216.58.220.228	http://www.google.com/hoge/fuga
www.google.com	216.58.197.164	http://www.google.com/test
```

### 特定のリクエストを抽出する
- GETサンプル
```
$ sudo tshark -Y 'http.request.method == GET and tcp contains "test"'
Running as user "root" and group "root". This could be dangerous.
Capturing on 'enp0s3'
 18 2.307003322    10.0.2.15 -> 72.30.35.9   HTTP 165 GET /test HTTP/1.1 
188 15.721177872    10.0.2.15 -> 98.138.219.231 HTTP 173 GET /testtesttest HTTP/1.1 
```
- POSTサンプル
```
// リクエスト例
$ curl -X POST -d 'hoge=test' 'http://www.yahoo.co.jp/aaa'
```
```
$ sudo tshark -Y 'http.request.method == POST and tcp contains "test"'
Running as user "root" and group "root". This could be dangerous.
Capturing on 'enp0s3'
 24 2.903970063    10.0.2.15 -> 182.22.25.252 HTTP 214 POST /aaa HTTP/1.1  (application/x-www-form-urlencoded)
```

### POSTリクエストを抽出する
tsharkを使うことでGET以外のデータを抽出することができて非常に便利です。
```
$ sudo tshark -Y http.request.method==POST -Tfields -e text
Running as user "root" and group "root". This could be dangerous.
Capturing on 'enp0s3'
POST /aaa HTTP/1.1\r\n,\r\n,HTTP request 1/1,hoge=test
POST /aaa HTTP/1.1\r\n,\r\n,HTTP request 1/1,hoge=test&fuga=zzzzzzzzz&piyo=AAAAAAAAAAAAAAAAAAA
```

