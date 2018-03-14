# 概要
TLS1.3についての概要

現時点で最新はdraft26となる。
- https://tools.ietf.org/html/draft-ietf-tls-tls13-26

# TLS1.2未満とTLS1.3の違いについて
- 全般
  - CBCモードが廃止され、AEAD(AES-GCM, ChaCha20-Poly1305など)
    - CBCモードを狙ったBEAST攻撃、Lucky Thirteen攻撃などが頻発したことが背景にある。
- ClientHello
  - TLS1.2と互換性がある
  - サーババージョンはSupported Version拡張(必須)にその役割を移動し、固定で0x0303(TLS1.2)
  - session_idやcompression_methodsは廃止され、代わりにPSKが利用される。ミドルボックス問題のためにlegacy_としてその名残は残る。
  - extensionは必ず存在することになる
  - extensions中で暗号パラメータのやりとりが行われる
- ServerHello
  - 互換性がなくなった
- ClienKeyExchange
  - 廃止
  - ClientHello中のExtensionに移動する
- ServerKeyExchange
  - 廃止
  - ServerHello中のExtensionに移動する
- ChangeCipherSpec
  - 廃止
  - 鍵交換直後に暗号化が開始される

TODO: まだ整理していないので後で追記

# 詳細

### Wiresharkで最新のパケット構造
nightly buildを使うのが一番
- https://www.wireshark.org/download/automated/

### ブラウザからTLS1.3を利用する
利用するためには最新のdraftに対応させるためにnightly buildをインストールして、その後設定を変更する必要があります。
- chrome
  - nightly bildをインストールする
    - https://www.google.com/chrome/browser/canary.html
  - chromeでは「chrome://flags」にアクセスして、TLS1.3設定を有効にして再起動します。
- firefox
  - nightly bildをインストールする
    - https://nightly.mozilla.org/
  - 「about:config」にアクセス、「security.tls.version.max」をTLS1.3を表す4に変更する

- SeeAlso
  - https://www.ghacks.net/2017/06/15/how-to-enable-tls-1-3-support-in-firefox-and-chrome/

### ブラウザからどのTLSプロトコルを利用しているのかどうかを確認する
- chrome
  - Developer Toolsの「Security」タブから確認することができます。
- firefox
  - 開発ツールを開いたら「暗号化」タブでどのプロトコルを利用しているのかを確認することができます。


### opensslでのTLS1.3利用について
openssl-1.1.1ではTLS1.3がデフォルトで利用できる予定となっています。
APIには変更が必要となりそうです。
参考
- https://www.openssl.org/blog/blog/2017/05/04/tlsv1.3/


### TLS1.3を利用できるようにopensslをビルドする(Cent7)
gitコマンドが入っていないので以下に従う
- https://qiita.com/copei/items/710a2d05114ec1637268
```
$ cd /etc/yum.repos.d/
$ sudo wget http://wing-repo.net/wing/7/EL7.wing.repo
$ sudo yum install git
```

参考までに自分が使ったopenssl:masterのコミットバージョンは以下の通り
```
3266cf582a8e1b0bd04600658f64e2c9a79cf903
```

opensslビルドを行います。最新ブランチはOpenSSL_1_1_1-pre2だと若干エラーがありますので最新版を取得します。
configにはTLS1.3を有効にするためにenable-tls1_3を指定します。
```
$ git clone https://github.com/openssl/openssl.git
$ cd openssl
$ ./config -fPIC --prefix=/opt/openssl-1.1.1 shared zlib enable-tls1_3
$ make
$ sudo make install
```

あとはライブラリパスを通しておくことにする
```
$ sudo sh -c 'echo /opt/openssl-1.1.1/lib/ > /etc/ld.so.conf.d/openssl.conf'
$ sudo ldconfig
```

lddやopensslコマンドを実行してみて問題ないことを確認しておく
```
$ ldd /opt/openssl-1.1.1/bin/openssl        
$ /opt/openssl-1.1.1/bin/openssl version
```

### trafficserverをTLS1.3
特に特別なことをせずにビルドしたopenssl-1.1.1とリンクできさえすればOKです。今回は7.1.xタグでビルドします。
```
$ git clone https://github.com/apache/trafficserver.git
$ cd trafficserver
$ git checkout 7.1.x
```

```
$ sudo yum install autoconf automake libtool
$ autoreconf -if
$ ./configure --prefix=/opt/trafficserver-7.1.x_tls13 --enable-debug --enable-experimental-plugins --with-openssl=/opt/openssl-1.1.1
$ make
$ sudo make install
```


### 接続確認の方法など
- サーバとして起動する
```
$ /opt/openssl-1.1.1/bin/openssl s_server -accept 443 -cert server.crt -key server.key -www -debug -tls1_3
```

- クライアントとして接続する
```
$ /opt/openssl-1.1.1/bin/openssl s_client -connect localhost:443 --tls1_3
```


### TLS1.3 draft23として公開されているサーバ
- enabled.tls13.com
- www.tls13.facebook.com
- tls13.crypto.mozilla.org

# 参考資料
- TLS 1.3 の標準化動向(IIJ: 山本和彦さん)
  - draftの歴史などについて。なぜ仕様が変わっていったのかを垣間見れて面白い
  - http://www.mew.org/~kazu/material/2018-tls13.pdf
- TLS 1.3 draft 23 ハンズオン(IIJ: 山本和彦さん)
  - Haskel用クライアントライブラリやpicotlsの説明
  - http://www.mew.org/~kazu/material/2018-handson.pdf
- TLS1.3とは何か? 大津さん資料
  - https://speakerdeck.com/shigeki/tls1-dot-3tohahe-ka
- あどけない話
  - 山本和彦さんによるTLS1.3について20回以上に分割して掲載している。すごい勉強になる記事
  - http://d.hatena.ne.jp/kazu-yamamoto/archive
- 今なぜHTTPS化なのか？インターネットの信頼性のために、技術者が知っておきたいTLSの歴史と技術背景
  - https://employment.en-japan.com/engineerhub/entry/2018/02/14/110000
- TLS1.3 Overview
  - https://qiita.com/sylph01/items/3bf7bc2d42da4e0efb37	
