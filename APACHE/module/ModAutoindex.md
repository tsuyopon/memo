# 概要
インデックス化されたページを表示させたい場合にこのモジュールを利用することができます。

# 詳細
### 使い方
```
<Directory "/path/to">
  Options FollowSymLinks Indexes
  IndexOptions FancyIndexing    # add
  # 必要に応じてACLも追加すること
</Directory>
```

# 参考URL
- Apache Module mod_autoindex
  - https://httpd.apache.org/docs/2.4/en/mod/mod_autoindex.html
