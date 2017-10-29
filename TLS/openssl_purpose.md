# 概要
openssl.cnfのnsCertTypeを弄ってpurposeの出力変化を確認します。
この値はopenssl.cnfの次のセクションに存在しているようです。
- usr_cert
- v3_ca
- proxy_cert_ext

# usr_certセクションのnsCertTypeを弄ってpurposeの変化を確認する
環境は次の通り
```
$ dpkg -l | grep -i openssl | grep -w openssl
ii  openssl                                              1.0.1f-1ubuntu11                           amd64        Secure Sockets Layer toolkit - cryptographic utility
```

openssl.cnfを弄ってpurposeで出力される違いを確認します。
```
$ vim ../conf/openssl.cnf
$ openssl ca -policy policy_anything -config ../conf/openssl.cnf -out ca.crt -infiles ca.csr
$ openssl x509 -in ca.crt -noout -purpose 
```

- 何openssl.cnfをいじらない場合
```
Certificate purposes:
SSL client : Yes
SSL client CA : Yes
SSL server : Yes
SSL server CA : Yes
Netscape SSL server : Yes
Netscape SSL server CA : Yes
S/MIME signing : Yes
S/MIME signing CA : Yes
S/MIME encryption : Yes
S/MIME encryption CA : Yes
CRL signing : Yes
CRL signing CA : Yes
Any Purpose : Yes
Any Purpose CA : Yes
OCSP helper : Yes
OCSP helper CA : Yes
Time Stamp signing : No
Time Stamp signing CA : Yes
```

- 「nsCertType = server」に修正した場合
```
Certificate purposes:
SSL client : No
SSL client CA : Yes
SSL server : Yes
SSL server CA : Yes
Netscape SSL server : Yes
Netscape SSL server CA : Yes
S/MIME signing : No
S/MIME signing CA : Yes
S/MIME encryption : No
S/MIME encryption CA : Yes
CRL signing : Yes
CRL signing CA : Yes
Any Purpose : Yes
Any Purpose CA : Yes
OCSP helper : Yes
OCSP helper CA : Yes
Time Stamp signing : No
Time Stamp signing CA : Yes
```

- 「nsCertType = objsign」に修正した場合
```
Certificate purposes:
SSL client : No
SSL client CA : Yes
SSL server : No
SSL server CA : Yes
Netscape SSL server : No
Netscape SSL server CA : Yes
S/MIME signing : No
S/MIME signing CA : Yes
S/MIME encryption : No
S/MIME encryption CA : Yes
CRL signing : Yes
CRL signing CA : Yes
Any Purpose : Yes
Any Purpose CA : Yes
OCSP helper : Yes
OCSP helper CA : Yes
Time Stamp signing : No
Time Stamp signing CA : Yes
```

- 「nsCertType = client, email」に修正した場合
```
Certificate purposes:
SSL client : Yes
SSL client CA : Yes
SSL server : No
SSL server CA : Yes
Netscape SSL server : No
Netscape SSL server CA : Yes
S/MIME signing : Yes
S/MIME signing CA : Yes
S/MIME encryption : Yes
S/MIME encryption CA : Yes
CRL signing : Yes
CRL signing CA : Yes
Any Purpose : Yes
Any Purpose CA : Yes
OCSP helper : Yes
OCSP helper CA : Yes
Time Stamp signing : No
Time Stamp signing CA : Yes
```

- 「sCertType = client, email, objsign」に修正した場合
```
Certificate purposes:
SSL client : Yes
SSL client CA : Yes
SSL server : No
SSL server CA : Yes
Netscape SSL server : No
Netscape SSL server CA : Yes
S/MIME signing : Yes
S/MIME signing CA : Yes
S/MIME encryption : Yes
S/MIME encryption CA : Yes
CRL signing : Yes
CRL signing CA : Yes
Any Purpose : Yes
Any Purpose CA : Yes
OCSP helper : Yes
OCSP helper CA : Yes
Time Stamp signing : No
Time Stamp signing CA : Yes
```

- 参考
  - https://serverfault.com/questions/111625/openssl-x509-purpose-flag-any-purpose-what-is-this

### ベンダーのpurposeを覗いてみる
試しに以下からルート証明書と中間証明書を見てみることにします。
- https://www.cybertrust.ne.jp/sureserver/support/download_ca.html

- ルート証明書の場合
```
$ openssl x509 -in BCTRoot.txt -noout -purpose
Certificate purposes:
SSL client : No
SSL client CA : Yes
SSL server : No
SSL server CA : Yes
Netscape SSL server : No
Netscape SSL server CA : Yes
S/MIME signing : No
S/MIME signing CA : Yes
S/MIME encryption : No
S/MIME encryption CA : Yes
CRL signing : Yes
CRL signing CA : Yes
Any Purpose : Yes
Any Purpose CA : Yes
OCSP helper : Yes
OCSP helper CA : Yes
```

- 中間証明書の場合
```
$ openssl x509 -in PUBCAG3.txt -noout -purpose
Certificate purposes:
SSL client : No
SSL client CA : Yes
SSL server : No
SSL server CA : Yes
Netscape SSL server : No
Netscape SSL server CA : Yes
S/MIME signing : No
S/MIME signing CA : Yes
S/MIME encryption : No
S/MIME encryption CA : Yes
CRL signing : Yes
CRL signing CA : Yes
Any Purpose : Yes
Any Purpose CA : Yes
OCSP helper : Yes
OCSP helper CA : Yes
```
