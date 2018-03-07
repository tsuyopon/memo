### 仮想ディレクトリのマッピング
/home/www/imagesディレクトリを/images/にマッピングしたければhttpd.confに
```
Alias /images/ "home/www/images/"
```
を指定すればよい。(mod_aliasモジュールが必要)

### CGIプログラムを配置するディレクトリのマッピング
/home/www/cgi-binディレクトリを/cgi-bin/にマッピングしたければhttpd.confに
```
ScriptAlias /cgi-bin/ "/home/www/cgi-bin"
```
を追加指定すればよい。
これはCGIだけが利用するものであって、PHPなどはApache本体が実行するものでは
ない。あくまでも、拡張モジュールなどを必要としないCGIプログラムだけに使用す
ることを忘れないでほしい。

### 全てのユーザーでのCGIプログラムの実行
これは仮想的なディレクトリの設定位置(<IfModule mod_alias.c>〜<IfModule>の間)
に以下を記述するだけでよい。
```
ScriptAliasMatch /~(..*)/cgi-bin/(.*) /home/$1/public_html/cgi-bin/$2
```
