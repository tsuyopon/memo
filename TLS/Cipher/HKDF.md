# HMAC-based Extract-and-Expand Key Derivation Function (HKDF)
KDF(Key Derivation Function)$B$O80$r9=@.$9$k=i4|CM$r<u$1<h$C$F!"(B1$B$D$J$$$7$OJ#?t$N0E9f3XE*$K6/$$80$r@8@.$9$k$3$H$,$G$-$k;EAH$_$G$9!#(B
HKDF$B$H8F$P$l$k(BKDF$B$N<BAu$N(B1$B$D$,(BRFC5869$B$G5,Dj$5$l$F$$$^$9!#(B

RFC5869$B$NL\E*$H$7$F$O!">-MhE*$J%W%m%H%3%k$d%"%W%j%1!<%7%g%s$G$N0lHLE*$J(BKDF$B$rDj5A$7$F!"J#?t$N(BKDF$B%a%+%K%:%`$,A}?#$5$l$k$3$H$rHr$1$kL\E*$b$"$j$^$9!#(B

HKDF$B$O(Bextract-then-expand$B$NOHAH$_$K=>$C$F=hM}$5$l$^$9!#(B

KDF$B$O$3$N>l9g$K$O!"O@M}E*$K#2$D$N%b%8%e!<%k$+$i9=@.$5$l$^$9!#(B
- Step1(Extract): $BF~NO$H$J$k80$N=i4|CM(B(IKM: Input Keying Material)$B$r<u$1<h$j!"(BIKM$B$+$i8GDjD9$H$J$k(BPRK(PesedoRandom Key)$B$r<hF@$7$^$9!#(B
- Step2(Expand):  Step1$B$G@8@.$7$?(BPRK$B$rJ#?t$N(BPRK$B$X$H3HD%$7$^$9!#(B


Extract$B$O(BIKM$B$NJ,;6%(%s%H%m%T!<$r$h$jC;$$7A$X$HJQ49$9$k!#$7$+$7!"0E9f3XE*$K$O6/$$$H$$$C$?$3$H$rL\E*$H$9$k!#(B
Expand$B$O(BPRK$B$r4uK>$9$kD9$5$N(BPRK$B$X$H3HD%$9$k$3$H$G$9!#(B

# HKDF

### Step1: Extract
```
$B=hM}FbMF(B: HKDF-Extract(salt, IKM)$B$+$i(BPRK$B$X$NJQ49=hM}(B
```

- $B%*%W%7%g%s(B
  - Hash: $B%O%C%7%e4X?t!#(BHashLen$B$O%O%C%7%e4X?t$N=PNO%"%&%H%W%C%H$H$J$k%*%/%F%C%H$ND9$5$rI=$9!#(B
- $BF~NO(B: 
  - salt:
  - IKM:  $BF~NOCM$H$J$k%a%C%;!<%8(B(Input Keying Material)
- $B=PNO(B: 
  - PRK(PesedoRandom Key)
- $B=hM}4X?t(B:
```
PRK = HMAC-Hash(salt, IKM)
```

### Step2: Expand
```
$B=hM}FbMF(B: HKDF-Expand(PRK, info, L) $B$+$i(B OKM(Output Keying Material) $B$X$NJQ49=hM}(B
```

- $B%*%W%7%g%s(B:
  - Hash: $B%O%C%7%e4X?t!#(BHashLen$B$O%O%C%7%e4X?t$N=PNO$N%*%/%F%C%HD9$r<($9(B
- $BF~NO(B:
  - PRK:  $B>/$J$/$H$b(BHashLen$B%*%/%F%C%HD9$N(BPRK
  - info: $B%*%W%7%g%J%k$J%3%s%F%-%9%H$d%"%W%j%1!<%7%g%sFCM-$N>pJs(B
  - L:    $B%*%/%F%C%HD9$G$N(BOKM$B$ND9$5(B (<= 255*HashLen)
- $B=PNO(B:
  - L$B%*%/%F%C%H$N(BOKM
- $B=hM}4X?t(B:
  - $B<!$N$h$&$K7W;;$5$l$^$9!#(B|$B$O7k9g$rI=$9!#(B
```
   N = ceil(L/HashLen)
   T = T(1) | T(2) | T(3) | ... | T(N)
   OKM = first L octets of T

   where:
   T(0) = empty string (zero length)
   T(1) = HMAC-Hash(PRK, T(0) | info | 0x01)
   T(2) = HMAC-Hash(PRK, T(1) | info | 0x02)
   T(3) = HMAC-Hash(PRK, T(2) | info | 0x03)
   ...
```


### $B%5%s%W%k(B
$B0J2<$N%1!<%9$r;n$7$F$_$k(B
- https://tools.ietf.org/html/rfc5869#appendix-A.1


$B%W%m%0%i%`$O<!$NFbMF$G$"$k!#(Btestvector$B$O0J2<$K5-:\$5$l$F$$$k!#(B
```
#!/usr/bin/env python3
import hashlib
import binascii
import hmac
from math import ceil
from binascii import hexlify, unhexlify

# SHA256 = $B%O%C%7%e$ND9$5(B32byte
hash_len = 32

def hmac_sha256(key, data):
    return hmac.new(key, data, hashlib.sha256).digest()

# ikm = input key material
def hkdf(length, ikm, salt, info):
    prk = hmac_sha256(salt, ikm)
    print (hexlify(prk))
    t = b"" 
    okm = b"" 
    for i in range(ceil(length / hash_len)):
        t = hmac_sha256(prk, t + info + bytes([1+i]))
        okm += t
    return okm[:length]


ikm  = unhexlify("0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b")
salt = unhexlify("000102030405060708090a0b0c")
info = unhexlify("f0f1f2f3f4f5f6f7f8f9")
L = 42

print (hexlify(hkdf(L, ikm, salt, info)))
```

$B<B9T$7$F$_$k!##19TL\$,(BPRK$B$G!"(B2$B9TL\$,(BOKM$B$G$"$k!#(B
```
$ ./hkdf.py 
b'077709362c2e32df0ddc3f0dc47bba6390b6c73bb50f9c3122ec844ad7c2b3e5'
b'3cb25f25faacd57a90434f64d0362f2a2d2d0a90cf1a5a4c5db02d56ecc4c5bf34007208d5b887185865'
```


# $B;29M(BURL
- wikipedia: HKDF
  - https://en.wikipedia.org/wiki/HKDF
- Openssl: hkdf.c
  - https://github.com/openssl/openssl/blob/master/crypto/kdf/hkdf.c


# SeeAlso
- RFC5869: HMAC-based Extract-and-Expand Key Derivation Function (HKDF)
  - https://tools.ietf.org/html/rfc5869
