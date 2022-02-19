# 概要
RFC8472: Transport Layer Security (TLS) Extension for Token Binding Protocol Negotiation
基本的にRFC8471-8472はセットであり、このRFCはTLS拡張の挙動について規定しているものです。

# 解決したい課題
RFC8471のToken bindingを使いたい場合、サーバとクライアント間でToken BindingプロトコルのバージョンとToken Bindingのパラメータ(署名アルゴリズムと長さ )を合意する必要がある。


# 解決方法
token_binding拡張を定義することで、TLSメッセージ上でネゴシエートできるようにする。
TLS1.2やそれ以前で対応しています。なお、TLS1.3以降はこのドキュメントのスコープ外となっています。
TLS1.3は以下で規定していると書かれているが期限ぎれになっている
- https://datatracker.ietf.org/doc/html/draft-ietf-tokbind-tls13-03


# 詳細

次のTLS拡張が定義されます。
```
   enum {
       token_binding(24), (65535)
   } ExtensionType;
```

TLS拡張のデータフィールドであるextension_dataフィールドには以下の情報が含まれます
```
   struct {
       uint8 major;
       uint8 minor;
   } TB_ProtocolVersion;

   enum {
       rsa2048_pkcs1.5(0), rsa2048_pss(1), ecdsap256(2), (255)
   } TokenBindingKeyParameters;

   struct {
       TB_ProtocolVersion token_binding_version;
       TokenBindingKeyParameters key_parameters_list<1..2^8-1>
   } TokenBindingParameters;
```

- TB_ProtocolVersion
  - クライアントがそのコネクション中で利用したいToken Bindingプロトコルのバージョンを指定します。
  - もしクライアントが複数サポートしていたら、最新を指定すべきとなっています。
  - もしサーバによって選択されたバージョンをクライアントがサポートしていない場合には、そのコネクションはtoken bindingがないものとして進める。
- TokenBindingKeyParameters
  - クライアントによってサポートされるToken Bindingキーパラメータの識別リストが含まれている。
  - これはクライアントが好ましい順番で指定されます。


TokenBindingをサポートしていて、ClientHelloにtoken_binding拡張が含まれたメッセージを受信したサーバは、以下の条件を全て満たしたらServerHello中にtoken_binding拡張を応答します。
- クライアントによって提示されたToken Bindingプロトコルのバージョンまたはそれより下位のバージョンをサポートしている
- サーバがクライアントのリストからTokenBindingKeyParametersで受け入れられる値を見つけた場合
- サーバはextended_master_secret拡張、renegotiation_indicationででネゴシエートされる場合


サーバは次の情報を拡張として応答します。
- token_binding_version
  - 以下のいずれかのうち小さい方の値をかえします
    - token_binding拡張中にクライアントによって提示されたToken Bindingバージョン
    - サーバによってサポートされる最も高いToken Bindingバージョン
- key_parameters_list
  - クライアントリストからサーバによって選択された1つの値のみを持ちます。


もしクライアントがサーバによって選択されたバージョンをサポートしてない場合、Token Bindingなしで接続を進めます。
クライアントは、クライアントが提示したtoken_bindingバージョン以上の多くのバージョンをサポートしているという要件はない。



# 参考
- https://datatracker.ietf.org/doc/html/rfc8472
