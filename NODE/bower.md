# 概要
フロントエンドライブラリの管理用フレームワークbowerについて

# bower.jsonを生成し、使う
まずはbower installでライブラリをインストールします。 bowerも-gをつけるとグローバルになります。
```
$ bower install <package> --save       // dependencies
$ bower install <package> --save-dev   // devDependencies
```

次のコマンドを実行したらbower.jsonを生成するために必要な情報を尋ねられます。完了したらbower.jsonが生成されます。
```
$ bower init
```

bower.jsonがディレクトリにあると次のコマンドで記述されている全てがインストールされます。
```
$ bower install
```

次のようにしてHTMLなどにタグを埋め込めば利用することができます。
```
<script src="bower_components/jquery/dist/jquery.min.js"></script>
```

### install
```
# installs the project dependencies listed in bower.json
$ bower install
# registered package
$ bower install jquery
# GitHub shorthand
$ bower install desandro/masonry
# Git endpoint
$ bower install git://github.com/user/package.git
# URL
$ bower install http://example.com/script.js
```

### update
```
$ npm update bower
```

### remove
```
$ bower uninstall パッケージ名 --save
```

### インストール済みパッケージの表示
```
$ bower list
```

### 情報を表示する
```
$ bower info 
```

### 探す(search)
```
$ bower search <package>
```

### 登録する。登録を解除する
- register
```
$ bower register <my-package-name> <git-endpoint>
# for example
$ bower register example git://github.com/user/example.git
```

- unregister
```
$ bower unregister <package>
```

### .bowerrcを利用する
bowerを実行するディレクトリに.bowerrcを置いておけば、記述した設定が反映されます。
```
{
  "directory": "public/components",
  "json": "bower.json"
}
```

- "directory"はdependenciesのインストール先を指定します。
- "json"はbowerの設定ファイルの名称を設定出来ます。

# 参考URL
- http://qiita.com/oreo3@github/items/eb790fc091aa28af8d33
- https://github.com/bower/bower
