# mod_rewrite
特定の条件に応じてURL書き換えを行う仕組みです　

# 詳細
### 動的ページを静的ページに見せる
以下の様な方法で静的ページと見せかけることができます。
以下では.cgi&〜で始まっているような場合に利用することが可能です。
このようにすると検索サイトのロボットに引っかかりやすいそうです。
```
RewriteEngine on
RewriteRule ^/cgi-bin/sample/([0-9A-Za-z]+)/([0-9A-Za-z)]+)\.html$ /cgi-bin/sample/sample.cgi?a=$1&b=$2 [L]
```
尚、上記のRewriteEngineやRewriteRuleはDirectoryディレクティブの中では効かないので注意すること.

### GETで付与されたパラメータを自動付与する(query string append[QSA])
```
RewriteRule ^test/(.*)$ /test.php?no=$1 [QSA] 
```
上記の様なrewriteが設定されている場合を想定します。

以下のURLにアクセスすると
```
http://tsuyoshi.com/test/123?s=45&e=678&q=hoge
```

以下の様なURLとしてrewriteされます。(つまり、余分なパラメータもしっかりと付与してくれるわけです)
```
http://tsuyoshi.com/test.php?no=123&s=45&e=678&q=hoge
```

### %2F(スラッシュ)が含まれるものはmod_rewriteのパターンにマッチしない
使っているapacheのバージョンが1.3系の場合には対処不可能です。
バージョンが2.0系以降に存在する以下のディレクティブを有効にする必要があります。
```
AllowEncodedSlashes On
```

### rewrite前に存在するファイルやディレクトリに対してはrewriteを適用させたくない場合
- ファイルの場合には、以下の様に記述します。
```
	 RewriteCond %{REQUEST_FILENAME} !-f
	 !-f は存在するファイル名にはルールを適用しない
```
- ディレクトリの場合には、以下の様に記述します。
```
	 RewriteCond %{REQUEST_FILENAME} !-d
	 !-d は存在するディレクトリ名にはルールを適用しない
```

### rewriteのログを取得する
以下の様な行をconfに設定する
```
RewriteLog logs/rewrite_log
RewriteLogLevel 4
```

# SeeAlso
- URLを書き換えろ！Apache Rewrite 機能の応用
  - http://www.nurs.or.jp/~sug/homep/rewrite/rewrite1.htm
- mod_rewrite モジュール URL 書き換えエンジン
  - http://net-newbie.com/trans/mod_rewrite.html

