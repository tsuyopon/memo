# 概要
rbenv(RuBy ENVironment)は複数のRubyバージョンを管理して、プロジェクトごとにRubyのバージョンを指定して利用することが可能なツールです。

rbenvでインストールされると~/.rbenv/配下に保存されます。

# 詳細

### インストールして、使ってみる(自身のMacBook Proで確認)
rbenvとruby-buildをインストールします。
ruby-buildはUNIX互換環境に異なったバージョンのrubyをコンパイル、インストールするための「rbenv install」コマンドを利用できるようにするプラグインです。
```
$ brew update
$ brew install rbenv ruby-build
$ brew upgrade rbenv
```

以下のコマンドで、rbenvのバージョン確認とインストール可能なrubyのバージョンリストを確認することができます。
```
$ rbenv -v
rbenv 1.1.2
$ rbenv install --list
2.5.8
2.6.6
2.7.1
jruby-9.2.13.0
maglev-1.0.0
mruby-2.1.2
rbx-5.0
truffleruby-20.2.0
truffleruby+graalvm-20.2.0

Only latest stable releases for each Ruby implementation are shown.
Use 'rbenv install --list-all' to show all local versions.
```

今回は2.7.1をインストール
```
$ rbenv install 2.7.1
```

インストールしたRubyを使用可能な状態にする⇒~/.rbenv/shims/への反映が行われる。
```
$ rbenv rehash
```

rubyのバージョンを確認したが、これで切り替わってくれるわけではない。
```
$ ruby --version
ruby 2.3.7p456 (2018-03-28 revision 63024) [universal.x86_64-darwin18]
```

では切り替えを試してみる。が、うまく切り替わらない。
```
$ rbenv global 2.7.1
$ ruby --version
ruby 2.3.7p456 (2018-03-28 revision 63024) [universal.x86_64-darwin18]
```

以下の記事を参考にする。
- https://qiita.com/opiyo_taku/items/3312a75d5916f6cd32b1

次の箇所のrubyのバージョンを確認すると2.7.1になっていることが確認できた。
```
$  /Users/tsuyoshi/.rbenv/shims/ruby --version
ruby 2.7.1p83 (2020-03-31 revision a0c7c23c9c) [x86_64-darwin18]
```

上記のパスにrubyが存在していることがわかったので、あとは.bash_profileに以下を追加して、sourceで読み込ませればよい。
```
export PATH="~/.rbenv/shims:/usr/local/bin:$PATH"
```


### インストール可能なrubyバージョンの確認とインストールの実行
```
$ rbenv install --list
2.5.8
2.6.6
2.7.1
jruby-9.2.13.0
maglev-1.0.0
mruby-2.1.2
rbx-5.0
truffleruby-20.2.0
truffleruby+graalvm-20.2.0

Only latest stable releases for each Ruby implementation are shown.
Use 'rbenv install --list-all' to show all local versions.
$ rbenv install 2.7.1
```

インストールは~/.rbenv/配下に行われます。
ただし、インストールされただけではバージョンが切り替わっておらず"rbenv global"や"rbenv local"での切り替えが必要になります。

### rubyバージョンを変更する
以下では2.5.8と2.7.1が「rbenv install」でインストール済みの想定です。
デフォルトは2.7.1から2.5.8へと切り替えています。
```
$ rbenv versions
  system
  2.5.8
* 2.7.1 (set by /Users/tsuyoshi/.rbenv/version)
$ rbenv global 2.5.8
$ rbenv versions
  system
* 2.5.8 (set by /Users/tsuyoshi/.rbenv/version)
  2.7.1
```

ディストリビューションなどで例えば/usr/bin/rubyにRubyがインストールされていることがある。こういったRubyは system というキーワードで指定することができる。


### rbenv global, rbenv local, rbenv shellの違いについて
以下の違いがあります。
- rbenv global: 全てのシェルで使うデフォルトのRubyバージョンを指定することができるようになります。 
```
参考)
// 2.7.1へと変更する
$ rbenv global 2.7.1

// システムドフォルトへと変更する
$ rbenv global system
```

- rbenv local: 特定のディレクトリで利用すると、そのディレクトリ以下に適用されるRubyのローカルバージョンを指定することができます(rbenv globalよりも優先される)。ローカルバージョンはディレクトリ内部に作られる.ruby-versionファイルに書き込まれます。
```
// ローカルバージョンを指定する。
$ rbenv local 1.9.3-p327

// 指定したローカルバージョンを解除する
$ rbenv local --unset
```

- rbenv shell: コマンドラインから一時的に切り替えたい場合はshellを使います。これは環境変数RBENV_VERSIONに設定されるので、シェルが変わると破棄されます。
```
$ rbenv shell 2.7.1
```

- 参考資料
  - https://qiita.com/makoto_kw/items/cc73b628c9ef039f6e6f

### rbenvで現在利用中のrubyバージョンを確認する
表示されるのはインストール済みのバージョンのみです。利用中のものにはアスタリスクが付与されます。
```
$ rbenv versions
  system
  2.5.8
* 2.7.1 (set by /Users/tsuyoshi/.rbenv/version)
```

なお、versionsではなくversionを指定するとrbenv自体のバージョンを表示するので注意すること
```
$ rbenv version
2.5.8 (set by /Users/tsuyoshi/.rbenv/version)
```

### インストール後のディレクトリ構造について
rbenv installにてインストールされると~/.rbenv/配下に保存されます。
以下は2.5.8や2.7.1をインストールした段階で~/.rbenv/を２階層まで表示させたものです。
```
$ tree ~/.rbenv/ -L 2
/Users/tsuyoshi/.rbenv/
├── shims
│   ├── bundle
│   ├── bundler
│   ├── erb
│   ├── gem
│   ├── irb
│   ├── racc
│   ├── racc2y
│   ├── rake
│   ├── rdoc
│   ├── ri
│   ├── ruby
│   └── y2racc
├── version
└── versions
    ├── 2.5.8
    └── 2.7.1
```

簡単に1階層目までのディレクトリの役割を示しておく

```
~/.rbenv/ （ルートフォルダ）
~/.rbenv/shims/ （rubyやgemがインストールしてくれるコマンドのラッパーを保存するフォルダ）
~/.rbenv/version （グローバルに設定しているRubyバージョンを記録するファイル）
~/.rbenv/versions/ （その他のインストールした各種Rubyバージョンをインストールするフォルダ）
```

### コマンドの実体パスを知る
~/.rbenv/shimsにあるスクリプトが使うコマンド(irb, gem, rake, rails, rubyなど)を振り分けてくれる。shimsが振り分けた先を知るにはrbenv whichを使う。
```
$ rbenv which ruby
/Users/tsuyoshi/.rbenv/versions/2.5.8/bin/ruby
$ rbenv which gem
/Users/tsuyoshi/.rbenv/versions/2.5.8/bin/gem
```

### rbenvでrubyを切り替えて、bundle installでどこにgemが入るのか?
まだ試したことないですが、やるときはこの辺の記事を参考に
- https://bbbbruno.qrunch.io/entries/i9G2lQKOt25LMkjK
- https://mae.chab.in/archives/2612

### gemなどでインストールしたパッケージを、rbenvのrubyでも使いたい場合
bundleなどgemでインストールして新しいコマンドが増える場合は~/.rbenv/shimsに振り分けるスクリプトを置かないといけないのでrbenv rehashを唱える必要がある。
```
$ rbenv rehash
```

### RBENV_VERSION 環境変数

RBENV_VERSION 環境変数が使うバージョンを決める。 これはrbenv shellが行う操作と同じらしい
```
$ export RBENV_VERSION=1.9.3-p392
$ ruby -v
ruby 1.9.3p392 ...
```



# 公式資料
- github  rbenv/rbenv
  - https://github.com/rbenv/rbenv
