
## TIPS

### コミットメッセージをtypoしたのでやり直したい場合
```
$ git commit # コミットメッセージでtypoした
$ git commit --amend # 入力しなおす
```

### ブランチを切り忘れてmasterでコミットしてしまった
その時点でブランチを切る&reset --hardで間違ったコミットたちをmasterから消せばよい
```
$ git checkout -b new-branch
# masterの最新コミットを消す
$ git checkout master && git reset --hard HEAD~
```

### 間違ったコミットをプッシュしてしまった
個人プロジェクトならコミットを消して反則技のgit push -fする．そうでないなら，可能な限り速やかにgit revertを使って「間違ったコミットを打ち消すコミット」を行ない，pushする


## 設定関連
### アカウントや️パスワードを省略する方法
2つ方法が存在する。
(1) ~/.netrcに記述する。
```
machine github.com
login tarou
password xxxxxxx
```

(2) git cloneするURLに埋め込む
```
$ git clone https://<username>:<password>@github.com/tarou/sandbox.git
```

- 参考URL
 - http://shoken.hatenablog.com/entry/20120629/p1

### vimでUTF8がバイナリと扱われて表示できない場合
以下の設定を加えればOK
```
$ vi ~/.vimrc
set fileencoding=japan
set fileencodings=iso-2022-jp,utf-8,euc-jp,ucs-2le,ucs-2,cp932 
```

- 参考URL
 - http://www.itmedia.co.jp/help/tips/linux/l0671.html

### githubでエディタを設定する場合
以下のエラーが表示される
```
"error: There was a problem with the editor 'vi'."
```

下記コマンドで設定することができる。
```
$ config --global core.editor vim
```

設定の確認は

```
$ less ~/.gitconfig

[core]
        editor = vim
```

- 参考
 - http://qiita.com/shibushun@github/items/1745c3c2092d8d15c34b

### GITでバージョン管理したくないファイルを指定する場合
.gitignoreというファイルに管理したくないファイルを記述します。

```
$ cat .gitignore
TODO*
*.swp
```

- 参考
 - http://inkdesign.jp/posts/notes/gitignore/