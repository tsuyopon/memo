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

### HEADつきのログを表示する
```
$ git log --decorate 
commit 4d71925b570339a1d56a4cdfe314e0b3469e4930 (HEAD, origin/master, origin/HEAD, master)
Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
Date:   Tue Jan 15 08:39:44 2019 +0900

    added .DEFAULT_GOAL

commit 4ffd7c8243976bcf0123af5eb0ec4e3d5317c709
Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
Date:   Mon Jan 14 03:03:55 2019 +0900

    added

commit ba6c6189ac2495bf5b8c56e31e61f01d2a3047c5
Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
Date:   Sun Jan 13 16:59:34 2019 +0900

    added benchmark reference between intel cpu generation
...
```

### ブランチを指定する
git logの後にブランチ名を指定するだけ
```
$ git log remotes/origin/gh-pages
commit 5ec35039942bfde47b7feef7a080fa04f1137a04
Author: helloworld <tsuyoshiooishi@yahoo.co.jp>
Date:   Tue May 5 09:54:47 2015 +0900

    Create gh-pages branch via GitHub
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

ブランチ名を指定することができます。
```
$ git log --graph testbranch
*   commit f0b9f1bfe7dcbe278888fc278d90981477b8f6d1
|\  Merge: 434fde7 bd3dc5d
| | Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
| | Date:   Tue Mar 5 01:46:30 2019 +0900
| | 
| |     Merge branch 'mas1' of https://github.com/tsuyopon/test into mas1
| |     
| *   commit bd3dc5d24d39196359d952168e5382fbcba2739c
| |\  Merge: 6cf200f f77ff34
| | | Author: Tsuyoshi Ooishi <tsuyoshiooishi@yahoo.co.jp>
| | | Date:   Tue Mar 5 01:45:31 2019 +0900
| | | 
| | |     Merge pull request #2 from tsuyopon/mas2
| | |     
| | |     Mas2
| | |    
| | * commit f77ff34cf165ea7d3ebcec4649c0e52d1ccb0342
| | | Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
| | | Date:   Tue Mar 5 01:44:57 2019 +0900
| | | 
| | |     test3
| | |    
| | * commit c489b4adac06b7a38549345cba7502865ac11fb5
| |/  Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
| |   Date:   Tue Mar 5 01:44:46 2019 +0900
| |   
| |       test2.txt
| |   
* | commit 434fde776960506bdd1beb72f8c87adc599e2907
|/  Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
|   Date:   Tue Mar 5 01:46:11 2019 +0900
|   
|       added test.txt
|  
* commit 6cf200f99d4ef50596dad07ab78141dbcc981b7e
  Author: Tsuyoshi Ooishi <tsuyoshiooishi@yahoo.co.jp>
  Date:   Tue Mar 5 01:29:41 2019 +0900
  
      Initial commit
...
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

### 特定の文言が含まれるコミットのみを表示する
```
$ git log --grep mod | tail -10
Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
Date:   Sat Jun 27 02:30:48 2015 +0900

    mod

commit 667492289fb742f5cc2b377b6a0773631da741fd
Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
Date:   Sun Dec 28 22:58:34 2014 +0900

    modified
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

以下はハッシュ値とメールアドレスを表示する例です
```
$ git log --no-merges --pretty=format:"%H %ae" | head -3
43461d8bf19ecc7d51313efa9fa866be16f040f8 tsuyoppy@r2.dion.ne.jp
3a67edcd7945b7932e2a884957a4a68cc8a5fbab tsuyoppy@r2.dion.ne.jp
fccd03b90c2342a77ea373f6ddc2fe1639daf9b5 tsuyoppy@r2.dion.ne.jp
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

上記だけだと直前のblameのハッシュ値しかわかりません。
特定の行に関する更新されたハッシュ値を確認するには次のようにします。
```
$  git log -L 1890,1891:draft-ietf-tls-tls13.md 
```
