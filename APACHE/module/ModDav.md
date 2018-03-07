### WebDAVでSSLとBasic認証を使用する
Basic認証の基本は上記を見て欲しい。
すでに/etc/httpdディレクトリに.htpasswdファイルが作成されているものとします。
httpd.confに以下の設定を追加すればよい。
```
	 Alias /webdav/ "/var/www/html/webdav/"
	 
	   DAV on
	   SSLRequireSSL
	   AuthType        Basic
	   AuthName        "My Server's webDAV"
	   AuthUserFile    "/etc/httpd/.htpasswd"
	   Require valid-user
```

上記の設定を加えたらApacheを再起動すればよい。
windowsではネットワークプレイスの追加でDAVサーバーを加えることができる。

もしもできない場合は以下のApacheディレクティブがあることを確認します。
```
	 Addmodule mod_dav.c
	 Addmodule mod_dav_fs.c
	 DAVLockDB /var/lib/dav/lockdb
```
