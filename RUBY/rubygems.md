# 概要
Rubygemsについて

gemとはrubyで使われるライブラリを指す。
多くのライブラリがgem形式で提供されていてこれを管理するのがRubygemsとなり、gemコマンドはRubygemsの一部といえるだろう。

# 詳細


### remoteからgemパッケージを検索する
searchだとremoteからパッケージを検索します。ちなみにlistだとlocalからパッケージを検索する。
```
$ gem search zookeeper

*** REMOTE GEMS ***

carlosnz-zookeeper (0.2)
chef-handler-zookeeper (0.1.2)
hiera-zookeeper (0.1.3)
hiera_zookeeper (0.2.3)
logstash-output-zookeeper (1.0.0)
myelin-zookeeper_client (0.0.2)
neerfri-zookeeper_client (0.0.6)
newrelic-zookeeper (1.0.0)
rjack-zookeeper (3.4.5.0 java)
sensu-plugins-zookeeper (0.1.0)
shafferj-zookeeper_client (0.0.4)
slyphon-zookeeper (0.9.4 ruby java)
slyphon-zookeeper_jar (3.3.5 ruby java)
zk-ruby-zookeeper_jar (3.4.5)
zookeeper (1.4.11 ruby java)
zookeeper-jars (3.4.6 java)
```

正規表現も使うことができます。
```
$ gem search ^zookeeper

*** REMOTE GEMS ***

zookeeper (1.4.11 ruby java)
zookeeper-jars (3.4.6 java)
```

### ローカルにインストールされているgemパッケージを取得する

ローカルにインストールされているgemパッケージを取得する
```
$ gem list
```

正規表現を使ってみる。複数のバージョンがインストールされていることがわかります。
```
$ gem list ^json$

*** LOCAL GEMS ***

json (2.0.3, 1.6.5)
```

listを使っても実はremoteを検索できる。(紛らわしいが混乱しないように一応覚えておくと良い)
```
$ gem list --remote
```

### gemパッケージのインストール・アンインストール
```
$ gem install zookeeper
Fetching: zookeeper-1.4.11.gem (100%)
Building native extensions.  This could take a while...
/usr/local/share/ruby/site_ruby/rubygems/ext/builder.rb:76: warning: Insecure world writable dir /home/tsuyoshi in PATH, mode 040777
Successfully installed zookeeper-1.4.11
```

パッケージのアンインストールは次の通り
```
$ gem uninstall zookeeper
```

### gemパッケージのアップデート
```
$ gem update zookeeper
```


### パッケージに含まれるファイル一覧を取得する
```
$ gem contents zookeeper
```

### gemパッケージをインストールせずにgemパッケージをダウンロードだけする+展開する。
```
$ gem fetch zookeeper
Downloaded zookeeper-1.4.11
$ ls
zookeeper-1.4.11.gem
$ gem unpack zookeeper-1.4.11.gem 
Unpacked gem: '/home/tsuyoshi/hoge/z/zookeeper-1.4.11'
$ ls zookeeper-1.4.11
CHANGELOG  Guardfile  Manifest         Rakefile        ext   lib        scripts  zookeeper.gemspec
Gemfile    LICENSE    README.markdown  cause-abort.rb  java  notes.txt  spec     zoomonkey
```

### remoteサーバにアップデートのあるgemパッケージを表示する。
```
$ gem outdated
actionmailer (3.2.11 < 5.0.1)
actionpack (3.2.11 < 5.0.1)
activemodel (3.2.11 < 5.0.1)
activerecord (3.2.11 < 5.0.1)
activeresource (3.2.11 < 4.1.0)
activesupport (3.2.11 < 5.0.1)
arel (3.0.2 < 8.0.0)
...
```

### 古いバージョンのパッケージを削除する
古いバージョンのパッケージを削除する。パッケージを省略すればすべての古いパッケージをクリーンします。
```
$ gem update rdoc
Updating installed gems
$ gem cleanup rdoc
Cleaning up installed gems...
Clean Up Complete
```

### gemパッケージがインストールされたパスを確認する。
```
$ gem which zookeeper
/home/tsuyoshi/.gem/ruby/1.9.1/gems/zookeeper-1.4.11/lib/zookeeper.rb
```

### gemの依存関係を表示する
```
$ gem dependency multi_json
Gem multi_json-1.5.0
  rake (>= 0.9, development)
  rdoc (>= 3.9, development)
  rspec (>= 2.6, development)
  simplecov (>= 0.4, development)
```

### gemパッケージの仕様を確認する
```
$ gem specification zookeeper
--- !ruby/object:Gem::Specification
name: zookeeper
version: !ruby/object:Gem::Version
  version: 1.4.11
platform: ruby
authors:
- Phillip Pearson
- Eric Maland
- Evan Weaver
- Brian Wickman
- Neil Conway
- Jonathan D. Simms
autorequire: 
bindir: bin
cert_chain: []
date: 2015-09-28 00:00:00.000000000 Z
dependencies: []
description: ! 'A low-level multi-Ruby wrapper around the ZooKeeper API bindings.
  For a

  friendlier interface, see http://github.com/slyphon/zk. Currently supported:

  MRI: {1.8.7, 1.9.2, 1.9.3}, JRuby: ~> 1.6.7, Rubinius: 2.0.testing, REE 1.8.7.


  This library uses version 3.4.5 of zookeeper bindings.


'
email:
- slyphon@gmail.com
executables: []
extensions:
- ext/extconf.rb
extra_rdoc_files: []
files:
- ext/extconf.rb
homepage: https://github.com/slyphon/zookeeper
licenses: []
metadata: {}
post_install_message: 
rdoc_options: []
require_paths:
- lib
- ext
required_ruby_version: !ruby/object:Gem::Requirement
  requirements:
  - - ! '>='
    - !ruby/object:Gem::Version
      version: '0'
required_rubygems_version: !ruby/object:Gem::Requirement
  requirements:
  - - ! '>='
    - !ruby/object:Gem::Version
      version: '0'
requirements: []
rubyforge_project: 
rubygems_version: 2.6.10
signing_key: 
specification_version: 4
summary: Apache ZooKeeper driver for Rubies
test_files: []
```

### gemパッケージのチェックをする
gemパッケージのファイルが存在していない場合などに警告してくれる。
自分が見た感じだと改竄は検知しないように思われる。
```
$ gem check rdoc
Checking gems...

rdoc-3.12.gem has 1 problems
  /usr/share/gems/cache/rdoc-3.12.gem:
      missing gem file /usr/share/gems/cache/rdoc-3.12.gem
```

### gem自身のバージョンアップデートを行う。
```
$ gem --version
1.8.24
$ sudo gem update --system
$ gem --version
2.6.10
```

### gemの環境変数を表示する
```
$ gem environment
/usr/local/share/ruby/site_ruby/rubygems/commands/environment_command.rb:154: warning: Insecure world writable dir /home/tsuyoshi in PATH, mode 040777
RubyGems Environment:
  - RUBYGEMS VERSION: 2.6.10
  - RUBY VERSION: 1.9.3 (2013-06-27 patchlevel 448) [x86_64-linux]
  - INSTALLATION DIRECTORY: /home/tsuyoshi/.gem/ruby/1.9.1
  - USER INSTALLATION DIRECTORY: /home/tsuyoshi/.gem/ruby/1.9.1
  - RUBY EXECUTABLE: /usr/bin/ruby
  - EXECUTABLE DIRECTORY: /home/tsuyoshi/bin
  - SPEC CACHE DIRECTORY: /home/tsuyoshi/.gem/specs
  - SYSTEM CONFIGURATION DIRECTORY: /etc
  - RUBYGEMS PLATFORMS:
    - ruby
    - x86_64-linux
  - GEM PATHS:
     - /home/tsuyoshi/.gem/ruby/1.9.1
     - /usr/share/gems
     - /usr/local/share/gems
  - GEM CONFIGURATION:
     - :update_sources => true
     - :verbose => true
     - :backtrace => false
     - :bulk_threshold => 1000
  - REMOTE SOURCES:
     - https://rubygems.org/
  - SHELL PATH:
     - /usr/local/bin
     - /usr/bin
     - /usr/local/sbin
     - /usr/sbin
     - /home/tsuyoshi/.local/bin
     - /home/tsuyoshi/bin
```


### そのパッケージのgemへの最終アクセス時刻を表示する。
```
$ gem stale | tail -5
builder-3.0.4 at Wed Feb 22 08:50:59 2017
zookeeper-1.4.11 at Wed Feb 22 08:54:34 2017
json-2.0.3 at Wed Feb 22 09:11:21 2017
rdoc-5.0.0 at Wed Feb 22 09:11:23 2017
multi_json-1.5.0 at Wed Feb 22 09:15:18 2017
```

### プライベートなgemサーバを作る(試していない)
実際に自分で試せていないが載せておく。
```
$ gem install builder -v 2.1.2
```

あとは適当にmkdirしてgenerate_indexすればいい。
```
$ mkdir -p /var/www/localgems/gems
$ cp ~/foo-0.0.1.gem /var/www/localgems/gems
$ cd /var/www/localgems
$ gem generate_index
```

### gemを取得するremoteサーバを表示・変更・追加する
現状の一覧を確認する。
```
$ gem source --list
*** CURRENT SOURCES ***

https://rubygems.org/
```

追加する。たとえば、HTTPSを追加する。
```
$ gem source --add https://rubygems.org/
```

削除する。たとえば、もともとあったHTTPのURLを削除する。
```
$ gem source --remove http://rubygems.org/
```

### 指定したバージョンのgemの公開停止を行う
指定したバージョンのgemの公開停止を行う。(gem pushで公開したgemパッケージへの対処方法)
```
$ gem yank foo -v0.0.1 
```

上記を取り消す方法も存在する。
```
$ gem yank foo -v0.0.1 --undo
```


### gemのヘルプコマンドを表示する
gemのヘルプを表示する。ただし、gemのサブ引数の詳細なhelpは次で挙げる「gem help command」となる。
```
$ gem help 
RubyGems is a sophisticated package manager for Ruby.  This is a
basic help message containing pointers to more information.

  Usage:
    gem -h/--help
    gem -v/--version
    gem command [arguments...] [options...]

  Examples:
    gem install rake
    gem list --local
    gem build package.gemspec
    gem help install

  Further help:
    gem help commands            list all 'gem' commands
    gem help examples            show some examples of usage
    gem help gem_dependencies    gem dependencies file guide
    gem help platforms           gem platforms guide
    gem help <COMMAND>           show help on COMMAND
                                   (e.g. 'gem help install')
    gem server                   present a web page at
                                 http://localhost:8808/
                                 with info about installed gems
  Further information:
    http://guides.rubygems.org
```

gemのサブコマンドの詳細を表示する。
```
$ gem help commands
GEM commands are:

    build             Build a gem from a gemspec
    cert              Manage RubyGems certificates and signing settings
    check             Check a gem repository for added or missing files
    cleanup           Clean up old versions of installed gems
    contents          Display the contents of the installed gems
    dependency        Show the dependencies of an installed gem
    environment       Display information about the RubyGems environment
    fetch             Download a gem and place it in the current directory
    generate_index    Generates the index files for a gem server directory
    help              Provide help on the 'gem' command
    install           Install a gem into the local repository
    list              Display local gems whose name matches REGEXP
    lock              Generate a lockdown list of gems
    mirror            Mirror all gem files (requires rubygems-mirror)
    open              Open gem sources in editor
    outdated          Display all gems that need updates
    owner             Manage gem owners of a gem on the push server
    pristine          Restores installed gems to pristine condition from files
                      located in the gem cache
    push              Push a gem up to the gem server
    query             Query gem information in local or remote repositories
    rdoc              Generates RDoc for pre-installed gems
    search            Display remote gems whose name matches REGEXP
    server            Documentation and gem repository HTTP server
    sources           Manage the sources and cache file RubyGems uses to search
                      for gems
    specification     Display gem specification (in yaml)
    stale             List gems along with access times
    uninstall         Uninstall gems from the local repository
    unpack            Unpack an installed gem to the current directory
    update            Update installed gems to the latest version
    which             Find the location of a library file you can require
    yank              Remove a pushed gem from the index

For help on a particular command, use 'gem help COMMAND'.

Commands may be abbreviated, so long as they are unambiguous.
e.g. 'gem i rake' is short for 'gem install rake'.
```

# 参考URL
- https://rubygems.org/
 - gemパッケージを検索することができる。
- http://guides.rubygems.org/command-reference/
 - gemコマンドの使い方がすべて乗っている

# TODO
以下のコマンドがまだ未記載なので、いつかまた調べた時にでも。。。
- gem build
 - gemspecからgemをつくる
- gem cert
 - サインの必要な証明のRubyGemsを管理する 
- gem lock
 - gemのロックダウンリストを生成する
- gem mirror
 - ローカルに gem を全部持ってきてくれる仕組み
- gem pristine
 - gemの隠し場所にあるファイルからインストールしたgemを初期状態へ戻す
- gem rdoc
 - プリインストールされたgemのRDocを生成する
- gem server
 - Documentation and gem repository HTTP server
