# 概要
git grepについて

殆どのオプションは通常のgrepと同等と思われます。
```
    -i : 大文字と小文字を区別せずに検索する
    -w : 単語境界(行頭か単語に含まれない文字で始まり、行末か単語に含まれない文字で終わる)のみに検索する
    -v : マッチしなかった行が出力される（通常の逆の検索）
    -h : マッチしたファイル名を行頭に表示するか否かの指定です。
    -G : 検索に POSIX の標準正規表現を利用します
    -F : 検索に正規表現を利用しません
    -n : マッチしたファイル名の後ろにマッチした行数を表示します
    -l : マッチしたファイルのファイル名だけを表示します
    -L : マッチしなかったファイル名だけを表示します
```

ヘルプを見るには次のようにして見れます
```
man git-grep
```

# 詳細

### 特定の拡張子の中から検索する
以下では.hファイルのみから"test"という文字列が存在する情報だけgrepする
```
$ git grep test -- "*.h"
```

なお、.hと.ccの拡張子から検索する場合にはそのまま引数として指定するだけで問題ない
```
$ git grep test -- "*.h" "*.cc"
```

以下のように記述することでも、.hと.cから検索することが可能です。
```
$ git grep test -- '*.[ch]'
```

### word, igreno, numberオプションを使う
```
$ git grep -winH v8
```

### 前後N行を表示する
```
$ git grep -C 2 -e string
```

### and, or検索の活用
```
# require と anythingの両方を含む行
git grep -e require --and -e anything

# require と anythingのどちらかを含む行
git grep -e require --or -e anything

# anythingは含むけど、requireは含まない行
git grep -e anything --and --not -e require

# anythingを含む行で、かつ、moccurかctagsのどちらかを含む行
git grep -e anything --and \( -e moccur --or -e ctags \)
```

次のコマンドでもhoge, fugaの両方マッチした行だけを表示させることができます
```
$ git grep --all-match -e hoge -e fuga 
```

### POSIX extended regexでマッチ
次のようにすることで数字にマッチした行を取得できるようになる。
```
$ git grep --extended-regexp -e "[0-9]+"
```

### 行番号を常に付与
オプションを付与せずに常に付与したい場合次のようにします
```
git config --global grep.lineNumber true
```

### grepでマッチした行番号やファイル名の色を変更したい
$HOME/.gitconfigに以下を配置します。
```
[color "grep"]
match = cyan
linenumber = bold white
filename = yellow
...
```

あとはgit grepを実行してみます。以下のコマンドは実行例です。
```
$ git grep -winH v8
```

# 参考
- git-grep(1) Manual Page 
  - https://img.atwikiimg.com/www8.atwiki.jp/git_jp/pub/git-manual-jp/Documentation/git-grep.html

