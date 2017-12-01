# 概要
OCSP Must StaplingはOCSPを必ず必須にしようというものです。

# 詳細
### OCSP MustStaplingの背景
実はブラウザは失効情報が確認できなかったときには多くがsoft failを採用しています。
ブラウザがCRLやOCSPレスポンダから失効情報を取得するのに時間を要したり、タイムアウトした際には、ブラウザは失効しているのか、有効なのかが判断つかない状態となります。  

この時にhard fail, soft failといった考え方があります。
- hard fail
  - 積極的にWebサーバにアクセスさせないような表示すとする
- soft fail
  - webサーバにはアクセスさせるようにする。

しかし、ブラウザがsoft failを採用していると悪用される攻撃などもあります。
- 中間者攻撃
- DDos攻撃

これがOCSP Must Staplingが登場することになった背景です。

### OCSP Must Stapling対応方法
OCSP Must Staplingに対応させるためには次の要件が必要となります。
- サーバ証明書にその拡張(証明書 extension (OID 1.3.6.1.5.5.7.1.24 id-pe-tlsfeature))を含める必要があります。CAに発行してもらいます。
- クライアント側もOCSP Must Staplingに対応しています。上記拡張が含まれたサーバ証明書を受け取ったらOCSP Must Staplingと認識します。

### OCSP Must Staplingのサーバ証明書発行方法(openssl)
以下にその手順が記載されています。
- https://scotthelme.co.uk/ocsp-must-staple/

openssl.confでv3_reqセクションがreq_extensionsにセットされていることを確認します。
```
req_extensions = v3_req
```

openssl.confでv3_reqセクションがreq_extensionsにセットされていることを確認します。
```
[ v3_req ]
basicConstraints = CA:FALSE
keyUsage = nonRepudiation, digitalSignature, keyEncipherment
subjectAltName = @alt_names
1.3.6.1.5.5.7.1.24 = DER:30:03:02:01:05                          #ここを追加
```

またはopenssl-1.1.0以降であれば次のようにtlsfeature = status_requestを指定することで、OCSP Must Staplingフラグを指定できるようです。
```
[ v3_req ]
basicConstraints = CA:FALSE
keyUsage = nonRepudiation, digitalSignature, keyEncipherment
subjectAltName = @alt_names
tlsfeature = status_request
```

上記の1.3.6.1.5.5.7.1.24というのは証明書extensionを表しています。

- 1.3.6.1.5.5.7.1配下は以下で定義されています。
  - https://tools.ietf.org/html/rfc7299#section-3.4
- 最後の"24"は以下のrfcで割り当てられています
  - https://tools.ietf.org/html/rfc7633#section-6


OCSP Must Staplingを利用しているサーバのサーバ証明書は次のような感じになっていました。
```
$ echo |  openssl s_client -connect scotthelme.co.uk:443 -showcerts | openssl x509 -text
(snip)
            X509v3 Subject Alternative Name: 
                DNS:ecdsa.scotthelme.co.uk, DNS:scotthelme.co.uk, DNS:www.scotthelme.co.uk, DNS:xn--lv8haa.scotthelme.co.uk
            1.3.6.1.5.5.7.1.24: 
                0....
(snip)
```

# 参考URL
- RFC7633
  - https://tools.ietf.org/html/rfc7633
- https://scotthelme.co.uk/ocsp-must-staple/
