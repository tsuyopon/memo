# 概要
ApacheのSSL/TLS周りについて

# 詳細

### Apacheサーバで、RSAとECCで署名した証明書を出し分けをする
confファイルにRSAとECCで署名されたサーバ証明書と鍵をそれぞれ記述するだけで出し分けすることが可能になるようだ。
```
SSLCertificateFile    ./rsa.crt
SSLCertificateKeyFile ./rsa.key
SSLCertificateFile    ./ecc.crt
SSLCertificateKeyFile ./ecc.key
```

- SeeAlso
  - http://asnokaze.hatenablog.com/entry/20141013/1413194597

### mod_sslを使用する。(RedHat9)
今回はOpenSSL＋mod_sslを使用して行います。(これがデファクトスタンダードです。)
この場合にはソースからmod_sslがモジュールとして組み込まれている必要があります。
尚、SSLはポート443/TCPでトランスポート層で動作します。

```
- 1.httpd.confに以下の記述があるかどうか確認する。
```
	 <IfModule mod_ssl.c>
	    Include conf/ssl.conf   <= $(ServerRoot)/confにssl.confがある亊を確認する
	 </IfModule>
```

- 2.ssl.confの設定
```
# mkdir /var/www/html/sslsite  <= SSLのDocumentRootとするディレクトリ
# vi /var/www/html/sslsite/index.html
 (test用に簡単なHTMLを作っておく)
# vi /etc/httpd/conf.d/ssl.conf
```
以下の記述があること確認する。省略している部分もある。
```
	 Listen 443 
	 
	 <VirtualHost test.itbdns.com:443>
	   DocumentRoot "/var/www/html/sslsite"
	   ServerName test.itbdns.com:443
	   ServerAdmin test@test.com
	   SSLEngine on
	   SSLCertificateFile /etc/httpd/conf/ssl.crt/server.crt
	   SSLCertificateKeyFile /etc/httpd/conf/ssl.key/server.key
	 </VirtualHost>
```
- 3.Apacheの起動
```
# /usr/sbin/apachectl start
SSLも起動したい場合には次のようにする。
# /usr/sbin/apachectl startssl
```

以上がデフォルトでRedHatなどに含まれるパッケージでの設定である。
以下にソースからインストールした場合に必要なサーバー鍵作成、証明書作成の手順を述べる。

### サーバー鍵作成、サーバー証明書の作成、ssl.confの作成(sourceインストール時)
以下では/usr/local/apacheにapacheがインストールされたものとして仮定する。ただ
しパッケージとしてapacheがrpmでインストールされているものと仮定する。
- 1.サーバーの鍵を作成する
```
# cd /etc/httpd/conf
# rm ssl.key/server.key  <=デフォルトで入っている鍵を削除
# rm ssl.crt/server.crt  <=デフォルトで入っている鍵を削除
# cd /usr/share/ssl/certs
# make genkey
ここでパスワード入力を求められる。
(注)
サーバーを起動する度にパスワードを入力しないようにするにはmake genkeyではなく 以下の2つのコマンドを使用する。
# /usr/bin/openssl genrsa 1024 > /etc/httpd/conf/ssl.key/server.key
# chmod 400 /etc/httpd/conf/ssl.key/server.key
```
- 2.サーバー証明書の作成
```
# make testcert
対話形式で聞かれるので、以下のように入力する。
Country Name(2 letter Code)[GB]:JP
State or Province Name(full Name)[Berkshire]:Saitama
Locality Name(eg,city)[Newnury]:Kawaguchi-City
Organization Name(eg,company)[My Company Ltd]:Univercity
Organization Unit Name(eg,section)[]:science and technology
Common Name ()[]:www.test.itbdns.com
Email Address[]:test@test.com
(注)ぶっちゃけ適当でも構わない。
# mkdir /usr/local/apache/conf/ssl.crt
# mkdir /usr/local/apache/conf/ssl.key
# cd /etc/httpd/conf
# cp ssl.crt/server.crt /usr/local/apache/conf/ssl.crt/server.crt
# cp ssl.key/server.key /usr/local/apache/conf/ssl.key/server.key
```
- 3.後は先ほどと同じようにssl.confを設定して、apacheを再起動すれば良い。

