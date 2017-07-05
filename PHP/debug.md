# 概要
PHPのデバッグ方法について
いくつか方法などが存在するようなのでまとめておくことにする。

# 詳細

### もっとも一般的な手法
var_dumpをpreエレメントで囲む手法などは結構重宝するとのことです。
```
<pre><?php var_dump($hoge) ?></pre>
```

### display_errorsとerror_reportingについて
display_errorsをOnにすると画面上にエラーを表示してくれるようになります。デバッグ用途の設定です。
```
<?php
ini_set('display_errors', 'On');
error_reporting(E_ALL);
```

error_reportingについては出力する PHP エラーの種類を設定することができます。
以下はドキュメントに記載のあった設定例
```
// 全てのエラー出力をオフにする
error_reporting(0);

// 単純な実行時エラーを表示する
error_reporting(E_ERROR | E_WARNING | E_PARSE);

// E_NOTICE を表示させるのもおすすめ（初期化されていない
// 変数、変数名のスペルミスなど…）
error_reporting(E_ERROR | E_WARNING | E_PARSE | E_NOTICE);

// E_NOTICE 以外の全てのエラーを表示する
error_reporting(E_ALL & ~E_NOTICE);

// 全ての PHP エラーを表示する (Changelog を参照ください)
error_reporting(E_ALL);

// 全ての PHP エラーを表示する
error_reporting(-1);

// error_reporting(E_ALL); と同じ
ini_set('error_reporting', E_ALL);
```

### PHP関連の設定でエラーに関するもの
php設定でerrorに関するものは結構多く存在します。以下を参考にしてください。
- http://phpspot.net/php/man/php/errorfunc.configuration.html#ini.xmlrpc-errors

### xdebug
** TODO **


### debug_backtrace関数を利用する

```
<?php
// ファイル名: /tmp/a.php

function a_test($str)
{
    echo "\nHi: $str";
    var_dump(debug_backtrace());
}

a_test('friend');
```

```
<?php
// ファイル名: /tmp/b.php
include_once '/tmp/a.php';
```

上記コードを実行するとdebug_backtrace()により次のような出力を得ることができる。
```
Hi: friend
array(2) {
[0]=>
array(4) {
    ["file"] => string(10) "/tmp/a.php"
    ["line"] => int(10)
    ["function"] => string(6) "a_test"
    ["args"]=>
    array(1) {
      [0] => &string(6) "friend"
    }
}
[1]=>
array(4) {
    ["file"] => string(10) "/tmp/b.php"
    ["line"] => int(2)
    ["args"] =>
    array(1) {
      [0] => string(10) "/tmp/a.php"
    }
    ["function"] => string(12) "include_once"
  }
}
```

- http://au2.php.net/manual/ja/function.debug-backtrace.php

### get_included_files関数

include,requireされた全てのPHPファイル名を返します。
 どういう順番でファイルが読み込まれていったのか、ちゃんとライブラリがロードされているかといったことを確認できます。


### phpdbg
ブレークポイントというその場所で一旦処理を止めて状態を確認する方法がとれたり、ステップ実行という１行ずつ動作を確認しながら処理を進める方法などが利用できます。

ただし、phpgdbはphpコマンドラインからの実行で利用できる仕組みのようでありSAPIレイヤーで実装されているので、mod_phpやfpmといった他のSAPI環境での動作デバッガを行う場合にはxdebugなどの拡張が必要となるようです。  
つまり、Apacheと組み合わせてデバッグすることができなさそうです。


**TODO** あとで使ってみてまとめる
- http://www.1x1.jp/blog/2013/12/phpdbg.html
- http://phpdbg.com/


### PHPエクステンションにおけるデバッグ手法
PHP Extensionを開発していてコアを吐いてしまった場合に、「何のファイル」の「何の関数」の「何行目」で落ちたかといった情報がわかります。

- 参考
  - https://techblog.yahoo.co.jp/tips/php/

```
// 落ちた箇所の特定
(gdb) print (char *)(executor_globals.function_state_ptr->function)->common.function_name
$1 = 0x21c2314a "down_method"

// 落ちたファイル名の特定
(gdb) print (char *)executor_globals.active_op_array->filename
$3 = 0x9c7ccc "/home/down.php"

// 落ちた行の特定
print executor_globals.current_execute_data.opline->lineno
$5 = 2
```




