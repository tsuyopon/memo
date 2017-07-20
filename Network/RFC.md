# 概要
RFCとはRequest For Commentsの略称であり、「インターネット」といったキーワードで関連づけられて広く公開しておくべきだと思われる情報を公開するための管理された文書シリーズ」となる。

# 詳細

# RFC公開までの流れ
RFCを公開するには次の流れとなる。
- 1. 最初に提出が必要なのがインターネットドラフト(I-Ds: Internet Drafts)であり、これは誰でも提出可能である。
- 2. 提出するだけでインターネットを通して広く公開されます。一定の期間(6月)が経過すると削除されることになります。
  - RFCはインターネットの様々な技術は広く相互運用性/相互接続性を持たなければならないので主にIETFでコンセンサスを取る必要がある。
- 3. IETFなどの議論はRFCとして公開されることで広く公知されることになる。
- 4. IETFでは必要に応じて議論や検討を行い、その結果をI-Dにフィードバックしていくことで、多くの人たちの意見を反映した成熟したものにする
- 5.十分な議論が行われIESGの承認を得ることができればRFCとして公開されることになる

### RFC標準化過程(最新版)

RFC6410によってRFCは従来の３ステージから２ステージへと変更になりました。
- https://tools.ietf.org/html/rfc6410

Proposed Standard (PS) -> Internet Standard (STD)の2ステージへと変更となりました

しかし、ここでは3ステージについて説明します。

なお、RFC6410が出る前まではつぎのような過程(Historyを除くと3ステージ)
Proposed Standard(PS) -> Draft Standard(DS) -> Internet Standard(STD) -> 仕様として古くなった -> Historical

- PSへの条件
  - 安定した十分に議論され尽くした仕様の存在など
- PSからDSへの条件
  - 最低6ヶ月間のPSの経過など
  - その間の議論の反映、IESGからの要請の実現など
  - 相互接続性のある独立した２つ以上の実装の存在
- DSからSTDへの条件
  - 最低４ヶ月間のDS期間の経過もしくは最低1回のIETFミーティングの開催
  - 多数の実績、十分な実績、標準化のコンセンサス


段階としては次の３つがある。
- 標準化への提唱(PROPOSED STANDARD)
  - 標準化される最初の段階で、幅広く公開され評価されることが求められている。
- 標準化への草稿(DRAFT STANDARD)
  - 仕様として十分に成熟していることを表します。２つ以上の相互運用性のある独立した実装の存在や運用経験がこの段階になるための条件である。
  - 多くの場合、各ベンダーはこの段階の仕様を一般に市場に出回る製品に実装する。
  - https://tools.ietf.org/html/rfc2460
- 標準(STANDARD)
  - 標準プロトコルを表します。この段階になるためには、十分な運用経験/実績が必要となります

その他には次のような区分も存在します。
- 情報(INFORMATIONAL)
  - ほとんどあらゆるものがふくまれる
  - https://tools.ietf.org/html/rfc1785
- 実験(EXPERIMENTAL)
  - インターネットに関して有用と考えられる研究成果や実験結果を広く公開するためのもの。実際には標準化過程へ昇格していないだけの文書も含まれる。
  - https://tools.ietf.org/html/rfc6962
- 現状(BEST CURRENT PRACTICE)
  - 「情報」には留まらないが実際にネットワークで使われるデータには影響しない、公的なルールと見なされている実務上の文書
  - https://tools.ietf.org/html/rfc6410
- 歴史(HISTORIC)
  - 標準化過程で破棄された文書や標準化以前に公開されていた廃れた RFC に適用される。
  - https://tools.ietf.org/html/rfc3525

# UPDATE Byは何?
Updated Byでリンクがある場合にはそのRFCの内容を更新することを意味する
- https://tools.ietf.org/html/rfc2460

# Errata Existsは何
たとえば、次のRFCの右上に「Errata Exists」が存在する場合には 
- https://tools.ietf.org/html/rfc2460

画面上に「Errata」というリンクがあります。
Errata Exists自体は正誤表が存在しますといった意味なのでこの表がリンク先に存在します。

# Diff1とかDiff2といったリンクは何？
差分と思われる(**TODO**)

# Obsoletesとは何?
たとえば、次のRFCには
- https://tools.ietf.org/html/rfc2460

次のリンクがObsoletesに指定されている
- https://tools.ietf.org/html/rfc1883

RFCには、一連のRFC番号が付けられているが、新しい版が発行されると、古い番号のRFCはObsolete（廃止）またはUpdate（更新）される。Obsoleteされている場合は、新しい方のRFCだけを参照しなければならない。Updateの場合は両方のRFCを参照する必要がある。

# 参考URL
- JPNIC
  - https://www.nic.ad.jp/ja/newsletter/No24/090.html
