# 概要
Hybrid key exchange in TLS 1.3
以下のドキュメントを参考にしています。
- https://datatracker.ietf.org/doc/html/draft-stebila-tls-hybrid-design-03

# 課題

### 解決したい課題
量子コンピュータが普及した際に、安全でなくなる鍵交換方式がある。
今後このような脅威に対しての対応方針の検討が必要となる。

### 解決方法
ハイブリッド鍵交換を使うことで、複数の鍵交換アルゴリズムを同時に使用し、その結果を組み合わせることで、鍵交換を行うようにする。
それによって、構成するアルゴリズムのうち1つ以外が壊れても、セキュリティが確保することができます。


# 詳細


## ハイブリッド鍵交換のための構築


# 参考URL
- https://datatracker.ietf.org/doc/draft-stebila-tls-hybrid-design/
