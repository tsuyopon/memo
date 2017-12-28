# 概要
キャッシュに効くヘッダについてまとめます
- Cache-Control, Pragma, Expires, Last-Modified, ETag, Cache-Controlなどのブラウザキャッシュさせるためのレスポンスヘッダ
- ブラウザ等から確認に使われるIf-Modified-Since, If-None-Match, If-Matchヘッダについて

RFC2616の「13 Caching in HTTP」を一通り目を通しておくと良いかもしれない
- https://tools.ietf.org/html/rfc2616#section-13

# 詳細

### Cache-Controlヘッダについて
HTTP1.0ではPragmaヘッダが利用されます
以下で表現する"共有キャッシュ"とは中継者(プロキシサーバ)を指していることに注意してください。

- キャッシュストレージを全く使用しない
  - www.yahoo.co.jpなどにアクセスすると後者のパターンが表示されました。
```
Cache-Control: no-store
or
Cache-Control: no-cache, no-store, must-revalidate
```
- キャッシュを使う場合は必ずサーバーにキャッシュに変更がないか確認しろという意味も含む(no-cacheから勘違いしやすいので注意)
```
Cache-Control: no-cache
```
- ひとりのユーザーのためのものである(private)
  - 共有キャッシュに保存してはならない。ブラウザのプライベートキャッシュはこの場合でも保存します。
```
Cache-Control: private
```
- どのキャッシュでも保存して構わない(public)
  - HTTP 認証を伴うページや通常はキャッシュできないレスポンスステータスコードのページも保存されるかもしれない。
```
Cache-Control: public
```
- 有効期限を指定する
  - リソースが陳腐化していないと考えられる再長時間です。変更しない予定のアプリケーションのファイル(css, js, img)には、たいてい積極的なキャッシュを行います
```
Cache-Control: max-age=31536000
```
- ブラウザにキャッシュはさせるけど、変更がないかどうかを都度確認させるようにしたい
```
Cache-Control: max-age=0
or
Expires "Mon, 26 Jul 1997 05:00:00 GMT"      // そのときの時刻を指定する
```
- 共有キャッシュにおいて、max-ageディレクティブまたはExpiresヘッダで指定された値を上書きする
```
Cache-Control: s-maxage=60
```
- 共有キャッシュには200秒だが、ブラウザには60秒までしか保存させない
```
Cache-Control: s-maxage=200, max-age=60
```
- キャッシュはリソースを使用する前に陳腐化の検証をしなければならない
```
Cache-Control: must-revalidate
```
- 中継者は形式変換してはならない(画像の圧縮等を防ぐ)
```
Cache-Control: no-transform
```
- 共有キャッシュに対して、キャッシュしたレスポンスの有効性の再確認を要求する(プロキシに対してmust-revalidateを要求する)
```
Cache-Control: proxy-revalidate
```

ここで説明した以外にもあるようだが詳しくは以下のあたりを参考のこと
- http://d.hatena.ne.jp/s-kita/20080927/1222508924

- max-ageとs-maxageについては以下が詳しい
  - https://suin.io/534

### Pragmaヘッダについて
Content-Typeと処理が似ているPragmaヘッダだが、HTTP1.1だとContent-Typeを解せないプロキシやブラウザがいるのかもしれない。
このような場合には、Pragmaヘッダをレスポンスに含めると処理してくれる可能性がある(この方法が常に有効であるという保証はない)。
```
Pragma: no-cache
```

### Expiresを含めたブラウザ処理の流れ
次のような形式でExpiresは指定されます。キャッシュの有効期限を指定します。 Expiresを1年よりも先に指定するのはRFC違反です。
```
Expires: "Mon, 26 Jul 1997 05:00:00 GMT"
```

次のCache-Control指定と冗長です。
```
Cache-Control: max-age=xxx
```

こちらGoogleの記事によると「より広くサポートされているため、Cache-Control: max-age よりも Expires をおすすめします」とのこと。Cache-Control, Expiresを両方指定するのは冗長なのでどちらか片方にしてくださいといったことも記載されています
- https://developers.google.com/speed/docs/insights/LeverageBrowserCaching


強制的にキャッシュを利用させないといったことで次のような荒業が利用されることがあります(www.yahoo.co.jpではこれを返していました)
```
Expires: -1
```

### Last-Modified, If-Modified-Sinceヘッダを含めたブラウザの処理の流れ
Last-Modifiedがサーバからのレスポンスに付与されている場合の流れは次の通りです。
- 1. ブラウザからリクエスト(初回リクエスト)
- 2. サーバからレスポンスコード200応答 + Last-Modifiedレスポンスヘッダ付きで応答が帰ってくる
- 3. ブラウザからリクエスト(2度目)
  - 前回、Last-Modifiedを含めて受信しているので、Last-Modifiedの内容をIf-Modified-Sinceヘッダ(以下、IMS)に含めてサーバに送信します。
- 4. サーバはIMSと比較してコンテンツ最終更新時刻を比較します。
  - 変更がなければ、ブラウザにレスポンスコード304 Not Modifiedを返却します。
- 5. ブラウザは304を受信したら、自分自身のキャッシュを読み込んでブラウザに表示させます。

CDNでは304ヘッダはそのままオリジンにプロキシするケースがほとんどです。

### ETag, If-None-Matchを含めたブラウザの処理の流れ
ETagがサーバからのレスポンスに付与されている場合の流れは次の通りです。
- 1. ブラウザからリクエスト(初回リクエスト)
- 2. サーバからレスポンスコード200応答 + コンテンツごとにユニークに生成したETagを添付して送信する。
```
例) ETag: "3c-60473f10"
```
- 3. ブラウザからリクエスト(2度目)
  - すでにETagを受信している場合は、ETAGSの内容をIf-None-Matchヘッダに含めてリクエストする
- 4. サーバはIf-None-Matchを受信したらサーバ内にあるコンテンツと比較する。
  - 同じETagであれば、ブラウザにレスポンスコード304 Not Modifiedを返却する。


ETagの生成規則はWebサーバごとに異なります。Apacheは次の３つで構成されます。
- iNode
- ファイルサイズ
- 更新日時
上記はスタンドアロン環境では問題ありませんが、ロードバランサ配下環境では上記のようにiNodeを含むとコンテンツは同一だがサーバ毎にETagが異なるという問題があります。
そこで、Apacheでは次のような対応を行う場合があります。
- ETag自体を生成しない
```
FileETag None
```
- ETag生成にinode番号を利用しない
```
FileETag MTime Size
```

CDNなども含めた場合には、ETagヘッダは一般的には削除するのが普通のようです。
ETagはfirefoxでは動くけど、chromeやsafariでは動かないといった情報もあるので、あまり当てにならないのかもしれない。

### If-Matchについて
If-None-Matchとは逆のIf-Matchというヘッダがあります。以下に特徴を記しておきます。
- サーバがIf-Matchのフィールド値とリソースのETag値が一致した場合のみリクエストを受け付けます。
- ETag値が一致しないとステータスコード412 Precondition Failedレスポンスを応答する。
- If-Matchのフィールドには"*"を指定することが可能です。

### If-Modified-SinceとIf-None-Matchヘッダの優先順位について
ETagはLast-Modifiedより優先順位が高いです(ExpiresヘッダはETagよりも優先度が高いです)。
サーバから同時に出力していた場合にはETagが優先されます。

次のようなルールがあるようです
- If-Modified-SinceよりもIf-None-Matchが優先されます。
- If-Modified-SinceはIf-None-Matchが存在しない場合にのみ利用されます。
- If-Modified-Sinceの値が同一でも、If-None-Matchの値が変更されていた場合にはコンテンツを配信します。

SeeAlso
- https://blog.redbox.ne.jp/http-header-tuning.html


### 冗長ヘッダについて
次のヘッダは同一の意味を表すのでどちらか片方のみをつけるようにしましょう。

- ExpiresとCache-Control
```
Expires: "Mon, 26 Jul 1997 05:00:00 GMT"
Cache-Control: max-age=xxx
```

- If-None-Match, If-Match, If-Modified-Since
```
If-None-Match
If-Match
If-Modified-Since
```



