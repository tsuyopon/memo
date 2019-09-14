# 概要
nghttp2パッケージを使うとHTTP/2用のCライブラリとして提供されています。
nghttp2には他にも次のような便利なツールが提供されます。
- HTTP/2クライアント(nghttp)
- HTTP/2サーバ(nghttpd)
- HTTP/2用ベンチマークの提供(h2load)
- HTTP/2プロキシ(nghttpx)

# nghttp2インストール

### パッケージインストール
Linux
```
$ sudo sh -c 'yum -y install epel-release && yum -y install nghttp2'
```

### ソースコードからのインストール
curlとともにビルドする手順を以下に載せています。
- BUILD_curl.md 


# 参考URL
- Github nghttp2/nghttp2
  - https://github.com/nghttp2/nghttp2
- Official Site
  - https://nghttp2.org/
- API Reference
  - https://nghttp2.org/documentation/apiref.html
