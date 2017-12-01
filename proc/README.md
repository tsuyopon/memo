# 概要
/procについて

特定のjavaプロセスのファイルディスクリプタが知りたい場合には次のようにします
```
$ ls -l /proc/`pgrep -n java`/fd
```

# 参考URL
- https://linux.die.net/man/5/proc
- http://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/tree/Documentation/filesystems/proc.txt?id=HEAD#n866
- https://linuxjm.osdn.jp/html/LDP_man-pages/man5/proc.5.html
- KernelAnalysis-HOWTO
 - http://tldp.org/HOWTO/KernelAnalysis-HOWTO.html
