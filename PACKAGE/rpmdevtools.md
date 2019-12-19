TODO: 時間があれば、不足しているコマンドを追加する

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

なお、以下のパスにrpmdevtools用の設定フィアルが存在しているようです。
```
$ ls  /etc/rpmdevtools/
devscripts.conf  rmdevelrpms.conf     spectemplate-dummy.spec  spectemplate-minimal.spec  spectemplate-perl.spec      spectemplate-python.spec  template.init
newspec.conf     spectemplate-R.spec  spectemplate-lib.spec    spectemplate-ocaml.spec    spectemplate-php-pear.spec  spectemplate-ruby.spec
```

# 詳細

### shがbashの記法に依存していないかどうかを確認する(checkbashisms)
以下のshスクリプトがあるとします。
```
$ cat hogehoge.sh 
#!/bin/sh
source hogehoge
```

checkbashismsでshファイルがbashに依存した記述になっていないかどうかをチェックできます。
```
$ checkbashisms hogehoge.sh
possible bashism in hogehoge.sh line 2 (should be '.', not 'source'):
source hogehoge
```

### 出力にannotationを付与する(annotate-output)
以下の例ではvmstatを3秒ごとに5回実行しているが、出力に時刻が付与されていることが確認できる。またシンボルも表示される。
```
$ annotate-output vmstat -n 3 5
09:48:43 I: Started vmstat -n 3 5
09:48:43 O: procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
09:48:43 O: r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
09:48:43 O: 1  0      0 3496404   2108 176516    0    0   299    10   88  224  0  1 99  0  0
09:48:46 O: 0  0      0 3496156   2108 176548    0    0     0     0   34   62  0  0 100  0  0
09:48:49 O: 1  0      0 3496156   2108 176548    0    0     0     0   31   59  0  0 100  0  0
09:48:52 O: 0  0      0 3496156   2108 176548    0    0     0     0   33   60  0  0 100  0  0
09:48:55 O: 0  0      0 3496156   2108 176548    0    0     0     0   32   59  0  0 100  0  0
09:48:55 I: Finished with exitcode 0
```

上記で出力されるシンボルには次のような意味があります。
- I: おそらく最初と最後
- O: stdout
- E: stderr

- 参考
  - https://linux.die.net/man/1/annotate-output


### ディレクトリを指定してコマンドにmanpageが存在するかを確認する(manpage-alert)
引数にはディレクトリを指定します。
以下の例では/usr/sbin中には440個のコマンドがあるが、34個のマニュアルが見つからないということでそのコマンドも表示してくれています。
```
$ ls /usr/sbin/* | wc -l
440
$ manpage-alert /usr/sbin/
No manual entry for /usr/sbin/build-locale-archive
No manual entry for /usr/sbin/ebtables-restore
No manual entry for /usr/sbin/ebtables-save
No manual entry for /usr/sbin/glibc_post_upgrade.x86_64
No manual entry for /usr/sbin/grub2-get-kernel-settings
No manual entry for /usr/sbin/gss-server
No manual entry for /usr/sbin/iconvconfig
No manual entry for /usr/sbin/iconvconfig.x86_64
No manual entry for /usr/sbin/ldconfig
No manual entry for /usr/sbin/mkdict
No manual entry for /usr/sbin/nl-class-add
No manual entry for /usr/sbin/nl-class-delete
No manual entry for /usr/sbin/nl-class-list
No manual entry for /usr/sbin/nl-cls-add
No manual entry for /usr/sbin/nl-cls-delete
No manual entry for /usr/sbin/nl-cls-list
No manual entry for /usr/sbin/nl-link-list
No manual entry for /usr/sbin/packer
No manual entry for /usr/sbin/pdata_tools
No manual entry for /usr/sbin/sasldblistusers2
No manual entry for /usr/sbin/saslpasswd2
No manual entry for /usr/sbin/selabel_digest
No manual entry for /usr/sbin/selabel_lookup
No manual entry for /usr/sbin/selabel_lookup_best_match
No manual entry for /usr/sbin/selabel_partial_match
No manual entry for /usr/sbin/selinux_restorecon
No manual entry for /usr/sbin/sim_server
No manual entry for /usr/sbin/sln
No manual entry for /usr/sbin/sshd-keygen
No manual entry for /usr/sbin/uuserver
No manual entry for /usr/sbin/weak-modules
No manual entry for /usr/sbin/xtables-multi
No manual entry for /usr/sbin/zdump
No manual entry for /usr/sbin/zic
Of 440 commands, found manpages for 406 (34 missing).
```

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


### specファイルの雛形を生成する(rpmdev-newspec)
引数なしでrpmdev-newspecを実行するとnewpackage.specが生成されます。たとえば、hogeと引数を入れるとhoge.specが生成されます。
```
$ rpmdev-newspec 
newpackage.spec created; type minimal, rpm version >= 4.11.
$ ls
newpackage.spec
```

中身を見てみます。
```
$ cat newpackage.spec 
Name:           
Version:        
Release:        1%{?dist}
Summary:        

License:        
URL:            
Source0:        

BuildRequires:  
Requires:       

%description


%prep
%setup -q


%build
%configure
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
%make_install


%files
%doc



%changelog
```

### サービス起動用の雛形のスクリプトファイルを作成する(rpmdev-init)
以下のサンプルをinitスクリプトの雛形として生成してくれるようです。
```
/etc/rpmdevtools/template.init
```

たとえば、mytestと引数を指定するとmytest.initが生成されます。
```
$ rpmdev-newinit mytest
Skeleton init script has been created to "mytest.init".
$ ls mytest.init 
mytest.init
```

中身を見てみます。出力量が多いので一部snipしています。
```
$ cat mytest.init
(snip)
# Source function library.
. /etc/rc.d/init.d/functions

exec="/usr/sbin/mytest"
(snip)

[ -e /etc/sysconfig/$prog ] && . /etc/sysconfig/$prog

lockfile=/var/lock/subsys/$prog

start() {
    echo -n $"Starting $prog: "
    # if not running, start it up here, usually something like "daemon $exec"
    retval=$?
    echo
    [ $retval -eq 0 ] && touch $lockfile
    return $retval
}

stop() {
    echo -n $"Stopping $prog: "
    # stop it here, often "killproc $prog"
    retval=$?
    echo
    [ $retval -eq 0 ] && rm -f $lockfile
    return $retval
}

restart() {
    stop
    start
}

case "$1" in
    start|stop|restart)
        $1
        ;;
    force-reload)
        restart
        ;;
    status)
(snip)
```

- manpage
  - https://linux.die.net/man/1/rpmdev-newinit

### specへrpmバージョン番号およびChangeLog情報を追加する(rpmdev-bumpspec)

あらかじめspecを保存しておいて、rpmdev-bumpspec実行前と実行後でspecファイルの差分を確認してみます。
バージョン番号をインクリメントして、ChangeLogへのコメント追加も勝手に行ってくれるようです。ユーザー名は何もオプションが指定されないとrpmdev-packagerから取得しているようです。
```
$ cp test.spec test.spec.orig
$ rpmdev-bumpspec test.spec 
$ diff test.spec test.spec.orig 
3c3
< Release:    4.1
---
> Release:    3.1
27,29d26
< * Wed Dec 18 2019 tsuyoshi - 1-4.1
< - rebuilt
< 
```

ChangeLogへのコメントはもちろん変更できます。
- https://docs.fedoraproject.org/en-US/Fedora_Draft_Documentation/0.1/html-single/Packagers_Guide/index.html
```
$ rpmdev-bumpspec --comment="Initial RPM release" --userstring="John Doe <jdoe@example.com>" test.spec
$ diff test.spec test.spec.orig
3c3
< Release:    5.1
---
> Release:    4.1
27,29d26
< * Wed Dec 18 2019 John Doe <jdoe@example.com> - 1-5.1
< - Initial RPM release
< 
```

上記の例では4.1から5.1とmajorバージョンが挙げられていますが、これをminor部分を変更するには-rオプションを追加します。。以下は4.1からの差分です。
```
$ rpmdev-bumpspec --comment="This is minor version change" --userstring="Tsuyoshi <tsuyoshi@example.com>" -r test.spec
$ diff test.spec test.spec.orig
3c3
< Release:    4.2
---
> Release:    4.1
27,29d26
< * Wed Dec 18 2019 Tsuyoshi <tsuyoshi@example.com> - 1-4.2
< - This is minor version change
< 
```

次はstringオプションを見る。このオプションは覚えておく価値がある。
```
$ rpmdev-bumpspec --comment="--string option test" --userstring="tsuyoshi <tsuyoshi@example.com>" --string="XXXXX" test.spec
$ diff test.spec test.spec.orig
3c3
< Release:    3.1.XXXXX1
---
> Release:    3.1
27,29d26
< * Wed Dec 18 2019 tsuyoshi <tsuyoshi@example.com> - 1-3.1.XXXXX1
< - --string option test
< 
```

上記の出力結果を保存して、次は--stringを除いて実行してみる。3.1から4.1にメジャーはインクリメントされるが、XXXXX1は変わらない。
```
$ cp test.spec test.spec.orig2
$ rpmdev-bumpspec --comment="continue without string option test" --userstring="tsuyoshi <tsuyoshi@example.com>" test.spec
$ diff test.spec test.spec.orig2 
3c3
< Release:    4.1.XXXXX1
---
> Release:    3.1.XXXXX1
27,29d26
< * Wed Dec 18 2019 tsuyoshi <tsuyoshi@example.com> - 1-4.1.XXXXX1
< - continue without string option test
< 
```

再度先ほどと同じ--string="XXXXX"を付与して実行する。4.1から4.1のままメジャーは変わらず、XXXXX1からXXXXX2にインクリメントしている。
```
$ cp test.spec test.spec.orig3
$ rpmdev-bumpspec --comment="continue --string again" --userstring="tsuyoshi <tsuyoshi@example.com>" --string="XXXXX" test.spec
$ diff test.spec test.spec.orig3 
3c3
< Release:    4.1.XXXXX2
---
> Release:    4.1.XXXXX1
27,29d26
< * Wed Dec 18 2019 tsuyoshi <tsuyoshi@example.com> - 1-4.1.XXXXX2
< - continue --string again
< 
```

今度は、上記のspecに対して、--string="YYYYY"という別の文字列を付与してみる。4.1.XXXXX2の後にYYYYY1が付与されたことがわかる。
```
$ cp test.spec test.spec.orig4
$ rpmdev-bumpspec --comment="continue --string again" --userstring="tsuyoshi <tsuyoshi@example.com>" --string="YYYYY" test.spec
$ diff test.spec test.spec.orig4 
3c3
< Release:    4.1.XXXXX2.YYYYY1
---
> Release:    4.1.XXXXX2
27,29d26
< * Wed Dec 18 2019 tsuyoshi <tsuyoshi@example.com> - 1-4.1.XXXXX2.YYYYY1
< - continue --string again
< 
```

- manpage
  - https://linux.die.net/man/1/rpmdev-bumpspec

### 開発用パッケージの操作を行う(rpmdev-rmdevelrpms)
lオプションでインストールされている開発用パッケージの表示を行う。
デフォルトで表示されるのは-devel, -sdk, -static, --debuginfoなどで、これらに追加しようとするのであれば/etc/rpmdevtools/rmdevelrpms.confを修正すればよいようです。
```
$ rpmdev-rmdevelrpms -l
autoconf-2.69-11.el7.noarch
automake-1.13.4-3.el7.noarch
bison-3.0.4-2.el7.x86_64
cmake-2.8.12.2-2.el7.x86_64
devtoolset-8-libstdc++-devel-8.3.1-3.1.el7.x86_64
expat-devel-2.1.0-10.el7_3.x86_64
flex-2.5.37-6.el7.x86_64
gettext-0.19.8.1-2.el7.x86_64
keyutils-libs-devel-1.5.8-3.el7.x86_64
krb5-devel-1.15.1-37.el7_6.x86_64
libcom_err-devel-1.42.9-13.el7.x86_64
libgo-devel-4.8.5-36.el7_6.2.x86_64
libselinux-devel-2.5-14.1.el7.x86_64
libsepol-devel-2.5-10.el7.x86_64
libtool-2.4.2-22.el7_3.x86_64
libverto-devel-0.2.5-4.el7.x86_64
libxml2-devel-2.9.1-6.el7_2.3.x86_64
m4-1.4.16-10.el7.x86_64
nasm-2.10.07-7.el7.x86_64
openssl-devel-1.0.2k-16.el7_6.1.x86_64
pcre-devel-8.32-17.el7.x86_64
perl-Test-Harness-3.28-3.el7.noarch
pkgconfig-0.27.1-4.el7.x86_64
tcl-devel-8.5.13-8.el7.x86_64
texinfo-5.1-5.el7.x86_64
xz-devel-5.2.2-1.el7.x86_64
zlib-devel-1.2.7-18.el7.x86_64
```

実行したことは無いが、以下で不要な開発用パッケージを削除できる(root権限が必要)。
```
$ rpmdev-rmdevelrpms -y
```

- 参考
  - https://www.systutorials.com/docs/linux/man/8-rpmdev-rmdevelrpms/

### rpm開発者を推測する (rpmdev-packager)
rpm開発者と思われる情報を出力してくれます。基本的に引数なしで実行します。
```
$ rpmdev-packager
tsuyoshi
```

内部ロジックでは次のような複数の情報をチェックして開発者を推測しているようです。
```
$ rpmdev-packager -h
rpmdev-packager guesses rpm packager info from various sources:

  $RPM_PACKAGER   from environment (full name + email address)
  %packager       from rpm configuration (full name + email address)
  /etc/passwd     gecos (full name)
  certificates    ~/.fedora.cert (email address)
  $MAILTO         from environment (email address)

Usage: rpmdev-packager [option]...

Options:
  -h, --help      Show help message and exit.
  -v, --version   Print version information and exit.

Report bugs at <https://bugzilla.redhat.com/>, component rpmdevtools,
or at <https://fedorahosted.org/rpmdevtools/>.
```

### rpmの署名のgpgが登録されているかどうかを確認する(rpmdev-checksig)
署名が設定されていて、gpg鍵が署名が入っているかどうかは次のコマンドで確認することができます。
```
$ rpmdev-checksig vim-8.0.1568-lp150.3.1.x86_64.rpm
vim-8.0.1568-lp150.3.1.x86_64.rpm: MISSING KEY - 3dbdc284
```

登録されているgpgの公開鍵は次で確認できます。
```
$ rpm -qa gpg-pubkey*
gpg-pubkey-f4a80eb5-53a7ff4b
gpg-pubkey-352c64e5-52ae6884
gpg-pubkey-34fa74dd-540237d4
gpg-pubkey-f2ee9d55-560cfc0a
```

gpg鍵はrpmfindだと以下の場所に配置されているので、インポートする必要があります。
- http://rpmfind.net/linux/centos/

なお、署名が設定されていないパッケージの場合にはNoneと表示されます。
```
$ rpmdev-checksig hello-2.0-1.i686.rpm
hello-2.0-1.i686.rpm: MD5 - None - <None>
```

### パッケージ自身とその中身のsum値を取得する(rpmdev-sum)
パッケージ自身とそれに含まれるファイルのsumを取得することができます。
```
$ /usr/bin/rpmdev-sum hello-1.0-1.i386.rpm 
27332     5
21477     3 usr/local/bin/hello
12603     1 usr/share/doc/hello-1.0/FAQ
```

試しにsumした以下のrpmと一致していることが確認できます。
```
$ sum hello-1.0-1.i386.rpm 
27332     5
```

### パッケージ自身とその中身のcksum値を取得する(rpmdev-cksum)
パッケージ自身とそれに含まれるファイルのcksumを取得することができます。 rpmdev-sumと使い方は同じ
```
$ /usr/bin/rpmdev-cksum hello-1.0-1.i386.rpm 
4135240491 4410 hello-1.0-1.i386.rpm
1476200091 2880 usr/local/bin/hello
2093171843 36 usr/share/doc/hello-1.0/FAQ
```

試しにcksumした以下のrpmと一致していることが確認できます。
```
$ cksum hello-1.0-1.i386.rpm
4135240491 4410 hello-1.0-1.i386.rpm
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
rpmdev-cksum, rpmdev-md5と同じです。出力例だけ添付しておきます。

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


# 参考URL
- ソースコード
  - https://pagure.io/rpmdevtools
- Package rpmdevtools
  - rpmdev-xxx関連等のコマンドのmanpage
  - https://www.mankier.com/package/rpmdevtools

# TODO
- licensecheckコマンドの使い方だけまだ不明
