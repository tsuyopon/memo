# 概要
pythonのデバッグ方法について
pdgを使ったデバッグについては、pdb.mdの方を参考にすること


# 詳細

### printで出力する
通常の出力であれば次のようにすればよい。
```
print('{0} is {1} years old / {0}{0}{0}'.format(s, i))
```

オブジェクトを出力したい場合にはpprintで出力した方がオブジェクトであるJSONが綺麗に出力される
```
import pprint
pprint.pprint(vars(self.hoge))
```


- 参考
  - https://note.nkmk.me/python-print-basic/


### バックトレースを出力する

関数のスタックトレースを出力したい場合、出力したい箇所に以下の2行をそのまま埋め込むと良い。
```
import traceback
traceback.print_stack()
```

- 参考: traceback --- スタックトレースの表示または取得
  - https://docs.python.org/ja/3/library/traceback.html


### エラー時のスタックトレース

```
import traceback
 
try:
    raise Exception
except:
    traceback.print_exc()
```

実行結果の例
```
Traceback (most recent call last):
  File "sample.py", line 4, in <module>
    raise Exception
Exception
```

- 参考
  - https://uxmilk.jp/39845


### 現在のコードの行番号
以下のような関数を定義しておいて、
```
import inspect
def location(depth=0):
    frame = inspect.currentframe(depth+1)
    return (frame.f_code.co_filename, frame.f_lineno)
```

好きな箇所で次のように呼び出すことで
```
print location()
```

ファイル名と行番号を次のように出力してくれます。
```
('hoge.py', 12)
```


# 参考URL
- https://qiita.com/podhmo/items/6657ae7b6ffbadc8f773
- StackOverflow: Print current call stack from a method in Python code
  - https://stackoverflow.com/questions/1156023/print-current-call-stack-from-a-method-in-python-code
