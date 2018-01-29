# 概要
このプラグインはキャッシュオブジェクトの再検証をすべきかどうか、いつすべきかといったことをリマップされたURLにマッチした正規表現に対して実施します。

# 使い方
plugin.configに以下の設定を追加します。
```
regex_revalidate.so -c <path to rules> -l <path to log>
```
- c: 設定ファイルを指定します
- l: ログファイルを指定します。
- d: 定期的なチェックを無効にします。必要があれば付加してください。引数指定は不要です。

デフォルトでは、60秒ごとに定期的に設定ファイルに変化があったかどうかをチェックします。


# サンプル
オリジンサーバがorigin.tldで、パスが/images/foo.jpgの場合に1447483647で指定されたunixtimeまでにキャッシュオブジェクトの再検証を行う。
```
http://origin\.tld/images/foo\.jpg 1447483647
```

- PCREスタイルの正規表現をサポートしています。
- リマップされたURLにマッチした正規表現に対して使われます。(クライアントサイドのURLではなく、オリジンURLとなることに注意すること)。プロトコルスキーマやオリジンサーバドメインを含みます。
- リマップされた後(Post-remapping)の時にだけマッチします。このプラグインは TS_HTTP_CACHE_LOOKUP_COMPLETE_HOOKフックを利用しています。


# SeeAlso
- https://docs.trafficserver.apache.org/ja/latest/admin-guide/plugins/regex_revalidate.en.html
