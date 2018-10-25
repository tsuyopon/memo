TODO:  攻撃手法を埋める

# 概要
Factoring RSA Export Keys（FREAK）の略称で、FREAKと呼ばれるOpenSSLの脆弱性(CVE-2015-0204)です。
Logjamと似ていますが、FREAKはプロトコルではなくOpenSSL実装の脆弱性です。

これは輸出グレードの RSA 鍵を受け入れる問題に依存した攻撃ですが、次のような背景があります。
1992年までは米国では、強固な暗号化技術が輸出規制されていました。
米国の通信暗号化プロトコルSSLの開発会社では、脆弱な暗号化しか行えない商品を輸出せざるを得ない状況となりました。
このような状況が、脆弱な暗号を受け入れてしまうウェブサイトやサーバを世界的に広めるきっかけとなってしいまいました。


# 詳細
### どのような攻撃か
大抵はデフォルトで無効になっているものの、AndroidブラウザのOpenSSLクライアントやSafariなどのApple TLS/SSLクライアントなど幾つかの実装では、サーバが非輸出グレードの暗号を使おうとした場合でも、中間者攻撃を仕掛けて輸出グレードのRSAを要求し、512ビットのRSA鍵を返させることができてしまうという問題です。

### 攻撃手法
大津さんの資料に記載されている
- http://d.hatena.ne.jp/jovi0608/20150304/1425461359

### 対処方法
- 古いブラウザを最新のバージョンにアップグレードする。
- サーバ上のすべてのexport cipher suitesのサポートを無効にする
- Openssl-1.0.1k以降のバージョンには該当のCipherSuiteを無効にしているのでバグが存在しない
  - https://github.com/openssl/openssl/commit/ce325c60c74b0fa784f5872404b722e120e5cab0


### テスト方法
以下方法でLogjamに該当するかどうかをチェックすることができる。
```
OpenSSL: openssl s_client -connect www.example.com:443 -cipher 'EXP'

nmap: nmap --script ssl-enum-ciphers -p 443 www.example.com
```


# 参考URL
- https://weakdh.org/
- https://gist.github.com/spiegel-im-spiegel/47f340122c895ccc8bb8
- 華麗なる因数分解:FREAK攻撃の仕組み
  - http://d.hatena.ne.jp/jovi0608/20150304/1425461359
