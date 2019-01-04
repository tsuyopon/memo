# 概要
xv6でのブート処理概要を理解することを目的とする。
Makefileで起動ターゲットを実行してから、main.c中のmain関数までどのように辿りつくのかについて明らかにする。

以下の資料がxv6ブートローダーの理解に非常に役立った。技術力の高い著者の方に感謝!
- https://qiita.com/knknkn1162/items/cb06f19e1f999bf098a1

# 詳細

### xv6起動時のMakefile処理
xv6を起動する場合には次のコマンドで起動します。
```
$ make qemu-nox
```

Makefile中だと上記qemu-noxターゲットは次のようにL222-223で定義されます。
prerequisiteにfs.imgとxv6.imgを要求します。また、QEMU環境変数は定義されていない場合にはL58-69のものを利用します。
```
 53 # If the makefile can't find QEMU, specify its path here
 54 # QEMU = qemu-system-i386
 55 
 56 # Try to infer the correct QEMU
 57 ifndef QEMU
 58 QEMU = $(shell if which qemu > /dev/null; \
 59     then echo qemu; exit; \
 60     elif which qemu-system-i386 > /dev/null; \
 61     then echo qemu-system-i386; exit; \
 62     else \
 63     qemu=/Applications/Q.app/Contents/MacOS/i386-softmmu.app/Contents/MacOS/i386-softmmu; \
 64     if test -x $$qemu; then echo $$qemu; exit; fi; fi; \
 65     echo "***" 1>&2; \
 66     echo "*** Error: Couldn't find a working QEMU executable." 1>&2; \
 67     echo "*** Is the directory containing the qemu binary in your PATH" 1>&2; \
 68     echo "*** or have you tried setting the QEMU variable in Makefile?" 1>&2; \
 69     echo "***" 1>&2; exit 1)
 70 endif
...
211 ifndef CPUS
212 CPUS := 2
213 endif
214 QEMUOPTS = -hdb fs.img xv6.img -smp $(CPUS) -m 512 $(QEMUEXTRA)    // $(QEMUEXTRA)はMakefile中に定義されていなかった
...
222 qemu-nox: fs.img xv6.img
223     $(QEMU) -nographic $(QEMUOPTS)
```

上記で要求される２つのターゲットは次のように定義されています。
fs.imgについてはファイルシステム側の処理なのでここでは深入りせず、xv6.imgターゲットの方の処理概要を覗いてみることにします。
```
 85 xv6.img: bootblock kernel fs.img
 86     dd if=/dev/zero of=xv6.img count=10000
 87     dd if=bootblock of=xv6.img conv=notrunc
 88     dd if=kernel of=xv6.img seek=1 conv=notrunc
...
177 fs.img: mkfs README $(UPROGS)
178     ./mkfs fs.img README $(UPROGS)
```

上記について見ていくと
L86: デフォルトで512バイトのブロックサイズを10000個用意して、0で書き込みxv6.imgとして出力する
L87: bootblockプログラムを読み込みxv6.imgに出力します。この際にconv=notruncを付与することでbootblockの記録が終わった513バイト以降でも元々そこにあったxv6.imgの値を記録します。
L88: seek=1を指定することで最初の1ブロック分は何も書き出しせずに、その後から書き出しを行うことを指定しています。つまり、最初の1ブロックはL87のbootblockを書き出しているので、その後にkernelプログラムで埋めています。
L178: fs.imgというファイルシステムを生成する

ではxv6.imgターゲットでrerequisiteとして定義されるbootblock、kernel、fs.imgのうち、bootblockとkernelを見ていきます。
これは、上記のddのifで指定されているbootblockとkernelプログラムを生成します。


```
 95 bootblock: bootasm.S bootmain.c
 96     $(CC) $(CFLAGS) -fno-pic -O -nostdinc -I. -c bootmain.c
 97     $(CC) $(CFLAGS) -fno-pic -nostdinc -I. -c bootasm.S
 98     $(LD) $(LDFLAGS) -N -e start -Ttext 0x7C00 -o bootblock.o bootasm.o bootmain.o
 99     $(OBJDUMP) -S bootblock.o > bootblock.asm
100     $(OBJCOPY) -S -O binary -j .text bootblock.o bootblock
101     ./sign.pl bootblock
```

kernelはL116で生成が完了します。関連するターゲットや変数も合わせて記載しています。
L117-118はプログラム解析用にkernel.asmとkernel.symが生成されているようです。
```
  1 OBJS = \
  2     bio.o\
  3     console.o\
  4     exec.o\
  5     file.o\
  6     fs.o\
  7     ide.o\
  8     ioapic.o\
  9     kalloc.o\
 10     kbd.o\
 11     lapic.o\
 12     log.o\
 13     main.o\
 14     mp.o\
 15     picirq.o\
 16     pipe.o\
 17     proc.o\
 18     spinlock.o\
 19     string.o\
 20     swtch.o\
 21     syscall.o\
 22     sysfile.o\
 23     sysproc.o\
 24     timer.o\
 25     trapasm.o\
 26     trap.o\
 27     uart.o\
 28     vectors.o\
 29     vm.o\
...
103 entryother: entryother.S
104     $(CC) $(CFLAGS) -fno-pic -nostdinc -I. -c entryother.S
105     $(LD) $(LDFLAGS) -N -e start -Ttext 0x7000 -o bootblockother.o entryother.o
106     $(OBJCOPY) -S -O binary -j .text bootblockother.o entryother
107     $(OBJDUMP) -S bootblockother.o > entryother.asm
108 
109 initcode: initcode.S
110     $(CC) $(CFLAGS) -nostdinc -I. -c initcode.S
111     $(LD) $(LDFLAGS) -N -e start -Ttext 0 -o initcode.out initcode.o
112     $(OBJCOPY) -S -O binary initcode.out initcode
113     $(OBJDUMP) -S initcode.o > initcode.asm
114 
115 kernel: $(OBJS) entry.o entryother initcode kernel.ld
116     $(LD) $(LDFLAGS) -T kernel.ld -o kernel entry.o $(OBJS) -b binary initcode entryother
117     $(OBJDUMP) -S kernel > kernel.asm
118     $(OBJDUMP) -t kernel | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > kernel.sym
```

TODO: 0x7000って何?  entryotherやinitcodeってどのような意味があるのか?

### 起動時の処理を確認する
bootasm.Sというアセンブラファイルからbootblockというプログラムが生成されます。
L96-97でbootmain.c, bootasm.Sの２つのファイルがコンパイルされます。この２つの処理の詳細については後で深追いします。
L98ではリンカプログラムを実行する際に次のオプションを指定しています。
- 「-N」: textとdataセクションを読み書き可能にする。このオプションを指定するとリンカはdataセグメントのページ位置調整を行わない。
- 「-e start」: 指定した文字列(start)をプログラムのエントリポイントを示すシンボルとして扱います。
- 「-Ttext 0x7C00」: 出力ファイルのtextセグメントに対して0x7C00を開始アドレスとする。

その後、L99で参照ようにasmファイルが生成され、L101では何やらbootblockに対してperlスクリプトでの処理が行われています。
```
 95 bootblock: bootasm.S bootmain.c
 96     $(CC) $(CFLAGS) -fno-pic -O -nostdinc -I. -c bootmain.c
 97     $(CC) $(CFLAGS) -fno-pic -nostdinc -I. -c bootasm.S
 98     $(LD) $(LDFLAGS) -N -e start -Ttext 0x7C00 -o bootblock.o bootasm.o bootmain.o
 99     $(OBJDUMP) -S bootblock.o > bootblock.asm
100 
101     ./sign.pl bootblock
```

上記L101では次のsign.plが実行されていて、行われていることとしては引数として与えられたbootblockを読み込み511バイト、512バイトに0xAA55を挿入して保存しています。
```
// sign.pl
  1 #!/usr/bin/perl
  2 
  3 # このファイルはMakefile中で実行されている
  4 
  5 open(SIG, $ARGV[0]) || die "open $ARGV[0]: $!";
  6 
  7 $n = sysread(SIG, $buf, 1000);
  8 
  9 if($n > 510){
 10   print STDERR "boot block too large: $n bytes (max 510)\n";
 11   exit 1;
 12 }
 13 
 14 print STDERR "boot block is $n bytes (max 510)\n";
 15 
 16 # 512バイトの最後のバイトがaa55だと起動ディスクとして認識されるとのこと。以下で挿入してる
 17 # (参考) http://msyksphinz.hatenablog.com/entry/2015/09/15/020000
 18 $buf .= "\0" x (510-$n);
 19 $buf .= "\x55\xAA";
 20 
 21 open(SIG, ">$ARGV[0]") || die "open >$ARGV[0]: $!";
 22 print SIG $buf;
 23 close SIG;
```

上記で生成されたバイナリがMBR(Master Boot Recorder)と呼ばれるハードドライブの最初のセクタに格納されている情報となります。

この辺りの処理は起動時のBIOSの処理を理解しておく必要があります。BIOS起動時からブートローダーの読み込みまでの流れは次の通りです。
- 1. BIOSはPOST(Power On Self Test)が行われて周辺機器が認識する。
- 2. POST後にBIOSはFDDやHDDを見つけると、そのディスクの先頭セクタ末尾(フロッピーディスクなら510バイト目に)0xAA55というMBR領域にブート用データがあること確認して、それがブートローダープログラムであることを認識します。
- 3. MBRは0x7C00にロードしてそこから処理を行う
- 4. MBRにはOSのカーネルをロードして、実行するための機械語が格納されている。

生成されたbootblockがMBRに格納される情報で、そこから0x7C00に配置されたブートローダー読み込んでいくことになります。  
0x7C00に配置された情報はMakefileでターゲット実行時に生成されるbootblock.asmを見るとbootasm.Sのstartであることがわかります。Makefileのリンカに指定された「e start -Ttext 0x7C00」が効いていることが確認できます。
```
  1 
  2 bootblock.o:     file format elf32-i386
  3 
  4 
  5 Disassembly of section .text:
  6 
  7 00007c00 <start>:
  8 # with %cs=0 %ip=7c00.
  9 
 10 .code16                       # Assemble for 16-bit mode
 11 .globl start
 12 start:
 13   cli                         # BIOS enabled interrupts; disable
 14     7c00:   fa                      cli
 15 
...
```

では、ブートローダの入り口となるbootasm.Sコードの詳細見ていくことにします。

ブートローダーの役割としては、リアルモードからプロテクトモードに切り替えなくてはならない。
リアルモードは16bitで動作し、プロテクトモードは32bitで動作する。
ほとんどのx86 OSはプロテクトモードで稼動していていて、このモードだとメモリ管理、タスク管理、保護機能、仮想メモリなどを利用するためのモードである。


まずはbootasm.Sのリアルモード部分の処理を確認していくことにする。
```
// bootasm.S
  1 #include "asm.h"
  2 #include "memlayout.h"
  3 #include "mmu.h"
  4 
  5 # Start the first CPU: switch to 32-bit protected mode, jump into C.
  6 # The BIOS loads this code from the first sector of the hard disk into
  7 # memory at physical address 0x7c00 and starts executing in real mode
  8 # with %cs=0 %ip=7c00.
  9 
 10 .code16                       # Assemble for 16-bit mode
 11 .globl start
 12 start:
 13   cli                         # BIOS enabled interrupts; disable
 14 
 15   # Zero data segment registers DS, ES, and SS.   // 0をax, ds, es, ssのレジスタにセットする
 16   xorw    %ax,%ax             # Set %ax to zero
 17   movw    %ax,%ds             # -> Data Segment
 18   movw    %ax,%es             # -> Extra Segment
 19   movw    %ax,%ss             # -> Stack Segment
 20 
 21   # Physical address line A20 is tied to zero so that the first PCs 
 22   # with 2 MB would run software that assumed 1 MB.  Undo that.
 23 seta20.1:
 24   inb     $0x64,%al               # Wait for not busy
 25   testb   $0x2,%al
 26   jnz     seta20.1
 27 
 28   movb    $0xd1,%al               # 0xd1 -> port 0x64
 29   outb    %al,$0x64
 30 
 31 seta20.2:
 32   inb     $0x64,%al               # Wait for not busy
 33   testb   $0x2,%al
 34   jnz     seta20.2
 35 
 36   movb    $0xdf,%al               # 0xdf -> port 0x60
 37   outb    %al,$0x60
 38 
 39   # Switch from real to protected mode.  Use a bootstrap GDT that makes
 40   # virtual addresses map directly to physical addresses so that the
 41   # effective memory map doesn't change during the transition.
 42   lgdt    gdtdesc
 43   movl    %cr0, %eax
 44   orl     $CR0_PE, %eax
 45   movl    %eax, %cr0
 46 
 47 //PAGEBREAK!
 48   # Complete transition to 32-bit protected mode by using long jmp
 49   # to reload %cs and %eip.  The segment descriptors are set up with no
 50   # translation, so that the mapping is still the identity mapping.
 51   ljmp    $(SEG_KCODE<<3), $start32
 52 
...
 85 gdtdesc:
 86   .word   (gdtdesc - gdt - 1)             # sizeof(gdt) - 1
 87   .long   gdt                             # address gdt
```

- L10: .code16で16bitモードでアセンブルしてくれます。.code32, .code64などもあり、L53からは32bitモードに以降するので.code32で記述しています。
- L11-12: 関数エントリの開始
- L13: CLI命令を実行することによって、BIOSからのPIC割り込みを無効化する
- L16-19: ax, ds, es, ssのレジスタを初期化して0を入れている。
- L23-37: A20を解放する
  - 現在のCPUはアドレスバスが32本までしかありませんでしたが、昔では20本しかありませんでした。つまり、昔はメモリは1MB上限であった。
  - ここで0x64, 0x60という特殊なメッセージを送ることによって、32本のアドレスバスが使えるようにします。これをA20を解放すると言っています。
- L42: LGDT命令によってL85-L87で定義されたGDT(Global Descriptor Table)を設定し、その先頭アドレスをレジスタGDTRにセットする。GDTRを使って論理アドレスから物理アドレスへの変換を行ないます。
- L43-L45: CR0_PEはmmu.hに0x00000001(=1)として定義されています。1がセットされるとプロテクトモード(32bit)へ移行します。
  - L43で現在のCR0レジスタの状態をeaxに保存しておき、L44で0x00000001との倫理和をとった値がeaxに格納される、その値をL45でCR0レジスタに設定しておく
- L51: ljmp命令で引数を２つ与えるとそれぞれCS(コードセグメント)とEIPレジスタの更新を指示している。CSレジスタはMOVで上書きすることはできないのであえてLJMP命令を利用する。
  - TODO: "SEG_KCODE<<3"によって何を意味している?
- L85-87: TODO: 宣言がよくわからないので確認する?


では、引き続きbootasm.SのL52以降の後半処理を眺めることによって、32bitのプロテクトモードの処理を見ていくことにします。
```
// bootasm.S
 53 .code32  # Tell assembler to generate 32-bit code now.
 54 start32:
 55   # Set up the protected-mode data segment registers
 56   movw    $(SEG_KDATA<<3), %ax    # Our data segment selector
 57   movw    %ax, %ds                # -> DS: Data Segment
 58   movw    %ax, %es                # -> ES: Extra Segment
 59   movw    %ax, %ss                # -> SS: Stack Segment
 60   movw    $0, %ax                 # Zero segments not ready for use
 61   movw    %ax, %fs                # -> FS
 62   movw    %ax, %gs                # -> GS
 63 
 64   # Set up the stack pointer and call into C.
 65   movl    $start, %esp
 66   call    bootmain
 67 
 68   # If bootmain returns (it shouldn't), trigger a Bochs
 69   # breakpoint if running under Bochs, then loop.
 70   movw    $0x8a00, %ax            # 0x8a00 -> port 0x8a00
 71   movw    %ax, %dx
 72   outw    %ax, %dx
 73   movw    $0x8ae0, %ax            # 0x8ae0 -> port 0x8a00
 74   outw    %ax, %dx
 75 spin:
 76   jmp     spin
 77 
 78 # Bootstrap GDT
 79 .p2align 2                                # force 4 byte alignment
 80 gdt:
 81   SEG_NULLASM                             # null seg
 82   SEG_ASM(STA_X|STA_R, 0x0, 0xffffffff)   # code seg
 83   SEG_ASM(STA_W, 0x0, 0xffffffff)         # data seg
 84 
 85 gdtdesc:
 86   .word   (gdtdesc - gdt - 1)             # sizeof(gdt) - 1
 87   .long   gdt                             # address gdt
```
- L53: 32bitモードでアセンブルしてくれます。
- L56-62: プロテクトモードで利用可能なデータセグメントのレジスタを初期化しています。
  - CSレジスタに入れていた値をDS, ES, SSレジスタに格納します。
  - FS, GSレジスタには0を格納します。
- L65: $startはMakefileでのリンカでの指定でstartをテキストセグメント(0x7C00)をeipレジスタの値として指定しています。
- L66 bootmain関数を呼び出す。これはbootmain.cで呼び出されるC言語の関数です。
- L70-74: bootmain関数が戻り値を返してきた場合の処理が記載されているようですが、今回はよくわからなかったので気にしないでおきます。


### bootasm.Sから呼び出されるbootmain関数の処理を確認する。
起動時に実行されるCファイルの関数は次のbootmainです。
このプログラムで実行することによってHDDからメモリにロードが行われて、その後kernelプログラムのエントリポイントであるentry.Sに遷移します。
```
// bootmain.c
 17 void
 18 bootmain(void)
 19 {
 20   struct elfhdr *elf;
 21   struct proghdr *ph, *eph;
 22   void (*entry)(void);
 23   uchar* pa;
 24 
 25   elf = (struct elfhdr*)0x10000;  // scratch space
 26 
 27   // Read 1st page off disk
 28   readseg((uchar*)elf, 4096, 0);
 29 
 30   // Is this an ELF executable?
 31   if(elf->magic != ELF_MAGIC)
 32     return;  // let bootasm.S handle error
 33 
 34   // Load each program segment (ignores ph flags).
 35   ph = (struct proghdr*)((uchar*)elf + elf->phoff);
 36   eph = ph + elf->phnum;
 37   for(; ph < eph; ph++){
 38     pa = (uchar*)ph->paddr;
 39     readseg(pa, ph->filesz, ph->off);
 40     if(ph->memsz > ph->filesz)
 41       stosb(pa + ph->filesz, 0, ph->memsz - ph->filesz);
 42   }
 43 
 44   // Call the entry point from the ELF header.
 45   // Does not return!
 46   entry = (void(*)(void))(elf->entry);
 47   entry();
 48 }
```

- L25: elfは0x10000番地と設定する。(調べてみた感じだと、この値に特に理由があるわけではなさそう!?)
- L28: entry.Sの実行バイナリ(ELF)の先頭部分をDiskから0x10000番地~0x11000番地のメモリにロードする (補足: 4096(=0x1000))
- L31-32: ELF先頭のマジックワードとして"\x7FELF"が含まれていることをチェックする。これに合致しなければエラーとする。
- L35: ELFヘッダからプログラムヘッダへのオフセット(phoff)を取得して、その構造体へのポインタを取得する。
- L36: phnumではプログラムヘッダの個数がわかるので、+はポインタ演算として計算していることに注意する
- L37: プログラムヘッダの個数分だけループします。
- L38-39: プログラムヘッダのアドレスを取得して、読み込みを行います。
- L40-41: ph->memszがph->fileszよりも大きい場合、.bss領域を0で埋めている。
  - fileszはファイルイメージの大きさを表し、memszはメモリ上に展開された時の大きさを表す。
  - 参考1: 4.2.5 BSSの大きさを参照のこと http://caspar.hazymoon.jp/OpenBSD/lib/libsa/kernel_elf.html
    - セグメントによっては、ファイルイメージサイズを表す変数p_fileszとメモリ上のイメージサイズを表す変数p_memsが一致しないものがある。この差は何を意味するかというとBSSの領域となる。BSSは初期値を持たない変数の集まりなのでファイル上に領域を取っていてもDisk領域の無駄になるだけであり、論理的な差分として持っていた方が効率的になる。
  - 参考2: https://stackoverflow.com/questions/27958743/difference-between-p-filesz-and-p-memsz-of-elf32-phdr/31011428#31011428
    - As per the ELF specification, in the case where p_memsz is greater than p_filesz, the extra bytes following the segment's initialized area are defined to hold the value 0.
- L46: elfヘッダ中のentryから実行すべきエントリポイントのアドレスを取得する。 (void(*)(void))は別途xv6studyのレポジトリに説明を記載しているが、"void f(void)"に対する関数ポインタの型を表している。
- L47: 上記で取得した値はカーネルのエントリポイント(entry.SのELFバイナリ)へと遷移します。なぜentry.Sのバイナリを指しているのかについてはこれから説明します。

1つ謎があります。なぜ、上記のL47ではentry関数ポインタはentry.SのELFバイナリとなっているんでしょうか?
上記でentry.Sが呼ばれているんでしょうか。ELFのデフォルトエントリポイントは「_start」と決まっていて、entry.Sにこれが定義されています。
では、entry.Sについて引き続き追いかけていくことにします。

# entry.Sからmainまでの流れ
entry.Sの中身を確認します。entry.Sの先頭コメントを見るとGNU Grubのようなマルチブートローダーであると記載されています。
```
// entry.S
  1 # Multiboot header, for multiboot boot loaders like GNU Grub.
  2 # http://www.gnu.org/software/grub/manual/multiboot/multiboot.html
  3 #
  4 # Using GRUB 2, you can boot xv6 from a file stored in a
  5 # Linux file system by copying kernel or kernelmemfs to /boot
  6 # and then adding this menu entry:
  7 #
  8 # menuentry "xv6" {
  9 #   insmod ext2
 10 #   set root='(hd0,msdos1)'
 11 #   set kernel='/boot/kernel'
 12 #   echo "Loading ${kernel}..."
 13 #   multiboot ${kernel} ${kernel}
 14 #   boot
 15 # }
 16 
 17 #include "asm.h"
 18 #include "memlayout.h"
 19 #include "mmu.h"
 20 #include "param.h"
 21 
 22 # Multiboot header.  Data to direct multiboot loader.
 23 .p2align 2
 24 .text
 25 .globl multiboot_header
 26 multiboot_header:
 27   #define magic 0x1badb002
 28   #define flags 0
 29   .long magic
 30   .long flags
 31   .long (-magic-flags)
 32 
 33 # By convention, the _start symbol specifies the ELF entry point.
 34 # Since we haven't set up virtual memory yet, our entry point is
 35 # the physical address of 'entry'.
 36 .globl _start
 37 _start = V2P_WO(entry)
 38 
 39 # Entering xv6 on boot processor, with paging off.
 40 .globl entry
 41 entry:
 42   # Turn on page size extension for 4Mbyte pages
 43   movl    %cr4, %eax
 44   orl     $(CR4_PSE), %eax
 45   movl    %eax, %cr4
 46   # Set page directory
 47   movl    $(V2P_WO(entrypgdir)), %eax
 48   movl    %eax, %cr3
 49   # Turn on paging.
 50   movl    %cr0, %eax
 51   orl     $(CR0_PG|CR0_WP), %eax
 52   movl    %eax, %cr0
 53 
 54   # Set up the stack pointer.
 55   movl $(stack + KSTACKSIZE), %esp
 56 
 57   # Jump to main(), and switch to executing at
 58   # high addresses. The indirect call is needed because
 59   # the assembler produces a PC-relative instruction
 60   # for a direct jump.
 61   mov $main, %eax
 62   jmp *%eax
 63 
 64 .comm stack, KSTACKSIZE
```

L37で利用されているV2P_WOの定義も以下に記載しておきます。
```
// memlayout.h
  8 #define KERNBASE 0x80000000         // First kernel virtual address
...
 21 #define V2P_WO(x) ((x) - KERNBASE)    // same as V2P, but without casts
```

では、entry.Sのコードを見ていきます。
- L23-31: entry.Sのコメント先頭にも記述されているがGrubの仕様である。以下の資料に記載されているマジックナンバー0x1badb002が8192byte以内に存在している必要がある。参考資料などにも記載されているがL29のmagicは固定で0x1badb002、L30のflagsはOSが必要な機能とブートローダーが必要な情報をヘッダに格納しているかどうかを示すフラグ(詳細は資料を参考のこと)、L31はchecksumでmagicフィールドとflagsフィールドの値の合計と足すと0になる値を指定する必要があります。
  - Grub公式資料
    - https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Header-magic-fields
  - 参考資料
    - http://softwaretechnique.jp/OS_Development/Grub/grub03.html
- L36-37: ELFのデフォルトエントリポイントである"_start"です。
  - L37のV2P_WO(entry)はentryの仮想アドレスからKERNBASEを差し引くことで物理アドレスを取得しています(book-rev10.pdfに記載)
  - これにより無理やり0x0000_0000を設定することでページングハードウェアがまだONになっていないにもかかわらず、entryを読み込んで実行されるらしい。
    - 参考: http://msyksphinz.hatenablog.com/entry/2015/07/02/020000
- L40-41: entryエントリポイントを定義します。
- L43-45: 既存のCR4の設定を取得して、その設定にPSEフラグを立てて、CR4レジスタに再設定する。PSEフラグを立てるというのは、Paging Size Extension(ページング機能)がここで機能を利用できるとCPUに設定しています。紛らわしいのですが、L50-52のCR0のPGフラグをonにすることでページングが有効になります(つまり、両方設定されてはじめてページング機能が有効になると思われます)
  - CR4はコントロールレジスタで各種拡張機能を制御するフラグが存在するレジスタ: 参考 http://www.wiki.os-project.jp/?x86%2FRegister#kdc81e7f
- L47-48: ページングディレクトリのベースアドレスをentrypgdirとして設定します。CR3レジスタでその設定は行います。
  - entrypgdirはmain.cにその定義がされています。
```
// main.c
190 // Boot page table used in entry.S and entryother.S.
191 // Page directories (and page tables), must start on a page boundary,
192 // hence the "__aligned__" attribute.  
193 // Use PTE_PS in page directory entry to enable 4Mbyte pages.
194 __attribute__((__aligned__(PGSIZE)))
195 pde_t entrypgdir[NPDENTRIES] = {                            // NPDENTRIES = 1024の固定値です
196   // Map VA's [0, 4MB) to PA's [0, 4MB)
197   [0] = (0) | PTE_P | PTE_W | PTE_PS,                       // 0x0-0x400000 --> 0x00000に変換
198   // Map VA's [KERNBASE, KERNBASE+4MB) to PA's [0, 4MB)
199   [KERNBASE>>PDXSHIFT] = (0) | PTE_P | PTE_W | PTE_PS,      // 0x8000_0000-0x8040_0000 を 0x0000000に変換
200 };
```

- L50-52: 既存のCR0設定を取得して、その設定にPGフラグ(Paging)とWPフラグ(Write Protect)フラグを立てて、CR0レジスタに再設定しています。
  - WPフラグについては次のURLを参考のこと:  https://stackoverflow.com/questions/15275059/whats-the-purpose-of-x86-cr0-wp-bit
- L55: 
- L61-62: main関数へのポインタ参照を%eaxに格納して、jmp *%eaxでmain関数へのポインタが指し示すアドレスへとジャンプします。
  - *%eaxについては次のURLを参考のこと
    - https://www.quora.com/Assembly-Language-What-does-call-*-eax-mean
    - https://stackoverflow.com/questions/21324087/what-c-code-would-compile-to-something-like-call-eax
- L64: グローバル変数は.commに記載される。stackとKSTACKSIZEはグローバル変数として扱う


# まとめ
main到達まで非常に長い道のりでしたが、どのようにxv6プログラムがmainまで到達するのかの処理について追いかけてきました。

Makefileでqemu-noxターゲットを実行すると、カーネルxv6.imgとファイルシステムfs.imgを作成していて、それをqemuで実行していた。
今回はxv6.imgの方の作成について深追いしてきた。

xv6.imgは次のような流れで作成されていた
- ddから10000ブロックを/dev/zeroで書き込む
- ddで上記で生成したxv6.imgに、MBRとなるbootblockプログラム分を先頭から1ブロック(512byteまで)配置する。bootblockは512byteからなるプログラムであり、511-512byteの2byteはperlプログラムからブートプログラムの署名(0xAA55)を入れている。
- ddで上記で生成したxv6.imgに、その他のカーネルプログラムを先頭から1ブロック後方から配置する。

起動時の処理の流れとしては次のような感じになっている。
- bootasm.S:  MBRとしてカーネルの先頭に記述されているプログラムであり、Makefileのリンカの指定によってstartエントリポイントはメモリの0x7C00に読み込みようになっている。16bitモード、32bitモードの初期化処理を行い、最終的にはespレジスタを0x7C00に設定する。
- bootmain.c: bootasm.Sから呼ばれます。ELFを読み込む処理をして、ELFデフォルトのエントリポイントとなる_startを呼び出し次のentry.Sを呼び出します。
- entry.S:    ELFのエントリポイントである「_start」が定義されているのでこのファイルが呼ばれます。 CR4でページング拡張機能を有効にし、CR3でページディレクトリを設定し、CR0でページングの有効開始をその時点から指定して、次のmain関数へと遷移します。
- main.c:     起動時の処理が書かれたプログラムです。main関数が定義されています。

上記のファイルについてのロジックについてまとめます。
bootasm.Sは起動ディスクのMBR (Master Boot Record)領域に記録されたプログラムであり、PC起動後にBIOSはMBR領域のデータをメモリ上(0x7C00の位置)にロードし、そのプログラムに制御を移します。
生成されるバイナリはMBRとして認識させるための署名として0xAA55を511,512バイト目に付与しています。

16bitモードで次の処理を行っていました。
- 割り込みの禁止
- 各種レジスタの初期化
- A20の解放
- LGDT命令によってGDTを設定することで、GDTRレジストリを有効化
- プロテクトモードへの移行(CR0レジスタのPEフラグを操作)
- ljmpで32bitモードのバイナリ命令に移行

32bitモードで次の処理を行っていました。
- プロテクトモードから利用できるデータセグメントの初期化
- espレジスタに0x7C00を設定して、bootmainを呼び出す

bootmain.cは、次に実行するELFバイナリ(entry.S)を0x10000番地から0x11000番地に1ブロックサイズ分ロードして、ELFバイナリのチェックなどを行ないます。
そして、内部的に組み込まれているELF起動時のエントリポイント_startへと遷移させます。

entry.Sは、ELF起動時のエントリポイントである_startが定義されていて、
- CR4でPSEフラグをセットしてPaging Size Extension機能を有効にします。
- CR3でページディレクトリエントリのベースアドレスentrypgdirを設定します。
- CR0でPGフラグ(Paging)とWPフラグ(Write Protect)フラグを立てます。ここではじめてページングが有効となるようです。
- main関数へとjmpします。 

以上により、起動時からmain関数までのおおまかな流れを辿ってきました。

# 参考URL
- 神資料: xv6実装の詳解(boot処理編: segmentationとpagingを中心に)
  - 全体像がわかりやすく記載されている。コードを追う際のとっかかりに非常に良い資料。
  - https://qiita.com/knknkn1162/items/cb06f19e1f999bf098a1
- xv6のブートプロセスめも 32bit-modeになるまで
  - https://qiita.com/lastcat_/items/72d792c50f051c6dbbf8
- wikipedia: マスターブートレコード
  - 0xAA55のブートシグニチャについて記述されています。
  - https://ja.wikipedia.org/wiki/%E3%83%9E%E3%82%B9%E3%82%BF%E3%83%BC%E3%83%96%E3%83%BC%E3%83%88%E3%83%AC%E3%82%B3%E3%83%BC%E3%83%89
- A20について
  - http://caspar.hazymoon.jp/OpenBSD/annex/gate_a20.html
- A20解放について
  - http://softwaretechnique.jp/OS_Development/kernel_loader3.html
- CR0レジスタについて
  - プロテクトモードに移行する際にセットされるレジスタ
  - http://www.wiki.os-project.jp/?x86%2FRegister#e7cea17d

# 要確認メモ
- TODO解消する
- TODO: 0x7000って何?  entryotherやinitcodeってどのような意味があるのか?
- TODO: jmpとcallの違いを確認しておく。
- entrypgdirを設定しているのはいいんだっけ?
- initcode.Sの役割
- mkfsで生成されるfs.imgとの関係性
