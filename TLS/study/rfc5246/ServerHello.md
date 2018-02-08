# 概要
この資料はRFC5246のServer Helloについてです。
https://tools.ietf.org/html/rfc5246#section-7.4.1.3

# 詳細
- このメッセージが送られる時は:
```
アルゴリズムの受け入れられる設定を見つけることができた場合に、サーバはClientHelloへの応答としてこのメッセージを送信するでしょう。
もし、受け入れられるアルゴリズムを見つけることができなかったら、handshake failure alert(fatalアラート)を返すでしょう.
```

このメッセージの構造は次のようになります。
```
struct {
    ProtocolVersion server_version;
    Random random;
    SessionID session_id;
    CipherSuite cipher_suite;
    CompressionMethod compression_method;
    select (extensions_present) {
        case false:
            struct {};
        case true:
            Extension extensions<0..2^16-1>;        // Vectors: https://tools.ietf.org/html/rfc5246#section-4.3  (TODO)
    };
} ServerHello;
```

拡張があるかどうかは、ServerHello中においてcompression_methodフィールドに続いてバイト数が存在するかどうかどうかによって決定します。


上記項目についてそれぞれ説明を行う

- server_version
  - このフィールドはclient hello中のクライアントやserverによる最も高いバージョンサポートによるものから提案されたもののうち、低い値がはいります (TODO: 確認)
  - この仕様書のバージョンはversion 3.3. です。
  - 後方互換製についての詳細については以下を参照のこと
  - https://tools.ietf.org/html/rfc5246#appendix-E  (TODO: やる)

- random
  - サーバによって生成される。ClientHello.randomとは独立して生成されなければならない

- session_id
  - このコネクションに一致するセッションを識別するidである。
  - ClientHello.session_idが空でなかったら、サーバはセッションキャッシュ中にマッチするものを探します。
  -	もし、マッチするものが見つかって、サーバは指定されたセッション状態を使って新しいコネクションを確立しようとしたら、サーバはクライアントによって渡されてきたものと同様の値を応答します。
  - これはセッションを再開することを示していて、そして、直接Finishedメッセージにすすめるように指示しています。    (RFC5246 Page36 abbrebiated handshake)
  - さもなければ、このフィールドには新しいセッションの識別子として異なった値を含むことになってしまうでしょう。
  - サーバはセッションをキャッシュしておらず、故に再開することができなかったということを示すために空のsession_idを返却するかもしれません。
  - もし、セッションが再開されたら元々のネゴシエーションで利用していたcipher suiteを使って再開しなければなりません。
  - たとえもし以前に発行されたsession_idが存在してたとしても、サーバはセッションを再開しなければならないといった要求事項は存在しないことに注意する。
  - クライアントはフルネゴシエーションするための準備をしなければならない。
  -  Clients MUST be prepared to do a full negotiation -- including negotiating new cipher suites -- during any handshake.

- cipher_suite
  - ClientHello.cipher_suitesのリスト中からサーバによって選択された１つのcipher suiteが入る。
    - https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-4
  - 再開されたセッションに対しては、このフィールドは再開されたセッション時のcipher suiteが入ります。  (TODO: レジストリ確認)

- compression_method
  - ClientHello.compression_methodsのリストの中からサーバによって選択された１つの圧縮アルゴリズムが入る。
  - 再開されたセッションに対しては、このフィールドは再開されたセッションの値が入る

- extensions
  - 拡張のリストを表す。
  - クライアントによって提示された拡張のみがサーバ側で提示されるリストに現れることに注意する。	

