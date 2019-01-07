# XV6とは
XV6とは、マサチューセッツ工科大の院生向け教材として、UNIX V6 を ANSI の C で書き直し、x86 CPU 向けに書き直したオペレーティングシステムです。 
講義用の資料、動画とソースコード、ビルド環境( MakeFile や QEMU オプション )などの一式が、無料で公開・配布されています。
- http://pdos.csail.mit.edu/6.828/2011/xv6.html
- http://en.wikipedia.org/wiki/Xv6
- Sphinx
  - http://pekopeko11.sakura.ne.jp/unix_v6/xv6-book/en/index.html
- doxygen
  - http://ertl.jp/~yutaka/os/xv6-doxygen/spinlock_8c_source.html

ソースコードは以下のテキストを参考に読んでいくといいようです。
- http://pdos.csail.mit.edu/6.828/2011/xv6/book-rev6.pdf
- http://pdos.csail.mit.edu/6.828/2014/xv6/book-rev8.pdf
- https://pdos.csail.mit.edu/6.828/2017/xv6/book-rev10.pdf(最新版)

# XV6を使ってみる(Fedora上にてXV6を動かしてみる)
```
$ cat /proc/version 
Linux version 3.3.4-5.fc17.x86_64 (mockbuild@x86-14.phx2.fedoraproject.org) (gcc version 4.7.0 20120504 (Red Hat 4.7.0-4) (GCC) ) #1 SMP Mon May 7 17:29:34 UTC 2012

$ mkdir UNIX_V6
$ cd UNIX_V6
```

続いて必要なパッケージをインストールします。
```
$ sudo yum install git qemu build-essential
git clone git://pdos.csail.mit.edu/xv6/xv6.git
```

ディレクトリに移動してMakefileを修正します。
```
$ cd xv6
$ vim Makefile 
QEMU = /usr/bin/qemu-system-x86_64   # コメントアウトしているのでそれを外すこと
```

以下のようにして起動することができます
```
ターミナルモードで起動する:      $ make qemu-nox 
ターミナルモードで起動する(GDB): $ make qemu-nox-gdb
Windowモードで起動する:          $ make qemu
Windowモードで起動する(GDB):     $ make qemu-gdb
```

XV6を抜ける場合には
```
$ Ctrl + A を押して、その後 Xを押す
```

XV6をwindowモードで起動した時のマウスの切り替えは
```
$ Ctrl + Alt
```

# 公式資料
- xv6トップページ
  - http://pdos.csail.mit.edu/6.828/2011/xv6.html
- 教材
  - http://pdos.csail.mit.edu/6.828/2011/xv6/book-rev6.pdf
  - http://pdos.csail.mit.edu/6.828/2014/xv6/book-rev8.pdf(最新版)
- スライド資料
  - http://www.cse.iitm.ac.in/~chester/courses/16o_os/syllabus.html

# 参考資料
- doxygenについては以下を参考のこと
  - http://ertl.jp/~yutaka/os/xv6-doxygen/dir_9ea4cef9241f1bffc3ca4a9e1d6c3cce.html
- このあたりのブログがXV6のソースコードリーディングについて解説しています。
  - http://peta.okechan.net/blog/xv6%E3%82%BD%E3%83%BC%E3%82%B9%E3%82%B3%E3%83%BC%E3%83%89%E3%83%AA%E3%83%BC%E3%83%87%E3%82%A3%E3%83%B3%E3%82%B0
- 「はじめてのOSコードリーディング」の著者が書いているブログのようです
  - http://d.hatena.ne.jp/takahirox/20120212/1329049014
- xv6実行環境構築参考資料
  - http://krakenbeal.blogspot.jp/2014/04/xv6-ubuntu.html


# 参考URL
- xv6実装の詳解(boot処理編: segmentationとpagingを中心に)
  - https://qiita.com/knknkn1162/items/cb06f19e1f999bf098a1
- xv6実装の詳解(マルチタスク処理 switching編)
  - https://qiita.com/knknkn1162/items/0bc9afc3ae304590e16c

# 簡単なコマンドを追加してみる。

xv6ディレクトリ中にhello.cを追加してみる
```
$ hello.c
#include "types.h"
#include "stat.h"
#include "user.h"
int main(int argc, char *argv[])
{
    printf(1, "hello, world\n");
    exit();
}
```

Makefile の UPROGS に _hello を追加します(一部のみ抜粋)
```
$ vim Makefile
UPROGS=\
_cat\
_echo\
_forktest\
_grep\
_hello\
_init\
_kill\
_ln\
_ls\
_mkdir\
_rm\
_sh\
_stressfs\
_usertests\
_wc\
_zombie\
```

続いて、hello.cを単体でビルドする。
```
$ make _hello
```

実行してみます。
```
$ make qemu-nox
xv6...
cpu1: starting
cpu0: starting
init: starting sh
(xv6)$ ./hello
hello, world
```

