# A DANE Record and DNSSEC Authentication Chain Extension for TLS

# 解決したい課題
(本当かどうかはちゃんとまだ未検証だが)
サーバ証明書が本来の想定元から送付されてきたものかどうかについては、ServerKeyExchangeの署名を検証することで妥当な証明書かどうかを検証している。でないと、第三者が仲介して独自のサーバ証明書を送付することがありえる。
近年DNSSECというDNSが信頼できる情報として扱うことができる仕組みが整備されてきたので、その仕組みを利用してもっとサーバ証明書の検証を容易にしたい。


# 解決方法
この提案は、DNSSECの署名検証に必要な認証チェインの情報をTLSの通信を通じてクライアント側に伝えるもので、クライアント側がその認証チェインのみをDNSを使って問い合わせるだけで、認証の処理ができるようにするものです。
TLSを拡張して、クライアントからの要求があればTLSA RRとルートからTLSA RRの検証に必要とされるすべてのDS, DNSKEYをTLSでクライアントに送付します。

TLSAレコードはRFC6698で規定される。次のようにDNS RRとして登録されている。
```
_443._tcp.www.example.com. IN TLSA ( 0 0 1 d2abde240d7cd3ee6b4b28c54df034b97983a1d16e8a410e4561cb106618e971 )
```

このTLSAについてはクライアントアプリ側の実装も普及しないと全体として普及しない問題があります。

# 仕様詳細
- 1. クライアントはdnssec_chain拡張をClientHelloに含んでリクエストする
- 2. サーバはdnssec_chain拡張を受け取ったら次の情報をServerHelloにレスポンスする。この中にはDNSのレコードセット(RRset)と一致する署名(RRSIG)が含まれる
  - この値は定期的に更新されるらしい
```
opaque AuthenticationChain<1..2^16-1>
```
- 3. クライアントはサーバからdnssec_chainを受け取る。そして、DNSから該当レコードを取得してDNSから取得した結果の署名検証を行い妥当性を検証する。
- 4. トラストアンカーの検証を行う
- 5. TLSAレコードの値をサーバ認証として利用する。

# 参考URL
- RFC6698: The DNS-Based Authentication of Named Entities (DANE) Transport Layer Security (TLS) Protocol: TLSA
  - TLSA RRについて
  - https://tools.ietf.org/html/rfc6698
- スライド
  - https://www.slideshare.net/shumonhuque/dane-and-dnssec-authentication-chain-extension-for-tls
- IETF 93 スライド
  - https://datatracker.ietf.org/meeting/93/materials/slides-93-tls-1
- IETF 95 スライド
  - https://datatracker.ietf.org/meeting/95/materials/slides-95-tls-3
- IETF 97 スライド
  - https://datatracker.ietf.org/meeting/97/materials/slides-97-tls-dnssec-chain-validation-00
- IETF 98 スライド
  - https://datatracker.ietf.org/meeting/98/materials/slides-98-tls-a-dane-record-and-dnssec-authentication-chain-extension-00
- IETF 99 スライド
  - https://datatracker.ietf.org/meeting/99/materials/slides-99-tls-sessb-dnssec-chain-validation-00
- IETF 101 スライド
  - https://datatracker.ietf.org/meeting/101/materials/slides-101-tls-sessa-dnssec-chain-extension-00


# TODO
- トラストアンカーによるルート証明書の検証処理はこの仕様では省略されない認識だけどあっている?
