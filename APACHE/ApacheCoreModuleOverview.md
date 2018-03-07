# 概要
Apacheのcore処理について説明する

# 詳細
###  http_coreの処理
coreにはapacheをwebサーバとして動作させるための最低限の仕組みが含まれています。
- サーバとモジュールの初期化処理(http_main)
- 設定ファイル読み込み、コマンドの実行(http_config)
- TCPコネクションの確立(http_main)
- HTTPリクエストの受付と、レスポンスの返却(http_protocol)
- リクエスト処理フロー制御(モジュール呼び出し) (http_request)
- メモリ等リソースの確保および管理(all)
- 子プロセスの生成と管理(http_main)

### moduleの処理
- モジュール組み込み方法(2種類)
  - 本体にmoduleを組み込む場合(静的)
    - ロード負荷を抑えることができ、パフォーマンスをあげられます。
  - DSOを利用してmoduleを組み込む場合(動的)
    - 設定ファイルで有効・無効を簡単に切り替えられます。

以下、moduleが行う処理シーケンスです
```
ロギング
リクエスト受信
URI変換
ヘッダ解析
アクセス制御
認証
アクセス許可
MIMEタイプチェック
レスポンス送信
```

### apache v2.0.40のモジュール機能についてまとめる
```
<モジュール> 　　<機能> 　　　　　　　　　　　　　　　　　　　    　<デフォルト>
mod_access　　　 ホストに基づいたアクセス制御                         Yes 
mod_actions　　　ファイル種別／メソッドに基づいたスクリプトの実行     Yes 
mod_alias　　　　Aliases and redirects.                               Yes 
mod_asis .asis　 ファイルハンドラー                                   Yes 
mod_auth　　　　 テキストファイルを用いたユーザ認証                   Yes 
mod_auth_anon　　FTPスタイルの匿名（Anonymous）ユーザー認証           No 
mod_auth_db　　　バークレイDBファイルを用いたユーザー認証             No 
mod_auth_dbm　　 DBMファイルを用いたユーザー認証                      No 
mod_autoindex　　自動ディレクトリリスト表示                           Yes 
mod_cern_meta　　HTTPハンドラメタファイルのサポート                   No 
mod_cgi　　　　　CGIスクリプトの実行                                  Yes 
mod_digest　　　 MD5ユーザー認証                                      No 
mod_dir　　　　　基本的なディレクトリハンドリング                     Yes 
mod_env　　　　　CGIスクリプトへの環境変数の継承                      Yes 
mod_example　　　Apache APIの実証                                     No 
mod_expires　　　割り当ての終了：リソースへのヘッダ                   No 
mod_headers　　　リソースに任意のHTTPヘッダを加える                   No 
mod_imap　　　　 イメージマップファイルのハンドラ                     Yes 
mod_include　　　サーバで解析するドキュメント                         Yes 
mod_info　　　　 サーバの設定情報                                     No 
mod_log_agent　　ユーザーエージェントのログ蓄積                       No 
mod_log_config　 ユーザー定義ログ                                     Yes 
mod_log_referer　ドキュメントリファレンスのログ蓄積                   No 
mod_mime　　　　 ファイル拡張子を使ったドキュメントタイプの決定       Yes 
mod_mime-magic　 magic numbers を使ったドキュメントタイプの決定       No 
mod_negotiation　コンテンツのネゴシエーション                         Yes 
mod_proxy　　　　キャッシングプロキシ機能                             No 
mod_rewrite　　　通常表記を使った強力なURI-to-filenameマッピング      No 
mod_setenvif　 　クライアント情報を基にした環境変数の設定             Yes 
mod_spelling     URLでのminor typosの自動訂正                         No 
mod_status       サーバステータスを表示                               Yes 
mod_unique-id    あらゆるリクエストのためのユニークなリクエスト識別の生成  No 
mod_userdir      ユーザーのホーム・ディレクトリ                       Yes 
mod_usertrack    cookieを用いたユーザー追跡（mod_cookies.cと置き換え）No
```

# SeeAlso
- apache v2.0 モジュール一覧
  - http://httpd.apache.org/docs/2.0/ja/mod/
