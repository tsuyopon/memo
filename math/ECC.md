# Elliptic Curve Cryptography(楕円曲線暗号)
楕円暗号曲線の定義についてはこちらです。
- https://ja.wikipedia.org/wiki/%E6%A5%95%E5%86%86%E6%9B%B2%E7%B7%9A%E6%9A%97%E5%8F%B7
- https://ja.wikipedia.org/wiki/%E6%A5%95%E5%86%86%E6%9B%B2%E7%B7%9A

あらかじめ理解するに群論の定理を理解しておく必要がある。

# 詳細

### 理解の流れ
こちらの「楕円曲線暗号入門(2013年度)_rev60r.zip」が非常に良い
- https://researchmap.jp/mulzrkzae-42427/

上記の資料で次の手順で確認します。
- 1.1の有限体の概念を理解する
- 演習1.1, 演習1.2, 演習1.3, 演習1.4を行いa+b, a-b, a+b, a/bの表を完成される。(これらの加法定理が重要なのでその定義を確認すること)
- 定義1.15を確認することによって、楕円曲線定義方程式を確認する。
- 演習1.17を実施する
- 演習1.21を実施する
- 演習1.21により表1.7の生成方法が求まるようになる。これが楕円曲線y^2 = x^3 + 3x + 4 mod 7で表される有利点となる。
- 表1.7を用いることによって、楕円曲線関数を使ってアリスとボブが安全に暗号交換できることを確認する。

アリスとボブの共有鍵の生成手順としては次の通り。
- 表1.7はmod 7で表現された楕円曲線なので1-6で秘密鍵rを作成する。(この値は相手にばれないように秘密にしなければならない)
- 相手から該当のP(ポイント)をもらう
- 自分のrと掛け算をしてどこの点にいくのかを決定する。このポイントがアリスとボブの共有鍵となる。


### 簡単な共有鍵生成の流れ

- 今回はP1の値から開始することをアリスとボブで合意する。表1.7は次の情報である。
```
楕円曲線: y^2 = x^3 + 3x + 4   (つまり、 a=3, b=4)
素数: mod 7
双方で開始点: P1
```

下記の計算は表1.7を利用すると良い
- アリス
  - 秘密鍵を1-6から選んで3とした。この値はアリスの秘密鍵である。
  - 3と開始点P1をかける。この値をボブに公開鍵として送付する。
    - 3 * P1 = (P1 + P1) + P1 = P8 + P1 = P2 
  - ボブから公開鍵を受け取る。公開鍵はP9を受け取ることになる(後述)
  - ボブから受け取った公開鍵と自身が持つ秘密鍵の値をかける
    - P9 * 3 = (P9 + P9) + P9 = P2 + P9 = P8
  - アリスとボブの共通鍵はP8となる。
- ボブ
  - 秘密鍵を1-6から選んで4とした。この値はボブの秘密鍵である。
  - 4と開始点P1をかける。この値をアリスに公開鍵として送付する。
    - 4 * P1 = (P1 + P1) + (P1 + P1) = P8 + P8 = P9
  - アリスから公開鍵を受け取る。公開鍵はP2を受け取ることになる。
  - アリスから受け取った公開鍵と自身が持つ秘密鍵の値をかける
    - P2 * 4 = (P2 + P2) + (P2 + P2) = P1 + P1 = P8
   - アリスとボブの共通鍵はP8となる。

上記では双方でP8の共通鍵が生成できていることが確認できる。
なお、これだけで疑わしいと思う方は開始点を変更して上記を計算してもアリスとボブで共通鍵が生成されることを確認すると良い。
公開鍵暗号方式が成立するのは公開鍵情報から秘密鍵情報を見つけるのが非常に難しいといった性質を利用している。


さて、ここでTLSに関する話をする。
```
楕円曲線: y^2 = x^3 + 3x + 4   (つまり、 a=3, b=4)
素数: mod 7
開始点: P1   (ここではP1といったポイント表記だがG記号が使われることも多い。なお、GにはX座標、Y座標があるのでGx, Gyなどと表されることがあります。
```

上記の楕円曲線、素数、開始点に関する3つの情報がsecp256r1などで定義されているパラメータ群である。
- https://tools.ietf.org/html/rfc4492#appendix-A

secp256r1などのパラメータに関する定義はおそらくこの辺の資料で表されている。
pが素数、楕円曲線パラメータa, b、開始点Gがcompressとuncompressでそれぞれ定義される。なお、S、n、hなどのパラメータは不明(TODO)
- http://www.secg.org/SEC2-Ver-1.0.pdf

公開鍵は（何かしらの証明を付けた）静的なものであっても、一時的なもの（ephemeral、この場合特にECDHEと略記される）であるかでECDHかECDHEか異なる。
静的な場合にはForward Secrecyの特性がなくなることになる。


### Curve25519、Curve448などの命名理由について
上記はqmailで有名なDJBが策定したものである。その理由としては素数を見れば明らかである。

- Curve25519
  - 2^255 - 19
- Curve448
  - 2^448 - 2^224 - 1

上記は以下で定義されているので実装する際には確認すると良い。
- https://tools.ietf.org/html/rfc7748


# 参考
- 技術勉強会（楕円曲線暗号）資料
  - https://www.slideshare.net/tyk97/ss-35444178
- An Introduction to the Theory of Elliptic Curves
  - http://www.math.brown.edu/~jhs/Presentations/WyomingEllipticCurve.pdf
