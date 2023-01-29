# 概要
簡単な使い方

# psqlクライアントのインストール (Mac)
下記をbrewから入れるだけでpsqlクライアントが入ります。ただし、サーバは入りません。
```
$ brew install libpq
```

# 接続方法
Uにはロール名、dにはデータベース名を指定します。
```
$ psql -h localhost -p 5432 -U postgres -d testdb
```

localhostで、デフォルト5432の場合には省略できます。
```
psql -U postgres -d testdb
```

# 接続終了時
```
\q
```
