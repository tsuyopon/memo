# 概要
TLSでのリネゴーシエーションについて
TLSでリネゴーシエーションが発生する起因については次の２つであるようだ。
- (1) 鍵について
  - 鍵のアップデートを行う場合
  - シーケンス番号が１巡してしまう
- (2) クライアント認証をさせる場合
  - たとえば、今まではサーバ認証しか行われていなかったが特定のエントリポイントでクライアント認証が必要な場合

関連がある箇所としては次のHelloRequestの箇所となる。HelloRequestパケットはサーバからいつでも新しいネゴシエーションを行いたい場合に行うことができる。
- https://tools.ietf.org/html/rfc5246#section-7.4.1.1

TLS1.3ではこのリネゴーシエーションの仕組みが廃止されている。

# TODO
- TLS1.3でリネゴーシエーションが廃止されているのはなぜか?
- HelloRequestを返却するタイミングをopensslライブラリから確認してみる。
- WiresharkでHelloRequestを補足してみる