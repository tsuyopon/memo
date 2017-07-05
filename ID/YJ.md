# 概要
Yahoo! JAPANのIDについて

ヤフーにはYConnectというOAuth2.0とOpenID Connectをサポートした仕組みが存在します。
- https://developer.yahoo.co.jp/
- https://marketing.yahoo.co.jp/service/yidconnect/

認証と認可は混乱しやすいので注意
- OpenIDは認証(Authentication)
  - 第三者サイトなどでヤフーのIDでログインできる仕組みを提供すること
- OAuthは認可(Authorization)
  - 第三者サイトなどでヤフーのリソースなどにアクセスできる仕組みを提供すること

現在では認証と認可を組み合わせたOpenID ConnectというのがIDトレンドらしい

ID連携v2で次の２つの大きな変更がある。
- 標準仕様に準拠(いままではdraftだった)
- Hybrid flowに対応

# OAuth, OpenID, YConnectなどが混合している場合のメモ
- https://www.slideshare.net/kura_lab/standardbased-identity-1

認証・認可の歴史(OpenID, OAuth1.0, OAuth2.0, OpenID Connect)や関係性などについてわかりやすく記載されている。
また、Authorization Codeのinput, outputで詳しい説明がある。

# ヤフーが対応しているフロー
- Authorization Code Flow
  - サーバサイドで認証
- Implicit Flow
  - クライアントサイドで認証
- Hybrid Flow
  - クライアントサイド・サーバサイドの両方で認証

# PHPの実装(Authorization Code Flowを確認する) 
PHPのSDKを使ったAuthorization Code Flowについて説明しています。
- YConnectで簡単ID連携！その1 ～ログインボタンの設置～
  - https://techblog.yahoo.co.jp/web/auth/yconnect1/
- YConnectで簡単ID連携！その2 ～登録情報の取得～
  - https://techblog.yahoo.co.jp/web/auth/yconnect2/

その1では
- appidの取得
- ログインボタンの設置してstart.phpを起動
- start.phpの実装
  - コールバックやnonceなどを指定してauthorizationエントリポイントにアクセスする仕組み
- その後、Y!J側のサーバが呼ばれて認証が行われるとコールバック先にリクエストが戻る
- コールバックの戻り先では認可コードを取得して、tokenエントリポイントにアクセス、accessTokenとrefreshTokenを取得する

その2では
- その1で取得したaccessTokenを指定してユーザーinfo APIというユーザー情報属性を取得するAPIにアクセスする。
  - もしエラーが帰ってきたら有効期限切れかどうかをチェックしてtokenを再発行する。
  - https://developer.yahoo.co.jp/yconnect/v1/userinfo.html

以上により、appidの発行、accessToken, refreshTokenの取得をし、accessTokenを使ってuserinfo APIから取得するまでを確認した。

# 参考資料
- https://www.slideshare.net/kura_lab/20161317-cloud-serverfesta2016yahooidfederation
- https://www.slideshare.net/kura_lab/yahoo-japanopenid-certified-mark
