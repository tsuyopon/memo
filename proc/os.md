# 概要
/procのosについて


# 詳細
### バージョンを表示する(/proc/version)
```
$ cat /proc/version 
Linux version 3.3.4-5.fc17.x86_64 (mockbuild@x86-14.phx2.fedoraproject.org) (gcc version 4.7.0 20120504 (Red Hat 4.7.0-4) (GCC) ) #1 SMP Mon May 7 17:29:34 UTC 2012
```

### カーネルモジュールを表示する(/proc/modules)

1番目のフィールドはモジュール名が表示されます。  
2番目のフィールドにはモジュールのメモリ容量(byte)が表示されます。  
3番目のフィールドには現在ロードされているモジュールのインスタンス数が表示されます。  
4番目のフィールドにはそのモジュールが依存するモジュール名が表示されます。「-」の場合には独立したモジュールとなります。  
5番目のフィールドはロード状態があり、Live、Loading、Unloadingの３つの状態がある。  
6番目のフィールドは、カーネルメモリオフセットが表示される。  

```
$ cat /proc/modules 
fuse 77772 4 - Live 0xffffffffa01a6000
bnep 19584 2 - Live 0xffffffffa01a0000
bluetooth 273667 7 bnep, Live 0xffffffffa014a000
rfkill 21384 3 bluetooth, Live 0xffffffffa013e000
ip6t_REJECT 12939 2 - Live 0xffffffffa0139000
nf_conntrack_ipv6 14297 10 - Live 0xffffffffa0130000
nf_defrag_ipv6 18095 1 nf_conntrack_ipv6, Live 0xffffffffa0126000
ipt_MASQUERADE 12880 1 - Live 0xffffffffa0121000
xt_state 12578 19 - Live 0xffffffffa011c000
iptable_nat 13383 1 - Live 0xffffffffa0117000
nf_nat 25179 2 ipt_MASQUERADE,iptable_nat, Live 0xffffffffa010b000
nf_conntrack_ipv4 14622 12 iptable_nat,nf_nat, Live 0xffffffffa0102000
nf_defrag_ipv4 12673 1 nf_conntrack_ipv4, Live 0xffffffffa00f4000
ip6table_filter 12815 1 - Live 0xffffffffa00fd000
nf_conntrack 82339 6 nf_conntrack_ipv6,ipt_MASQUERADE,xt_state,iptable_nat,nf_nat,nf_conntrack_ipv4, Live 0xffffffffa00de000
ip6_tables 27073 1 ip6table_filter, Live 0xffffffffa0073000
snd_intel8x0 38143 2 - Live 0xffffffffa00d3000
microcode 19252 0 - Live 0xffffffffa00a1000
e1000 145411 0 - Live 0xffffffffa00aa000
snd_ac97_codec 133281 1 snd_intel8x0, Live 0xffffffffa007f000
ac97_bus 12718 1 snd_ac97_codec, Live 0xffffffffa0053000
snd_pcm 97129 2 snd_intel8x0,snd_ac97_codec, Live 0xffffffffa005a000
snd_page_alloc 18101 2 snd_intel8x0,snd_pcm, Live 0xffffffffa0042000
snd_timer 28690 1 snd_pcm, Live 0xffffffffa004a000
snd 78862 8 snd_intel8x0,snd_ac97_codec,snd_pcm,snd_timer, Live 0xffffffffa002d000
soundcore 14491 1 snd, Live 0xffffffffa0025000
i2c_piix4 13694 0 - Live 0xffffffffa0006000
i2c_core 38028 1 i2c_piix4, Live 0xffffffffa001a000
uinput 17673 0 - Live 0xffffffffa0014000
binfmt_misc 17463 1 - Live 0xffffffffa000b000
video 18980 0 - Live 0xffffffffa0000000
```

### マウント情報を表示する
現在マウントされているマウントポイントの一覧を表示する。
```
$ cat /proc/mounts 
rootfs / rootfs rw 0 0
sysfs /sys sysfs rw,seclabel,nosuid,nodev,noexec,relatime 0 0
proc /proc proc rw,nosuid,nodev,noexec,relatime 0 0
devtmpfs /dev devtmpfs rw,seclabel,nosuid,size=1928188k,nr_inodes=482047,mode=755 0 0
securityfs /sys/kernel/security securityfs rw,nosuid,nodev,noexec,relatime 0 0
tmpfs /dev/shm tmpfs rw,seclabel,nosuid,nodev 0 0
devpts /dev/pts devpts rw,seclabel,nosuid,noexec,relatime,gid=5,mode=620,ptmxmode=000 0 0
tmpfs /run tmpfs rw,seclabel,nosuid,nodev,mode=755 0 0
tmpfs /sys/fs/cgroup tmpfs ro,seclabel,nosuid,nodev,noexec,mode=755 0 0
cgroup /sys/fs/cgroup/systemd cgroup rw,seclabel,nosuid,nodev,noexec,relatime,xattr,release_agent=/usr/lib/systemd/systemd-cgroups-agent,name=systemd 0 0
pstore /sys/fs/pstore pstore rw,nosuid,nodev,noexec,relatime 0 0
cgroup /sys/fs/cgroup/cpuset cgroup rw,seclabel,nosuid,nodev,noexec,relatime,cpuset 0 0
cgroup /sys/fs/cgroup/cpu,cpuacct cgroup rw,seclabel,nosuid,nodev,noexec,relatime,cpuacct,cpu 0 0
cgroup /sys/fs/cgroup/devices cgroup rw,seclabel,nosuid,nodev,noexec,relatime,devices 0 0
cgroup /sys/fs/cgroup/memory cgroup rw,seclabel,nosuid,nodev,noexec,relatime,memory 0 0
cgroup /sys/fs/cgroup/net_cls,net_prio cgroup rw,seclabel,nosuid,nodev,noexec,relatime,net_prio,net_cls 0 0
cgroup /sys/fs/cgroup/blkio cgroup rw,seclabel,nosuid,nodev,noexec,relatime,blkio 0 0
cgroup /sys/fs/cgroup/freezer cgroup rw,seclabel,nosuid,nodev,noexec,relatime,freezer 0 0
cgroup /sys/fs/cgroup/hugetlb cgroup rw,seclabel,nosuid,nodev,noexec,relatime,hugetlb 0 0
cgroup /sys/fs/cgroup/perf_event cgroup rw,seclabel,nosuid,nodev,noexec,relatime,perf_event 0 0
cgroup /sys/fs/cgroup/pids cgroup rw,seclabel,nosuid,nodev,noexec,relatime,pids 0 0
configfs /sys/kernel/config configfs rw,relatime 0 0
/dev/mapper/centos-root / xfs rw,seclabel,relatime,attr2,inode64,noquota 0 0
selinuxfs /sys/fs/selinux selinuxfs rw,relatime 0 0
systemd-1 /proc/sys/fs/binfmt_misc autofs rw,relatime,fd=34,pgrp=1,timeout=0,minproto=5,maxproto=5,direct,pipe_ino=15124 0 0
debugfs /sys/kernel/debug debugfs rw,relatime 0 0
hugetlbfs /dev/hugepages hugetlbfs rw,seclabel,relatime 0 0
mqueue /dev/mqueue mqueue rw,seclabel,relatime 0 0
/dev/sda1 /boot xfs rw,seclabel,relatime,attr2,inode64,noquota 0 0
tmpfs /run/user/1000 tmpfs rw,seclabel,nosuid,nodev,relatime,size=388064k,mode=700,uid=1000,gid=1000 0 0
```

### サポートされているファイルシステムを確認する

```
$ cat /proc/filesystems
nodev	sysfs
nodev	rootfs
nodev	ramfs
nodev	bdev
nodev	proc
nodev	cgroup
nodev	cpuset
nodev	tmpfs
nodev	devtmpfs
nodev	debugfs
nodev	securityfs
nodev	sockfs
nodev	dax
nodev	bpf
nodev	pipefs
nodev	anon_inodefs
nodev	configfs
nodev	devpts
nodev	hugetlbfs
nodev	autofs
nodev	pstore
nodev	mqueue
nodev	selinuxfs
	xfs
```

### 統計情報を取得する
irqbalanceなどのソフトウェアも参照している/proc/statは次の通り

```
$ cat /proc/stat 
cpu  60678 5685 30089 11996532 20652 35416 13469 0 0 0
cpu0 60678 5685 30089 11996532 20652 35416 13469 0 0 0
intr 7723060 155 29 0 0 0 0 0 0 0 0 0 0 133 0 0 119534 0 0 0 982235 0 707157 780 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
ctxt 17750874
btime 1483238983
processes 62675
procs_running 1
procs_blocked 0
softirq 7963428 0 3162835 24416 1302554 669895 0 21 0 36888 2766819
```

これらの値の意味は次の通り
- cpu: 合計10個の値があるが各種状態で消費された時間の合計値。 時間は USER_HZ を単位として計測される。
 - (1) user: ユーザーモードで消費した時間
 - (2) nice: 低い優先度(nice)のユーザーモードで消費した時間
 - (3) system: システムモードで消費した時間
 - (4) idle: タスク待ちで消費した時間
 - (5) iowait: I/O完了待ちの時間
 - (6) irq: 割り込み処理に使った時間(Linux 2.5.41 以降)
 - (7) softirq: 割り込みの処理に使った時間(Linux 2.6.0-test4 以降)
 - (8) steal: 盗まれた時間。仮想化環境での動作時に他のオペレーティングシステムにより消費された時間を表す(Linux 2.6.11 以降)
 - (9) guest: Linux カーネルの制御下のゲストオペレーティングシステムの仮想 CPU の 実行に消費された時間(Linux 2.6.24 以降)
 - (10) guest_nice: nice が適用されたゲスト (Linux カーネルの制御下のゲストオペレーティングシステムの仮想 CPU) の 実行に消費された時間(Linux 2.6.33 以降)
- intr: この行はシステム起動時以降に処理された割り込みの回数を示す
 - 最初の欄は処理された割り込み全ての合計であり、 これには番号が割り振られていないアーキテクチャー固有の割り込みも含まれる。 
 - それ以降の欄はそれぞれ番号が割り振られた割り込みについての合計である。 番号が割り振られていない割り込みは表示されず、 全体の合計にのみ加算される。 
- btime: 起動時刻で1970/01/01からの秒数を表す
- ctxt: コンテクストスイッチの延べ回数
- procs_running: 実行中状態のプロセス数 (Linux 2.5.45 以降)
- procs_blocked: I/O 完了待ちで停止 (blocked) しているプロセス数(Linux 2.5.45 以降)

- 参考: https://linuxjm.osdn.jp/html/LDP_man-pages/man5/proc.5.html
 - /proc/statの箇所を参照すること

### Linuxカーネルが利用している暗号化アルゴリズムを表示する(/proc/crypto)
```
$ sudo cat /proc/crypto | tail -25
min keysize  : 16
max keysize  : 32

name         : aes
driver       : aes-aesni
module       : kernel
priority     : 300
refcnt       : 1
selftest     : passed
type         : cipher
blocksize    : 16
min keysize  : 16
max keysize  : 32

name         : aes
driver       : aes-asm
module       : kernel
priority     : 200
refcnt       : 1
selftest     : passed
type         : cipher
blocksize    : 16
min keysize  : 16
max keysize  : 32
```

nameだけを表示した例は次の通り
```
$ grep '^name' /proc/crypto
name         : stdrng
name         : crc32c
name         : aes
name         : sha1
name         : md5
name         : xts(aes)
name         : pcbc(aes)
name         : lrw(aes)
name         : rfc3686(ctr(aes))
name         : rfc4106(gcm(aes))
name         : __gcm-aes-aesni
name         : ctr(aes)
name         : __ctr-aes-aesni
name         : cbc(aes)
name         : __ecb-aes-aesni
name         : ecb(aes)
name         : __cbc-aes-aesni
name         : __ecb-aes-aesni
name         : __aes-aesni
name         : aes
name         : aes
```

- 参考
 - https://www.centos.org/docs/5/html/5.1/Deployment_Guide/s2-proc-crypto.html
