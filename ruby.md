
# 概要
rubyに関するメモ
とりあえず読むときに困らないように

# 詳細

### 変数種別について
```
foo   #=> ローカル変数
@foo  #=> インスタンス変数(@)
@@foo #=> クラス変数(@@)
$foo  #=> グローバル変数($)
FOO   #=> 定数(大文字から始まる)
```

### 文字列基本操作
- str1を参照する
```
str1 = 'abc'
str2 = "#{str1} def"  #=> "abc def"
```

- 結合
```
str1 = "aaa" + "bbb"
str2 = ["aaa", "bbb", "ccc"].join(",")
```

- 分割
```
record = "xxx,yyy,zzz".split(/,/)
```
- 長さ
```
length = "abcde".length
length = "abcde".size
```
- 探す
```
index = "abcd".index(/bc/) 
```
- 切り出し
```
substr = "abcd"[0, 2]     #=> "ab" (0番目から2文字)
```

### 出力について
```
print "foo"   #=> 改行なし
puts "foo"    #=> 改行あり
p 123         #=> デバッグ用
```

<<を使うこともできる
```
s = "Hello"
s << ", world"
puts s
```

### インタラクティブに実行する
irbコマンドを使って試せば良い
```
$ irb
irb(main):001:0> puts "helloworld"
helloworld
=> nil
irb(main):002:0> 100+200
=> 300
```

### 破壊的メソッドについて
破壊的メソッドには!を付与する。例えばmap!とか
- http://qiita.com/tadsan/items/7baab2605a4d8ac1858e

### 変数名やメソッド名のルール
- http://qiita.com/oshou/items/b7873c67cf22b5e8b42f

### include?
「include?」で文字列の中に引数の文字列が含まれているかを調べることができる。
```
s = "hoge.com"
puts s.include?("hoge")    # true
```

### アクセサ
次の３種類のアクセサがある。fooは変数名です。
- attr_reader :foo
 - 参照が可能
- attr_writer :foo
 - 更新が可能
- attr_accessor :foo
 - 参照, 更新が可能

- 参考: http://qiita.com/jordi/items/7baeb83788c7a8f2070d

### MEMO
- 全ての要素が条件に合うかを調べる
```
 [1,2,3,4,5].all?{|x| x.even?}    #=> false
```
- 条件に合うものがあるか調べる
```
 [1,2,3,4,5].any?{|x| x.even?}    #=> true
```
- 等しい値があるか調べる
```
 [1,2,3,4,5].member?(3)           #=> true
```

### TODO
- rubyのよく使いそうな関数をざっと見てもいいかも
 - http://ref.xaio.jp/ruby/classes/string

# 参考URL
以下はざっと目をとおしておくと良い
- Ruby基本文法まとめ
 - http://qiita.com/oshou/items/b7873c67cf22b5e8b42f
- Ruby基礎文法最速マスター
 - http://route477.net/d/?date=20100125
- Ruby 2.1 / Rails4.1 の意外に忘れられている便利なメソッド 
 - http://ruby-rails.hatenadiary.com/entry/20150101/1420049679
