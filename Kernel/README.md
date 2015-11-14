Linux Kernelについて
============================

### 注意点
- このディレクトリ配下のメモは全てバージョンは2.6.16を想定している(現在では最新版は4系になっているので注意すること)

### Linuxバージョンについて
3.0以降は３つの数からバージョンが成立します。  
例えば、3.1.4 の場合、以下を表しているようです。
```
「メジャー・バージョン」． 「リビジョン」． 「パッチ番号」
```

- 現在開発が進められいるのは、3.2 系列。
- 新しい機能は、リビジョンが上がる所で入る。 例: 3.2 の次は、3.3 。
- 重大な問題がバグが見つかると、パッチが出される。例: 3.1.{1,2,3,...}
- 開発中、リリース前には、release candidate として-rc1, -rc2, -rc3 のよう出される。 

2.6 系列は、4つの数からバージョンが成立しています。 例えば、2.6.26.1 といった場合以下を表しています。
```
「メジャー・バージョン」． 「マイナー・バージョン」． 「リビジョン」． 「パッチ番号」 
```