# 概要
各種パフォーマンスの参考値について

# 詳細
### 各種処理パフォーマンス
```
L1キャッシュ参照                                   0.5ns
分岐予測ミス                                         5ns
L2キャッシュ参照                                     7ns
Mutexのlock/unlock                                  25ns
メモリ参照                                         100ns
1KBをZIP圧縮                                     3,000ns
1Gbpsで2KB送る                                  20,000ns
メモリから1MB連続で読む                        250,000ns
同一のデータセンター内のマシンと通信1往復      500,000ns
HDDシーク                                   10,000,000ns
HDDから1MB読み出し                          20,000,000ns
カリフォルニアとオランダ間で通信1往復      150,000,000ns
```

ざっくりいうとO(N)で示すと
```
レジスタ        O(1ns)
キャッシュ      O(10ns)
メインメモリ    O(100ns)
ハードディスク  O(10,000,000ns)
```

### 人間の待ち時間の感じ方
```
    〜16ミリ秒：対話型アニメーションのフレーム動作
    100ミリ秒：ユーザが瞬間的だと感じる速さ
    200ミリ秒：典型的な人間の反応速度
    500ミリ秒〜：認知できるくらいの遅さ
    3秒〜：反応が鈍いと感じる遅さ
    10秒〜：待っていられない遅さ
```

- プロファイラは本当に必須か？―パフォーマンスについて考える
  - http://postd.cc/thinking-about-performance/


### 様々な地域からの速度を計測する(Global latency testing tool)
以下のurlパラメータに指定すると様々な場所から測定することが可能となる。
- https://latency.apex.sh/?url=https%3A%2F%2Fwww.yahoo.co.jp

# 参考URL
- 全盛期のJeff Dean伝説
  - http://qiita.com/umegaya/items/ef69461d6f4967d5c623
- プロファイラは本当に必須か？―パフォーマンスについて考える(POSTD)
  - http://postd.cc/thinking-about-performance/
