# HMAC-based Extract-and-Expand Key Derivation Function (HKDF)
KDF(Key Derivation Function)は鍵を構成する初期値を受け取って、1つないしは複数の暗号学的に強い鍵を生成することができる仕組みです。
HKDFと呼ばれるKDFの実装の1つがRFC5869で規定されています。

RFC5869の目的としては、将来的なプロトコルやアプリケーションでの一般的なKDFを定義して、複数のKDFメカニズムが増殖されることを避ける目的もあります。

HKDFはextract-then-expandの枠組みに従って処理されます。

KDFはこの場合には、論理的に２つのモジュールから構成されます。
- Step1(Extract): 入力となる鍵の初期値(IKM: Input Keying Material)を受け取り、IKMから固定長となるPRK(PesedoRandom Key)を取得します。
- Step2(Expand):  Step1で生成したPRKを複数のPRKへと拡張します。


ExtractはIKMの分散エントロピーをより短い形へと変換する。しかし、暗号学的には強いといったことを目的とする。
ExpandはPRKを希望する長さのPRKへと拡張することです。

# HKDF

### Step1: Extract
```
処理内容: HKDF-Extract(salt, IKM)からPRKへの変換処理
```

- オプション
  - Hash: ハッシュ関数。HashLenはハッシュ関数の出力アウトプットとなるオクテットの長さを表す。
- 入力: 
  - salt:
  - IKM:  入力値となるメッセージ(Input Keying Material)
- 出力: 
  - PRK(PesedoRandom Key)
- 処理関数:
```
PRK = HMAC-Hash(salt, IKM)
```

### Step2: Expand
```
処理内容: HKDF-Expand(PRK, info, L) から OKM(Output Keying Material) への変換処理
```

- オプション:
  - Hash: ハッシュ関数。HashLenはハッシュ関数の出力のオクテット長を示す
- 入力:
  - PRK:  少なくともHashLenオクテット長のPRK
  - info: オプショナルなコンテキストやアプリケーション特有の情報
  - L:    オクテット長でのOKMの長さ (<= 255*HashLen)
- 出力:
  - LオクテットのOKM
- 処理関数:
  - 次のように計算されます。|は結合を表す。
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


### サンプル
以下のケースを試してみる
- https://tools.ietf.org/html/rfc5869#appendix-A.1


プログラムは次の内容である。testvectorは以下に記載されている。
```
#!/usr/bin/env python3
import hashlib
import binascii
import hmac
from math import ceil
from binascii import hexlify, unhexlify

# SHA256 = ハッシュの長さ32byte
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

実行してみる。１行目がPRKで、2行目がOKMである。
```
$ ./hkdf.py 
b'077709362c2e32df0ddc3f0dc47bba6390b6c73bb50f9c3122ec844ad7c2b3e5'
b'3cb25f25faacd57a90434f64d0362f2a2d2d0a90cf1a5a4c5db02d56ecc4c5bf34007208d5b887185865'
```


# RFC5869に記載されたテストベクタを使ってサンプルを検証する。
以下はHKDFの簡単なサンプルです。
以下はpython3で実行すること。
- https://github.com/tsuyopon/python/blob/9826f72d6a350b7a698d37ca37ae8dad9ed4176b/cipher/hkdf.py

上記サンプルでは以下のTest Case1に関するPRFとOKMを出力しています。
- https://tools.ietf.org/html/rfc5869#appendix-A.1

# 参考URL
- wikipedia: HKDF
  - https://en.wikipedia.org/wiki/HKDF
- Openssl: hkdf.c
  - https://github.com/openssl/openssl/blob/master/crypto/kdf/hkdf.c

# 実装サンプル
- https://github.com/warner/id-keywrapping-demo/blob/e77d260399e14cbe1794543164a1f41fdb4b86b0/hkdf.py
  - PythonコードでRFC5869に記載されたテストベクターを試しているサンプルコード

# SeeAlso
- RFC5869: HMAC-based Extract-and-Expand Key Derivation Function (HKDF)
  - https://tools.ietf.org/html/rfc5869
