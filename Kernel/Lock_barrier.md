# 概要
Lockとメモリバリアについてまとめる

以下の３つの概念を押さえておくことは非常に重要です。
- Semaphore
- Mutex
- Spin Lock

メモリ・バリア(Intel用語ではメモリフェンス)はlockとはまた異なった概念です。

# Lock
### Semaphore
カウンティングセマフォとバイナリセマフォに分かれる。バイナリセマフォは0か1の値しか持たずMutexと同等である。 CPUをWAIT状態にする。

### Mutex
クリティカルセッションにアクセス可能にするスレッドの管理数が1つしか存在しない。

### Spin Lock
マルチプロセッサ環境において，各CPUが同じ資源（リソース）に同時アクセスする際に用いられる排他制御の仕組みです。  
ある資源にアクセスされる期間は非常に短くすぐにロックが解放されるはずという思想でスピンロックが使われているものと思われます。  
CPUをずっと使用状態(busy wait)とするので、待ち時間が短い場合に有効です。
x86だとxchg命令で実現されています。

# メモリ・バリア
メモリの初期化順序などが異なる場合(out of orderと呼ぶ)やIOPORTやDirectメモリアクセス等で最適化されたくないような場合に利用する。
Lock Free Synchronizationにおいてメモリ・バリアが必要なことを以下の資料で説明している。C++11のstd::atomicはメモリバリアを使って実装されているらしい。
- http://www.nminoru.jp/~nminoru/data/b2con2006_nminoru.pdf

メモリ・バリアと同様のことがvolatileを使ってもできるらしい(全てに有効では無いなどの記述も多い)。
- http://www.wdic.org/w/TECH/volatile

x86のCPU命令ではsfence(SSE), lfence, mfence(SSE2)の３つが存在する。
なお、lfenceは50サイクル強、sfenceは50サイクル弱程度の実行レイテンシーがあるが、mfenceは130サイクル程度を要し、非常に遅い命令の一つである。

x86だとlinux kernelでは次のように定義されている。
```
// arch/x86/include/asm/system.h
350 /*
351  * Force strict CPU ordering.
352  * And yes, this is required on UP too when we're talking
353  * to devices.
354  */
355 #ifdef CONFIG_X86_32
356 /*
357  * Some non-Intel clones support out of order store. wmb() ceases to be a
358  * nop for these.
359  */
360 #define mb() alternative("lock; addl $0,0(%%esp)", "mfence", X86_FEATURE_XMM2)
361 #define rmb() alternative("lock; addl $0,0(%%esp)", "lfence", X86_FEATURE_XMM2)
362 #define wmb() alternative("lock; addl $0,0(%%esp)", "sfence", X86_FEATURE_XMM)
363 #else
364 #define mb()    asm volatile("mfence":::"memory")
365 #define rmb()   asm volatile("lfence":::"memory")
366 #define wmb()   asm volatile("sfence" ::: "memory")
367 #endif
```

３つの命令について簡単に概要を記しておく
- SFENCE（store fence）
 -メモリへの書き込み順序を制御します。SFENCEの前に発行された書き込み命令が終わるまで、SFENCEより後の書き込み命令は開始されません。
- LFENCE（load fence）
 - メモリの読み込み順序を制御します。LFENCEの前に発行された読み込み命令が終わるまで、SFENCEより後の読み込み命令は開始されません。
- MFENCE（m…?? fence）
 - SFENCEとLFENCEの複合版です。MFENCEの間に発行された書き込み/読み込み命令が終わるまで、MFENCEより後の書き込み/読み込み命令は開始されません。



