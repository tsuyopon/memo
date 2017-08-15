# 概要

SSLのバージョンや歴史などについて整理しておく

# 内容
- ?
  - SSL1.0(未発表)
- 1994
  - SSL2.0
- 1995
  - SSL3.0
    - 2014年、暗号データの最後尾にある「パディングデータ」を改変する「POODLE攻撃」に対する脆弱性によりトドメを刺される
	- ガラケーが対応しているのはここまでが多い
- 1999
  - TLS1.0
	- AndroidはAndroid4.3未満はほぼTLS1.0までが対応となっている
	- Beast攻撃における脆弱性が存在する。
- 2006
  - TLS1.1
    - Android4.3以降が対応している
- 2008
  - TLS1.2
    - ハッシュ関数にSHA-256が追加
- 2013
  - TLS1.3検討開始


# 参考
### Androidの標準ブラウザ・HTTPクライアント・WebViewでのSNI対応状況
- Android 3.0 (Honeycomb)以降の標準ブラウザでは、SNIに対応済
- HTTPクライアントは2.3以降でHttpsURLConnectionクラスを使っている場合、SNIに対応する。
- WebViewでは、Android2.3ではNG、Android4.0以上ではOKとなるとのこと

- 参考
  - http://knowledge.sakura.ad.jp/tech/1706/

### Androidの注意点
- AndroidのWebは癖が強く、他の環境では必要ない中間証明書が必要であったりするらしい

### 対応状況一覧
一覧が可視化された資料でブラウザや各種プラットフォームでのTLSやその詳細の対応状況などが確認できる。
- https://ja.wikipedia.org/wiki/Template:%E3%82%A6%E3%82%A7%E3%83%96%E3%83%96%E3%83%A9%E3%82%A6%E3%82%B6%E3%81%AB%E3%81%8A%E3%81%91%E3%82%8BTLS/SSL%E3%81%AE%E5%AF%BE%E5%BF%9C%E7%8A%B6%E6%B3%81%E3%81%AE%E5%A4%89%E5%8C%96
