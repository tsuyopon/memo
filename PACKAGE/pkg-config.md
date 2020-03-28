# 概要
pkg-configとは、ライブラリを利用する際に必要となる各種フラグやパス等を、共通したインターフェースで提供でするための手段です。
CentOS7にはデフォルトでインストールされているようです。

pkg-config を使えば、利用者はインストール済みライブラリのメタデータ(metadata)を容易く利用することができるようになります。

pkg-configの設定は以下のようなパスのいずれかになっているかもしれません。cent7では/usr/share/pkgconfig/の方でした。
```
/usr/lib/pkgconfig/
/usr/share/pkgconfig/
```


上記に
```
$ ls /usr/share/pkgconfig/
dracut.pc  shared-mime-info.pc  udev.pc
```


# 詳細

### 設定ファイル(.pc)が存在しているパスを環境変数で指定する
PKG_CONFIG_PATHという環境変数でpkg-configの設定が配置されているパスを参照している参照先を変更することができます。
```
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH
```

### pkg-configがローカルで探索するパスを確認する

pkg-configコマンドを使って確認する方法がわからなかったので、パッケージに包括されるディレクトリやファイル名から逆引きした。
```
$ rpm -ql pkgconfig-0.27.1-4.el7.x86_64
/usr/bin/pkg-config
/usr/lib64/pkgconfig
/usr/share/aclocal/pkg.m4
/usr/share/doc/pkgconfig-0.27.1
/usr/share/doc/pkgconfig-0.27.1/AUTHORS
/usr/share/doc/pkgconfig-0.27.1/COPYING
/usr/share/doc/pkgconfig-0.27.1/NEWS
/usr/share/doc/pkgconfig-0.27.1/README
/usr/share/doc/pkgconfig-0.27.1/pkg-config-guide.html
/usr/share/man/man1/pkg-config.1.gz
/usr/share/pkgconfig
```

上記内容では以下の２つのパスを探索していることがわかる。(pkg-configの--debugなどを使うと.pcファイルを探索しているパスは確認できる)
```
/usr/lib64/pkgconfig
/usr/share/pkgconfig
```

以下は自分の環境での出力状態です。
```
$ ls /usr/lib64/pkgconfig/*
/usr/lib64/pkgconfig/com_err.pc      /usr/lib64/pkgconfig/kdb.pc          /usr/lib64/pkgconfig/libpcre.pc       /usr/lib64/pkgconfig/libselinux.pc  /usr/lib64/pkgconfig/mit-krb5-gssapi.pc
/usr/lib64/pkgconfig/expat.pc        /usr/lib64/pkgconfig/krb5-gssapi.pc  /usr/lib64/pkgconfig/libpcre16.pc     /usr/lib64/pkgconfig/libsepol.pc    /usr/lib64/pkgconfig/mit-krb5.pc
/usr/lib64/pkgconfig/gssrpc.pc       /usr/lib64/pkgconfig/krb5.pc         /usr/lib64/pkgconfig/libpcre32.pc     /usr/lib64/pkgconfig/libssl.pc      /usr/lib64/pkgconfig/openssl.pc
/usr/lib64/pkgconfig/kadm-client.pc  /usr/lib64/pkgconfig/libcrypto.pc    /usr/lib64/pkgconfig/libpcrecpp.pc    /usr/lib64/pkgconfig/libverto.pc    /usr/lib64/pkgconfig/systemd.pc
/usr/lib64/pkgconfig/kadm-server.pc  /usr/lib64/pkgconfig/liblzma.pc      /usr/lib64/pkgconfig/libpcreposix.pc  /usr/lib64/pkgconfig/libxml-2.0.pc  /usr/lib64/pkgconfig/zlib.pc
$ ls /usr/share/pkgconfig/* 
/usr/share/pkgconfig/dracut.pc  /usr/share/pkgconfig/shared-mime-info.pc  /usr/share/pkgconfig/udev.pc
```


### pkg-configに対応しているパッケージを表示する
```
$ pkg-config --list-all
libxml-2.0       libXML - libXML library version2.
systemd          systemd - systemd System and Service Manager
kdb              kdb - Kerberos database access libraries
liblzma          liblzma - General purpose data compression library
dracut           dracut - dracut
libsepol         libsepol - SELinux policy library
libpcrecpp       libpcrecpp - PCRECPP - C++ wrapper for PCRE
openssl          OpenSSL - Secure Sockets Layer and cryptography libraries and tools
libselinux       libselinux - SELinux utility library
kadm-server      kadm-server - Kerberos administration server library
udev             udev - udev
libverto         libverto - Event loop abstraction interface
libcrypto        OpenSSL-libcrypto - OpenSSL cryptography library
zlib             zlib - zlib compression library
krb5             krb5 - An implementation of Kerberos network authentication
com_err          com_err - Common error description library
libpcre          libpcre - PCRE - Perl compatible regular expressions C library with 8 bit character support
kadm-client      kadm-client - Kerberos administration client library
mit-krb5-gssapi  mit-krb5-gssapi - Kerberos implementation of the GSSAPI
mit-krb5         mit-krb5 - An implementation of Kerberos network authentication
gssrpc           gssrpc - GSSAPI RPC implementation
libpcre32        libpcre32 - PCRE - Perl compatible regular expressions C library with 32 bit character support
libpcre16        libpcre16 - PCRE - Perl compatible regular expressions C library with 16 bit character support
expat            expat - expat XML parser
libpcreposix     libpcreposix - PCREPosix - Posix compatible interface to libpcre
krb5-gssapi      krb5-gssapi - Kerberos implementation of the GSSAPI
libssl           OpenSSL-libssl - Secure Sockets Layer and cryptography libraries
shared-mime-info shared-mime-info - Freedesktop common MIME database
```


### pkg-configで取得できる内容を確認する
hコマンドで取得できる内容を表示することができます。
```
$ pkg-config -h
Usage:
  pkg-config [OPTION?]

Help Options:
  -h, --help                              Show help options

Application Options:
  --version                               output version of pkg-config
  --modversion                            output version for package
  --atleast-pkgconfig-version=VERSION     require given version of pkg-config
  --libs                                  output all linker flags
  --static                                output linker flags for static linking
  --short-errors                          print short errors
  --libs-only-l                           output -l flags
  --libs-only-other                       output other libs (e.g. -pthread)
  --libs-only-L                           output -L flags
  --cflags                                output all pre-processor and compiler flags
  --cflags-only-I                         output -I flags
  --cflags-only-other                     output cflags not covered by the cflags-only-I option
  --variable=NAME                         get the value of variable named NAME
  --define-variable=NAME=VALUE            set variable NAME to VALUE
  --exists                                return 0 if the module(s) exist
  --print-variables                       output list of variables defined by the module
  --uninstalled                           return 0 if the uninstalled version of one or more module(s) or their dependencies will be used
  --atleast-version=VERSION               return 0 if the module is at least version VERSION
  --exact-version=VERSION                 return 0 if the module is at exactly version VERSION
  --max-version=VERSION                   return 0 if the module is at no newer than version VERSION
  --list-all                              list all known packages
  --debug                                 show verbose debug information
  --print-errors                          show verbose information about missing or conflicting packages,default if --cflags or --libs given on the command line
  --silence-errors                        be silent about errors (default unless --cflags or --libsgiven on the command line)
  --errors-to-stdout                      print errors from --print-errors to stdout not stderr
  --print-provides                        print which packages the package provides
  --print-requires                        print which packages the package requires
  --print-requires-private                print which packages the package requires for static linking
```

# pkg-configコマンドでの設定取得サンプル

対応している場合にはコマンドの応答が返ってきます。いくつか出力が得られた例を記載しておきます。
--libsと--cflagsを同時に指定することも可能です。

```
$ pkg-config libcrypto --libs
-lcrypto  
```

```
$ pkg-config libssl --libs-only-l
-lssl -lcrypto  
```

```
$ pkg-config libxml-2.0 --cflags
-I/usr/include/libxml2  
```

```
$ pkg-config libxml-2.0 --cflags-only-I
-I/usr/include/libxml2  
```

```
$ pkg-config libssl --variable=prefix
/usr
```

```
$ pkg-config libxml-2.0 --print-variables 
exec_prefix
prefix
libdir
includedir
modules
```

パッケージのバージョン情報
```
$ pkg-config libcrypto --modversion
1.0.2k
```


### .pcファイルの設定を確認してみる。
以下はlibssl.pcのサンプルだが次のような可読性の高いデータ構造になっています。
```
$ cat /usr/lib64/pkgconfig/libssl.pc 
prefix=/usr
exec_prefix=${prefix}
libdir=${exec_prefix}/lib64
includedir=${prefix}/include

Name: OpenSSL-libssl
Description: Secure Sockets Layer and cryptography libraries
Version: 1.0.2k
Requires: libcrypto
Libs: -L${libdir} -lssl
Libs.private: -ldl -lz -lgssapi_krb5 -lkrb5 -lcom_err -lk5crypto
Cflags: -I${includedir} -I/usr/include
```

これらの値は次のようにして取得できる。

```
$ pkg-config libssl --libs
-lssl -lcrypto  
```

```
$ pkg-config --modversion libssl
1.0.2k
```

```
$ pkg-config --variable=libdir libssl
/usr/lib64
```

詳細は以下のmanpageを参照にすること
- https://linux.die.net/man/1/pkg-config

### pkg-configコマンド自体のデバッグ情報を出力する
読み込みんでいる.pcファイルなどのデバッグ情報を出力しますが、あまり使わないかもしれません。
```
[tsuyoshi@localhost ~]$ pkg-config libssl --debug
Error printing disabled by default, value of --print-errors: 0
Error printing disabled
Adding virtual 'pkg-config' package to list of known packages
Scanning directory '/usr/lib64/pkgconfig'
Ignoring file '.' in search directory; not a .pc file
Ignoring file '..' in search directory; not a .pc file
File 'systemd.pc' appears to be a .pc file
(snip)
File 'libssl.pc' appears to be a .pc file
Will find package 'libssl' in file '/usr/lib64/pkgconfig/libssl.pc'
File 'openssl.pc' appears to be a .pc file
Will find package 'openssl' in file '/usr/lib64/pkgconfig/openssl.pc'
File 'liblzma.pc' appears to be a .pc file
Will find package 'liblzma' in file '/usr/lib64/pkgconfig/liblzma.pc'
File 'libxml-2.0.pc' appears to be a .pc file
Will find package 'libxml-2.0' in file '/usr/lib64/pkgconfig/libxml-2.0.pc'
File 'expat.pc' appears to be a .pc file
Will find package 'expat' in file '/usr/lib64/pkgconfig/expat.pc'
Scanning directory '/usr/share/pkgconfig'
Ignoring file '.' in search directory; not a .pc file
Ignoring file '..' in search directory; not a .pc file
File 'shared-mime-info.pc' appears to be a .pc file
Will find package 'shared-mime-info' in file '/usr/share/pkgconfig/shared-mime-info.pc'
File 'dracut.pc' appears to be a .pc file
Will find package 'dracut' in file '/usr/share/pkgconfig/dracut.pc'
File 'udev.pc' appears to be a .pc file
Will find package 'udev' in file '/usr/share/pkgconfig/udev.pc'
Looking for package 'libssl'
Looking for package 'libssl-uninstalled'
Reading 'libssl' from file '/usr/lib64/pkgconfig/libssl.pc'
Parsing package file '/usr/lib64/pkgconfig/libssl.pc'
  line>prefix=/usr
 Variable declaration, 'prefix' has value '/usr'
  line>exec_prefix=${prefix}
 Variable declaration, 'exec_prefix' has value '/usr'
  line>libdir=${exec_prefix}/lib64
 Variable declaration, 'libdir' has value '/usr/lib64'
  line>includedir=${prefix}/include
 Variable declaration, 'includedir' has value '/usr/include'
  line>
  line>Name: OpenSSL-libssl
  line>Description: Secure Sockets Layer and cryptography libraries
  line>Version: 1.0.2k
  line>Requires: libcrypto
  line>Libs: -L${libdir} -lssl
  line>Libs.private: -ldl -lz -lgssapi_krb5 -lkrb5 -lcom_err -lk5crypto
Unknown keyword 'Libs.private' in '/usr/lib64/pkgconfig/libssl.pc'
  line>Cflags: -I${includedir} -I/usr/include
Path position of 'OpenSSL-libssl' is 1
Package OpenSSL-libssl has -I/usr/include in Cflags
Removing -I/usr/include from cflags for libssl
Package OpenSSL-libssl has -I/usr/include in Cflags
Removing -I/usr/include from cflags for libssl
Package OpenSSL-libssl has -L /usr/lib64 in Libs
Removing -L /usr/lib64 from libs for libssl
Adding 'libssl' to list of known packages, returning as package 'libssl'
```


# 参考URL
- pkg-config(1) - Linux man page
  - 環境変数やコマンドなどの説明もあり、このページが一番詳しいかも。pkg-configはドキュメントが少ないので
  - https://linux.die.net/man/1/pkg-config
- pkg-config wikipedia
  - https://ja.wikipedia.org/wiki/Pkg-config
- 公式サイト
  - ソースコードへのリンクはここから
  - https://www.freedesktop.org/wiki/Software/pkg-config/
  - Guide to pkg-config
    - https://people.freedesktop.org/~dbn/pkg-config-guide.html#faq
- pkg-config の手引き
  - http://goutou.mamagoto.com/%E6%89%8B%E5%BC%95%E3%81%8D/pkg-config%20%E3%81%AE%E6%89%8B%E5%BC%95%E3%81%8D


