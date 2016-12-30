# 概要
SystemTapについてまとめる

# セットアップ方法(Fedora17でyumを使う場合)
SystemTapを利用するためには次のsystemtapに関連するパッケージ、kernelに関連するパッケージをインストールする必要がある。
```
$ sudo yum install systemtap systemtap-runtime systemtap-sdt-devel kernel-debuginfo kernel-debuginfo-common kernel-devel -y
```

試しに以下のサンプルを実行してみる
```
$ sudo stap -v -e 'probe vfs.read {printf("read performed\n"); exit()}'
Pass 1: parsed user script and 124 library script(s) using 166280virt/89908res/2884shr/87976data kb, in 470usr/50sys/716real ms.
semantic error: while resolving probe point: identifier 'kernel' at /usr/share/systemtap/tapset/linux/vfs.stp:751:18
        source: probe vfs.read = kernel.function("vfs_read")
                                 ^

semantic error: missing x86_64 kernel/module debuginfo [man warning::debuginfo] under '/lib/modules/3.3.4-5.fc17.x86_64/build'
semantic error: while resolving probe point: identifier 'vfs' at <input>:1:7
        source: probe vfs.read {printf("read performed\n"); exit()}
                      ^

semantic error: no match
Pass 2: analyzed script: 0 probe(s), 0 function(s), 0 embed(s), 0 global(s) using 174012virt/97424res/4780shr/93608data kb, in 180usr/180sys/1980real ms.
Pass 2: analysis failed.  [man error::pass2]
```

(この辺の記事)[http://itiut.hatenablog.com/entry/2015/04/19/180314#f-e3bfb4ca]によると、稼働しているカーネルとdebuginfo関連のパッケージのバージョンが異なるとのことらしいので確認してみることにする。
```
$ uname -r
3.3.4-5.fc17.x86_64
$ rpm -qa | grep -i kernel-debug
kernel-debuginfo-common-x86_64-3.9.10-100.fc17.x86_64
kernel-debuginfo-3.9.10-100.fc17.x86_64
```

debuginfo関連のバージョンの方が新しいのでダウングレードする。
```
$ sudo yum downgrade kernel-debuginfo-common-x86_64-3.3.4-5.fc17.x86_64 kernel-debuginfo-3.3.4-5.fc17.x86_64
```

以上でSystemTapを使うための準備が整ったはずなので再度実行してみる。
```
$ sudo stap -v -e 'probe vfs.read {printf("read performed\n"); exit()}'
Pass 1: parsed user script and 124 library script(s) using 166280virt/89908res/2884shr/87976data kb, in 450usr/80sys/706real ms.
Pass 2: analyzed script: 1 probe(s), 1 function(s), 3 embed(s), 0 global(s) using 424240virt/211332res/7388shr/204092data kb, in 1540usr/150sys/2255real ms.
Pass 3: translated to C into "/tmp/stapFuYrkj/stap_05dba080c12edbedf9082c6f9b021326_1610_src.c" using 417032virt/209492res/6384shr/204092data kb, in 0usr/0sys/10real ms.
Pass 4: compiled C into "stap_05dba080c12edbedf9082c6f9b021326_1610.ko" in 5180usr/1100sys/7815real ms.
Pass 5: starting run.
read performed
Pass 5: run completed in 10usr/10sys/332real ms.
```

### 特定のコマンドに関するシステムコールを追いかける
以下ではdfに関するシステムコールを追いかけることにする。
```
$ sudo stap -c df -e 'probe syscall.* { if (target()==pid()) log(name." ".argstr) }'
Filesystem             1K-blocks     Used Available Use% Mounted on
rootfs                  19401644 16952248   2255116  89% /
devtmpfs                  500224        0    500224   0% /dev
tmpfs                     510024      100    509924   1% /dev/shm
tmpfs                     510024     3544    506480   1% /run
/dev/mapper/vg-lv_root  19401644 16952248   2255116  89% /
tmpfs                     510024        0    510024   0% /sys/fs/cgroup
tmpfs                     510024        0    510024   0% /media
/dev/sda1                 508745    60650    422495  13% /boot
rt_sigreturn 
rt_sigaction SIGUSR1, {SIG_DFL}, 0x0, 8
rt_sigprocmask SIG_SETMASK, [EMPTY], 0x0, 8
execve /sbin/df 
execve /bin/df 
close 3
close 5
brk 0x0
mmap2 0x0, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0
access <unknown>, R_OK
faccessat AT_FDCWD, <unknown>, R_OK
open "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC|O_CLOEXEC
fstat 3, 0x7fffec1939c0
mmap2 0x0, 83597, PROT_READ, MAP_PRIVATE, 3, 0
close 3
open "/lib64/libc.so.6", O_RDONLY|O_CLOEXEC|O_CLOEXEC
read 3, 0x7fffec193b78, 832
fstat 3, 0x7fffec193a20
mmap2 0x3897a00000, 3892376, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0
mprotect 0x3897bac000, 2097152, PROT_NONE
mmap2 0x3897dac000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 428
mmap2 0x3897db2000, 17560, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0
close 3
mmap2 0x0, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0
mmap2 0x0, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0
arch_prctl 4098, 0x7ffd1dc6e740
mprotect 0x615000, 4096, PROT_READ
mprotect 0x3897dac000, 16384, PROT_READ
mprotect 0x389781f000, 4096, PROT_READ
munmap 0x7ffd1dc71000, 83597
brk 0x0
brk 0x1725000
brk 0x0
open "/etc/mtab", O_RDONLY|O_CLOEXEC|O_CLOEXEC
fstat 3, 0x7fffec193c00
mmap2 0x0, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0
read 3, 0x7ffd1dc85000, 1024
read 3, 0x7ffd1dc85000, 1024
read 3, 0x7ffd1dc85000, 1024
read 3, 0x7ffd1dc85000, 1024
close 3
munmap 0x7ffd1dc85000, 4096
statfs "/", 0x7fffec193dd0
statfs "/sys", 0x7fffec193dd0
statfs "/dev", 0x7fffec193dd0
statfs "/dev/pts", 0x7fffec193dd0
statfs "/dev/shm", 0x7fffec193dd0
statfs "/run", 0x7fffec193dd0
statfs "/", 0x7fffec193dd0
statfs "/sys/fs/cgroup", 0x7fffec193dd0
statfs "/sys/fs/cgroup/systemd", 0x7fffec193dd0
statfs "/sys/fs/cgroup/cpuset", 0x7fffec193dd0
statfs "/sys/fs/cgroup/cpu,cpuacct", 0x7fffec193dd0
statfs "/sys/fs/cgroup/memory", 0x7fffec193dd0
statfs "/sys/fs/cgroup/devices", 0x7fffec193dd0
statfs "/sys/fs/cgroup/freezer", 0x7fffec193dd0
statfs "/sys/fs/cgroup/net_cls", 0x7fffec193dd0
statfs "/sys/fs/cgroup/blkio", 0x7fffec193dd0
statfs "/sys/fs/cgroup/perf_event", 0x7fffec193dd0
statfs "/sys/kernel/security", 0x7fffec193dd0
statfs "/dev/hugepages", 0x7fffec193dd0
statfs "/media", 0x7fffec193dd0
statfs "/dev/mqueue", 0x7fffec193dd0
statfs "/sys/kernel/debug", 0x7fffec193dd0
statfs "/sys/kernel/config", 0x7fffec193dd0
statfs "/proc/sys/fs/binfmt_misc", 0x7fffec193dd0
statfs "/boot", 0x7fffec193dd0
statfs "/run/user/tsuyoshi/gvfs", 0x7fffec193dd0
statfs "/home/tsuyoshi/git/cpp/fuse/mnt", 0x7fffec193dd0
fstat 1, 0x7fffec1940c0
mmap2 0x0, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0
write 1, "Filesystem             1K-blocks     Used Ava"..., 575
close 1
munmap 0x7ffd1dc85000, 4096
close 2
exit_group 0
exit 0
```

# 参考URL
- (SystemTap公式サイト)[https://sourceware.org/systemtap/]
- (SystemTap Beginners Guide)[https://sourceware.org/systemtap/SystemTap_Beginners_Guide/index.html]
- (Systemtap Document)[https://sourceware.org/systemtap/documentation.html]
 - TutorialやBeginner Guide, Language Reference, Tapset ReferenceなどがHTMLとPDFそれぞれで用意されている。



