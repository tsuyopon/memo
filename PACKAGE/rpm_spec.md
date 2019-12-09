# 概要
specファイルを作成してrpmパッケージにする方法について

# 詳細
## 初めてのrpm作成(環境構築から)
rpmbuildというコマンドが必要になるので次のパッケージをインストールします。
```
$ sudo yum install rpm-build
```

今回は上記だけで構いませんが、今後spectool, yumdownloaderなどを使う場合には以下を入れておくと重宝します。
```
$ sudo yum install -y rpmdevtools yum-utils
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


## rpmdev-setuptreeを使う
この辺の作業を手動でやったりする場合もあったがrpmdev-setuptreeパッケージを使うと手動でディレクトリを作る必要がなくなります。
- 参考
  - http://blog.gachapin-sensei.com/archives/618872.html
```
$ mkdir -p ~/rpmbuild/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}
$ echo '%_topdir %(echo $HOME)/rpmbuild' > ~/.rpmmacros
```

パッケージをインストールして実行すると$HOME/rpmbuildディレクトリ作成と$HOME/.rpmmacroを生成します。
```
$ yum install rpmdevtools
```

```
$ rpmdev-setuptree 
$ tree ~/rpmbuild/
/home/tsuyoshi/rpmbuild/
|-- BUILD
|-- RPMS
|-- SOURCES
|-- SPECS
`-- SRPMS

5 directories, 0 files
```

.rpmmacroは以下の通り
```
%_topdir %(echo $HOME)/rpmbuild

%_smp_mflags %( \
[ -z "$RPM_BUILD_NCPUS" ] \\\
&& RPM_BUILD_NCPUS="`/usr/bin/nproc 2>/dev/null || \\\
/usr/bin/getconf _NPROCESSORS_ONLN`"; \\\
if [ "$RPM_BUILD_NCPUS" -gt 16 ]; then \\\
echo "-j16"; \\\
elif [ "$RPM_BUILD_NCPUS" -gt 3 ]; then \\\
echo "-j$RPM_BUILD_NCPUS"; \\\
else \\\
echo "-j3"; \\\
fi )

%__arch_install_post \
[ "%{buildarch}" = "noarch" ] || QA_CHECK_RPATHS=1 ; \
case "${QA_CHECK_RPATHS:-}" in [1yY]*) /usr/lib/rpm/check-rpaths ;; esac \
/usr/lib/rpm/check-buildroot
```

上記設定でrpmをビルドするとrpmを生成する直前に rpmdevtools に含まれている  check-rpaths と check-buildroot というコマンドが実行されるようになっています。
例えば、次のように実行すると
```
$ QA_RPATHS=$[ 0x0001|0x0010 ] rpmbuild -ba $HOME/rpmbuild/SPECS/foo.spec
```


QA_RPATHSについては以下の通り
```
*    0x0001 ... standard RPATHs (e.g. /usr/lib); such RPATHs are a minor
*               issue but are introducing redundant searchpaths without
*               providing a benefit. They can also cause errors in multilib
*               environments.
*    0x0002 ... invalid RPATHs; these are RPATHs which are neither absolute
*               nor relative filenames and can therefore be a SECURITY risk
*    0x0004 ... insecure RPATHs; these are relative RPATHs which are a
*               SECURITY risk
*    0x0008 ... the special '$ORIGIN' RPATHs are appearing after other
*               RPATHs; this is just a minor issue but usually unwanted
*    0x0010 ... the RPATH is empty; there is no reason for such RPATHs
*               and they cause unneeded work while loading libraries
*    0x0020 ... an RPATH references '..' of an absolute path; this will break
*               the functionality when the path before '..' is a symlink
```
- 上記のQA_RPATHS環境変数の日本語説明については以下を参考のこと
  - https://www.sssg.org/blogs/naoya/archives/1544


## specファイル説明

specファイルは基本的には次の構成になります。
イントロダクションはパッケージ基本情報を定義して他のセクションとは若干ことなります。
```
イントロダクション　セクション
description セクション
prep セクション(下準備)
build セクション(ビルド手順)
install セクション(インストール手順)
clean セクション(パッケージ構築後の後始末)
files セクション(
```

### イントロダクションセクション

URL, Packager, Patch1, BuildArchなどは特になくても大丈夫そう。
Sourceは複数あればSource0, Source1などと指定することになります。
```
Name: xyz
Version: 1.2.3
Release: 1%{?dist}
Group: Utilities
Vendor: Example Company
URL: http://www.example.com/product/xyz
Packager: Toru Takahashi <torutk@example.com>
License: MIT
Summary: Tools for doing something about xyz.
Summary(ja): xyzについてなにかをするツール
Buildroot: %{_tmppath}/%{name}-%{version}-%{release}-root
BuildArch: i386
Source: xyz-1.2.3.tar.gz
Patch1: xyz-cvs.patch
```

- ビルド時に依存するパッケージを記述する。複数行に渡ってBuildRequiresを記述することができる。
```
BuildRequires: gcc-c++, libgnomeui-devel, guile-devel
BuildRequires: libgnomecanvas-devel, gtk2-devel >= 2.6.0
BuildRequires: fftw-devel, audiofile-devel, esound-devel
BuildRequires: lame-devel, libmad-devel, libvorbis-devel, ladspa-devel
```
- 稼働時に依存するパッケージを記述する
```
Requires: tcl >= 8.4, tk >= 8.4
```
- 稼働させたくないアーキテクチャを指定する
```
ExclusiveArch: i386 x86_64
```

- 自動的な依存追加を回避する
```
AutoReq: 0
```

- debuginfoパッケージを作成しない場合
  - 以下の記述があるとdebuginfoパッケージを作成しなくなります。
```
%define debug_package %{nil}
```


### descriptionセクション


### buildセクション
以下はこのセクションに置かれるサンプルです。
```
%build
%configure
%{__make} %{?_smp_mflags}
```

### installセクション
以下はこのセクションに置かれるサンプルです。
```
%install
%{__rm} -rf %{buildroot}
%makeinstall -C src INSTALL_DIR="%{buildroot}%{_bindir}"
```

### cleanセクション
以下はこのセクションに置かれるサンプルです。
```
%clean
%{__rm} -rf %{buildroot}
```

### filesセクション
以下はこのセクションに置かれるサンプルです。
```
%files
%defattr(-, root, root, 0755)
%doc doc/*.gif doc/*.html README
%{_bindir}/iperf
```

### changelogセクション
以下はこのセクションに置かれるサンプルです。
```
%changelog
* Mon Apr 28 2008 hoge <hoge@hoge.com> - 0.0.0.3
- Updated to release 0.0.0.3.

* Thu Sep 27 2007 piyo piyo <piyo@piyo.com> - 0.0.0.2
- patch

* Sun Sep 18 2005 fuga <fuga@fuga.org> - 0.0.0.1
- Updated to release 0.0.0.1.
```

## spec関連
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

### specのBuildRequiresに指定されているものをインストールする
```
$ sudo yum-builddep ./your-spec.spec
```

### specファイルに含まれているソースやパッチをダウンロードして展開する
spectoolを使うとSourcesに記載されているURLからダウンロードして展開してくれるようです。
- https://stackoverflow.com/questions/33177450/how-do-i-get-rpmbuild-to-download-all-of-the-sources-for-a-particular-spec

次のようにしてコマンドを実行します。
```
$ spectool -g -R ./your-spec.spec
```

specに含まれるソースやパッチの一覧を表示にはlオプションを利用する
```
$ spectool -l ./your-spec.spec
```

## rpmbuildコマンド

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

## rpmdevtoolsパッケージ
```
rpmdev-setuptree: ユーザのホームディレクトリ内に RPM のビルドツリーを作成する
rpmdev-diff: 二つのアーカイブの内容の差分を表示する
rpmdev-newspec: テンプレートから新しい .spec ファイルを作成する
rpmdev-rmdevelrpms: “development” RPMS から検索する
rpmdev-checksig: RPM 署名をチェックする
rpminfo: 実行ファイルやライブラリついての情報を表示する
rpmdev-md5: RPM のすべてのファイルの md5sum を表示する
rpmdev-vercmp: RPM バージョンを比較するチェッカー
spectool: SPEC ファイルに含まれているソースやパッチをダウンロードして展開する
rpmdev-wipetree: rpmdev-setupree によって作成されたディレクトリをすべて削除する
rpmdev-extrac: さまざまなアーカイブを “tar xvf” スタイルで展開する
```

### 2つのrpmを比較する(rpmdev-diff)
```
$ rpmdev-diff  xxx.rpm yyy.rpm
```

### rpminfo
```
$ rpminfo httpd-2.2.23-1.fc17.x86_64.rpm  | head -10

httpd-2.2.23-1.fc17.x86_64.rpm
        /usr/lib64/httpd/modules/mod_actions.so DSO PIC
        /usr/lib64/httpd/modules/mod_alias.so   DSO PIC
        /usr/lib64/httpd/modules/mod_asis.so    DSO PIC
        /usr/lib64/httpd/modules/mod_auth_basic.so      DSO PIC
        /usr/lib64/httpd/modules/mod_auth_digest.so     DSO PIC
        /usr/lib64/httpd/modules/mod_authn_alias.so     DSO PIC
        /usr/lib64/httpd/modules/mod_authn_anon.so      DSO PIC
        /usr/lib64/httpd/modules/mod_authn_dbd.so       DSO PIC
```

# 参考URL
- specファイル一覧
  - rspecサンプルが多くあるのでこちらを参考にすること
  - https://github.com/repoforge/rpms/tree/master/specs
- Fedora Packaging Guidelines
  - https://fedoraproject.org/wiki/Packaging:Guidelines

