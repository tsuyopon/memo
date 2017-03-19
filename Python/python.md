# 概要
python関連の文法についての基本的な事項についてまとめます。

### 覚えておくこと
- pythonはタブによって表現します。
- Pythonには変数の宣言はありません。変数に代入する型も制限されません。

### モジュールを試してみる
pythonコマンドを引数なしで実行すると対話モードとして実行することができるのでちょっとした文法の確認などに重宝する。
```
$ python
Python 2.7.6 (default, Sep  9 2014, 15:04:36) 
[GCC 4.2.1 Compatible Apple LLVM 6.0 (clang-600.0.39)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>> import math
>>> print math.pi
3.14159265359
```

### 文字列操作
```
# 結合
join1 = 'hoge' + 'moge' # 'hogemoge'
join2 = ','.join(['aaa', 'bbb', 'ccc']) # 'aaa,bbb,ccc'

# 分割
record1 = 'aaa bbb  ccc'.split() # ['aaa', 'bbb', 'ccc'] デフォルトでは空白で分割
record2 = 'aaa,bbb,ccc'.split(',') # ['aaa', 'bbb', 'ccc']

# 長さ(文字数)
length = len('Supercalifragilisticexpialidocious') # 34

# 切り出し
# [start:stop]の形で指定して切り出す
substr1 = '0123456789'[:3]  # '012'  0～stop-1を切り出す
substr2 = '0123456789'[3:6] # '345'  start～stop-1を切り出す
substr3 = '0123456789'[6:]  # '6789' start～末尾を切り出す

# 検索
result = 'abcd'.find('cd') # 見つかった場合はその位置、見つからなかった場合は-1が返る
```

### リスト操作
```
array = [1, 2, 3, 4]

# 任意の要素を取り出す
first = array.pop(0)      # first == 1, array == [2, 3, 4]

# 任意の要素を追加する
array.insert(0, 5)        # array == [5, 2, 3]

# 末尾を取り出す
last = array.pop()        # last == 3, array = [5, 2]

# 末尾に追加
array.append(9)           # array == [5, 2, 9]

# 末尾にリストを追加
array.extend([0, 1])      # array == [5, 2, 9, 0, 1]
```

### リストとタプル
```
# 空リストの作成
list1 = []
list2 = list()

# 複数要素からなるリストを作成
list3 = [0, 1, 2]

# 他のリストの(浅い)コピーを作成
list4 = list(list3)

# 連番のリストを作成 
list5 = range(3) # [0, 1, 2] range(stop)は[0, 1, ..., stop-1]を返す
list6 = range(3, 6) # [3, 4, 5] range(start, stop)は[start, start+1, ..., stop-1]を返す
list7 = range(1, 8, 2) # [1, 3, 5, 7] 3番目の引数で値の増減量を指定できる

# 空タプルの作成
tuple1 = ()
tuple2 = tuple()

# 要素が1つのタプルの作成
tuple3 = (1,)

# 複数要素からなるタプルを作成
tuple4 = (0, '1', 2, [3], -4)
```

### タプル・リストの要素数
リストの要素数を取得するにはタプルでもリストでもlenを使えば良い
```
len(mylist)
len(mytuple)
```

### ディクショナリ
```
dic = {} # 空ディクショナリ
dic = dict() # 空ディクショナリその2
dic = {'a': 1, 'b': 2} # key:value, ... の形式で初期化
dic = dict(a=1, b=2) # キーワード引数による初期化
```

### 暗黙の変数_について
暗黙の変数 _ に一つ前に入力した式の結果が代入されます。
```
>>> 1+2
3
>>> _+17
20
>>> _
20
>>> hoge = _ + 100
>>> _                   # 代入の場合だと_は更新されません。
20
```

### 型を調べる
```
>>> type(100)
<class 'int'>
>>> type('hoge')
<class 'str'>
```

### ワンライナーを実行する
```
$ python -c "print 'Hello'"
```

### UTF-8に統一する
プログラムのコメントに次のような行を入れるのが一般的です。
```
# -*- coding: UTF-8 -*-
```

### コマンドライン引数を取得する
次で取得することができます。
```
print sys.argv
```

実行ファイル名は次のように表せます。
```
print sys.argv[0]
```

### 可変長引数の関数を定義する。
- 収まりきらなかった引数はタプルとして*付き引数に
- キーワード引数はディクショナリとして**付き引数に格納されます。
```
def f(arg, *args, **kwargs):
    print arg
    print args
    print kwargs
```

### コメント
シャープの後にコメントを書くと1行コメントとなります。
```
# ここにコメントを書きます。
```

複数行のコメントだと３重ダブルクォートで囲みます。
```
"""
ここに囲む
ここに囲む
"""
```

### 特殊なオブジェクト属性を見る
dir(1)をするとわかります。
```
>>> dir(1)
['__abs__', '__add__', '__and__', '__bool__', '__ceil__', '__class__', '__delattr__', '__dir__', '__divmod__', '__doc__', '__eq__', '__float__', '__floor__', '__floordiv__', '__format__', '__ge__', '__getattribute__', '__getnewargs__', '__gt__', '__hash__', '__index__', '__init__', '__int__', '__invert__', '__le__', '__lshift__', '__lt__', '__mod__', '__mul__', '__ne__', '__neg__', '__new__', '__or__', '__pos__', '__pow__', '__radd__', '__rand__', '__rdivmod__', '__reduce__', '__reduce_ex__', '__repr__', '__rfloordiv__', '__rlshift__', '__rmod__', '__rmul__', '__ror__', '__round__', '__rpow__', '__rrshift__', '__rshift__', '__rsub__', '__rtruediv__', '__rxor__', '__setattr__', '__sizeof__', '__str__', '__sub__', '__subclasshook__', '__truediv__', '__trunc__', '__xor__', 'bit_length', 'conjugate', 'denominator', 'from_bytes', 'imag', 'numerator', 'real', 'to_bytes']
```

### 例外処理
例外はraiseであげて、あとはtry, except, finally, elseで受ける
```
try:
    #何かの処理
    if 条件:
        raise Exception();
except Exception, e:
    # 捕捉したException型の例外はeに代入される
    (略)
finally:
    # 例外の有無に関わらず実行されるブロック(必須ではない)
    (略)
else:
    # 例外が発生しなかった場合のみ実行されるブロック(必須ではない)
```

python2.6からはexceptについては次の書き方ができる。こっちの方がわかりやすいかも
```
except Exception as e:
    # 捕捉したException型の例外はeに代入される
```

### 論理演算
```
x or y  # x が偽なら y 、そうでなければ x
x and y # x が偽なら x 、そうでなければ y
not x   # x が偽なら True 、そうでなければ False
```

### 三項演算子
```
//a=1のとき10が代入、その他の場合20
x = 10 if a == 1 else 20
```

### コンストラクタとデストラクタ
```
class Hoge:
  def __init__(self):  # コンストラクタ
    pass
  def __del__(self):   # デストラクタ
    pass
```

# 参考
- http://d.hatena.ne.jp/dplusplus/20100126/p1