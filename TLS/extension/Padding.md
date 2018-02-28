# 概要
TLS1.2ではさらなるCipherSuitesやTLS拡張をサポートしてきたのでClientHelloのサイズがだんだん大きくなってきました。
そして、サイズ成長はいくつかの実装上のバグを引き起こすようになってきました。いくつかの実装ではこれらの実装上のバグでClientHelloのサイズをさらに大きくした時に改善が見られるようになりました。
この拡張によってClientHelloのサイズを伸張して上記のバグを回避するためのパディングを行うための仕組みを提供しているようです。

# 利用例
- TLSCiphertext.lengthの長さが256から511バイトのClientHelloを受信した場合にハングアップしてしまうことが知られています。このような場合には少なくとも512バイトのデータを送る必要があります。

# SeeAlso
- RFC7685: A Transport Layer Security (TLS) ClientHello Padding Extension
  - https://tools.ietf.org/html/rfc7685
