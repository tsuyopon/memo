# 概要
Linuxの場合、strace, ltrace, trace-cmd(ftrace)の３つが主にトレースとして利用されるようです。
- starce:    システムコール
- ltrace:    ライブラリコール
- trace-cmd: カーネルコール

ここではカーネルコールをトレースするtrace-cmdコマンドの使い方について説明する。
ftraceというカーネル関数コールをトレースする仕組みを使うとtrace-cmd, debugfs, kernelshar(GUI)などの機能を利用することができる。

### trace-cmd(ftrace)のインストール

デフォルトではインストールされていないのでインストールが必要かもしれない。
```
$ yum install trace-cmd
```

### 特定のコマンドのカーネルコールを取得する
例えば、wコマンドのカーネルコールを取得する場合
```
$ sudo trace-cmd record -p function_graph w
  plugin 'function_graph'
 19:00:48 up  4:19,  4 users,  load average: 0.96, 0.60, 0.29
USER     TTY      FROM              LOGIN@   IDLE   JCPU   PCPU WHAT
tsuyoshi :0       :0               Thu03   ?xdm?  33:22   0.05s gdm-session-worker [pam/gdm-password]
tsuyoshi pts/0    10.0.2.2         Thu04    3.00s  1.49s  0.02s sshd: tsuyoshi [priv]
tsuyoshi pts/1    10.0.2.2         Thu06    5:39   0.21s  0.21s -bash
tsuyoshi pts/2    :0               Thu06    2days  0.06s  0.06s bash
Kernel buffer statistics:
  Note: "entries" are the entries left in the kernel ring buffer and are not
        recorded in the trace data. They should all be zero.

CPU: 0
entries: 0
overrun: 750319
commit overrun: 0
bytes: 708
oldest event ts: 15572.878240
now ts: 15572.894780

^PCPU0 data recorded at offset=0x28f000
    1847296 bytes in size
$ ls trace.dat
```

上記コマンドを実行したディレクトリにtrace.datが生成されています。
続いて、そこに記されたカーネルコールを見ます。
```
$ trace-cmd report | less
version = 6
cpus=1
CPU:0 [EVENTS DROPPED]
            pool-1416  [000] 15572.662039: funcgraph_exit:         0.502 us   |                            }
            pool-1416  [000] 15572.662040: funcgraph_exit:         1.055 us   |                          }
            pool-1416  [000] 15572.662040: funcgraph_exit:         3.410 us   |                        }
            pool-1416  [000] 15572.662040: funcgraph_exit:         4.315 us   |                      }
            pool-1416  [000] 15572.662040: funcgraph_exit:         5.201 us   |                    }
            pool-1416  [000] 15572.662040: funcgraph_exit:         5.551 us   |                  }
            pool-1416  [000] 15572.662040: funcgraph_entry:                   |                  __page_cache_alloc() {
            pool-1416  [000] 15572.662041: funcgraph_entry:                   |                    alloc_pages_current() {
            pool-1416  [000] 15572.662041: funcgraph_entry:        0.036 us   |                      policy_nodemask();
            pool-1416  [000] 15572.662041: funcgraph_entry:        0.034 us   |                      policy_zonelist();
            pool-1416  [000] 15572.662041: funcgraph_entry:                   |                      __alloc_pages_nodemask() {
(省略)
```


# 参考URL
- LWN.net: trace-cmd: A front-end for Ftrace
 - https://lwn.net/Articles/410200/
