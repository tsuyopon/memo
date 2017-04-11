# 概要
PHPのコマンドライン処理について

### phpのsytanxチェックを行う
```
$ php -l test.php
No syntax errors detected in test.php
```

### インストール済みモジュールを確認する
```
$ php -m
[PHP Modules]
bz2
calendar
Core
ctype
(snip)
SimpleXML
sockets
SPL
standard
tokenizer
xml
zip
zlib

[Zend Modules]
```

### コマンドラインからphpを実行する
```
$php -r '$a=var_dump(phpinfo()); print_r($a);'
```

### PHPに設定されている設定情報が知りたい
php.iniに記述されるような各種モジュール設定や環境変数、$_SERVERなどの設定情報などが全て表示される。
```
$ php -i
(snip)
Core

PHP Version => 5.4.17

Directive => Local Value => Master Value
allow_url_fopen => On => On
allow_url_include => Off => Off
always_populate_raw_post_data => Off => Off

(上記のCoreの他にも全てのphp.ini関連の設定が表示される)


Environment

Variable => Value
XDG_SESSION_ID => 6
HOSTNAME => localhost.localdomain
TERM => xterm-256color
SHELL => /bin/bash
HISTSIZE => 1000
SSH_CLIENT => 10.0.2.2 49200 22
OLDPWD => /home/tsuyoshi/git/memo
SSH_TTY => /dev/pts/0
USER => tsuyoshi

(snip)


_SERVER["_"] => /usr/bin/php
_SERVER["PHP_SELF"] => 
_SERVER["SCRIPT_NAME"] => 
_SERVER["SCRIPT_FILENAME"] => 
_SERVER["PATH_TRANSLATED"] => 
_SERVER["DOCUMENT_ROOT"] => 
_SERVER["REQUEST_TIME_FLOAT"] => 1481147452.2965
_SERVER["REQUEST_TIME"] => 1481147452
_SERVER["argv"] => Array
(
)

_SERVER["argc"] => 0
```




