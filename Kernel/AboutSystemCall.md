
# システムコールについて

Linuxカーネルにおけるシステムコールについてまとめておく


# 調査


``` include/asm-x86_64/unistd.hから抜粋
 14 /* at least 8 syscall per cacheline */
 15 #define __NR_read                                0
 16 __SYSCALL(__NR_read, sys_read)
 17 #define __NR_write                               1
 18 __SYSCALL(__NR_write, sys_write)
 19 #define __NR_open                                2
 20 __SYSCALL(__NR_open, sys_open)
 21 #define __NR_close                               3
 22 __SYSCALL(__NR_close, sys_close)
 23 #define __NR_stat                                4
 24 __SYSCALL(__NR_stat, sys_newstat)
 25 #define __NR_fstat                               5
 26 __SYSCALL(__NR_fstat, sys_newfstat)
 27 #define __NR_lstat                               6
 28 __SYSCALL(__NR_lstat, sys_newlstat)
 29 #define __NR_poll                                7
 30 __SYSCALL(__NR_poll, sys_poll)
```



# 参考資料
* システムコールとLinuxカーネルのソース(筑波大学講義資料)
	* http://www.coins.tsukuba.ac.jp/~yas/coins/os2-2011/2011-12-06/index.html