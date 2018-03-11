# 概要 
ab(Apache Bench)はApacheに付属で添付されているベンチマーク測定用ツールです。


# 詳細
以下に特徴を記します。 コマンドライン上から発行リクエスト数、同時接続数を指定して測定できます

### abオプションについて
```
オプション 意味 
-n 数値 テストで発行するリクエストの回数を数値で指定 
-c 数値 テストで同時に発行するリクエストの数を数値で指定 
-t 数値 サーバからのレスポンスの待ち時間（秒）を数値で指定 
-p ファイル名 サーバへ送信するファイルがある場合に指定 
-T コンテンツタイプ サーバへ送信するコンテンツヘッダを指定 
-v 数値 指定した数値に応じた動作情報を表示 
-w 結果をHTMLで出力（出力をファイルに保存すればWebブラウザで表組みされたものが見られる） 
-x 属性 HTML出力のtableタグに属性を追加（BORDERなど） 
-y 属性 HTML出力のtrタグに属性を追加 
-z 属性 HTML出力のtdまたはthタグに属性を追加 
-C 'Cookie名称=値' Cookie値を渡してテストする 
-A ユーザー名:パスワード ベーシック認証が必要なコンテンツにテストする 
-P ユーザー名:パスワード 認証の必要なプロキシを通じてテストする 
-X プロキシサーバ名:ポート番号 プロキシ経由でリクエストする場合に指定 
-V abのバージョン番号を表示 
-k HTTP/1.1のKeepAliveを有効にしてテストする 
-h abのヘルプを表示 
```

### 測定コマンドのサンプル
```
(例)#ab -n 10000 -c 100 http://www.test.co.jp/test.html
```
上記はテストで発行するリクエストの回数を10000回として、テストで同時に発行する リクエストの数を100に指定し、http://www.test.co.jp/test.htmlに対してベンチマークを測定しています。

```
測定結果
Server Software:        Apache/1.3.33     <=apacheのバージョン
Server Hostname:        localhost         <=ベンチマークを行ったサーバ
Server Port:            80                <=ベンチマークを行ったポート

Document Path:          /                 <=ベンチマークを行ったURI
Document Length:        122 bytes

Concurrency Level:      100               <=同時接続数
Time taken for tests:   43.92620 seconds  <=ベンチマークにかかった時間
Complete requests:      10000             <=ベンチマークで測定を行ったリクエストの数
Failed requests:        0
Write errors:           0
Total transferred:      4267136 bytes
HTML transferred:       1227808 bytes             
Requests per second:    232.06 [#/sec] (mean)     <=1秒間に処理されたリクエスト数
Time per request:       430.926 [ms] (mean)
Time per request:       4.309 [ms] (mean, across all concurrent requests)
Transfer rate:          96.70 [Kbytes/sec] received

Connection Times (ms)
                min   mean[+/-sd] median   max
    Connect:        0  127  88.9    155     418
    Processing:    98  296 203.5    234    1056
    Waiting:       79  270 211.5    192    1046
    Total:        140  423 163.1    373    1056

Percentage of the requests served within a certain time (ms)
50%    373
66%    412
75%    434
80%    451
90%    549
95%    989
98%   1000
99%   1007
100%   1056 (longest request)
```
