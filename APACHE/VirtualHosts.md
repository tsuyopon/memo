# 概要
VirtualHostについて

# 詳細

### 特定のドメインとそれ以外を分けたい場合
たとえば、your.service.comでアクセスしてきた時とそれ以外とのアクセス先を分けたい場合を分ける場合次のようにします。
最初に書かれた方はServerNameがdummy.comとして記述されていますが、実はyour.service.com以外の直接IPアドレスや意図しない逆引きからアクセスされた場合にもdummy.comの設定が効いてきます。
```
NameVirtualHost *:80
<VirtualHost *:80>
    ServerName dummy.com
    DocumentRoot /var/www/dummy.com
    ...
</VirtualHost>

<VirtualHost *:80>
    ServerName your.service.com
    DocumentRoot /var/www/your.service.com
    ...
</VirtualHost>
```

- 参考URL
  - http://dqn.sakusakutto.jp/2011/07/apachevirtualhost.html


### ポートが異なる場合のVirtualHostの分割方法について
_default_という記述を利用する事ができます。例えば、公式ドキュメントに従うと次のように記述することができます。
```
<VirtualHost _default_:80>
    DocumentRoot "/www/default80"
    # ...
</VirtualHost>

<VirtualHost _default_:*>
    DocumentRoot "/www/default"
    # ...
</VirtualHost>
```

# SeeAlso
- https://httpd.apache.org/docs/2.4/en/vhosts/examples.html
