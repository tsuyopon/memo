# 概要
制約された環境下ではHMACタグの大きさもバンド幅が問題になります。
Truncted HMAC拡張は通常付与されるHMACを80bitへと切り詰める、バンド幅を削減することができる拡張機能です。

この切り詰められたHMACを利用する場合、暗号化対象のアプリケーションデータが短く、暗号化データがブロックサイズを超えないケースにおいて平文が漏洩する可能性があります。


# これに基づいた脆弱性も公開されているようです。
- https://sect.iij.ad.jp/d/2011/12/079269.html


# 参考URL
- Transport Layer Security (TLS) Extensions: Extension Definitions
  - https://tools.ietf.org/html/rfc6066
- truncated_hmacに関する脆弱性の論文
  - http://www.isg.rhul.ac.uk/~kp/mee-comp.pdf
