(WARNING)ちゃんと検証できていないので間違っている可能性十分にあり

# 概要
アルパカ攻撃について(application layer protocol content confusion attack)
Cross-Protocol Attack

# 攻撃概要
HTTPSから特定のサイト(www.bank.com:443)に接続した際に、中間者によって同じサブドメインの別のプロトコル(ftp.bank.com:990)に飛ばされることで以下の３つの攻撃の可能性がありうる。
詳細は本家の図を参照のこと
- 1. Cookieの取得
- 2. ダウンロード攻撃
- 3. reflect攻撃

しかし、これが発生するには条件がありそうである。
- ワイルドカード\*.bank.comの証明書が使われていること
- ftp.bank.com側を改竄できなければダウンロード攻撃やreflect攻撃を実行させることは難しい 
- (論文によると)HTTPSサーバ実装は大抵がALPNに対応しているが、TLSを利用するプロトコルではSMTP, IMAP, POP3, FTPではほとんどがALPNに対応していないという実態がある。

# 対応方法
- クライアント及び、サーバ側の実装がALPNに対応できていることで、接続に使用しているプロトコルが異なれば実装で弾くことが可能
  - HTTPS以外のTLSを使う実装でも、ALPNに対応した実装になっている必要がある。
- サーバ側の実装がSNIで証明書出しわけに対応できていること。さらにエンドポイントごとに異なるドメインを使うようにすること(ワイルドカードを利用することが今回の攻撃にもつながるかも)

# 資料
- https://alpaca-attack.com/
  - アルパカ攻撃の概要について説明した本家ウェブサイト
- https://alpaca-attack.com/ALPACA.pdf
  - アルパカ攻撃について記載された論文
- https://github.com/RUB-NDS/alpaca-code/
  - 検証用コード
