# 概要
RFC8471: The Token Binding Protocol Version 1.0

Token Bindingは、TLSレイヤやHTTPレイヤの実装も必要であり複雑な設計となるため、ブラウザサポートも中止や停滞しています。このため、今後普及の可能性はほぼ無いと思われます。

# 解決したい課題
Bearer Tokenが何かしらの原因で漏れてしまうと不正に入手した人でもそれを使うことができてしまいます。
Tokenを取得してしまった何者かがTokenのExportやReplay攻撃を防ぐことが可能になるようにしたい。

# 解決方法
トークンの発行者と所持者が同一であることを確認できるようにTLS通信経路と暗号学的にトークン情報と紐づけて発酵できるようにする(bindする)

(なお、このドキュメントはTLS1.2について扱っていて、TLS1.3はスコープ外です)

# 参考資料

## Section1. Introduction

Token Bindingをサポートしているクライアントにトークンを発行する際には、サーバはトークン中にクライアントのToken Binding IDを含めています。

のちに、クライアントがToken Binding IDを含めたトークンを渡した際に、サーバはトークン中のIDがクライアントで接続されたToken BindingのIDと一致しているかどうかを確認します。マッチしなかった場合には、そのトークンを拒否します。


## Section2. Token Binding Protocol Overview


```
enum {
    rsa2048_pkcs1.5(0), rsa2048_pss(1), ecdsap256(2), (255)
} TokenBindingKeyParameters;

struct {
    opaque modulus<1..2^16-1>;
    opaque publicexponent<1..2^8-1>;
} RSAPublicKey;

struct {
    opaque point <1..2^8-1>;
} TB_ECPoint;

struct {
    TokenBindingKeyParameters key_parameters;
    uint16 key_length;  /* Length (in bytes) of the following
                           TokenBindingID.TokenBindingPublicKey */
    select (key_parameters) {
        case rsa2048_pkcs1.5:
        case rsa2048_pss:
            RSAPublicKey rsapubkey;
        case ecdsap256:
            TB_ECPoint point;
    } TokenBindingPublicKey;
} TokenBindingID;

enum {
    (255)        /* No initial TB_ExtensionType registrations */
} TB_ExtensionType;

struct {
    TB_ExtensionType extension_type;
    opaque extension_data<0..2^16-1>;
} TB_Extension;

enum {
    provided_token_binding(0), referred_token_binding(1), (255)
} TokenBindingType;

struct {
    TokenBindingType tokenbinding_type;
    TokenBindingID tokenbindingid;
    opaque signature<64..2^16-1>; /* Signature over the concatenation
                                     of tokenbinding_type,
                                     key_parameters, and EKM */
    TB_Extension extensions<0..2^16-1>;
} TokenBinding;

struct {
    TokenBinding tokenbindings<132..2^16-1>;     // 複数含まれる
} TokenBindingMessage;
```




## Section3. Token Binding Protocol Message


このドキュメントでは2つのToken Bindingタイプを定義してます。
- provided_token_binding
  - サーバへ接続する際にToken Bindingを確立するために使われる
- referred_token_binding
  - 他のサーバに対しての提示するためのトークンとして要求される


## Section4. Establishing a Token Binding


# 公式
- https://datatracker.ietf.org/doc/html/rfc8471
