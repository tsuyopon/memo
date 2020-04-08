# 概要
tcpdumpコマンドについて

- うまくいかないときにはSELinuxが有効になっていることを疑う

# 詳細
### オプション
```
-i 	  キャプチャするインターフェースを指定します。-iオプションを指定しない場合はループバックを除いた一番小さいインターフェースが指定されます。（大体の場合はeth0ですね。）
-n 	  アドレスやポート番号を名前に変換しないで表示します。プロトコル名のみ解決させない場合は-nnとなる。
-s 	  キャプチャするサイズを指定します。-s0ですべてキャプチャします。
-vvv   	詳細を出力します。
-w 	  生データをそのままファイルに書き込みます。WireSharkやEtherealで開く場合に便利です。
-X 	  16進とASCII文字で表示を行います。
-e    イーサネットヘッダも付与
-c    指定された回数だけ表示して終了する
-S    Absolute Sequence Numberを表示する
-q    プロトコル情報の表示をすこしだけにする
-E    IPSECトラフィックの解読を行う
-tttt 読みやすい時刻を表示する("2016-10-26 16:49:15.038959"こんな感じの形式の時刻で表示)
```

オプションについてはこの辺も参考のこと
- https://danielmiessler.com/study/tcpdump/#gs.SOxLWhY

### tcpdumpの基本的な出力の確認方法について

3way handshakeでは次の流れで応答される
- 1: SYN=1, ACK=0
- 2: SYN=1, ACK=1
- 3: SYN=0, ACK=1

Flagsの後にある意味は次の通り
- S: SYN
  - 接続要求を表す
- P: PUSH
  - 受信したデータをすみやかに上位アプリケーションに引き渡すように要求するためのフラグである。
  - 通常の通信では受信したデータはバッファ領域などに貯めておき、一定の時間や量に達したら上位のプロトコルなどに渡すようになっているが、PSHフラグが1にセットされたパケットはすぐにデータを渡さなくてはならない
- F: FIN
  - TCP接続を終了させるためにセットされる
- R: RST
  - TCP接続を中断または拒否したい場合にセットされる
- U: URG
  - 実際に利用されているアプリケーションはほとんど存在しない
- W: ECN CWR
- E: ECN-Echo
- .: 上記いずれのビットも立っていない場合(ACK)
  - ACKはAcknowledgeで「承認」を意味する
たとえば、[S]としてSYN、[S.]としてSYN+ACK、[.]としてACKが返却されていることを確認することができます。

TCPヘッダの中にはOptionsという項目が可変長で存在しますtcpdumpではoptions [〜]の中にパケット解析した結果が入ってきます。
- mss(Maximum Segment Size)
  - MSSとは、TCPが格納するユーザデータで「受信可能なセグメントサイズの最大値」です。EthernetだとMTUが1500byteの場合には、そこからヘッダ40byteを差し引いた1460byteがMSSとなります。
- wscale
  - ウィンドウスケール
- TS val
  - TCPタイムスタンプを表す。パケットが送付された順番を決定する役割を併せ持つ
  - https://unix.stackexchange.com/questions/233830/what-does-ts-val-mean-in-tcpdumps-output
- TS ecr
  - ECR(Echo reply) は、ACK時は、元のパケットのTSvalをTSecrに複写する。
  - https://tools.ietf.org/html/rfc7323
- nop
  - パディング
- sackOK
  - Selective Acknowledgmentが有効であることを表している。これは3way handshakeの段階で示されます。
  - 「一部のデータだけ正しく受け取った」ということを意味を持つ信号であり、通信に失敗したデータだけの再送信を要求する際に使用される。

オプションについてはIANAで規定されている
- https://www.iana.org/assignments/tcp-parameters/tcp-parameters.xhtml

lengthについては上位層に渡すデータがあればサイズが存在するようになります。これはFlagsに通常「P」が付与されるようです。

以下はtcpdumpで443を検知している際に次のコマンドを実行した際のtcpdump出力結果です。
```
$ echo Q | openssl s_client -connect <IP>:443
```

```
$ sudo tcpdump -i lo port 443
11:23:51.053250 IP localhost.localdomain.45332 > localhost.localdomain.https: Flags [S], seq 2625778895, win 43690, options [mss 65495,sackOK,TS val 70728129 ecr 0,nop,wscale 7], length 0
06:56:43.089509 IP localhost.localdomain.https > localhost.localdomain.45332: Flags [S.], seq 1340900893, ack 2625778896, win 43690, options [mss 65495,sackOK,TS val 70728129 ecr 70728129,nop,wscale 7], length 0
11:23:51.053293 IP localhost.localdomain.45332 > localhost.localdomain.https: Flags [.], ack 1, win 342, options [nop,nop,TS val 70728129 ecr 70728129], length 0
11:23:51.054754 IP localhost.localdomain.45332 > localhost.localdomain.https: Flags [P.], seq 1:290, ack 1, win 342, options [nop,nop,TS val 70728132 ecr 70728129], length 289
11:23:51.055049 IP localhost.localdomain.https > localhost.localdomain.45332: Flags [.], ack 290, win 350, options [nop,nop,TS val 70728133 ecr 70728132], length 0
11:23:51.057300 IP localhost.localdomain.https > localhost.localdomain.45332: Flags [P.], seq 1:1201, ack 290, win 350, options [nop,nop,TS val 70728134 ecr 70728132], length 1200
11:23:51.058701 IP localhost.localdomain.45332 > localhost.localdomain.https: Flags [.], ack 1201, win 1365, options [nop,nop,TS val 70728137 ecr 70728134], length 0
11:23:51.060400 IP localhost.localdomain.45332 > localhost.localdomain.https: Flags [P.], seq 290:416, ack 1201, win 1365, options [nop,nop,TS val 70728138 ecr 70728134], length 126
11:23:51.061267 IP localhost.localdomain.https > localhost.localdomain.45332: Flags [P.], seq 1201:1427, ack 416, win 350, options [nop,nop,TS val 70728139 ecr 70728138], length 226
11:23:51.062307 IP localhost.localdomain.45332 > localhost.localdomain.https: Flags [P.], seq 416:447, ack 1427, win 1384, options [nop,nop,TS val 70728140 ecr 70728139], length 31
11:23:51.062337 IP localhost.localdomain.45332 > localhost.localdomain.https: Flags [F.], seq 447, ack 1427, win 1384, options [nop,nop,TS val 70728140 ecr 70728139], length 0
11:23:51.064926 IP localhost.localdomain.https > localhost.localdomain.45332: Flags [F.], seq 1427, ack 448, win 350, options [nop,nop,TS val 70728143 ecr 70728140], length 0
11:23:51.064956 IP localhost.localdomain.45332 > localhost.localdomain.https: Flags [.], ack 1428, win 1384, options [nop,nop,TS val 70728143 ecr 70728143], length 0
```

### 対象となるデバイスリストを確認する
```
$ sudo tcpdump -D
1.enp0s3
2.nflog (Linux netfilter log (NFLOG) interface)
3.nfqueue (Linux netfilter queue (NFQUEUE) interface)
4.usbmon1 (USB bus number 1)
5.any (Pseudo-device that captures on all interfaces)
6.lo [Loopback]
```

### 通信の内容をASCIIで表示したい場合(よく使う!!!)
HTTPリクエストやレスポンスのヘッダ及びボディを綺麗に出力してみることができます。
```
$ sudo tcpdump -i eth0 -A port 80
```

通常は上記で十分だが、メモリダンプ(X)とさらにパケットデータを表示したい(s0)場合には次のようにします。デバッグ用途などで使うレベルでしょう。
```
$ sudo tcpdump -i eth0 -A port 80 -s0 -X
```

### etho0の80番ポートを除く
```
$ tcpdump -Z root -i eth0 -X -S port 80
```
Zオプションでは実行ユーザを指定している。

### pcapなどに吐かせたい
pcapに吐かせると、wiresharkなどで表示させることができます。
```
$ tcpdump -i eth0 -w ~/log_%Y%m%d_%H%M%S.pcap
```

### 100MBごとにローテーションしたい
test.pcap, test.pcap1, test.pcap2, ...とファイル名の末尾に数字が付与される。
```
$ tcpdump -i eth0 -C 100 -w test.pcap
```

### 一定時間でローテーションしたい
以下の例だと3600秒でローテーションさせることになる。
```
$ tcpdump -i eth0 -G 3600 -w test.pcap
```

ローテーションさせるときに自動的に圧縮させるようにするにはzオプションを指定すると良い。
```
$ tcpdump -i eth0 -G 3600 -w test.pcap -z gzip
```

### wireshirkで覗いてみる
tcpdumpは-wでダンプファイルを指定して結果をファイルに保存できます。
```
$ tcpdump -w dumpfile
```

このファイルをwireshirkに流し込むと見ることができます。

### IP、ポート、レンジなどによる指定
- 送信元ipアドレスを指定
```
$ tcpdump src host [src_ip]
```
- 送信先ipアドレスを指定
```
$ tcpdump dst host [dst_ip]
```
- 送信元もしくは送信先にipアドレスを指定
```
$ tcpdump host [target_ip]
```
- 送信元ipアドレスレンジを指定
```
$ tcpdump src net [src_net] mask [net_mask]
```
- 送信先ipアドレスレンジを指定
```
$ tcpdump dst net [dst_net] mask [net_mask]
```
- 送信元もしくは送信先にipアドレスレンジを指定
```
$ tcpdump net [target_net] mask [net_mask]
```
- 送信元のポート番号を指定
```
$ tcpdump src port [port_num]
```
- 送信先のポート番号を指定
```
$ tcpdump dst port [port_num]
```
- 送信先もしくは送信元のポート番号を指定
```
$ tcpdump port [port_num]
```

### IPアドレスをドメイン解決せずにそのまま表示する
```
$ tcpdump -i eth0 -A -nn
```

### 条件を組み合わせる
and
```
$ tcpdump port 80 and host 192.168.0.100    // andは&&でも代用可能
```

or
```
$ tcpdump port 80 or host 192.168.0.100     // orは||でも代用可能
```

not
```
$ tcpdump not src 192.168.10.100           // notは!でも代用可能
```

andとorの複合
```
$ tcpdump src \(192.168.10.100 or 192.168.20.100 \) and port 23
```

### ポート範囲指定
```
$ tcpdump portrange 21-23
$ tcpdump less 32
$ tcpdump greater 128
```

### キャプチャーの軽量〜重量までのパターン
- Basic communication // see the basics without many options
```
# tcpdump -nS
```
- Basic communication (very verbose) // see a good amount of traffic, with verbosity and no name help
```
# tcpdump -nnvvS
```
- A deeper look at the traffic // adds -X for payload but doesn’t grab any more of the packet
```
# tcpdump -nnvvXS
```
- Heavy packet viewing // the final “s” increases the snaplength, grabbing the whole packet
```
# tcpdump -nnvvXSs 1514
```

### オプションによる判定
- URG(URGENT)パケットの表示
```
# tcpdump 'tcp[13] & 32!='
```
- ACK(ACKNOWLEDGE)パケットの表示
```
# tcpdump 'tcp[13] & 16!=0'
```
- PSH(PUSH)パケットの表示
```
# tcpdump 'tcp[13] & 8!='
```
- RST(RESET)パケットの表示
```
# tcpdump 'tcp[13] & 4!='
```
- SYN(SYNCHRONIZE)パケットの表示
```
# tcpdump 'tcp[13] & 2!='
```
- FIN(FINISH)パケットの表示
```
# tcpdump 'tcp[13] & 1!='
```
- SYN+ACKパケットの表示
```
# tcpdump 'tcp[13]=1'
```

### そのほか
- ICMP
```
# tcpdump icmp
```
- IPv6
```
# tcpdump ip6
```
- RST+SYNフラグがセットされたパケットの表示
```
# tcpdump 'tcp[13] = 6'
```
- Evil Bitがセットされた場合
```
# tcpdump 'ip[6] & 128 != 0'
```

### 80番ポートの送受信で利用されるHTTP IPv4全てのパケットを表示する
以下の例ではSYN, FIN, ACKなどのパケットが除外されることになります。
```
$ sudo tcpdump -i any 'tcp port 80 and (((ip[2:2] - ((ip[0]&0xf)<<2)) - ((tcp[12]&0xf0)>>2)) != 0)'
10:44:27.999829 IP localhost.44980 > localhost.webcache: Flags [P.], seq 72352275:72352357, ack 463199513, win 342, options [nop,nop,TS val 353883924 ecr 353883924], length 82: HTTP: GET /test HTTP/1.1
10:44:28.000446 IP localhost.webcache > localhost.44980: Flags [P.], seq 1:363, ack 82, win 342, options [nop,nop,TS val 353883924 ecr 353883924], length 362: HTTP: HTTP/1.1 404 Not Found
```

### mysqlへのクエリリクエストを知りたい
こんな感じのリクエストを発行すれば良い。前者は簡易にSELECTだけ知りたいような場合。後者は文字列で抽出している。
```
# tcpdump -l -i eth0 -A -n -s 0 dst port 3306 | grep SELECT
```
や

呼ばれたリクエストが知りたい場合。次のようにすると簡易なSQL文がわかるが、見ての通りゴミデータまで含まれてしまう。ただし、prepared statementなどは?として扱われるのでまた別の方法が必要
```
$ sudo tcpdump -i lo -s 0 -l -w - dst port 3306 | awk '{if(match($0, /SELECT|UPDATE|DELETE|INSERT|SET|COMMIT|ROLLBACK|CREATE|DROP|ALTER|CALL/, _)){ print $0; } }'
tcpdump: listening on lo, link-type EN10MB (Ethernet), capture size 262144 bytes
/d/ZSELECT * FROM citym=[?TB4)?@@??
                                   ?}r?@i?)?g?(
/t?/dSELECT DATABASE()q=[^?B4)?@@??
                                   ?}r?Vi?i?g?(
/{/t?SELECT * FROM cityr=[??B4)?@@??
                                    ?}r?i????(
/?i/{SHOW CREATE PROCEDURES~=[;B4)?@@???
```

- http://keyamb.hatenablog.com/entry/20120725/1343198298
- https://web.liferay.com/ja/web/david.zhang/blog/-/blogs/how-to-catch-mysql-sql-with-tcpdump-in-linux

### tcpdumpの出力がわからない
このサイトをみるとよさそうです。
- http://net-newbie.com/tcpip/tcp/tcpdump.html

# 参考
- http://qiita.com/tossh/items/4cd33693965ef231bd2a
- https://danielmiessler.com/study/tcpdump/#gs.SOxLWhY
  - tcpdumpでいろいろなことができることがわかるサイト
- http://net-newbie.com/tcpip/tcp/tcpdump.html
  - TCPの出力の見方の参考になるサイト
