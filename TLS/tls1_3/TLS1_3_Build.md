# 概要
TLS1.3関連ソフトウェアのビルドなど

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
$ ./config -d -fPIC --prefix=/opt/openssl-1.1.1 shared zlib enable-tls1_3      // gdbでもデバッグビルドできるように-dをここでは付与
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

### trafficserverでTLS1.3を利用する
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

### curlでTLS1.3を利用するようにビルドする
```
$ git clone https://github.com/curl/curl.git
```
自身が使ったハッシュ値は「b7b2809a212a69f1ce59a25ba86b4f1d8a17ebc4」です。

続いて、ビルドを行います。
```
$ cd curl
$ ./buildconf
$ ./configure --prefix=/opt/curl_master --with-ssl=/opt/openssl-1.1.1 --enable-debug
$ make
$ make test // 省略ok
$ sudo make install
```

- 参考資料
  - https://curl.haxx.se/docs/install.html

あとは次のようにvオプションを付与してアクセスするとTLS1.3で接続しているかどうかを確認することができます。
```
$ /opt/curl_master/bin/curl -k -v -I https://localhost/
```

### tsharkのみをビルドしていれる

GUI環境が存在しないような場合にtsharkだけでも使えると便利です。ここではtsharkが最新版で使えるようにビルドしてみましょう。

あらかじめ必要なソフトウェアをインストールしておきます
```
sudo yum install bison flex libgcrypt libgcrypt-devel glib2-devel libpcap-devel
```

あとはtsharkコマンドのみ使えるようにビルドを行います。
```
$ git clone https://github.com/wireshark/wireshark.git
$ cd wireshark
$ ./autogen.sh
$ ./configure --disable-wireshark --enable-tshark --enable-ipv6 --disable-gtktest --disable-glibtest --disable-editcap --disable-capinfos --disable-mergecap --disable-reordercap --disable-text2pcap --disable-dftest --disable-randpkt --disable-airpcap --disable-rawshark --enable-pcap-ng-default --without-lua --prefix=/opt/wireshark_master
$ make
$ sudo make install
```
