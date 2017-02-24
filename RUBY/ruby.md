
# 概要
rubyに関するメモ
とりあえず読むときに困らないように

# 詳細

### インタラクティブに実行する
irbコマンドを使って試せば良い。このコマンドは真っ先に覚えるべきコマンド
```
$ irb
irb(main):001:0> puts "helloworld"
helloworld
=> nil
irb(main):002:0> 100+200
=> 300
```

### イテレータ記法について
以下はrubyのイテレータ記法となる。
```
{|v| xxx = v}
{|v| xxx = v.to_i}    # intに変換
{|v| xxx = v.to_s}    # 文字列に変換
```

### 変数種別について
```
foo   #=> ローカル変数
@foo  #=> インスタンス変数(@)
@@foo #=> クラス変数(@@)
$foo  #=> グローバル変数($)
FOO   #=> 定数(大文字から始まる)
```

@fooのインスタンス変数にはインスタンス変数とクラスインスタンス変数という２種類の利用法があるので注意しよう
- http://qiita.com/mogulla3/items/cd4d6e188c34c6819709

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
- 大文字・小文字変換
```
"abcde".upcase            #=> "ABCDE"
"ABCDE".downcase          #=> "abcde"
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

### 配列関連
```
irb(main):012:0>  ary = [100, 200, 300]    // 配列定義
=> [100, 200, 300] 
irb(main):013:0> print ary[1]              // 出力
200=> nil
irb(main):014:0> ary.length                // 配列サイズの取得(sizeと同じ)
=> 3
irb(main):015:0> ary.size                  // 配列サイズの取得(lengthと同じ)
=> 3
irb(main):016:0> ary.shift                 // 左から取得
=> 100
irb(main):017:0> print ary                 // 配列を出力
[200, 300]=> nil
irb(main):018:0> ary.unshift(5)            // 先頭に値を入れる
=> [5, 200, 300]
irb(main):019:0> ary.pop                   // 末尾から値を取得する
=> 300
irb(main):020:0>  ary.push(9)              // 末尾に値を突っ込む
=> [5, 200, 9]
```

### ハッシュ関連
```
rb(main):001:0> hash1 = {"a" => 1, "b" => 2}    // hashの定義
=> {"a"=>1, "b"=>2}
irb(main):002:0> hash2 = {:a => 1, :b => 2}     // hashの定義
=> {:a=>1, :b=>2}
irb(main):003:0> hash1["a"]            // ダブルクォートで囲んで取得する
=> 1
irb(main):004:0> hash2["a"]            // 存在しない場合nilとなる
=> nil
irb(main):005:0> hash2[a]              // 取得できない
NameError: undefined local variable or method `a' for main:Object
	from (irb):5
	from /usr/bin/irb:12:in `<main>'
irb(main):006:0> hash2[:a]             // hash2の場合には":a"で取得できる
=> 1
irb(main):007:0> hash1.keys            // キーを取得する場合
=> ["a", "b"]
irb(main):008:0> hash2.keys            // キーを取得する場合
=> [:a, :b]
irb(main):009:0> hash1.values          // キーの値を取得する場合
=> [1, 2]
irb(main):010:0> hash1.key?("b")       // キーの存在確認(trueの場合)
=> true
irb(main):011:0> hash1.key?("c")       // キーのそない確認(falseの場合)
=> false
irb(main):013:0> hash1.delete("a")     // キーを削除する場合
=> 1
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

### アクセサ(クラスアノテーション)
次の３種類のアクセサがある。fooは変数名です。
- attr_reader :foo
 - 参照が可能
- attr_writer :foo
 - 更新が可能
- attr_accessor :foo
 - 参照, 更新が可能

- 参考: http://qiita.com/jordi/items/7baeb83788c7a8f2070d

### loop
以下でloopします。Ctrl+Cで止めてください。
```
loop do
  puts "this is loop!"
end
```

### eachメソッド(each, each_char, each_line, each_byte)

- each
eachには次の２種類の記述方法(doを使う場合と{}を使う場合)があります
```
irb(main):014:0> [1, 2, 3].each do |i|
irb(main):015:1* puts i
irb(main):016:1> end
1
2
3
=> [1, 2, 3]
```

```
irb(main):017:0> [1, 2, 3].each{|i| 
irb(main):018:1* puts i
irb(main):019:1> }
1
2
3
=> [1, 2, 3]
```

次のように数値を指定することも可能です。
```
irb(main):020:0> 5.times do |i| puts i end
0
1
2
3
4
=> 5
```

- each_line
```
irb(main):005:0> "hello\njapan\world!".each_line { |line| puts line }
hello
japanworld!
=> "hello\njapanworld!"
```
- each_byte
```
irb(main):001:0> 'Ruby'.each_byte { |b| puts b}
82
117
98
121
=> "Ruby"
```

### 引数
以下で表示させることができます。
```
p ARGV
```

ファイル名は$0で取得できるようです。
ARGV[0]といった感じで個別に取得することもできるようだ。
```
f = open(ARGV[0])
```


### ファイル入出力
- read
```
str = File.read("foo.txt") 
```
- write
```
File.open("out.txt", "wb") do |f|
  f.write str
end
```

### MEMO
```
$ irb
irb(main):001:0>  [1,2,3,4,5].select{|x| x.even?}     // 条件にマッチするものだけ
=> [2, 4]
irb(main):002:0>  [1,2,3,4,5].reject{|x| x.even?}     // 条件にマッチするものだけを除く
=> [1, 3, 5]
irb(main):003:0>  [1,2,3,4,5].detect{|x| x.even?}     // 条件に合う最初のやつを探す
=> 2
irb(main):004:0>  [1,2,3,4,5].member?(3)              // 指定した値があるかどうかを判定する
=> true
irb(main):005:0> [1,2,3,4,5].any?{|x| x.even?}        // 条件に合うものがあるかどうか
=> true
irb(main):006:0>  [1,2,3,4,5].all?{|x| x.even?}       // すべての要素が条件に合うかを調べる
=> false
irb(main):007:0>  [1,2,3,4,5].count{|x| x.even?}      // 条件にあった個数を表示する
=> 2
irb(main):008:0>  [1,2,3,4,5].max                     // 最大のものを返す
=> 5
irb(main):009:0>  [1,2,3,4,5].min                     // 最小のものを返す
=> 1
irb(main):010:0>  [1,-2,3,-4,-5].max_by{|x| x.abs}    // 絶対値が最大のものを返す
=> -5
irb(main):011:0>  [1,-2,3,4,-5].min_by{|x| x.abs}     // 絶対値が最小のものを返す
=> 1
irb(main):012:0>  [1,-2,3,4,-5].sort                  // 昇順にソートする
=> [-5, -2, 1, 3, 4]
irb(main):013:0>  [1,-2,3,4,-5].sort_by{|x| x.abs}    // 加工結果で昇順ソート
=> [1, -2, 3, 4, -5]
irb(main):014:0>  [1,-2,3,4,-5].collect{|x| x.abs}    // 加工結果を配列で返す
=> [1, 2, 3, 4, 5]
irb(main):015:0> 'Ruuuubbbbyyyyy'.squeeze             // 重複文字を除去する
=> "Ruby"
irb(main):016:0> 'Ruuuubbbbyyyyy'.squeeze('ub')       // 指定した重複文字を除去
=> "Rubyyyyy"
irb(main):017:0> 'Ruby is practical programming language!'.sub(/p.*?\s/, 'awesome ')   // 文字列の置換
=> "Ruby is awesome programming language!"
irb(main):018:0> "  Ruby \n\t ".strip                 // 空白行・改行・タブのstrip
=> "Ruby"
irb(main):019:0> 'Ruby is my 1st language!'.slice(0..3)  // 部分取得
=> "Ruby"
irb(main):020:0> 'Ruby is my 1st language!'.slice(/[0-9]+/)  // 正規表現による部分取得
=> "1"
irb(main):021:0> 'Ruby is practical programming language!'.gsub(/p.*?\s/){|str| str.upcase}  // 見つかった部分を大文字にして置換
=> "Ruby is PRACTICAL PROGRAMMING language!"
irb(main):022:0> 'Ruby is practical programming language!'.gsub(/p.*?\s/){ $&.to_s.upcase}   // 上と同じ(マッチした文字列情報を$&で取得)
=> "Ruby is PRACTICAL PROGRAMMING language!"
irb(main):023:0> "abcde".delete("cd")                    // 指定した文字を削除する
=> "abe"
irb(main):024:0> "hi\r\n".chomp                          // chompする
=> "hi"
```

配列
```
irb(main):028:0> [1, 2, 3].reverse_each { |a| p a }      // 逆順ソート
3
2
1
=> [1, 2, 3]
irb(main):029:0> [1, 2, 3] + [4, 5, 6]
=> [1, 2, 3, 4, 5, 6]
irb(main):030:0> [1, 2, 3] + [] 
=> [1, 2, 3]
rb(main):032:0> [1, 2, 3] << 4
=> [1, 2, 3, 4]
irb(main):033:0> [1, 2, 3] << [4, 5]
=> [1, 2, 3, [4, 5]]
```

### 関数の引数について
通常の引数は次のような形で取得する。以下の場合num2は指定されなければデフォルト引数が1となります。
```
def plus(num1, num2=1)
  num1 + num2
end
```
次はキーワード引数です(ruby2.0以降らしい)。これを利用すると引数の順番を逆にすることもできます。
```
def plus(num1:, num2:)
  num1 + num2
end

plus(num1: 3, num2: 5) # => 8 
plus(num2: 3, num1: 5) # => 8 
```

引数に*のアスタリスクを1つ付与すると、可変長引数となります。可変長引数は配列として受け付けられます。
```
def self.piyo(*msg)
  p msg
end

Hoge.piyo('fuga')                # => ['huga']
Hoge.piyo('huga', 'hugahuga')    #=> ['fuga', 'fugafuga']
```

引数に**のアスタリスクを２つ付与すると、オプション引数となります。オプション引数は"ハッシュ"として受け付けられるようになります。
```
def self.piyo(**msg)
  p msg
end

Hoge.piyo(msg: 'fuga')                   #=> {:msg => 'huga'}
Hoge.piyo(msg: 'huga', name: 'hugahuga') #=> { :msg => 'fuga', :name => 'fugafuga' }
```

アンパサンド(&)を付加することによって、ブロックも引数として渡すことができます。ブロックとは{ p "foo" } のように囲まれたものです。
```
def self.piyo(&block)
  block.call
end

Hoge.piyo{ p 'fuga' } # => 'fuga'
```

上記のブロックについてはyieldと同じらしい。しかし、yieldは直感的なのでわかりにくいので個人的にはアンパサンドを使いたい。
- http://d.hatena.ne.jp/yoshidaa/20090511/1241967137
```
def self.piyo
  yield
end
```


### インスタンスメソッド(def xxx)とクラスメソッド(def self.xxx)について
クラスメソッドの方がstatic関数のような使われ方をします。

これら２つの違いは呼び出し方の違いを見ると一目瞭然です。
```
#インスタンスメソッド
dog = Dog.new
dog.ihoge

#クラスメソッド
Dog.ihoge
```

Dogクラスの中にihogeとself.ihoge両方の定義を記述することができます。
なお、initializeというのはコンストラクタであるとrubyでは決まっています。デストラクタはrubyにはありません。
```
class Dog

   # コンストラクタ(インスタンスメソッドだけ呼ばれるはず...)
   def initialize
      puts "start"
   end

   # インスタンスメソッド
   def ihoge
      puts "ihoge"
   end

   # クラスメソッド
   def self.ihoge
      puts "self.ihoge"
   end
end
```

### MODULEとClassの違い
これを見たら一目瞭然です。モジュール空間Zooの中にクラスCatが定義されるような感じです。
```
module Zoo
  class Cat
    def where_self
      self
    end
  end
end
Zoo::Cat.new.where_self
```

言葉にすると
- モジュールはインスタンス化する能力はもたないがクラスやメソッドを格納することができる。
- クラスはオブジェクトになれる。つまりインスタンス化する能力を持ち、インスタンスメソッドとクラスメソッドを格納できる。

## "::"の使い方
Klass.Fooは次のように::を使って呼び出すこともできます。しかしFooの後に()が必要となる。
```
Klass::Foo()
```

::は定数を表す場合に、使う必要があります(例えば、Math::PI)ので覚えておくと良い。


### 豆知識
- 命名規則
 - クラス名は TestClassなどとして最初は大文字として_は使わないこと
 - メソッド名は英小文字のsnake_caseでadd_somethingなどを用いることaddSomethingはNGとなる。
 - 定数は大文字のsnake_caseでEXAMPLE_CONSTANTといった感じで定義する。
 - 変数は英小文字のsnake_caseとなる。local_variableのようにする。
- rubyにはインクリメント演算子が存在しない
- デストラクタのような概念は存在しない
- 真偽にはfalseとnilがある。
- シンボルとはコロン(:)で始まる文字列

### TODO
- rubyのよく使いそうな関数をざっと見てもいいかも
 - http://ref.xaio.jp/ruby/classes/string
- シンボルについてのせておく
- アクセサの例を乗せておく
- クラス継承などについても触れておく

# 参考URL
以下はざっと目をとおしておくと良い
- Ruby基本文法まとめ
 - http://qiita.com/oshou/items/b7873c67cf22b5e8b42f
- Ruby基礎文法最速マスター
 - http://route477.net/d/?date=20100125
- Ruby 2.1 / Rails4.1 の意外に忘れられている便利なメソッド 
 - http://ruby-rails.hatenadiary.com/entry/20150101/1420049679
