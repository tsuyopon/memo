# 概要
コアファイルの生成方法に関する設定や確認方法について

# 詳細

### 一時的にコアファイルを出力するように変更する(再起動後には無効になる)
以下の設定を行うことでコアファイルを出力するようにします。
コアファイルはメモリダンプを行ない容量が大きくなることが想定されるのでunlimitedを指定しておきます。(この設定は一時的にそのターミナルのみで有効な設定となります。別のターミナルを起動すると以下の設定は無効になっている場合があるので注意してください。)
```
$ ulimit -c unlimited
$ ulimit -c 
unlimited
```

現在稼働しているプロセスに対して上記設定が適用されているのかを確認するために、/proc/[fd]/limitsを確認しておきます。
上記コマンドを実行すれば「Max core file size」が適用されているはずです。
```
$ cat /proc/14965/limits 
Limit                     Soft Limit           Hard Limit           Units     
Max cpu time              unlimited            unlimited            seconds   
Max file size             unlimited            unlimited            bytes     
Max data size             unlimited            unlimited            bytes     
Max stack size            8388608              unlimited            bytes     
Max core file size        0                    unlimited            bytes     
Max resident set          unlimited            unlimited            bytes     
Max processes             3884                 3884                 processes 
Max open files            1024                 4096                 files     
Max locked memory         65536                65536                bytes     
Max address space         unlimited            unlimited            bytes     
Max file locks            unlimited            unlimited            locks     
Max pending signals       3884                 3884                 signals   
Max msgqueue size         819200               819200               bytes     
Max nice priority         0                    0                    
Max realtime priority     0                    0                    
Max realtime timeout      unlimited            unlimited            us        
```

続いて、コアが出力される場所について記載します。
```
$ sudo sh -c 'echo "/tmp/core.%e.%p" > /proc/sys/kernel/core_pattern'
$ cat  /proc/sys/kernel/core_pattern
/tmp/core.%e.%p
```



# 参考URL
- Qiita: coreファイルを生成,参照する方法
  - https://qiita.com/hana_shin/items/8065f66332a088303439
