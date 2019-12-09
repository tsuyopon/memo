# 概要
spectoolコマンドの使い方について

spectoolを使うことでspecファイルに記載されたSource0, Source1, Patch0, Patch1などに指定されているリモート取得先から取得し、特定のパスに配置します。
- https://pagure.io/rpmdevtools/blob/master/f/spectool.in#_183


spectoolの実体はpythonのソースコードで、参考資料にソースコードを添付しています。

# 詳細

### パッケージのインストール
```
$ sudo yum install rpmdevtools
```


### リモートから取得するファイルの一覧を取得する(実際には取得しない)

以下のspecファイルで試してみる。
```
$ cat test.spec 
#
# Example spec file for cdplayer app...
#
Summary: A CD player app that rocks!
Name: cdplayer
Version: 1.0
Release: 1
License: GPL
Group: Applications/Sound
Source0: ftp://ftp.gnomovision.com/pub/cdplayer/cdplayer-1.0.tgz
Source1: ftp://ftp.gnomovision.com/pub/cdplayer/cdplayer-1.1.tgz
Patch0: ftp://ftp.gnomovision.com/pub/cdplayer/patch0.diff
URL: http://www.gnomovision.com/cdplayer/cdplayer.html
Distribution: WSS Linux
Vendor: White Socks Software, Inc.
Packager: Santa Claus <sclaus@northpole.com>

%description
It slices!  It dices!  It's a CD player app that
can't be beat.  By using the resonant frequency
of the CD itself, it is able to simulate 20X
oversampling.  This leads to sound quality that
cannot be equaled with more mundane software...
```

SourceやPatchを取得します。
```
$ spectool -l test.spec 
Source0: ftp://ftp.gnomovision.com/pub/cdplayer/cdplayer-1.0.tgz
Source1: ftp://ftp.gnomovision.com/pub/cdplayer/cdplayer-1.1.tgz
Patch0: ftp://ftp.gnomovision.com/pub/cdplayer/patch0.diff
```

lオプションはデフォルトなので抜いても同じです。
```
$ spectool test.spec 
```

Sourceの場合だけ表示する
```
$ spectool -S test2.spec 
Source0: ftp://ftp.gnomovision.com/pub/cdplayer/cdplayer-1.0.tgz
Source1: ftp://ftp.gnomovision.com/pub/cdplayer/cdplayer-1.1.tgz
```

Patchの場合だけ表示する
```
$ spectool -P test2.spec 
Patch0: ftp://ftp.gnomovision.com/pub/cdplayer/patch0.diff
```

### リモートからファイルを取得する
gオプションを指定することで指定されたSourceやPatchを取得する。Rを指定することで_sourcedirに配置します。
```
$ spectool -g -R test.spec 
```

配置先は以下のコマンドで取得できるパスとなります。
```
$ rpm --eval '\%{_sourcedir}'
\/home/tsuyoshi/rpmbuild/SOURCES
```

なお、特定のディレクトリに取得したい場合にはCオプションを指定します。以下の例ではカレントディレクトリに対してtar.gzを配置するように指定しています。
```
$ spectool -g -C . test.spec 
Getting http://xmlsoft.org/sources/libxml2-2.9.10.tar.gz to ./libxml2-2.9.10.tar.gz
$ ls *.tar.gz
libxml2-2.9.10.tar.gz
```


### マクロ定義を設定する
たとえば、次のように%{_hoge}と設定しておくと
```
$ grep _hoge test.spec 
Source0: http://xmlsoft.org/sources/%{_hoge}/libxml2-2.9.10.tar.gz
```

以下のようにマクロで定義を指定することができます。
```
$ spectool --define '_hoge fuga' test.spec 
Source0: http://xmlsoft.org/sources/fuga/libxml2-2.9.10.tar.gz
```

### rpmdevgtool用のcurl設定を変更する
以下を修正すること
```
/etc/rpmdevtools/curlrc
```

### デバッグ情報を出力する
```
$ spectool --debug test2.spec 
temp dir: /tmp/spectool_a5tz17WOo9
temp spec filename: /tmp/spectool_a5tz17WOo9/spec_V785_HUGtt
stderr filename: /tmp/spectool_a5tz17WOo9/stderr_gZ3qHlQi2n
Source0: ftp://ftp.gnomovision.com/pub/cdplayer/cdplayer-1.0.tgz
Source1: ftp://ftp.gnomovision.com/pub/cdplayer/cdplayer-1.1.tgz
Patch0: ftp://ftp.gnomovision.com/pub/cdplayer/patch0.diff
```

# 参考資料
- マニュアル
  - http://pkgbuild.sourceforge.net/spectool.html
- レポジトリ(rpmdevtools)
  - https://pagure.io/rpmdevtools
