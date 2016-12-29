# cocoapodsについて

### ▪️インストール+初期設定
```
$ sudo gem install cocoapods
$ pod setup
```

###▪️podspecファイルの雛形を生成する。
```
$ pod spec create <projectname>
```

###▪️podspecの構文チェックをする
```
$ pod spec lint xxx.podspec
```

### レポジトリを表示する
```
$ pod repo

master
- Type: git (master)
- URL:  https://github.com/CocoaPods/Specs.git
- Path: /Users/tsuyoshi/.cocoapods/repos/master

myrepo
- Type: git (master)
- URL:  https://github.com/tsuyopon/podspec.git
- Path: /Users/tsuyoshi/.cocoapods/repos/myrepo

2 repos
```

### レポジトリ追加
```
$ pod repo add myrepo https://github.com/tsuyopon/podspec.git
$ pod repo
$ pod search rssmanager
-> rssmanager (0.0.1)
   Rss manager.
   pod 'rssmanager', '~> 0.0.1'
   - Homepage: https://github.com/tsuyopon
   - Source:   git@github.com:tsuyopon/rssmanager.git
   - Versions: 0.0.1 [myrepo repo]
```

▪️パッケージ一覧を確認する。
```
$pod list
```

▪️podで利用可能なプラグイン一覧を表示する。
```
$ pod plugins
```

うまく更新できない
```
$ cat ~/.cocoapods/repos/myrepo/rssmanager_ios/0.0.1/rssmanager_ios.podspec 
$ pod repo remove myrepo
$ pod repo add myrepo https://github.com/tsuyopon/podspec.git
$ pod setup
```

### ローカルに存在するpodspecファイルをチェックする。
```
$ pod lib lint ~/.cocoapods/repos/myrepo/rssmanager/0.0.1/rssmanager.podspec 

 -> rssmanager (0.0.1)
    - ERROR | [iOS] The `source_files` pattern did not match any file.

[!] rssmanager did not pass validation.
You can use the `--no-clean` option to inspect any issue.
```

# 参考URL
- podspec逆引き
 - http://qiita.com/makoto_kw/items/447448d8fcabc4a9e8e0
