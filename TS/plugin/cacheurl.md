# 概要
cacheurlプラグインはcache keyを書き換えるためのプラグインです。trafficserver7未満にデフォルトで包括されています
なお、このプラグインはv6.2.0でdeprecated扱いとなり、v7.0.0から完全に削除されています。代替としてはcachekeyプラグインが利用されるようです。

trafficserverではデフォルトではcache keyは完全なリクエストURL(パラメータも含む)をキャッシュキーとしています。このプラグインを使うことで複数のURLに対して1つのキャッシュを利用することができるようになるといったことが可能です。

# 使い方
このプラグインはグローバルプラグインとして稼働します。
- plugin.configに以下のso読み込み設定を追加します。
```
cacheurl.so
```
- cacheurl.configを作成します。
  - patternはリクエストされてきたURLで正規表現で実現されています。replacementは$1, $2などを含んでいるかもしれません。replacementに置き換えが行われます。
```
<pattern> <replacement>
```

あとはtrafficserverの再起動を行います。
このプラグインはcacheurl.logというログファイルを別で生成します。

# cacheurl.configの例
trafficserver7系で代替となる例を含めて記載しておく

- 例1: ドメイン間でキャッシュ情報を統合する
```
http://s[123].example.com/(.*)  http://s.example.com.TSINTERNAL/$1

// cachekeyプラグインだと上記は次のようにかける
@plugin=cachekey.so @pparam=--capture-prefix=/s[123].example.com:.*/s.example.com.TSINTERNAL/
```

- 例2: idとformatパラメータは削除する
```
http://www.example.com/video\?.*?\&?(id=[0-9a-f]*).*?\&(format=[a-z]*)  http://video-srv.example.com.ATSINTERNAL/$1&$2

// cachekeyプラグインだと上記は次のようにかける
@plugin=cachekey.so @pparam=--include-params=id,format
```

- 例3: 全てのパラメータを除去する
```
http://www.example.com/some/page(?:\?|$)  http://www.example.com/some/page

// cachekeyプラグインだと上記は次のようにかける
@plugin=cachekey.so @pparam=--remove-all-params
```


# SeeAlso
- https://docs.trafficserver.apache.org/en/6.2.x/admin-guide/plugins/cacheurl.en.html
