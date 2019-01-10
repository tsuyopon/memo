# gcovとは
C言語で記述されたプログラムのカバレッジを測定するツールでgccに付属していて、gcovというコマンドが存在します。
gcovで生成された情報をブラウザ上で閲覧するためのツールとしてlcovがありますが、そちらはlcov.mdで記載しています。

gcovで生成されるプログラムについては以下にあります。
- https://github.com/tsuyopon/cpp/tree/master/gcov

# 詳細

### gcov基本事項
上記プログラムにはカバレッジレポートを生成するオプションが指定されていますが、
```
古いgccの場合:   -fprofile-arcs -ftest-coverage
新しいgccの場合: --coverage
```

上記プログラムをmakeすると次の３つのファイルが生成されます。
- sample1.c.gcov
- sample1.gcda
- sample1.gcno

これらのファイルは次のような意味をもちます。 (参考: https://gcc.gnu.org/onlinedocs/gcc/Gcov-Data-Files.html )
- .gcnoファイル: コンパイル時に生成されソースコードの行番号の情報などが格納されている。fprofile-arcsオプションが指定されると生成される。
- .gcdaファイル: カバレッジデータファイル。このファイルにデータが蓄積される。ftest-coverageオプションが指定されると生成される。
- .gcovファイル: catで閲覧できる。おそらく、.gcnoと.gcdaを合わせて生成したファイルだと思われる(推測です)


### gcovコマンドの使い方
gcovコマンドでカバレッジレポートを見る。
引数にはプログラム名を指定するようです(個人環境では.gcovや他の拡張子を指定しても以下の出力となりました)
```
$ gcov sample1.c
File 'sample1.c'
実行された行:75.00% of 8
Creating 'sample1.c.gcov'
```

fオプションを付与すると各関数の要約情報も表示されます。
```
$ gcov -f sample1.c
Function 'main'
実行された行:100.00% of 4

Function 'bar'
実行された行:0.00% of 2

Function 'foo'
実行された行:100.00% of 2

File 'sample1.c'
実行された行:75.00% of 8
Creating 'sample1.c.gcov'
```

### カバレッジレポートをコマンドラインで確認する。
.covファイルをcatするとカバレッジレポートが出力されます。
```
$ cat sample1.c.gcov 
        -:    0:Source:sample1.c
        -:    0:Graph:sample1.gcno
        -:    0:Data:sample1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include <stdio.h>
        -:    2:
        2:    3:int foo(int x, int y) {
        2:    4:  return x + y;
        -:    5:}
        -:    6:
    #####:    7:int bar(int x, int y) {
    #####:    8:  return x - y;
        -:    9:}
        -:   10:
        1:   11:int main(void) {
        1:   12:  printf("%d\n", foo(2, 3));
        1:   13:  printf("%d\n", foo(3, 4));
        1:   14:  return 0;
        -:   15:}
```

### Jenkinsでカバレッジレポートを表示したい
gcovrツールを使う
- http://futurismo.biz/archives/485

# 参考URL
- Gcov公式リファレンス
  - https://gcc.gnu.org/onlinedocs/gcc/Gcov.html
- 日本語版リファレンス(gcc-2.95.2)
  - http://www.asahi-net.or.jp/~wg5k-ickw/html/online/gcc-2.95.2/gcc_6.html
