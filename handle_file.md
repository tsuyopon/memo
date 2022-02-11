# 概要
ファイル操作で結合処理を行う方法について記載します。

- paste
  - 複数のファイルを同じ行番号同士で結合します。
  - 1つのファイルを1行に書き出して結合することもできます

- join
  - それぞれのフィールドを指定して内部結合・外部結合のような処理が可能です


# 詳細

次のA.txt, B.txtの２つのファイルがあることを仮定します

```
$ cat sample1.txt
01 AAAAA abcde
02 bbbbb fghij
03 ccccc klmno
04 ddddd pqrst
05 eeeee uvwxy
```

```
$ cat sample2.txt
01 AAAAA ABCDE
02 BBBBB FGHIJ
03 CCCCC KLMNO
04 DDDDD PQRST
```


## joinコマンド 

(重要) joinコマンドで結合するためには予め指定するファイルが共に適切にsortされている必要があります。
ソート済みのファイル同士を上から比較することで、"ファイル1のサイズ"+"ファイル2のサイズ"のオーダーの計算量で比較を行ないます。
例えば、ファイル1が100万行,ファイル2が1000万行だったときには計算量のオーダーは1100万回となります。

なお、注意点としてjoinを実行する前に利用するsortコマンドは以下の環境依存項目があるためにLANG=Cなどの環境変数を付与することが推奨されています。
- 大文字小文字を無視する
- 数値以外を無視する
- ハイフンやプラスを無視する
- 上記以外

以下のようなコマンドを実行します
```
LANG=C sort [ファイル1] > [ソート済みファイル1]
```

(参考資料) https://qiita.com/taruhachi/items/04ccca5e3bc20ad01791

### 先頭カラムでjoinする
この場合にはオプションは指定不要です。
```
$ join sample1.txt sample2.txt 
01 AAAAA abcde AAAAA ABCDE
02 bbbbb fghij BBBBB FGHIJ
03 ccccc klmno CCCCC KLMNO
04 ddddd pqrst DDDDD PQRST
```

### 結合カラムを指定してjoinする
1つ目に指定したファイル(sample1.txt)の2番目のフィールドとして「-1 2」を、
2つ目に指定したファイル(sample2.txt)の2番目のフィールドとして「-2 2」を指定する。

下記の場合には内部結合となるために一致した行のみを表示する
```
$ join -1 2 -2 2 sample1.txt sample2.txt 
AAAAA 01 abcde 01 ABCDE
```

ペアにならなかった行も含めて表示する場合には-aオプションを指定する。

1つ目に指定したファイル側でペアにならなかったフィールドも表示する。この場合には「-a 1」と指定する。
```
$ join -a 1 -1 2 -2 2 sample1.txt sample2.txt 
AAAAA 01 abcde 01 ABCDE
02 bbbbb fghij
03 ccccc klmno
04 ddddd pqrst
05 eeeee uvwxy
```

2つ目に指定したファイル側でペアにならなかったフィールドも表示する。この場合には「-a 2」と指定する。
```
$ join -a 2 -1 2 -2 2 sample1.txt sample2.txt 
AAAAA 01 abcde 01 ABCDE
02 BBBBB FGHIJ
03 CCCCC KLMNO
04 DDDDD PQRST
```

なお、内部結合できずにペアにならなかったフィールドだけ表示することもできます。
この場合には「-v」の後に表示したいN番目のファイルを指定します。
```
$ join -v 1 -1 2 -2 2 sample1.txt sample2.txt
02 bbbbb fghij
03 ccccc klmno
04 ddddd pqrst
05 eeeee uvwxy
```

```
$ join -v 2 -1 2 -2 2 sample1.txt sample2.txt
02 BBBBB FGHIJ
03 CCCCC KLMNO
04 DDDDD PQRST
```


### 出力順を指定する
-oオプションとして出力する順番を指定することができます。
```
# -o オプションで出力フォーマットを指定
# 0 はキー列
# 1.2 は1番目ファイルの2列目
# 2.2 は2番目ファイルの2列目
# 1.3 は1番目ファイルの3列目
# 2.3 は2番目ファイルの3列目


$ join -a 2 -1 1 -2 1 -o '0 1.2 2.2 1.3 2.3' sample1.txt sample2.txt 
01 AAAAA AAAAA abcde ABCDE
02 bbbbb BBBBB fghij FGHIJ
03 ccccc CCCCC klmno KLMNO
04 ddddd DDDDD pqrst PQRST
```

### 大文字・小文字を無視して結合する
iオプションらしいがMACではうまくいかず..


## pasteコマンド 

### ２つのファイルを行で結合する。
pasteコマンドは行で結合する。垂直に結合するcatとは逆の操作となる。
```
$ paste sample1.txt sample2.txt 
01 AAAAA abcde	01 AAAAA ABCDE
02 bbbbb fghij	02 BBBBB FGHIJ
03 ccccc klmno	03 CCCCC KLMNO
04 ddddd pqrst	04 DDDDD PQRST
05 eeeee uvwxy	
```

なお、デリミタを指定して結合することもできます。
```
$ paste -d ":" sample1.txt sample2.txt 
01 AAAAA abcde:01 AAAAA ABCDE
02 bbbbb fghij:02 BBBBB FGHIJ
03 ccccc klmno:03 CCCCC KLMNO
04 ddddd pqrst:04 DDDDD PQRST
05 eeeee uvwxy:

$ paste -d , sample1.txt sample2.txt 
01 AAAAA abcde,01 AAAAA ABCDE
02 bbbbb fghij,02 BBBBB FGHIJ
03 ccccc klmno,03 CCCCC KLMNO
04 ddddd pqrst,04 DDDDD PQRST
05 eeeee uvwxy,
```

各ファイルを1行にして結合する
```
$ paste -s sample1.txt sample2.txt 
01 AAAAA abcde	02 bbbbb fghij	03 ccccc klmno	04 ddddd pqrst	05 eeeee uvwxy
01 AAAAA ABCDE	02 BBBBB FGHIJ	03 CCCCC KLMNO	04 DDDDD PQRST
```

上記場合にもデリミタを指定することが可能
```
$ paste -d , -s sample1.txt sample2.txt 
01 AAAAA abcde,02 bbbbb fghij,03 ccccc klmno,04 ddddd pqrst,05 eeeee uvwxy
01 AAAAA ABCDE,02 BBBBB FGHIJ,03 CCCCC KLMNO,04 DDDDD PQRST
```

# 参考URL
