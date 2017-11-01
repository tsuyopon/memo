# 概要
ルート証明書の確認方法やインポート方法などについてまとめる
サーバーとブラウザの２つに分けてこれらについてまとめることにする。

# 詳細(サーバー)

## ルート証明書のパスを確認する

### Linux
yumが存在するシステムでは次のようにしてインストールすることが可能である。
```
$ yum install ca-certificates
```

- RHEL6以降
```
/etc/pki/tls/certs/ca-bundle.crt
```
- FedoraCore2
```
/usr/share/ssl/certs/ca-bundle.crt
```

### MacOSX
- https://superuser.com/questions/247686/wheres-the-ca-cert-bundle-on-osx

ただし、キーチェーンのフォーマットなのでどのように確認すればいいのか謎
```
/System/Library/Keychains/
/Library/Keychains/
~/Library/Keychains/
```

と思ったらhomebrewなどをインストールするとopensslでインストールされるcert.pem(この中に沢山のルート証明書が入っている)が以下に配置される。
ただし、これはMACのシステム的(キーチェーンなどからは利用されない)に利用されるものでは無いので注意すること
```
/usr/local/etc/openssl/cert.pem
```

## ルート証明書を追加・削除する

### MacOSX
- 追加
```
$ sudo security add-trusted-cert -d -r trustRoot -k /Library/Keychains/System.keychain ~/new-root-certificate.crt
```
- 削除
```
$ sudo security delete-certificate -c "<name of existing certificate>"
```

### Windows
- 追加
```
$ certutil -addstore -f "ROOT" new-root-certificate.crt
```
- 削除
```
$ certutil -delstore "ROOT" serial-number-hex
```

### Linux
- CentOS5
```
// add
$ cat foo.crt >>/etc/pki/tls/certs/ca-bundle.crt
```
- CentOS6
```
$ yum install ca-certificates
$ update-ca-trust enable                        # CentOS 6ではデフォルト無効、CentOS 7ではデフォルト有効であることに注意
$ cp foo.crt /etc/pki/ca-trust/source/anchors/
$ update-ca-trust extract
$ stat /etc/pki/tls/certs/ca-bundle.crt         # 更新を確認する
```
- Ubuntu, Debian
```
// add
$ sudo cp foo.crt /usr/local/share/ca-certificates/foo.crt
$ sudo update-ca-certificates

// remove
$ sudo rm /usr/local/share/ca-certificates/foo.crt
$ sudo update-ca-certificates --fresh
```


### Linuxのルート証明書の作成方法を知る

```
$ ls -alt /etc/ssl/certs/ca-certificates.crt
-rw-r--r-- 1 root root 273790 Apr 27  2015 /etc/ssl/certs/ca-certificates.crt
```



# 詳細(ブラウザ)
### ルート証明書のパスをサーバーに追加する方法

## ルート証明書を確認する

### IEでルート証明書を確認する
- 「インターネットオプション」-> コンテンツタブから「証明書」をクリック -> 「信頼されたルート証明機関」タブをクリック

### firefoxでルート証明書を確認する
以下はver56.0.2の方法で確認
- 画面右上のハンバーガーアイコン -> 「設定」をクリック -> 画面左の「プライバシーとセキュリティ」をクリック -> 「証明書を表示」をクリック -> 「認証局証明書」タブを選択

### MacOS端末で含まれるルート証明書を確認する
「Finder」->「ユーティリティ」->「キーチェーンアクセス」を開いて
画面左側の「システムルート」と「証明書」を選択すると表示されます。

- 参考
  - https://www.websec-room.com/2016/05/15/2647

### Android端末で含まれるルート証明書を確認する
Android 4.0 以降から、ちゃんと標準機能でルート証明書ストアのビューアというのがあるらしく次の方法で見ることができるようです。
表示内容はかなりイマイチで拡張領域などの情報は表示されないとのこと
- 「Settings/設定＞Security/セキュリティ＞Trusted credentials/信頼できる認証情報」

### chromeでルート証明書をインストールする
以下はver62.0.3202.75でのMACの確認方法です。

ブラウザ画面右上の設定ボタンからchrome://settings/を開いて、画面最下部の「詳細設定」をクリックする。
「証明書の管理」をクリック -> キーチェーンアクセスの画面が表示される。 


## ルート証明書をインポートする

### IEでルート証明書をインストールする。
「インターネットオプション」-> コンテンツタブから「証明書」をクリック -> 「信頼されたルート証明機関」タブをクリック -> 「インポート」で配置します。

- 参考
  - https://knowledge.symantec.com/jp/support/mpki-support/index?vproductcat=V_S_M&vdomain=VERISIGN.JP&page=content&actp=CROSSLINK&id=SO23863&locale=ja_JP&redirected=true

### firefoxでルート証明書をインストールする
以下はver56.0.2の方法で確認
- 画面右上のハンバーガーアイコン -> 「設定」をクリック -> 画面左の「プライバシーとセキュリティ」をクリック -> 「証明書を表示」をクリック -> 「認証局証明書」タブを選択 -> 「インポート」からファイルを選択

### chromeでルート証明書をインストールする
以下はver62.0.3202.75でのMACの確認方法です。

ブラウザ画面右上の設定ボタンからchrome://settings/を開いて、画面最下部の「詳細設定」をクリックする。
「証明書の管理」をクリック -> キーチェーンアクセスの画面が表示される。 

### iOSでルート証明書をインストールする
iOSでルート証明書を入れる手順は次のようにすればいけるらしい(実際には未確認)
- 1. ルート証明書を.cer, .crt, .pemのいずれかの形式で保存します。
- 2. メールでiPhoneやiPadなどに送信します。
- 3. 受け取った端末で上記形式のファイルを開こうとするとインストール画面が表示されるので、「インストール」をクリック

- 参考
  - http://security.data-site.info/291.html

### Androidでルート証明書をインストールする
Androidでルート証明書を入れる手順は次のようにすればいけるらしい(実際には未確認)
- 1. ルート証明書を.cer, .crtの拡張子のいずれかで保存します。(.pemは含まれていない)
- 2. ルート証明書を端末へメールで送るか、SDカードで送ります。
- 3. 「設定」>「ユーザ設定」>「セキュリティ」>「認証情報ストレージ」>「ストレージからのインストール」に移動(バージョンなどで異なる可能性あり)
- 4. インストールする証明書のファイル名をタップしてインストールします。

- 参考
  - http://security.data-site.info/291.html

## ルート証明書に含まれる証明書一覧をウェブサイトから確認する

### Microsoft(Windows)
参考になりそうなURL
- ルート証明書プログラム(Microsoft)
  - https://technet.microsoft.com/ja-jp/library/cc751157.aspx
- Configure Trusted Roots and Disallowed Certificates
  - https://technet.microsoft.com/en-us/library/dn265983.aspx

ルート証明書一覧は以下の「Participants list」配下のリンクにありそう
- Microsoft Trusted Root Certificate Program: Participants
  - https://social.technet.microsoft.com/wiki/contents/articles/31634.microsoft-trusted-root-certificate-program-participants.aspx

### MacOS
macOS で利用できる信頼されたルート証明書の一覧
- https://support.apple.com/ja-jp/HT202858

上記ページにはMAC各バージョンに含まれるルート証明書一覧へのリンクが記載されています。
- macOS High Sierra で利用できる信頼されたルート証明書の一覧
  - https://support.apple.com/ja-jp/HT208127
- macOS Sierra で利用できる信頼されたルート証明書の一覧
  - https://support.apple.com/ja-jp/HT207189
- OS X El Capitan で利用できる信頼されたルート証明書の一覧
  - https://support.apple.com/ja-jp/HT205204
- OS X Yosemite で利用できる信頼されたルート証明書の一覧
  - https://support.apple.com/ja-jp/HT205218
- OS X Mavericks で利用できる信頼されたルート証明書の一覧
  - https://support.apple.com/ja-jp/HT203120


### iOS
iOS で利用できる信頼されたルート証明書の一覧
- https://support.apple.com/ja-jp/HT204132

上記ページにはiOS各バージョンに含まれるルート証明書一覧へのリンクが記載されています。
- iOS 11 で利用できる信頼されたルート証明書の一覧
  - https://support.apple.com/ja-jp/HT208125
- iOS 10 で利用できる信頼されたルート証明書の一覧
  - https://support.apple.com/ja-jp/HT207177
- iOS 9 で利用できる信頼されたルート証明書の一覧
  - https://support.apple.com/ja-jp/HT205205
- iOS 8 で利用できる信頼されたルート証明書の一覧
  - https://support.apple.com/ja-jp/HT205214
- iOS 7：信用できるルート証明書の一覧
  - https://support.apple.com/ja-jp/HT203065


## トラブルシュート

### 中間証明書がキャッシュされているかもしれないので削除する
ブラウザでは中間証明書をキャッシュすることがあります。
中間証明書の設定を間違えてしまったのに、ルート証明書を辿ってアクセスできるといった場合には中間証明書がブラウザ内でキャッシュしている可能性を疑うのがいいかもしれません。

- chrome
  - https://serverfault.com/questions/279984/how-do-i-clear-chromes-ssl-cache
- firefox
  - cert8.dbのパスを検索してrenameすることによって、中間証明書のキャッシュが含まれるファイルを削除することができます。
  - (参考) https://superuser.com/questions/351516/do-intermediate-certificates-get-cached-in-firefox
```
$ find ~/Library -name cert8.db
/Users/tsuyoshi/Library/Application Support/Firefox/Profiles/l4n4yk3y.default-1462627312215/cert8.db
$ mv -iv "/Users/tsuyoshi/Library/Application Support/Firefox/Profiles/l4n4yk3y.default-1462627312215/cert8.db" ~
```

- 参考
  - http://qiita.com/Hexa/items/ce0ac23526df12a64ad0

### サーバ証明書と中間証明書が一致していることを検証する
```
$ openssl s_client -connect hoge100.xxx.co.jp:443 -servername example.co.jp -showcerts
// 上記出力結果から「BEGIN CERTIFICATE」から「END CERTIFICATE」までのサーバ証明書の行を抽出してserver.pemとして保存する
$ openssl x509 -issuer_hash -noout -in server.pem
99d91429
```

続いて、CA認証局から中間証明書をダウンロードして上記のハッシュ値と一致することが確認できればサーバ証明書から中間証明書が辿れることがわかります。
以下の中間証明書はサイバートラストのリンク。
```
$ wget https://www.cybertrust.ne.jp/sureserver/download/root_ca/PUBCAG3.txt
$ openssl x509 -subject_hash -noout 
99d91429
```

一致しているのでサーバ証明書から中間証明書へとたどる事ができることが確認できる。
中間証明書がキャッシュで持っていたとしてもおそらくこのハッシュ値経由でルート証明書まで検出することができる。

ハッシュ値の考え方については以下の資料が役に立つ
- http://dsas.blog.klab.org/archives/50484787.html


# 雑記メモ(あとで整理)
### ルート証明書

このディレクトリはなに?
- http://dsas.blog.klab.org/archives/50484787.html
```
$ ls /etc/ssl/certs/
00673b5b.0  8470719d.0								TURKTRUST_Certificate_Services_Provider_Root_1.pem
024dc131.0  84cba82f.0								TURKTRUST_Certificate_Services_Provider_Root_2.pem
02b73561.0  85cde254.0								TURKTRUST_Certificate_Services_Provider_Root_2007.pem
034868d6.0  861a399d.0								TWCA_Global_Root_CA.pem
039c618a.0  861e0100.0								TWCA_Root_Certification_Authority.pem
(snip)
```
このディレクトリはなに?

```
$ ls -alt /usr/share/ca-certificates/
mozilla/     spi-inc.org/ 
```

上記をまとめたもの?
```
$ ls -alt /etc/ssl/certs/ca-certificates.crt
-rw-r--r-- 1 root root 273790 Apr 27  2015 /etc/ssl/certs/ca-certificates.crt
```

- 参考
  - http://d.hatena.ne.jp/satob/20060226/p2
