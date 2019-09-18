# 概要
ATT記法のアセンブラについてまとめてみる。

ここではAT&T記法の標準となっているGAS(Gnu Assembler)についてまとめていくことにします。
GASはbinutilsパッケージ中でasコマンドとして提供されています。

Cygwinなどを使っているのであれば、Mingwを使うことでGASをインストールすることができます。


# 詳細

### コメントを記述する
次の３つのコメント記法がサポートされています。
```
/* 複数行にまたがってもOK */
//
#
```

### レジスタ
GASの命令は「ニーモニック  転送元  転送先」の順序で記述する。
ebxレジスタをeaxレジスタに入れる場合には、レジスタには%を付与します。
```
movl	%ebx,	%eax
```

### 定数
0x20をeaxレジスタに入れる場合には、値に$を付与します。
```
movl	$0x20,	%eax
```

### ディレクティブの種類

```
.byte     1byteのデータを配置する
.word     2byteのデータを配置する
.short    2byteのデータを配置する
.long     4byteのデータを配置する
.int      4byteのデータを配置する
.ascii    アスキーコードの文字列を配置する
```

### アドレスオペランドの記法
```
movl    -4(%ebp, %edx, 4), %eax  # 完全な例: (ebp - 4 + (edx * 4))のアドレスの内容をeaxに転送する
movl    -4(%ebp), %eax           # よくある例: スタックの値をeaxに転送する
movl    (%ecx), %edx             # オフセットのない場合: ポインタの指す内容をレジスタに転送する
leal    8(,%eax,4), %eax         # 算術演算の例: eaxに4を掛け8を足したアドレスをeaxに格納する
leal    (%eax,%eax,2), %eax      # 算術演算の例: eaxの指す値を3倍したアドレスをeaxに格納する
```


# 参考URL
- 公式ウェブサイト
  - https://www.gnu.org/software/binutils/
- Using as (Gas Manual)
  - https://sourceware.org/binutils/docs/as/
  - バージョン指定の場合
    - https://sourceware.org/binutils/docs-2.18/as/index.html
