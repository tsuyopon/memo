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

### 特定のディレクトリを除外したい
--オプションでディレクトリの指定に':!'を付与することで特定のディレクトリだけ除外することができる。
「:!」の代わりに「:^」を使うこともできるらしい
```
$ git grep 'hoge' -- ':!app/assets/'
```

「:^」の場合の例
```
$ git grep hoge -- :^test/
```

### リポジトリに追加されていない対象のファイルも含める。ただし、.gitignoreで無視対象となっているものを除く
--untrackedまたは--no-exclude-standardオプションを利用します。
```
$ git grep --untracked hoge
CHANGES:     [Tomas Hoger <thoger@redhat.com>]
hogehoge:hogehoge
```

### working treeの代わりにindexを探索する
```
$ git grep --cached hoge
```

### 特定のリビジョンで探索する
```
$ git grep hoge HEAD~100
```

### 指定した単語を含むファイル名のみ出力する
```
$ git grep -l hoge
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

### 前、後、前後の行を表示する
```
# 後の5行
$ git grep -A 5 hoge

# 前の5行
$ git grep -B 5 hoge

# 前後の5行
$ git grep -C 5 hoge
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

### ファイル毎に空行を入れてみやすくする
```
$ git grep --break test
```

### ファイルで何個指定した文字列がマッチしたかを表示する
```
$ git grep -c openssl
.github/PULL_REQUEST_TEMPLATE.md:1
.gitignore:14
ACKNOWLEDGEMENTS:1
CHANGES:162
CONTRIBUTING:5
(snip)
```

### ヒットした文字行の前にある関数名を出力する
```
$ git grep -p reuse apps/*
apps/s_client.c=static int ssl_servername_cb(SSL *s, int *ad, void *arg)
apps/s_client.c:        p->ack = !SSL_session_reused(s) && hn != NULL;
apps/s_client.c=static void print_stuff(BIO *bio, SSL *s, int full)
apps/s_client.c:        if (peer != NULL && !SSL_session_reused(s) && SSL_ct_is_enabled(s)) {
apps/s_client.c:    BIO_printf(bio, (SSL_session_reused(s) ? "---\nReused, " : "---\nNew, "));
apps/s_server.c=static void print_connection_info(SSL *con)
apps/s_server.c:    if (SSL_session_reused(con))
apps/s_server.c=static int www_body(int s, int stype, int prot, unsigned char *context)
apps/s_server.c:            BIO_printf(io, (SSL_session_reused(con)
apps/s_time.c=const OPTIONS s_time_options[] = {
apps/s_time.c:    {"reuse", OPT_REUSE, '-', "Just time connection reuse"},
apps/s_time.c=int s_time_main(int argc, char **argv)
apps/s_time.c:        if (SSL_session_reused(scon)) {
apps/s_time.c:    printf("\n\nNow timing with session id reuse.\n");
apps/s_time.c:    /* Get an SSL object so we can reuse the session id */
apps/s_time.c:        if (SSL_session_reused(scon)) {
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

