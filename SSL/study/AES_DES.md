# 概要
ブロック暗号(DES, AES)について説明する。
```
対象暗号(共通鍵)
	ストリーム暗号: 
		データを逐次暗号化(RC4, Chacha20)
	ブロック暗号:
		データをブロック毎に暗号化(DES, AES)
```

# 詳細

### DES(Data Encryption Standard)
AESより前の方式です。
DESは次の問題があった。
- ・時代の経過による相対的な強度の低下
- ・NSAの関与があるその設計の不透明性

入力としては64bit(8bytes)単位でデータと64bitの暗号化用の鍵を受け付ける。    
入力されたデータを上下32bitずつに分けて、それに対して16段の暗号化処理を繰り返し適用する(ファイステル構造)。  
出力としては64bitの暗号化済みデータを出力する。




参考
- https://ja.wikipedia.org/wiki/Data_Encryption_Standard

### AES(Advanced Encryption Standard) とは何か?
アメリカではDESやトリプルDESといった暗号方式が使われていた。  
しかし、この方法は古くなったのでアメリカ政府は公募によってより強力な暗号化方式を選択した。  
それが、Rijndael (ラインダール) というアルゴリズムで、これが AES として採択されることになりました。  
AESの特徴としては次の通り
- SPN構造のブロック暗号
- ブロック長は128ビット
- 鍵長は128ビット・192ビット・256ビットの3つが利用できる。

AESは無線LANで使われることが多く、安全とされるWPA2に採用されている。  
(WEP, WPA, WPA2は暗号化に関する規格を表し、TKIPやAESは暗号化方式を表す概念)  

アルゴリズムとしては入力されたデータをいくつかのブロックに分割して、bitデータの
「置換(Substitution)」を行い、それらをまとめてブロック全体へ「転置(Permutation)」する。これがSPN(Substitution Permutation Network)の由来です。

具体的には
- SubBytes、ShiftRows、MixColumns、AddRoundKeyはそれぞれ置換、シフト、混合、XOR演算を行うAESの基本処理である。
- 上記一覧の処理をセットとしてこれを１ラウンドとして、入力されたデータに対して10, 12, 14ラウンドのいずれかを繰り返し適用する。


- 参考ポインタ
  - AES仕様書
    - http://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf
    - アルゴリズムやinput, outputなどが記述されている。
  - AES概説
    - http://web.archive.org/web/20090503235219/http://www-ailab.elcom.nitech.ac.jp/security/aes/overview.html
  - NISTによる資料(Report on Development of the AES)
    - http://csrc.nist.gov/archive/aes/round2/r2report.pdf
  - 専用のCPU命令がある。(出してみたい*TODO)
    - https://ja.wikipedia.org/wiki/AES-NI
    - https://ja.wikipedia.org/wiki/CLMUL_instruction_set
  - wikipedia
   - https://ja.wikipedia.org/wiki/Advanced_Encryption_Standard

### DESとAESの技術的な違いについて
DESとAESの比較を記述する。DESの鍵長は56bitと非常に短いので安全とされない。
- 鍵長
  - DES: 56bit
  - AES: 128/192/256bitから選択可能
- ブロック長
  - DES: 64bit
  - AES: 128bit
- ラウンド数
  - DES: 16
  - AES: 10, 12, 14(鍵長による)
- 構造
  - DES: ファイステル構造
    - 入力されたデータを上下32bitずつに分けて、それに対して16段の暗号化処理を繰り返し適用する。
    - 資料: http://www.atmarkit.co.jp/ait/articles/1505/21/news030.html
  - AES: SPN構造(Substitution Permutation Network)
    - 入力されたデータに対して同じような処理を何回か繰り返し適用する。




