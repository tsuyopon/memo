# アセンブラについて
アセンブリ言語はプログラム可能な機器を動作させるための機械語を人間にわかりやすい形で記述する低水準言語である。  
アセンブリ言語で記述されたプログラムを機械語プログラムに変換することをアセンブルするといい(コンパイル言語の場合はコンパイルするといいます)、それを行うプログラムをアセンブラと呼びます。

アセンブラには２つの記述方法があります。
- AT&T記法
  - AT&Tはアメリカの代表的通信業者
  - GCCで標準的に使われるGASはこちらの記法である。(ただし、GASでも指定でIntel記法にできる。)
- Intel記法
  - 最も違うのIntel記法であるNASM(Netwide Assembler)やMASM(Microsoft Assembler)はGASの場合とオペランドの順番が逆ということである。これ以外にも細かな文法の違いはある。

主要な記法の違いを記しておく

| 記法 | MASM | GAS(AT&T)  | GAS(Intel) |
| :---: | :--- | :--- | :--- |
| instruction | mov <to> <from> | mov <from> <to> | mov <to> <from> |
| comment | # comment | # comment | @ comment|
| literal | 29 | $29 | #29 |
| register | reg | %reg | reg |

アセンブラの種類については以下を参照のこと
- http://ja.wikibooks.org/wiki/X86%E3%82%A2%E3%82%BB%E3%83%B3%E3%83%96%E3%83%A9/x86%E3%82%A2%E3%82%BB%E3%83%B3%E3%83%96%E3%83%A9

ここでは、アセンブリ言語でプログラムを記述するために重要なレジスタの意味について記載しておく

# 基本事項

### CPU基礎
レジスタなどを理解するためにCPUとそれが何bitレジスタに対応したCPUかを記載しておく
```
年代     CPU              bit   概要
1971     4004             8 	　
1973     8080             16 	　
1978     8086             16 	　
1984     80286            16 	　
1985     80386            32 	　
1989     80486            32 	　
1993     Pentium(i586) 	  32     Pentaは数字の5を意味する。この時から486などの数番からPentiumという言葉をつかう
1994     PentiumPro(i686) 32     80686という位置付けだが、Pentiumから名前で呼ぶようになったためPentium Proといわれた。
1997     MMX Pentium 	  32     MMX命令の追加
1997     PentiumⅡ         32     オペコードの拡張とCPUの集積化（CPUの大きさを小さくすればそれだけ電力が少なくなるため、
1999     PentiumⅢ         32     オペコードの拡張とCPUの集積化
2000     Pentium 4 	      32     3Dグラフィックなどマルチメディア系命令がどんどん追加される。
2001     Itenium 	      64     IntelとPentiumを文字って作られた用語。Intel初の64bitプロセッサ。サーバ用
2002     Itenium2 	      64     サーバ用、オペコードの拡張とCPUの集積化
2004     Pentium-M 	      32     Pentium4の熱問題が原因で、新しく設計された省電力版Pentium
```

- 参考資料
  - http://ascii.jp/elem/000/000/536/536012/

### レジスタ概要

- 汎用レジスタ
```
レジスタ名 	呼び名                          一般的な役割
eax         アキュムレータ                  何に使っても良いが、計算につかうことが多い
ebx         ベースレジスタ                  何に使っても良いが、アドレスのベースにつかうことが多い
ecx         カウンタレジスタ                何に使っても良いが、反復処理のカウントとして使うことが多い
edx         データレジスタ                  何に使っても良いが、計算につかうことが多い
esi         ソースインデックス              ストリング命令で使用しますが、何に使っても良い
edi         デスティネーションインデックス  ストリング命令で使用しますが、何に使っても良い
esp         スタックポインタ                メモリ制御につかう。一般にプログラマは、スタック領域の読み込みに利用。
ebp         ベースポインタ                  メモリ制御につかう。一般にプログラマは、スタック領域の読み書きに利用。
```
EAX,EBX,EDX(AX,BX,DX)は、一般的に何に用いても良い。   
ECXは主にカウンタとして利用することが多いが何に用いてもよい。

- ステータス・制御レジスタ
```
eip     インストラクションポインタ  次に行う命令が入る。次に実行すべきアドレスのオフセットを指している。
eflags  フラグ                      比較、分岐などの際にこのフラグを確認する。CPUの状態や前の命令の実行結果のエラー状態が入ります。
                                    この中にCF, PF, AF, ZF, SF, IF, DF, OFなどの各種フラグが含まれています。
```

- セグメントレジスタ
```
cs      コードセグメント        コードがどこから始まるかメモリの場所を指定する。次に実行すべき命令があるアドレスのセグメントを指しているとのこと
ds      データセグメント        データがどこから始まるかメモリの場所を指定する
es      エクストラセグメント    その他がどこから始まるかメモリの場所を指定する
ss      スタックセグメント      スタックがどこから始まるかメモリの場所を指定する
fs      　
gs      　
```

最初に説明した汎用レジスタは特にビット数などでもレジスタの呼称が変わるので押さえておくこと
eaxは32bit(4byte)で構成される。
```
1bit〜8bit目をAL,
9bit〜16bit目をAH,
1bit〜16bit目をAX
```

ebxは32bit(4byte)で構成される。
```
1bit〜8bit目をBL
9bit〜16bit目をBH,
1bit〜16bit目をBX
```

ecxは32bit(4byte)で構成される。
```
1bit〜8bit目をCL
9bit〜16bit目をCH,
1bit〜16bit目をCX
```

edxは32bit(4byte)で構成される。
```
1bit〜8bit目をDL
9bit〜16bit目をDH,
1bit〜16bit目をDX
```

esi, edi, esp, ebpは1〜16bit(2byte)をそれぞれsi, di, sp, bpと呼びます。

- 参考
  - http://www5c.biglobe.ne.jp/~ecb/assembler/1_1.html
  - http://www5c.biglobe.ne.jp/~ecb/assembler/assembler00.html

### フラグレジスタ詳細(EFLAGS)
演算の結果によって変化するレジスタです。他のレジスタと大きく異なるのは各ビットごとに意味があることです。

フラグレジスタはEFLAGSのみです。

各ビットの意味は以下の通りです。

```
Bit 31～22. 未使用
Bit 21.     IDフラグ：CPUID命令の使用を制御する。(ID)
Bit 20.     仮想割り込みペンディングフラグ：仮想86モードでの割り込み関連のフラグ(VIP)
Bit 19.     仮想割り込みフラグ：仮想86モードでの割り込み関連のフラグ(VIF)
Bit 18.     アラインメントチェックフラグ：メモリアクセスのアラインメントチェックを制御するフラグ(AC)
Bit 17.     仮想86モードフラグ：仮想86モードの制御をするフラグ(VM)
Bit 16.     レジュームフラグ：デバッグ関連の制御フラグ(RF)
Bit 15.     未使用
Bit 14.     ネストタスクフラグ：タスクがネストしているかどうかを示す。(NNT)
Bit 13～12. 割り込み特権レベルフラグ：動作中タスクの割り込み特権レベルを示す。(IOPL)
Bit 11.     オーバーフローフラグ(OF)
Bit 10.     ディレクションフラグ(DF)
Bit 9.      インタラプトフラグ(IF)
Bit 8．     トラップフラグ(TF)
Bit 7.      サインフラグ (SF)
Bit 6.      ゼロフラグ (ZF)
Bit 5.      未使用
Bit 4.      補助キャリーフラグ(AF)
Bit 3.      未使用
Bit 2.      パリティフラグ (PF)
Bit 1.      未使用
Bit 0.      キャリーフラグ (CF)
```

# 参考URL
- GNU アセンブラ入門(GAS) 
  - http://www.oklab.org/program/assembler/gas.html
- x86系(8086系)アセンブラ入門
  - http://www5c.biglobe.ne.jp/~ecb/index.html
  - http://www5c.biglobe.ne.jp/~ecb/assembler/assembler00.html
- 記法
  - http://sci10.org/on_gcc_asm.html
- x86レジスタ一覧
  - http://www.wiki.os-project.jp/?x86%2FRegister
- GCC-Inline-Assembly-HOWTO
  - http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html

