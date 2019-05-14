# 概要
SHA関連について

- SHA1
  - 160byte
- SHA2: 6種類存在する
  - SHA-224
  - SHA-256
  - SHA-384
  - SHA-512
  - SHA-512/224
  - SHA-512/256
- SHA3
  - ダイジェスト長は224, 256, 384, 512 bitsの４つがある。SHA2とSHA3の違いはまだ未調査(TODO)

# 詳細

### SHA1の状況について
以下のサイトでSHA1を利用したデジタル証明書がすでに安全ではなくなっていることを説明している。
このサイトは2017年にGoogleによって同様のSHA1ハッシュ値を持つファイルを生成できてしまうことを証明した。SHA256やSHA3への移行を推奨している。
- https://shattered.it/

CA/BrowserフォーラムでもSHA1の発行は許可していない。
- https://cabforum.org/2014/10/16/ballot-118-sha-1-sunset/


# Reference
関連リファレンスが充実しているのでwikipediaも適宜参照すると良い。
- SHA1
  - 一次情報
    - NIST PUB 180-4
    - https://csrc.nist.gov/publications/detail/fips/180/4/final
  - https://ja.wikipedia.org/wiki/SHA-1
- SHA2
  - 一次情報
    - NIST PUB 180-4
    - https://csrc.nist.gov/publications/detail/fips/180/4/final
  - https://ja.wikipedia.org/wiki/SHA-2
- SHA3
  - 一次情報
    - FIPS PUB 202
    - https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.202.pdf
  - https://ja.wikipedia.org/wiki/SHA-3
