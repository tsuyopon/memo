# 概要
traffic_viaやViaヘッダに関連する

# 詳細

### traffic_viaコマンドによる状態解析をしたい
```
$ traffic_via "[uScMsEf p eC:t cCMi p sF]"
Via header is uScMsEf p eC:t cCMi p sF, Length is 24
Via Header Details:
Request headers received from client                   :simple request (not conditional)
Result of Traffic Server cache lookup for URL          :miss (a cache "MISS")
Response information received from origin server       :error in response
Result of document write-to-cache:                     :no cache write performed
Proxy operation result                                 :unknown
Error codes (if any)                                   :connection to server failed
Tunnel info                                            :no tunneling
Cache Type                                             :cache
Cache Lookup Result                                    :cache miss (url not in cache)
Parent proxy connection status                         :no parent proxy or unknown
Origin server connection status                        :connection open failed
```

traffic_viaについては以下に公式ドキュメントが有ります
- https://docs.trafficserver.apache.org/ja/latest/appendices/command-line/traffic_via.en.html

### Viaに表示される記号の説明ドキュメント
- https://docs.trafficserver.apache.org/en/latest/appendices/faq.en.html#how-do-i-interpret-the-via-header-code

### trafficserverサイトにViaヘッダを解析する簡単なツールがあります。
- http://trafficserver.apache.org/tools/via

### Viaヘッダのシンボルが定義されているソースコード箇所を確認したい
以下は7.1.xです。
- https://github.com/apache/trafficserver/blob/7.1.x/proxy/http/HttpTransact.h#L145-L228
