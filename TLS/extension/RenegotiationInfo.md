# 概要・背景
RFC5746はrenegtiaion_infoのTLS拡張に関するものです。
これは、2009年にTLSv1, SSL3のハンドシェイク過程において脆弱性(CVE-2009-3555)が発見されたのをきっかけとしてできたRFCで、2010年2月にリリースされました。
この脆弱性はHTTP, IMAP, SMTPをはじめとする多くのTLS/SSLに依存するプロトコルに影響を与えます。

# 詳細
### 利用方法
クライアント側は次のいずれかをとります
- (1) 初期ハンドシェイクのClientHello中にrenegotiation_infoフィールドまたは使用可能な暗号アルゴリズムとしてTLS_EMPTY_RENEGOTIATION_INFO_SCSV(Signaling Cipher Suite Value (SCSV))の追加
  - TLS_EMPTY_RENEGOTIATION_INFO_SCSV暗号スイートは、レガシーなサーバとの接続のためにダウングレードして再接続を行っていることを意味します。
- (2) 初期ハンドシェイクのClientHello中にrenegotiation_infoを追加する

サーバ側は次のチェックを行います
- クライアントはサーバから返却されたServerHelloメッセージ中にrenegotiation_infoがあるかどうか、またはcipher_suites中にTLS_EMPTY_RENEGOTIATION_INFO_SCSVが存在するかどうかをチェックします。 (TODO: この一文本当にあってる?)


### データ構造サンプル
- ServerHelloサンプル
```
Extension: renegotiation_info
    Type: renegotiation_info (0xff01)
    Length: 1
    Renegotiation Info extension
        Renegotiation info extension length: 0
```
- ServerHelloからの応答サンプル
```
Extension: renegotiation_info
    Type: renegotiation_info (0xff01)
    Length: 1
    Renegotiation Info extension
        Renegotiation info extension length: 0
```

### opensslコマンドでTLS_EMPTY_RENEGOTIATION_INFO_SCSVを追加する
fallback_scsvオプションを付与するとClientHelloのCipher Suites中にTLS_EMPTY_RENEGOTIATION_INFO_SCSVが追加されます。
```
$ openssl s_client -fallback_scsv -connect google.com:443
```

以下の例は、Googleではfallback_scsvオプションを付与して次のコマンドでアクセスするとGoogleのサーバでは実際にTLS1.2に対応しているのでアラートが返されてハンドシェイクが中断されることが確認できます。
```
$ openssl s_client -connect google.com:443 -tls1 -fallback_scsv
CONNECTED(00000003)
95616:error:1409443E:SSL routines:SSL3_READ_BYTES:tlsv1 alert inappropriate fallback:/SourceCache/OpenSSL098/OpenSSL098-52.40.1/src/ssl/s3_pkt.c:1145:SSL alert number 86
95616:error:1409E0E5:SSL routines:SSL3_WRITE_BYTES:ssl handshake failure:/SourceCache/OpenSSL098/OpenSSL098-52.40.1/src/ssl/s3_pkt.c:566:
```

# MEMO
- https://rms-digicert.ne.jp/howto/basis/ssl-renego.html

# TODO
- データ構造サンプルにはTLS_EMPTY_RENEGOTIATION_INFO_SCSVが存在していないので追加すること
- renegotiation_infoはどのような時に付与されるの? ときどきwiresharkで表示されるのはなぜか?
- opensslコマンドでrenegotiation_infoを含める方法について調査する
- CVE-2009-3555をちゃんと理解すること

# SeeAlso
- RFC5746: Transport Layer Security (TLS) Renegotiation Indication Extension
  - https://tools.ietf.org/html/rfc5746
