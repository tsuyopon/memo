# mod_authについて


# 詳細
### Basic認証を行うpart1。(暗号化を行わない認証)
認証をかけるディレクトリを/var/www/html/secretとする。
```
#mkdir -p /var/www/html/secret
```

次にパスワードのデータベースを作成する。これにはhtpasswdコマンドを使用する。
今回、認証をかけるパスワードデータベースを/etc/httpd/.htpasswdとする。
このパスワードデータベースを新規作成する場合には
```
#htpasswd -c /etc/httpd/.htpasswd tsuyoshi
New password:
Re-type new password:
Adding password for user secret
```
また、追加作成をする場合には-cオプションを付加しない。
```
htpasswd -c /etc/httpd/.htpasswd yuuta
 ※.htpasswdは644である必要がある。
```

次に、以下の様にしてhttpd.confに以下のディレクティブを追加する。
```
AuthType Basic
AuthName "Enter your password underline!!"
AuthUserFile /etc/httpd/.htpasswd
AuthGroupFile /dev/null
Require valid-user   (<=ここにユーザー指定するにはRequire user yuutaの様に書く)
```

設定ファイルに追加した後はApacheを再起動してあげればよい。

### Basic認証を行うpart2。(暗号化を行わない認証)
httpd.confにあるディレクティブがあれば、認証を行なうディレクトリに.htaccessファイルを置くだけで済む方法を紹介する。
以下のディレクティブがhttpd.confに書かれている事を確認する。
```
AccessFileName .htaccess 
 
Order allow,deny
Deny from all
```

上記の他にも勿論、アクセスコントロールをしたいディレクトリの〜が必要である。
次にBasic認証を行ないたいディレクトリに置く.htaccessファイルをに記載の内容を以下に示します。
下記の設定が記されたファイルは、/home/tsuyoshi/public_htmlに置くと仮定します。
```
AuthType Basic
AuthName "Password Verify"
AuthUserFile /home/tsuyoshi/public_html/.htpasswd
require valid-user
```

あとは/home/tsuyoshi/public_htmlに.htpasswdを作っておく必要がある[par1参照]
また、httpd.confは変更したらhttpdを再起動するが.htaccessは再起動する必要がない。

### Digest認証を行う
認証をかけるディレクトリを/var/www/html/secret-digestとする。
```
#mkdir -p /var/www/html/secret-digest
```
次にパスワードのデータベースを作成する。これにはhtdigestコマンドを使用する。
認証をかけるパスワードのデータベースを/etc/httpd/.htdigestとする。

新規作成の場合には
```
#htdigest -c /etc/httpd/.htdigest 'server.phys.test.ac.jp' tsuyoshi
Adding password for secret in realm Secret Zone.
New password:
Re-type new password:
```
上記でBasic認証とは違いserver.phys.test.ac.jpを指定したが、これはhttpd.confでのAuthNameで指定した文字と同じものでなければならない。

追加作成の場合には次のように-cオプションを付加しない。
```
#htdigest /etc/httpd/.htdigest 'server.phys.aoyama.ac.jp' yuuta
```

次にhttpd.confに以下のディレクティブを追加する。
```
AuthType Digest
AuthName "server.phys.test.ac.jp"
AuthDigestDomain /secret-digest/
AuthDigestFile /etc/httpd/.htdigest
Require valid-user
```

あとはhttpdを再起動してあげればよい。
