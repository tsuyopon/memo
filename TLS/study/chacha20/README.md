# 概要
ChaCha20-Poly1305は新しい暗号方式です。
- Chacha20はストリーム暗号方式(共通鍵暗号)で、Poly1305はメッセージ認証(MAC)の機能です。
- AEAD付きなCipher SuiteなのでAEADの規定がないTLS1.0/TLS1.1では利用することができません。

ChachaはSHA-3選定の最終候補であったBLAKEの基礎となっている。
ChaCha20-Poly1305はRC4に変わる新しいストリーム暗号として注目されている。

- 特徴
  - 暗号化・復号が１つの関数で行うことが可能である。
  - サイドチャネル攻撃に強い

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
- ChaCha20-Poly1305 Cipher Suites for Transport Layer Security (TLS)
  - https://tools.ietf.org/html/rfc7905
- ChaCha20 and Poly1305 for IETF Protocols
  - https://tools.ietf.org/html/rfc7539
- ChaCha, a variant of Salsa20
  - http://cr.yp.to/chacha/chacha-20080128.pdf
