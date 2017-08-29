# BGP(Boarder Gateway Protooclについて
経路の対象範囲によって次の２つにわけられます。
- 外部で使用するEGP(Exterior Gateway Protocol)
  - BGP
- 内部で使用するIGP(Interior Gateway Protocol)
  - RIPv2, EIGRP, OSPF, IS-IS

BGPはAS(Autonomous System)間で経路情報を交換するEGPです。  
EGPには「EGP」、「BGP」という２つの経路制御プロトコルが存在しますが(名前がEGPで煩わしいですが)、現在ではBGPv4が使われています。

AS番号は
- プライベート番号
  - 1〜64511: インターネット全体で一意のAS番号
- グローバルAS番号
  - 64512〜65535: 組織内部で自由に使えるAS番号

BGPの概要についてはあきみちさんが解説してくれた記事がすごいわかりやすいです
- http://www.geekpage.jp/blog/?id=2009/2/20/1

BGPは誰とお隣さんになるかが重要なお金の臭いがするプロトコルであるとのことです。

# 特徴
インターネット上のBGPが設定されているルータは、2016年時点で60万ルート以上をルーティングテーブルに保持しています。
以下に特徴を記します。
- 転送プロトコルにTCP(port179)を利用する
- 差分アップデートをおこなう
  - 定期的ではなく変更があったときだけ交換する。
- ルーターはプレフィックス値が大きい方を優先して経路を書き換える(longest matching)

企業、個人などがインターネットに接続するためにはISPとの契約が必要となります。  
ISP内部ではIGPs(OSPF,  EIGRP)などが動作しています。

# 設定方法
- 1. BGPプロセス起動
```
(config)# router bgp (AS番号)
```
- 2. ネイバーの設定
  - ネイバーIPアドレスとそのネイバーが所属するAS番号を指定する事によって、手動で設定が必要となります。
  - このAS番号と1で設定したAS番号を比較することにより、EBGPネイバーかIBGPネイバーか判断できます
```
(config-router)# neighbor (ネイバーIPアドレス) remote-as (AS番号)
```
- 3. BGPルート設定
```
(config-router)# network (ネットワーク番号) mask (サブネットマスク)
```
- 4. BGP設定確認
```
# show ip bgp summary
# show ip bgp neighbor (ネイバーIPアドレス)
# show ip bgp
```


# BGP関連の障害
BGPを広告するためのAS番号はISP大手プロバイダーや大企業では所有しています。
BGPでは広告されてきた情報を基本的に信用する「来る経路拒まず」といった仕様が経路ハイジャッキング(BGPハイジャッキング)を引き起こす原因となっています。
- 2009年2月17日 世界的インターネット経路障害解説
  - http://www.geekpage.jp/blog/?id=2009/2/17/2
  - http://www.geekpage.jp/blog/?id=2009/2/20/2
- 「YouTubeのネットワークはパキスタン・テレコミュニケーションのAS内にある」と広告した障害
  - https://japan.cnet.com/article/20368032/
- 2017年8月25日の大規模インターネット障害
  - http://www.geekpage.jp/blog/?id=2017-8-29-1


電子証明書を使ってBGPの経路情報を認証するプロトコルも複数検討されているが，実装にはかなり時間がかかりそうだとのこと

# 公式
- A Border Gateway Protocol 4 (BGP-4)
  - https://tools.ietf.org/html/rfc4271
