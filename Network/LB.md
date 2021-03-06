# 概要
ロードバランサについて

# DSR
## L2DSRとは

### しくみ
一言でいうと、LBがMACアドレス書き換えを行うことによって実現する方式です。
- 1. あらかじめロードバランサ配下のサーバにはloopbackアドレスとしてロードバランサのIPを設定しておく
- 2. リクエストが来ると、ロードバランサが宛先MACアドレスをロードバランサ配下にある負荷分散対象のサーバのMACアドレスに書き換える。SrcIpやDstIpは書き換えない。
- 3. サーバにリクエストが来るとDstIpはloopbackに設定されているので自身のパケットであると解釈する。
- 4. ロードバランサを経由せずにクライアントにパケットを直接返すことが可能(Direct Server Return)

L2DSRを使うと次のメリットがあります。
- 全体のスループットが上がります。

デメリットとしては
- リアルサーバでVIP設定やロードバランサを経由しないstaticルートの設定が必要

### 疑問点
なぜloopbackに対してVIPのIPを設定する必要があるのか?
- リクエスト元(ブラウザ等)が送付してきたDstIPの値を、レスポンスのSrcIPへと入れる必要があるから。
- VIPのIPへの応答としてARP応答を行わないようにするため(通称arp problemというらしい。「dsr arp problem」などで検索すると出てくる) これによってルーターでIPアドレスが衝突することはなくなる。

arp problemについては以下のリンクを参考にすると良い
- https://www.loadbalancer.org/blog/yahoos-l3-direct-server-return-an-alternative-to-lvs-tun-explored/
- 6. LVS: The ARP Problem
  - http://www.austintek.com/LVS/LVS-HOWTO/HOWTO/LVS-HOWTO.arp_problem.html


## L3DSRとは
一言でいうと、LBがL3レイヤーのビットを書き換えて、リアルサーバがそれをチェックしてSrcアドレスをVIPアドレスとして変換する方式です。

- 1. リクエストが送られてくる。
- 2. ロードバランサに到達するとDstIPを負荷分散対象サーバに書き換えて、TOSビット(DSCP)を0x22に書き換える
- 3. リアルサーバではDSCPが0x22ならば、SrcIPアドレスをVIPアドレス(loopbackで設定した値)に変換して、L2DSRと同様に直接クライアントに返却する。

L3DSRを実施する前にはあらかじめリアルサーバにloopbackの設定が入っていることと、DSCPの値が設定されている必要がある。


- 参考
  - https://www.janog.gr.jp/meeting/janog33/doc/janog33-lbaas-miyata-1.pdf

# ロードバランサ(スイッチ)

## L2スイッチ
通信したい相手がどのポートにつながっているかを記憶してパケットを転送する方式です。  
L2スイッチにはどのポート番号にはどのMACアドレスが接続されているのかという情報が記録されています。

- 1. client -> serverにパケットを送る
- 2. 同一ネットワーク内部でL2スイッチを経由するのであれば、L2のMACアドレスのみをみて送信先を決定する。
- 3. L2switch -> serverにパケットが送られる。

## L3スイッチ
L3スイッチは、L2スイッチの機能に加えてIPアドレスを用いたルーティングができる。
ルーティングやVLANの知識がないとL３スイッチの理解は難しい。
- http://sc.ipsecdh.net/entry/656 
** TODO**


## L4スイッチ
ロードバランサはL3スイッチ、L4スイッチやL7スイッチなどと呼ばれる違いが存在する。
L3スイッチではIPヘッダまでの解析を行うのにたいして、L4スイッチではTCPヘッダ内のプロトコル番号やセッションシーケンス番号の情報を解析したり書き換えたりすることによって最適化を行う。
- 1. clinet->LBにsyn   (L4スイッチではここで接続元IPと接続先Portから接続先を決定する)
- 2. LB->serverにsyn
- 3. server->LBにsyn+ack
- 4. LB->clientにsyn+ack
- 5. client->LBにack
- 6. LB->serverにack
- 7. client->LBにHTTP要求
- 8. LB->serverにHTTP要求
- 9. server->LBにHTTP応答
- 10. LB->clientにHTTP応答

同一IP, 同一ポートからのリクエストは同じサーバに転送するなどを行うことが可能です。

レイヤ4スイッチにも様々な振り分けアルゴリズムが存在する。
- https://ja.wikipedia.org/wiki/%E3%83%AC%E3%82%A4%E3%83%A44%E3%82%B9%E3%82%A4%E3%83%83%E3%83%81

上記では次のような手法が紹介されている。
- ラウンドロビン
- ハッシュ
- リーストコネクション
- リーストトラフィック
- リーストプロセッシング
- ファーストアンサー
- L7分散

## L4スイッチ(TLS終端)

## L7スイッチ
L7ではLayer7の情報で接続先を決定します。L4スイッチと接続先の決定箇所が異なる点を確認してください。
- 1. clinet->LBにsyn
- 2. LB->clientにsyn+ack
- 3. client->LBにack
- 4. client->LBにHTTP要求 (ここでUser-AgentやCookieなど様々なL7データで接続先を決定します)
- 5. LB->serverにsyn
- 6. server->LBにsyn+ack
- 7. LB->serverにack
- 8. LB->serverにHTTP要求
- 9. server->LBにHTTP応答

trafficserverなどはソフトウェアとしてはこの部分に該当します。

# 参考
L4とL7ロードバランサの違いを図解付きで比較していてわかりやすい
- https://www.janog.gr.jp/meeting/janog32/program/lb.html

