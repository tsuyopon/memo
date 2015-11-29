Intel表記とATT表記の違いについて
====

# 概要
NASMとGASの大きな違いは構文です。
- GASはATT構文(AT&T構文とも呼ぶ)を使います。
- NASMはTASMやMASMなど大多数のアセンブラがサポートするIntel構文を使います。(GASでも最近ではIntel構文を使える仕組みとして.intel_syntaxというものを用意しているようです。)
 - TASMはTurbo Assemblerで、ボーランドが開発したx86アセンブラパッケージです。
 - MASMはThe Microsoft Assemblerで、TASMとMASMは開発会社が違いますが大きな違いはないとのことです。


# 詳細
特に押さえておくべきルールは以下の6つです。
この他にも様々なルールがありますが、ここでは触りとして以下の６つを代表例として取り上げます。

ルール1: ATT構文では即値オペランドの前に $ が付きますが、Intel 構文では付きません。
```
   Intel: push 3
   ATT:   pushl $3
```

ルール2: ATT構文ではレジスター・オペランドの前に % が付きますが、Intel 構文では付きません。
```
   Intel: rbp
   ATT:   %rbp
```

ルール3: ATT構文とIntel構文でメモリー・オペランドのサイズ指定方法が異なります。
- ATT 構文では、メモリー・オペランドのサイズはオペコード名の最後の文字で決まります。オペコードの接尾辞の b、w、l は、byte (8 ビット)、word (16 ビット)、そして long (32 ビット) のメモリー参照を指定します。
- Intel 構文はこれを、(オペコード自体ではなく) メモリー・オペランドの前に byte ptr と word ptr、dword ptr を付けることで実現します。従って次のようになります。

ルール4: ATT構文と Intel 構文ではソース・オペランドとデスティネーション・オペランドの順序が逆です
```
   Intel: mov eax, 4
   ATT:  movl $4, %eax
```


ルール5: ATT構文の場合にメモリオペランドのサイズはオペコード名の接尾辞で決定します。b(byte:8bit),w(word:16bit),l(long:32bit)のメモリーを参照します。Intel構文の場合にはメモリオペランドの前にbyte ptr, word ptr, dword ptrと付加することで実現します。
```
    Intel: mov al, byte ptr foo
    ATT: movb foo, %al
```


ルール6: 即値形式のロング・ジャンプとロング・コール、far リターン命令に違いがあります

即値形式のロング・ジャンプとロング・コール
```
   Intel: call/jmp far section:offset
   ATT:   lcall/ljmp $section, $offset
```

farリターン
```
   Intel: ret far stack-adjust 
   ATT:   lret $stack-adjust
```


# 参考URL
- [http://www.ibm.com/developerworks/jp/linux/library/l-gas-nasm.html]

