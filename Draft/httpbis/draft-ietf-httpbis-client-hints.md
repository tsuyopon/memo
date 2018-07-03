# 概要
HTTP Client Hintsについて
- https://tools.ietf.org/html/draft-ietf-httpbis-client-hints-05

# 解決する課題
- クライアント側デバイスでは画像ごとに最適なデバイスピクセル比に対応したものを応答して欲しいが、HTTP上でそれを知る仕様が存在しない

# 解決方法
- デバイスピクセル比等クライアント側のデバイス情報を HTTP のリクエストヘッダに記載してサーバに通知してあげようとの仕組みです

- 1. クライアントはHTTPリクエストヘッダ中に「CH-DPR」ヘッダにデバイスピクセル値を付与するか、「CH-RW」ヘッダにデバイスリソース幅値を付与する。
- 2. サーバはCH-DPRヘッダを検証の上で、クライアントのデバイスピクセル値に最適なリソースを送信する。例えば、CH-DPRヘッダが付与された場合、レスポンスヘッダとして「Vary: CH-DPR」、「DPR:2.0」などを付与します。

# 詳細



# 参考URL
- ぼちぼち日記: Chrome Beta for Android で Client Hints を試すAdd Star
  - http://d.hatena.ne.jp/jovi0608/20131217/1387271748
