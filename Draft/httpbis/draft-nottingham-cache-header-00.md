# 概要

# 解決したい課題
HTTPではデバッグで深堀する際に、リクエストがどのように扱われたのかの詳細事項をヘッダに追加することが多い。
しかし、これらのヘッダのセマンティクスは曖昧であるので、明らかにすることで実践的なものへと現行のHTTPキャッシュモデルをアップデートしたい。

# 解決手段
次のようなヘッダを定義する。
最初に書かれたキャッシュアクションがオリジンの近くにいるキャッシュを表しており、一番後ろに記述されたものがuser-agentの近くで利用されたキャッシュアクションを表している(user-agentで付与することも可能)
```
Cache: HIT_FRESH; node="reverse-proxy.example.com:80";
                  key="https://example.com/foo|Accept-Encoding:gzip",
       HIT_STALE; node="FooCDN parent"; fresh=-45; age=200; latency=3,
       MISS; node="FooCDN edge"; fresh=-45; age=200; latency=98
```

上記で登場するHIT_FRESH, HIT_STALE, MISSなどのキャッシュアクションを意味する大文字の意味は次の通り
- HIT_FRESH
  - The cache used a fresh stored response to satisfy the request without going forward
- HIT_STALE 
  - The cache used a stale stored response to satisfy the request without going forward
- HIT_REFRESH_MODIFIED 
  - The cache had a stale stored response, went forward to validate it, and used the new response to satisfy the request
- HIT_REFRESH_NOT_MODIFIED 
  - The cache had a stale stored response, went forward to validate it, and used the stored response to satisfy the request
- HIT_REFRESH_STALE 
  - The cache had a stale stored response, went forward to validate it, and encountered a problem, so the stored response was used to satisfy the request
- MISS 
  - The cache did not have a stored response, so the request was forwarded
- MISS_CLIENT 
  - The client included request directives (e.g., Pragma, Cache-Control) that prevented the cache from returning a response, so the request was forwarded
- BYPASS 
  - The cache was configured to forward the request without attempting to use a stored response
- ERROR 
  - The cache was unable to use a stored response or obtain one by going forward

上記で登場するnode, key, fresh, age等の小文字の意味は次の通り
- node 
  - a string identifying for the cache node. MAY be a hostname, IP address, or alias.
- fresh 
  - an integer indicating the cache’s estimation of the freshness lifetime ([RFC7234], Section 4.2.1) of this response in seconds, including any locally applied configuration. MAY be negative.
- age 
  - an integer indicating the cache’s estimation of the age ([RFC7234], Section 4.2.3) of this response in seconds. MUST be 0 or greater.
- cacheable 
  - a boolean indicating whether the cache can store this response, according to [RFC7234], Section 3 and any locally applied configuration.
- key 
  - a string representing the key that the cache has associated with this response. This might include the request URL, request headers, and other values.
- latency 
  - an integer indicating the amount of time in milliseconds between the receipt of a complete set of request headers and sending the complete set of response headers of this response, from the viewpoint of the cache. Note that this may not include buffering time in transport protocols and similar delays.
- cl_nm 
  - a boolean indicating whether the response to the client had a 304 Not Modified status code.

# URL
- https://mnot.github.io/I-D/cache-header/
