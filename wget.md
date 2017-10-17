# 概要
wgetコマンドについてまとめます。
curlコマンドと同様に覚えておくと、curlでうまくいかないときにwgetでも試してみるといったことが可能となりトラブルシュートもはかどります。

wgetの利点としては次のようなものがある
- 左手だけでwgetのタイピングとペーストが可能
- 再帰的なダウンロード

curlとwgetとの比較は以下の資料が参考になりそうです。
- http://postd.cc/curl-vs-wget/

# 詳細
### レスポンスを標準出力のみに出力する(-O -)
```
$ wget https://www.yahoo.co.jp/ -O -
--2017-10-18 08:42:46--  https://www.yahoo.co.jp/
Resolving www.yahoo.co.jp (www.yahoo.co.jp)... 182.22.31.124
Connecting to www.yahoo.co.jp (www.yahoo.co.jp)|182.22.31.124|:443... connected.
HTTP request sent, awaiting response... 200 OK
Length: unspecified [text/html]
Saving to: ‘STDOUT’

-                                           [<=>                                                                             ]       0  --.-KB/s             <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="content-type" content="text/html; charset=utf-8">
<meta http-equiv="content-style-type" content="text/css">
<meta http-equiv="content-script-type" content="text/javascript">
<meta name="description" content="日本最大級のポータルサイト。検索、オークション、ニュース、メール、コミュニティ、ショッピング、など80以上のサービスを展開。あなたの生活をより豊かにする「ライフ・エンジン」を目指していきます。">

(以下省略)
```

### サーバのレスポンス内容とレスポンスヘッダを両方出力する
```
$ wget https://www.yahoo.co.jp/ -S -O -
--2017-10-18 08:45:37--  https://www.yahoo.co.jp/
Resolving www.yahoo.co.jp (www.yahoo.co.jp)... 183.79.250.251
Connecting to www.yahoo.co.jp (www.yahoo.co.jp)|183.79.250.251|:443... connected.
HTTP request sent, awaiting response... 
  HTTP/1.1 200 OK
  Date: Tue, 17 Oct 2017 23:45:37 GMT
  P3P: policyref="http://privacy.yahoo.co.jp/w3c/p3p_jp.xml", CP="CAO DSP COR CUR ADM DEV TAI PSA PSD IVAi IVDi CONi TELo OTPi OUR DELi SAMi OTRi UNRi PUBi IND PHY ONL UNI PUR FIN COM NAV INT DEM CNT STA POL HEA PRE GOV"
  X-Content-Type-Options: nosniff
  X-XSS-Protection: 1; mode=block
  X-Frame-Options: SAMEORIGIN
  Vary: Accept-Encoding
  Expires: -1
  Pragma: no-cache
  Cache-Control: private, no-cache, no-store, must-revalidate
  X-XRDS-Location: https://open.login.yahooapis.jp/openid20/www.yahoo.co.jp/xrds
  Content-Type: text/html; charset=UTF-8
  Age: 0
  Transfer-Encoding: chunked
  Connection: keep-alive
  Via: http/1.1 edge2552.img.umd.yahoo.co.jp (ApacheTrafficServer [c sSf ])
  Server: ATS
Length: unspecified [text/html]
Saving to: ‘STDOUT’

-                                           [<=>                                                                             ]       0  --.-KB/s             <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
(以下省略)
```

### レスポンスヘッダを確認する(レスポンス内容は出力しない)
例えばヤフートップにhttp://www.yahoo.co.jpにアクセスすると最初は80ポートで接続してLocationで443ポートに飛ばされることが確認できます。
なお、spiderオプションはダウンロードさせないオプションです。
```
$ wget http://www.yahoo.co.jp --server-response --spider
Spider mode enabled. Check if remote file exists.
--2017-10-18 08:36:30--  http://www.yahoo.co.jp/
Resolving www.yahoo.co.jp (www.yahoo.co.jp)... 183.79.250.123
Connecting to www.yahoo.co.jp (www.yahoo.co.jp)|183.79.250.123|:80... connected.
HTTP request sent, awaiting response... 
  HTTP/1.1 301 Redirect
  Date: Tue, 17 Oct 2017 23:36:30 GMT
  Connection: keep-alive
  Via: http/1.1 edge2404.img.djm.yahoo.co.jp (ApacheTrafficServer [c s f ])
  Server: ATS
  Cache-Control: no-store
  Location: https://www.yahoo.co.jp:443/
  Content-Type: text/html
  Content-Language: en
  Content-Length: 6794
Location: https://www.yahoo.co.jp:443/ [following]
Spider mode enabled. Check if remote file exists.
--2017-10-18 08:36:30--  https://www.yahoo.co.jp/
Connecting to www.yahoo.co.jp (www.yahoo.co.jp)|183.79.250.123|:443... connected.
HTTP request sent, awaiting response... 
  HTTP/1.1 200 OK
  Date: Tue, 17 Oct 2017 23:36:31 GMT
  P3P: policyref="http://privacy.yahoo.co.jp/w3c/p3p_jp.xml", CP="CAO DSP COR CUR ADM DEV TAI PSA PSD IVAi IVDi CONi TELo OTPi OUR DELi SAMi OTRi UNRi PUBi IND PHY ONL UNI PUR FIN COM NAV INT DEM CNT STA POL HEA PRE GOV"
  X-Content-Type-Options: nosniff
  X-XSS-Protection: 1; mode=block
  X-Frame-Options: SAMEORIGIN
  Expires: -1
  Pragma: no-cache
  Cache-Control: private, no-cache, no-store, must-revalidate
  X-XRDS-Location: https://open.login.yahooapis.jp/openid20/www.yahoo.co.jp/xrds
  Content-Type: text/html; charset=UTF-8
  Age: 0
  Connection: keep-alive
  Via: http/1.1 edge2431.img.djm.yahoo.co.jp (ApacheTrafficServer [c sSf ])
  Server: ATS
Length: unspecified [text/html]
Remote file exists and could contain further links,
but recursion is disabled -- not retrieving.
```

### 自己証明書を無視する
```
$ wget https://www.yahoo.co.jp/ --no-check-certificate -O -
```


### 失敗しても何度でもやりなおす
```
$ wget -c https://www.yahoo.co.jp
```

### ダウンロードの速度制限を行う
```
$ wget --limit-rate=2m https://www.yahoo.co.jp/
```

### ダウンロードをバックグラウンドで実行する
容量が大きいファイルのダウンロードなどは便利です。
```
$ wget -b http://example.com/test.iso
```

### User-Agentを偽装する
```
$ wget --user-agent="testua" http://example.com
```

### URLの記述されたファイルをダウンロードする
```
$ cat wget-list.txt
http://example.com/test
http://example.com/test2
http://example.com/test3
$ wget -i wget-list.txt
```




