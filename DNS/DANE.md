# DNS-based Authentication of Named Entities（DANE)について

認証に関する情報をDNSを用いて通信するための仕組みです。
最近ではDNSSECの導入によってDNSサーバへの問い合わせに対する応答が正しいかどうかの正当性の検証が可能になることで、DNSの信頼できる認証手段としてDNSを利用できるようになりました。

DNSを従来とは異なる方法として次のような用途で利用しようという動きがIETFで議論してDANE(デーン)が登場しました。
- サーバ認証
- OpenPGPによる認証

もともとはこのDANEが登場してきた背景としては、「信頼された認証局(トラストアンカー)のもとで発行された証明書はすべてのドメインに対して有効である」という考え方に対する反省からのようです。
不正な第三者が認証局を狙い証明書を不正に発行して中間者攻撃に悪用される可能性を秘めています。

DANEでは、DNSとドメインに証明書を発行する認証局あるいは発行された証明書そのものの紐付けを行うことで上記のように悪用されることを防ぎます。

DANEではユースケースと要求事項がRFC6394で定義され、仕様についてはRFC6698で定義されています。DANEはDNSSECの利用を前提としていて、そこにDNSのレコードとしてTLSAというレコードを定義して、この中に証明書の情報を格納します。


# 詳細

### TLSAフィールドについて
TLSA RRレコードは次のような書式となります。
```
_443._tcp.www.example.com. IN TLSA ( 0 0 1 d2abde240d7cd3ee6b4b28c54df034b97983a1d16e8a410e4561cb106618e971 )
```

TLSAの後の()で囲まれた４つのフィールドについて説明します。
- 第1フィールド(Certificate Usage): 照合対象の証明書種別
```
0: CA constraint(中間CA証明書)
1: Service certificate constraint(CAから発行されたサーバ証明書)
2: Trust anchor assertion(ルートCA証明書)
3: Domain-issued certificate(自己署名証明書でも問題なしとして判断します)
```
- 第2フィールド(Selector): 照合対象が証明書(Full certificate)か証明書中に含まれる公開鍵情報(subjectPublicKeyInfo)かを表します。
```
0: Full certificate
1: subjectPublicKeyInfo
```
- 第3フィールド(Matching Type): Selectorで指定された文字列を第４フィールドでどのように表現するか
```
0: Exact match
1: SHA-256
2: SHA-512
```
- 第4フィールド(Certiicate Association Data): 検証される文字列
  - 第１フィールドから第３フィールドで指定されたデータを参照する


詳細については以下を参考のこと
- https://tools.ietf.org/html/rfc6698#section-2.1

# 参考URL
- Use Cases and Requirements for DNS-Based Authentication of Named Entities (DANE)
  - https://tools.ietf.org/html/rfc6394
- The DNS-Based Authentication of Named Entities (DANE) Transport Layer Security (TLS) Protocol: TLSA
  - 認証局(CA)無し TLS クライアントとサーバーのエンティティを認証するための方法として、RFC6698 で提案されている。
  - https://tools.ietf.org/html/rfc6698
- Adding Acronyms to Simplify Conversations about DNS-Based Authentication of Named Entities (DANE)
  - https://tools.ietf.org/html/rfc7218

