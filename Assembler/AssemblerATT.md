# 概要
gdbなどでもデバッグに困らないようにATT記法のアセンブラについてまとめてみる。

ここではAT&T記法の標準となっているGAS(Gnu Assembler)についてまとめていくことにします。
GASはbinutilsパッケージ中でasコマンドとして提供されています。


# 詳細

### コメントを記述する
次の３つのコメント記法がサポートされています。
```
/* 複数行にまたがってもOK */
//
#
```

### レジスタ
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


# 参考URL
- 公式ウェブサイト
  - https://www.gnu.org/software/binutils/
- Using as (Gas Manual)
  - https://sourceware.org/binutils/docs/as/
  - バージョン指定の場合
    - https://sourceware.org/binutils/docs-2.18/as/index.html
