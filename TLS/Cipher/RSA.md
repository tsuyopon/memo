# 概要
RSAは1978年にRivest, Shamir, Adlemanが発表した公開鍵暗号方式です。
大きな素数しか含まので、素因数分解が難しいことを利用しています。

このアルゴリズムは1983年にRSA Security社が特許を取得していましたが、特許期間満了により2000年9月からは誰でも利用できるようになりました。

# RSAの処理の流れ
RSAは鍵生成、暗号化、復号の３つのアルゴリズムによって定義される。

### 鍵生成
- 1. 大きな2つの素数であるp, qを求め、n=pqを求める。
  - p = 5, q = 11と決めると n = 55
- 2. (p-1), (q-1)の最小公倍数lを求める。
  - l = 20 (4, 10の最小公倍数)
- 3. lと互いに素なeを選び、ed = 1 (mod l)を満たすdを求める。
  - e = 3を選ぶと、d = 7
- 4. 公開鍵を(n, e)、秘密鍵をdと定義する。

### 暗号化
Mから暗号文Cを求める手順は次の通り
- 1. 平文を0以上、n未満の値Mに変換する。Mは暗号化するメッセージである。
  - M = 4とする
- 2. C = M^e mod n をMの暗号文とする
```
C = M^e mod n
= 4^3 mod 55
= 9
```

### 復号
暗号文CからメッセージMを復号する手順は次の通り
- 1. D = C^d mod n をCの復号結果とする
```
D = C^d mod n
= 9^7 mod 55
= 4
```

# opensslコマンドを使ってRSAの処理(鍵生成・暗号化・復号)を確認する
以下の記事を参考にしてopensslコマンドでRSAの鍵生成、暗号化、復号処理を手を動かして確認する。
- https://ozuma.hatenablog.jp/entry/20130510/1368114329

次のコマンドで秘密鍵を生成する。以下は簡単のために512byteとしているが、本来は2048などを指定する方が強度が高い。
```
$ openssl genrsa 512 > private-key.pem
Generating RSA private key, 512 bit long modulus
...................++++++++++++
........++++++++++++
e is 65537 (0x10001)
```

秘密鍵を確認すると次のようになります。(テスト用の秘密鍵なので添付している)
```
$ cat private-key.pem
-----BEGIN RSA PRIVATE KEY-----
MIIBOgIBAAJBANvloSCar1TT/dJ71sftXjx6WIrAEcrfEtZ+KSW3J5vyFYJZcp2S
dnPd6U0z05OqZc65w84H5TDx344jUtgHQdMCAwEAAQJAaMC3RUTrCUoDvGVqJ8uX
/M97pn1g/HfQDYYELAdYQxzpFeP/6ZGxXvV6AKwuurad6lGmXGIIIbtYyS964NDj
gQIhAP/z26YG2aryxwiALAM6BElX5sfBCNuN17YaMBkQmyMxAiEA2/APnGS45utW
G49ZfU+Z55Vt/UfNcMsfMUE9aukCzEMCIQDgFn59841q77d2J9Fg2dCa7gytYsIA
h0UOuArYRwOsYQIgU/tx6pUnab3ZToLJeCkqKp0Lt9hwIS7exU8VJbq9/8MCIEHP
nQNqbrLxYwDFDYIqm4WWB7s0TNhTVVVt5f5Dtu2s
-----END RSA PRIVATE KEY-----
```

秘密鍵の情報は次のようにして詳細を確認することができます。
modulusは実はprime1とprime2の積の値となっています。
```
$ openssl rsa -text < private-key.pem
Private-Key: (512 bit)
modulus:
    00:db:e5:a1:20:9a:af:54:d3:fd:d2:7b:d6:c7:ed:
    5e:3c:7a:58:8a:c0:11:ca:df:12:d6:7e:29:25:b7:
    27:9b:f2:15:82:59:72:9d:92:76:73:dd:e9:4d:33:
    d3:93:aa:65:ce:b9:c3:ce:07:e5:30:f1:df:8e:23:
    52:d8:07:41:d3
publicExponent: 65537 (0x10001)
privateExponent:
    68:c0:b7:45:44:eb:09:4a:03:bc:65:6a:27:cb:97:
    fc:cf:7b:a6:7d:60:fc:77:d0:0d:86:04:2c:07:58:
    43:1c:e9:15:e3:ff:e9:91:b1:5e:f5:7a:00:ac:2e:
    ba:b6:9d:ea:51:a6:5c:62:08:21:bb:58:c9:2f:7a:
    e0:d0:e3:81
prime1:
    00:ff:f3:db:a6:06:d9:aa:f2:c7:08:80:2c:03:3a:
    04:49:57:e6:c7:c1:08:db:8d:d7:b6:1a:30:19:10:
    9b:23:31
prime2:
    00:db:f0:0f:9c:64:b8:e6:eb:56:1b:8f:59:7d:4f:
    99:e7:95:6d:fd:47:cd:70:cb:1f:31:41:3d:6a:e9:
    02:cc:43
exponent1:
    00:e0:16:7e:7d:f3:8d:6a:ef:b7:76:27:d1:60:d9:
    d0:9a:ee:0c:ad:62:c2:00:87:45:0e:b8:0a:d8:47:
    03:ac:61
exponent2:
    53:fb:71:ea:95:27:69:bd:d9:4e:82:c9:78:29:2a:
    2a:9d:0b:b7:d8:70:21:2e:de:c5:4f:15:25:ba:bd:
    ff:c3
coefficient:
    41:cf:9d:03:6a:6e:b2:f1:63:00:c5:0d:82:2a:9b:
    85:96:07:bb:34:4c:d8:53:55:55:6d:e5:fe:43:b6:
    ed:ac
writing RSA key
-----BEGIN RSA PRIVATE KEY-----
MIIBOgIBAAJBANvloSCar1TT/dJ71sftXjx6WIrAEcrfEtZ+KSW3J5vyFYJZcp2S
dnPd6U0z05OqZc65w84H5TDx344jUtgHQdMCAwEAAQJAaMC3RUTrCUoDvGVqJ8uX
/M97pn1g/HfQDYYELAdYQxzpFeP/6ZGxXvV6AKwuurad6lGmXGIIIbtYyS964NDj
gQIhAP/z26YG2aryxwiALAM6BElX5sfBCNuN17YaMBkQmyMxAiEA2/APnGS45utW
G49ZfU+Z55Vt/UfNcMsfMUE9aukCzEMCIQDgFn59841q77d2J9Fg2dCa7gytYsIA
h0UOuArYRwOsYQIgU/tx6pUnab3ZToLJeCkqKp0Lt9hwIS7exU8VJbq9/8MCIEHP
nQNqbrLxYwDFDYIqm4WWB7s0TNhTVVVt5f5Dtu2s
-----END RSA PRIVATE KEY-----
```

上記の出力結果を「RSAの処理の流れ」で説明したパラメータを当てはめるとprime1, prime2がそれぞれp, qを表し、n=pqがmodulus、秘密鍵dがprivateExponentである。
lについては秘密鍵dを生成するときにだけ必要なので以下では表示されていないものと思われる。
また、eについてはpublicExponentに記載されている65537(=0x10001)が表しています(計算量の観点から固定値になっているらしい)

- prime1: p
- prime2: q
- modulus: n=pq
- publicExponent: e=65537 (=0x10001)
- privateExponent: d = e^(-1) mod (p-1)*(q-1)
- exponent1: d mod (p-1) 
- exponent2: d mod (q-1) 
- coefficient: q^(-1) mod p

上記のexponent1, exponent2, coefficientは複合処理を中国の剰余定理により効率的に行うために保存されている数字である。
- https://en.wikipedia.org/wiki/RSA_%28cryptosystem%29#Using_the_Chinese_remainder_algorithm

TODO: 中国の剰余定理でどのようにexponent1, exponent2, coefficientが使われるのかわかっていないので時間があれば調査すること


秘密鍵の情報を元に公開鍵を書き出します。
```
$ openssl rsa -pubout < private-key.pem > public-key.pem
writing RSA key
```

生成された公開鍵の中を確認します。
先程まで秘密鍵に含まれていたprime1, prime2などの情報が削除されていて、prime1とprime2の積となるmodulusとExponentが記載されていることが確認できました。
よって、これは公開鍵として公開しても問題ないファイルであることが確認できました。
```
$ openssl rsa -text -pubin < public-key.pem
Modulus (512 bit):
    00:db:e5:a1:20:9a:af:54:d3:fd:d2:7b:d6:c7:ed:
    5e:3c:7a:58:8a:c0:11:ca:df:12:d6:7e:29:25:b7:
    27:9b:f2:15:82:59:72:9d:92:76:73:dd:e9:4d:33:
    d3:93:aa:65:ce:b9:c3:ce:07:e5:30:f1:df:8e:23:
    52:d8:07:41:d3
Exponent: 65537 (0x10001)
writing RSA key
-----BEGIN PUBLIC KEY-----
MFwwDQYJKoZIhvcNAQEBBQADSwAwSAJBANvloSCar1TT/dJ71sftXjx6WIrAEcrf
EtZ+KSW3J5vyFYJZcp2SdnPd6U0z05OqZc65w84H5TDx344jUtgHQdMCAwEAAQ==
-----END PUBLIC KEY-----
```

公開鍵を使って暗号化を行います。暗号化にはencryptを指定します。生成されるmessageはバイナリになります。
```
$ echo "HELLO" | openssl rsautl -encrypt -pubin -inkey public-key.pem > message
```

秘密鍵を使って復号します。復号にはdecryptを指定します。
```
$ cat message | openssl rsautl -decrypt -inkey private-key.pem
HELLO
```

# RSA暗号が正しく復号できることの証明
秘密鍵であるprivateExponentはmod p*qではなくmod (p-1)*(q-1) から計算が行われていることを利用している。
この計算式が実はRSA暗号が正しく復号できることと大きく関係しています。

RSA暗号が正しく復号できることは、次のフェルマーの小定理によって証明できます。
下記で(p-1) が出てくることが、(p-1)*(q-1) が用いられる背景となっています。
```
p を素数、a を p と互いに素な整数としたとき、a^(p-1) == 1 mod p
```

なお、次の条件は成り立つ。
- p, qは互いに素
- d = publicExponent も (p-1)*(q-1) は互いに素
- e = 65537 (=0x10001)  も素

暗号文 ciphertext を c としたとき、フェルマーの小定理を利用すると、m が p と互いに素な場合と素でない場合のどちらについても
```
c^d == m mod p
```

同様に、pとqは対象の関係にあるので
```
c^d == m mod q
```

が成り立ちます。
上記が成立するための計算については以下を参照のこと(フェルマーの小定理を省いてしまっているので)
- https://en.wikipedia.org/wiki/RSA_%28cryptosystem%29#Proof_using_Fermat.27s_little_theorem

TODO: 上記の計算途中式をちゃんと見ていないので確認しておくこと


上の２つの式はある整数k, lを用いることによって次の連立式に書き換えられることができます。
この連立式は次の事実から導き出されます。
- pで割ってm余るというのは、mを差し引くとpのk倍である
- qで割ってm余るというのは、mを差し引くとqのl倍である

```
c^d - m = k*p
c^d - m = j*q
```

p, qは素数なので、上の連立式が成り立つとき、k は q の倍数、j は p の倍数になっているはずである。
つまり、上の公式は K = k/q = j/p となっているはずであるので、Kを使って次の式にまとめることができます。また、n = p*qなので、
```
c^d - m = K*p*q
        = K*n
```

これを先程の逆で合同の形に戻すと次の式になります。
```
c^d == m mod n
```

以上により復号の式を表すことができました。



以下を参考のこと
- https://ja.wikipedia.org/wiki/RSA%E6%9A%97%E5%8F%B7


# 参考URL
- wikipedia: RSA暗号
  - https://ja.wikipedia.org/wiki/RSA%E6%9A%97%E5%8F%B7
- ろば電子が詰まっている: opensslでRSA暗号と遊ぶ
  - https://ozuma.hatenablog.jp/entry/20130510/1368114329
- ももいろテクノロジー: OpenSSLとPythonでRSA暗号の原理を知る
  - http://inaz2.hatenablog.com/entry/2013/11/27/225953
