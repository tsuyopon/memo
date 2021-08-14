# 概要
HTTP/2はTLS通信が実質必須となっていますので、解読スキルも必要です。

# 詳細

### 鍵情報を指定してtsharkでHTTP/2通信を解析する
keylog_fileにサーバやブラウザ等から出力されるtls_key.logを指定します。
debug_fileにはtsharkが出力するファイルを指定します。
```
$ tshark -o "http2.heuristic_http2: TRUE" \
       -o "ssl.desegment_ssl_records: TRUE" \
       -o "ssl.desegment_ssl_application_data: TRUE" \
       -o "ssl.keylog_file:/path/to/tls_key.log" \
       -o "ssl.debug_file:/Users/moto/Desktop/debug.log" \
       -Y http2
```

- 参考
  - https://gist.github.com/summerwind/a482dd1f8e9887d26199
