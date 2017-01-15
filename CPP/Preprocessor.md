# 概要
プリプロセッサについて
defineなどで定義されているマクロはその実装を追いにくかったりする。　

# 詳細
### 試しにlinux kernelのいくつかをヘッダファイルにかけてみる。
以下はlinux-2.6.32.65/kernel/mutex.hを試しにプリプロセッサにかけてみた例です。  
その環境のプリプロセッサを生成するためには、プリプロセッサにかける「-P」とそこで終了する「-E」を付与する。  
下記の例ではコメントも残しておきたいので「-C」を付与している。  
実行結果は*.oにプリプロセス結果がテキストとして出力されるおようになる。
```
$ cc -P -C -E  mutex.h
/*
 * Mutexes: blocking mutual exclusion locks
 *
 * started by Ingo Molnar:
 *
 *  Copyright (C) 2004, 2005, 2006 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *
 * This file contains mutex debugging related internal prototypes, for the
 * !CONFIG_DEBUG_MUTEXES case. Most of them are NOPs:
 */
static inline void mutex_set_owner(struct mutex *lock)
{
}
static inline void mutex_clear_owner(struct mutex *lock)
{
}
static inline void
debug_mutex_lock_common(struct mutex *lock, struct mutex_waiter *waiter)
{
```

続いて、include/linux/kernel.hをかけてみた。
```
$ cc -P -E include/linux/kernel.h
include/linux/kernel.h:720:2: warning: #warning Attempt to use kernel headers from user space, see http: [-Wcpp]
struct sysinfo {
 long uptime;
 unsigned long loads[3];
 unsigned long totalram;
 unsigned long freeram;
 unsigned long sharedram;
 unsigned long bufferram;
 unsigned long totalswap;
 unsigned long freeswap;
 unsigned short procs;
 unsigned short pad;
 unsigned long totalhigh;
 unsigned long freehigh;
 unsigned int mem_unit;
 char _f[20-2*sizeof(long)-sizeof(int)];
};
```

たとえば、tlbflush.hなどの場合にはIncludeを適切に設定すれば取得できる。
```
$ cc -P -E tlbflush.h -I/home/tsuyoshi/SOURCE/linux-2.6.32.65/include/ -I/home/tsuyoshi/SOURCE/linux-2.6.32.65/arch/x86/include/
```
