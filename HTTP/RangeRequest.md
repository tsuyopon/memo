# 概要
大容量のファイル(pdf, 動画)などでは部分的なリクエストを発行することができます。


# 詳細
### サンプルリクエスト
例えば、ヤフーがCSRとして提供しているPDFにRangeRequestでアクセスをしてみましょう。次の点を確認して見てください。
- リクエストヘッダ
  - Range
- レスポンスヘッダ
  - ステータスコードが206
  - Accept-Ranges
  - Content-Length
  - Content-Range
```
$ curl -v -k -r 0-100 "https://s.yimg.jp/i/docs/csr/2017/images/pdf/csr_report_full_2015.pdf"
* About to connect() to s.yimg.jp port 443 (#0)
*   Trying 182.22.25.124...
* Connected to s.yimg.jp (182.22.25.124) port 443 (#0)
* Initializing NSS with certpath: sql:/etc/pki/nssdb
* skipping SSL peer certificate verification
* SSL connection using TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256
* Server certificate:
* 	subject: CN=*.yahoo.co.jp,OU=EDGE_201710,O=Yahoo Japan Corporation,L=Chiyoda-ku,ST=Tokyo,C=JP
* 	start date: 10月 16 11:04:19 2017 GMT
* 	expire date: 11月 15 14:59:00 2018 GMT
* 	common name: *.yahoo.co.jp
* 	issuer: CN=Cybertrust Japan Public CA G3,O="Cybertrust Japan Co., Ltd.",C=JP
> GET /i/docs/csr/2017/images/pdf/csr_report_full_2015.pdf HTTP/1.1
> Range: bytes=0-100
> User-Agent: curl/7.29.0
> Host: s.yimg.jp
> Accept: */*
> 
< HTTP/1.1 206 Partial Content
< Date: Thu, 28 Dec 2017 19:02:49 GMT
< Cache-Control: public
< P3P: policyref="http://privacy.yahoo.co.jp/w3c/p3p_jp.xml", CP="CAO DSP COR CUR ADM DEV TAI PSA PSD IVAi IVDi CONi TELo OTPi OUR DELi SAMi OTRi UNRi PUBi IND PHY ONL UNI PUR FIN COM NAV INT DEM CNT STA POL HEA PRE GOV"
< Last-Modified: Thu, 25 May 2017 05:37:49 GMT
< Accept-Ranges: bytes
< Content-Length: 101
< Cache-Control: max-age=600
< Expires: Thu, 28 Dec 2017 19:12:49 GMT
< Content-Disposition: Attachment
< Content-Range: bytes 0-100/3343399
< Content-Type: application/octet-stream
< Age: 0
< Via: http/1.1 edge1521.img.bbt.yahoo.co.jp (ApacheTrafficServer [cMsSf ]), http/1.1 edge1516.img.bbt.yahoo.co.jp (ApacheTrafficServer [cMsSf ])
< Server: ATS
< Connection: keep-alive
< 
```

続いて、1000byte以降を指定してみます。次のように指定します。レスポンスコードは別に変わりません。
```
$ curl -v -k -r 1000- "https://s.yimg.jp/i/docs/csr/2017/images/pdf/csr_report_full_2015.pdf" > /dev/null
(snip)
> GET /i/docs/csr/2017/images/pdf/csr_report_full_2015.pdf HTTP/1.1
> Range: bytes=1000-
> User-Agent: curl/7.29.0
> Host: s.yimg.jp
> Accept: */*
> 
< HTTP/1.1 206 Partial Content
< Date: Thu, 28 Dec 2017 19:08:39 GMT
< P3P: policyref="http://privacy.yahoo.co.jp/w3c/p3p_jp.xml", CP="CAO DSP COR CUR ADM DEV TAI PSA PSD IVAi IVDi CONi TELo OTPi OUR DELi SAMi OTRi UNRi PUBi IND PHY ONL UNI PUR FIN COM NAV INT DEM CNT STA POL HEA PRE GOV"
< Last-Modified: Thu, 25 May 2017 05:37:49 GMT
< Accept-Ranges: bytes
< Content-Length: 3342399
< Expires: Thu, 28 Dec 2017 19:18:39 GMT
< Content-Disposition: Attachment
< Content-Type: application/octet-stream
< Cache-Control: public
< Cache-Control: max-age=600
< Age: 0
< Content-Range: bytes 1000-3343398/3343399
< Via: http/1.1 edge1221.img.bbt.yahoo.co.jp (ApacheTrafficServer [cSsNfU]), http/1.1 edge1216.img.bbt.yahoo.co.jp (ApacheTrafficServer [cMsSf ])
< Server: ATS
< Connection: keep-alive
```

### If-Rangeヘッダについて
上記のcurlコマンドの実行結果で登場してこなかったRangeで関連するヘッダとしてIf-Rangeというヘッダが存在します。
これは、Rangeヘッダと一緒に指定され、

```
Range: bytes=0-1023
If-Range: "1dba6-131b-3fd31e4a"
```

上記は次のような意味となります。指定されたETagであれば指定されたRangeをください。 ETagが変わっていたらすべてのコンテンツ情報をください。


### 先頭1byteだけ受け取る
次のようなリクエストを投げます
```
Range: bytes=0-1
```

次のようなリクエストを投げれば良い
```
$ curl -v -k -r 0-1 "https://example.com/
```

iphoneなどでは動画再生時にまず「Range: bytes0-1」を送付してRangeリクエストに対応しているかどうかをチェックして206が返ってこないと再生を諦めるといった仕様のようだ。

### Rangeリクエストによる複数指定について
Rangeリクエストは次のような指定がRFC的にも可能なようです。
```
Range: bytes=0-,5-0,5-1,5-2,5-3,5-4,5-5,5-6,5-7,5-8,5-9,
```

RFC的には次のようにも記載されているので無視される可能性もあるとのこと...
```
A server MAY ignore the Range header.
```

上記は、Apache Killerという脆弱性(CVE-2011-3192)を引き起こす可能性があるので注意が必要です。
- https://blog.tokumaru.org/2011/08/apache-killerapache-killer.html


# 参考URL
- RFC7233: Hypertext Transfer Protocol (HTTP/1.1): Range Requests
  - https://tools.ietf.org/html/rfc7233
