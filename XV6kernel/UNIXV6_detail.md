UNIXV6.md$B$+$iGI@8$7$?;qNA!#8E$$$N$G@0M}$,I,MW$+$b$7$l$J$$!#!#!#(B


# $B%=!<%9%3!<%I2r@O(B
main.c$B$N(Bmain$B4X?t$O0J2<$N$h$&$K$J$C$F$$$k(B
```
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
```


# $B%=!<%9%3!<%I2r@O(B (1) kinit1(end, P2V(4*1024*1024))
```
kinit1(end, P2V(4*1024*1024))
```
$B$rDI$C$F$_$k!#(B

memlayout.h$B$K(BP2V$B$,Dj5A$5$l$F$$$k(B
```
  8 #define KERNBASE 0x80000000         // First kernel virtual address
    ($BCfN,(B)
 19 #define P2V(a) (((void *) (a)) + KERNBASE)
```

```
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
```


initlock$B$O(Bspinlock.c$B$KDj5A$5$l$F$$$k!#(B
```
 12 void
 13 initlock(struct spinlock *lk, char *name)
 14 {
 15   lk->name = name;
 16   lk->locked = 0; 
 17   lk->cpu = 0;
 18 } 
```

freerange$B$O(Bcalloc.c$B$KDj5A$5$l$F$$$k!#(B
```
 45 void
 46 freerange(void *vstart, void *vend)
 47 {
 48   char *p;
 49   p = (char*)PGROUNDUP((uint)vstart);
 50   for(; p + PGSIZE <= (char*)vend; p += PGSIZE)
 51     kfree(p);
 52 }
```

mmu.h$B$K>e5-$G;H$o$l$F$$$k(BPGSIZE$B$H(BPGGROUNDU$B$,Dj5A$5$l$F$$$k!#(B
```
123 #define PGSIZE          4096    // bytes mapped by a page
129 #define PGROUNDUP(sz)  (((sz)+PGSIZE-1) & ~(PGSIZE-1))
```

$B$3$N4X?t$O$7$F$$$5$l$?NN0hA4$F$N=i4|2=$r9T$C$F$$$k$h$&$@!#(B

# $B%=!<%9%3!<%I2r@O(B (1) kvmalloc();      // (2) kernel page table
$B$3$3$iJU$r;29M$K$G$-$k!#(B
- http://peta.okechan.net/blog/archives/1273

vm.c$B$KDj5A$,B8:_$9$k!#(B
```
146 // Allocate one page table for the machine for the kernel address
147 // space for scheduler processes.
148 void
149 kvmalloc(void)
150 {
151   kpgdir = setupkvm();  // (a)
152   switchkvm();          // (b)
153 }
```

(a)$B$NDj5A$+$i$^$:8+$F$_$k$3$H$H$9$k!#(B
```
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
```

mamlayout.h$B$h$jDj5A$rH4?h(B
```
4 #define PHYSTOP 0xE000000           // Top physical memory
5 #define DEVSPACE 0xFE000000         // Other devices are at high addresses
```

defs.h$B$h$j(BNELEM$BDj5A$rH4?h(B
```
182 // number of elements in fixed-size array
183 #define NELEM(x) (sizeof(x)/sizeof((x)[0]))
```

vm.c$B$h$j(Bkmap$BDj5A$rH4?h(B
```
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
```

vm.c$B$h$j(Bmappages$B$rH4?h(B
```
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
```

PGROUNDDOWN$B$NDj5A$O0J2<!#$J$K$r$d$C$F$$$k$s$@$m$&(B!?
```
 130 #define PGROUNDDOWN(a) (((a)) & ~(PGSIZE-1))
```

mmu.h$B$K5-:\(B
```
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
```


kalloc()$B$O(Bkalloc.c$B$GDj5A$5$l$F$$$k!#(B
```
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
```


$B$D$E$$$F!"(B(b)$B$NDj5A$rFI$_2r$/(B
(b)$B$NDj5A$O0J2<(B
```
155 // Switch h/w page table register to the kernel-only page table,
156 // for when no process is running.
157 void
158 switchkvm(void)
159 {
160   lcr3(v2p(kpgdir));   // switch to the kernel page table
161 }
```


v2p$B$NDj5A$O(Bmemlayout.h$B$K5-=R$5$l$F$$$k(B
```
  8 #define KERNBASE 0x80000000         // First kernel virtual address
     ($B>JN,(B)
 13 static inline uint v2p(void *a) { return ((uint) (a))  - KERNBASE; }
```

lcr3$B$NDj5A$O(Bx86.h$B$K5-=R$5$l$F$$$k!#(B
$B%Z!<%8%G%#%l%/%H%j%F!<%V%k$N%"%I%l%9$r(BCPU$B$K%;%C%H$9$k$?$a$N%l%8%9%?$H$7$F(BCR3$B%l%8%9%?$,MQ0U$5$l$F$$$^$9!#(B
```
141 static inline void
142 lcr3(uint val)
143 {
144   asm volatile("movl %0,%%cr3" : : "r" (val));
145 }
```


- http://homepage1.nifty.com/herumi/prog/prog10.html
$B$r;29M$KFI$_2r$$$F$_$k$H(B
$BF~NO%Q%i%a!<%?(Bval$B$,(B%0$B$KF~$j!"$=$l$r(BCR$B#3$KBeF~$7$^$9!#;2>H$9$k$b$N$,$"$k$H$-$K$O(B%$B$,#2$DO"B3$7$^$9!#(B


