# AEAD or AE
$BG'>ZIU$-0E9f(B(AE: Authentiated Encryption or AEAD: Authenticated Encryption with Associated Data)$B$O!"<!$N#3$D$rF1;~$KDs6!$9$k0E9f%b!<%I$G$9!#(B
- $B%G!<%?$NHkF?@-(B
- $B40A4@-(B
- $BG'>Z@-(B

$B<!$N(B6$B<oN`$N0[$J$k%b!<%I$,B8:_$9$k!#(B
- CCM
- GCM
- Encrypt Then MAC
- EAX
- Key Wrap
- OCB2.0

Ciphersuite$B$rI=$9J8;zNs:G8e$NMWAG(BSHA256, SHA384$B$O!"(BPRF$B$N%O%C%7%e4X?t$r(BSHA256, SHA384$B$KCV$-49$($k$H0J2<$G5,Dj$7$F$$$^$9!#(B
- https://tools.ietf.org/html/rfc5288#section-3

- TODO: CHACHA20-POLY1305$B$O5,Dj$5$l$F$$$J$$(B?

# AEAD Algorthms
RFC5116$B$G$O<!$N#4$D$N(BAEAD$B%"%k%4%j%:%`$,5,Dj$5$l$F$$$^$9!#(B
GCM$B$b(BCCM$B$b$I$A$i$b(B128bit
- AES GCM
  - 1. AEAD_AES_128_GCM
  - 2. AEAD_AES_256_GCM
- AES CCM
  - 3. AEAD_AES_128_CCM
  - 4. AEAD_AES_256_CCM

### 1. AEAD_AES_128_GCM

AEAD_AES_128_GCM$B$O(BAE$B%"%k%4%j%:%`$O(BGCM$B$,F/$-!"%V%m%C%/0E9f$H$7$F(BAES-128$B$rMxMQ$5$l$k!#(B
key, nonce, plaintext, associated data$B$N#4$D$N>pJs$rEO$9$3$H$K$h$C$FDs6!$5$l$k!#(B

$BG'>Z%?%0$O(B16$B%*%/%F%C%H(B(128bit)$B$,MxMQ$5$l$k!#(B
AEAD_AES_128_GCM $B$N(Bciphertext$B$O!"(BGCM$B0E9fA`:n$H$7$F@8@.$5$l$?G'>Z%?%0$rIUM?$9$k$3$H$G7A@.$5$l$^$9!#(B

$B0J2<$K%F%9%H%1!<%9$,Ds6!$5$l$F$$$^$9!#(B
- https://tools.ietf.org/html/rfc5116#ref-GCM

$BF~NO$H=PNO$ND9$5$O<!$N$h$&$K$J$j$^$9!#(B
- K_LEN is 16 octets,
- P_MAX is 2^36 - 31 octets,
- A_MAX is 2^61 - 1 octets,
- N_MIN and N_MAX are both 12 octets, and
- C_MAX is 2^36 - 15 octets.

AEAD_AES_128_GCM$B$N(Bciphertext$B$O$-$C$A$j(B16byte$BD9$G$"$k!#(B

### 2. AEAD_AES_256_GCM
AEAD_AES_128_GCM$B$H$[$H$s$IF1$8$@$,<!$NE@$G0[$J$k!#(B
- K_LEN is 32 octets, instead of 16 octets, and
- AES-256 GCM is used instead of AES-128 GCM.

### 3. AEAD_AES_128_CCM
AEAD_AES_128_GCM$B$O(BAE$B%"%k%4%j%:%`$O(BCCM$B$,F/$-!"%V%m%C%/0E9f$H$7$F(BAES-128$B$rMxMQ$5$l$k!#(B
key, nonce, associated data, plaintext$B$rF~NOCM$H$7$FEO$7$^$9!#(B

$BG'>Z%?%0$H$7$F$O(B16$B%*%/%F%C%HD9(B(128bit)$B$,MxMQ$5$l$^$9!#(B
AEAD_AES_128_CCM  ciphertext$B$O(BCCM$B0E9fA`:n$H$7$F@8@.$5$l$?G'>Z%?%0$rIUM?$9$k$3$H$G7A@.$5$l$^$9!#(B

$B0J2<$K%F%9%H%1!<%9$,Ds6!$5$l$F$$$k!#(B
- https://tools.ietf.org/html/rfc5116#ref-CCM

$BF~NO$d=PNO$ND9$5$O<!$N$H$*$j$G$9!#(B
- K_LEN is 16 octets,
- P_MAX is 2^24 - 1 octets,
- A_MAX is 2^64 - 1 octets,
- N_MIN and N_MAX are both 12 octets, and
- C_MAX is 2^24 + 15 octets.


### 4. AEAD_AES_256_CCM
AEAD_AES_128_CCM$B$H$[$H$s$IF1$8$@$,<!$NE@$G0[$J$k!#(B
- K_LEN is 32 octets, instead of 16, and
- AES-256 CCM is used instead of AES-128 CCM.

# TLS1.2$B$H(BTLS1.3$B$N0c$$(B


- TLS1.2$BL$K~(B
  - $B8E$$%P!<%8%g%s$N(BTLS$B$G$O%/%i%$%"%s%H$O(BAEAD cipher$B$O;XDj$7$F$O$J$i$:!"$^$?%5!<%PB&$b(BAEAD cipher$B$r<u$1IU$1$F$O$J$i$J$$(B(MUST NOT)
  - $B%/%i%$%"%s%H$O(BTLS$B%P!<%8%g%s$r%A%'%C%/$7$F!"ITE,@Z$J%P!<%8%g%s$G$"$l$P(Billegal_parameter$B$N(Bfatal$B%"%i!<%H$rAw$i$J$1$l$P$J$i$J$$(B(MUST)
  - TLS1.2 (RFC5288$B$h$jH4?h(B) $B$N(BAEAD CipherSuite
```
CipherSuite TLS_RSA_WITH_AES_128_GCM_SHA256 = {0x00,0x9C}
CipherSuite TLS_RSA_WITH_AES_256_GCM_SHA384 = {0x00,0x9D}
CipherSuite TLS_DHE_RSA_WITH_AES_128_GCM_SHA256 = {0x00,0x9E}
CipherSuite TLS_DHE_RSA_WITH_AES_256_GCM_SHA384 = {0x00,0x9F}
CipherSuite TLS_DH_RSA_WITH_AES_128_GCM_SHA256 = {0x00,0xA0}
CipherSuite TLS_DH_RSA_WITH_AES_256_GCM_SHA384 = {0x00,0xA1}
CipherSuite TLS_DHE_DSS_WITH_AES_128_GCM_SHA256 = {0x00,0xA2}
CipherSuite TLS_DHE_DSS_WITH_AES_256_GCM_SHA384 = {0x00,0xA3}
CipherSuite TLS_DH_DSS_WITH_AES_128_GCM_SHA256 = {0x00,0xA4}
CipherSuite TLS_DH_DSS_WITH_AES_256_GCM_SHA384 = {0x00,0xA5}
CipherSuite TLS_DH_anon_WITH_AES_128_GCM_SHA256 = {0x00,0xA6}
CipherSuite TLS_DH_anon_WITH_AES_256_GCM_SHA384 = {0x00,0xA7}
```
  - CCM$B$bDI2C$9$k(B
- TLS1.3 (RFC8446$B$h$jH4?h(B)
```
+------------------------------+-------------+
| Description                  | Value       |
+------------------------------+-------------+
| TLS_AES_128_GCM_SHA256       | {0x13,0x01} |
|                              |             |
| TLS_AES_256_GCM_SHA384       | {0x13,0x02} |
|                              |             |
| TLS_CHACHA20_POLY1305_SHA256 | {0x13,0x03} |
|                              |             |
| TLS_AES_128_CCM_SHA256       | {0x13,0x04} |
|                              |             |
| TLS_AES_128_CCM_8_SHA256     | {0x13,0x05} |
+------------------------------+-------------+
```

# $B;29M%j%s%/(B
- $B$"$I$1$J$$OC(B: TLS 1.3 $B3+H/F|5-(B $B$=$N(B17 AEAD
  - https://kazu-yamamoto.hatenablog.jp/entry/20170426/1493186127

# SeeAlso
- RFC5116: An Interface and Algorithms for Authenticated Encryption
  - https://tools.ietf.org/html/rfc5116
- RFC5288: AES Galois Counter Mode (GCM) Cipher Suites for TLS
  - https://tools.ietf.org/html/rfc5288
- NIST: Recommendation for Block Cipher Modes of Operation: Galois/Counter Mode (GCM) and GMAC
  - https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38d.pdf

