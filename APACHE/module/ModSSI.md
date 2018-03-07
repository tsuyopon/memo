# 概要
httpd.confでSSIを使うと定義する必要があります。(INCLUDEが定義されていればよい)
以下に特徴を記します。
- shtmlというファイル名を持ちます。
- 環境変数やファイル情報などの様々なデータを挿入することが可能になります
- すべてのファイルに同じヘッダやフッタを表示することが容易になります
- ファイルの最終更新時刻やサイズを自動的に表示できるようになります
- カウンタを容易に作れます

尚、SSIには以下のデメリットも存在することを覚えておいてください。
- パフォーマンスが下がる
- セキュリティが弱まる

SSIを利用する倍、Apacheの設定は下記記述がhttpd.confか.htaccessに記載されている必要があります。
```
AddType text/x-server-parsed-html .shtml
Options Includes
```

# 詳細
### 拡張子がhtmlでもSSIを利用したい
SSIは通常shtmlという拡張子になります。
ですが、htmlでもこれを利用したい場合にはconfに以下のAddType設定を追加します。
```
AddType text/x-server-parsed-html .shtml .html
```

### SSIページで利用できる追加変数
一般的にperlで%ENVで出力可能なものの他にも利用可能な追加変数を以下に挙げる。
```
DOCUMENT_NAME           現在のファイル名
DOCUMENT_URI            ファイルへの仮想パス
QUERY_STRING_UNESCAPED  シェルでのメタ文字が全て"\"でエスケープシーケンスされ
                        たデコードされた文字列
DATE_LOCAL              ローカルタイムゾーンでの現在日時 
DATE_GMT                GMTでの現在日時
LAST_MODIFIED           ブラウザがリクエストしたファイルの最終更新日時
```

### 環境変数を出力
```
<!--#echo var="LAST_MODIFIED" -->
```

また、環境変数一覧を表示させるには以下の様にします。
```
<!--#printenv -->
```

### 変数に値を格納する
以下の例ではmsgという変数に値を格納して、それを出力させる例です。
```
<!--#set var="msg" value="Hello!!" -->
<!--#echo var="msg" -->
```

### 最終更新時刻を表示させる
```
<!--#config timefmt="%Y/%m/%d %X" -->     <=　時刻表示形式を指定できる
<!--#echo var="LAST_MODIFIED" -->
```

### ファイルの読み込み処理を行う
```
<!--#include file="header.html" -->
```

### ファイルサイズを表示させる
```
<!--#config sizefmt="abbrev" -->
<a href="xxx.zip">ダウンロード</a>（サイズ：<!--#fsize file="xxx.zip" -->）
```

### コマンドを実行する
実際のUNIXコマンドおよびcgiコマンドを実行させる例になります。
CGIの時にはパラメータ(?以降)は渡すことができないので注意が必要です。
```
<!--#exec cmd="/bin/ls" -->
<!--#exec cgi="./cgi-bin/test.cgi" -->
```

### エラーメッセージを指定する
文書処理中にエラーが発生した場合のメッセージを指定できる。これはエラーログにも記載されます。
```
<!--#config errmsg="〜" -->
```

### 制御構文を利用する
```
<!--#if expr="〜" -->
<!--#elif expr="〜" -->
<!--#else -->
<!--#endif -->
```

# SeeAlso
- とほほのSSI入門
  - http://www.tohoho-web.com/wwwssi.htm
- Apache チュートリアル: Server Side Includes 入門
  - http://httpd.apache.org/docs/2.0/ja/howto/ssi.html
