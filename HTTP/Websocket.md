# 概要
WebSocketはリアルタイムWeb技術の一種であり、リアルタイムかつ双方向な通信を実現するプロトコルです。
Websocketではコネクション確立時にHTTPからWebSocketへプロトコルを切り替えます。コネクションが確立されると「ws」や「wss」から始まるURIスキームでクライアントとサーバ間のやりとりを行います。

これにより次のメリットがあります
- サーバからでもクライアントにデータを送付することができる
- HTTPに比べて小さなデータサイズで必要な情報を送信する

余談ですが、Pushの方式としてはpolling, cometときて、その後Server Sent EventsやWebSocketが登場してきています。

# 詳細
### ライブラリ
- 以下のURLで言語ごとにまとまっています
  - https://www.html5rocks.com/ja/tutorials/websockets/basics/

JavaScriptだと主要なライブラリは以下の通り、star数を見るとsocket.ioが圧倒的かも
- https://socket.io/
- https://github.com/websockets/ws
- https://github.com/theturtle32/WebSocket-Node

### サンプル
- すぐに利用できそうなサンプル
  - 落としてきてnpm insltallしたら、app.js, index.htmlのサーバ名とポート番号を変更して node app.jsする。
  - ブラウザ側でアクセスするだけ
  - https://github.com/Lushe/WebSocket-Chat-Sample.git 

# 参考URL
- WebSocket / WebRTCの技術紹介
  - https://www.slideshare.net/mawarimichi/websocketwebrtc

# SeeAlso
- RFC6455: The WebSocket Protocol
  - https://tools.ietf.org/html/rfc6455
- MSN web docs: WebSockets
  - https://developer.mozilla.org/en-US/docs/Web/API/WebSockets_API
