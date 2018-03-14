# 概要
TLS1.3についての概要

現時点で最新はdraft26となる。
- https://tools.ietf.org/html/draft-ietf-tls-tls13-26

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

