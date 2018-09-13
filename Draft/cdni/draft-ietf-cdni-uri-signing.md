#  URI Signing for CDN Interconnection (CDNI)
次のドラフトを基準にして整理する
- https://tools.ietf.org/html/draft-ietf-cdni-uri-signing-14

CDNI(Content Delivery Network Interconnection)については以下のWIKIを参考にすること
- https://en.wikipedia.org/wiki/Content_delivery_network_interconnection

# 解決する課題

- このドキュメントではURL署名の概念とどのようにしてリダイレクトケースでアクセス認証を提供するかといった概念について述べている。
  - リダイレクトのケースについては、CDN同士やCSP(ContentServiceProvider)とCDN間
- 初期の署名URLに関するゴールとしては、認証されたUser-Agentのみが確実にコンテンツにアクセスできるようにしたい

- URL署名はコンテンツ保護の手法ではないことを明記しておく。すなわち、もし、CSPがコンテンツ自体にプロテクトしたかったとしても、他のメカニズム(例えば、DRM)などが望ましい

アクセスコントロールに加えて、URL署名はDoSインパクトを削減する効果もあります。


次のような全体像になるものと思われる。
```
                   --------
                  /        \
                  |   CSP  |< * * * * * * * * * * *
                  \        /        Trust         *
                   --------      relationship     *
                     ^  |                         *
                     |  |                         *
          1. Browse  |  | 2. Signed               *
               for   |  |    URI                  *
             content |  |                         *
                     |  v                         v
                   +------+ 3. Signed URI     --------
                   | User |----------------->/        \
                   | Agent|                  |  CDN   |
                   |      |<-----------------\        /
                   +------+ 4. Content        --------
                               Delivery

           Figure 1: Figure 1: URI Signing in a CDN Environment

1.3.  CDNI URI Signing Overview
```

# 解決方法
- JSON Web Token(JWT)を用いる事によってURL署名方法を提案する



# 詳細
