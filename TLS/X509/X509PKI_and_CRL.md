# 概要
RFC5280についてまとめています。
このRFCはX509v3とX590v2のインターネット利用についてまとめています。

このRFCは非常にボリューム量が多いので骨格がわかるように全体像を述べておきます。

- section1: 各セクションの特徴について述べています。introductionです。
- section2: Internet PKIへのrequirementとこのドキュメントの範囲について規定しています。
- section3: アーキテクチャモデルとIETFやISO/IEC/ITU-T標準との関係性について述べています。
- section4: X509v3証明書について説明しています
- section5: X509v2証明書について説明しています
- section6: 証明書のパス検証手順について説明しています。これらの手順はISO/IEC/ITU-Tの定義に基づいています。
- section7: 国際名称のための発展的なサポートについて述べられています。


# 概略

### section2

WWW, 電子メール, ユーザ認証, IPSecを含むようなインターネットアプリケーションでX509を最大限に利用しその促進を促すようにすることがこの仕様書の目的である。


# 参考URL
- https://tools.ietf.org/html/rfc5280


# メモ
OIDの定義はX.660で確認することができます。
- https://itu.int/itu-t/recommendations/rec.aspx?rec=X.660

定義によると
```
3.5.11 object identifier: An ordered list of primary integer values from the root of the international object identifier tree to a node, which unambiguously identifies that node (see 7.8). 
```

# ASN.1サンプル
```
$ ./dumpasn1 -dial cert.der  
   0 3961: SEQUENCE {
   4 3681: . SEQUENCE {
   8    3: . . [0] {
  10    1: . . . INTEGER 2
         : . . . }
  13   20: . . INTEGER 0E C2 F2 8A 08 6A FF 40 F6 25 79 36 A6 4C C4 37 E4 4D 28 AC
  35   13: . . SEQUENCE {
  37    9: . . . OBJECT IDENTIFIER
         : . . . . sha256WithRSAEncryption (1 2 840 113549 1 1 11)
         : . . . . (PKCS #1)
  48    0: . . . NULL
         : . . . }
  50   90: . . SEQUENCE {
  52   11: . . . SET {
  54    9: . . . . SEQUENCE {
  56    3: . . . . . OBJECT IDENTIFIER countryName (2 5 4 6)
         : . . . . . . (X.520 DN component)
  61    2: . . . . . PrintableString 'JP'
         : . . . . . }
         : . . . . }
  65   35: . . . SET {
  67   33: . . . . SEQUENCE {
  69    3: . . . . . OBJECT IDENTIFIER organizationName (2 5 4 10)
         : . . . . . . (X.520 DN component)
  74   26: . . . . . PrintableString 'Cybertrust Japan Co., Ltd.'
         : . . . . . }
         : . . . . }
 102   38: . . . SET {
 104   36: . . . . SEQUENCE {
 106    3: . . . . . OBJECT IDENTIFIER commonName (2 5 4 3)
         : . . . . . . (X.520 DN component)
 111   29: . . . . . PrintableString 'Cybertrust Japan Public CA G3'
         : . . . . . }
         : . . . . }
         : . . . }
 142   30: . . SEQUENCE {
 144   13: . . . UTCTime 24/09/2019 07:01:27 GMT
 159   13: . . . UTCTime 23/10/2020 14:59:00 GMT
         : . . . }
 174  132: . . SEQUENCE {
 177   11: . . . SET {
 179    9: . . . . SEQUENCE {
 181    3: . . . . . OBJECT IDENTIFIER countryName (2 5 4 6)
         : . . . . . . (X.520 DN component)
 186    2: . . . . . PrintableString 'JP'
         : . . . . . }
         : . . . . }
 190   14: . . . SET {
 192   12: . . . . SEQUENCE {
 194    3: . . . . . OBJECT IDENTIFIER stateOrProvinceName (2 5 4 8)
         : . . . . . . (X.520 DN component)
 199    5: . . . . . PrintableString 'Tokyo'
         : . . . . . }
         : . . . . }
 206   19: . . . SET {
 208   17: . . . . SEQUENCE {
 210    3: . . . . . OBJECT IDENTIFIER localityName (2 5 4 7)
         : . . . . . . (X.520 DN component)
 215   10: . . . . . PrintableString 'Chiyoda-ku'
         : . . . . . }
         : . . . . }
 227   32: . . . SET {
 229   30: . . . . SEQUENCE {
 231    3: . . . . . OBJECT IDENTIFIER organizationName (2 5 4 10)
         : . . . . . . (X.520 DN component)
 236   23: . . . . . PrintableString 'Yahoo Japan Corporation'
         : . . . . . }
         : . . . . }
 261   22: . . . SET {
 263   20: . . . . SEQUENCE {
 265    3: . . . . . OBJECT IDENTIFIER organizationalUnitName (2 5 4 11)
         : . . . . . . (X.520 DN component)
 270   13: . . . . . UTF8String 'EDGE_20190924'
         : . . . . . }
         : . . . . }
 285   22: . . . SET {
 287   20: . . . . SEQUENCE {
 289    3: . . . . . OBJECT IDENTIFIER commonName (2 5 4 3)
         : . . . . . . (X.520 DN component)
 294   13: . . . . . UTF8String '*.yahoo.co.jp'
         : . . . . . }
         : . . . . }
         : . . . }
 309  290: . . SEQUENCE {
 313   13: . . . SEQUENCE {
 315    9: . . . . OBJECT IDENTIFIER rsaEncryption (1 2 840 113549 1 1 1)
         : . . . . . (PKCS #1)
 326    0: . . . . NULL
         : . . . . }
 328  271: . . . BIT STRING, encapsulates {
 333  266: . . . . SEQUENCE {
 337  257: . . . . . INTEGER
         : . . . . . . 00 C0 91 A4 9B 67 F1 4D 1F 2D F2 09 A6 C8 99 9A
         : . . . . . . 0D 77 FF FC 57 29 C0 03 F6 78 A9 17 EB 59 EB 33
         : . . . . . . A7 05 9B AD 82 29 49 7C C1 3A C7 16 2C 56 54 5F
         : . . . . . . 94 6C 9C 94 A7 9D 60 E1 B1 45 47 01 EF 1F FF AB
         : . . . . . . 8D 4D DC 28 8D CF 00 4E 42 33 5C BB 4C E6 EF 42
         : . . . . . . EB E8 9C 34 FC 2A E4 8E DC E9 47 44 E6 F2 08 ED
         : . . . . . . 06 AB 99 D1 9A DD 43 91 69 70 D6 C0 E1 08 6C 7F
         : . . . . . . A1 30 27 5C 10 AD 66 D4 C6 00 36 24 7C 3C 4C 69
         : . . . . . . A6 C2 0D 5C 46 A6 C5 DB CA 8F CC E2 64 DC 56 B3
         : . . . . . . 4C EE 8D 41 8A 50 51 ED 25 AF DA 29 9B 4F 52 00
         : . . . . . . 7A 92 BE 10 77 A6 53 11 E4 D5 3B C0 F0 06 85 6E
         : . . . . . . 0E 4B 1B B2 1F 9D C2 BE 47 7C C9 A0 AB FC 54 F9
         : . . . . . . B5 8C 59 05 CE 25 03 4E 40 DB 86 4F 4B DE 64 55
         : . . . . . . A9 30 7B 30 B8 C2 D1 EF 79 C8 DC AD C7 39 7A B2
         : . . . . . . 08 71 B4 54 8D 82 E9 D1 1E 98 E5 B7 DF 4C AB E0
         : . . . . . . 68 9F EC D0 A3 F2 61 5E 74 CD 91 A7 8A 7E 5E D3
         : . . . . . . 41
 598    3: . . . . . INTEGER 65537
         : . . . . . }
         : . . . . }
         : . . . }
 603 3082: . . [3] {
 607 3078: . . . SEQUENCE {
 611   12: . . . . SEQUENCE {
 613    3: . . . . . OBJECT IDENTIFIER basicConstraints (2 5 29 19)
         : . . . . . . (X.509 extension)
 618    1: . . . . . BOOLEAN TRUE
 621    2: . . . . . OCTET STRING, encapsulates {
 623    0: . . . . . . SEQUENCE {}
         : . . . . . . }
         : . . . . . }
 625  101: . . . . SEQUENCE {
 627    3: . . . . . OBJECT IDENTIFIER certificatePolicies (2 5 29 32)
         : . . . . . . (X.509 extension)
 632   94: . . . . . OCTET STRING, encapsulates {
 634   92: . . . . . . SEQUENCE {
 636   80: . . . . . . . SEQUENCE {
 638    8: . . . . . . . . OBJECT IDENTIFIER '1 2 392 200081 1 1'
 648   68: . . . . . . . . SEQUENCE {
 650   66: . . . . . . . . . SEQUENCE {
 652    8: . . . . . . . . . . OBJECT IDENTIFIER cps (1 3 6 1 5 5 7 2 1)
         : . . . . . . . . . . . (PKIX policy qualifier)
 662   54: . . . . . . . . . . IA5String
         : . . . . . . . . . 'https://www.cybertrust.ne.jp/ssl/repository/inde'
         : . . . . . . . . . 'x.html'
         : . . . . . . . . . . }
         : . . . . . . . . . }
         : . . . . . . . . }
 718    8: . . . . . . . SEQUENCE {
 720    6: . . . . . . . . OBJECT IDENTIFIER '2 23 140 1 2 2'
         : . . . . . . . . }
         : . . . . . . . }
         : . . . . . . }
         : . . . . . }
 728 2085: . . . . SEQUENCE {
 732    3: . . . . . OBJECT IDENTIFIER subjectAltName (2 5 29 17)
         : . . . . . . (X.509 extension)
 737 2076: . . . . . OCTET STRING, encapsulates {
 741 2072: . . . . . . SEQUENCE {
 745   13: . . . . . . . [2] '*.yahoo.co.jp'
 760   17: . . . . . . . [2] '*.ane.yahoo.co.jp'
 779   22: . . . . . . . [2] '*.auctions.yahoo.co.jp'
 803   11: . . . . . . . [2] '*.c.yimg.jp'
 816   24: . . . . . . . [2] '*.chiebukuro.yahoo.co.jp'
 842   21: . . . . . . . [2] '*.clorder.yahoo.co.jp'
 865   28: . . . . . . . [2] '*.east.edge.storage-yahoo.jp'
 895   31: . . . . . . . [2] '*.east.edge.storage-yahoobox.jp'
 928   23: . . . . . . . [2] '*.edge.storage-yahoo.jp'
 953   21: . . . . . . . [2] '*.finance.yahoo.co.jp'
 976   30: . . . . . . . [2] '*.global.edge.storage-yahoo.jp'
1008   21: . . . . . . . [2] '*.listing.yahoo.co.jp'
1031   18: . . . . . . . [2] '*.news.yahoo.co.jp'
1051   19: . . . . . . . [2] '*.order.yahoo.co.jp'
1072   20: . . . . . . . [2] '*.shopping.c.yimg.jp'
1094   22: . . . . . . . [2] '*.shopping.yahoo.co.jp'
1118   19: . . . . . . . [2] '*.store.yahoo.co.jp'
1139   20: . . . . . . . [2] '*.travel.yahoo.co.jp'
1161   28: . . . . . . . [2] '*.west.edge.storage-yahoo.jp'
1191   31: . . . . . . . [2] '*.west.edge.storage-yahoobox.jp'
1224   25: . . . . . . . [2] '*.xml.listing.yahoo.co.jp'
1251   15: . . . . . . . [2] '*.yahoo-labs.jp'
1268   14: . . . . . . . [2] '*.yahooapis.jp'
1284   13: . . . . . . . [2] '*.yahoobox.jp'
1299    9: . . . . . . . [2] '*.yimg.jp'
1310   10: . . . . . . . [2] '*.yjtag.jp'
1322   19: . . . . . . . [2] '*.yjtag.yahoo.co.jp'
1343   20: . . . . . . . [2] '*.ys-insurance.co.jp'
1365   23: . . . . . . . [2] 'hrm.grmtrez.yahoo.co.jp'
1390   27: . . . . . . . [2] 'api.stg.clorder.yahoo.co.jp'
1419   28: . . . . . . . [2] 'api.stg2.clorder.yahoo.co.jp'
1449   25: . . . . . . . [2] 'api.y.clorder.yahoo.co.jp'
1476   20: . . . . . . . [2] 'app.commerce21.co.jp'
1498   21: . . . . . . . [2] 'app.news.yahooapis.jp'
1521   20: . . . . . . . [2] 'arc.help.yahoo.co.jp'
1543   26: . . . . . . . [2] 'assist.search.yahooapis.jp'
1571   25: . . . . . . . [2] 'auth.carnavi.yahooapis.jp'
1598   25: . . . . . . . [2] 'biz.marketing.yahoo.co.jp'
1625    9: . . . . . . . [2] 'bspace.jp'
1636   24: . . . . . . . [2] 'cgi2.r-agent.yahoo.co.jp'
1662   23: . . . . . . . [2] 'cksync.pdsp.yahoo.co.jp'
1687   20: . . . . . . . [2] 'cm.froma.yahoo.co.jp'
1709   27: . . . . . . . [2] 'compass.ymobile.yahoo.co.jp'
1738   25: . . . . . . . [2] 'custom.search.yahoo.co.jp'
1765   23: . . . . . . . [2] 'e.developer.yahoo.co.jp'
1790   32: . . . . . . . [2] 'feedback.advertising.yahoo.co.jp'
1824   29: . . . . . . . [2] 'feedback.premiads.yahoo.co.jp'
1855   35: . . . . . . . [2] 'feedback.promotionalads.yahoo.co.jp'
1892   26: . . . . . . . [2] 'forms.business.yahoo.co.jp'
1920   23: . . . . . . . [2] 'frame.games.yahoo.co.jp'
1945   26: . . . . . . . [2] 'help.marketing.yahoo.co.jp'
1973   19: . . . . . . . [2] 'add.dir.yahoo.co.jp'
1994   17: . . . . . . . [2] 'im.ov.yahoo.co.jp'
2013   25: . . . . . . . [2] 'info.hatalike.yahoo.co.jp'
2040   23: . . . . . . . [2] 'lyrics.gyao.yahoo.co.jp'
2065   18: . . . . . . . [2] 'm.gyao.yahoo.co.jp'
2085   15: . . . . . . . [2] 'm.yahoo-help.jp'
2102   26: . . . . . . . [2] 'movie.chocotle.yahoo.co.jp'
2130   27: . . . . . . . [2] 'online.security.yahoo.co.jp'
2159   32: . . . . . . . [2] 'opetool.bylines.news.yahoo.co.jp'
2193   29: . . . . . . . [2] 'personalapp.news.yahooapis.jp'
2224   23: . . . . . . . [2] 'pf.carnavi.yahooapis.jp'
2249   23: . . . . . . . [2] 'poiedit.map.yahoo.co.jp'
2274   33: . . . . . . . [2] 'portal.yadui.business.yahoo.co.jp'
2309   23: . . . . . . . [2] 'rf.carnavi.yahooapis.jp'
2334   31: . . . . . . . [2] 'sandbox.frame.games.yahoo.co.jp'
2367   21: . . . . . . . [2] 'shopping.geocities.jp'
2390   36: . . . . . . . [2] 'ssl-tools.kainavi.search.yahoo.co.jp'
2428   24: . . . . . . . [2] 'ssl.api.olp.yahooapis.jp'
2454   19: . . . . . . . [2] 'ssl.map.srv.yimg.jp'
2475   25: . . . . . . . [2] 'stg-shopping.geocities.jp'
2502   21: . . . . . . . [2] 'sub.push.yahooapis.jp'
2525   30: . . . . . . . [2] 'subscription.push.yahooapis.jp'
2557   29: . . . . . . . [2] 'suggest.auctions.yahooapis.jp'
2588   27: . . . . . . . [2] 'suggest.search.yahooapis.jp'
2617   29: . . . . . . . [2] 'tool.bylines.news.yahoo.co.jp'
2648   25: . . . . . . . [2] 'vics.carnavi.yahooapis.jp'
2675   17: . . . . . . . [2] 'www.richlab.co.jp'
2694   18: . . . . . . . [2] 'www.techbasevn.com'
2714   17: . . . . . . . [2] 'www.yahoo-help.jp'
2733   16: . . . . . . . [2] 'www.yjcard.co.jp'
2751   23: . . . . . . . [2] 'xml.listing.yahoo.co.jp'
2776   11: . . . . . . . [2] 'yahoo.co.jp'
2789   26: . . . . . . . [2] 'yoshimoto.gyao.yahoo.co.jp'
         : . . . . . . . }
         : . . . . . . }
         : . . . . . }
2817  165: . . . . SEQUENCE {
2820    8: . . . . . OBJECT IDENTIFIER authorityInfoAccess (1 3 6 1 5 5 7 1 1)
         : . . . . . . (PKIX private extension)
2830  152: . . . . . OCTET STRING, encapsulates {
2833  149: . . . . . . SEQUENCE {
2836   51: . . . . . . . SEQUENCE {
2838    8: . . . . . . . . OBJECT IDENTIFIER ocsp (1 3 6 1 5 5 7 48 1)
         : . . . . . . . . . (PKIX)
2848   39: . . . . . . . . [6] 'http://ocsp.cybertrust.ne.jp/OcspServer'
         : . . . . . . . . }
2889   94: . . . . . . . SEQUENCE {
2891    8: . . . . . . . . OBJECT IDENTIFIER caIssuers (1 3 6 1 5 5 7 48 2)
         : . . . . . . . . . (PKIX subject/authority info access descriptor)
2901   82: . . . . . . . . [6]
         : . . . . . . . . . 'http://sureseries-crl.cybertrust.ne.jp/SureServe'
         : . . . . . . . . . 'r/ctjpubcag3/ctjpubcag3_sha256.crt'
         : . . . . . . . . }
         : . . . . . . . }
         : . . . . . . }
         : . . . . . }
2985   14: . . . . SEQUENCE {
2987    3: . . . . . OBJECT IDENTIFIER keyUsage (2 5 29 15)
         : . . . . . . (X.509 extension)
2992    1: . . . . . BOOLEAN TRUE
2995    4: . . . . . OCTET STRING, encapsulates {
2997    2: . . . . . . BIT STRING 5 unused bits
         : . . . . . . . '101'B
         : . . . . . . }
         : . . . . . }
3001   29: . . . . SEQUENCE {
3003    3: . . . . . OBJECT IDENTIFIER extKeyUsage (2 5 29 37)
         : . . . . . . (X.509 extension)
3008   22: . . . . . OCTET STRING, encapsulates {
3010   20: . . . . . . SEQUENCE {
3012    8: . . . . . . . OBJECT IDENTIFIER serverAuth (1 3 6 1 5 5 7 3 1)
         : . . . . . . . . (PKIX key purpose)
3022    8: . . . . . . . OBJECT IDENTIFIER clientAuth (1 3 6 1 5 5 7 3 2)
         : . . . . . . . . (PKIX key purpose)
         : . . . . . . . }
         : . . . . . . }
         : . . . . . }
3032   31: . . . . SEQUENCE {
3034    3: . . . . . OBJECT IDENTIFIER authorityKeyIdentifier (2 5 29 35)
         : . . . . . . (X.509 extension)
3039   24: . . . . . OCTET STRING, encapsulates {
3041   22: . . . . . . SEQUENCE {
3043   20: . . . . . . . [0]
         : . . . . . . . . 73 A8 08 53 29 B8 15 FB 99 80 E5 C5 37 D8 F8 39
         : . . . . . . . . 7B A4 13 06
         : . . . . . . . }
         : . . . . . . }
         : . . . . . }
3065   85: . . . . SEQUENCE {
3067    3: . . . . . OBJECT IDENTIFIER cRLDistributionPoints (2 5 29 31)
         : . . . . . . (X.509 extension)
3072   78: . . . . . OCTET STRING, encapsulates {
3074   76: . . . . . . SEQUENCE {
3076   74: . . . . . . . SEQUENCE {
3078   72: . . . . . . . . [0] {
3080   70: . . . . . . . . . [0] {
3082   68: . . . . . . . . . . [6]
         : . . . . . . . . . 'http://sureseries-crl.cybertrust.ne.jp/SureServe'
         : . . . . . . . . . 'r/ctjpubcag3/cdp.crl'
         : . . . . . . . . . . }
         : . . . . . . . . . }
         : . . . . . . . . }
         : . . . . . . . }
         : . . . . . . }
         : . . . . . }
3152   29: . . . . SEQUENCE {
3154    3: . . . . . OBJECT IDENTIFIER subjectKeyIdentifier (2 5 29 14)
         : . . . . . . (X.509 extension)
3159   22: . . . . . OCTET STRING, encapsulates {
3161   20: . . . . . . OCTET STRING
         : . . . . . . . FB F6 21 82 4E 59 45 73 91 B4 76 EE 53 57 9B 9E
         : . . . . . . . 75 F9 29 7E
         : . . . . . . }
         : . . . . . }
3183  502: . . . . SEQUENCE {
3187   10: . . . . . OBJECT IDENTIFIER '1 3 6 1 4 1 11129 2 4 2'
3199  486: . . . . . OCTET STRING, encapsulates {
3203  482: . . . . . . OCTET STRING
         : . . . . . . . 01 E0 00 76 00 A4 B9 09 90 B4 18 58 14 87 BB 13
         : . . . . . . . A2 CC 67 70 0A 3C 35 98 04 F9 1B DF B8 E3 77 CD
         : . . . . . . . 0E C8 0D DC 10 00 00 01 6D 62 6D EF 69 00 00 04
         : . . . . . . . 03 00 47 30 45 02 21 00 C1 D7 AE F2 9E 8A 51 33
         : . . . . . . . 53 BD 8A 4B 2A E3 80 7C 84 DA A5 D7 8F 6D 06 D3
         : . . . . . . . CA 24 95 3E 0F 49 A2 73 02 20 2A B1 AA 57 28 ED
         : . . . . . . . 2B A9 3F C3 10 B8 63 C5 23 8B 12 05 FE 3A 63 E6
         : . . . . . . . 28 4C 6F 84 83 58 79 E3 D4 47 00 77 00 EE 4B BD
         : . . . . . . . B7 75 CE 60 BA E1 42 69 1F AB E1 9E 66 A3 0F 7E
         : . . . . . . . 5F B0 72 D8 83 00 C4 7B 89 7A A8 FD CB 00 00 01
         : . . . . . . . 6D 62 6D FB 47 00 00 04 03 00 48 30 46 02 21 00
         : . . . . . . . C6 AE 5A 22 59 21 30 E2 05 F7 3B D3 CC 44 FE 8D
         : . . . . . . . 2E 6D 73 31 B5 4D E7 53 96 84 6D 56 CA EB E3 B4
         : . . . . . . . 02 21 00 C6 59 F6 8E F5 6A 3B 5E FE EB 61 24 12
         : . . . . . . . 8B 9D E1 94 25 04 51 51 2F 83 99 C5 0F CC A4 9F
         : . . . . . . . 16 03 DB 00 76 00 BB D9 DF BC 1F 8A 71 B5 93 94
         : . . . . . . . 23 97 AA 92 7B 47 38 57 95 0A AB 52 E8 1A 90 96
         : . . . . . . . 64 36 8E 1E D1 85 00 00 01 6D 62 6E 05 7A 00 00
         : . . . . . . . 04 03 00 47 30 45 02 20 62 38 45 39 44 D5 9E F7
         : . . . . . . . 44 A8 07 DC 99 62 01 DD 58 B7 43 7C D1 B4 C8 16
         : . . . . . . . 37 F4 69 42 08 FF 1C F1 02 21 00 99 A9 84 BD DE
         : . . . . . . . 3A 34 CE D5 0A 5D 46 57 C7 31 4B 8A 4C 56 F9 B1
         : . . . . . . . 8C DF 50 62 10 3D D9 AE C7 63 EB 00 75 00 56 14
         : . . . . . . . 06 9A 2F D7 C2 EC D3 F5 E1 BD 44 B2 3E C7 46 76
         : . . . . . . . B9 BC 99 11 5C C0 EF 94 98 55 D6 89 D0 DD 00 00
         : . . . . . . . 01 6D 62 6E 10 30 00 00 04 03 00 46 30 44 02 20
         : . . . . . . . 6C DE 29 73 95 78 FF 6D 53 65 EE 18 CA 45 9C 88
         : . . . . . . . AA BC 1B 48 03 0C 44 52 6D 74 AB A0 46 01 54 9A
         : . . . . . . . 02 20 4D 94 55 DA 5C 31 69 8C 46 3F 4A 03 92 8A
         : . . . . . . . C2 E3 D1 5F 2E 6C FB 56 84 8A 8D 78 69 44 FA 19
         : . . . . . . . 56 D9
         : . . . . . . }
         : . . . . . }
         : . . . . }
         : . . . }
         : . . }
3689   13: . SEQUENCE {
3691    9: . . OBJECT IDENTIFIER sha256WithRSAEncryption (1 2 840 113549 1 1 11)
         : . . . (PKCS #1)
3702    0: . . NULL
         : . . }
3704  257: . BIT STRING
         : . . 02 C9 D5 B7 10 CA 92 8F 57 33 69 99 8A BD 34 24
         : . . D0 65 E2 C7 5C F7 DC B4 BD 67 6A 84 33 27 A2 29
         : . . B6 56 93 B5 FF E8 2A B4 D3 1D EB AF DC F5 1D 39
         : . . 6F FF D3 69 14 F3 1E A2 C1 AE A1 B2 36 F8 46 B5
         : . . 64 52 C8 4C 74 10 0C 2D 07 CF 88 29 01 8A AE A5
         : . . F0 BA 68 C6 33 43 37 CA 19 BE 9D A5 92 86 D6 6B
         : . . E4 61 D4 B3 28 87 24 A6 DC 5F CA CE E5 1C 8D 8A
         : . . BE A4 8E E5 B3 0D 01 69 82 5C BD 9A 95 0D B7 B8
         : . . 80 A6 60 B5 D8 4B DF 81 16 A4 EF 30 9C 3E 58 0B
         : . . 8E 90 BF 91 AC 03 93 02 20 6C 5D 86 96 F0 EE 92
         : . . 70 22 23 B4 BC 5E D4 0C 5A D7 CF DA FC 7E 53 41
         : . . 1B 53 9C C8 65 97 81 3A 47 A2 DC 7D F4 2A 1F E0
         : . . 4A CF 36 19 65 B6 EA A6 CA 54 85 E1 98 02 E8 DE
         : . . 15 5A 2C 9B 52 20 67 92 B5 7B FA 82 4E CB 0D 38
         : . . BA 0E 78 6D 8D 98 73 F5 8B C7 D6 13 96 4E 15 23
         : . . D1 2D 6C 75 12 03 37 60 F0 A6 61 08 E5 51 2E 0A
         : . }

0 warnings, 0 errors.
```

# 参考

- https://www.ipa.go.jp/security/pki/033.html
