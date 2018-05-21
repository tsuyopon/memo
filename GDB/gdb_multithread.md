# 概要
マルチスレッドプログラミングにおけるgdbの扱い方

# 詳細

### 基本操作のまとめ

全スレッドの表示
```
(gdb) info threads
  3 Thread 0x7ffff75d2710 (LWP 4688)  thread3 (d=0x0) at three-threads.c:9
* 2 Thread 0x7ffff7fd3710 (LWP 4687)  thread2 (d=0x0) at three-threads.c:23
  1 Thread 0x7ffff7fd5720 (LWP 4620)  main () at three-threads.c:34
```

スレッド番号の切り替え + バックトレース取得
```
(gdb) thread <num>
(gdb) bt
```

スレッドの全てのバックトレースを表示する
```
(gdb) thread apply all bt
or
(gdb) t a a bt
```

特定のスレッドに対してブレークポイントを設定する
```
(gdb) b xxxfunc thread <num>
or
(gdb) b xxxfunc thread <num>  if a > b
```

- 参考
 - https://sourceware.org/gdb/current/onlinedocs/gdb/Threads.html

### 特定のスレッドでのみbreakpointが貼られるようにしたい
```
(gdb) b Server::accept thread 7
Breakpoint 1 at 0x7853ae: file Connection.cc, line 73.
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00000000007853ae in Server::accept(Connection*) at Connection.cc:73 thread 7
	stop only in thread 7
```

さらに特定の条件を加えるには次のようにします。たとえば、cがNULLでない場合を追加するには次のようにします。
```
(gdb) b Server::accept thread 7 if c != 0
Breakpoint 1 at 0x7853ae: file Connection.cc, line 73.
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00000000007853ae in Server::accept(Connection*) at Connection.cc:73 thread 7
	stop only if c != 0
	stop only in thread 7
```

### 特定のスレッドに移動し、バックトレースを取得する
info threadで現在存在するスレッドIDを確認します。特定のスレッドに移動するには「thread <N>」を実行します。
そのスレッドのバックトレースを確認するにはそのままbtを実行します。
```
(gdb) info thread
(gdb) thread 3
(gdb) bt
```

### 全スレッドのバックトレースを表示したい

次のコマンドで全スレッドのバックトレースを表示する
```
(gdb) thread apply all where
```

次のコマンドではN個に絞ってバックトレースを表示する
```
(gdb) t a a bt 3         // thread apply all bt 3

Thread 5 (Thread 0x2b6bbb832700 (LWP 4249)):
#0  0x00002b6bb713ecf2 in pthread_cond_timedwait@@GLIBC_2.3.2 () from /lib64/libpthread.so.0
#1  0x00000000007cc8a5 in ink_cond_timedwait (cp=0x2b6bbb630b68, mp=0x2b6bbb630b40, t=0x2b6bbb831ca0) at ../../lib/ts/ink_thread.h:251
#2  0x00000000007ccc57 in ProtectedQueue::wait (this=0x2b6bbb630b20, timeout=1526863484230392716) at ProtectedQueue.cc:117
(More stack frames follow...)

Thread 4 (Thread 0x2b6bbb933700 (LWP 4250)):
---Type <return> to continue, or q <return> to quit---
#0  0x00002b6bb713ecf2 in pthread_cond_timedwait@@GLIBC_2.3.2 () from /lib64/libpthread.so.0
#1  0x00000000007cc8a5 in ink_cond_timedwait (cp=0x2b6bbb731b68, mp=0x2b6bbb731b40, t=0x2b6bbb932ca0) at ../../lib/ts/ink_thread.h:251
#2  0x00000000007ccc57 in ProtectedQueue::wait (this=0x2b6bbb731b20, timeout=1526863484189061976) at ProtectedQueue.cc:117
(More stack frames follow...)

Thread 3 (Thread 0x2b6bbbb35700 (LWP 4251)):
#0  0x00002b6bb7e6c7df in accept4 () from /lib64/libc.so.6
#1  0x00000000007cd108 in SocketManager::accept4 (this=0x10a00a0 <socketManager>, s=32, addr=0x2b6bbbb34bec, addrlen=0x2b6bbbb34ba8, flags=526336)
    at SocketManager.cc:72
#2  0x00000000007853ed in Server::accept (this=0x2419eb8, c=0x2b6bbbb34be0) at Connection.cc:76
(More stack frames follow...)

Thread 2 (Thread 0x2b6bb98f1700 (LWP 4236)):
#0  0x00002b6bb7e6b923 in epoll_wait () from /lib64/libc.so.6
#1  0x00000000007a1ab8 in NetHandler::waitForActivity (this=0x2b6bb96f3e60, timeout=1574691) at UnixNet.cc:403
#2  0x00000000007cea6b in EThread::execute_regular (this=0x2b6bb96f0010) at UnixEThread.cc:248
(More stack frames follow...)

Thread 1 (Thread 0x2b6bb5a284c0 (LWP 4234)):
#0  0x00002b6bb7e321ad in nanosleep () from /lib64/libc.so.6
#1  0x00002b6bb7e32044 in sleep () from /lib64/libc.so.6
#2  0x000000000055054f in main (argv=0x7ffedc0f6018) at Main.cc:1962
```

- SeeAlso
  - https://stackoverflow.com/questions/3282389/determining-the-correct-thread-to-debug-in-gdb


引数情報なども含めて全て表示したい場合には次のようにします。
```
(gdb) t a a bt full

Thread 18 (Thread 0x2b6bb94ee700 (LWP 4235)):
#0  0x00002b6bb7e627a3 in select () from /lib64/libc.so.6
No symbol table info available.
#1  0x00000000006e863a in mgmt_select (nfds=19, readfds=0x2b6bb94edc50, writefds=0x0, errorfds=0x0, timeout=0x2b6bb94edcd0) at MgmtSocket.cc:175
        r = 0
        retries = 0
#2  0x00000000006e8982 in mgmt_read_timeout (fd=18, sec=1, usec=0) at MgmtSocket.cc:294
        timeout = {tv_sec = 0, tv_usec = 490036}
        readSet = {fds_bits = {262144, 0 <repeats 15 times>}}
#3  0x00000000006e5182 in ProcessManager::pollLMConnection (this=0x223f5a0) at ProcessManager.cc:237
        num = 1
        mh_hdr = {msg_id = 10009, data_len = 264}
        mh_full = 0x2b6bbc02a430
        count = 16
        __FUNCTION__ = "pollLMConnection"
        res = 264
        data_raw = 0x2b6bbc02a438 "x"
#4  0x00000000006e4936 in startProcessManager (arg=0x0) at ProcessManager.cc:65
        ret = 0x0
        __FUNCTION__ = "startProcessManager"

(snip)
```


### 「new thread」、「thread exited」メッセージを表示しない
```
(gdb) set print thread-events off
```

- SeeAlso
  - https://stackoverflow.com/questions/10937289/how-can-i-disable-new-thread-thread-exited-messages-in-gdb

### プログラムが終了した箇所を知る方法
シングルプロセスだと終了させてbtさせるだけだが、マルチスレッドで特定のスレッドが終了したことを知るにはexitや_exitにbreakpointを貼ることができる
```
(gdb) break exit
or
(gdb) break _exit
```

- SeeAlso
  - https://stackoverflow.com/questions/6376869/gdb-how-to-find-out-from-where-program-exited?rq=1
