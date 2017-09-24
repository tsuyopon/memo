# 概要
TLS周りのtipsなど

### chromeでアドレスバーを押したらすぐに証明書がみれるようにする。

Chrome56からは、UI/UXポリシーによって、HTTPSで接続した際に使用しているSSLサーバ証明書の表示が鍵アイコンから簡単にできなくなってしまいました。

アドレスバーから次の画面にアクセスして、
- chrome://flags/#show-cert-link

次の箇所がデフォルトで無効なので、有効に変更して再起動します。
```
Show certificate link Mac, Windows, Linux, Chrome OS
```

詳細は以下の記事を参考にしてください。

- 参考
  - http://blog.livedoor.jp/k_urushima/
