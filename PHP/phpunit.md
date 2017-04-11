# 概要
phpunitについてのメモなど

# 詳細
### PHPUnit実行時の1文字シンボルについて
phpunitコマンドを実行した時に表示される1文字シンボルについて

```
.   テストが成功した際に表示されます。 
F   テストメソッドの実行中、アサーションに失敗した際に表示されます。 
E   テストメソッドの実行中、エラーが発生した際に表示されます。 
R   テストが危険だとマークされている場合に表示されます
S   テストが飛ばされた場合に表示されます
I   テストが「不完全」あるいは「未実装」とマークされている場合に表示されます
```

- 参考URL
  - https://phpunit.de/manual/current/ja/textui.html

## テスト実行を効率化したい
次の２つに大別される。
- テストを分割したい
  - phpunit.xmlを書く
- テスト時間が無視できない場合
  - groupを指定する。


### phpunit.xmlを書く場合
phpunit.xmlをカレントディレクトリに配置しておけばphpunitコマンドを引数なしで実行するだけで読み込みます。
次のようなファイルを準備します。directoryに指定したディレクトリを再帰的に走査して、その配下に存在するテストコード*Test.phpを全部見つけてきて、テストしてくれます。
```
<?xml version="1.0" encoding="UTF-8"?>
<phpunit
  colors="true"
  bootstrap="bootstrap.php">
  <testsuite name="Sample">
    <directory>.</directory>
  </testsuite>
</phpunit>
```

phpunit.xmlの記法などについてはphpunitの公式ドキュメントを参考のこと
- https://phpunit.de/manual/6.1/ja/appendixes.configuration.html

### groupを指定する場合
groupを指定する場合にはclass定義の直前に記述するか、function定義の直前に記述するか２つの方法があります。  
次の例のように複数のgroupを指定することもできます。以下はclass定義の直前に記述している例です。
```
/**
 * @group unit
 * @group db
 */
class HogeTest extends PHPUnit_Framework_TestCase
```

たとえば、unitグループのunittestだけを実行したい場合
```
$ phpunit --group unit
```

逆にunitグループのunittestだけを除外したい場合
```
$ phpunit --exclude-group unit
```

### 失敗時にテスト実行を止める
```
$ phpunit --stop-on-failure
```

### パターンにマッチするテストだけを実行する
次の例ではSampleTest.phpからFooという文字列を含むテストだけを実行する
```
$ phpunit --filter="Foo" SampleTest.php

$ phpunit --filter="/あいう/" SampleTest.php   // マルチバイトは/ /で囲む必要あり
```

### phpunit.xmlのパスを指定したい
```
$ phpunit -c phpunit.xml 
```

### コマンドラインオプションが知りたい
ここを見ろ
- https://phpunit.de/manual/current/ja/textui.html

### 存在するassertion一覧が知りたい
ここを見ろ
- https://phpunit.de/manual/6.1/ja/appendixes.assertions.html

### アノテーションが知りたい
ここを見ろ
- https://phpunit.de/manual/6.1/ja/appendixes.annotations.html

# 参考URL
- 公式ドキュメント
  - https://phpunit.de/manual/6.1/ja/index.html
- phpunitコマンドについて
  - https://phpunit.de/manual/current/ja/textui.html
