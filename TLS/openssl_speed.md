# 概要
opensslでのベンチマーク測定方法について

# 詳細
### ベンチマークについて
opensslにはspeedというオプションが存在する。これによりベンチマークを測定できる。  

以下は代表的なものだけ
```
$ openssl speed -evp aes-128-gcm
$ openssl speed -evp aes-128-cbc
$ openssl speed rsa2048
$ openssl speed ecdhp256
```

evpというオプションはAES-NI(EVP_Decrypt, EVP_Encrypt)に対応した結果として測定するということを意味する(もちろんCPU、コンパイルしたgasの対応も必要)。このオプションを付与しない場合にはAES-NIは利用されない。
```
$ openssl speed -evp aes-128-gcm   // AES-NI対応
$ openssl speed aes-128-gcm        // AES-NI非対応
```

- たとえばRSAに関してテストコマンドを実行すると様々なオプションでテストを実行してくれます。
```
$ openssl speed rsa
Doing 512 bit private rsa's for 10s: 142745 512 bit private RSA's in 9.76s
Doing 512 bit public rsa's for 10s: 1776110 512 bit public RSA's in 9.88s
Doing 1024 bit private rsa's for 10s: 44200 1024 bit private RSA's in 9.87s
Doing 1024 bit public rsa's for 10s: 603680 1024 bit public RSA's in 9.83s
Doing 2048 bit private rsa's for 10s: 5431 2048 bit private RSA's in 9.74s
Doing 2048 bit public rsa's for 10s: 179589 2048 bit public RSA's in 9.82s
Doing 4096 bit private rsa's for 10s: 796 4096 bit private RSA's in 9.84s
Doing 4096 bit public rsa's for 10s: 49787 4096 bit public RSA's in 9.86s
OpenSSL 1.0.1f 6 Jan 2014
built on: Fri Dec  4 13:26:29 UTC 2015
options:bn(64,64) rc4(16x,int) des(idx,cisc,16,int) aes(partial) blowfish(idx) 
compiler: cc -fPIC -DOPENSSL_PIC -DOPENSSL_THREADS -D_REENTRANT -DDSO_DLFCN -DHAVE_DLFCN_H -m64 -DL_ENDIAN -DTERMIO -g -O2 -fstack-protector-strong -Wformat -Werror=format-security -D_FORTIFY_SOURCE=2 -Wl,-Bsymbolic-functions -Wl,-z,relro -Wa,--noexecstack -Wall -DMD32_REG_T=int -DOPENSSL_IA32_SSE2 -DOPENSSL_BN_ASM_MONT -DOPENSSL_BN_ASM_MONT5 -DOPENSSL_BN_ASM_GF2m -DSHA1_ASM -DSHA256_ASM -DSHA512_ASM -DMD5_ASM -DAES_ASM -DVPAES_ASM -DBSAES_ASM -DWHIRLPOOL_ASM -DGHASH_ASM
                  sign    verify    sign/s verify/s
rsa  512 bits 0.000068s 0.000006s  14625.5 179768.2
rsa 1024 bits 0.000223s 0.000016s   4478.2  61412.0
rsa 2048 bits 0.001793s 0.000055s    557.6  18288.1
rsa 4096 bits 0.012362s 0.000198s     80.9   5049.4
```

- 2CPUでテスト
```
$ openssl speed rsa -multi 2
```
- CPUを使い切ってテストする
```
$ openssl speed rsa -multi `grep processor /proc/cpuinfo|wc -l`
```

