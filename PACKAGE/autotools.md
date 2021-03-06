# 環境構築
たいていのLinuxディストリビューションにはこれらのツールの パッケージがある。たとえばDebianやUbuntuなら
```
$ sudo apt-get install autoconf automake libtool autoconf-doc libtool-doc
```
でインストールできる。Mac OS X で Mac Ports https://www.macports.org を使っているなら

```
$ sudo port install automake autoconf
```
でインストールできる。

- 参考
  - http://loto.sourceforge.net/feram/Autotools-memo.ja.html

# 参考URL
- Debianパッケージングチュートリアル(Slide Share)
  - 概要がつかめる
  - http://www.slideshare.net/nabetaro/packaging-tutorialja

### Makefile.am
- 新しめの Autotools (Autoconf&Automake) を使ってみよう 
  - configure.inやMakefile.amあたりに詳しい
  - http://www.spa.is.uec.ac.jp/~kinuko/slidemaker/autotools/
- makefile.amの構文
  - http://homepage2.nifty.com/hippos/autoconf/makefile_am_2.html
- A tutorial for porting to autoconf & automake
  - http://mij.oltrelinux.com/devel/autoconf-automake/
- パターン別
  - http://d.hatena.ne.jp/shakemi/20100730#1280505497
- GNU Automake By Example
  - http://socgsa.cs.clemson.edu/seminar/tools06/resources/08_autotools/automake.htm

### dh_make
- 電脳倶楽部謹製 ubuntu パッケージ PPA リポジトリ公開の手引き
  - http://www.gfd-dennou.org/arch/cc-env/ubuntu-dennou/old/TEBIKI.ubuntu-dennou.htm.en

### Autotools
- Autotoolsについてのメモ
  - http://loto.sourceforge.net/feram/Autotools-memo.ja.html
- configureの作り方(autotoolsの使い方）
  - http://nopipi.hatenablog.com/entry/2013/01/14/025509
- wikipedia Autotools
  - https://ja.wikipedia.org/wiki/Autotools
- automakeマニュアル(gnu.org)
  - http://www.gnu.org/software/automake/manual/automake.html

### debパッケージ作成
- 独自Debパッケージやaptリポジトリを使ったサーバー管理術
  - http://knowledge.sakura.ad.jp/tech/1123/
- 第4章 debian/ ディレクトリー以下に無くてはならないファイル
  - https://www.debian.org/doc/manuals/maint-guide/dreq.ja.html

### ライブラリ生成について
- 8.3 Building a Shared Library
  - http://www.gnu.org/software/automake/manual/html_node/A-Shared-Library.html
- ライブラリバージョンについて
  - http://www.gnu.org/software/libtool/manual/html_node/Versioning.html
- version-infoで指定するバージョンのルール
  - http://www.astro.gla.ac.uk/~norman/star/ssn78/ssn78.htx/N-a2b3.html
- how do you make a .so library with autoconf, rather that a .la library?
  - http://stackoverflow.com/questions/5671681/how-do-you-make-a-so-library-with-autoconf-rather-that-a-la-library
- How to create a shared library (.so) in an automake script?
  - http://stackoverflow.com/questions/8916425/how-to-create-a-shared-library-so-in-an-automake-script

### MISC
- autogen.sh
  - http://d.hatena.ne.jp/moriyoshi/20070101
