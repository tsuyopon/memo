# Cookies: HTTP State Management Mechanism

# 解決したい課題
このRFC6265bisの前はもともとはそれぞれ別のドラフトとして扱われていました。
- (1). Cookie Prefixes
  - 歴史的経緯によって
  - https://tools.ietf.org/html/draft-ietf-httpbis-cookie-prefixes-00
- (2). Same-Site Cookies
  - https://tools.ietf.org/html/draft-ietf-httpbis-cookie-same-site-00
- (3). Deprecate modification of 'secure' cookies from non-secure origins
  - https://tools.ietf.org/html/draft-ietf-httpbis-cookie-alone-01

# 解決方法
- 「__Secure-」と「__Host-」prefixを用意する



# 参考URL
- https://tools.ietf.org/html/draft-ietf-httpbis-rfc6265bis-02
- Cookieの仕様改定版、RFC6265bisの議論
  - https://asnokaze.hatenablog.com/entry/2017/04/26/080916
