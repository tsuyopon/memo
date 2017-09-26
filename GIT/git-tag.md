# 概要
git tagについて

# 詳細

### git tag一覧を表示する
```
$ git tag
v0.1
v0.2
v0.22
```

### git tagを検索して表示する
```
$ git tag -l 'v0.2*'
v0.2
v0.22
```

### ローカルでタグ付けする
```
$ git tag v_1.0.0
```

コメント付きでタグ付けできるのでこちらのほうがいいでしょう
```
$ git tag -a タグ -m 'タグのコメント'
```

### ローカルで付与したタグをリモートに反映する
最後にタグ情報を指定します。
```
$ git push origin v_1.0.0
```

### タグ情報を確認する
git showの後にタグ名を入力するだけです。つぎのような情報が出力されます。
```
$ git show v1.4
tag v1.4
Tagger: Scott Chacon <schacon@gee-mail.com>
Date:   Mon Feb 9 14:45:11 2009 -0800

my version 1.4

commit 15027957951b64cf874c3557a0f3547bd83b3ff6
Merge: 4a447f7... a6b4c97...
Author: Scott Chacon <schacon@gee-mail.com>
Date:   Sun Feb 8 19:02:46 2009 -0800

    Merge branch 'experiment'
```

### ローカルで付与したタグをすべてremote側に反映する
```
$ git push origin --tags
```

### 過去のコミットに対してタグ付けする
```
$ git log --pretty=oneline

hogehoge1 dev
fugafuga1 pre
fufufufu1 prod

$ git tag pre_v1.0.0 fugafuga1
```

### タグを削除する
ローカルのタグを削除する
```
git tag -d v1.0.0
```

リモートサーバにタグ削除を反映する。タグ名の前にコロンがあることに注意する
```
git push origin :v1.0.0
```

### gitタグをPULLする
```
$ git pull upstream --tags
```


# 参考URL
- https://git-scm.com/book/ja/v1/Git-%E3%81%AE%E5%9F%BA%E6%9C%AC-%E3%82%BF%E3%82%B0
