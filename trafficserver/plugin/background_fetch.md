# 概要
background fetchプラグインはtrafficserverに包括されているプラグインです
オリジンからのレスポンスを調査して、以下の状態に基いてクライアントリクエストのバックグラウンドフェッチを行うかどうかを決定します。
- このリクエストがGETであるかどうか(これしか現在サポートしていない)
- レスポンスが206かどうか
- クライアントのリクエスト及びサーバからのレスポンスがキャッシュ可能な状態を示しているかどうか
  - これにはTSHttpTxnIsCacheable()を使ってtrafficserverの現在の設定状態を確認しています。

バックグラウンドのための候補であると判定されたら、trafficserverは再度オリジンサーバにリクエストを投げます。この際にはRangeヘッダを除去してアクセスが行われます。

# 使い方
リマッププラグインとグローバルプラグインの２つのいずれかとして利用する事が可能です。
- リマッププラグインとしては以下をリマップ各行に追加を行います。
```
@plugin=background_fetch.so @pparam=<config-file>
```
- グローバルプラグインとしてはplugin.configに以下を追加します。
```
background_fetch.so --config <config-file>
```

上記で表すconfig-fileとしては次のような指定をすることが可能です。
```
include User-Agent ABCDEF
exclude User-Agent *
exclude Content-Type text
exclude X-Foo-Bar text
exclude Content-Length <1000
```

# 利用されるフック
- リマッププラグインの場合
  - TSRemapDoRemap中でRangeヘッダが見つかった場合には以下の２つを追加する
    - TS_HTTP_READ_RESPONSE_HDR_HOOK
	  - 上記フックでサーバレスポンスが206であれば、TS_HTTP_SEND_RESPONSE_HDR_HOOKフックも追加
    - TS_HTTP_TXN_CLOSE_HOOK
	  - 後処理
- グローバルプラグインの場合
  - TS_HTTP_READ_RESPONSE_HDR_HOOK
    - 上記フックでサーバレスポンスが206であれば、TS_HTTP_SEND_RESPONSE_HDR_HOOKフックも追加

# SeeAlso
- https://docs.trafficserver.apache.org/ja/latest/admin-guide/plugins/background_fetch.en.html
