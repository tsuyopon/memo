# 概要
apacheプロセスが詰まった際にどのようなパケットを応答するのかを確認して、ロードバランサの挙動がどのようになるのかを整理する

# 手順
シングルプロセスモードでapacheを起動して
```
$ sudo gdb /usr/sbin/httpd 
(gdb) run -X
Ctrl + Cを押下して、プロセスを停止しておく
```

その後、何個かのセッションからcurlへリクエストする(ここでは8080ポートと家庭)
```
$ curl http://127.0.0.1:8080
```

予めtcpdumpをしておく
```
$ sudo tcpdump -i lo port 8080
```

curlリクエストされると同時に次のような出力が表示される。何回リクエストしても次のような感じになる。
```
09:18:48.910933 IP localhost.52576 > localhost.webcache: Flags [S], seq 645502471, win 43690, options [mss 65495,sackOK,TS val 23326348 ecr 0,nop,wscale 7], length 0
22:25:02.518308 IP localhost.webcache > localhost.52576: Flags [S.], seq 2083140616, ack 645502472, win 43690, options [mss 65495,sackOK,TS val 23326348 ecr 23326348,nop,wscale 7], length 0
09:18:48.910980 IP localhost.52576 > localhost.webcache: Flags [.], ack 1, win 342, options [nop,nop,TS val 23326348 ecr 23326348], length 0
09:18:48.911039 IP localhost.52576 > localhost.webcache: Flags [P.], seq 1:79, ack 1, win 342, options [nop,nop,TS val 23326348 ecr 23326348], length 78: HTTP: GET / HTTP/1.1
09:18:48.911059 IP localhost.webcache > localhost.52576: Flags [.], ack 79, win 342, options [nop,nop,TS val 23326348 ecr 23326348], length 0
```

上記からわかることは、apacheプロセスをgdbにより強制的に停止していたとしても次の動作は行われることがわかる。
- SYNを送信
- SYN+ACKを受信
- ACKを送信
- データ送付を送信
- データ応答のACKを受信

余談だが、プロンプトの応答が帰ってこないcurlコマンドをCtrl + Cするとちゃんとお作法よくFINをサーバに送って、そのackが帰ってきている。
```
09:18:54.687262 IP localhost.52576 > localhost.webcache: Flags [F.], seq 79, ack 1, win 342, options [nop,nop,TS val 23332125 ecr 23326348], length 0
09:18:54.730939 IP localhost.webcache > localhost.52576: Flags [.], ack 80, win 342, options [nop,nop,TS val 23332168 ecr 23332125], length 0
```

例えば、ロードバランサ配下にApacheがこのような停止状態に陥っている場合にはどのようになるのだろうか？

L4ロードバランサの場合には、次の流れで処理が行われる。接続先サーバはクライアントからsynを受け取った時点で判定される。
- 1. クライアント(以下、CL)はロードバランサ(以下、LB)にsynを送付
- 2. ** ロードバランサはsynのパケットを受信した段階で接続先サーバを決定する **
- 3. LBはCLからsynを受信すると、サーバ(以下、SV)にsynを送付
- 4. SVはLBからsynを受信すると、LBにsyn+ackを応答
- 5. LBはSVからsyn+ackを受信すると、CLにsyn+ackを応答
- 6. CLはLBからsyn+ackを受信すると、LBへackパケットを送付
- 7. LBはCLからackパケットを受信すると、SVにackパケットを送付
- 8. CLはackを送ると、LBへHTTPリクエストを送信
- 9. LBはCLからHTTPリクエストを受信すると、SVにHTTPリクエストを送付
- 10. SVからLBへHTTPリクエストに応答するackが返却される
- 11. LBからCLへHTTPリクエストに応答するackが返却される
- 12. 以降SVから、LBへデータがかえらない。つまり、LBからCLもデータがかえらない。
- 13. あまりに待ち時間が長いと、セッションタイムアウト時刻により切れる


L7 HTTPロードバランサの場合には、次の流れで処理が行われる。接続先サーバはクライアントからHTTPリクエストを受け取った時点で判定される。
- 1. クライアント(以下、CL)からsynをロードバランサ(以下、LB)に送付
- 2. LBはsynを受信すると、syn+ackをCLに送付
- 3. CLはsyn+ackを受信すると、ackをLBに送付
- 4. CLはHTTPリクエストをLBに送付
- 5. LBはHTTPリクエスト応答としてackをCLに送付  (おそらくここであってる?もしくは、LBから返すとき?)
- 6. ** HTTPリクエストをもとにしてLBはサーバ(以下、SV)を確定させる **
- 7. LBはサーバ(以下、SV)にsynを送付
- 8. SVはsynを受信すると、syn+ackをLBに送付
- 9. LBはsyn+ackを受信すると、ackをSVに送付
- 10. LBはSVにHTTPデータを送付する
- 11. SVはLBにデータに対する応答のackを返却する
- 12. 以降SVから、LBへデータがかえらない。つまり、LBからCLもデータがかえらない。
- 13. あまりに待ち時間が長いと、セッションタイムアウト時刻により切れる

# まとめ
apacheプロセスをgdbのシングルプロセスで立ち上げ、無理やり処理を停止させることでLBが詰まった場合の処理を確認した

tcpdumpではApacheが詰まっていたとしてもサーバ側はHTTPデータを受信するとその応答のackを返す
- SYNを送信
- SYN+ACKを受信
- ACKを送信
- データ送付を送信
- データ応答のACKを受信

また、そこからL4ロードバランサ、L7 HTTPロードバランサの挙動がどのようになるのかを整理した


