# $B35MW(B
$B%3%"%U%!%$%k$K$D$$$F(B

## $B%3%"4XO"@_Dj(B

#####  $B%3%"$,@8@.$5$l$J$$>l9g(B
ulimit$B%3%^%s%I@_Dj$r8+D>$9I,MW$,$"$j$^$9!#(B
```
$ ulimit -c              // $B3NG'%3%^%s%I(B
$ ulimit -c unlimited    // $BL5@)8B$KJQ99(B
```

##### $B5/F0Cf%W%m%;%9$N%3%"$r<hF@$9$k!#(B
gcore$B%3%^%s%I$K%W%m%;%9(BID$B$r;XDj$9$l$P@8@.$9$k$3$H$,$G$-$k(B
```
$ sudo gcore 2567
[sudo] password for tsuyoshi: 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".
0x00007f3325b03e47 in accept4 () from /lib64/libc.so.6
Saved corefile core.2567
$ ls core.2567
$ sudo gdb /usr/local/bin/httpd core.2567
```

#####  core$B%U%!%$%k$,2?=h$K:n@.$5$l$k$+3NG'$9$k(B
```
$ sysctl -a | grep core 
kern.corefile: /cores/core.%P
kern.coredump: 1
kern.sugid_coredump: 0
machdep.cpu.cores_per_package: 8
machdep.cpu.thermal.core_power_limits: 1
machdep.cpu.core_count: 2
```

## $B%3%"%U%!%$%k$r@8@.$9$k(B
$B$^$:(Bcore$B%U%!%$%k$O$I$N$h$&$K@8@.$9$k$+$H$$$&$H(B(apache$B$K8B$C$?$b$N$G$O$J$$(B)

(1) gcore$B$+$i(Bpid$B$r;XDj$7$F@8@.$9$k(B
```
$ gcore <pid>
```

(2) gdb$B$+$i@8@.$9$k(B
```
$ gdb
(gdb) attach <pid>
(gdb) gcore core
(gdb) detach
$ ls -alt ./core
```

$B$3$l$N(Bcore$B$rMxMQ$9$k$H0J2<$N$h$&$K$7$F860x2U=j$NFCDj$,$G$-$k$h$&$G$9!#(B
```
$ sudo gdb /usr/sbin/httpd core
(gdb) where
(gdb) bt
(gdb) bt full
```

$B$^$?$O$3$s$J46$8$G$b$$$1$k$H;W$&(B($B;n$7$F$$$J$$(B)
```
$ sudo gdb
(gdb) file /usr/sbin/httpd
(gdb) core-file core
(gdb) bt
```


