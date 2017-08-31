# 概要
specファイルを作成してrpmパッケージにする方法について

# 詳細
### 初めてのrpm作成(環境構築から)
rpmbuildというコマンドが必要になるので次のパッケージをインストールします。
```
$ sudo yum install rpm-build
```

rpmパッケージに入れるのは次のプログラムhelloを入れることにします。
```
$ cat hello.c
#include <stdio.h>

main(void)
{
    printf("hello, world!\n");
}
$ gcc -o hello hello.c
$ tar czvf hello-1.0.tar.gz hello    // ビルドしたhelloコマンドをアーカイブ化しておく
```

必要なディレクトリを作って、アーカイブをコピーしたりします。
```
$ mkdir -p rpmbuild/{SOURCES,SPECS}
$ cp hello-1.0.tar.gz rpmbuild/SOURCES
$ cd rpmbuild
```

次のspecファイルを作成します。以下は簡単な今回のサンプルspecファイルです。
```
$ vim SPECS/sample.spec
%define name hello
%define version 1.0
%define unmangled_version 1.0
%define release 1
%define _binaries_in_noarch_packages_terminate_build 0

Summary: sample hello world program
Name: %{name}
Version: %{version}
Release: %{release}
License: GPL2
Source0: %{name}-%{unmangled_version}.tar.gz
Group: Applications/File
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-buildroot
Prefix: %{_prefix}
BuildArch: noarch

%define INSTALLDIR %{buildroot}/usr/local/bin

%description
This is a sample program to learn how to make a rpm package.

%prep

%build

%install
rm -rf %{INSTALLDIR}
mkdir -p %{INSTALLDIR}
cp -R * %{INSTALLDIR}

%clean
rm -rf %{buildroot}

%files
/usr/local/bin
%defattr(-,root,root)
```

以上でrpmパッケージを作成する準備が整いました。rpmbuildで生成したら所定の位置に作成されます。
```
$ rpmbuild -bb SPECS/sample.spec
$ ls RPMS/noarch/
hello-1.0-1.noarch.rpm
```

- 参考URL
  - http://qiita.com/gucci3/items/f9fbab8396295385541f


## specファイル説明

specファイルは基本的には次の構成になります。
```
イントロダクション　セクション
description セクション
prep セクション
build セクション
install セクション
clean セクション
files セクション
```

### システムで利用されているマクロを確認する
例えば、_rpmdirを知りたい場合には次のようにすれば確認することができます。
```
$ rpm --eval '%{_rpmdir}'
/usr/src/redhat/RPMS
```

または、次のコマンドでrpmrc関連の設定をダンプしてくれます。
```
$ rpm --showrc
```

- 参考
  - https://stackoverflow.com/questions/8076471/how-to-know-the-value-of-built-in-macro-in-rpm

## rpmbuild

### rpmbuildコマンドのオプションの説明
次のようなオプションがあります。
```
-bp 	ソースの展開とパッチ当てまで行う
-bc 	makeまで実行
-bi 	インストールまで実行
-bb 	バイナリパッケージを作成
-bs 	ソースパッケージを作成
-ba 	バイナリパッケージとソースパッケージの両方を作成
--short-circuit -bc  %buildセクションを実行（%prepを飛ばして）
--short-circuit -bi  %installセクションを実行（%prepと%buildを飛ばして）
--nobuild            何もビルドをせず、specファイルの検査を行うのに使う
```

### .rpmmacros設定ファイルの説明
rpmbuildコマンドは$HOME/.rpmmacrosファイルを設定ファイルとして読み込みます。
```
%_topdir /home/mike/rpm
%packager Mike <mike@example.org>
%_sysconfdir /etc
```





