# 概要
trafficserver7未満はcacheurlプラグインでキャッシュキー情報を制御していましたが、trafficserver7系からはcacheurlプラグインが削除され、cachekeyプラグインがその代替となりました。


# 使い方
キャッシュを構成する際の条件によって指定するパラメータが変わってきます。

- 全てのパラメータを無視する
```
@plugin=cachekey.so @pparam=--remove-all-params=true
```
- 特定のパラメータを無視する。以下はa, bを除外
```
@plugin=cachekey.so @pparam=--exclude-params=a,b

// 正規表現を使う場合
@plugin=cachekey.so @pparam=--exclude-match-params=(a|b)
```
- 特定のパラメータのみを含む
```
@plugin=cachekey.so @pparam=--include-params=a,c

// 正規表現を使う場合
@plugin=cachekey.so @pparam=--include-match-params=(a|c)
```
- パラメータをソートする
```
@plugin=cachekey.so @pparam=--sort-params=true
```

# 各種オプション

# SeeAlso
- https://docs.trafficserver.apache.org/en/latest/admin-guide/plugins/cachekey.en.html
