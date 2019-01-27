# 概要
RFC5746はrenegtiaion_infoのTLS拡張に関するもので、脆弱性(CVE-2009-3555)が発見されたことからこの拡張が策定されました。

Renegotiationは次のタイミングでサーバからHelloRetryRequestをクライアント側に送付することで引き起こします。
- クライアント認証をさせたい場合
- 鍵のアップデート処理を行いたい場合

renegtiaion_info拡張が導入する前は、Renegotiationした後との２つの情報を結びつけることができませんでした。
このため第三者が無理やりHelloRetryRequestを行うことでハンドシェイクの脆弱性(CVE-2009-3555: 後述)が発見された。

このため、クライント及びサーバで前のハンドシェイクのFinishedを保存しておきそれをもとにハンドシェイクを行ないます。それによって前のハンドシェイクのFinished値を知っている人しかハンドシェイクができなくなります。


なお、TLS1.3からは次のメッセージが追加された為に、リネゴーシエーション自体が廃止されました。
- クライアント認証をさせたい場合はPost-Handshake Authenticationメッセージが追加された
  - https://tools.ietf.org/html/rfc8446#section-4.6.2
- 鍵のアップデート処理を行いたい場合はKey and Initialization Vector Updateメッセージが追加された
  - https://tools.ietf.org/html/rfc8446#section-4.6.3


# 脆弱性(CVE-2009-3555)

これは、2009年にTLSv1, SSL3のハンドシェイク過程において「TLSリネゴシエーション時の中間者攻撃」の脆弱性(CVE-2009-3555)が発見されたのをきっかけとしてできたRFCで、TLS1.2から2年後の2010年2月にリリースされました。
この脆弱性はHTTP, IMAP, SMTPをはじめとする多くのTLS/SSLに依存するプロトコルに影響を与えます。
この脆弱性を防ぐ対応としてrenegotion_info拡張(RFC5746)が提案されるようになりました。

この仕様はリネゴシエーションの新しい仕組みであると同時に、バージョン及び拡張に対するintorelanceが開発者によって解消されることを期待しています。

SSLv3, TLS 1.0, TLS 1.1などの仕様ではClientHelloに拡張を含んでしまうとハンドシェイクエラーを引き起こしてしまう可能性があります。そこで、RFC5746の3.3節ではTLS_EMPTY_RENEGOTIATION_INFO_SCSVによる第２のメカニズムを提供しています(RFC7507で規定)。


# この拡張ができた背景とそれが解決するもの

TLS1.2よりまでは後方互換性に関する明確な記述は存在しなかった。
そのために、プロトコルバージョンが大きいと未知であると判断したり、好ましくなければハンドシェイクを拒否したりする実装が発生する。
また、TLS1.2に対応した最初のブラウザIEはデフォルトでTLS1.1とTLS1.2を両方とも無効にした状態でローンチされました。
この盲点をついたのがCVE-2009-3555です。

この脆弱性のためにこのTLS1.2以降の拡張としてrenegtiaion_info拡張が策定され、TLS1.2未満のためにTLS_EMPTY_RENEGOTIATION_INFO_SCSVによるメカニズムを提供することでダウングレード攻撃を防ぐことを意図している。

この拡張がないと攻撃者はクライアントの接続を乗っ取ることができます。クライアントからは攻撃が見えず、サーバでは通常の接続とみなされてしまいます。
以下はRFC5746に記載された図ですが、簡単にその問題点の概略を説明します。
- あらかじめAttackerとServerでの初期ハンドシェイクを行います。
- Attackerはその時の秘密鍵情報を保存しておきます。
- Clientがハンドシェイクをしようとした際に、Attackerは先ほどまでServerとやりとりしていたHandshakeに必要な情報を返却します。
- ClientはServerと安全に通信していると思い込んでいますが、Attackerによってその通信が見えてしまいます。
```
Client                        Attacker                        Server
------                        -------                         ------
                                  <----------- Handshake ---------->
                                  <======= Initial Traffic ========>
<--------------------------  Handshake ============================>
<======================== Client Traffic ==========================>
```
TODO: 上の図にはHelloRetryRequestが記載されていないので記載が必要


# 解決方法
この拡張を導入することによって、ConnectionState(RFC5246#section6.1)に次の３つの変数が追加されます。(詳しくは詳細で説明)
- secure_renegotiation
- client_verify_data
- server_verify_data

これによって、HelloRetryRequestを送付されてきて強制的にハンドシェイクをRetryする場合にも、前回やりとりしていたFinishedのハンドシェイクを必要とするようになります。


# 詳細

## 仕様詳細
主に3.2節から3.7節について説明する
- https://tools.ietf.org/html/rfc5746#section-3.2

この拡張を実現するにあたって、クライアントとサーバはTLSコネクション状態ごとに次の３つのフラグをConnectionState(RFC5246#section6.1)に追加すると規定しています。
- secure_renegotiation: このコネクションでセキュアなリネゴシエーションが利用されるかどうかを示すフラグ
- client_verify_data: 前回のハンドシェイクでクライアントによってFinishedメッセージから送付されたデータ。現行のTLSバージョンやCipherではこの値は12byteで、SSL3では36byteの値となります。
- server_verify_data: 前回のハンドシェイクでサーバによってFinishedメッセージから送付されたデータ

ここではクライアントとサーバの次の４つのフェーズについてのRFC仕様を説明します
- クライアントの初回ハンドシェイクの挙動(3.4節)
- クライアントのセキュアリネゴシエーションの挙動(3.5節)
- サーバの初回ハンドシェイクの挙動(3.6節)
- サーバのセキュアリネゴシエーションの挙動(3.7節)

TODO: サーバ側ではFinishedの値を保存しておくようになったということなのか??

### クライアントの初回ハンドシェイクの挙動
- ClientHelloでenegotiation_info拡張とTLS_EMPTY_RENEGOTIATION_INFO_SCSVを同時に載せることは推奨されていません。
- クライアントがServerHelloを受け取ったら、クライアントはrenegotiation_info拡張が含まれているかどうかをチェックしなければならない。
  - 拡張が存在しなければ、secure_renegotiation=falseをセットする。
  - 拡張が存在すれば、secure_renegotiation=trueをセットする。そして、クライアントはrenegotiated_connectionフィールドが0かどうかをチェックしなければならない、もし0じゃなかったらhandshake_failureアラートを送付してハンドシェイクをabortしなければならない。


### クライアントのセキュアリネゴシエーションの挙動
secure_renegotiation=trueとなっている場合にのみ次の処理を行います。

- クライアントはClientHelloのrenegotiation_info中に保存されたclient_verify_dataを含めなければならない。SCSVを含めてはならない。
- ServerHelloを受信したら、クライアントはrenegotiation_info拡張が存在するかどうかを検証しなければならない。もしなかったら、クライアントはハンドシェイクをabortしなければならない。
- クライアントはrenegotiated_connectionフィールドが保存されたclient_verify_dataとserver_verify_dataの値が保存されたものと一致するかどうかを検証しなければならない。
- ハンドシェイクが完了したら、クライアントは新しいclient_verify_dataとserver_verify_dataの値を保存しておく必要がある。

### サーバの初回ハンドシェイクの挙動
- サーバはClientHello中にrenegotiation_infoが含まれているかどうかをチェックしなければならない。
  - 拡張が存在しなければ、secure_renegotiation=falseをセットする。
  - 拡張が存在すれば、secure_renegotiation=trueをセットする。そして、サーバはrenegotiated_connectionフィールドが0かどうかをチェックしなければならない、もし0じゃなかったらhandshake_failureアラートを送付してハンドシェイクをabortしなければならない。
- TLS_EMPTY_RENEGOTIATION_INFO_SCSV SCSVもrenegotiation_info拡張も含まれていなければ、secure_renegotiation=falseをセットする。この場合だと、いくつかのサーバはハンドシェイクを終了するかもしれない。
  - secure_renegotiation=trueとセットされたのであれば、サーバはrenegotiation_infoをServerHelloに含めなければならない
- ハンドシェイクが完了したら、サーバはclient_verify_dataとserver_verify_data valuesを将来の利用のために保存する必要がある。

### サーバのセキュアリネゴシエーションの挙動
secure_renegotiation=trueとなっている場合にのみ次の処理を行います。
- ClientHelloを受信したら、サーバはTLS_EMPTY_RENEGOTIATION_INFO_SCSVを含んでいないことを検証する。もし含まれていたら、サーバはハンドシェイクをアボートしなければならない。
- サーバはrenegotiation_info拡張を検証しなければならない。もしなかったら、ハンドシェイクをabortしなければならない (???)
- サーバはrenegotiated_connectionの値が保存されたclient_verify_dataの値と一致するかどうかを検証しなければならない。もし一致しなかったら、サーバはハンドシェイクをabortしなければならない。
- サーバはServerHelloのrenegotiation_infoに保存されたclient_verify_dataとserver_verify_dataを含めなければならない
- ハンドシェイクが完了したら、サーバは新しいclient_verify_dataとserver_verify_dataの値を保存しておく必要がある。

次の２つについてもRFC5246での繰り返しになりますが規定されています。
- この仕様を実装するTLSサーバは、クライアントから知らない拡張がきても無視しなければならない。
- また、サポートするバージョンよりも大きなバージョン番号がきたとしても受け入れなければならない。そしてサーバとクライアントで共通の最も高いバージョンでネゴシエーションします。

## TLS_FALLBACK_SCSVについて
ClientHello.cipher_suitesに次を含むことによって、レガシーなサーバとの接続のためにダウングレードして再接続を行っていることを意味します。これはCipherではありませんのでWorkAroundとなります。
```
TLS_FALLBACK_SCSV          {0x56, 0x00}
```

サーバ側はTLS_FALLBACK_SCSVが含まれていた場合、自身がサポートするTLS最高のバージョンがクライアントから指定されたTLSバージョンで指定できないことがわかると、inappropriate_fallback fatalアラートを返却します。
サーバはTLS_FALLBACK_SCSVが含まれていない場合や、クライアントから指定されたバージョンがサーバがサポートする最高バージョンよりも高い場合には通常のハンドシェイクを行います。

## データ

### データ書式(rfc5746#section-3.2)
```
struct {
    opaque renegotiated_connection<0..255>;
} RenegotiationInfo;
```

renegotiated_connectionの仕様については初回ハンドシェイク時かリネゴシエーション時かで中身が変わってきます。
- 初回ハンドシェイク時
  - 接続に対する初回ハンドシェイクだとrenegotiated_connectionはClientHello及びServerHello共に長さ0となります。
- リネゴシエーション時
  - リネゴシエーションするClientHelloだと、client_verify_dataが入ります。
  - リネゴシエーションするServerHelloだと、client_verify_dataとserver_verify_dataの結合されたデータを含みます


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

## openssl
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

# TODO
- パケットをキャプチャーしても0以外(リネゴシエーション)が入っていることをみたことがないが、本当に使われている?
- session_idを指定したときとのロジックでの共通点は何か?
- RFCの読み込みがまだ足りない
- opensslコマンドでrenegotiation_infoを含める方法について調査する
- CVE-2009-3555をちゃんと理解すること
- データ構造サンプルにはTLS_EMPTY_RENEGOTIATION_INFO_SCSVが存在していないので追加すること

# 参考URL
- https://rms-digicert.ne.jp/howto/basis/ssl-renego.html

# SeeAlso
- RFC5746: Transport Layer Security (TLS) Renegotiation Indication Extension
  - https://tools.ietf.org/html/rfc5746
- RFC7507: TLS Fallback Signaling Cipher Suite Value (SCSV) for Preventing Protocol Downgrade Attacks
  - https://tools.ietf.org/html/rfc7507
- 「TLSリネゴシエーション時の中間者攻撃」の脆弱性(CVE-2009-3555)
  - http://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2009-3555
