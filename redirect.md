# 概要
リダイレクトやパイプなどに関する処理についてのメモ

### 標準出力も標準エラー出力も表示する場合
同一の出力先に対して出力するにはこれで可能
```
$ command 2>&1  | tee log.txt
```

標準出力と標準エラー出力を分けたいような場合には若干面倒になる。
- http://boscono.hatenablog.com/entry/20130227/p1

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

### コマンドラインからファイルを生成する
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


# 参考URL
- 覚えてると案外便利なBashのリダイレクト・パイプの使い方9個
 - https://orebibou.com/2016/02/%E8%A6%9A%E3%81%88%E3%81%A6%E3%82%8B%E3%81%A8%E6%A1%88%E5%A4%96%E4%BE%BF%E5%88%A9%E3%81%AAbash%E3%81%AE%E3%83%AA%E3%83%80%E3%82%A4%E3%83%AC%E3%82%AF%E3%83%88%E3%83%BB%E3%83%91%E3%82%A4%E3%83%97/
- http://qiita.com/laikuaut/items/e1cc312ffc7ec2c872fc
