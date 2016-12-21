# 概要
リダイレクトやパイプなどに関する処理についてのメモ


### リダイレクトをちゃんと理解する
これの意味について考えて見る。
```
$ command 1>file 2>&1
```

まずcommandだけ実行するとどうなるかというと、１は画面、２は画面に出力される。
続いて、command 1>fileとすると、1はfile、2は画面に出力される
続いて、command 1>file 2>&1とすると、"2の出力先は1と一緒にしたいという意図を2>&1が表す"ので1と2ともfileに出力される


### 標準出力も標準エラー出力も表示する場合
同一の出力先に対して出力するにはこれで可能
```
$ command 2>&1  | tee log.txt
```

標準出力と標準エラー出力を分けたい場合には次のようにすることで可能
```
$ command 1>file1 2>file2
```

### 標準エラー出力のみをパイプに出力する
```
$ command 2>&1 >/dev/null | command2
```

### 標準出力と標準エラー出力を入れ替える
```
$ command 3>&1 1>&2 2>&3
```

### ファイルディスクリプタを使ってファイルへ書き込む
```
$ exec 3>/tmp/hoge
$ echo "aaaaaaaa" >&3
$ cat /tmp/hoge
aaaaaaaa
```

### ファイルディスクリプタを使ってファイルへの書き込み・読み込みを行う
```
$ exec 3<>/tmp/hoge
$ echo "aaaaaaaa" >&3
$
$ exec 3<>/tmp/hoge
$ grep "" <&3
aaaaaaaa
```

### グルーピングしてリダイレクトする
```
$ (command1;command2;...) > file    # サブシェルあり
$ { command1;command2;...; } > file # サブシェルなし
```

### コマンドに複数のコマンドの実行結果を渡す
次のように使えば一時ファイルに書き出す必要なども無いので便利

```
$ sort /work/test_sort1
1 aaaaaa
2 dddddd
5 bbbbbb
6 gfgfgr

$ sort /work/test_sort2
1 aaaaaa
3 cfffff
4 bbbbbb
6 gfgfgr

# diff <(sort /work/test_sort1) <(sort /work/test_sort2)
2,3c2,3
< 2 dddddd
< 5 bbbbbb --- > 3 cfffff
> 4 bbbbbb
```

### パイプで繋がれた各実行結果のステータスを確認する
PIPESTATUS配列で確認することができます。  
以下の4つのコマンドを実行した場合、hoge, fuga, piyoは実行エラーとなるのでそのエラーステータスが入っています。
```
$ echo | hoge | fuga | piyo 
bash: fuga: command not found...
bash: piyo: command not found...
bash: hoge: command not found...
$ echo ${PIPESTATUS[@]}
0 130 130 130
```

### コマンドに文字列を送る
<<<というのがあるのを知った。
```
$ cat <<< "This Server is $(hostname)."
This Server is localhost.localdomain.
```

### sudoでリダイレクトしたい場合
cオプションあとは囲めばOK
```
$ sudo sh -c "echo 'redirect' >> /var/test/hoge.txt"
```

teeを使っても同様のことをできます
```
$ echo "redirect" | tee -a /var/test/hoge.txt
```

### コマンドラインから複数行のファイルを生成する
次を実行するだけでコマンドラインからファイルを生成することが可能です。
```
$ cat > hello.c << "EOF"
#include <stdio.h>

int main(int argc, char* argv[])
{
printf("hello\n");

return 0;
}
EOF
$ cc -O0 -g hello.c
```

なお、タブを入力したい場合には次のように<<-となるらしい。。
```
コマンド <<- EOF
......
EOF
```

# TODO
以下のコンフルを見てまとめる
- http://qiita.com/laikuaut/items/e1cc312ffc7ec2c872fc

# 参考URL
- 覚えてると案外便利なBashのリダイレクト・パイプの使い方9個
 - https://orebibou.com/2016/02/%E8%A6%9A%E3%81%88%E3%81%A6%E3%82%8B%E3%81%A8%E6%A1%88%E5%A4%96%E4%BE%BF%E5%88%A9%E3%81%AAbash%E3%81%AE%E3%83%AA%E3%83%80%E3%82%A4%E3%83%AC%E3%82%AF%E3%83%88%E3%83%BB%E3%83%91%E3%82%A4%E3%83%97/
- http://qiita.com/laikuaut/items/e1cc312ffc7ec2c872fc
