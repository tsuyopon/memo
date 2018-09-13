# HTTP-initiated Network Tunnelling (HiNT)

# 解決したい課題
HTTP CONNECTメソッドはHTTPクライアントに対して、プロキシ経由で別のオリジンサーバに対してのTCPトンネリングを許容してきました。
近年、HTTP/QUICが含まれることによって今まではTCPだけだったものが、UDP/TCP双方を踏まえた上での設計方針を立てる必要がある。

HTTP/QUICクライアントからHTTP/QUICによるフォワードプロキシを定義する。これは側が次のどのような種別でオリジンを提供しているのかといったことも考慮しなければならない
- HTTP/2サーバ
- HTTP/QUICサーバ

SOCKS(RFC1928)やTURN(RFC5766)といった他のプロキシも登場するが、TCPやUDPでもいくつかのwell-knownポートはブロックされているのでここで明確化しておくことでこれらを許容しやすくする狙いがある。
今回のこのドラフトはクライアントの裏側に存在するフォワードプロキシのみが対象となっています。

# 解決方法
次の構成が稼働できるようなUDPを含んだフォワードプロキシを検討する必要がある。
- UDP-based HTTP/QUIC client
- HTTP/QUICのオリジンサーバ

# 参考URL
- https://tools.ietf.org/html/draft-pardue-httpbis-http-network-tunnelling-00
- IETF102スライド
  - https://datatracker.ietf.org/meeting/102/materials/slides-102-httpbis-hint-and-helium-for-udp-and-ip-tunnelling-00


