# Advanced Encryption Standard(AES)
AESはオリジナルネームとしてRijndaelとして知られています。
開発者はベルギーの暗号学者「Joan Daemen」と「Vincent Rijmen」であり、この二人の名将から名付けられたとされている。
NISTのコンペによって選定された暗号です。

AES(2001年発表)はアメリカ政府によって採用され、現在ではDES(1977年発表)に取って代わっています。3DESよりも早くて安全らしいです。
共通鍵暗号方式(ブロック型)として暗号化及び複合します。

共通鍵暗号にはブロック型の他にもストリーム型としてCHACHA20が存在します。ブロック型は次の２つの種類に分類されます。
- Feistel構造
  - DES, Camellia
- SPN構造
  - AES

AESは鍵長に応じて３種類のバリエーションが存在します。現時点ではAES-128でも十分に安全と考えられています。
AESではブロック長は常に128bitで固定となります。
```
AES規格  鍵長     ブロック長  ラウンド数
AES-128   128bit   128bit      10段
AES-192   192bit   128bit      12段
AES-256   256bit   128bit      14段
```

AESの凄いところは、SubBytes,ShiftRows,MixColumns それぞれの処理をビット演算だけで実現できることにあるので、早くハードウェアの実装も簡単です。

ブロック長よりも長い鍵長を使うことによって、暗号学的により強固なブロックを生成することができます。


# AESアルゴリズム概要
以下はAES-128の場合の10ラウンドの例だがSubBytes,ShiftRows,MixColumn, AddRoundKeyの4つを10回連続で回せばいいだけなわけではない。
最初にAddRoundKeyを実施してから、9ラウンド処理を実行して、最後にShiftRows,MixColumn, AddRoundKeyを実行することで10ラウンドとして扱われる。
```
AddRoundKey

int roundSum = 10;                    // AES-128だと10
for (round = 1; round < roundSum - 1; round++){
	SubBytes
	ShiftRows
	MixColumns
	AddRoundKey
}

SubBytes
ShiftRows
AddRoundKey
```

上記のアルゴリズムについては以下の動画「AES Rijndael Cipher explained as a Flash animation」が参考になる。
- https://www.youtube.com/watch?v=gP4PqVGudtg&t=47s

以下の４つの命令についての説明は以下の通り
- SubBytes
  - S-BOXという行列を用いて、ある要素を他の要素へと変換する。すべての要素に対して処理を行う。(Substitute)
- ShiftRows
  - 2行目は右に1byteローテート、3行目は右に2byteローテート、4行目は右に3byteローテートする。(Shift)
- MixColumns
  - 縦の列(4x1行列)を4x4の行列と掛け合わせることで新しい列行列(4x1)を得る。これを元の行列部分と置き換える。すべての列に対して行う。
- AddRoundKey
  - RoundKeyという行列(4x4)が用意される。元の行列とRoundKeyの行列を行の部分(1行目, ..., 4行目)でそれぞれ排他的倫理和を取る。計算された列は組み合わせて新しい行列を形成する。

余談だが、Intel-CPUではAES-NIという命令を用いる事によって、SubBytes, ShiftRows, MixColumns, AddRoundKeyという1ラウンドの処理を1命令で実行できるようになる。

# 入力と出力

### Encrypt
- 入力: 鍵(鍵長も決定する)、平文
- 出力: 暗号文

### Decrypt
- 入力: 鍵(鍵長も決定する)、暗号文
- 出力: 平文


# 実装サンプル
- https://github.com/dhuertas/AES/blob/master/aes.c
  - C言語の実装サンプル
- https://en.wikipedia.org/wiki/Advanced_Encryption_Standard
  - PythonにおけるAESの実装で、わずか200行程度なので理解しやすい
  - 概要理解などはこれが一番わかりやすい気がする

# 参考URL
- Wikipedia: Advanced Encryption Standard
  - https://en.wikipedia.org/wiki/Advanced_Encryption_Standard

# SeeAlso
- AESの一次情報
  - http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf
- https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines/archived-crypto-projects/aes-development

