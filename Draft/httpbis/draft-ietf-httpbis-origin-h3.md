# The ORIGIN Extension in HTTP/3
下記資料を参考にしています
- https://datatracker.ietf.org/doc/html/draft-ietf-httpbis-origin-h3-03

# 解決したい課題
HTTP/2ではOriginフレームが送ることができ、これはサーバからどのドメインセットがそのTLSコネクションで対応しているのかという情報を返答します。

HTTP/2では下記のようにORIGINフレームが定義されていますが、
- https://www.iana.org/assignments/http2-parameters/http2-parameters.xhtml#frame-type

HTTP/3では現時点でまだORIGINフレームが割り当てられていないので定義しましょうとなっている。
- https://www.iana.org/assignments/http3-parameters/http3-parameters.xhtml#http3-parameters-frame-types

# 解決方法
IANAレジストリのORIGINフレームにHTTP/2と同じく0xcを割り当てる。

RFCにはORIGINフレームのデータ構造情報も記載されている
```
HTTP/3 Origin-Entry {
  Origin-Len (16),
  ASCII-Origin (..),
}

HTTP/3 ORIGIN Frame {
  Type (i) = 0x0c,
  Length (i),
  Origin-Entry (..) ...,
}
```
