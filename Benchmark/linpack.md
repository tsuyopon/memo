# 概要
LinpackベンチマークはTop500スーパーコンピューターでの測定指標に利用されるベンチマークです。

# 詳細

### 各種パラメータについて
High Performance Linpack Benchmark(http://www.netlib.org/benchmark/hpl/) は大きく次のパラメータに分かれる。
設定に大きく影響を与えるのは問題サイズN、ブロックサイズNB、プロセスグリッド (P、Q)、Broadcastのトポロジーである。
- 問題サイズN
- ブロックサイズNB
- プロセスグリッド(P、Q)
- 解のチェックにおける残差の境界値
- Panel Factorizationのアルゴリズム
- 再帰的Panel Factorizationのアルゴリズム   
- 再帰的Factorizationにおけるsubpanel数
- 再帰的Factorizationにおけるsubpane幅の最小値
- Panel Broadcastのトポロジー
- Look-aheadの深さ
- Updateにおける通信トポロジー
- longにおけるUの平衡化処理の有無
- mixにおける行数の境界値
- L1パネルの保持の仕方
- Uパネルの保持の仕方
