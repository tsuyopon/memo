# 概要
git checkoutについて

# 詳細

### ローカルで行った変更を破棄する
ファイル名を指定する
```
$ git checkout HEAD -- dir/xxxx
```

これだけでもいけるらしい
```
$ git checkout -- <file_name>
```

なお、--がついているのはその後の文字列をオプションではなくただの引数として解釈させるため
```
$ git checkout master      // master ブランチをチェックアウト
$ git checkout -- master   // masterというファイル名をチェックアウト
```

### タグの状態をチェックアウトする
```
$ git checkout <タグ名>
```

ローカルで行った変更を全て破棄してcheckoutするには-f(force)を付与する
```
$ git checkout -f <タグ名>
```

### 特定のブランチをチェックアウトする
```
$ git branch -a
* master 
  remotes/origin/HEAD
  remotes/origin/master
  remotes/origin/develop
```
上記で確認できたら特定のブランチをorigin/developのように指定する。以下ではdevelopという名称でブランチをチェックアウトしている。
```
$ git checkout -b develop origin/develop
```

上記ではブランチdevelopを作成していますが作成したくない場合には次のようにすることも可能です。(TODO: コマンド実行未確認)
```
$ git checkout remotes/origin/develop
```

### 特定のコミットをチェックアウトする
```
$ git checkout <commit_id>
```

### ブランチの作成と同時にそのブランチに切り替える
```
$ git checkout -b bugfix
```
