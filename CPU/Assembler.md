# 概要
アセンブラなどの知識についてまとめる

# 基本事項
### CPU基礎
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
 - [http://ascii.jp/elem/000/000/536/536012/]

# x86系(8086)アセンブラ
### アセンブラの基礎構造
```
	.file   "ファイル名.s"
	.data					#ここに変数の定義を書く
	#データを書く
	.text   				#ここから実行文が始まる
	.globl main			    #はじめに呼び出される関数を.globlで指定（globalではなくglobl)
	main:
	        # 命令を書く　
```

### Hello World
```
	$ vim helloworld.s
	.file   "helloworld.s"
	.data
	msg:    .ascii  "hello world\n"
	msgend: .equ    len, msgend - msg

	.globl main
	main:
	        movl $4,        eax    # write system call(sys_write)
	        movl $1,        ebx    # stdout
	        movl $msg,      ecx
	        movl $len,      edx
	        int  $0x80
	        ret

	$ gcc helloworld.s -o hw
	$ ./hw
```

eaxレジスタにsys_writeシステムコールを設定、引数が３つあるのでebxレジスタに出力先の標準出力を意味する$1を設定する。  
第二引数にメッセージのデータ$msgを設定、第三引数にメッセージの長さの$lenを設定、最後にシステムコールのint $0x80を実行してシステムコールを呼び出している。  
またその次の行のretオペコードはreturnをあらわしこれによりプログラムが終了される。  

### システムコール
システムコール番号(13番はtimeシステムコールを呼び出す)と引数を汎用レジスタに設定してソフトウェア割り込み 0x80 を発行  
eaxには、1-jan-1970からの秒数が入る。 
```
	.file "xxx.s"
	.data
	.text
	.global main
	main:
	        movl $13,       eax
	        movl $0,        ebx
	        int     $0x80

	        ret
```

システムコール番号とシステムコールの対応は i386 Linux の場合 i386/kernel/syscall_table.S に記述されています。  
ソースコードではarch/parisc/kernel/syscall.Sにそれが存在しているようです。

### ニーモニック
命令のことをニーモニックという。ニーモニックは、OPコード(オペコード)とオペランド(operand)のことをいう。
```
    movb $0x01 %al
```
上記の例では、移動する命令のmovbがOPコード 、１６進数の数値の$0x01とレジスタを意味する%alをオペランドという。


### オペコード
4004などの8bitCPUは、8bit(1byte)での処理を行っていたので、オペコードで8bitを処理をするにはbyteを意味するbをつける。
```
	movb $0xff %ah
	movb $0xff %al
```

8086などの16bitCPUは、eXtend(拡張)を意味するレジスタを利用し、オペコードで16bitを処理するには16bitを意味するwordのwをつける。
```
	movw $0x01ff %ax
```

386やPentiumなどの32bitCPUは、Extend(拡張)を意味するレジスタを利用し、オペコードで32bitを処理するには32bitを意味するlongのlをつける。
```
	movl $0x123401ff %eax
```

これでハローワールドのmovオペコードの意味が理解できたと思う．また数値は$記号ではじまり、レジスタは%記号で始まる。


### レジスタ

[汎用レジスタ]
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

[ステータス・制御レジスタ]
```
	eip 	インストラクションポインタ 	次に行う命令が入る。次に実行すべきアドレスのオフセットを指している。
	eflags 	フラグ 				    比較、分岐などの際にこのフラグを確認する。CPUの状態や前の命令の実行結果のエラー状態が入ります。
                                    この中にCF, PF, AF, ZF, SF, IF, DF, OFなどの各種フラグが含まれています。
```

[セグメントレジスタ]
```
	cs 		コードセグメント 		コードがどこから始まるかメモリの場所を指定する。次に実行すべき命令があるアドレスのセグメントを指しているとのこと
	ds 		データセグメント 		データがどこから始まるかメモリの場所を指定する
	es 		エクストラセグメント 	その他がどこから始まるかメモリの場所を指定する
	ss 		スタックセグメント 	スタックがどこから始まるかメモリの場所を指定する
	fs 	　 	　
	gs 	　 	　
```

EAX,EBX,EDX(AX,BX,DX)は、一般的に何に用いても良い。   
ECXは主にカウンタとして利用することが多いが何に用いてもよい。

汎用レジスタは特にビット数などでもレジスタの呼称が変わるので押さえておくこと
```
eaxは32bit(4byte)で構成される。
	1bit〜8bit目をAL,
	9bit〜16bit目をAH,
	1bit〜16bit目をAX
ebxは32bit(4byte)で構成される。
	1bit〜8bit目をBL
	9bit〜16bit目をBH,
	1bit〜16bit目をBX
ecxは32bit(4byte)で構成される。
	1bit〜8bit目をCL
	9bit〜16bit目をCH,
	1bit〜16bit目をCX
edxは32bit(4byte)で構成される。
	1bit〜8bit目をDL
	9bit〜16bit目をDH,
	1bit〜16bit目をDX
esi, edi, esp, ebpは1〜16bit(2byte)をそれぞれsi, di, sp, bpと呼びます。
```

* 参考
	* http://www5c.biglobe.ne.jp/~ecb/assembler/1_1.html
	* http://www5c.biglobe.ne.jp/~ecb/assembler/assembler00.html

### フラグレジスタ詳細
演算の結果によって変化するレジスタです。他のレジスタと大きく異なるのは各ビットごとに意味があることです。

フラグレジスタはEFLAGSのみです。

各ビットの意味は以下の通りです。

```
    Bit 31～22. 未使用
    Bit 21. IDフラグ：CPUID命令の使用を制御する。
    Bit 20. 仮想割り込みペンディングフラグ：仮想86モードでの割り込み関連のフラグ
    Bit 19. 仮想割り込みフラグ：仮想86モードでの割り込み関連のフラグ
    Bit 18. アラインメントチェックフラグ：メモリアクセスのアラインメントチェックを制御するフラグ
    Bit 17. 仮想86モードフラグ：仮想86モードの制御をするフラグ
    Bit 16. レジュームフラグ：デバッグ関連の制御フラグ
    Bit 15. 未使用
    Bit 14. ネストタスクフラグ：タスクがネストしているかどうかを示す。
    Bit 13～12. 割り込み特権レベルフラグ：動作中タスクの割り込み特権レベルを示す。
    Bit 11. オーバーフローフラグ(OF)
    Bit 10. ディレクションフラグ(DF)
    Bit 9.  インタラプトフラグ(IF)
    Bit 8． トラップフラグ
    Bit 7.  サインフラグ (SF)
    Bit 6.  ゼロフラグ (ZF)
    Bit 5.  未使用
    Bit 4.  補助キャリーフラグ(AF)
    Bit 3.  未使用
    Bit 2.  パリティフラグ (PF)
    Bit 1.  未使用
    Bit 0.  キャリーフラグ (CF)
```


### C言語との連動(x86拡張インラインアセンブリ)

x86拡張インラインアセンブリは以下の構文で表すことができます。
```
	asm(アセンブリテンプレート : 出力オペランド : 入力オペランド : 破壊されるレジスタのリスト)
```

この構文を用いると任意のレジスタをCの変数として書き出したり、Cの任意の変数の内容を任意のレジスタに設定した上でアセンブリ処理を行うことができるようになります。

##### サンプル1
例えば、
```
	asm(
	    "movl $0x01, %eax;"
	    "addl $0x05, %eax"
	);
```
は処理が終わった後にはeaxは0x06となっています。  

このeaxに設定された足し算結果をCの変数に格納したいような場合には拡張構文を使って以下のように記述できます。
```
	int result;
	asm(
	    "movl $0x01, %%eax;"
	    "addl $0x05, %%eax"
	    : "=a" (result)
	);
```
ここでは前半のmovlやaddlまでを「アセンブリテンプレート」、:以降が「出力オペランド」となります。  
構文の「入力オペランド」と「破壊されるレジスタのリスト」は使わないので省略しています。  

これにより"=a" (result)は「アセンブリ処理の最後にeaxに設定された値をresultという変数に書き出せ」という指令になります。  


##### サンプル2)
サンプル１とは異なり入力オペランドも含めた事例としてサンプル2を確認します。

```
	int x = 1, y = 5;
	int result;
	asm(
	    "movl %2, %%eax;"
	    "addl %1, %%eax"
	    : "=a" (result)
	    : "m" (x), "m" (y)
	);
```

「"m" (x), "m" (y)」が入力オペランドの指定です。  
メモリ中にx, yを設定し、その値をインラインアセンブリの中から指定できるようにしています。  
アセンブリテンプレート中の%1、%2が入出力オペランドに指定した値を参照するための指示詞  
```
	%0: result
	%1: x
	%2: y
```

上記のコードはeaxを経由せずに計算しないようにすれば、もう少し短くすることができます。
```
	int x = 1, y = 5;
	asm(
	    "addl %2, %0;"
	    : "=r" (x)
	    : "0" (x), "m" (y)
	);
```

この場合のポイントとしては
```
	xは入出力兼用
	入力オペランド"0"というのはアセンブリテンプレート内で %0 と同等の意味を持ちます。このように記述することでxが入出力兼用であることを指定しています。
	これによって、%0がx、%2がyで結果はxに出力するという準備が整いました。
```

- 参考資料
 - http://d.hatena.ne.jp/naoya/20070924/1190653790

### "=a"や"=r"などについての意味
"Constraint and Modifier"などで検索すると表示される。

この辺の資料を参考にすると良い
- https://gcc.gnu.org/onlinedocs/gcc/Constraints.html

### .bssとは
Block Started by Symbolの略称
- http://www.ertl.jp/~takayuki/readings/info/no03.html
- http://ja.wikipedia.org/wiki/.bss

ELFでは以下のように定義
	このセクションには、プログラムが使うメモリのうち、初期化されていないデータ(変数)が入っています。  
	定義では、システムはプログラムを走らせる前に、ゼロで初期化しないといけません。  
	このセクションは、SHT_NOBITSというセクション種別が示すように、ファイル内にデータを持ちません。  

.bssに格納されるもの
- 初期値を持たない大域変数
- 初期値が0の大域変数
- 初期値を持たない静的局所変数
- 初期値が0の静的局所変数

レジスタ
- eax 	汎用レジスタ
- ebx 	汎用レジスタ
- ecx 	汎用レジスタ
- edx 	汎用レジスタ

命令
- mov 	代入 	mov (値) (代入先)
- int 	割り込み 	int (番号)

命令
- movb 	1byteの値を代入
- movw 	2byteの値を代入
- movl 	4byteの値を代入

##### 加算
```
	MOV EAX, 13 
	MOV EBX, 4
	ADD EAX, EBX （←EAXにEBXの値を足しなさい）
```

##### 減算
```
	MOV EAX, 13 
	MOV EBX, 4
	SUB EAX, EBX （←EAXからEBXの値を引きなさい）
```

##### 乗算
```
	MOV EAX, 13 
	MOV EBX, 4
	MUL EBX      （←EAXにEBXの値を掛けなさい）
```

##### 除算
```
	MOV EAX, 13 
	MOV EBX, 4
	MOV EDX, 0
	DIV EBX      （←EAXをEBXの値で輪って、商をEAXに、余りをEDXに入れなさい）
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

