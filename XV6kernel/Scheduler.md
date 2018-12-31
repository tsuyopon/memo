# 概要
XV6におけるスケジューラについてまとめています。
どのようにカーネル空間とアプリケーション空間のスケジューリング処理を切り替えているのかを確認する

# 詳細

### 起動時に呼ばれるスケジューラ処理
main -> mpmain -> scheduler()といった流れで起動時からの処理が呼ばれている。
L272-L297ではこのスケジューラ処理がループしていることが確認できる。

```
259 //PAGEBREAK: 42
260 // Per-CPU process scheduler.
261 // Each CPU calls scheduler() after setting itself up.
262 // Scheduler never returns.  It loops, doing:
263 //  - choose a process to run
264 //  - swtch to start running that process
265 //  - eventually that process transfers control
266 //      via swtch back to the scheduler.
267 void
268 scheduler(void)           
269 {
270   struct proc *p;
271 
272   for(;;){
273     // Enable interrupts on this processor.
274     sti();
275 
276     // Loop over process table looking for process to run.
277     acquire(&ptable.lock);
278     for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
279       if(p->state != RUNNABLE)
280         continue;
281 
282       // Switch to chosen process.  It is the process's job
283       // to release ptable.lock and then reacquire it
284       // before jumping back to us.
285       proc = p;
286       switchuvm(p);
287       p->state = RUNNING;
288       swtch(&cpu->scheduler, proc->context);  // swtch.S 内にこの関数swtchが定義されている
289       switchkvm();
290       
291       // Process is done running for now.
292       // It should have changed its p->state before coming back.
293       proc = 0;
294     }
295     release(&ptable.lock);
296 
297   }
298 }
```

最大64回(NPROC)のプロセス切り替えを行なっている。(TODO: このロック解放には何の意味があるのか?)
L279-L289までの各種プロセス実行では次の処理が行われる
- RUNNNABLEのチェック
- プロセス情報の取得 (TODO: どこで設定されているのか?)
- アプリケーション空間へのページ切替
- プロセスの状態をRUNNINGに変更する
- swtchによる処理
- カーネル空間へのページ切替

swtchについてはswtch.Sにアセンブラとして定義されています。
実行していたプロセスのレジスタを退避して、新しいレジスタの切替を行ないます。
```
// swtch.S
  1 # Context switch
  2 #
  3 #   void swtch(struct context **old, struct context *new);
  4 # 
  5 # Save current register context in old
  6 # and then load register context from new.
  7 
  8 .globl swtch
  9 swtch:
 10   movl 4(%esp), %eax
 11   movl 8(%esp), %edx
 12 
 13   # Save old callee-save registers
 14   pushl %ebp
 15   pushl %ebx
 16   pushl %esi
 17   pushl %edi
 18 
 19   # Switch stacks
 20   movl %esp, (%eax)
 21   movl %edx, %esp
 22 
 23   # Load new callee-save registers
 24   popl %edi
 25   popl %esi
 26   popl %ebx
 27   popl %ebp
 28   ret
```

上記のswtch関数のレジスタポインタ周りの処理については以下のスライド8-19にわかりやすく記載されているのでそちらを参照のこと
- https://www.slideshare.net/mfumi/xv6-context

実はカーネル空間scueduler()から遷移してきた場合のswtchの場合の他に、ユーザー空間のsched()から遷移してきた場合のswtchがあるのですが、次のように異なります。
- カーネルスレッドscheduler()からのswtchの戻り: スケジュールとして実行しておいたプロセスへ遷移する。
- ユーザー空間sched()からのswtchの戻り: カーネルスレッドで保存しておいたプロセスに戻る

### アプリケーションからのスケジューリング切替
アプリケーションからのスケジューリング切替は次のsched()によって実現されます。
```
300 // Enter scheduler.  Must hold only ptable.lock
301 // and have changed proc->state.
302 void
303 sched(void)
304 {   
305   int intena;
306     
307   if(!holding(&ptable.lock))
308     panic("sched ptable.lock");
309   if(cpu->ncli != 1)
310     panic("sched locks");
311   if(proc->state == RUNNING)
312     panic("sched running");
313   if(readeflags()&FL_IF)
314     panic("sched interruptible");
315   intena = cpu->intena;
316   swtch(&proc->context, cpu->scheduler);
317   cpu->intena = intena;
318 } 
```

上記のsched()が呼ばれると次の状態をチェックします。つまり、これらの処理はsched()へ遷移する前にアプリケーション側で保証されていなければならない。
- ptable.lockが取得されていることのチェック(L307)
- 自身のproc->stateがRUNNINGとなっていることの確認(L311)
- sched()が割り込み可能となっていないことの確認(L313)

swtchによって現在実行しているプロセスからカーネル空間で先ほど退避しておいたプロセスに切替を行ないます。

### sched()が呼び出される箇所について
sched()が呼び出されるのはyield(), exit(), sleep()の３つの場合のみです。
exitはプロセス終了、sleepは待機時に呼び出されると容易に想像できますが、yieldはどのような場合に呼ばれるのだろうか?

yieldを呼び出している箇所を確認して、yieldがどのような場合によばれるのかを確認する。

```
 38 //PAGEBREAK: 41
 39 void
 40 trap(struct trapframe *tf)
 41 {
...
 52   switch(tf->trapno){
 53   case T_IRQ0 + IRQ_TIMER:
 54     if(cpu->id == 0){
 55       acquire(&tickslock);
 56       ticks++;
 57       wakeup(&ticks);
 58       release(&tickslock);
 59     }
 60     lapiceoi();
 61     break;
...
 98   }
...
100   // Force process exit if it has been killed and is in user space.
101   // (If it is still executing in the kernel, let it keep running 
102   // until it gets to the regular system call return.)
103   if(proc && proc->killed && (tf->cs&3) == DPL_USER)
104     exit();
105 
106   // Force process to give up CPU on clock tick.
107   // If interrupts were on while locks held, would need to check nlock.
108   if(proc && proc->state == RUNNING && tf->trapno == T_IRQ0+IRQ_TIMER)
109     yield();
110 
111   // Check if the process has been killed since we yielded
112   if(proc && proc->killed && (tf->cs&3) == DPL_USER)
113     exit();
114 }
```

yieldは上記で定義されるtrap()関数のL108-L109で呼び出されます。
L108ではプロセスがRUNNINGであることをチェックした後に、IRQ_TIMER割り込みである場合にyield()が実行される。つまり、プロセス実行の時間を使い果たしてしまった場合に呼び出される割り込み処理である。

# まとめ
起動時にmain -> mpmain -> schedulerの遷移を辿ることによって、その中でforによる無限ループが行われていて、その中でスケジューリング処理を行っていました。  
その中でswtch()でプロセス切替を行っていました。
- 割り込み獲得
- ユーザー空間へページ切り替え
- swtch()によるコンテキストスイッチ処理
- カーネル空間へページ切り替え
- 割り込み解放

また、実はCPU解放には次の2つのパターンが存在していることが確認できた。
- カーネルスレッドによるscheduler()からのCPU解放が行われ、swtchによるコンテキストスイッチでプロセスのeipに遷移する。
- ユーザー空間によるsched()からのCPU解放が行われ、swtchによるコンテキストスイッチで先ほどまでカーネルで実行していたeipに遷移する。

プロセスからのsched呼び出しは次の３つの場合があることを確認しました。
- yield: TIMERによるIRQ割り込みがあった(プロセス実行時間を使い果たしたら)実行される。
- exit
- sleep

TODO: どこでIRQタイマーを開始しているのか?

# 参考URL
- xv6のコンテキストスイッチを読む
  - https://www.slideshare.net/mfumi/xv6-context
- Kernel vm study_2_xv6_scheduler_part1_revised (スライド)
  - https://www.slideshare.net/toshiakinozawa/kernel-vm-study2xv6schedulerpart1revised
- x86とコンテキストスイッチ
  - https://www.slideshare.net/masamiichikawa/x86study

