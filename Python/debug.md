# 概要
Pythonでのデバッグ方法について

# 適当に使ってみる 
サンプルとしてはこのディレクトリ中にあるUnittestPdbSample.pyを使えば良い。(これはunittestのサンプルにもなっている)
以下は実行サンプルです
```
$ python -m pdb UnittestPdbSample.py 
> /Users/tsuyoshi/git/mymemo/memo/Python/UnittestPdbSample.py(3)<module>()
-> import unittest
(Pdb) b 10
Breakpoint 1 at /Users/tsuyoshi/git/mymemo/memo/Python/UnittestPdbSample.py:10
(Pdb) c
> /Users/tsuyoshi/git/mymemo/memo/Python/UnittestPdbSample.py(10)Sample()
-> def to_even(self, lst):
(Pdb) list
  5  	
  6  	class Sample(object):
  7  		"""
  8  		テスト対象のクラス
  9  		"""
 10 B->		def to_even(self, lst):
 11  			"""
 12  			リストを渡すと、偶数だけにして返す
 13  			"""
 14  	
 15  			# 意図的にバグらせていて、奇数しか返さない
(Pdb) n
> /Users/tsuyoshi/git/mymemo/memo/Python/UnittestPdbSample.py(10)Sample()->{'__doc__': '\n\t\xe3\x83...3\x82\xb9\n\t', '__module__': '__main__', '__return__': {'__doc__': '\n\t\xe3\x83...3\x82\xb9\n\t', '__module__': '__main__', '__return__': {'__doc__': '\n\t\xe3\x83...3\x82\xb9\n\t', '__module__': '__main__', '__return__': {'__doc__': '\n\t\xe3\x83...3\x82\xb9\n\t', '__module__': '__main__', '__return__': {'__doc__': '\n\t\xe3\x83...3\x82\xb9\n\t', '__module__': '__main__', '__return__': {'__doc__': '\n\t\xe3\x83...3\x82\xb9\n\t', '__module__': '__main__', '__return__': {...}, 'to_even': <functio...0e6eeaa0>}, 'to_even': <functio...0e6eeaa0>}, 'to_even': <functio...0e6eeaa0>}, 'to_even': <functio...0e6eeaa0>}, 'to_even': <functio...0e6eeaa0>}, 'to_even': <functio...0e6eeaa0>}
-> def to_even(self, lst):
(Pdb) n
> /Users/tsuyoshi/git/mymemo/memo/Python/UnittestPdbSample.py(20)<module>()
-> class TestSample(unittest.TestCase):
(Pdb) 
> /Users/tsuyoshi/git/mymemo/memo/Python/UnittestPdbSample.py(38)<module>()
-> if __name__ == '__main__':
(Pdb) n
> /Users/tsuyoshi/git/mymemo/memo/Python/UnittestPdbSample.py(39)<module>()
-> unittest.main()
(Pdb) s
--Call--
> /System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/unittest/main.py(72)__init__()
-> def __init__(self, module='__main__', defaultTest=None, argv=None,
(Pdb) p self
<unittest.main.TestProgram object at 0x10e6d4b10>
(Pdb) p module
'__main__'
(Pdb) n
> /System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/unittest/main.py(76)__init__()
-> if isinstance(module, basestring):
(Pdb) n
> /System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/unittest/main.py(77)__init__()
-> self.module = __import__(module)
(Pdb) n
> /System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/unittest/main.py(78)__init__()
-> for part in module.split('.')[1:]:
(Pdb) 
> /System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/unittest/main.py(82)__init__()
-> if argv is None:
(Pdb) 
```

以下は代表的な
```
s(tep)   ステップイン
n(ext)   ステップオーバー
r(eturn) ステップアウト
l(ist)   現在行の前後のソースコードを表示
a(rgs)   現在いる関数の引数を表示
p        出力
c        次のブレイクポイントまで実行
```


# 参考URL
- pdbを使ってみる際のとっかかりになりそうな資料
 - http://www.sakito.com/2012/10/python-debuggerpdb.html
- pdb - The Python Debugger
 - https://docs.python.org/3/library/pdb.html
