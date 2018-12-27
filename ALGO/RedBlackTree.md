# 概要
平衡二分木の赤黒木について

-  特徴
  - 最悪のケースにおける計算量が「データ挿入」、「データ削除」、「データ検索」のいずれにおいてもデータ構造のうちで最善であることを保証します。最悪時間計算量がO(log n)（nはツリーの要素数）と短い。
    - このため、リアルタイムコンピューティングのような時間計算量に敏感なアプリケーションにおいて有益である。
  - 最大でかかる探索でも、最短で表される根から葉までの２倍以内であることを保証します。
  - アルゴリズムが複雑である
  - std::map、LinuxカーネルのCFT(Completely Fair Scheduler)でもこのアルゴリズムが利用されています。


# アルゴリズム概要
通常の二分探索木であることの他にも、次の条件が与えられる。
- 1. 各ノードは赤か黒の色を持つ
- 2. 根は黒である
- 3. 葉(NIL)は全て黒である。葉は全て根と同じ色になる。
- 4. 赤ノードは黒ノードを２つ子に持つ
- 5. 任意のノードにおいて、そのノードから子孫の葉までの道に含まれている黒ノードの数は葉によらず一定の数となる

このアルゴリズムはデータの挿入や削除の場合分けをするのが大変である。

文字だけではわかりにくいので以下の資料がその手助けをしてくれるだろう。
- http://wwwa.pikara.ne.jp/okojisan/rb-tree/index.html

# 参考
- Red-Black Tree by Java -- これで分かった赤黒木
  - Javaと記述してはいるがアルゴリズムの概念的な資料としては図もちゃんと記載されていてもっともわかりやすい神資料。
  - http://wwwa.pikara.ne.jp/okojisan/rb-tree/index.html
- std::mapを線形探索してはいけない100の理由 (スライド)
  - 赤黒木でどのように値が参照されるのかをスライドでわかりやすく説明してくれています。
  - https://www.slideshare.net/kikairoya/map-17091504
- wikipedia: 赤黒木
  - https://ja.wikipedia.org/wiki/%E8%B5%A4%E9%BB%92%E6%9C%A8
  - 赤黒木のアルゴリズム詳細はenのwikipediaで説明されている方が丁寧である。
- Linux カーネル 2.6 Completely Fair Scheduler の内側
  - https://www.ibm.com/developerworks/jp/linux/library/l-completely-fair-scheduler/index.html



