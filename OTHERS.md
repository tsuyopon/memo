# 概要
とりあえず未整理な情報をここにとどめておくためのメモ

# 内容

## homebrew
- オプション一覧
  - http://qiita.com/omega999/items/6f65217b81ad3fffe7e6
- brew tapとは
  - http://qiita.com/saa/items/85ed5e914d424fbf9fd6
  - http://tech.caph.jp/2011/04/06/homebrew%E3%81%AE%E5%B0%8E%E5%85%A5%E3%81%A8%E4%BD%BF%E3%81%84%E6%96%B9/

## log4cpp
- http://log4cpp.sourceforge.net/
- doxygen
  - http://log4cpp-jp.osdn.jp/api/annotated.html
- ソースコード
  - https://sourceforge.net/projects/log4cpp/
- 基本的な使い方
  - http://www.02.246.ne.jp/~torutk/cxx/log4cpp/log4cpp.html

## イベント駆動

### eventfd
自分が試したサンプルがこちら。コピペで使えるので良い
- https://linuxjm.osdn.jp/html/LDP_man-pages/man2/eventfd.2.html

### timerfs
- ここに説明あり
  - https://linuxjm.osdn.jp/html/LDP_man-pages/man2/timerfd_create.2.html
- コピペで使えるサンプルはここにある
  - https://codezine.jp/article/detail/4799

### signalfd
- ビルド時に「-lrt」リンクが必要
  - http://stackoverflow.com/questions/259784/what-libraries-need-to-be-linked-for-timer-create-timer-settime-and-other-timer
- コピペで使えるサンプルは以下にある
  - https://codezine.jp/article/detail/4803


## httping
- http://www.e-agency.co.jp/column/20130618-2.html
- https://www.vanheusden.com/httping/
- http://recipe.kc-cloud.jp/archives/4910
- オプションについては以下を参考のこと
  - http://d.hatena.ne.jp/rx7/20110822/p0

## Asan
- https://github.com/google/sanitizers
- http://d.hatena.ne.jp/tkng/20110419/1303176182
- https://cwiki.apache.org/confluence/download/attachments/56066455/summit_asan.pptx?version=1
```
apt-get install clang
CXXFLAGSに以下を付与
	-fstanitize=address -fno-omit-frame-pointer
export CXX=clang++
```

## clang-format
- http://clang.llvm.org/docs/ClangFormat.html
- ヘルプ
```
$ clang-format -help
```
- 再帰的に適用
```
$ clang-format -i -style=file *.{cc,h}
```
- 適用可能なスタイル
  - http://algo13.net/clang/clang-format-style-oputions.html
```
$HOME/.clang-format
	% cat .clang-format
	---
	BasedOnStyle:  Google
	ColumnLimit: 110
	BinPackParameters: false
```
- http://rhysd.hatenablog.com/entry/2013/08/26/231858


## RPCについて
以下にあるプログラムのコピペを試したことがある
  - http://www.ncad.co.jp/~komata/c-kouza15.htm


## リンケージ周り
- http://www.lurklurk.org/linkers/linkers.html
- nm
  - http://www.geocities.jp/fut_nis/html/binutils-ja/nm.html
- LD_DEBUG
```
LD_DEBUG=symbols,bindings ./a.out
```
- http://ukai.jp/debuan/2002w/elf.html
  - あたりにもLD_DEBUGに指定できるものがのっている
  - LD_DEBUGの他の環境へんすうについてものっている
- http://d.hatena.ne.jp/dayflower/20080523/1211531833
- https://www.gnu.org/software/gnulib/manual/html_node/LD-Version-Scripts.html
- C++で仮想関数テーブルをダンプする
```
		-fdump-class-hierarchy
```
- http://blog.seasons.cc/entry/20090208/1234115944
- 出力内容についてはこちらを参考
  - http://stackoverflow.com/questions/17818556/how-can-i-understand-the-fdump-class-hierarchy-output


## kafka
- https://kafka.apache.org/documentation
- ここに従ってstandaloneでうごかした
  - https://kafka.apache.org/documentation#quickstart
```
		以下の関係を押さえておけばok
		           <zookeeper>
		producer -> broker -> consumer
```
- 以下にkafkaをつかった上記の概念図がきさいされているので参考にすると良さそう
  - http://inokara.hateblo.jp/entry/2016/05/01/113254










