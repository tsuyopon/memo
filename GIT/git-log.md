# 概要
gitのログについて

## log
### git log
git logだとログの詳細を表示します。
```
$ git log
commit 38288a7ab98de664c91b6e85947277e37cfaf08f
Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
Date:   Wed Sep 6 06:14:31 2017 +0900

    mod about git(git-diff.md, git-ui.md, git.md)

commit ee0ffcbc807bd97265d80ea90c4a7f6829db192f
Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
Date:   Mon Sep 4 09:05:41 2017 +0900

    added new (git-grep.md)

commit 1b29715be1b5453fe4586f7c02022c63f1f3a12f
Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
Date:   Mon Sep 4 08:37:35 2017 +0900

    add trivial(TS/Debugging.md, TS/DocumentLink.md)

commit 7ee8da8d2a7cfde3eff0450e50c68525d6d67b8e
Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
Date:   Mon Sep 4 08:37:17 2017 +0900

    add(rpm_spec.md)
```

引数に数字を指定すると指定されたコミットから指定された数のコミットログだけを表示します。
```
$ git log -2
commit 38288a7ab98de664c91b6e85947277e37cfaf08f
Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
Date:   Wed Sep 6 06:14:31 2017 +0900

    mod about git(git-diff.md, git-ui.md, git.md)

commit ee0ffcbc807bd97265d80ea90c4a7f6829db192f
Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
Date:   Mon Sep 4 09:05:41 2017 +0900

    added new (git-grep.md)
```

### git logの他に変更点も表示する
```
$ git log -p
```

### git logの範囲を指定する
ハッシュ値で表示範囲を範囲指定することが可能である。
```
$ git log 1c26396e..d9e8f42   // ハッシュ値は例
```

特定のコミットだけにする場合
```
$ git log 1c26396e
```

### onelineオプションを付与するとハッシュ値と概要を表示する
```
$ git log --oneline | head -5
38288a7 mod about git(git-diff.md, git-ui.md, git.md)
ee0ffcb added new (git-grep.md)
1b29715 add trivial(TS/Debugging.md, TS/DocumentLink.md)
7ee8da8 add(rpm_spec.md)
6412ac4 new added(rpm_spec.md)
```


### git reflog
```
$ git reflog | tail -5
4f5c32e HEAD@{151}: commit: mod
2508b17 HEAD@{152}: commit: add perl debug
06db4b6 HEAD@{153}: pull: Merge made by the 'recursive' strategy.
2159a97 HEAD@{154}: commit: mod
b454c0b HEAD@{155}: clone: from https://github.com/tsuyopon/memo.git
```

### サブツリーのネットワーク情報も含めて表示
```
$ git log --graph
* commit a8f93924612763507a9f1ba4061318b073012ec4
| Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
| Date:   Tue Jun 27 08:37:48 2017 +0900
| 
|     renamed to IPv4.md and added some
|    
*   commit 6ca0b3a79f496242cb5d293d44b9275f48c86153
|\  Merge: a4f9a43 8395435
| | Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
| | Date:   Mon Jun 26 09:26:14 2017 +0900
| | 
| |     Merge branch 'master' of https://github.com/tsuyopon/memo
| |   
| * commit 8395435dac52de621bd63e996e7122f7f5b467ef
| | Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
| | Date:   Wed Jun 21 05:14:50 2017 +0900
| | 
| |     added rc4 algorithms
| |   
```

onelineを付与すると画面表示がすっきりします。
```
$ git log --graph -oneline
* 8b3d80b git
*   31141b1 Merge branch 'master' of https://github.com/tsuyopon/memo
|\  
| * 0004f9b added A10 loadbalancer configuration
| * 1722314 added RFC.md
* | acd3a4d added how to create mysql patch and mysql query(update, delete) join.
|/  
* 41d29ef added Ethernet.md
* 8794e72 added SlowHttpDos
```

### git logを整形して出力する
```
$ git log --pretty="%h %ai %s" --date-order HEAD | head -5
38288a7 2017-09-06 06:14:31 +0900 mod about git(git-diff.md, git-ui.md, git.md)
ee0ffcb 2017-09-04 09:05:41 +0900 added new (git-grep.md)
1b29715 2017-09-04 08:37:35 +0900 add trivial(TS/Debugging.md, TS/DocumentLink.md)
7ee8da8 2017-09-04 08:37:17 +0900 add(rpm_spec.md)
6412ac4 2017-09-01 08:41:21 +0900 new added(rpm_spec.md)
```

### 単純なメッセージのみを表示する
```
$ git shortlog
tsuyopon(192):
      add
      Merge branch 'master' of https://github.com/tsuyopon/memo
      add
      add
      added ctags
(snip)
```


### 誰が多くコミットしたのか順番でみたい
この場合もshortlogで見れます。オプションは以下に説明していて、例では全て指定しています。
- s: パッチ作成者とコミット数を表示
- e: emailを追加表示する
- n: コミット数の多い順番で並び替える
```
$  git shortlog -e -s -n
   331  tsuyopon2 <tsuyopon2@r2.dion.ne.jp>
   185  tsuyopon3<tsuyoppy3@r2.dion.ne.jp>
     7  hoge <hoge@yahoo.co.jp>
     5  helloworld <helloworld@yahoo.co.jp>
```

## blame

### git blame
git blameのあとにファイル名を指定するとその対象ファイルのblame情報を表示してくれます。
```
$ git blame xxxx.md
6f47d60c (tsuyopon 2017-04-21 08:40:17 +0900   1) # 概要
6f47d60c (tsuyopon 2017-04-21 08:40:17 +0900   2) gitのdiffを見る方法について
6f47d60c (tsuyopon 2017-04-21 08:40:17 +0900   3) 
6f47d60c (tsuyopon 2017-04-21 08:40:17 +0900   4) # 比較方法(ブラウザ)
6f47d60c (tsuyopon 2017-04-21 08:40:17 +0900   5) 
6f47d60c (tsuyopon 2017-04-21 08:40:17 +0900   6) ### ブラウザで比較する
6f47d60c (tsuyopon 2017-04-21 08:40:17 +0900   7) 
```
