# 概要
chromeについて

# 詳細

## 役に立つプラグイン
自身が使ったことがある役に立つプラグインを紹介する
- SeleniumIDE
  - テスト操作を録画したり、実行することができるプラグイン
- EditThisCookie
  - Cookie情報を変更することができるプラグイン

### chrome://関連URL一覧を表示する
- chrome://で始まる一覧リンクを表示する
  - chrome://chrome-urls


以下のようなURLが表示されます。この他にもたくさんありますが一例です。
- バージョン情報
  - chrome://version/
- 設定
  - chrome://settings/
- クラッシュレポート
  - chrome://crashes
- ネットワーク関連(Evetns, Proxy, DNS, Sockets, DomainSecurityPolicy)
  - chrome://net-internals/
- HTTP/2周り!?
  - chrome://process-internals/#web-contents
- 特殊機能を変更する場合
  - chrome://flags/


### PDFを作成する
chrome バージョン59以降ではヘッドレスchromeが利用できるらしいので調べてみる。
```
$ chrome --headless --print-to-pdf https://www.chromestatus.com/
```

### 極めろ！！Google Chrome Devtools 52の関節技
- https://qiita.com/sueshin/items/7da3330b0e17696602b1

# 参考URL
- https://developers.google.com/web/updates/2017/04/headless-chrome
- headless chrome demo
  - https://www.youtube.com/watch?v=n6biclFh0i0&feature=youtu.be
