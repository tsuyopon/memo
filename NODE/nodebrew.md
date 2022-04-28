# 概要
nodebrew は Node.js のバージョン管理ツールです。nodebrew を使うと複数のバージョンの Node.js を切り替えて利用することができます。

nodebrew 以外にも nodenv や nvm などの Node.js のバージョン管理ツールがあります。
nodenv はディレクトリごとに利用するnodeバージョンを切り替えることができるので、そのような環境が必要な用途にはnodenvがあっているかもしれません。

nodebrewは非常に学習コストもかからないシンプルなシステムとして、自分の利用用途としては現状こちらで十分です。


インストールの流れは以下の通りです。
- 1. Homebrew をインストール
- 2. nodebrew をインストール
- 3. Node.js をインストール



# 詳細
### brewでインストールされたnodeや、別でインストールされたnpmをuninstallして、nodebrewをセットアップする。


npmでインストールしたパッケージやnodeがbrewからインストールされたものかをあらかじめ確認しておきます。
```
$ sudo npm list -g
/usr/local/lib
└── npm@7.13.0
$ brew list | grep node
node
```

npmをアンインストールする
```
$ sudo npm uninstall npm -g
```

nodeを削除します。
```
$ brew uninstall node
Uninstalling /usr/local/Cellar/node/16.2.0... (2,784 files, 49MB)
```

関連ファイルも削除します。
```
$ rm -rf ~/.npm/ ~/node_modules/
```


では、インストールを行います。
```
$ brew install nodebrew
```

上記コマンド実行時に出力される下記に従ってパスを通します。自分は.bashrcにパス設定を追記した。
```
Add path:
  export PATH=$HOME/.nodebrew/current/bin:$PATH

To use Homebrew's directories rather than ~/.nodebrew add to your profile:
  export NODEBREW_ROOT=/usr/local/var/nodebrew
```

引き続きセットアップを行います。以下を実行すると$HOME/.nodebrewに必要なファイル等が配置されます。
```
$ nodebrew setup
Fetching nodebrew...
Installed nodebrew in $HOME/.nodebrew

========================================
Export a path to nodebrew:

export PATH=$HOME/.nodebrew/current/bin:$PATH
========================================
$ ls $HOME/.nodebrew
completions current     default     iojs        node        nodebrew    src
```


nodeをインストールする。以下の例ではstableをインストールしています。
```
$ nodebrew install stable
Fetching: https://nodejs.org/dist/v18.0.0/node-v18.0.0-darwin-x64.tar.gz
####################################################################################################################################################################################### 100.0%
Installed successfully
```

インストールしたバージョンを確認する
```
$ nodebrew list
v18.0.0

current: none
```

この状態ではまだ使えない状態です。
```
$ node -v
-bash: node: command not found
```

使いたいnodeバージョンを指定する
```
$ nodebrew use v18.0.0
use v18.0.0
```

以上で利用できるようになりました。
```
$ node -v
v18.0.0
```


### インストールする
いくつかの指定方法があります。install-binaryというオプションの方がコンパイルせずに早いとありましたが、自分試したnodebrew 1.2.0ではinstallもおそらくバイナリを取得していたと思います。
```
// stableをインストールする
$ nodebrew install stable

// latestをインストールする
$ nodebrew install latest

// v8.9のlatest版をインストールする
$ nodebrew install v8.9   # v8.9 latest

// バージョン固定でインストールする
$ nodebrew install v8.9.4       // v8.9.4のvは省略可能
```

### アンインストールする

```
// アンインストール
$ nodebrew uninstall v8.9.4

// ソースファイルも削除する
$ nodebrew clean v8.9.4
```


### インストール可能なバージョンを確認する
nodebrewからインストール可能なバージョンを確認することができます。

```
$ nodebrew ls-remote

(snip)

v6.0.0    v6.1.0    v6.2.0    v6.2.1    v6.2.2    v6.3.0    v6.3.1    v6.4.0
v6.5.0    v6.6.0    v6.7.0    v6.8.0    v6.8.1    v6.9.0    v6.9.1    v6.9.2
v6.9.3    v6.9.4    v6.9.5    v6.10.0   v6.10.1   v6.10.2   v6.10.3   v6.11.0
v6.11.1   v6.11.2   v6.11.3   v6.11.4   v6.11.5   v6.12.0   v6.12.1   v6.12.2
v6.12.3   v6.13.0   v6.13.1   v6.14.0   v6.14.1   v6.14.2   v6.14.3   v6.14.4
v6.15.0   v6.15.1   v6.16.0   v6.17.0   v6.17.1   

v7.0.0    v7.1.0    v7.2.0    v7.2.1    v7.3.0    v7.4.0    v7.5.0    v7.6.0
v7.7.0    v7.7.1    v7.7.2    v7.7.3    v7.7.4    v7.8.0    v7.9.0    v7.10.0
v7.10.1   

v8.0.0    v8.1.0    v8.1.1    v8.1.2    v8.1.3    v8.1.4    v8.2.0    v8.2.1
v8.3.0    v8.4.0    v8.5.0    v8.6.0    v8.7.0    v8.8.0    v8.8.1    v8.9.0
v8.9.1    v8.9.2    v8.9.3    v8.9.4    v8.10.0   v8.11.0   v8.11.1   v8.11.2
v8.11.3   v8.11.4   v8.12.0   v8.13.0   v8.14.0   v8.14.1   v8.15.0   v8.15.1
v8.16.0   v8.16.1   v8.16.2   v8.17.0   

v9.0.0    v9.1.0    v9.2.0    v9.2.1    v9.3.0    v9.4.0    v9.5.0    v9.6.0
v9.6.1    v9.7.0    v9.7.1    v9.8.0    v9.9.0    v9.10.0   v9.10.1   v9.11.0
v9.11.1   v9.11.2   

v10.0.0   v10.1.0   v10.2.0   v10.2.1   v10.3.0   v10.4.0   v10.4.1   v10.5.0
v10.6.0   v10.7.0   v10.8.0   v10.9.0   v10.10.0  v10.11.0  v10.12.0  v10.13.0
v10.14.0  v10.14.1  v10.14.2  v10.15.0  v10.15.1  v10.15.2  v10.15.3  v10.16.0
v10.16.1  v10.16.2  v10.16.3  v10.17.0  v10.18.0  v10.18.1  v10.19.0  v10.20.0
v10.20.1  v10.21.0  v10.22.0  v10.22.1  v10.23.0  v10.23.1  v10.23.2  v10.23.3
v10.24.0  v10.24.1  

v11.0.0   v11.1.0   v11.2.0   v11.3.0   v11.4.0   v11.5.0   v11.6.0   v11.7.0
v11.8.0   v11.9.0   v11.10.0  v11.10.1  v11.11.0  v11.12.0  v11.13.0  v11.14.0
v11.15.0  

v12.0.0   v12.1.0   v12.2.0   v12.3.0   v12.3.1   v12.4.0   v12.5.0   v12.6.0
v12.7.0   v12.8.0   v12.8.1   v12.9.0   v12.9.1   v12.10.0  v12.11.0  v12.11.1
v12.12.0  v12.13.0  v12.13.1  v12.14.0  v12.14.1  v12.15.0  v12.16.0  v12.16.1
v12.16.2  v12.16.3  v12.17.0  v12.18.0  v12.18.1  v12.18.2  v12.18.3  v12.18.4
v12.19.0  v12.19.1  v12.20.0  v12.20.1  v12.20.2  v12.21.0  v12.22.0  v12.22.1
v12.22.2  v12.22.3  v12.22.4  v12.22.5  v12.22.6  v12.22.7  v12.22.8  v12.22.9
v12.22.10 v12.22.11 v12.22.12 

v13.0.0   v13.0.1   v13.1.0   v13.2.0   v13.3.0   v13.4.0   v13.5.0   v13.6.0
v13.7.0   v13.8.0   v13.9.0   v13.10.0  v13.10.1  v13.11.0  v13.12.0  v13.13.0
v13.14.0  

v14.0.0   v14.1.0   v14.2.0   v14.3.0   v14.4.0   v14.5.0   v14.6.0   v14.7.0
v14.8.0   v14.9.0   v14.10.0  v14.10.1  v14.11.0  v14.12.0  v14.13.0  v14.13.1
v14.14.0  v14.15.0  v14.15.1  v14.15.2  v14.15.3  v14.15.4  v14.15.5  v14.16.0
v14.16.1  v14.17.0  v14.17.1  v14.17.2  v14.17.3  v14.17.4  v14.17.5  v14.17.6
v14.18.0  v14.18.1  v14.18.2  v14.18.3  v14.19.0  v14.19.1  

v15.0.0   v15.0.1   v15.1.0   v15.2.0   v15.2.1   v15.3.0   v15.4.0   v15.5.0
v15.5.1   v15.6.0   v15.7.0   v15.8.0   v15.9.0   v15.10.0  v15.11.0  v15.12.0
v15.13.0  v15.14.0  

v16.0.0   v16.1.0   v16.2.0   v16.3.0   v16.4.0   v16.4.1   v16.4.2   v16.5.0
v16.6.0   v16.6.1   v16.6.2   v16.7.0   v16.8.0   v16.9.0   v16.9.1   v16.10.0
v16.11.0  v16.11.1  v16.12.0  v16.13.0  v16.13.1  v16.13.2  v16.14.0  v16.14.1
v16.14.2  v16.15.0  

v17.0.0   v17.0.1   v17.1.0   v17.2.0   v17.3.0   v17.3.1   v17.4.0   v17.5.0
v17.6.0   v17.7.0   v17.7.1   v17.7.2   v17.8.0   v17.9.0   

v18.0.0   

io@v1.0.0 io@v1.0.1 io@v1.0.2 io@v1.0.3 io@v1.0.4 io@v1.1.0 io@v1.2.0 io@v1.3.0
io@v1.4.1 io@v1.4.2 io@v1.4.3 io@v1.5.0 io@v1.5.1 io@v1.6.0 io@v1.6.1 io@v1.6.2
io@v1.6.3 io@v1.6.4 io@v1.7.1 io@v1.8.1 io@v1.8.2 io@v1.8.3 io@v1.8.4 

io@v2.0.0 io@v2.0.1 io@v2.0.2 io@v2.1.0 io@v2.2.0 io@v2.2.1 io@v2.3.0 io@v2.3.1
io@v2.3.2 io@v2.3.3 io@v2.3.4 io@v2.4.0 io@v2.5.0 

io@v3.0.0 io@v3.1.0 io@v3.2.0 io@v3.3.0 io@v3.3.1 
```

ls-allを使うとremoteとlocal双方の状態を表示します。
```
$ nodebrew ls-all
remote:

(snip)

v16.0.0   v16.1.0   v16.2.0   v16.3.0   v16.4.0   v16.4.1   v16.4.2   v16.5.0
v16.6.0   v16.6.1   v16.6.2   v16.7.0   v16.8.0   v16.9.0   v16.9.1   v16.10.0
v16.11.0  v16.11.1  v16.12.0  v16.13.0  v16.13.1  v16.13.2  v16.14.0  v16.14.1
v16.14.2  v16.15.0  

v17.0.0   v17.0.1   v17.1.0   v17.2.0   v17.3.0   v17.3.1   v17.4.0   v17.5.0
v17.6.0   v17.7.0   v17.7.1   v17.7.2   v17.8.0   v17.9.0   

v18.0.0   

(snip)

io@v3.0.0 io@v3.1.0 io@v3.2.0 io@v3.3.0 io@v3.3.1 

local:
v18.0.0

current: v18.0.0
```


### バージョンにエイリアスを付与する

```
$ nodebrew alias default v8.9.4
default -> v8.9.4

$ nodebrew use default
use v8.9.4

$ nodebrew unalias default
remove default
```

### 一時的に現在使っているnodeバージョンとは別のバージョンを動かす
```
$ nodebrew exec v8.9.4 -- node app.js
```

### nodebrew自体をupdateする
```
$ nodebrew selfupdate
Fetching nodebrew...
Updated successfully
```

### ソースコードからコンパイルする
ソースコードからコンパイルします。20-30分はかかるとのことですので、理由がなければnodebrew installでインストールするほうが良いかと思います。
M1チップだと14.17.0以降でないと対応していないので、以下のコンパイルオプションが役に立つようです。
```
$ nodebrew compile v14.18.1
```

### nodebrewをアンインストールする
下記のディレクトリを削除するだけらしい
```
$ rm -rf $HOME/.nodebrew
```


### ヘルプを表示する
```
$ nodebrew -h
nodebrew 1.2.0

Usage:
    nodebrew help                         Show this message
    nodebrew install <version>            Download and install <version> (from binary)
    nodebrew compile <version>            Download and install <version> (from source)
    nodebrew install-binary <version>     Alias of `install` (For backward compatibility)
    nodebrew uninstall <version>          Uninstall <version>
    nodebrew use <version>                Use <version>
    nodebrew list                         List installed versions
    nodebrew ls                           Alias for `list`
    nodebrew ls-remote                    List remote versions
    nodebrew ls-all                       List remote and installed versions
    nodebrew alias <key> <value>          Set alias
    nodebrew unalias <key>                Remove alias
    nodebrew clean <version> | all        Remove source file
    nodebrew selfupdate                   Update nodebrew
    nodebrew migrate-package <version>    Install global NPM packages contained in <version> to current version
    nodebrew exec <version> -- <command>  Execute <command> using specified <version>
    nodebrew prune [--dry-run]            Uninstall old versions, keeping the latest version for each major version

Example:
    # install
    nodebrew install v8.9.4

    # use a specific version number
    nodebrew use v8.9.4
```



# 参考
- https://github.com/hokaccha/nodebrew
