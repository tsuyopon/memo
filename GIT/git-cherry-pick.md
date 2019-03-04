# 概要
git cherry-pickコマンドについて

# 詳細
### マージブランチをcherry pickする

例えば、次のようなグラフになるようにコミットを行うとします。これは次のような操作が行われています。
- (1) first.txtを直接コミット
- (2) second_1.txt, second_2.txtについては別の派生ブランチからPR経由によりマージされる。
- (3) third_1.txt, third_2.txt, third_3.txt, third_4.txt, third_5.txtについても別の派生ブランチからのPR経由によりマージされる。

```
$ git log --graph 
*   commit 0dae1432a8b2455c1c4d7edfa94c1189cc917fd1
|\  Merge: 25ff275 ad1c949
| | Author: Tsuyoshi Ooishi <tsuyoshiooishi@yahoo.co.jp>
| | Date:   Tue Mar 5 01:53:53 2019 +0900
| | 
| |     Merge pull request #3 from tsuyopon/master_2_1
| |     
| |     Master 2 1
| |   
| * commit ad1c9492e02aa0f70041524c82198d560391c5ee
| | Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
| | Date:   Tue Mar 5 01:53:01 2019 +0900
| | 
| |     add third_5.txt
| |   
| * commit ed9b18ff285a472cff5869cffb068daea8ff15db
| | Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
| | Date:   Tue Mar 5 01:52:57 2019 +0900
| | 
| |     add third_4.txt
| |   
| * commit 20cd9971f854565a4ecb634bc32a6c1292e5164b
| | Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
| | Date:   Tue Mar 5 01:52:53 2019 +0900
| | 
| |     add third_3.txt
| |   
| * commit c6321d8055308a739630886cb35e7677315ac743
| | Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
| | Date:   Tue Mar 5 01:52:44 2019 +0900
| | 
| |     add third_2.txt
| |   
| * commit 572e793a023fe767943980d6f1c1668fde121e7d
| | Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
| | Date:   Tue Mar 5 01:52:40 2019 +0900
| | 
| |     add third_1.txt
| |     
* |   commit 25ff275fa54b4c4cb2180419f3cce68289e9afe5
|\ \  Merge: 78d2b22 01c875a
| | | Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
| | | Date:   Tue Mar 5 01:37:17 2019 +0900
| | | 
| | |     Merge branch 'master_2' of https://github.com/tsuyopon/test into master_2
| | |      
| * |   commit 01c875ae643b4ecc90ce2131f75c00619d73c7aa
| |\ \  Merge: aba11c9 882d9f0
| | |/  Author: Tsuyoshi Ooishi <tsuyoshiooishi@yahoo.co.jp>
| | |   Date:   Tue Mar 5 01:33:07 2019 +0900
| | |   
| | |       Merge pull request #1 from tsuyopon/master_2_1
| | |       
| | |       Master 2 1
| | |    
| | * commit 882d9f0b0f19744e0dbec64bc0db948a0feb8a03
| | | Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
| | | Date:   Tue Mar 5 01:32:27 2019 +0900
| | | 
| | |     added second_2.txt
| | |    
| | * commit e2137f73fc8d549598cb98908505646fbf13b825
| |/  Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
| |   Date:   Tue Mar 5 01:32:13 2019 +0900
| |   
| |       added second_1.txt
| |   
* | commit 78d2b22a272529ce503552edfec483db914bddd2
|/  Author: tsuyopon <tsuyoppy@r2.dion.ne.jp>
|   Date:   Tue Mar 5 01:36:50 2019 +0900
|   
|       added first.txt
|  
....
```

たとえば、masterから派生したmaster_branchというブランチに対して(1)〜(3)をcherry-pickして追加する場合には次のようになります。
マージの場合には"-m"オプションを付与しないとマージすることができません。
```
$ git cherry-pick 78d2b22a272529ce503552edfec483db914bddd2
$ git cherry-pick -m 1 25ff275fa54b4c4cb2180419f3cce68289e9afe5
$ git cherry-pick -m 1 0dae1432a8b2455c1c4d7edfa94c1189cc917fd1
```

"-m 1"と"-m 2"にはどのような意味があるのかというと派生元へのマージか、派生先へのマージかといった点で異なります。
```
      X-Y-Z
     /     \
...-A-B-C-D-E-...
```

- A-B-C-D-Eとコミット進化してきた**派生元ブランチ**に対してX, Y, Zの内容をマージする。
```
git cherry-pick -m 1 E
```

- 大元のAから分岐してX-Y-Zとコミット進化した**派生先ブランチ**に対してB, C, Dの内容をマージする。
```
git cherry-pick -m 2 E
```

- 参考: https://qiita.com/takc923/items/8e2d87d692f840b14464


