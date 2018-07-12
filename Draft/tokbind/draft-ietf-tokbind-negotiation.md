# Transport Layer Security (TLS) Extension for Token Binding Protocol Negotiation

# 解決したい課題
- TLSを使ってToken Bindingプロトコルのバージョン及び鍵パラメータのネゴシエーションをしたい 

# 解決方法
- TLS拡張としてtoken_bindingを定義します。ClientHelloの中にバージョンとToken Bindingの鍵パラメータを含めることによって、サーバ側とのネゴシエーションを行います。
- この仕様書ではTLS1.2以前のみが有効で、TLS1.3以降はスコープ外となっています。

# 仕様詳細
### ClientHello
token_binding拡張では次のデータが送付されます。
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

- TB_ProtocolVersionにはサポートしている最も高いプロトコルバージョンを指定します。
- key_parameters_listにはクライアントがサポートしているToken Binding鍵パラメータのリストが指定されます。

### 振る舞い
クライアントは次に該当する状態を満たしたら、token_binding拡張をunsupported_extensionアラートにて終了しなければならない
- クライアントがClientHello中にtoken_binding拡張を含めなかったが、ServerHelloでtoken_bindingが返された場合
- クライアントによって提示されたtoken_binding_versionが高かった場合
- key_parameters_listがToken Binding鍵交換identifierよりも多かった場合(?)
- key_parameters_listにクライアントによって提示されないものが含まれた場合
- TLS1.2や古いバージョンが使われているが、Extended Master Secret拡張やTLS Renegotiation Indicationが指定されなかった場合

# 参考URL
- Token Bindingについて
  - lepidumの前田さんによるわかりやすい記事
  - https://lepidum.co.jp/blog/2016-12-20/tokbind/
