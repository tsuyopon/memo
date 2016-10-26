# 概要
tcpdumpコマンドについて

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


### etho0の80番ポートを除く
```
$ tcpdump -Z root -i eth0 -X -S port 80
```

### 通信の内容をASCIIで表示したい場合
HTTPリクエストやレスポンスのヘッダ及びボディを綺麗に出力してみることができます。
```
$ sudo tcpdump -i eth0 -A port 80
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

### tcpdumpの出力がわからない
このサイトをみるとよさそうです。
- http://net-newbie.com/tcpip/tcp/tcpdump.html

# 参考
- http://qiita.com/tossh/items/4cd33693965ef231bd2a
- https://danielmiessler.com/study/tcpdump/#gs.SOxLWhY
 - tcpdumpでいろいろなことができることがわかるサイト
- http://net-newbie.com/tcpip/tcp/tcpdump.html
 - TCPの出力の見方の参考になるサイト
