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

### どのアドレスベースのバーチャルホストにもマップできないリクエストを処理したい

ServerNameを省略する次のような記述方法も存在します
```
ServerName  127.0.0.1
<VirtualHost 192.168.1.9>
    ServerName part1.itbdns.com
    DocumentRoot /var/www/html_1
</VirtualHost>

<VirtualHost 192.168.1.10>
    ServerName part2.itbdns.com
    DocumentRoot /var/www/html_2
</VirtualHost>

<VirtualHost _default_>
    DocumentRoot /var/www/html_3
</VirtualHost>
```

_default_に対してはバーチャルホストとして設定されていない「アドレス：ポート」宛の全てのリクエストを受け付ける
例えば、443ポートに対しての全てのマッピングできなかったものを処理したい場合には次のようにします
```
<VirtualHost _default_:443>
```

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

### 設定したServerNameドメイン以外のドメインでもアクセスしたい
VirtualHostで設定したドメインでアクセスしないと、VirtualHost内部で設定を行った内容が反映されないことがあります。
そのような場合には、ServerAliasを利用します。
```
<VirtualHost 192.168.1.200>
   ServerName  production.co.jp
   ServerAlias test.co.jp
   DocumentRoot /var/www/html_2
</VirtualHost>
```

### IPアドレスが1つのWebサーバで、1台のシステム上で複数のドメインをサポートしたい
次のサンプルを例に説明します。
```
ServerName  127.0.0.1
NameVirtualHost *
<VirtualHost *>
    ServerName 192.168.1.9
    DocumentRoot /var/www/html
</VirtualHost> 

<VirtualHost *>
    ServerName test.itbdns.com
    DocumentRoot /var/www/html/secret-digest/it
</VirtualHost>
```

上記は次のような意味を持ちます。
- 192.168.1.9でアクセスが来た場合には/var/www/htmlをドキュメントルートとする。
- test.itbdn.comでアクセスが来た場合には/var/www/html/secret-digest/itをドキュメントルートとする。
- VirtualHost後の*は正規表現ではないということを覚えておいてください。

### 1台のシステムに複数のIPアドレスが割り当てられていて、各IPアドレスでWebサイトをサポートしたい場合
次のサンプルを例に説明します。
```
ServerName  127.0.0.1
<VirtualHost 192.168.1.9>
    ServerName part1.itbdns.com
    DocumentRoot /var/www/html_1
</VirtualHost>

<VirtualHost 192.168.1.10>
    ServerName part2.itbdns.com
    DocumentRoot /var/www/html_2
</VirtualHost>
```

上記は、次のことを意味します。
- 192.168.1.9のIPアドレスに対してアクセスが来て、part1.itbdns.comというアクセスで来ているのであれば/var/www/html_1をドキュメントルートとする設定である。
- 192.168.1.10のIPアドレスに対してアクセスが来て、part2.itbdns.comというアクセスで来ているのであれば/var/www/html_2をドキュメントルートとする設定である。

# SeeAlso
- https://httpd.apache.org/docs/2.4/en/vhosts/examples.html
