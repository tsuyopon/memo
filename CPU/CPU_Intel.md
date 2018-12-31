# Intel CPUについて

次のようなブランドが存在しています。
- Xeon(企業向けの高価格CPU)
- Core i9(超高性能。第７世代から登場)
- Core i7(高機能＆高価格CPU。Core2 Quadの最新型的なイメージ)
- Core i5(一般向けの高機能なCPU。Core2 Duoの最新型なイメージ)
- Core i3(ファミリー向けの高機能向けでないCPU)
- Core 2 Quad(i7 の前に主流だったCPU)
- Core i3(価格も性能も標準のCPU)
- Core 2 Duo(i5 と Quad の前に主流)
- Pentium(i3より低機能＆低価格)
- Celeron(かなり機能を抑えた廉価版)
- Atom(性能と消費電力が最も低い CPU)


# Intel Core i9, Core i7, Core i5, Core i3の世代について

### Core i9, Core i7, Core i5, Core i3の違いについて　
Core i9については第７世代から登場しています。

- Core i9: 超最高性能
- Core i7: 高性能で動画編集、エンコード、画像編集、高度な描画を必要とするオンラインゲームなど明らかに負荷がかかる作業をする人向け
- Core i5: 動画視聴、オンラインゲームなどある程度の処理能力が欲しいデスクワークなどをする人向け
- Core i3: ブラウザで閲覧したり、wordで文章を作ったり、メールを送付したりするような通常作業をする人向け


### 世代、アーキテクチャ、ソケット、販売開始日

世代ごとに、対応しているCPUソケット・チップセット・OSが違うので、規格を確認して間違えないように。
第8世代は従来のソケットとは別物なのに「LGA 1151」と表記されているようですが、第８世代には特に注意が必要です。

- 第1世代 Nehalem             LGA1366,LGA1156 2008～2011年販売開始
- 第2世代 Sandy Bridge        LGA1155     2011年1月9日販売開始
- 第3世代 Ivy Bridge	      LGA1155     2012年4月29日販売開始
- 第4世代 Haswell             LGA1150     2013年6月2日販売開始
- 新第4世代 Haswell Refresh   LGA1150     2014年5月11日販売開始
- 第5世代 Broadwell           LGA1150     2015年6月18日販売開始
- 第6世代 Skylake             LGA1151     2015年8月7日販売開始
- 第7世代 Kaby Lake           LGA1151     2017年1月6日販売開始
- 第8世代 Kaby Lake Refresh   ???         2017年8月21日販売開始
- 第8世代 Coffee Lake         LGA1151(v2) 2017年11月2日販売開始
- 第8世代 Cannon Lake         ???         2018年10月20日販売開始
- 第9世代 Coffee Lake Refresh ???         2018年10月8日販売開始
- 第9世代 Ice Lake            ???         2019年販売開始予定

MEMO: 
- 第８世代、第９世代あたりはまた時間をおいて整理したほうがよさそう
- 第８世代にはモバイル用にWhiskey Lake、Amber Lakeがあるようで、上記以外にもモバイル版などありそう!?


### 型番について
Core i9については第７世代から登場しています。
- 第1世代 Core i7 950, Core i5 670などの3桁
- 第2世代 Core i7 2600、Core i3 2100など2000番台
- 第3世代 Core i7 3770、Core i3 3220など3000番台
- 第4世代 Core i7 4770、Core i5 4670など4000番台
- 新第4世 Core i7-4790K、 Core i5-4690K、 Core i3-4370などの4000番台
- 第5世代 Core i7 5775C、Core i5 5775Cなど5000番台
- 第6世代 Core i7 6700K、Core i3 6320など6000番台
- 第7世代 Core i7 7700K、Core i3 7300など7000番台
- 第8世代 Core i9 8950HK、Core i7 8700K、Core i3 8100など8000番台
- 第9世代 Core i9 9900K、など9000番台

### コア数/スレッド数について
この辺を参考に
- http://pcinformation.info/cpu/corei9-corei7-corei5-corei3-difference.html


### 型番に付与されるアルファベットについて

デスクトップ用途で
- 付与なし: 通常盤CPU。性能としては、X > K > C > 付与なし となっている。
- X: 最大クロック数の調整が可能(倍率ロックフリー)、性能・価格ともに最上級モデル(Extreme Edition の略)
- K: 最大クロック数の調整が可能(倍率ロックフリー)
- C: 末尾X, Kと同様に倍率ロックフリーを示す
- S: デスクトップ用の低電圧版
- T: デスクトップ用の超低電圧版
- P: 内蔵グラフィック機能付きの CPU から内臓グラフィック機能を取り除いた
- R: CPU単体では販売されていないモデル。GIGABYTEの小型PCに搭載されている

モバイル用途
- B
- G
- H
- HK
- HQ
- MX
- MQ
- M
- U: 超低消費電力CPU
- Y: 極低消費電力CPU。Uよりもダウングレードされたシリーズ
- QM

- 参考
  - https://pssection9.com/archives/intel-cpu-alphabet-suffix-meaning.html


TODO: 要整理

### プロセスルール
- 第1世代: 32nm
- 第2世代: 32nm
- 第3世代: 22nm
- 第4世代: 22nm
- 新第4世: 22nm
- 第5世代: 14nm
- 第6世代: 14nm 
- 第7世代: 14nm 
- 第8世代: 10nm
- 第9世代: 10nm+ 


- 参考
  - 【CPUの基本】図解でよく分かる「プロセスルール」の意味
  - https://chimolog.co/bto-cpu-process/

### 世代別の違いについて
世代別の性能差
- https://chimolog.co/bto-cpu-intel-core-gen/#Core_i7

それぞれの特徴など(TODO)
- 第1世代 
- 第2世代 
- 第3世代 
- 第4世代 
- 新第4世
  - 第４世代と比較して、動作周波数が+100MHzと少しだけ上昇した程度で、それ以外は全て変わらない。
- 第5世代 
  - プロセスルールが22nmから14nmに変更になった世代
- 第6世代 
- 第7世代 
- 第8世代 
  - プロセスルールが14nmから10nmに変更になった世代
  - Coffee Lake
    - https://ja.wikipedia.org/wiki/Coffee_Lake%E3%83%9E%E3%82%A4%E3%82%AF%E3%83%AD%E3%82%A2%E3%83%BC%E3%82%AD%E3%83%86%E3%82%AF%E3%83%81%E3%83%A3
- 第9世代 



2018年版性能差比較サイト
- http://arbitrage.jpn.org/it/cpu-ranking/


