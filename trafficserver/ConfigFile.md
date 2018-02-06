# 概要
設定ファイルについて

# 詳細

### trafficserver各種設定ファイルの説明へのリンク一覧
以下のページに各種設定ファイルの説明とその詳細ページへのリンクが載せられている。
- https://docs.trafficserver.apache.org/en/latest/admin-guide/files/index.en.html

### records.configファイルを比較したい
次の箇所にツールが存在する
- https://github.com/apache/trafficserver/blob/7.1.x/contrib/python/compare_records_config.py

次のようにして使うことができる。
```
$ python compare_records_config.py <比較したいrecords.config1> <比較したいrecords.config2>
```

### 設定ファイルへのドキュメント
次のページに各種設定ファイルの概要や説明詳細へのリンクがあります
- https://docs.trafficserver.apache.org/ja/7.0.x/admin-guide/files/index.en.html

### 設定ファイルが正しいかどうかを検証したい
```
$ traffic_server -Cverify_config -D<config_dir>
```

- 参考
  - https://docs.trafficserver.apache.org/en/latest/appendices/faq.en.html#troubleshooting-tips

### records.configの値を取得したい
```
$ traffic_ctl config get VARIABLE
```

records.configに設定できる値は沢山存在するので以下のリンクを参照のこと
- https://docs.trafficserver.apache.org/en/latest/admin-guide/files/records.config.en.html

### 設定を変更する
次のコマンドもしくは手動でrecords.configを修正したら
```
$ traffic_ctl config set VARIABLE VALUE
```

次のコマンドで読み込みさせることが可能です
```
$ traffic_ctl config reload
```

- 参考
  - https://docs.trafficserver.apache.org/ja/latest/admin-guide/configuring-traffic-server.en.html
