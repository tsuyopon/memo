# CDNI SVA Request Routing Extensions

# 解決したい課題
OpenCachingによるケースでISPがdCDNになる特別なケースがあります。(詳しくはdraft-finkelman-cdni-triggers-sva-extensions.mdを参照)
このドキュメントでは上記ケースでのリクエストルーティングについて述べています。


# 解決方法
OpenCachingに必要となるオブジェクトを定義する。それによって、RFC8006とRFC8008を拡張することを目的とする。
追加するオブジェクトは次の２つです(これらは同時にRFC7736に登録します)
- FCI.RedirectTarget
- MI.FallbackTarget


###  仕様詳細
これから


# 参考URL
- https://tools.ietf.org/html/draft-finkelman-cdni-rr-sva-extensions-01


# TODO
- 仕様がほとんどよめていない
