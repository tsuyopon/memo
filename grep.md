# 概要
grepコマンドに関するtipsなど

# 詳細
### 特定のディレクトリや特定のファイルを検索対象から除外する場合
```
$ export GREP_OPTIONS="--exclude-dir=.git --exclude-dir=doc --exclude-dir=experimental --exclude=cscope.out --exclude=tags"
```

### エスケープシーケンスを不要にしたい
例えば、次の様な文字列を含むソースコードを検索したい場合
```
['hoge']['fuga']
```

毎回以下の様にエスケープシーケンスするのは非常に面倒です。
```
grep -rinH "\['hoge'\]\['fuga'\]"
```

この場合には grep -Fを使います。または、実質同じコマンドであるfgrepを利用します。
```
grep -F "['hoge']['fuga']" ./*
```

ただし、「$」の場合にはバックスラッシュ(\)でエスケープが必要となる様です。
```
grep -F "\$hoge['hoge']['fuga']" ./*
```

