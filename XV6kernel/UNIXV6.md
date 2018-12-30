# XV6とは
XV6とは、マサチューセッツ工科大の院生向け教材として、UNIX V6 を ANSI の C で書き直し、x86 CPU 向けに書き直したオペレーティングシステムです。 
講義用の資料、動画とソースコード、ビルド環境( MakeFile や QEMU オプション )などの一式が、無料で公開・配布されています。
- http://pdos.csail.mit.edu/6.828/2011/xv6.html
- http://en.wikipedia.org/wiki/Xv6

ソースコードは以下のテキストを参考に読んでいくといいようです。
- http://pdos.csail.mit.edu/6.828/2011/xv6/book-rev6.pdf
- http://pdos.csail.mit.edu/6.828/2014/xv6/book-rev8.pdf(最新版)

# XV6を使ってみる(Fedora上にてXV6を動かしてみる)
```
$ cat /proc/version 
Linux version 3.3.4-5.fc17.x86_64 (mockbuild@x86-14.phx2.fedoraproject.org) (gcc version 4.7.0 20120504 (Red Hat 4.7.0-4) (GCC) ) #1 SMP Mon May 7 17:29:34 UTC 2012

$ mkdir UNIX_V6
$ cd UNIX_V6
```

続いて必要なパッケージをインストールします。
```
$ sudo yum install git qemu build-essential
git clone git://pdos.csail.mit.edu/xv6/xv6.git
```

ディレクトリに移動してMakefileを修正します。
```
$ cd xv6
$ vim Makefile 
QEMU = /usr/bin/qemu-system-x86_64   # コメントアウトしているのでそれを外すこと
```

以下のようにして起動することができます
```
ターミナルモードで起動する:      $ make qemu-nox 
ターミナルモードで起動する(GDB): $ make qemu-nox-gdb
Windowモードで起動する:          $ make qemu
Windowモードで起動する(GDB):     $ make qemu-gdb
```

XV6を抜ける場合には
```
$ Ctrl + A を押して、その後 Xを押す
```

XV6をwindowモードで起動した時のマウスの切り替えは
```
$ Ctrl + Alt
```

# 参考資料
- doxygenについては以下を参考のこと
  - http://ertl.jp/~yutaka/os/xv6-doxygen/dir_9ea4cef9241f1bffc3ca4a9e1d6c3cce.html
- このあたりのブログがXV6のソースコードリーディングについて解説しています。
  - http://peta.okechan.net/blog/xv6%E3%82%BD%E3%83%BC%E3%82%B9%E3%82%B3%E3%83%BC%E3%83%89%E3%83%AA%E3%83%BC%E3%83%87%E3%82%A3%E3%83%B3%E3%82%B0
- 「はじめてのOSコードリーディング」の著者が書いているブログのようです
  - http://d.hatena.ne.jp/takahirox/20120212/1329049014
- xv6実行環境構築参考資料
  - http://krakenbeal.blogspot.jp/2014/04/xv6-ubuntu.html


*** コマンドを追加してみる。

xv6ディレクトリ中にhello.cを追加してみる
$ hello.c
#include "types.h"
#include "stat.h"
#include "user.h"
int main(int argc, char *argv[])
{
    printf(1, "hello, world\n");
    exit();
}

Makefile の UPROGS に _hello を追加します(一部のみ抜粋)
$ vim Makefile
UPROGS=\
_cat\
_echo\
_forktest\
_grep\
_hello\
_init\
_kill\
_ln\
_ls\
_mkdir\
_rm\
_sh\
_stressfs\
_usertests\
_wc\
_zombie\

続いて、hello.cを単体でビルドする。
$ make _hello

実行してみます。
$ make qemu-nox
xv6...
cpu1: starting
cpu0: starting
init: starting sh
(xv6)$ ./hello
hello, world

###########################################################################
ソースコード解析
###########################################################################
*** main.cについて調べる

main.cのmain関数は以下のようになっている
 17 int
 18 main(void)
 19 {
 20   kinit1(end, P2V(4*1024*1024)); // (1) phys page allocator
 21   kvmalloc();      // (2) kernel page table
 22   mpinit();        // (3) collect info about this machine
 23   lapicinit();     // (4)
 24   seginit();       // (5) set up segments
 25   cprintf("\ncpu%d: starting xv6\n\n", cpu->id); // (6)
 26   picinit();       // (7) interrupt controller
 27   ioapicinit();    // (8) another interrupt controller
 28   consoleinit();   // (9) I/O devices & their interrupts
 29   uartinit();      // (10) serial port
 30   pinit();         // (11) process table
 31   tvinit();        // (12) trap vectors
 32   binit();         // (13) buffer cache
 33   fileinit();      // (14) file table
 34   iinit();         // (15) inode cache
 35   ideinit();       // (16) disk
 36   if(!ismp)        //
 37     timerinit();   // (17) uniprocessor timer
 38   startothers();   // (18) start other processors
 39   kinit2(P2V(4*1024*1024), P2V(PHYSTOP)); // (19) must come after startothers()
 40   userinit();      // (20) first user process
 41   // Finish setting up this processor in mpmain.
 42   mpmain();        // (21)
 43 }



###########################################################################
ソースコード解析 (1) kinit1(end, P2V(4*1024*1024))
###########################################################################

kinit1(end, P2V(4*1024*1024))
を追ってみる。

memlayout.hにP2Vが定義されている
  8 #define KERNBASE 0x80000000         // First kernel virtual address
    (中略)
 19 #define P2V(a) (((void *) (a)) + KERNBASE)



 19 struct {
 20   struct spinlock lock;
 21   int use_lock;
 22   struct run *freelist;
 23 } kmem;
 24 
 25 // Initialization happens in two phases.
 26 // 1. main() calls kinit1() while still using entrypgdir to place just
 27 // the pages mapped by entrypgdir on free list.
 28 // 2. main() calls kinit2() with the rest of the physical pages
 29 // after installing a full page table that maps them on all cores.
 30 void
 31 kinit1(void *vstart, void *vend)
 32 {
 33   initlock(&kmem.lock, "kmem");
 34   kmem.use_lock = 0;
 35   freerange(vstart, vend);
 36 }


initlockはspinlock.cに定義されている。
 12 void
 13 initlock(struct spinlock *lk, char *name)
 14 {
 15   lk->name = name;
 16   lk->locked = 0; 
 17   lk->cpu = 0;
 18 } 

freerangeはcalloc.cに定義されている。
  45 void
 46 freerange(void *vstart, void *vend)
 47 {
 48   char *p;
 49   p = (char*)PGROUNDUP((uint)vstart);
 50   for(; p + PGSIZE <= (char*)vend; p += PGSIZE)
 51     kfree(p);
 52 }

mmu.hに上記で使われているPGSIZEとPGGROUNDUが定義されている。
123 #define PGSIZE          4096    // bytes mapped by a page
129 #define PGROUNDUP(sz)  (((sz)+PGSIZE-1) & ~(PGSIZE-1))


この関数はしていされた領域全ての初期化を行っているようだ。

###########################################################################
ソースコード解析 (1) kvmalloc();      // (2) kernel page table
###########################################################################
ここら辺を参考にできる。
	http://peta.okechan.net/blog/archives/1273

vm.cに定義が存在する。
146 // Allocate one page table for the machine for the kernel address
147 // space for scheduler processes.
148 void
149 kvmalloc(void)
150 {
151   kpgdir = setupkvm();  // (a)
152   switchkvm();          // (b)
153 }

(a)の定義からまず見てみることとする。
127 // Set up kernel part of a page table.
128 pde_t*
129 setupkvm(void)
130 {
131   pde_t *pgdir;
132   struct kmap *k;
133 
134   if((pgdir = (pde_t*)kalloc()) == 0)
135     return 0;
136   memset(pgdir, 0, PGSIZE);
137   if (p2v(PHYSTOP) > (void*)DEVSPACE)
138     panic("PHYSTOP too high");
139   for(k = kmap; k < &kmap[NELEM(kmap)]; k++)
140     if(mappages(pgdir, k->virt, k->phys_end - k->phys_start,
141                 (uint)k->phys_start, k->perm) < 0)
142       return 0;
143   return pgdir;
144 }

mamlayout.hより定義を抜粋
  4 #define PHYSTOP 0xE000000           // Top physical memory
  5 #define DEVSPACE 0xFE000000         // Other devices are at high addresses

defs.hよりNELEM定義を抜粋
182 // number of elements in fixed-size array
183 #define NELEM(x) (sizeof(x)/sizeof((x)[0]))

vm.cよりkmap定義を抜粋
 92 // There is one page table per process, plus one that's used when
 93 // a CPU is not running any process (kpgdir). The kernel uses the
 94 // current process's page table during system calls and interrupts;
 95 // page protection bits prevent user code from using the kernel's
 96 // mappings.
 97 // 
 98 // setupkvm() and exec() set up every page table like this:
 99 //
100 //   0..KERNBASE: user memory (text+data+stack+heap), mapped to
101 //                phys memory allocated by the kernel
102 //   KERNBASE..KERNBASE+EXTMEM: mapped to 0..EXTMEM (for I/O space)
103 //   KERNBASE+EXTMEM..data: mapped to EXTMEM..V2P(data)
104 //                for the kernel's instructions and r/o data
105 //   data..KERNBASE+PHYSTOP: mapped to V2P(data)..PHYSTOP, 
106 //                                  rw data + free physical memory
107 //   0xfe000000..0: mapped direct (devices such as ioapic)
108 //
109 // The kernel allocates physical memory for its heap and for user memory
110 // between V2P(end) and the end of physical memory (PHYSTOP)
111 // (directly addressable from end..P2V(PHYSTOP)).
112 
113 // This table defines the kernel's mappings, which are present in
114 // every process's page table.
115 static struct kmap {
116   void *virt;
117   uint phys_start;
118   uint phys_end;
119   int perm;
120 } kmap[] = {
121  { (void*)KERNBASE, 0,             EXTMEM,    PTE_W}, // I/O space
122  { (void*)KERNLINK, V2P(KERNLINK), V2P(data), 0},     // kern text+rodata
123  { (void*)data,     V2P(data),     PHYSTOP,   PTE_W}, // kern data+memory
124  { (void*)DEVSPACE, DEVSPACE,      0,         PTE_W}, // more devices
125 };

vm.cよりmappagesを抜粋
 67 // Create PTEs for virtual addresses starting at va that refer to
 68 // physical addresses starting at pa. va and size might not
 69 // be page-aligned.
 70 static int
 71 mappages(pde_t *pgdir, void *va, uint size, uint pa, int perm)
 72 {   
 73   char *a, *last; 
 74   pte_t *pte;
 75                 
 76   a = (char*)PGROUNDDOWN((uint)va);
 77   last = (char*)PGROUNDDOWN(((uint)va) + size - 1);
 78   for(;;){
 79     if((pte = walkpgdir(pgdir, a, 1)) == 0)
 80       return -1;
 81     if(*pte & PTE_P)
 82       panic("remap");
 83     *pte = pa | perm | PTE_P;
 84     if(a == last)
 85       break;
 86     a += PGSIZE;
 87     pa += PGSIZE;
 88   }
 89   return 0;
 90 }

PGROUNDDOWNの定義は以下。なにをやっているんだろう!?
 130 #define PGROUNDDOWN(a) (((a)) & ~(PGSIZE-1))

mmu.hに記載
132 // Page table/directory entry flags.
133 #define PTE_P           0x001   // Present
134 #define PTE_W           0x002   // Writeable
135 #define PTE_U           0x004   // User
136 #define PTE_PWT         0x008   // Write-Through
137 #define PTE_PCD         0x010   // Cache-Disable
138 #define PTE_A           0x020   // Accessed
139 #define PTE_D           0x040   // Dirty
140 #define PTE_PS          0x080   // Page Size
141 #define PTE_MBZ         0x180   // Bits must be zero


kalloc()はkalloc.cで定義されている。
 79 // Allocate one 4096-byte page of physical memory.
 80 // Returns a pointer that the kernel can use.
 81 // Returns 0 if the memory cannot be allocated.
 82 char*
 83 kalloc(void)
 84 {
 85   struct run *r;
 86 
 87   if(kmem.use_lock)
 88     acquire(&kmem.lock);
 89   r = kmem.freelist;
 90   if(r)
 91     kmem.freelist = r->next;
 92   if(kmem.use_lock)
 93     release(&kmem.lock);
 94   return (char*)r;
 95 }


つづいて、(b)の定義を読み解く
(b)の定義は以下

155 // Switch h/w page table register to the kernel-only page table,
156 // for when no process is running.
157 void
158 switchkvm(void)
159 {
160   lcr3(v2p(kpgdir));   // switch to the kernel page table
161 }


v2pの定義はmemlayout.hに記述されている
  8 #define KERNBASE 0x80000000         // First kernel virtual address
     (省略)
 13 static inline uint v2p(void *a) { return ((uint) (a))  - KERNBASE; }

lcr3の定義はx86.hに記述されている。
ページディレクトリテーブルのアドレスをCPUにセットするためのレジスタとしてCR3レジスタが用意されています。
141 static inline void
142 lcr3(uint val)
143 {
144   asm volatile("movl %0,%%cr3" : : "r" (val));
145 }


http://homepage1.nifty.com/herumi/prog/prog10.html
を参考に読み解いてみると
入力パラメータvalが%0に入り、それをCR３に代入します。参照するものがあるときには%が２つ連続します。


