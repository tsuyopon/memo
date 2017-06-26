# 概要
RC4とはRSA Securityの Ronald Rivestによって作られたアルゴリズムであり、SSL, WEPやWPAなどに用いられているストリーム暗号である。  
RC4は営業秘密であったが何者かが匿名でCypherpunksのメーリングリストに解説を流してしまった。

# 詳細
- test vectors for RC4
  - https://tools.ietf.org/html/rfc6229


### ソースコード
- rc4sample1
  - keyと平文を標準入力から受け付けてRC4で暗号化・複合する
- rc4sample2
  - 別のサンプルプログラム


# 参考URL
- https://sites.math.washington.edu/~nichifor/310_2008_Spring/Pres_RC4%20Encryption.pdf
- wikipedia
  - https://ja.wikipedia.org/wiki/RC4
