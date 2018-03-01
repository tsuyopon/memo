# 概要
TLS1.2ではさらなるCipherSuitesやTLS拡張をサポートしてきたのでClientHelloのサイズがだんだん大きくなってきました。
そして、サイズ成長はいくつかの実装上のバグを引き起こすようになってきました。露見したのはF5社製のBIG IPロードバランサで255バイト以上512バイト未満のハンドシェイクメッセージを処理できないことがわかりました。BIG IPは特に大規模なWebサイトで利用されてたのでこの問題はTLS1.2普及の足枷になりました。

これらの実装上のバグでClientHelloのサイズをさらに大きくした時に改善が見られるようになりました。
この拡張では、ClientHelloのサイズを伸張して上記のバグを回避するためのパディングを行うための仕組みを提供しているようです。

# 利用例
- TLSCiphertext.lengthの長さが256から511バイトのClientHelloを受信した場合にハングアップしてしまうことが知られています。このような場合には少なくとも512バイトのデータを送る必要があります。

# SeeAlso
- RFC7685: A Transport Layer Security (TLS) ClientHello Padding Extension
  - https://tools.ietf.org/html/rfc7685
- HTTP/2.0のALPN利用に伴うSSL負荷分散装置の不具合にご注意下さい
  - http://d.hatena.ne.jp/jovi0608/20131106/1383724662
- HTTP/2.0のALPN利用に伴うSSL負荷分散装置の不具合、その後の顛末
  - http://d.hatena.ne.jp/jovi0608/20131112/1384241722
