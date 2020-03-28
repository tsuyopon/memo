# 概要
ソフトウェアコレクション(SCL)に関連するコマンドについて

以下のコマンドでツールをダウンロードしてください。
```
# yum install scl-utils scl-utils-build
```

上記scl-utils系パッケージ中に含まれるファイルは少ししかありません。

```
$ rpm -ql scl-utils
/etc/bash_completion.d/scl.bash
/etc/scl/conf
/etc/scl/prefixes
/opt/rh
/usr/bin/scl
/usr/bin/scl_enabled
/usr/bin/scl_source
/usr/share/man/man1/scl.1.gz

$ rpm -ql scl-utils-build
/etc/rpm/macros.scl
/usr/lib/rpm/brp-scl-compress
/usr/lib/rpm/brp-scl-python-bytecompile
/usr/lib/rpm/fileattrs/scl.attr
/usr/lib/rpm/scldeps.sh
```

# 詳細

### SCLパッケージ一覧を表示する
```
$ scl --list 
devtoolset-8
rh-python36
```

コレクション中のパッケージを全て表示するにはlistオプションの後にパッケージ名を指定します。
```
$ scl --list devtoolset-8
devtoolset-8-gdb-8.2-3.el7.x86_64
devtoolset-8-make-4.2.1-4.el7.x86_64
devtoolset-8-runtime-8.1-1.el7.x86_64
devtoolset-8-binutils-2.30-54.el7.x86_64
devtoolset-8-gcc-c++-8.3.1-3.1.el7.x86_64
devtoolset-8-libstdc++-devel-8.3.1-3.1.el7.x86_64
devtoolset-8-gcc-8.3.1-3.1.el7.x86_64
```

### ソフトウェアコレクションの制御下で特定のコマンドを実行する
```
$ scl enable devtoolset-8 'which gcc'
/opt/rh/devtoolset-8/root/usr/bin/gcc
$ scl enable devtoolset-8 'gcc --version'
gcc (GCC) 8.3.1 20190311 (Red Hat 8.3.1-3)
Copyright (C) 2018 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

### ファイルに記載されているコマンドをソフトウェアコレクションに引き渡す
```
$ cat cmd | scl enable devtoolset-8 - 
```

### ソフトウェアコレクションをbash上で有効にする。
以下のコマンドでは2つのdevtoolset-8とrh-python36をbash上で有効にします。
```
$ scl enable devtoolset-8 rh-python36 bash 
```


### 現在のシェル上でソフトウェアコレクションを有効化する

scl_sourceスクリプトを経由して起動するのが望ましい。
```
$ source scl_source enable devtoolset-8
```

scl_sourceスクリプトを経由しないで以下のコマンドをそのまま実行すると、X_SCLSなどの環境変数が適切に設定されません。
```
$ source /opt/rh/devtoolset-8/enable
```

よって、SCLの場合にはscl_source経由で起動させるのが作法となっているようです。

- 参考
  - https://access.redhat.com/solutions/527703


### 現在のソフトウェアコレクションを取得する
X_SCLS環境変数を確認すると、現在enabledとなっているソフトウェアコレクションを表示します。
どのソフトウェアコレクションもenabledとなっていない場合には空行を表示します。
```
$ echo $X_SCLS 

$ scl enable devtoolset-8 rh-python36 bash
$ echo $X_SCLS 
devtoolset-8 rh-python36
```

### %globalで定義されたmacro
scl-utils-buildパッケージ中にはマクロが含まれていて、その中ではscl用の変数が定義されています。
```
$ grep "^%global" /etc/rpm/macros.scl
%global debug_package %{expand:
%global pkg_name		%1
%global scl_name		%{scl}
%global scl_prefix		%{scl}-
%global scl_runtime		%{scl}-runtime
%global _scl_scripts		%{_scl_prefix}/%{scl}
%global _scl_root		%{_scl_prefix}/%{scl}/root
%global _root_prefix		%{_prefix}
%global _root_exec_prefix	%{_root_prefix}
%global _root_bindir		%{_exec_prefix}/bin
%global _root_sbindir		%{_exec_prefix}/sbin
%global _root_libexecdir	%{_exec_prefix}/libexec
%global _root_datadir		%{_prefix}/share
%global _root_sysconfdir	%{_sysconfdir}
%global _root_sharedstatedir	%{_prefix}/com
%global _root_localstatedir	%{_localstatedir}
%global _root_libdir		%{_exec_prefix}/%{_lib}
%global _root_includedir	%{_prefix}/include
%global _root_infodir		%{_datadir}/info
%global _root_mandir		%{_datadir}/man
%global _root_initddir		%{_sysconfdir}/rc.d/init.d
%global _prefix			%{_scl_root}/usr
%global _exec_prefix		%{_prefix}
%global _bindir			%{_exec_prefix}/bin
%global _sbindir		%{_exec_prefix}/sbin
%global _libexecdir		%{_exec_prefix}/libexec
%global _datadir		%{_prefix}/share
%global _sysconfdir		%{_scl_root}/etc
%global _sharedstatedir		%{_scl_root}/var/lib
%global _localstatedir		%{_scl_root}/var
%global _libdir			%{_exec_prefix}/%{_lib}
%global _includedir		%{_prefix}/include
%global _infodir		%{_datadir}/info
%global _mandir			%{_datadir}/man
%global _docdir			%{_datadir}/doc
%global _defaultdocdir		%{_docdir}
%global scl_pkg_name		%{scl}-%{pkg_name}
%global __os_install_post %{expand:
```



# 参考URL
- Software Collection Packaging Guide
  - https://www.softwarecollections.org/en/docs/guide/
