# TLS 1.3 Extension for Certificate-based Authentication with an External Pre-Shared Key
Note: External Pre-Shared KeyはTLS1.2でのPre-Shared-Keyを意味する

# 解決したい課題
将来的には量子コンピュータによってDHやECDHなどの暗号も簡単に解けてしまう問題が出てくる。
将来的な脅威にも対応できるように外部PSKを用いた証明書認証について定義しておく必要がある。

# 解決方法
証明書と外部PSKのコンビネーションによるサーバ認証を許容する方法をTLS1.3拡張(tls_cert_with_extern_psk)として規定する。

クライアント側とサーバ側の処理は次のとおりです。
- クライアントはClientHello中にtls_cert_with_extern_pskを含みます。
  - tls_cert_with_extern_psk拡張はkey_share拡張, psk_key_exchange_modes拡張, pre_shared_key拡張と一緒に使われなければなりません。
  - pre_shared_key拡張はClientHello中の最後のメッセージでなければなりません。
  - tls_cert_with_extern_psk拡張は初回ハンドシェイクのみで使われることを意図しているので、early_data拡張と一緒に送付してはなりません。
- サーバー側がpre_shared_key拡張の中にある1つを証明書ベースの認証として利用しようとしているのであれば、その時にはサーバ側はServerHello中にtls_cert_with_extern_pskを含めます。
  - tls_cert_with_extern_psk拡張は、key_share拡張とpre_shared_key拡張と共に利用されなければならない。
  - もし、サーバ側にクライアントによって提示された外部PSKで受け入れられるものが存在しない場合には、tls_cert_with_extern_psk拡張はServerHelloメッセージから取り除かれなければならない。
  - tls_cert_with_extern_pskネゴシエーションが成功するということは、選択された外部PSKや(EC)DHEで共有する秘密値の両方を包括するTLS1.3鍵スケジューリングの処理を要求します。その結果として、Early Secret, Handshake Secret, Master Secretの値についてはすべて選択された外部PSKに依存します。


この拡張における特徴は次の通りです。
- 特徴
  - サーバ認証やクライアントの追加認証は、証明書内の公開鍵で検証できるかどうかといった署名生成の能力に依存します。
    - なお、認証プロセスは選択されたPSKによって変わることはありません。
  - それぞれの外部PSKというのは唯一のハッシュアルゴリズムと紐付いています。
  - ハッシュアルゴリズムはPSKが確立される際にセットされなければなりません。そして、セッション確立中にハッシュアルゴリズムが明示されなければSHA-256がデフォルトとして用いられます。

# 仕様詳細

### 外部PSKを持った証明書

- ClientHelloやServerHello中に含まれるtls_cert_with_extern_psk拡張についてここでは延べる。
  - この拡張は他のメッセージには含まれていてはならない。
  - ClientHelloで受取っていない場合にはServerHello中にこの拡張が現れてもならない。
  - もしなんらかの実装が上記不正を検知したら「illegal_parameter」アラートを送付しなければらない。
- サーバ側がHelloRetryRequestで応答した場合、クライアントは


### セキュリティ上での考慮
TLS1.3ではPSKが使われた場合にCertificateRequestメッセージを送付することを許容していない。
しかし、この制限はtls_cert_with_extern_psk拡張で取り除かれることになります。

# 参考URL
- https://tools.ietf.org/html/draft-housley-tls-tls13-cert-with-extern-psk-00

# TODO
- ちゃんと読めていない
