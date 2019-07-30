# 概要
リクエストやレスポンスのヘッダの修正、追加、削除などを行うことができるモジュールです。

# 詳細

### HTTPキャッシュ設定に関するヘッダをレスポンス時に追加する
```
<Directory "/path/to">
  Header always set Cache-Control "public"
  Header append Cache-Control "max-age=600"
</Directory>
```

# 参考URL
- Apache Module mod_headers
  - https://httpd.apache.org/docs/2.4/en/mod/mod_headers.html
