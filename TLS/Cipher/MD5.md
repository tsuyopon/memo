# 概要
MD5は任意長のメッセージから128bitのフィンガープリントを出力する仕組みです。
MD5はMD4のクリティカルレビューを発端として設計されました。MD5は複数人でのレビューが行われ、最適化処理も行われています。

RFC1321についてはMD5の定義について規定している。
RFC6151についてはRFC1321の「Security Considerations」部分を置き換える意味のRFCとなっている。

# 詳細

## RFC1321
### MD5について
MD5ので入力される文字長は8bitの倍数である必要はない。
次の5つのステップを持って計算処理が行われる。詳細はRFC1321を読むこと。
- Step 1. Append Padding Bits
- Step 2. Append Length
- Step 3. Initialize MD Buffer
- Step 4. Process Message in 16-Word Blocks
- Step 5. Output


### MD4との違い
- 第４ラウンドが追加された
- それぞれのステップにおいてユニークな追加の定数を持つようになった。
- ラウンド2のg関数が(XY v XZ v YZ) から(XZ v Y not(Z)) へと変化した。
- 各ステップでは前回のステップの結果を加算するようになった。これは「avalanche effect」を促進する。
- ラウンド2やラウンド3でアクセスされる入力ワードの順番が変更となった。
- それぞれのラウンドのシフトされる量が「avalanche effect」を生み出すために最適化された

## RFC6151
- MD5はもはやデジタル署名では安全でないことが明記された。ただし、HMAC-MD5のような場合には緊急性があるわけではない。
- HMAC-MD5の代替としてHMAC-SHA256を記載している。　

# Reference
- RFC1321: The MD5 Message-Digest Algorithm
  - https://tools.ietf.org/html/rfc1321
- RFC6151: Updated Security Considerations for the MD5 Message-Digest and the HMAC-MD5 Algorithms
  - https://tools.ietf.org/html/rfc6151

