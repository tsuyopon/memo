# 概要
mod_expiresモジュールを利用すると特定のファイルにアクセスした際のレスポンスとしてExpiresヘッダを付与してくれます。

# 詳細

### 簡単な使い方
.htaccessやhttpd.confどちらでも良いので次のような設定を追加します。
```
<IfModule expires_module>
   ExpiresActive On
   ExpiresDefault "access plus 2 weeks"
</IfModule>
```

上記のExpiresDefaultで指定している期間の指定は次のように何種類かの書き方があります。
- A31536000
- access plus 30 days
- access plus 1 month 2 days 3 hours
- M86400
- modification plus 5 hours 3 minutes

### CSSだけは長期間にしたい場合
```
ExpiresActive On
ExpiresDefault "access plus 14 days"
ExpiresByType text/css "access plus 1 month 2 days 3 hours"
```

# 参考URL
- http://httpd.apache.org/docs/current/mod/mod_expires.html
