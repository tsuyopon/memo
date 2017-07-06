# 概要
GSLB(Global Server Load Balancing)の略称で広域負荷分散と呼ばれることがあります。  
地理的に離れた複数のサイトに負荷を分散したり、障害時にサイト単位のフェイルオーバーを行ったりする場合に利用されます。  

DNSは最初はUDPで接続を行い512byteを超過すると、TCPで同じ内容を問い合わせるといったことが行われている。
このような背景もあり
- http://internet.watch.impress.co.jp/docs/event/625963.html

GSLBの主要機能は次の通りです。
- 誘導先サーバへのヘルスチェック
- DNSサーバとしてDNSクエリに対するダイナミックなレスポンスを行う

OSSのソフトウェアとしてはgdnsdというものがあるとのことです。
- http://qiita.com/jh1vxw/items/7ce5d14e9f964f001257

# アルゴリズム

### Citrix製品
次のモードが存在する
- Round Robin
- Least Response Time
- Least Connections
- Least Bandwidth
- Least Packets
- Source IP Hash
- Custom Load

参考
- https://docs.citrix.com/en-us/netscaler/12/global-server-load-balancing/methods/configuring-algorithm-based-methods.html
- How GSLB works(CITRIX)
  - https://docs.citrix.com/en-us/netscaler/10-1/ns-tmg-wrapper-10-con/netscaler-gslb-gen-wrapper-10-con/ns-gslb-how-works-con.html

この辺も参考になりそう
- https://kb.wisc.edu/ns/page.php?id=13201
