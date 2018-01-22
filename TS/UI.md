# 概要
trafficserverで持っているUI概要について

# 詳細

### ATSで予め用意されている設定UIを利用する

records.configに予め次の設定を行っておく必要があります。
```
proxy.config.http_ui_enabled
```
- https://docs.trafficserver.apache.org/en/latest/admin-guide/files/records.config.en.html?highlight=proxy%20config%20http_ui_enabled#proxy-config-http-ui-enabled

この設定は次の4つの値を持ちます。
- 0: すべてのUIエントリポイントは無効
- 1: cacheエントリポイントのみ有効
- 2: cacheエントリポイント以外のstasのみ有効
- 3: すべてのUIエントリポイントを有効

v8.0では次の5つが存在する(v5系ではもっと多かったが削減された)
- cache
- cache-internal
- hostdb
- http
- net

なおhttpエントリポイントを使う場合には、デフォルトで無効となっている次の設定を有効にしないと真っさらな画面しか表示しません。
```
proxy.config.http.enable_http_info
``

例えば、records.configには次のように記述することでUIを表示できる。注意するのは「_ats_stat/cache」などとして最後にスラッシュを付与しないと画面からのリンク遷移ができなくなるので注意すること
```
map /_ats_stat/cache-internal/ http://{cache-internal}
map /_ats_stat/cache/ http://{cache}
map /_ats_stat/hostdb/ http://{hostdb}
map /_ats_stat/http/ http://{http}
map /_ats_stat/net/ http://{net}
map / http://127.0.0.1:8080/
````

あとはブラウザから次のようにアクセスすれば良い
```
http://<hostname>/_ats_stat/cache/
```

各種UIについては公式ドキュメントにも説明があるので参照すると良い
- https://docs.trafficserver.apache.org/en/latest/admin-guide/storage/index.en.html#using-the-cache-inspector-utility
