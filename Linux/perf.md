# 概要
Linux用のパフォーマンス計測ツールperfについて

# 詳細

### perfの内容をFlame Graphsで可視化する
Flame Graphsはperfを可視化する際に非常に便利なツールです。

root以外でも解析するために以下のカーネルパラメータを変更します。
```
$ echo 0 > /proc/sys/kernel/kptr_restrict
```

FlameGraphからグラフ生成に必要なスクリプトを取得します。
```
$ wget https://raw.githubusercontent.com/brendangregg/FlameGraph/master/stackcollapse-perf.pl
$ wget https://raw.githubusercontent.com/brendangregg/FlameGraph/master/flamegraph.pl
```

perfによるデータを取得します。
```
$ perf record -a -g -F100000 dd if=/dev/zero of=/tmp/test.dat bs=1024K count=1000

perf で取得したデータをテキストに変換する。
$ perf script> perf_data.txt
```

続いて、Flame Graphを生成して可視化する。
```
$ perl stackcollapse-perf.pl perf_data.txt|perl flamegraph.pl --title "Flame Graphs - dd if=/dev/zero of=/tmp/test.dat bs=1024K count=1000" > flamegraph_dd.svg
````

- 参考URL
  - http://d.hatena.ne.jp/yohei-a/20150706/1436208007


# 公式ページ
- FlameGraphs
  - https://github.com/brendangregg/FlameGraph
- perf Examples
  - perfについてもっとも参考になる資料
  - http://www.brendangregg.com/perf.html
- Blazing Performance with Flame Graphs (SlideShare)
  - Flame Graphsの参考資料
  - https://www.slideshare.net/brendangregg/blazing-performance-with-flame-graphs

# 参考資料
- perf + Flame Graphs で Linux カーネル内のボトルネックを特定する 
  - https://yohei-a.hatenablog.jp/entry/20150706/1436208007
- Linux perfで快適に計測するためのtips
  - https://qiita.com/k0kubun/items/b094c4b9bd4fe0027a48


