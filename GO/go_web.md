# 概要
go言語でwebアプリケーションを作る際のtips


# 詳細

### WebAPI用フレームワーク比較について

- Qiita: Go言語Webフレームワークランキング
  - https://qiita.com/loftkun/items/1a9951d1864bebdc51e1
  - gin, beego, iris, echo, revel, martiniあたりが10000 over
- Qiita: Golang フレームワーク比較
  - ベンチマークもあって参考になる
  - https://qiita.com/yumin/items/5de33b068ead564ebcbf


### WebAPI用フレームワークについて

標準ではnet/http/httptestが存在する
- https://pkg.go.dev/net/http/httptest

このほかにもstar 1.7kのhttpexpectもある(websocketサポート)
- https://github.com/gavv/httpexpect

# 参考資料
- https://github.com/astaxie/build-web-application-with-golang/tree/master/ja
