# 概要
chacha20について

# 詳細

### ソースコード詳細について
- basic1.c, basic2.c, basic3.c
  - RFCに記述された途中確認用プログラム
- chacha20.c
  - chacha20で20ラウンド終了後の暗号化プログラム。RFC記載のサンプルinput, outputと同じになっています。
- chacha20decrypt.c
  - chacha20で20ラウンド終了後の複合プログラム(chacha20.cの出力を複合しているものです)
  - ソースコードはほとんどchacha20.cと同じで、出力のための修正を入れています。

# 参考URL
- 新しいTLSの暗号方式ChaCha20-Poly1305
  - http://d.hatena.ne.jp/jovi0608/20160404/1459748671
- GoogleがTLSでの採用を提唱している共通鍵暗号方式「ChaCha」についてまとめた
  - http://sonickun.hatenablog.com/entry/2016/04/03/183220
- 実装に関する参考
  - http://d.hatena.ne.jp/tociyuki/20160326/1458998292

# 仕様書
- ChaCha20 and Poly1305 for IETF Protocols
  - https://tools.ietf.org/html/rfc7539
- ChaCha, a variant of Salsa20
  - http://cr.yp.to/chacha/chacha-20080128.pdf
