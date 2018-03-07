### 全てのユーザーでwwwを利用できるようにしたい
たとえば$HOMEの直下のpublic_html以下のファイルにアクセスする場合、httpd.conf
に以下を指定すればよい。
```
UserDir public_html
```
これにはmod_userdirモジュールが必要である。

### ユーザーのディレクトリでの認証を行なう場合
httpd.confから以下が記述されている行を探して以下のようにコメントアウトを外す。
```
<Directory /home/*/public_html>
  AllowOverride FileInfo AuthConfig Limit
  Options MultiViews Indexes SymLinksIfOwnerMatch IncludeNoExec
  <Limit GET POST OPTIONS PROPFIND>
     Order allow,deny
     Allow from all
  </Limit>
  <LimitExcept GET POST OPTIONS PROPFIND>
     Order deny,allow
     Deny from all
  </LimitExcept>
</Directory>
```

これはプログラムの実行を許可せずに、読みだし系のメソッドのみ許可する制限のある設定となります。
(注)ディレクトリでの認証にはhttpd.confでUserDir public_html」が必要です。
「UserDir none」とするとユーザーディレクトリでの認証を拒否します。
