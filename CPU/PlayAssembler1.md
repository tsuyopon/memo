アセンブラで遊ぶ
======

# 概要
もっとも単純なサンプルでアセンブラを体験します。
ATT形式で基本的には進めます。

# 詳細

以下のように何も行わないソースコードのアセンブリ出力を見てみましょう。
```
$ cat none.c
include<stdio.h>

int main(void){
	return 0;
}
```

以下のオプションでコンパイルします。  
-Sはアセンブラを表示します。-O0はコンパイル最適化をしません。
```
$ gcc -S -O0 none.c
```

以下の出力を得ることができます。
```
$ nl none.s 
     1		.file	"none.c"
     2		.text
     3		.globl	main
     4		.type	main, @function
     5	main:
     6	.LFB0:
     7		.cfi_startproc
     8		pushq	%rbp
     9		.cfi_def_cfa_offset 16
    10		.cfi_offset 6, -16
    11		movq	%rsp, %rbp
    12		.cfi_def_cfa_register 6
    13		movl	$0, %eax
    14		popq	%rbp
    15		.cfi_def_cfa 7, 8
    16		ret
    17		.cfi_endproc
    18	.LFE0:
    19		.size	main, .-main
    20		.ident	"GCC: (GNU) 4.7.2 20120921 (Red Hat 4.7.2-2)"
    21		.section	.note.GNU-stack,"",@progbits
```


cfiから始まるディレクティブは[http://sourceware.org/binutils/docs/as/CFI-directives.html]で定義されているように
- .cfi_def_cfa_register
 - CFAコンピューティングのための規則を修正する。今から
- .cfi_def_cfa
 - CFAコンピューティングのための規則を定義している。第１引数にregister、第２引数にoffsetが入る。
- .cfi_endproc
 - 関数の終わりに定義される

訳してもよくわからないものもあったので検索してみたらstack overflawに回答らしきものがあった。
- http://stackoverflow.com/questions/2529185/what-are-cfi-directives-in-gnu-assembler-gas-used-for

とりあえず、以下のようにコンパイルすればcfi関連のディレクティブは表示されなくなりましたので、とりあえずは学習用にこちらのオプションを付加して進めていきたいと思います。
```
  $ gcc -S -O0 -fno-asynchronous-unwind-tables none.c
```

以下の出力になりました。
```
$ cat none.s
     1		.file	"none.c"
     2		.text
     3		.globl	main
     4		.type	main, @function
     5	main:
     6		pushq	%rbp
     7		movq	%rsp, %rbp
     8		movl	$0, %eax
     9		popq	%rbp
    10		ret
    11		.size	main, .-main
    12		.ident	"GCC: (GNU) 4.7.2 20120921 (Red Hat 4.7.2-2)"
    13		.section	.note.GNU-stack,"",@progbits
```

http://d.hatena.ne.jp/yz2cm/20130526/1369591965
