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

### Hostヘッダを付与して
参考までにヘッダも付与するようにSオプションも指定してみている。
```
$ wget -S -O - http://www.yahoo.co.jp/ --header 'Host: hoge.yahoo.co.jp'
--2017-10-18 08:58:59--  http://www.yahoo.co.jp/
Resolving www.yahoo.co.jp... 183.79.248.252
Connecting to www.yahoo.co.jp|183.79.248.252|:80... connected.
HTTP request sent, awaiting response... 
  HTTP/1.1 404 Not Found on Accelerator
  Date: Tue, 17 Oct 2017 23:58:59 GMT
  Connection: keep-alive
  Via: http/1.1 edge2112.img.djm.yahoo.co.jp (ApacheTrafficServer [c s f ])
  Server: ATS
  Cache-Control: no-store
  Content-Type: text/html
  Content-Language: en
  X-Frame-Options: SAMEORIGIN
  Content-Length: 6794
2017-10-18 08:58:59 ERROR 404: Not Found on Accelerator.
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

### オプション一覧
```
-o ログファイル指定
-w ウェイト
-N タイムスタンプ保持
-x ドメインとかパスを保持
-r 再帰
-l inf 再帰の深さを無限にする
-P /path/to/ ファイルのダウンロードパス
--no-proxy プロキシを通さずにアクセス
--tries=4 リトライ回数の上限を指定 (0 は無制限).
--retry-connrefused 接続を拒否されてもリトライする
--no-clobber 存在しているファイルをダウンロードで上書きしない
--continue 部分的にダウンロードしたファイルの続きから始める
--http-user="userName" ベーシック認証のユーザ名
--http-passwd="password" ベーシック認証のパスワード
--restrict-file-names=modes ファイル名の制御：modeで規定
--restrict-file-names=nocontrol マルチバイト文字のファイル名をダウンロードする場合の文字化け防止
--content-disposition content-dispositionに記載されているファイル名でダウンロードする
--server-response サーバの応答を表示する
--spider 何もダウンロードしない
--timeout=SECONDS 全てのタイムアウトを SECONDS 秒に設定する
--dns-timeout=SECS DNS 問い合わせのタイムアウトを SECS 秒に設定する
--connect-timeout=SECS 接続タイムアウトを SECS 秒に設定する
--read-timeout=SECS 読み込みタイムアウトを SECS 秒に設定する
--wait=SECONDS ダウンロード毎に SECONDS 秒待つ
--waitretry=SECONDS リトライ毎に 1?SECONDS 秒待つ
--random-wait ダウンロード毎に 0?2*WAIT 秒待つ
--quota=NUMBER ダウンロードするバイト数の上限を指定する
--bind-address=ADDRESS ローカルアドレスとして ADDRESS (ホスト名か IP) を使う
--limit-rate=RATE ダウンロード速度を RATE に制限する
--no-dns-cache DNS の問い合わせ結果をキャッシュしない
--restrict-file-names=OS OS が許しているファイル名に制限する
--ignore-case ファイル名/ディレクトリ名の比較で大文字小文字を無視する
--inet4-only IPv4 だけを使う
--inet6-only IPv6 だけを使う
--prefer-family=FAMILY 指定したファミリ(IPv6, IPv4, none)で最初に接続する
--user=USER ftp, http のユーザ名を指定する
--password=PASS ftp, http のパスワードを指定する
--ask-password パスワードを別途入力する
--no-iri IRI サポートを使わない
--local-encoding=ENC 指定した ENC を IRI のローカルエンコーディングにする
--remote-encoding=ENC 指定した ENC をデフォルトのリモートエンコーディングにする
--no-http-keep-alive HTTP の keep-alive (持続的接続) 機能を使わない
--no-cookies クッキーを使わない
--load-cookies=FILE クッキーを FILE から読みこむ
--save-cookies=FILE クッキーを FILE に保存する
--keep-session-cookies セッションだけで用いるクッキーを保持する
--auth-no-challenge サーバからのチャレンジを待たずに、Basic認証の情報を送信します。
--user-agent="Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:52.0) Gecko/20100101 Firefox/52.0" ユーザーエージェントの偽装
--referer="http://example.com/" リファラの偽装
--header="Host: example.com" ヘッダーの付与
--post-data="userid=hoge&password=hogehoge" POST送信
--post-file="/path/to/file" POSTでファイル送信
--secure-protocol=PR セキュアプロトコルを選択する (auto, SSLv2, SSLv3, TLSv1)
--no-check-certificate サーバSSL証明書を検証しない
--certificate=FILE クライアント証明書として FILE を使う
--certificate-type=TYPE クライアント証明書の種類を TYPE (PEM, DER) に設定する
--private-key=FILE 秘密鍵として FILE を使う
--private-key-type=TYPE 秘密鍵の種類を TYPE (PEM, DER) に設定する
--ca-certificate=FILE CA 証明書として FILE を使う
--ca-directory=DIR CA のハッシュリストが保持されているディレクトリを指定する
--random-file=FILE  SSL PRNG の初期化データに使うファイルを指定する
--egd-file=FILE  EGD ソケットとして FILE を使う
--recursive 再帰ダウンロードを行う
--level=NUMBER 再帰時の階層の最大の深さを NUMBER に設定する (0 で無制限)
--delete-after ダウンロード終了後、ダウンロードしたファイルを削除する
--convert-links HTML や CSS 中のリンクをローカルを指すように変更する
--backup-converted リンク変換前のファイルを .orig として保存する
--mirror "-N -r -l 0 --no-remove-listing" の省略形
--page-requisites HTML を表示するのに必要な全ての画像等も取得する
--strict-comments HTML 中のコメントの処理を厳密にする
--accept=LIST ダウンロードする拡張子をコンマ区切りで指定する
--reject=LIST ダウンロードしない拡張子をコンマ区切りで指定する
--domains=LIST ダウンロードするドメインをコンマ区切りで指定する
--exclude-domains=LIST ダウンロードしないドメインをコンマ区切りで指定する
--follow-ftp HTML 文書中の FTP リンクも取得対象にする
--follow-tags=LIST 取得対象にするタグ名をコンマ区切りで指定する
--ignore-tags=LIST 取得対象にしないタグ名をコンマ区切りで指定する
--span-hosts 再帰中に別のホストもダウンロード対象にする
--relative 相対リンクだけ取得対象にする
--include-directories=LIST 取得対象にするディレクトリを指定する
--trust-server-names use the name specified by the redirection url last component.
--exclude-directories=LIST 取得対象にしないディレクトリを指定する
--no-parent 親ディレクトリを取得対象にしない
--ftp-user=USER ftp ユーザとして USER を使う
--ftp-password=PASS ftp パスワードとして PASS を使う
--no-remove-listing  `.listing' ファイルを削除しない
--no-glob FTP ファイル名のグロブを無効にする
--no-passive-ftp "passive" 転送モードを使わない
--retr-symlinks 再帰取得中に、シンボリックリンクでリンクされた先のファイルを取得する
```

