# 概要
rubygemsのインストールを管理するための仕組みがGemfileである。   
bundlerにあるbundleコマンドから利用するためのファイルである。

レポジトリ直下に次のようなファイルが配置されることがある。 
- Gemfile
  - ここにインストールするgemパッケージとバージョンなどを記載して、bundle installコマンドを実行するとサーバにパッケージがインストールされる。
- Gemfile.lock
  - bundle installが実行されるとGemfileから読み込みパッケージが生成されるが、その時インストールしたバージョン情報などを記録するファイルである。


つまり、Gemfileを使うと次の利点がある。
- 今まで１つ１つgem install xxxとやっていたが、今後はbundle installだけでgemパッケージが一括インストールされる。
- おまえのパッケージ動かないんだけどがGemfile.lockがあればバージョンがわかっているでそのような問題が発生しない。 

# Gemfile

### もっとも単純なGemfileについて
sourceでgemパッケージの取得元をGemfileの先頭に記述して、その後インストールするパッケージを記述するのが一般的となる。
```
source 'https://rubygems.org'

gem "hoge"                 # 最新版を入れる
gem "rails", "3.0.0.beta3" # 3.0.0.beta3で固定
gem "rack",  ">=1.0"       # 1.0以降のバージョンに制限
gem "thin",  "~>1.1"       # 2.0 > version > 1.1 に制限
gem "xxxx",  "~>1.1.2"     # 1.2.0 > version >= 1.1.2 に制限
```

sourceは最低1つが指定されている必要があります。

### rubyのバージョンなどを指定する
実はGemfileにrubyのバージョンを指定することができます。
```
ruby '1.9.3', engine: "jruby", engine_version: "1.6.7"
```

### ソースとブランチを指定する。
```
gem "fuga", git: "git://github.com/xxx/fuga.git", branch: "1.4"
```

### パスを指定する
```
gem "piyo", path: "~/xxx/piyo"
```

### groupを指定する
次のような感じで指定する。以下は２つの:developmentと:testを指定している例となる。
```
group :development, :test do
  gem "rspec-rails"
  gem "cucumber"
end
```

上記のような場合で本番環境ではdevelopmentやtestを除外したい場合には次のようにします。
```
$ bundle install --without development test
```

ちなみにtest用だけインストールしたいといったことはできないようだ

### gemspecファイルの中を見る。

Gemfileに以下を追加しておくと、 そのパスの中にgemspec がひとつの場合はGemfile に gemspec と書いておけば gemspec の方の依存関係をみて bundle install されます
```
gemspec
```

複数個のgemspecが存在する場合は次のように記述します。以下はhoge.gemspec, fuga.gemspecがある場合です。
```
gemspec :name => 'hoge'
gemspec :name => 'fuga'
```

gemspecサンプルを添付しておく
```
# -*- encoding: utf-8 -*-
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'hello/version'
 
Gem::Specification.new do |gem|
  gem.name          = "hello"
  gem.version       = Hello::VERSION
  gem.authors       = ["seventhsense"]
  gem.email         = ["seventhsense@scimpr.com"]
  gem.description   = %q{TODO: Write a gem description}
  gem.summary       = %q{TODO: Write a gem summary}
  gem.homepage      = ""
 
  gem.files         = `git ls-files`.split($/)
  gem.executables   = gem.files.grep(%r{^bin/}).map{ |f| File.basename(f) }
  gem.test_files    = gem.files.grep(%r{^(test|spec|features)/})
  gem.require_paths = ["lib"]
end
```

上記リファレンスについては以下を参考のこと
- https://docs.ruby-lang.org/ja/latest/class/Gem=3a=3aSpecification.html
- http://guides.rubygems.org/specification-reference/

### Gemfile.lockについて
例えば、以下のGemfileを生成して
```
$ cat Gemfile
source 'https://rubygems.org'

gem "inifile"
gem "zookeeper"
gem "rubocop"
gem "rspec"
```

bundle installやbundle updateするとGemfile.lockが生成されます。
```
$ bundle install
$ cat Gemfile.lock
GEM
  remote: https://rubygems.org/
  specs:
    ast (2.3.0)
    diff-lcs (1.3)
    inifile (3.0.0)
    parser (2.4.0.0)
      ast (~> 2.2)
    powerpack (0.1.1)
    rainbow (2.2.1)
    rspec (3.5.0)
      rspec-core (~> 3.5.0)
      rspec-expectations (~> 3.5.0)
      rspec-mocks (~> 3.5.0)
    rspec-core (3.5.4)
      rspec-support (~> 3.5.0)
    rspec-expectations (3.5.0)
      diff-lcs (>= 1.2.0, < 2.0)
      rspec-support (~> 3.5.0)
    rspec-mocks (3.5.0)
      diff-lcs (>= 1.2.0, < 2.0)
      rspec-support (~> 3.5.0)
    rspec-support (3.5.0)
    rubocop (0.41.2)
      parser (>= 2.3.1.1, < 3.0)
      powerpack (~> 0.1)
      rainbow (>= 1.99.1, < 3.0)
      ruby-progressbar (~> 1.7)
      unicode-display_width (~> 1.0, >= 1.0.1)
    ruby-progressbar (1.8.1)
    unicode-display_width (1.1.3)
    zookeeper (1.4.11)

PLATFORMS
  ruby

DEPENDENCIES
  inifile
  rspec
  rubocop
  zookeeper

BUNDLED WITH
   1.14.5
```


# bundleコマンドについて

### bundle自身をアップデートする
bundle installなどを実行して、gem install xxxしろなんてエラーが出てきた場合に、bundle自身をアップデートすることでうまくいくことがあります。
gem update --systemなどをした時に同時にやるべしと覚えておくといいかもしれない
```
$ bundle -v
Bundler version 1.2.3
$ gem update bundler
Updating installed gems
Updating bundler
Fetching: bundler-1.14.5.gem (100%)
Successfully installed bundler-1.14.5
Parsing documentation for bundler-1.14.5
Installing ri documentation for bundler-1.14.5
Installing darkfish documentation for bundler-1.14.5
Done installing documentation for bundler after 16 seconds
Parsing documentation for bundler-1.14.5
Done installing documentation for bundler after 7 seconds
Gems updated: bundler
$ bundle -v
Bundler version 1.14.5
```

### Gemfileに従ってインストールを実行する
Bundlerによってインストールするgemをデフォルト（$BUNDLE_PATHまたは$GEM_HOME）のディレクトリ以外にする。
```
$ bundle install --path vendor/bundle
```

なお、システムディレクトリにインストールする場合には
```
$ bundle install --system
```


### bundle installでインストールしたパッケージを更新したい
Gemfileに従って最新版など取得できるものは以下のコマンドによりインストールパッケージを更新することができます。  
ただし、Gemfileに固定バージョンで記述されたものは対象外です。
```
$ bundle update
```

### コマンドを実行する
Bundlerでインストールされたgemパッケージを使用してコマンドを実行します。
```
$ bundle exec rspec
```

### withoutオプションが効かない
以下のファイルを見てみると良い。自動的にWITHOUTが指定されるオプションが指定されているかもしれない。
```
$ cat .bundle/config
```

### Gemfileの雛形を作成する
bundle initを実行するとGemfileの雛形を生成します。
```
$ bundle init
$ ls 
Gemfile
$ cat Gemfile 
# frozen_string_literal: true
source "https://rubygems.org"

# gem "rails"
```

### bundleからインストールされた一覧を表示する
```
$ bundle list
Gems included by the bundle:
  * ast (2.3.0)
  * bundler (1.14.5)
  * diff-lcs (1.3)
  * inifile (3.0.0)
  * parser (2.4.0.0)
  * powerpack (0.1.1)
  * rainbow (2.2.1)
  * rspec (3.5.0)
  * rspec-core (3.5.4)
  * rspec-expectations (3.5.0)
  * rspec-mocks (3.5.0)
  * rspec-support (3.5.0)
  * rubocop (0.41.2)
  * ruby-progressbar (1.8.1)
  * unicode-display_width (1.1.3)
  * zookeeper (1.4.11)
```

### bundleからインストールしたパッケージが依存関係を満たしているかどうかを確認する
```
$ bundle check 
Resolving dependencies...
The Gemfile's dependencies are satisfied
```

### MEMO
```
bundle install	依存ライブラリのインストール
bundle update	依存ライブラリのアップデート
bundle package	依存ライブラリを「vender/cache」以下にまとめる
bundle check	依存ライブラリがインストールされているかチェック
bundle list	インストールされているライブラリの一覧
bundle show	gemファイルのソースのパスを表示
bundle init	gemを初期化
```

### bundleコマンドが読み込む設定について
次の順番で探索します。見つけたものが読み込まれます。
```
1. Railsルート下の .bundle/config
2. 環境変数
3.  .bundle/config
```

```
$ ls .bundle/config
ls: cannot access .bundle/config: No such file or directory
$ bundle config --local build.nokogiri --use-system-libraries
You are replacing the current local value of build.nokogiri, which is currently nil
$ cat .bundle/config 
---
BUNDLE_BUILD__NOKOGIRI: "--use-system-libraries"
```

bundle configについては以下のドキュメントをみるといいかもしれない
- http://ruby.studio-kingdom.com/bundler/bundle_config/
- http://bundler.io/v1.3/man/bundle-config.1.html

# TODO
- budnle configについてもっと深く
  - http://bundler.io/v1.3/man/bundle-config.1.html

# 参考URL
- http://railsdoc.com/references/gemfile
  - gemfile公式ドキュメント
- http://qiita.com/oshou/items/6283c2315dc7dd244aef
