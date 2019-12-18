# 概要
rpmdevtools関連のパッケージについて
このパッケージに包括されるコマンドとしてはrpmdev-xxxxという名称となっていることが多いです。
spectoolについては、rpmdevtoolsに含まれますが、spectool.mdにあります。

手元のrpmdevtoolsパッケージのコマンド構成は次のようになっていて、基本的にはコマンドはbashやpython, perlなので気になったら中を読めば良い。
```
$ rpm -ql rpmdevtools | grep bin | xargs file
/usr/bin/annotate-output:    Bourne-Again shell script, ASCII text executable
/usr/bin/checkbashisms:      Perl script, ASCII text executable
/usr/bin/licensecheck:       Perl script, ASCII text executable
/usr/bin/manpage-alert:      Bourne-Again shell script, ASCII text executable
/usr/bin/rpmdev-bumpspec:    Python script, ASCII text executable
/usr/bin/rpmdev-checksig:    Python script, ASCII text executable
/usr/bin/rpmdev-cksum:       POSIX shell script, UTF-8 Unicode text executable
/usr/bin/rpmdev-diff:        Bourne-Again shell script, UTF-8 Unicode text executable, with very long lines
/usr/bin/rpmdev-extract:     Bourne-Again shell script, UTF-8 Unicode text executable
/usr/bin/rpmdev-md5:         POSIX shell script, UTF-8 Unicode text executable
/usr/bin/rpmdev-newinit:     Bourne-Again shell script, UTF-8 Unicode text executable
/usr/bin/rpmdev-newspec:     Bourne-Again shell script, UTF-8 Unicode text executable
/usr/bin/rpmdev-packager:    Bourne-Again shell script, UTF-8 Unicode text executable
/usr/bin/rpmdev-rmdevelrpms: Python script, UTF-8 Unicode text executable
/usr/bin/rpmdev-setuptree:   POSIX shell script, ASCII text executable
/usr/bin/rpmdev-sha1:        POSIX shell script, UTF-8 Unicode text executable
/usr/bin/rpmdev-sha224:      POSIX shell script, UTF-8 Unicode text executable
/usr/bin/rpmdev-sha256:      POSIX shell script, UTF-8 Unicode text executable
/usr/bin/rpmdev-sha384:      POSIX shell script, UTF-8 Unicode text executable
/usr/bin/rpmdev-sha512:      POSIX shell script, UTF-8 Unicode text executable
/usr/bin/rpmdev-sort:        Python script, UTF-8 Unicode text executable
/usr/bin/rpmdev-sum:         POSIX shell script, UTF-8 Unicode text executable
/usr/bin/rpmdev-vercmp:      Python script, UTF-8 Unicode text executable
/usr/bin/rpmdev-wipetree:    POSIX shell script, UTF-8 Unicode text executable
/usr/bin/rpminfo:            Bourne-Again shell script, ASCII text executable
/usr/bin/rpmls:              POSIX shell script, ASCII text executable
/usr/bin/spectool:           Perl script, UTF-8 Unicode text executable
```

# 詳細

### rpmパッケージ生成に必要なディレクトリを一括で自動生成する(rpmdev-setuptree)
rpmdev-setuptreeを引数なしで実行すると、$HOME配下にrpmbuildというディレクトリとその中に必要なディレクトリを作成します。
```
$ ls $HOME/rpmbuild
ls: cannot access /home/tsuyoshi/rpmbuild: No such file or directory
$ rpmdev-setuptree 
$ tree $HOME/rpmbuild
/home/tsuyoshi/rpmbuild
|-- BUILD
|-- RPMS
|-- SOURCES
|-- SPECS
`-- SRPMS

5 directories, 0 files
```

### ~/rpmbuildの中を綺麗にクリーンする(rpmdev-wipetree)
あらかじめ手元に次のような~/rpmbuildが存在するとします。
```
$ tree ~/rpmbuild/
/home/tsuyoshi/rpmbuild/
|-- BUILD
|   `-- moge
|-- RPMS
|   `-- hoge.rpm
|-- SOURCES
|-- SPECS
`-- SRPMS

5 directories, 2 files
```

rpmdev-wipetreeを実行すると中身が綺麗サッパリとなります。
```
$ rpmdev-wipetree
Removing all build files...
$ tree ~/rpmbuild/
/home/tsuyoshi/rpmbuild/
|-- BUILD
|-- RPMS
|-- SOURCES
|-- SPECS
`-- SRPMS

5 directories, 0 files
```

### rpmに関する情報を取得する(rpminfo)

```
$ rpminfo vim-8.0.1568-lp150.3.1.x86_64.rpm 

vim-8.0.1568-lp150.3.1.x86_64.rpm
	/usr/bin/vim-nox11	PIE
	/usr/bin/vitmp	PIE
	/usr/bin/xxd	PIE
```

全てのインストール済みパッケージを表示する。出力が大量になるので注意。別の引数-lや-r, -eなどを付与して複合探索してサンプルを探す場合に便利。
```
$ rpminfo -i

devtoolset-8-gcc-c++-8.3.1-3.1.el7.x86_64
	/opt/rh/devtoolset-8/root/usr/bin/c++	PIC
	/opt/rh/devtoolset-8/root/usr/bin/g++	PIC
	/opt/rh/devtoolset-8/root/usr/bin/x86_64-redhat-linux-c++	PIC
	/opt/rh/devtoolset-8/root/usr/bin/x86_64-redhat-linux-g++	PIC
	/opt/rh/devtoolset-8/root/usr/libexec/gcc/x86_64-redhat-linux/8/cc1plus	PIC

GeoIP-1.5.0-13.el7.x86_64
	/usr/bin/geoiplookup	PIC
	/usr/bin/geoiplookup6	PIC
	/usr/bin/geoipupdate	PIC
	/usr/lib64/libGeoIP.so.1.5.0	DSO PIC
	/usr/lib64/libGeoIPUpdate.so.0.0.0	DSO PIC

(snip)
```

以下の例では、全てのインストール済みrpmに設定されているrpathを確認する
```
$ rpminfo -i -r

binutils-2.27-34.base.el7.x86_64
	/usr/bin/ld.bfd	RPATH /usr/lib64

(snip)
```

もちろんパッケージだけ指定もできる。
```
$ rpminfo -r binutils

binutils-2.27-34.base.el7.x86_64
	/usr/bin/ld.bfd	RPATH /usr/lib64
```

ライブラリを表示する
```
$ rpminfo -l openssl-libs

openssl-libs-1.0.2k-16.el7_6.1.x86_64
	/usr/lib64/libcrypto.so.1.0.2k	DSO PIC
	/usr/lib64/libssl.so.1.0.2k	DSO PIC
	/usr/lib64/openssl/engines/lib4758cca.so	DSO PIC
	/usr/lib64/openssl/engines/libaep.so	DSO PIC
	/usr/lib64/openssl/engines/libatalla.so	DSO PIC
	/usr/lib64/openssl/engines/libcapi.so	DSO PIC
	/usr/lib64/openssl/engines/libchil.so	DSO PIC
	/usr/lib64/openssl/engines/libcswift.so	DSO PIC
	/usr/lib64/openssl/engines/libgmp.so	DSO PIC
	/usr/lib64/openssl/engines/libnuron.so	DSO PIC
	/usr/lib64/openssl/engines/libpadlock.so	DSO PIC
	/usr/lib64/openssl/engines/libsureware.so	DSO PIC
	/usr/lib64/openssl/engines/libubsec.so	DSO PIC
```

含まれるファイルのみの情報を出力する
```
$ rpminfo -q openssl-libs

openssl-libs-1.0.2k-16.el7_6.1.x86_64
	/usr/lib64/libcrypto.so.1.0.2k
	/usr/lib64/libssl.so.1.0.2k
	/usr/lib64/openssl/engines/lib4758cca.so
	/usr/lib64/openssl/engines/libaep.so
	/usr/lib64/openssl/engines/libatalla.so
	/usr/lib64/openssl/engines/libcapi.so
	/usr/lib64/openssl/engines/libchil.so
	/usr/lib64/openssl/engines/libcswift.so
	/usr/lib64/openssl/engines/libgmp.so
	/usr/lib64/openssl/engines/libnuron.so
	/usr/lib64/openssl/engines/libpadlock.so
	/usr/lib64/openssl/engines/libsureware.so
	/usr/lib64/openssl/engines/libubsec.so
```

バイナリを表示する
```
$ rpminfo -e openssl     

openssl-1.0.2k-16.el7_6.1.x86_64
	/usr/bin/openssl	PIC
```

PIEのバイナリを表示する。なお、-nPで表示しないようにすることも可能です。
```
$ rpminfo -P dbus

dbus-1.10.24-12.el7.x86_64
	/usr/bin/dbus-cleanup-sockets	PIE
	/usr/bin/dbus-daemon	PIE
	/usr/bin/dbus-monitor	PIE
	/usr/bin/dbus-run-session	PIE
	/usr/bin/dbus-send	PIE
	/usr/bin/dbus-test-tool	PIE
	/usr/bin/dbus-update-activation-environment	PIE
	/usr/bin/dbus-uuidgen	PIE
```

PICのバイナリを表示する。なお-npで表示しないようにさせることも可能です。
```
$ rpminfo -p openssl-libs

openssl-libs-1.0.2k-16.el7_6.1.x86_64
	/usr/lib64/libcrypto.so.1.0.2k	DSO PIC
	/usr/lib64/libssl.so.1.0.2k	DSO PIC
	/usr/lib64/openssl/engines/lib4758cca.so	DSO PIC
	/usr/lib64/openssl/engines/libaep.so	DSO PIC
	/usr/lib64/openssl/engines/libatalla.so	DSO PIC
	/usr/lib64/openssl/engines/libcapi.so	DSO PIC
	/usr/lib64/openssl/engines/libchil.so	DSO PIC
	/usr/lib64/openssl/engines/libcswift.so	DSO PIC
	/usr/lib64/openssl/engines/libgmp.so	DSO PIC
	/usr/lib64/openssl/engines/libnuron.so	DSO PIC
	/usr/lib64/openssl/engines/libpadlock.so	DSO PIC
	/usr/lib64/openssl/engines/libsureware.so	DSO PIC
	/usr/lib64/openssl/engines/libubsec.so	DSO PIC
```

### rpmパッケージを展開する(rpmdev-extract)

rpmを簡単に展開することができます。出力を抑制したければ-qを付与します。
```
$ rpmdev-extract capstest-1.0-1.noarch.rpm 
capstest-1.0-1.noarch/a/emptyCaps1
capstest-1.0-1.noarch/a/emptyCaps2
capstest-1.0-1.noarch/a/noCaps
```

特定のディレクトリに展開結果を配置する場合には次のようにあらかじめディレクトリを生成して、-Cで指定します。
```
$ mkdir testdir
$ rpmdev-extract -C ./testdir capstest-1.0-1.noarch.rpm 
capstest-1.0-1.noarch/a/emptyCaps1
capstest-1.0-1.noarch/a/emptyCaps2
capstest-1.0-1.noarch/a/noCaps
$ ls ./testdir/
capstest-1.0-1.noarch
```

### パッケージの中身のファイルの権限を確認する(rpmls)
```
$ rpmls capstest-1.0-1.noarch.rpm 
-rwxrwxrwx  /a/emptyCaps1
-rwxrwxrwx  /a/emptyCaps2
-rwxrwxrwx  /a/noCaps
```


### パッケージの差分を比較する(rpmdev-diff)

差分があるときは次のように表示されます。差分がなければ何も出力されません。
```
$ rpmdev-diff  hello-1.0-1.i386.rpm capstest-1.0-1.noarch.rpm 
diff -r -Nup hello-1.0-1.i386/a/emptyCaps1 capstest-1.0-1.noarch/a/emptyCaps1
--- hello-1.0-1.i386/a/emptyCaps1	1970-01-01 09:00:00.000000000 +0900
+++ capstest-1.0-1.noarch/a/emptyCaps1	2018-11-09 22:19:21.000000000 +0900
@@ -0,0 +1 @@
+x
diff -r -Nup hello-1.0-1.i386/a/emptyCaps2 capstest-1.0-1.noarch/a/emptyCaps2
--- hello-1.0-1.i386/a/emptyCaps2	1970-01-01 09:00:00.000000000 +0900
+++ capstest-1.0-1.noarch/a/emptyCaps2	2018-11-09 22:19:21.000000000 +0900
@@ -0,0 +1 @@
+x
diff -r -Nup hello-1.0-1.i386/a/noCaps capstest-1.0-1.noarch/a/noCaps
--- hello-1.0-1.i386/a/noCaps	1970-01-01 09:00:00.000000000 +0900
+++ capstest-1.0-1.noarch/a/noCaps	2018-11-09 22:19:21.000000000 +0900
@@ -0,0 +1 @@
+x
Binary files hello-1.0-1.i386/usr/local/bin/hello and capstest-1.0-1.noarch/usr/local/bin/hello differ
diff -r -Nup hello-1.0-1.i386/usr/share/doc/hello-1.0/FAQ capstest-1.0-1.noarch/usr/share/doc/hello-1.0/FAQ
--- hello-1.0-1.i386/usr/share/doc/hello-1.0/FAQ	1998-10-20 23:50:30.000000000 +0900
+++ capstest-1.0-1.noarch/usr/share/doc/hello-1.0/FAQ	1970-01-01 09:00:00.000000000 +0900
@@ -1 +0,0 @@
-This is the FAQ file for hello-1.0.
```

比較した内容のリストを得るには-lを付与します。
```
$ rpmdev-diff -l hello-1.0-1.i386.rpm capstest-1.0-1.noarch.rpm 
--- hello-1.0-1.i386.files	2019-12-19 03:10:56.371640255 +0900
+++ capstest-1.0-1.noarch.files	2019-12-19 03:10:56.380640369 +0900
@@ -1,8 +1,4 @@
-usr
-usr/local
-usr/local/bin
-usr/local/bin/hello
-usr/share
-usr/share/doc
-usr/share/doc/hello-1.0
-usr/share/doc/hello-1.0/FAQ
+a
+a/emptyCaps1
+a/emptyCaps2
+a/noCaps
```

比較した内容のリストに関する詳細を得るには-Lを付与します。
```
$ rpmdev-diff -L hello-1.0-1.i386.rpm capstest-1.0-1.noarch.rpm 
--- hello-1.0-1.i386.files	2019-12-19 03:10:37.447398872 +0900
+++ capstest-1.0-1.noarch.files	2019-12-19 03:10:37.452398935 +0900
@@ -2,8 +2,4 @@
--rw-r--r-- tsuyoshi tsuyoshi       36 Oct 20  1998 usr/share/doc/hello-1.0/FAQ
--rwxr-x--x tsuyoshi tsuyoshi     2880 Aug 19  2007 usr/local/bin/hello
-drwxr-xr-x tsuyoshi tsuyoshi       17 Dec 19 03:10 usr/share/doc/hello-1.0
-drwxrwxr-x tsuyoshi tsuyoshi       17 Dec 19 03:10 usr/local
-drwxrwxr-x tsuyoshi tsuyoshi       17 Dec 19 03:10 usr/share
-drwxrwxr-x tsuyoshi tsuyoshi       19 Dec 19 03:10 usr/local/bin
-drwxrwxr-x tsuyoshi tsuyoshi       23 Dec 19 03:10 usr/share/doc
-drwxrwxr-x tsuyoshi tsuyoshi       32 Dec 19 03:10 usr
+-rwxrwxrwx tsuyoshi tsuyoshi        2 Nov  9  2018 a/emptyCaps1
+-rwxrwxrwx tsuyoshi tsuyoshi        2 Nov  9  2018 a/emptyCaps2
+-rwxrwxrwx tsuyoshi tsuyoshi        2 Nov  9  2018 a/noCaps
+drwxrwxr-x tsuyoshi tsuyoshi       56 Dec 19 03:10 a
```

specファイルなどの差分を表示する
```
$ rpmdev-diff -m hello-1.0-1.i386.rpm capstest-1.0-1.noarch.rpm 
--- old.meta	2019-12-19 03:11:26.470024166 +0900
+++ new.meta	2019-12-19 03:11:26.491024434 +0900
@@ -1 +1 @@
-Name        : hello
+Name        : capstest
@@ -4 +4 @@
-Architecture: i386
+Architecture: noarch
@@ -6,2 +6,2 @@
-Group       : Utilities
-Size        : 2916
+Group       : Testing
+Size        : 6
@@ -10,8 +10,5 @@
-Source RPM  : hello-1.0-1.src.rpm
-Build Date  : Sun Aug 19 15:14:34 2007
-Build Host  : columbo.corsepiu.local
-Relocations : /usr 
-Packager    : Red Hat Software <bugs@redhat.com>
-Vendor      : Red Hat Software
-URL         : http://www.redhat.com
-Summary     : hello -- hello, world rpm
+Source RPM  : capstest-1.0-1.src.rpm
+Build Date  : Fri Nov  9 22:19:21 2018
+Build Host  : dell-430-41.gsslab.pnq2.redhat.com
+Relocations : (not relocatable)
+Summary     : Testing file capabilities behavior
@@ -19,3 +16,3 @@
(snip)
```

### rpmパッケージバージョンをソートする(rpmdev-sort)
パッケージ名が複数ありバージョン番号のソートを確認したいときに使えるツールのようです。
rpmdev-sortを引数なしで実行して、その後rpm名を入力します(存在しないrpmでもok)。そして、最後にCtrl + Dを押下します。
```
$ rpmdev-sort          // 引数なしで実行した後に判定したい文字名を入力する
test1.rpm
test99.rpm
testx.rpm
test43.rpm
(ここでCtrl + Dを押す)
```

Ctrl + Dでソートが開始され、次の順番で出力されました。
```
test1.rpm
test43.rpm
test99.rpm
testx.rpm
```


### パッケージ自身とその中身のmd5値を取得する(rpmdev-md5)
パッケージ自身とそれに含まれるファイルのmd5を取得することができます。
```
$ rpmdev-md5 capstest-1.0-1.noarch.rpm 
f7575e557d64f2a9530ec86fc1dcd0b9  capstest-1.0-1.noarch.rpm
401b30e3b8b5d629635a5c613cdb7919  a/emptyCaps1
401b30e3b8b5d629635a5c613cdb7919  a/emptyCaps2
401b30e3b8b5d629635a5c613cdb7919  a/noCaps
```

試しにmd5sumした以下のrpmと一致していることが確認できます。
```
$ md5sum capstest-1.0-1.noarch.rpm 
f7575e557d64f2a9530ec86fc1dcd0b9  capstest-1.0-1.noarch.rpm
```

### パッケージ自身とその中身のsha値を取得する(rpmdev-sha1, rpmdev-sha224, rpmdev-sha256  rpmdev-sha384  rpmdev-sha512)
rpmdev-md5と同じです。出力例だけ添付しておきます。

- rpmdev-sha1
```
$ rpmdev-sha1 capstest-1.0-1.noarch.rpm 
d4d444aa13062f1898b89763ef696eb06ef5a339  capstest-1.0-1.noarch.rpm
6fcf9dfbd479ed82697fee719b9f8c610a11ff2a  a/emptyCaps1
6fcf9dfbd479ed82697fee719b9f8c610a11ff2a  a/emptyCaps2
6fcf9dfbd479ed82697fee719b9f8c610a11ff2a  a/noCaps
$ sha1sum capstest-1.0-1.noarch.rpm 
d4d444aa13062f1898b89763ef696eb06ef5a339  capstest-1.0-1.noarch.rpm
```

- rpmdev-sha224
```
$ rpmdev-sha224 capstest-1.0-1.noarch.rpm
06b39468a3b01c43ff09f9980b9bbb007efcbb018ab3141dae853ded  capstest-1.0-1.noarch.rpm
f18276755ba8725bfe0e6bff764621dc562fdaba9d60308327ad55a2  a/emptyCaps1
f18276755ba8725bfe0e6bff764621dc562fdaba9d60308327ad55a2  a/emptyCaps2
f18276755ba8725bfe0e6bff764621dc562fdaba9d60308327ad55a2  a/noCaps
$ sha224sum capstest-1.0-1.noarch.rpm
06b39468a3b01c43ff09f9980b9bbb007efcbb018ab3141dae853ded  capstest-1.0-1.noarch.rpm
```

以下の３つも同じなので載せません
- rpmdev-sha256 
- rpmdev-sha384
- rpmdev-sha512 

### バージョン番号を比較する(rpmdev-vercmp)
バージョン番号の比較を行います。
```
$ rpmdev-vercmp hello-1.0-1.i386.rpm hello-2.0-1.i686.rpm
hello-1.0-1.i386.rpm < hello-2.0-1.i686.rpm
```

archのみの違いや別のパッケージでも判定できます。
```
$ rpmdev-vercmp hello-1.0-1.i386.rpm hello-1.0-1.ppc64.rpm 
hello-1.0-1.i386.rpm < hello-1.0-1.ppc64.rpm
$ rpmdev-vercmp hello-1.0-1.i386.rpm foo-1.0-1.noarch.rpm 
hello-1.0-1.i386.rpm > foo-1.0-1.noarch.rpm
```

同じパッケージだと==と出力されます。
```
$ rpmdev-vercmp hello-1.0-1.i386.rpm hello-1.0-1.i386.rpm 
hello-1.0-1.i386.rpm == hello-1.0-1.i386.rpm
```

# 参考URL
- ソースコード
  - https://pagure.io/rpmdevtools
- Package rpmdevtools
  - rpmdev-xxx関連等のコマンドのmanpage
  - https://www.mankier.com/package/rpmdevtools
