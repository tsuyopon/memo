TODO:  攻撃手法を埋める

# 概要
CVE-2015-4000 (通称 Logjam) は TLS プロトコルの仕様に関する脆弱性です。

2015年5月19日に複数の研究機関と大学の研究者で構成された合同チームが以下の論文を発表することで知られるようになりました。
- Imperfect Forward Secrecy: How Diffie-Hellman Fails in Practice(PDF)
  - https://weakdh.org/imperfect-forward-secrecy-ccs15.pdf


# 詳細
### どのような攻撃か
「ディフィー・ヘルマン鍵共有」(DH)と呼ばれる暗号化方式に存在します。  
この脆弱性が悪用されると、中間者攻撃により、Webサイトの通信に強度の低い暗号を使うように強制させられ輸出グレードの512ビット暗号に格下げされる可能性があります。  
これによって通信内容の盗聴や改ざんといった被害に遭う可能性があります。

OpenSSL中に存在するFREAK攻撃と似ているがFREAKはサーバとクライアントの実装の問題であるのに対して、Logjamはプロトコル自体に存在する脆弱性である。

### 攻撃手法

詳細なシーケンシャルずは以下に記載されている。
- https://weakdh.org/logjam.html

### 対処方法
- 最新版のブラウザを利用すること
- 「DHE_EXPORT」の暗号スイートが有効であるすべてのサーバーとブラウザが影響を受けるので、サーバ・クライアントで「DHE_EXPORT」の暗号スイートを無効にすること
  - 輸出グレードの暗号スイートを禁止する
  - 2048ビットのDiffie-Hellman groupを使用する
  - ECDHEを使用する

### テスト方法
以下方法でLogjamに該当するかどうかをチェックすることができる。
```
OpenSSL: openssl s_client -connect www.example.com:443 -cipher 'EXP'

nmap: nmap --script ssl-enum-ciphers -p 443 www.example.com
```

上記でEXPは輸出を意味していて次のようなCipherSuiteが存在する
```
EXP-DES-CBC-SHA
EXP-RC2-CBC-MD5
EXP-RC4-MD5
EXP-EDH-RSA-DES-CBC-SHA
EXP-EDH-DSS-DES-CBC-SHA
EXP-ADH-DES-CBC-SHA
EXP-ADH-RC4-MD5
```

# 参考URL
- Imperfect Forward Secrecy: How Diffie-Hellman Fails in Practice(PDF)
  - logjam脆弱性が提起された元の論文
  - https://weakdh.org/imperfect-forward-secrecy-ccs15.pdf
- Weak Diffie-Hellman and the Logjam Attack
  - https://weakdh.org/
- Logjam攻撃のシーケンスや動画が載っている。
  - https://weakdh.org/logjam.html
- Guide to Deploying Diffie-Hellman for TLS
  - Diffie-Helmanを設定する際のサーバ設定ガイド
  - https://weakdh.org/sysadmin.html

