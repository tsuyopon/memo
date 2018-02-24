# 概要
YAML(ヤムル)とは、「YAML Aint Markup Language」(ヤムルはマークアップ言語ではない)という意味です。 構造化データやオブジェクトを文字列にシリアライズ(直列化)するためのデータ形式の一種です。
- YAMLの特徴
  - テキストの為、可読です
  - 軽量マークアップ言語です
  - インデントを使い階層構造を表現できます(タブは使えず、スペースのみ使用可能。スペース2個単位でインデントすることが多い。)
  - 参照機能も用意されています。
- 表記可能な方法
  - リスト
  - ハッシュ
  - ハッシュのリスト
  - リストのハッシュ
尚、yamlでは参照利用に関して注意すべき点があります。 yamlファイルから参照定義を1度読み込んでしまったら、そこからyamlファイルに戻しても定義は復元できませんので注意してください。

これから、yaml記述に関する仕様についてまとめていきます。 抑えておくべきは、yamlでは以下の3つの概念によりデータ形式を記述します。
- スカラー（文字列、数値、真偽値、日付等)
- 配列
- ハッシュ

# 詳細
## 基礎知識

### スカラー(基本)
```
---
# 改行がスペースに変換される
foo:
  text text text text
  text text text text
# 改行は保存される
bar: |
  text text text text
  text text text text
# 改行と空行が保存される
baz: >
  text text text text
  text text text text
  text text text text
# エスケープ・シーケンスが解釈される/Perlのqq{}みたいなもの(？)
hoge: "Hello, world\n"
# エスケープ・シーケンスが解釈されない/Perlのq{}みたいなもの(？)
huge: 'AAA BBB CCC'
```
- 引用元
  - http://blog.nyarla.net/2006/12/18/1

### スカラー(中級: 複数行の文字列の取り扱い)
```
## 各行の改行を保存する
text1: |
  aaa
  bbb
  ccc

## 各行の改行と、最終行に続く改行を保存する
text2: |+
  aaa
  bbb
  ccc


## 各行の改行は保存するが、最終行の改行は取り除く
text3: |-
  aaa
  bbb
  ccc


## 改行を半角スペースに置き換える、ただし最終行の改行は保存される
text4: >
  aaa
  bbb
  ccc


## 改行を半角スペースに置き換え、最終行に続く改行を保存する
text5: >+
  aaa
  bbb
  ccc


## 改行を半角スペースに置き換え、最終行の改行を取り除く
text6: >-
  aaa
  bbb
  ccc
```

上記の実行結果は以下の様になります。
```
{"text1"=>"aaa\nbbb\nccc\n",
 "text2"=>"aaa\nbbb\nccc\n\n\n",
 "text3"=>"aaa\nbbb\nccc",
 "text4"=>"aaa bbb ccc\n",
 "text5"=>"aaa bbb ccc\n\n\n",
 "text6"=>"aaa bbb ccc"}
```

### データ型の種類
yamlでは以下のデータ型を自動的に判別することができます。
```
整数
浮動小数点
真偽値 (true, yes, false, no)
Null値 (null, ~)
日付 (yyyy-mm-dd)
タイムスタンプ (yyyy-mm-dd hh:mm:ss [+-]hh:mm)
```

### データ型の明示的指定 †
「!データ型」により明示的にどのデータ型であるかを指定することができます。
```
- !str 123            # 文字列であることを明示的に指定しています。
```

- (参考URL)指定できるデータ型について
  - http://yaml.org/type/index.html

### インデント幅指定について
```
- |2
     foo
     bar
     baz

- |0
     foo
     bar
     baz

- >2
     foo
     bar
     baz

- >0
     foo
     bar
     baz
```
上記に関する実行結果は以下の様になります。
```
["   foo\n   bar\n   baz\n",
 "foo\nbar\nbaz\n",
 "   foo\n   bar\n   baz\n",
 "foo bar baz\n"]
```

### 配列
以下の2種類の方法で定義することができます。 配列であることを表現するには「- 」(ハイフン+スペース)で表現できます。
```
array: 
  - aaa
  - bbb
  - ccc
```
または
```
array: [ aaa, bbb, ccc ]
```

### ハッシュ(key:value)
「: 」コロンとスペースの結合がkeyとvalueの結合を表しています。 つまり、以下の例では、「hash: 」とスペースが含まれていることに注意してください。
```
hash: 
  aaa: aaavalue
  bbb: bbbvalue
```
または
```
hash: { aaa: aaavalue, bbb: bbbvalue }
```

### コメント
コメントはシャープ(#)で表します
```
# シャープが現れた時点から行末までがコメントとして扱われます。
```

### 参照
&で参照定義を、*にて参照を行っています。
```
hoge: &ref_hoge hogeo      # 参照定義
hage: *ref_hoge            # 参照仕様
```

### タブ文字について
yamlではタブ文字は利用できません

### 複数のYAMLドキュメントを1ファイルに含めたい場合・読み込ませたくない行について
この場合には、「---」を利用します。尚、以降の行を読み込ませたくない場合には「...」を利用します。
```
---
aaa: aaa_value
bbb: bbb_value
---
ccc: ccc_value
...
ddd: ddd_value        # 「...」以降の行は読み込まれません
```

### YAMLのバージョンを指定する
以下の例ではyaml1.2で読み込むように指定しています。
```
--- %YAML 1.2
```

### 文字エンコーディング指定について
文字エンコーディング指定は特に必要ありません。

### YAML関連ライブラリメモ
- Spyc
  - sourceforgeからダウンロードして利用できるライブラリです。
- php_yaml
  - php_yamlはlibyamlのPHP用ラッパーです。
- Syck for PHP
  - PEARからダウンロードできるライブラリです。

詳細は以下に様々な言語のYAMLを紹介しています。
- http://yaml.org/

# 参考URL
- プログラマーの為のyaml入門(初級編)
  - http://jp.rubyist.net/magazine/?0009-YAML
- 指定できるデータ型について
  - http://yaml.org/type/index.html

# 一次資料
- yaml公式サイト(English)
  - http://yaml.org/
- yaml仕様書(V1.2) 英語
  - http://www.yaml.org/spec/1.2/spec.html
