# 概要
ブラウザとTLS関連の技術的なメモ

# 詳細

### SSL証明書の詳細確認方法

- Google Chrome(version56以降)
  - (参考) https://www.howtogeek.com/292076/how-do-you-view-ssl-certificate-details-in-google-chrome/
```
Menu -> More Tools -> Developer Tools -> click on the Security Tab. 
```
- Firefox
```
アドレスの鍵マークをクリック -> ">"をクリック -> 「詳細を表示」-> 「証明書を表示...」-> 「詳細」タブ
```
各種項目にクリックするとその値を表示します。


### ルート証明書
ブラウザによってはHTTPSが正しく表示されて、別のブラウザではHTTPSが正しく表示されないといったことがおります。  
ルート証明書への対応状況などをよく確認して、テストすべきブラウザも決めましょう。
- Microsoft(Windows, WindowsPhone, IE, EDGE)
  - windows内部では次のファイルを定期的にダウンロードしているようです。
  - http://ctldl.windowsupdate.com/msdownload/update/v3/static/trustedr/en/authrootstl.cab
  - Active Directoryで管理者がエンタープライズ向けに更新することも可能
- Apple(MacOS X)
  - 下記から各OSバージョンごとに利用できるルート証明書へのリンクがあるのでたどることができます。
  - https://support.apple.com/ja-jp/HT202858
- Apple(iOS)
  - 下記から各OSバージョンごとに利用できるルート証明書へのリンクがあるのでたどることができます。
  - https://support.apple.com/ja-jp/HT204132
- Android
  - メーカーごとに独自のルート証明書リストを搭載しているようです。探しましたが一覧ありませんでした。一応stack flowがあったのでそのリンクを添付しておきます
  - https://stackoverflow.com/questions/6665588/android-list-of-available-trusted-root-certificates
- Mozilla(Firefox, Thunderburd)
  - 大元はこの辺でバージョン管理されている。OSSとして絶大な信頼がある
  - https://hg.mozilla.org/projects/nss/raw-file/NSS_3_30_2_RTM/lib/ckfw/builtins/certdata.txt
- curl
  - Mozillaで利用しているcertdata.txtのファイル形式が独特なので、扱いやすい普通のPEMに変換されて次のURLからリンクが存在します。
  - https://curl.haxx.se/docs/caextract.html
- openssl
  - opensslには最初からバンドルされているルート証明書はなく、opensslにもポリシーは無い。
  - https://www.openssl.org/docs/faq.html#USER15
- ガラケー
  - docomo(30個)
    - https://www.nttdocomo.co.jp/service/developer/make/content/ssl/spec/
  - KDDI(45個)
    - http://www.au.kddi.com/ezfactory/web/zip/ssl_download.zip
  - SoftBank(31個)
    - http://creation.mb.softbank.jp/mc/tech/doc/A-426-111-SSLCertificates_1.0.5.pdf
- Oracle(Java)
  - Oracle JDK/JREのcacertsファイルにはルート証明書リストが格納されています。
  - 次のコマンドで確認できます
```
$keytool -list -rfc -keystore C:/Java/jre1.8.0_102/lib/security/cacerts -storepass changeit
```

### ルート証明書ポリシー
ルート証明書ポリシーに対するポインタをまとめておく
- Microsoft
  - https://social.technet.microsoft.com/wiki/contents/articles/31633.microsoft-trusted-root-program-requirements.aspx
- Apple Root Certificate Program
  - http://www.apple.com/certificateauthority/ca_program.html
- The Chromium Projects
  - https://www.chromium.org/Home/chromium-security/root-ca-policy
- Mozilla Root Store Policy
  - https://www.mozilla.org/en-US/about/governance/policies/security-group/certs/policy/

### go.jpのサイトがmozillaだと安全ではない接続とされる理由
Mozillaはユーザーの安全を守るために、どのルート証明書を登録するかを独自に判断しており、他社の判断を鵜呑みにはしないというポリシーで証明書ストアを管理しています。

例えば、次のGPKIのサイトにアクセスをしても認証してくれません。
- https://www.gpki.go.jp/

以下のチケットにてルート証明書として登録してほしいチケットを投げていますが、mozillaポリシーに合致しておらず議論が長引いている状況です。
- https://bugzilla.mozilla.org/show_bug.cgi?id=870185

尚、Firefox52以降ではsecurity.enterprise_roots.enabledをtrueに変更することによって、Windowsの証明書ストアに登録されたルート証明書をFirefox側で認識して使えるようになりましたが、あくまでもWindowsのみでこの機能はMACでは使うことはできません。
- 参考URL
  - http://www.clear-code.com/blog/2017/6/1.html
  - https://github.com/mozilla-japan/enterprise/issues/21

### クライアントPCでApplicationDataの暗号化された内容をwiresharkで確認する
ブラウザを稼働させるPCで次のようにSSLKEYLOGFILE環境変数を打つことで、その後firefoxで対象ページでアクセスします。
それによって指定したファイルにrandomとmaster secretを出力します。
```
$ export SSLKEYLOGFILE=/tmp/sslkeylog.log
$ open /Applications/Firefox.app/
```

wiresharkでは上記パスを参照して暗号化されているapplication dataを解読することができるようです。

- 参考
  - http://qiita.com/Hexa/items/ce0ac23526df12a64ad0

# 参考URL
- http://qiita.com/n-i-e/items/4de24ac543b07dd5cf82

