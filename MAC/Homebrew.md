# 概要
MacにはHomebrew, MacPorts, Finkといった複数のパッケージ管理システムが存在するが、 複数のパッケージ管理システムを混在させるべきではない。  
Homebrewを利用すると最初から入っているrubyやsvnとは異なるディレクトリにインストールを行ってくれるために既存ソフトウェアに影響を与えずにインストールすることができる。

HomebrewとMacportsについての違いは以下を参考のこと
- http://qiita.com/b4b4r07/items/6efebc2f3d1cbbd393fc

# 詳細

### インストールされているパッケージ
```
$ brew list
```

### パッケージのインストール・アンインストール
インストールは次のコマンドで可能
```
$ brew install curl
```

dryrunモードは存在しないので、以下の例のように依存関係を確認してからというのが最も望ましい
```
$ brew deps emacs
pkg-config
```

パッケージのアンインストールは以下のようにして可能
```
$ brew uninstall emacs
```

### パッケージを探す
```
$ brew search vim
macvim	 vim	   vimpager  vimpc
```

### パッケージの有効化・無効化
一時的に有効にするか、無効にするかを指定することができます。
```
$ brew unlink emacs   // 無効
$ brew link emacs     // 有効
```

### パッケージ一覧の更新
```
$ brew update
$ brew upgrade
```

### パッケージ情報詳細を確認する
```
$ brew info wget
wget: stable 1.15, HEAD
http://www.gnu.org/software/wget/
/usr/local/Cellar/wget/1.15 (8 files, 728K) *
  Built from source
From: https://github.com/Homebrew/homebrew/commits/master/Library/Formula/wget.rb
==> Dependencies
Required: openssl 〓〓〓
==> Options
--enable-debug
Build with debug support
--enable-iri
Enable iri support
--HEAD
install HEAD version
```

### brew環境設定とconfig設定を確認する
- 環境設定の確認
```
HOMEBREW_CC: clang
HOMEBREW_CXX: clang++
MAKEFLAGS: -j4
CMAKE_PREFIX_PATH: /usr/local
CMAKE_INCLUDE_PATH: /usr/include/libxml2:/System/Library/Frameworks/OpenGL.framework/Versions/Current/Headers
CMAKE_LIBRARY_PATH: /System/Library/Frameworks/OpenGL.framework/Versions/Current/Libraries
PKG_CONFIG_LIBDIR: /usr/lib/pkgconfig:/usr/local/Library/ENV/pkgconfig/10.8
ACLOCAL_PATH: /usr/local/share/aclocal
PATH: /usr/local/Library/ENV/4.3:/usr/bin:/bin:/usr/sbin:/sbin
```
- config設定の確認
```
$ brew --config
HOMEBREW_VERSION: 0.9.5
ORIGIN: https://github.com/Homebrew/homebrew
HEAD: 7051972d87696f44c6e421604e42bb188ee13b96
HOMEBREW_PREFIX: /usr/local
HOMEBREW_CELLAR: /usr/local/Cellar
CPU: quad-core 64-bit ivybridge
OS X: 10.8.4-x86_64
Xcode: 5.0.1
CLT: 5.0.1.0.1.1377666378
LLVM-GCC: build 2336
Clang: 5.0 build 500
MacPorts/Fink: /opt/local/bin/port
X11: N/A
System Ruby: 1.8.7-358
Perl: /usr/bin/perl
Python: /usr/bin/python
Ruby: /usr/bin/ruby => /System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/bin/ruby
```

### 古いバージョンのパッケージを削除する。
```
＄brew cleanup [パッケージ名]
```

### コマンドのソースコードを閲覧する。
```
$ brew cat wget
```

### インストール済パッケージの依存関係を調査する
```
$ brew uses --installed openssl
curl  wget
```

### 利用できるパッケージのバージョンを確認する。
```
$ brew versions wget
Warning: brew-versions is unsupported and may be removed soon.
Please use the homebrew-versions tap instead:
  https://github.com/Homebrew/homebrew-versions
1.15     git checkout 9e0f6f8 Library/Formula/wget.rb
1.14     git checkout d9339ac Library/Formula/wget.rb
1.13.4   git checkout 122c0b2 Library/Formula/wget.rb
```

### パッケージの公式ホームページに遷移する
ブラウザが起動してパッケージの公式サイトに遷移します。
```
$ brew home maven
$ brew home curl
```

### brewコマンドまとめ
http://takuya-1st.hatenablog.jp/entry/20111224/1324750111
からの引用
- brew install foo fooをインストール
- brew install --HEAD foo fooのHEADバージョンをインストール
- brew install --force --HEAD foo fooの新しいHEADバージョンをインストール
- brew search インストール可能なすべてのformulaを表示
- brew search foo インストール可能なformulaからfooを検索
- brew search /foo/ 正規表現fooを検索
- brew list インストール済みのformulaeを表示
- brew list foo fooのインストールしたファイルを表示
- brew info --github foo foo formulaのGithub履歴ページをブラウザで表示
- brew info インストール済みのHomebrewパッケージのサマリーを表示
- brew info foo インストール済みのfooのすべての情報を表示
- brew home HomebrewのWebサイトをデフォルトブラウザで表示
- brew home foo fooのWebサイトをデフォルトブラウザで表示
- brew update HomebrewのformulaeとHomebrew自体をアップデート
- brew remove foo fooのアンインストール
- brew create [url] ダウンロード可能なファイルのURLのformulaを生成して$BREW_EDITORか$EDITORで指定されているエディタで開く
- brew create url-of-tarball --cache formulaを生成して、tarballをダウンロードする。md5をformulaテンプレートに追加する。
- brew create --macports foo どのようにfooをインストールするか調べるために、MacPortsパッケージ検索ページでfooを検索する。
- brew create --fink foo Finkで同様のことを行う。
- brew edit foo formulaを$HOMEBREW_EDITORか$EDITORで開く
- brew link foo fooのインストールされたファイルのHomebrew prefixシンボリックリンク作成する。（Homebrewでインストールすると自動的に行われる。DIYインストールを行った場合に有用。
- brew unlink foo Homebrew prefixシンボリックリンクを削除する。
- brew prune Homebrewprefixからデッドシンボリックリンクを削除する。
- brew outdated 利用可能なアップデートバージョンが存在するformulaを表示する。新しいバージョンをインストールするにはbrew install fooを実行する。
- brew upgrade 利用可能なアップデートバージョンが存在するformulaをすべてアップグレードする。
- brew --config Homebrewのシステム設定を表示する
- brew --prefix Howebrew prefixのパスを表示する。(普通は /usr/local)
- brew --prefix (formula) インストールされたformulaのパスを表示する。
- brew --cellar Homebrew Cellarのパスを表示する。(普通は /usr/local/Cellar)
- brew --cache Homebrew キャッシュダウンロードのパスを表示する。(普通は ~/Library/Caches/Homebrew)
- brew doctor インストールの一般的な問題をチェックする。
- brew audit すべてのformulaeのコードとスタイルの問題を検査する。
- brew cleanup foo インストールしたすべてもしくは特定のformulaeの古いバージョンをcellarから削除する。すべての場合はbrew cleanupを実行する。

### curlでhttp2を利用したい
Mac付属のcurlだとhttp2に対応していません。
http2もともにinstallして再コンパイルする。時間はちょっとかかるかもしれない
```
$ brew reinstall curl --  --with-nghttp2
```

上記だけだと使えないので以下のコマンドを実行する。
```
$ brew link curl --force
$ hash -r
```

以上でhttp2が利用できるようになりました。
```
$ curl --http2 -I https://http2bin.org/get
```

- SeeAlso
  - http://harashun11.hatenablog.com/entry/2016/06/15/191959
  - https://simonecarletti.com/blog/2016/01/http2-curl-macosx/

# 参考URL
- http://yonchu.hatenablog.com/entry/20110226/1298723822
