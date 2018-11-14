# 概要
Chunked Requestに関するメモ

# 詳細

### ChunkedRequestを出してみる。
```
$ telnet localhost 80
GET / HTTP/1.1
Host: hoge.example.co.jp
User-Agent: Mozilla/5.0
Transfer-Encoding: chunked
5
aaaaa
0       // この後にEnterを２回押下することでchunked requestが完了する。


```
