
# 概要
glibcは標準ライブラリです。  
chown, write, ldconfig等のシステムで標準で使われているようなコマンドや各種システムコールなども含んでいます。  

glibcには何が含まれているのかといった記述に関してはwikipediaが参考になります。
- https://ja.wikipedia.org/wiki/%E6%A8%99%E6%BA%96C%E3%83%A9%E3%82%A4%E3%83%96%E3%83%A9%E3%83%AA

wikipediaよりglibcに含まれる標準ライブラリ一覧を抜粋
```
assert.h 	診断機能
complex.h 	複素数計算 (C99より追加)
ctype.h 	文字操作
errno.h 	エラー
fenv.h 	浮動小数点環境 (C99より追加)
float.h 	浮動小数点型の特性
inttypes.h 	整数型の書式の変換 (C99より追加)
iso646.h 	代替つづり(Alternate spellings) (ISO/IEC 9899/AMD1:1995 より追加)
limits.h 	整数型の大きさ
locale.h 	文化圏固有操作
math.h 	数学
setjmp.h 	非局所分岐
signal.h 	シグナル操作
stdalign.h 	アライメント (C11より追加)
stdarg.h 	可変個数の実引数
stdatomic.h 	アトミック操作 (C11より追加)
stdbool.h 	論理型および論理値 (C99より追加)
stddef.h 	共通の定義
stdint.h 	整数型 (C99より追加)
stdio.h 	入出力
stdlib.h 	一般ユーティリティ
stdnoreturn.h 	_Noreturn (C11より追加)
string.h 	文字列操作
tgmath.h 	型総称数学関数(Type-generic math) (C99より追加)
threads.h 	マルチスレッド (C11より追加)
time.h 	日付及び時間
uchar.h 	Unicodeユーティリティ (C11より追加)
wchar.h 	多バイトおよびワイド文字拡張ユーティリティ (ISO/IEC 9899/AMD1:1995 より追加)
wctype.h 	ワイド文字種分類およびワイド文字大文字小文字変換ユーティリティ (ISO/IEC 9899/AMD1:1995 より追加)
```

# 内容

### stdio.hやstring.hなどがどこにあるか?

stdio.hはstdio-common/配下にソースがあります。stdlib.hはstdlib/配下にソースがあります。

### ソースコードにロジック内容が記載されていない。。。
例えば、glibc/io/chown.c などのソースコードを見るとロジックの記載が存在しない。

```
 18 #include <errno.h>
 19 #include <stddef.h>
 20 #include <unistd.h>
 21 #include <sys/types.h>
 22 
 23 /* Change the owner and group of FILE.  */
 24 int
 25 __chown (file, owner, group)
 26      const char *file;
 27      uid_t owner;
 28      gid_t group;
 29 {
 30   if (file == NULL)
 31     {
 32       __set_errno (EINVAL);
 33       return -1;
 34     }
 35 
 36   __set_errno (ENOSYS);
 37   return -1;
 38 }
 39 libc_hidden_def (__chown)
 40 stub_warning (chown)
 41 
 42 weak_alias (__chown, chown)
```

おそらく、stub_warning(chown)のような記述が存在する場合には下記に示すsysdepsディレクトリ配下に存在しています。

```
    sysdeps/unix/sysv/linux
    sysdeps/posix
    sysdeps/i386 (or x86_64 or whatever your cpu arch is)
```

* 参考URL
	* Need help with glibc source(Stack Overflow)
		* http://stackoverflow.com/questions/6515583/need-help-with-glibc-source


### どのようなコマンドやメソッドがglibcに含まれているかoverviewしてみる。

全てというわけではないが先に示した３つのディレクトリで主に拡張子がcやSを表示すると全てではないが大概表示されていると思われる。

```
$ ls sysdeps/unix/sysv/linux/*.{c,S}
sysdeps/unix/sysv/linux/_exit.c                sysdeps/unix/sysv/linux/lseek64.c                sysdeps/unix/sysv/linux/setregid.c
sysdeps/unix/sysv/linux/accept.S               sysdeps/unix/sysv/linux/lutimes.c                sysdeps/unix/sysv/linux/setresgid.c
sysdeps/unix/sysv/linux/accept4.c              sysdeps/unix/sysv/linux/lxstat.c                 sysdeps/unix/sysv/linux/setresuid.c
sysdeps/unix/sysv/linux/adjtime.c              sysdeps/unix/sysv/linux/lxstat64.c               sysdeps/unix/sysv/linux/setreuid.c
sysdeps/unix/sysv/linux/aio_sigqueue.c         sysdeps/unix/sysv/linux/makedev.c                sysdeps/unix/sysv/linux/setrlimit64.c
sysdeps/unix/sysv/linux/bind.S                 sysdeps/unix/sysv/linux/mmap64.c                 sysdeps/unix/sysv/linux/setsockopt.S
sysdeps/unix/sysv/linux/check_native.c         sysdeps/unix/sysv/linux/mq_close.c               sysdeps/unix/sysv/linux/setsourcefilter.c
sysdeps/unix/sysv/linux/check_pf.c             sysdeps/unix/sysv/linux/mq_getattr.c             sysdeps/unix/sysv/linux/setuid.c
sysdeps/unix/sysv/linux/clock.c                sysdeps/unix/sysv/linux/mq_notify.c              sysdeps/unix/sysv/linux/shm-directory.c
sysdeps/unix/sysv/linux/clock_getcpuclockid.c  sysdeps/unix/sysv/linux/mq_open.c                sysdeps/unix/sysv/linux/shmat.c
sysdeps/unix/sysv/linux/clock_getres.c         sysdeps/unix/sysv/linux/mq_receive.c             sysdeps/unix/sysv/linux/shmctl.c
sysdeps/unix/sysv/linux/clock_gettime.c        sysdeps/unix/sysv/linux/mq_send.c                sysdeps/unix/sysv/linux/shmdt.c
sysdeps/unix/sysv/linux/clock_nanosleep.c      sysdeps/unix/sysv/linux/mq_unlink.c              sysdeps/unix/sysv/linux/shmget.c
sysdeps/unix/sysv/linux/clock_settime.c        sysdeps/unix/sysv/linux/msgctl.c                 sysdeps/unix/sysv/linux/shutdown.S
sysdeps/unix/sysv/linux/cmsg_nxthdr.c          sysdeps/unix/sysv/linux/msgget.c                 sysdeps/unix/sysv/linux/sigaction.c
sysdeps/unix/sysv/linux/connect.S              sysdeps/unix/sysv/linux/msgrcv.c                 sysdeps/unix/sysv/linux/signal.c
sysdeps/unix/sysv/linux/createthread.c         sysdeps/unix/sysv/linux/msgsnd.c                 sysdeps/unix/sysv/linux/signalfd.c
sysdeps/unix/sysv/linux/dl-brk.c               sysdeps/unix/sysv/linux/nice.c                   sysdeps/unix/sysv/linux/sigpending.c
sysdeps/unix/sysv/linux/dl-execstack.c         sysdeps/unix/sysv/linux/nscd_setup_thread.c      sysdeps/unix/sysv/linux/sigprocmask.c
sysdeps/unix/sysv/linux/dl-fxstatat64.c        sysdeps/unix/sysv/linux/ntp_gettime.c            sysdeps/unix/sysv/linux/sigqueue.c
sysdeps/unix/sysv/linux/dl-getcwd.c            sysdeps/unix/sysv/linux/ntp_gettimex.c           sysdeps/unix/sysv/linux/sigreturn.c
sysdeps/unix/sysv/linux/dl-openat64.c          sysdeps/unix/sysv/linux/open64.c                 sysdeps/unix/sysv/linux/sigstack.c
sysdeps/unix/sysv/linux/dl-opendir.c           sysdeps/unix/sysv/linux/openat.c                 sysdeps/unix/sysv/linux/sigsuspend.c
sysdeps/unix/sysv/linux/dl-origin.c            sysdeps/unix/sysv/linux/openat64.c               sysdeps/unix/sysv/linux/sigtimedwait.c
sysdeps/unix/sysv/linux/dl-sbrk.c              sysdeps/unix/sysv/linux/opendir.c                sysdeps/unix/sysv/linux/sigwait.c
sysdeps/unix/sysv/linux/dl-sysdep.c            sysdeps/unix/sysv/linux/opensock.c               sysdeps/unix/sysv/linux/sigwaitinfo.c
sysdeps/unix/sysv/linux/dl-vdso.c              sysdeps/unix/sysv/linux/pathconf.c               sysdeps/unix/sysv/linux/sleep.c
sysdeps/unix/sysv/linux/epoll_pwait.c          sysdeps/unix/sysv/linux/posix_fadvise.c          sysdeps/unix/sysv/linux/socketpair.S
sysdeps/unix/sysv/linux/eventfd.c              sysdeps/unix/sysv/linux/posix_fadvise64.c        sysdeps/unix/sysv/linux/speed.c
sysdeps/unix/sysv/linux/eventfd_read.c         sysdeps/unix/sysv/linux/posix_fallocate.c        sysdeps/unix/sysv/linux/statfs64.c
sysdeps/unix/sysv/linux/eventfd_write.c        sysdeps/unix/sysv/linux/posix_fallocate64.c      sysdeps/unix/sysv/linux/statvfs.c
sysdeps/unix/sysv/linux/faccessat.c            sysdeps/unix/sysv/linux/posix_madvise.c          sysdeps/unix/sysv/linux/statvfs64.c
sysdeps/unix/sysv/linux/fallocate.c            sysdeps/unix/sysv/linux/ppoll.c                  sysdeps/unix/sysv/linux/sync_file_range.c
sysdeps/unix/sysv/linux/fallocate64.c          sysdeps/unix/sysv/linux/pread.c                  sysdeps/unix/sysv/linux/sysconf.c
sysdeps/unix/sysv/linux/fchmodat.c             sysdeps/unix/sysv/linux/pread64.c                sysdeps/unix/sysv/linux/sysctl.c
sysdeps/unix/sysv/linux/fcntl.c                sysdeps/unix/sysv/linux/preadv.c                 sysdeps/unix/sysv/linux/syslog.c
sysdeps/unix/sysv/linux/fexecve.c              sysdeps/unix/sysv/linux/preadv64.c               sysdeps/unix/sysv/linux/system.c
sysdeps/unix/sysv/linux/fpathconf.c            sysdeps/unix/sysv/linux/prlimit.c                sysdeps/unix/sysv/linux/tcdrain.c
sysdeps/unix/sysv/linux/fstatfs64.c            sysdeps/unix/sysv/linux/prof-freq.c              sysdeps/unix/sysv/linux/tcflow.c
sysdeps/unix/sysv/linux/fstatvfs.c             sysdeps/unix/sysv/linux/profil.c                 sysdeps/unix/sysv/linux/tcflush.c
sysdeps/unix/sysv/linux/fstatvfs64.c           sysdeps/unix/sysv/linux/pselect.c                sysdeps/unix/sysv/linux/tcgetattr.c
sysdeps/unix/sysv/linux/ftime.c                sysdeps/unix/sysv/linux/pt-raise.c               sysdeps/unix/sysv/linux/tcgetpgrp.c
sysdeps/unix/sysv/linux/ftruncate64.c          sysdeps/unix/sysv/linux/pthread_getaffinity.c    sysdeps/unix/sysv/linux/tcsendbrk.c
sysdeps/unix/sysv/linux/futimens.c             sysdeps/unix/sysv/linux/pthread_getcpuclockid.c  sysdeps/unix/sysv/linux/tcsetattr.c
sysdeps/unix/sysv/linux/futimes.c              sysdeps/unix/sysv/linux/pthread_getname.c        sysdeps/unix/sysv/linux/tcsetpgrp.c
sysdeps/unix/sysv/linux/futimesat.c            sysdeps/unix/sysv/linux/pthread_kill.c           sysdeps/unix/sysv/linux/time.c
sysdeps/unix/sysv/linux/fxstat.c               sysdeps/unix/sysv/linux/pthread_setaffinity.c    sysdeps/unix/sysv/linux/timer_create.c
sysdeps/unix/sysv/linux/fxstat64.c             sysdeps/unix/sysv/linux/pthread_setname.c        sysdeps/unix/sysv/linux/timer_delete.c
sysdeps/unix/sysv/linux/fxstatat.c             sysdeps/unix/sysv/linux/pthread_sigmask.c        sysdeps/unix/sysv/linux/timer_getoverr.c
sysdeps/unix/sysv/linux/fxstatat64.c           sysdeps/unix/sysv/linux/pthread_sigqueue.c       sysdeps/unix/sysv/linux/timer_gettime.c
sysdeps/unix/sysv/linux/gai_sigqueue.c         sysdeps/unix/sysv/linux/ptrace.c                 sysdeps/unix/sysv/linux/timer_routines.c
sysdeps/unix/sysv/linux/getclktck.c            sysdeps/unix/sysv/linux/ptsname.c                sysdeps/unix/sysv/linux/timer_settime.c
sysdeps/unix/sysv/linux/getcwd.c               sysdeps/unix/sysv/linux/pwrite.c                 sysdeps/unix/sysv/linux/times.c
sysdeps/unix/sysv/linux/getdents.c             sysdeps/unix/sysv/linux/pwrite64.c               sysdeps/unix/sysv/linux/timespec_get.c
sysdeps/unix/sysv/linux/getdents64.c           sysdeps/unix/sysv/linux/pwritev.c                sysdeps/unix/sysv/linux/truncate64.c
sysdeps/unix/sysv/linux/getdirentries.c        sysdeps/unix/sysv/linux/pwritev64.c              sysdeps/unix/sysv/linux/tst-align-clone.c
sysdeps/unix/sysv/linux/getdirentries64.c      sysdeps/unix/sysv/linux/raise.c                  sysdeps/unix/sysv/linux/tst-clone.c
sysdeps/unix/sysv/linux/getdtsz.c              sysdeps/unix/sysv/linux/readahead.c              sysdeps/unix/sysv/linux/tst-fanotify.c
sysdeps/unix/sysv/linux/gethostid.c            sysdeps/unix/sysv/linux/readdir64.c              sysdeps/unix/sysv/linux/tst-getcpu.c
sysdeps/unix/sysv/linux/getipv4sourcefilter.c  sysdeps/unix/sysv/linux/readdir64_r.c            sysdeps/unix/sysv/linux/tst-getpid1.c
sysdeps/unix/sysv/linux/getloadavg.c           sysdeps/unix/sysv/linux/readonly-area.c          sysdeps/unix/sysv/linux/tst-getpid2.c
sysdeps/unix/sysv/linux/getlogin.c             sysdeps/unix/sysv/linux/reboot.c                 sysdeps/unix/sysv/linux/tst-setgetname.c
sysdeps/unix/sysv/linux/getlogin_r.c           sysdeps/unix/sysv/linux/recv.S                   sysdeps/unix/sysv/linux/ttyname.c
sysdeps/unix/sysv/linux/getpagesize.c          sysdeps/unix/sysv/linux/recvfrom.S               sysdeps/unix/sysv/linux/ttyname_r.c
sysdeps/unix/sysv/linux/getpeername.S          sysdeps/unix/sysv/linux/recvmmsg.c               sysdeps/unix/sysv/linux/ualarm.c
sysdeps/unix/sysv/linux/getpid.c               sysdeps/unix/sysv/linux/recvmsg.S                sysdeps/unix/sysv/linux/umount.S
sysdeps/unix/sysv/linux/getpriority.c          sysdeps/unix/sysv/linux/remove.c                 sysdeps/unix/sysv/linux/umount2.S
sysdeps/unix/sysv/linux/getpt.c                sysdeps/unix/sysv/linux/sa_len.c                 sysdeps/unix/sysv/linux/unlockpt.c
sysdeps/unix/sysv/linux/getrlimit64.c          sysdeps/unix/sysv/linux/sched_getaffinity.c      sysdeps/unix/sysv/linux/updwtmp.c
sysdeps/unix/sysv/linux/getsockname.S          sysdeps/unix/sysv/linux/sched_getcpu.c           sysdeps/unix/sysv/linux/usleep.c
sysdeps/unix/sysv/linux/getsockopt.S           sysdeps/unix/sysv/linux/sched_setaffinity.c      sysdeps/unix/sysv/linux/ustat.c
sysdeps/unix/sysv/linux/getsourcefilter.c      sysdeps/unix/sysv/linux/segfault.c               sysdeps/unix/sysv/linux/utimensat.c
sysdeps/unix/sysv/linux/getsysstats.c          sysdeps/unix/sysv/linux/semctl.c                 sysdeps/unix/sysv/linux/utimes.c
sysdeps/unix/sysv/linux/grantpt.c              sysdeps/unix/sysv/linux/semget.c                 sysdeps/unix/sysv/linux/utmp_file.c
sysdeps/unix/sysv/linux/if_index.c             sysdeps/unix/sysv/linux/semop.c                  sysdeps/unix/sysv/linux/vfork.c
sysdeps/unix/sysv/linux/ifaddrs.c              sysdeps/unix/sysv/linux/semtimedop.c             sysdeps/unix/sysv/linux/wait.c
sysdeps/unix/sysv/linux/ifreq.c                sysdeps/unix/sysv/linux/send.S                   sysdeps/unix/sysv/linux/wait3.c
sysdeps/unix/sysv/linux/internal_accept4.S     sysdeps/unix/sysv/linux/sendmmsg.c               sysdeps/unix/sysv/linux/waitid.c
sysdeps/unix/sysv/linux/internal_recvmmsg.S    sysdeps/unix/sysv/linux/sendmsg.S                sysdeps/unix/sysv/linux/waitpid.c
sysdeps/unix/sysv/linux/internal_sendmmsg.S    sysdeps/unix/sysv/linux/sendto.S                 sysdeps/unix/sysv/linux/xmknod.c
sysdeps/unix/sysv/linux/internal_statvfs.c     sysdeps/unix/sysv/linux/setegid.c                sysdeps/unix/sysv/linux/xmknodat.c
sysdeps/unix/sysv/linux/internal_statvfs64.c   sysdeps/unix/sysv/linux/seteuid.c                sysdeps/unix/sysv/linux/xstat.c
sysdeps/unix/sysv/linux/lddlibc4.c             sysdeps/unix/sysv/linux/setgid.c                 sysdeps/unix/sysv/linux/xstat64.c
sysdeps/unix/sysv/linux/libc_fatal.c           sysdeps/unix/sysv/linux/setgroups.c              sysdeps/unix/sysv/linux/xstatconv.c
sysdeps/unix/sysv/linux/listen.S               sysdeps/unix/sysv/linux/sethostid.c
sysdeps/unix/sysv/linux/llseek.c               sysdeps/unix/sysv/linux/setipv4sourcefilter.c


$ ls sysdeps/posix/
Makefile        dup2.c               gethostname.c   open64.c             profil.c     rename.c         signal.c      system.c        utime.c
alarm.c         euidaccess.c         getpagesize.c   opendir.c            pwrite.c     rewinddir.c      sigpause.c    sysv_signal.c   utimes.c
clock.c         fdopendir.c          gettimeofday.c  pathconf.c           pwrite64.c   seekdir.c        sigset.c      telldir.c       wait.c
clock_getres.c  flock.c              isatty.c        pause.c              pwritev.c    shm-directory.c  sigsetmask.c  tempname.c      wait3.c
closedir.c      fpathconf.c          isfdtype.c      posix_fallocate.c    pwritev64.c  shm-directory.h  sigsuspend.c  time.c          waitid.c
ctermid.c       gai_strerror-strs.h  killpg.c        posix_fallocate64.c  raise.c      shm_open.c       sigwait.c     timespec_get.c  writev.c
cuserid.c       gai_strerror.c       libc_fatal.c    pread.c              readdir.c    shm_unlink.c     sleep.c       truncate.c
dirfd.c         getaddrinfo.c        mkfifo.c        pread64.c            readdir_r.c  sigblock.c       spawni.c      ttyname.c
dirstream.h     getcwd.c             mkfifoat.c      preadv.c             readv.c      sigignore.c      sprofil.c     ttyname_r.c
dup.c           getdtsz.c            nice.c          preadv64.c           remove.c     sigintr.c        sysconf.c     ulimit.c


$ ls sysdeps/i386/*.{S,c}
sysdeps/i386/____longjmp_chk.S  sysdeps/i386/crtn.S           sysdeps/i386/lshift.S      sysdeps/i386/setjmp.S          sysdeps/i386/strpbrk.S
sysdeps/i386/__longjmp.S        sysdeps/i386/dl-procinfo.c    sysdeps/i386/memchr.S      sysdeps/i386/start.S           sysdeps/i386/strrchr.S
sysdeps/i386/add_n.S            sysdeps/i386/dl-tlsdesc.S     sysdeps/i386/memcmp.S      sysdeps/i386/stpcpy.S          sysdeps/i386/strspn.S
sysdeps/i386/addmul_1.S         sysdeps/i386/dl-trampoline.S  sysdeps/i386/memset.c      sysdeps/i386/stpncpy.S         sysdeps/i386/strtok.S
sysdeps/i386/backtrace.c        sysdeps/i386/ffs.c            sysdeps/i386/mp_clz_tab.c  sysdeps/i386/strchr.S          sysdeps/i386/strtok_r.S
sysdeps/i386/bsd-_setjmp.S      sysdeps/i386/htonl.S          sysdeps/i386/mul_1.S       sysdeps/i386/strchrnul.S       sysdeps/i386/sub_n.S
sysdeps/i386/bsd-setjmp.S       sysdeps/i386/htons.S          sysdeps/i386/rawmemchr.S   sysdeps/i386/strcspn.S         sysdeps/i386/submul_1.S
sysdeps/i386/bzero.c            sysdeps/i386/i386-mcount.S    sysdeps/i386/rshift.S      sysdeps/i386/string-inlines.c  sysdeps/i386/tlsdesc.c
sysdeps/i386/crti.S             sysdeps/i386/ldbl2mpn.c       sysdeps/i386/setfpucw.c    sysdeps/i386/strlen.c
```
