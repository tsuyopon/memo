# 概要
opensslのx509サブオプションについて

# 詳細
### サーバ証明書の中の詳細を確認する
RFC 5280 の中には拡張として BasicConstraint/KeyUsage/ExtendedKeyUsage など定義されているのですが、これらを用いて認証局となれる (他の CSR への署名が許された) 証明書か、クライアント認証に用いて良いか、などが記述できます。
```
$ openssl x509 -in server.crt -noout -purpose
Certificate purposes:
SSL client : Yes
SSL client CA : Yes (WARNING code=3)
SSL server : Yes
SSL server CA : Yes (WARNING code=3)
Netscape SSL server : Yes
Netscape SSL server CA : Yes (WARNING code=3)
S/MIME signing : Yes
S/MIME signing CA : Yes (WARNING code=3)
S/MIME encryption : Yes
S/MIME encryption CA : Yes (WARNING code=3)
CRL signing : Yes
CRL signing CA : Yes (WARNING code=3)
Any Purpose : Yes
Any Purpose CA : Yes
OCSP helper : Yes
OCSP helper CA : Yes (WARNING code=3)
Time Stamp signing : No
Time Stamp signing CA : Yes (WARNING code=3)
```

### x509証明書の出力を個別に出す
X509のサブオプションを個別に出すことが可能です。以下では複数指定していますが1つでももちろん出力可能です。
```
# openssl x509 -in server.crt -noout -serial -issuer -startdate -enddate -subject -modulus
openssl x509 -in server.crt -noout -serial -issuer -startdate -enddate -subject -modulus
serial=9FBE7329375E63E5
issuer= /C=JP/ST=Saitama/L=Kawaguchi/O=OreOre Company/OU=TestDept/CN=example.co.jp
notBefore=Oct 28 14:09:38 2017 GMT
notAfter=Feb 28 14:09:38 3017 GMT
subject= /C=JP/ST=Saitama/L=Kawaguchi/O=OreOre Company/OU=TestDept/CN=example.co.jp
Modulus=B6B592B2265DAB74C76B23B36A5BB8AADDFADEC2A0D16B3EBA67172F7B566459F50EE0447979D5089A3FBF43D05E45FC691D86D59B797A612BD90B0731B02887AF536798815651196838A2AD75CC201737E563379250A97EBDD263C527AB32E69FADDA92954C67D70D5523F81262B1599A33AC0863B95F39D79DB3496702735AD8EE9F8F66D33B3EF8E28E1D160D9D3908501DE97DB3F7CF16FF644D211F062F6455CD99B8E09F5D3D0BCBC1F7F877F441FC3D1F078B1303C4A0703BA9CB08FF6FB2C274C8884F2371B606CD62CADF629B808C767BEF1605BC7C4FA6C1780F272E5193A50F0B23258428D69AB78B9EBFA52B9D5737F50DD003E00489FDE0C7F5
```
- X509サブオプション参考
  - https://www.openssl.org/docs/manmaster/man1/x509.html

### サーバ証明書の形式をcrtからpemに変換する
以下のコマンドではsource.crtをdest.pemに変換しています。
```
$ openssl x509 -in source.crt -out tmp.der -outform DER
$ openssl x509 -in tmp.der -inform DER -out dest.pem -outform pem
```

### asn1parse形式でサーバ証明書を表示する
ASN.1というのはX509で用いられるバイナリフォーマットの形式です。CSRもX509証明書で規定されているDERでエンコードされています。
```
$ openssl x509 -in server.crt | openssl asn1parse 
    0:d=0  hl=4 l= 876 cons: SEQUENCE          
    4:d=1  hl=4 l= 596 cons: SEQUENCE          
    8:d=2  hl=2 l=   9 prim: INTEGER           :9FBE7329375E63E5
   19:d=2  hl=2 l=  13 cons: SEQUENCE          
   21:d=3  hl=2 l=   9 prim: OBJECT            :sha256WithRSAEncryption
   32:d=3  hl=2 l=   0 prim: NULL              
   34:d=2  hl=2 l= 119 cons: SEQUENCE          
   36:d=3  hl=2 l=  11 cons: SET               
   38:d=4  hl=2 l=   9 cons: SEQUENCE          
   40:d=5  hl=2 l=   3 prim: OBJECT            :countryName
   45:d=5  hl=2 l=   2 prim: PRINTABLESTRING   :JP
   49:d=3  hl=2 l=  16 cons: SET               
   51:d=4  hl=2 l=  14 cons: SEQUENCE          
   53:d=5  hl=2 l=   3 prim: OBJECT            :stateOrProvinceName
   58:d=5  hl=2 l=   7 prim: UTF8STRING        :Saitama
   67:d=3  hl=2 l=  18 cons: SET               
   69:d=4  hl=2 l=  16 cons: SEQUENCE          
   71:d=5  hl=2 l=   3 prim: OBJECT            :localityName
   76:d=5  hl=2 l=   9 prim: UTF8STRING        :Kawaguchi
```

iオプションを付与すると出力にインデントを加えます。
```
$ openssl x509 -in server.crt | openssl asn1parse -i
    0:d=0  hl=4 l= 876 cons: SEQUENCE          
    4:d=1  hl=4 l= 596 cons:  SEQUENCE          
    8:d=2  hl=2 l=   9 prim:   INTEGER           :9FBE7329375E63E5
   19:d=2  hl=2 l=  13 cons:   SEQUENCE          
   21:d=3  hl=2 l=   9 prim:    OBJECT            :sha256WithRSAEncryption
   32:d=3  hl=2 l=   0 prim:    NULL              
   34:d=2  hl=2 l= 119 cons:   SEQUENCE          
   36:d=3  hl=2 l=  11 cons:    SET               
   38:d=4  hl=2 l=   9 cons:     SEQUENCE          
   40:d=5  hl=2 l=   3 prim:      OBJECT            :countryName
   45:d=5  hl=2 l=   2 prim:      PRINTABLESTRING   :JP
   49:d=3  hl=2 l=  16 cons:    SET               
   51:d=4  hl=2 l=  14 cons:     SEQUENCE          
   53:d=5  hl=2 l=   3 prim:      OBJECT            :stateOrProvinceName
   58:d=5  hl=2 l=   7 prim:      UTF8STRING        :Saitama
   67:d=3  hl=2 l=  18 cons:    SET               
   69:d=4  hl=2 l=  16 cons:     SEQUENCE          
   71:d=5  hl=2 l=   3 prim:      OBJECT            :localityName
   76:d=5  hl=2 l=   9 prim:      UTF8STRING        :Kawaguchi
```


### CApathにpemファイルを登録する
opensslにはCApathといってルート証明書を指定することができます。コマンドでは次のようにして指定することができます。
```
$ openssl s_client -connect localhost:4433 -CApath <ディレクトリ名>
```

あとは、そのディレクトリにCA証明書を全部放り込めば良いのですが、ファイル名の付け方に少々決まりがあります
CApath オプションを指定された際に openssl が利用するCA証明書のファイル名には次の命名でルールをつける必要があります。
```
<指定したディレクトリ>/(検証すべき証明書の issuer のハッシュ値).0
```
このハッシュ値は次のコマンドで取得できます。
```
$ openssl x509 -in CA.pem -hash -noout
```

わからなくならないようにpemファイルからシンボリックリンクファイルに落としておくのが一般的なようです。
```
$ cp CA.pem /usr/local/etc/ssl/CA/
$ cd /usr/local/etc/ssl/CA/
$ ln -s CA.pem `openssl x509 -in CA.pem -hash -noout`.0
$ openssl s_client -connect localhost:4433 -CApath /usr/local/etc/ssl/CA/
```

以上により、CApath オプションを使うだけで自動的に必要なCA証明書を選択してくれるようになります。

- 参考
                  - http://dsas.blog.klab.org/archives/50484787.html

