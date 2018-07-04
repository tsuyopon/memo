# 概要
DNSSEC(DNS SECurity Extensions)とは、公開鍵暗号を使うことによってDNS検索側が受け取ったレコードの出自・完全性を検証する事ができる仕組みです。
つまり、DNSの情報に電子署名を付与することでDNSデータが正式な発行元のデータであることを検証できる仕組みです。
名前的には暗号化されてそうですが、DNSSEC自体には暗号化の仕組みはありません。


- DNSSEC特徴
  - DNS情報に電子署名を付与することで、正式な発行元のデータであることを検証する仕組み
  - 暗号化はされていない
  - 従来のDNSとの互換性を維持した拡張である。
  - キャッシュポイズニングを防ぐことができる。
  - DNSSECでは、ドメイン名の見間違いや打ち間違いを狙うタイプのフィッシングには対応できません。("-"と"ー"の違いなど)
  - DNSSECを利用するためにはサーバ側もクライアント側も対応している必要がある


DNSSECのコア仕様についてはRFC 4033、4034、4035の三つにより定められています。

# 詳細

### DNSSEC利用の流れ
- TBD


### リクエストを確認する
```
$ dig +dnssec jprs.jp

; <<>> DiG 9.8.3-P1 <<>> +dnssec jprs.jp
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 45896
;; flags: qr rd ra; QUERY: 1, ANSWER: 3, AUTHORITY: 6, ADDITIONAL: 25

;; OPT PSEUDOSECTION:
; EDNS: version: 0, flags: do; udp: 4096
;; QUESTION SECTION:
;jprs.jp.			IN	A

;; ANSWER SECTION:
jprs.jp.		300	IN	A	117.104.133.164
jprs.jp.		300	IN	RRSIG	A 8 2 300 20180726032950 20180626032950 19155 jprs.jp. uQ20h2eVVidLzvm0lVOIiNbq2t0W6tKNKKuQVrX1WpumGlCz+xlukbwf WMMJOHQVT5fL+RNVEtKQwP6q5F2y2lppkp8LXML0MDkREB9gJy55Qy0v 4Ydtt6IBb2rudtFqMhlkeoR1F4qj8GFc363Jww6LgAZEni76f+P/9vcx A+A=

;; AUTHORITY SECTION:
jprs.jp.		50468	IN	NS	ns1.jprs.jp.
jprs.jp.		50468	IN	NS	ns2.jprs.jp.
jprs.jp.		86400	IN	RRSIG	NS 8 2 86400 20180726032950 20180626032950 19155 jprs.jp. U2ZViqor4LsCmIf6C66aBqUNCDwfC6djIGhOb9/MpG2J0EoDjXQOF/xf gcHa18mm44OzM5z3EZQwNMIOj9xgVeJsAa6PXdF3rLeJVMOJGqeNakTY uvsGMdCubGm4aPrcY9j5MvmRA04t1XunEDAcR2DIuMsYhtQXVYfyyRVU SXA=

;; ADDITIONAL SECTION:
ns1.jprs.jp.		50468	IN	AAAA	2001:df0:8::a153
ns2.jprs.jp.		50468	IN	AAAA	2001:df0:8::a253
ns1.jprs.jp.		50468	IN	A	202.11.16.49
ns2.jprs.jp.		50468	IN	A	202.11.16.59
ns1.jprs.jp.		86400	IN	RRSIG	A 8 3 86400 20180726032950 20180626032950 19155 jprs.jp. kbFmJ/s6X4sHxUtWmxQCYdmQVI80Gx7FFfzlpnPZ63XUl515Ea1TASji Kfr/x/CBPHQ7sym6uippJU54TerKVShfVwFBqb7zYZ8AuoFTXN+FluLV 9Lsnb6Sb8aZXC7yDStz8Wr8uChnIZbX63sFdzNne8J6ldZBiom8fVoxD wc4=
ns1.jprs.jp.		86400	IN	RRSIG	A 8 3 86400 20180726032950 20180626032950 22053 jprs.jp. kyJewuOPvLcNVqosPjs/8I7Xsteif3mpUV+X2j0CeOpB2Lz9AQMqlvdg Qbt94drwXe/1LnmpxMdjNX7tE2i+aRzZ5ZC0gEHMe9ZjoaE+yVXTOUMh 6AFWOTRoyo2p0AHypfLWd4NaICyw+0WKae15bx7qFkYwbyOTFrLAMpwg Cho=

;; Query time: 34 msec
;; SERVER: 192.168.3.1#53(192.168.3.1)
;; WHEN: Wed Jul  4 03:59:29 2018
;; MSG SIZE  rcvd: 3640
```

### 対応状況
- BINDバージョン9.3以降
  - 9.7からはSmart SigningというDNSSEC用の仕組みが機能追加された

### DNSSECにより規定されたレコード情報
- DNSKEY
  - ZSK
  - KSK
- RRSIG(Resource Record SIGnature)
- DS
- NSEC, NSEC3, NSEC3PARAM


# TODO
- とりあえず概要の概要を把握した程度なので、全然深掘りできていない
- DNSSEC登録方法がわからない
- DNSSECクライアントからの利用方法がわからない
- DNSSECにより規定された各種レコードがわからない
- コアRFC読んでいない


# 参考URL
- DNSSECとは
  - https://jprs.jp/dnssec/doc/dnssec.pdf
- DNSSEC FAQ
  - https://jprs.jp/dnssec/faq.html
- JAIPA セキュリティ部会 DNSSEC勉強会 DNSSEC 技術と運用
  - ガチ向けの資料
  - https://dnssec.jp/wp-content/uploads/2012/07/20101110-JAIPA-DNSSEC-1.pdf
