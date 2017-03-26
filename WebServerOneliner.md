# 概要
簡易WEBサーバの立て方についてまとめておく

# 詳細

### Python2
デフォルトでは8000番ポートとなっているようだが、以下のようにしてポート番号を指定することもできる
```
$ python -m SimpleHTTPServer 8080
```

python3で使えるかどうかわかっていないけど以下を使えばCGIが動かせるみたい
```
$ python -m CGIHTTPServer
or 
$ python -m CGIHTTPServer 8080
```

### Python3
実際に試せていないですがPython3だと次のように変わります。デフォルトだと8000番ポートとなる。
```
$ python3 -m http.server 8080
```

### ruby(1.9.3+)
unライブラリというのがあるらしい
```
$ ruby -run -e httpd . -p 8000
```

HTTPだと次のようにしてサーバにすることもできる
```
$ ruby -rwebrick -e 'WEBrick::HTTPServer.new(:DocumentRoot => "./", :Port => 8000).start'
```

HTTPSだと次のようになる
```
$ ruby -rwebrick -rwebrick/https -e 'WEBrick::HTTPServer.new(:DocumentRoot => "./", :Port => 8000, :SSLEnable => true, :SSLCertName => [["CN", WEBrick::Utils::getservername]] ).start'
```

### PHP(5.4+)
0.0.0.0としておけばどこからでも接続することができる。
```
$ php -S 0.0.0.0:3000
```

### コマンドライン
```
$ while true; do { echo -e 'HTTP/1.1 200 OK\r\n'; echo 'HELLO'; } | nc -l 8000; done
```

返信するファイルを指定したい場合には次のようにすればOK
```
$ while :; do { echo -e 'HTTP/1.1 200 OK\n\n'; cat index.html; } | nc -l 8000; done
```

こんな感じで確認できる。
```
$ curl http://localhost:8000/
```

### Node
次のようにしてhttpサーバが起動できます。
```
$ npm install -g http-server
$ http-server -p 8000
Starting up http-server, serving ./public
Available on:
  http:127.0.0.1:8000
  http:192/168/0.1:8000
Hit CTRL-C to stop the server
```

またはserveというモジュールを利用してもOK
```
$ npm install -g serve
$ serve -p 8000
serving /home/suda on port 8000
```

"Hello World"だけを返すウェブサーバ
```
$ node -e "require('http').createServer(function(req, res) { res.end('hello world'); }).listen(3000);"
```

### Perl
パッケージインストールが必要です。
```
$ sudo cpan Task::Plack
```

次のコマンドで実行可能です。
```
$ plackup -MPlack::App::Directory -e 'Plack::App::Directory->new({root=>$ENV{PWD}})->to_app'
HTTP::Server::PSGI: Accepting connections at http://0:5000/
```

# 参考
- ワンライナーWebサーバを集めてみた
 - http://qiita.com/sudahiroshi/items/e74d61d939f18779970d
