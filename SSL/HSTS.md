### HSTS(HTTP Strict Transport Security)ヘッダについて
サーバがクライアント側に送付するヘッダで、HTTPSでアクセスしなければならない時間を伝えるための仕組みです。
このヘッダは非常にシンプルでmax-ageのパラメータのみを受け付けます。
```
Strict-Transport-Security: max-age=15768000;includeSubDomains         // 一般的に6ヶ月
```

- https://tools.ietf.org/html/rfc6797

2015年6月にマイクロソフトもIEへサポートを追加したことで全てのブラウザでHSTSの対応が完了しています。

includeSubDomainsを付与するとxxx.jpへのアクセスに対して、サブドメインのyyy.xxx.jpへのアクセスも全てhttpsに変更します。
ただし、あまり頻繁にキャッシュアウトするような短い期間を設定してしまうとその度に http でつなぎにいってしまう可能性がありますので、十分長い期間を設定することが推奨されているようです。

### Preloaded HSTS
ブラウザのソースコードに組み込まれているリストで、このリストに含まれていればwww.abc.comでもHTTPSでアクセスするといったルールを記述しておきます。  
chromeとfirefoxにはこの仕組みが搭載されています。

例えば、Chrome, Firefoxの場合には次のようなリストが記載されているようです。
- Chrome  
-- https://src.chromium.org/viewvc/chrome/trunk/src/net/http/transport_security_state_static.json
- Firefox  
-- https://dxr.mozilla.org/mozilla-central/source/security/manager/tools/PreloadedHPKPins.json

たとえば、ChromeのPreloaded HSTSに組み込むには次から申請をするらしい
- https://hstspreload.appspot.com/

chromeで特定のドメインが登録されているかどうかを確認するには次から確認すればいいようだ。
- chrome://net-internals/#hsts

- 参考  
-- http://blog.cybozu.io/entry/6096

