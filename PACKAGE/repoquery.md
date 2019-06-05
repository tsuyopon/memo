# 概要
repoqueryコマンドの使い方についてまとめます。
repoqueryを使うことで、yumの出力結果などで取得できる項目を出力自在にできるのでシェルスクリプト用途などで利用できます。

repoqueryコマンド自身が存在しない場合には次のコマンドでインストールします。
```
$ sudo yum install yum-utils
```

# 詳細

### パッケージの情報を表示する
```
$ repoquery -i curl

Name        : curl
Version     : 7.29.0
Release     : 51.el7
Architecture: x86_64
Size        : 540293
Packager    : CentOS BuildSystem <http://bugs.centos.org>
Group       : Applications/Internet
URL         : http://curl.haxx.se/
Repository  : base
Summary     : A utility for getting files from remote servers (FTP, HTTP, and others)
Source      : curl-7.29.0-51.el7.src.rpm
Description :
curl is a command line tool for transferring data with URL syntax, supporting
FTP, FTPS, HTTP, HTTPS, SCP, SFTP, TFTP, TELNET, DICT, LDAP, LDAPS, FILE, IMAP,
SMTP, POP3 and RTSP.  curl supports SSL certificates, HTTP POST, HTTP PUT, FTP
uploading, HTTP form based upload, proxies, cookies, user+password
authentication (Basic, Digest, NTLM, Negotiate, kerberos...), file transfer
resume, proxy tunneling and a busload of other useful tricks.
```

### ファイルが所属するパッケージを表示する
```
$ repoquery -q --file /usr/bin/yum
yum-0:3.4.3-161.el7.centos.noarch
```

### 依存関係のあるライブラリを表示する
```
$ repoquery --requires --resolve curl
nss-0:3.36.0-7.el7_5.x86_64
nspr-0:4.19.0-1.el7_5.x86_64
libcurl-0:7.29.0-51.el7.x86_64
nss-util-0:3.36.0-1.1.el7_6.x86_64
glibc-0:2.17-260.el7_6.5.i686
zlib-0:1.2.7-18.el7.x86_64
glibc-0:2.17-260.el7_6.5.x86_64
libcurl-0:7.29.0-51.el7.i686
```

上記パッケージ全てを再帰的に表示するにはrecursiveオプションをつけますが、出力が大量になります。
```
$ repoquery --requires --resolve --recursive curl
```

### 依存関係のあるライブラリを表示する
```
$ repoquery --requires curl
libc.so.6(GLIBC_2.17)(64bit)
libcurl = 7.29.0-51.el7
libcurl.so.4()(64bit)
libdl.so.2()(64bit)
libnspr4.so()(64bit)
libnss3.so()(64bit)
libnssutil3.so()(64bit)
libplc4.so()(64bit)
libplds4.so()(64bit)
libpthread.so.0()(64bit)
libpthread.so.0(GLIBC_2.2.5)(64bit)
libsmime3.so()(64bit)
libssl3.so()(64bit)
libz.so.1()(64bit)
rtld(GNU_HASH)
```


### 調べたいパッケージを確認する
```
$ repoquery --list curl
/usr/bin/curl
/usr/share/doc/curl-7.29.0
/usr/share/doc/curl-7.29.0/BUGS
/usr/share/doc/curl-7.29.0/CHANGES
/usr/share/doc/curl-7.29.0/COPYING
/usr/share/doc/curl-7.29.0/FAQ
/usr/share/doc/curl-7.29.0/FEATURES
/usr/share/doc/curl-7.29.0/MANUAL
/usr/share/doc/curl-7.29.0/README
/usr/share/doc/curl-7.29.0/RESOURCES
/usr/share/doc/curl-7.29.0/TODO
/usr/share/doc/curl-7.29.0/TheArtOfHttpScripting
/usr/share/man/man1/curl.1.gz
```

### 特的のアーキテクチャ
一般的なx86_64の全パッケージを表示する場合
```
$ repoquery -q --archlist=x86_64 -a
```

### パッケージがrequireしているパッケージも含めて表示する
以下ではインストール済みに限定して表示している
```
$ repoquery --pkgnarrow=installed -q --whatrequires gcc
gcc-0:4.8.5-16.el7.x86_64
gcc-c++-0:4.8.5-16.el7.x86_64
gcc-gfortran-0:4.8.5-16.el7.x86_64
lcov-0:1.13-1.el7.noarch
libquadmath-devel-0:4.8.5-16.el7.x86_64
libtool-0:2.4.2-22.el7_3.x86_64
systemtap-devel-0:3.1-3.el7.x86_64
```

### 出力を加工してみる
```
$ repoquery --all --pkgnarrow=installed --qf="%{name}.%{arch}  %{version}-%{release}  %{repo}"  
GeoIP.x86_64  1.5.0-11.el7  installed
NetworkManager.x86_64  1.8.0-9.el7  installed
NetworkManager-libnm.x86_64  1.8.0-9.el7  installed
NetworkManager-team.x86_64  1.8.0-9.el7  installed
NetworkManager-tui.x86_64  1.8.0-9.el7  installed
NetworkManager-wifi.x86_64  1.8.0-9.el7  installed
...
```


### パッケージの依存ツリーを表示する
curlだけですがあまりに出力が膨大です。
```
$  repoquery --tree-requires curl
curl-0:7.29.0-51.el7.x86_64 [cmd line]
 \_  glibc-0:2.17-260.el7_6.5.i686 [1: rtld(GNU_HASH)]
 |   \_  basesystem-0:10.0-7.el7.centos.noarch [1: basesystem]
 |   |   \_  filesystem-0:3.2-25.el7.x86_64 [1: filesystem]
 |   |   |   \_  bash-0:4.2.46-31.el7.x86_64 [1: /bin/sh]

(snip)
```


### ヘルプオプションを確認する
```
$ repoquery --help
Usage: repoquery [options]

Options:
  --version             show program's version number and exit
  -h, --help            show this help message and exit
  -l, --list            list files in this package/group
  -i, --info            list descriptive info from this package/group
  -f, --file            query which package provides this file
  --qf=QUERYFORMAT, --queryformat=QUERYFORMAT
                        specify a custom output format for queries
  --groupmember         list which group(s) this package belongs to
  -q, --query           no-op for rpmquery compatibility
  -a, --all             query all packages/groups
  -R, --requires        list package dependencies
  --provides            list capabilities this package provides
  --obsoletes           list other packages obsoleted by this package
  --conflicts           list capabilities this package conflicts with
  --changelog           show changelog for this package
  --location            show download URL for this package
  --nevra               show name-epoch:version-release.architecture info of
                        package
  --envra               show epoch:name-version-release.architecture info of
                        package
  --nvr                 show name, version, release info of package
  -s, --source          show package source RPM name
  --srpm                operate on corresponding source RPM
  --resolve             resolve capabilities to originating package(s)
  --alldeps             check non-explicit dependencies (files and Provides:)
                        as well, defaults to on
  --exactdeps           check dependencies exactly as given, opposite of
                        --alldeps
  --recursive           recursively query for packages (for whatrequires)
  --whatprovides        query what package(s) provide a capability
  --whatrequires        query what package(s) require a capability
  --whatobsoletes       query what package(s) obsolete a capability
  --whatconflicts       query what package(s) conflicts with a capability
  -g, --group           query groups instead of packages
  --grouppkgs=GROUPPKGS
                        filter which packages (all,optional etc) are shown
                        from groups
  --archlist=ARCHLIST   only query packages of certain architecture(s)
  --releasever=RELEASEVER
                        set value of $releasever in yum config and repo files
  --pkgnarrow=PKGNARROW
                        limit query to installed / available / recent /
                        updates / extras / all (available + installed) /
                        repository (default) packages
  --installed           limit query to installed pkgs only
  --show-duplicates     show all versions of packages
  --repoid=REPOID       specify repoids to query, can be specified multiple
                        times (default is all enabled)
  --enablerepo=ENABLEREPOS
                        specify additional repoids to query, can be specified
                        multiple times
  --disablerepo=DISABLEREPOS
                        specify repoids to disable, can be specified multiple
                        times
  --repofrompath=REPOFROMPATH
                        specify repoid & paths of additional repositories -
                        unique repoid and complete path required, can be
                        specified multiple times. Example.
                        --repofrompath=myrepo,/path/to/repo
  --plugins             enable yum plugin support
  --quiet               quiet output, only error output to stderr (default
                        enabled)
  --verbose             verbose output (opposite of quiet)
  -C, --cache           run from cache only
  --tempcache           use private cache (default when used as non-root)
  --querytags           list available tags in queryformat queries
  -c CONFFILE, --config=CONFFILE
                        config file location
  --level=TREE_LEVEL    levels to display (can be any number or 'all', default
                        to 'all')
  --output=OUTPUT       output format to use (can be text|ascii-tree|dot-tree,
                        default to 'text')
  --search              Use yum's search to return pkgs
  --search-fields=SEARCHFIELDS
                        search fields to search using --search
  --installroot=INSTALLROOT
                        set install root
  --setopt=SETOPTS      set arbitrary config and repo options
```


