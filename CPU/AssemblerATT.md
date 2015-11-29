ATT記法のアセンブラ
====

# 概要
gdbなどでもデバッグに困らないようにATT記法のアセンブラについてまとめてみる。


# 関数の引数の扱いを眺めてみる。

以下のような関数呼び出しを行なうプログラムを準備します。
このプログラムのポイントは関数の引数がどのようにしてレジスタを扱うかという点です。

```
$ nl testfunc.c 
     1	#include<stdio.h>
       
     2	int addfunc(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9){
     3		return arg1 + arg2 + arg3 + arg4 + arg5 + arg6 + arg7 + arg8 + arg9;
     4	}
       
     5	int main(void){
     6		int sum;
     7		sum = addfunc(1, 2, 3, 4, 5, 6, 7, 8, 9);
     8		printf("sum=%d\n", sum);
     9	}
```

アセンブラを出力します。
```
$ gcc -S testfunc.c
$ nl testfunc.s a
     1		.file	"testfunc.c"
     2		.text
     3		.globl	addfunc
     4		.type	addfunc, @function
     5	addfunc:
     6	.LFB0:
     7		.cfi_startproc
     8		pushq	%rbp
     9		.cfi_def_cfa_offset 16
    10		.cfi_offset 6, -16
    11		movq	%rsp, %rbp
    12		.cfi_def_cfa_register 6
    13		movl	%edi, -4(%rbp)
    14		movl	%esi, -8(%rbp)
    15		movl	%edx, -12(%rbp)
    16		movl	%ecx, -16(%rbp)
    17		movl	%r8d, -20(%rbp)
    18		movl	%r9d, -24(%rbp)
    19		movl	-8(%rbp), %eax
    20		movl	-4(%rbp), %edx
    21		addl	%eax, %edx
    22		movl	-12(%rbp), %eax
    23		addl	%eax, %edx
    24		movl	-16(%rbp), %eax
    25		addl	%eax, %edx
    26		movl	-20(%rbp), %eax
    27		addl	%eax, %edx
    28		movl	-24(%rbp), %eax
    29		addl	%eax, %edx
    30		movl	16(%rbp), %eax
    31		addl	%eax, %edx
    32		movl	24(%rbp), %eax
    33		addl	%eax, %edx
    34		movl	32(%rbp), %eax
    35		addl	%edx, %eax
    36		popq	%rbp
    37		.cfi_def_cfa 7, 8
    38		ret
    39		.cfi_endproc
    40	.LFE0:
    41		.size	addfunc, .-addfunc
    42		.section	.rodata
    43	.LC0:
    44		.string	"sum=%d\n"
    45		.text
    46		.globl	main
    47		.type	main, @function
    48	main:
    49	.LFB1:
    50		.cfi_startproc
    51		pushq	%rbp
    52		.cfi_def_cfa_offset 16
    53		.cfi_offset 6, -16
    54		movq	%rsp, %rbp
    55		.cfi_def_cfa_register 6
    56		subq	$48, %rsp
    57		movl	$9, 16(%rsp)
    58		movl	$8, 8(%rsp)
    59		movl	$7, (%rsp)
    60		movl	$6, %r9d
    61		movl	$5, %r8d
    62		movl	$4, %ecx
    63		movl	$3, %edx
    64		movl	$2, %esi
    65		movl	$1, %edi
    66		call	addfunc
    67		movl	%eax, -4(%rbp)
    68		movl	-4(%rbp), %eax
    69		movl	%eax, %esi
    70		movl	$.LC0, %edi
    71		movl	$0, %eax
    72		call	printf
    73		leave
    74		.cfi_def_cfa 7, 8
    75		ret
    76		.cfi_endproc
    77	.LFE1:
    78		.size	main, .-main
    79		.ident	"GCC: (GNU) 4.7.2 20120921 (Red Hat 4.7.2-2)"
    80		.section	.note.GNU-stack,"",@progbits
```

まずは.mainに着目します。 57行目〜65行目では関数addfuncを呼ぶためにレジスタに値をセットしています。  
着目すべきは引数情報は以下のように格納されるということです。
- 引数1つめは$edi
- 引数2つめは$esi
- 引数3つめは$edx
- 引数4つめは$ecx
- 引数5つめは$r8d
- 引数6つめは$r9d
- 引数7つめは$rsp(スタックポインタ)
- 引数8つめは$rsp+8バイトした位置にあるポインタ
- 引数9つめは$rsp+16バイトした位置にあるポインタ

66行目で関数addfuncを呼び出しています。
```
	call
		次の命令のアドレスをスタックに push し、ラベル <label> へ分岐する。 
	leave
		%ebp の値を %esp にコピーし、スタックから pop した値を %ebp に保存する。
	ret
		次の命令のアドレスをスタックから pop し、そこへ分岐する。 Return 命令。 
```

cfi関連は[https://sourceware.org/binutils/docs/as/CFI-directives.html]で定義されているように
- .cfi_def_cfa_register
 - CFAコンピューティングのための規則を修正する。今から
- .cfi_def_cfa
 - CFAコンピューティングのための規則を定義している。第１引数にregister、第２引数にoffsetが入る。
- .cfi_endproc
 - 関数の終わりに定義される

訳してもよくわからないものもあったので検索してみたらstack overflawに回答らしきものがあった。
- http://stackoverflow.com/questions/2529185/what-are-cfi-directives-in-gnu-assembler-gas-used-for

とりあえず、以下のようにコンパイルすればcfi関連のディレクティブは表示されなくなります。今後はこちらを使っていきます
```
  $ gcc -S -fno-asynchronous-unwind-tables  xxxxx.c
```

スタックの概念については以下のURLが非常にわかりやすく説明しています。
- [http://d.hatena.ne.jp/yz2cm/20130526/1369591965]




