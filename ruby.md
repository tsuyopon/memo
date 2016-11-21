
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

### メモ


# 参考URL
- Ruby基本文法まとめ
 - http://qiita.com/oshou/items/b7873c67cf22b5e8b42f
- Ruby基礎文法最速マスター
 - http://route477.net/d/?date=20100125
