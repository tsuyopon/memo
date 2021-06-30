# 概要
httpdビルド時のオプションなどについてのメモ
デフォルトで指定する際に理解しておいた方が良いオプションにういて

# 詳細

## httpdパッケージ

### with-included-apr 
これは覚えておくべきオプションです。
httpdはapr, apr-utilsと合わせてビルドしますが、httpdレポジトリ配下のsrclibs/直下にapr, apr-utilsという名称で展開したソースコード配置しておけば、
このオプションを指定することによって一緒にビルドしてくれる便利なオプションです。
なお、with-included-apr-utilsというオプションは確認した限りでは無いようです。

### with-mpm
以下のようにmpmモードを指定することできます。(以下は一例です)
- prefork
- event

指定できる値は以下の資料を参考にしてください。
- https://httpd.apache.org/docs/2.4/ja/mod/


cf. https://httpd.apache.org/docs/2.4/ja/mpm.html


### enable-mods-shared

共有モジュールをどれだけコンパイルするかのオプションです。
以下の4種類を指定できます。
- reallyall
- all
- most (default)
- few 


cf. http://tech-wiki.pomme-verte.net/?p=550
