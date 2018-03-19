# 概要
SupportedVersionsはTLS拡張でTLS1.3のdraft中で規定されているものです。
- https://tools.ietf.org/html/draft-ietf-tls-tls13-26#section-4.2.1

まだ、IANAから正式に割り当ては行われていません。
TLS1.3以降はバージョン番号をTLS拡張の中に隠蔽します。それによりミドルボックスによる意図せぬフィルタリングの弊害を避けることを目的としています。

この拡張はTLS1.3としてサポートしているTLSバージョンのリストをTLSサーバに伝えるものです。この拡張が付与されない場合にはTLS1.3未満として扱うことになります。

# 詳細

### 仕様詳細
- クライアントからどのTLSバージョンが利用できるかどうかをTLS拡張によって優先度の高い順番で示すことができます。
- TLS1.3からはClientHello.versionはClientHello.legacy_versionに変換しました。0x0304(本来ならばTLS1.3を表すはずだがミドルボックス問題で使われない)かそれ以上に大きな値であればClientHelloを受信するとすぐにハンドシェイクをアボートしてもよい。
- この拡張が存在していたら、サーバ側はバージョンを決定するのに拡張に含まれるバージョンを用いて決定しなければならない
- 拡張中に含まれる不明なバージョンがあれば無視しなければならない
- TLS1.3以前のバージョンとネゴシエートするサーバはServerHello.versionをセットしなければならず、その際にsupported_versions拡張を送付してはならない。サーバはServerHelloのsupported_versionにClientHelloに含まれる拡張のリストから選択したものを提示する必要があります。
- supported_version拡張において、もしクライアントが提示していないバージョンがサーバから送付されてきた場合にはllegal_parameterアラートとしてハンドシェイクをアボートしなければなりません。

### データ構造
```
struct {
    select (Handshake.msg_type) {
        case client_hello:
             ProtocolVersion versions<2..254>;

        case server_hello: /* and HelloRetryRequest */
             ProtocolVersion selected_version;
    };
} SupportedVersions;
```

### サンプルデータ(draft 23)
- ClientHello
```
Extension: supported_versions (len=11)
    Type: supported_versions (43)
    Length: 11
    Supported Versions length: 10
    Supported Version: Unknown (0x1a1a)
    Supported Version: TLS 1.3 (draft 23) (0x7f17)
    Supported Version: TLS 1.2 (0x0303)
    Supported Version: TLS 1.1 (0x0302)
    Supported Version: TLS 1.0 (0x0301)
```
- ServerHello
```
Extension: supported_versions (len=2)
    Type: supported_versions (43)
    Length: 2
    Supported Version: TLS 1.3 (draft 23) (0x7f17)
```

# SeeAlso
- The Transport Layer Security (TLS) Protocol Version 1.3 (draft-ietf-tls-tls13-26)
  - https://tools.ietf.org/html/draft-ietf-tls-tls13-26#section-4.2.1
