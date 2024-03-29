# 正規表現について
正規表現について記載しておく

正規表現の4種類
- 1文字を表すものの例
```
.
[a-z]
\w
\W
```
- 繰り返す量を表すものの例
```
o*
o?
o{5,10}
```
- 前後の条件を表すものの例
```
^
$
\b
(?=...)
(?<=...)
```
- グルーピング, OR, 修飾子
```
(...)
|
\o
```

# 基本事項

### 基本的なメタ文字
```
A|B         正規表現Aか、正規表現Bのいずれか
.           任意の１文字。ただし、改行 (\n, \r)を除く
\X          直後のメタ文字Xをエスケープする
```

### 文字クラス
```
[ABC]     A,B,Cのいずれか1文字
[^ABC]    A,B,C以外の1文字
[A-Z]     大文字英語の１文字
[a-z]     小文字英語の１文字
[A-Za-z]  大文字・小文字英語の１文字
[0-9]     数字の１文字
(R)       正規表現をグルーピングする。括弧内の正規表現にマッチした文字列はキャプチャされ後方参照できる
```

### アンカー
```
^         行の先頭を指定
$         行の末尾を指定
```

### 量指定子
```
*         直前のパターンが0回以上連続する
+         直前のパターンが1回以上連続する
?         直前のパターンが0回または1回出現する
{N}       直前のパターンがN回連続する
{N,}      直前のパターンがN回以上連続する
{,M}      直前のパターンがM回以下連続する
{N,M}     直前のパターンがNからM回連続する
```

### エスケープシーケンス
小文字
```
\n        改行コード（Line Feed）
\r        改行コード（Carriage Return）
\f        改ページ
\t        タブ
\s        空白文字 (半角スペース、\t、\n、\r、\f）すべての文字。( |\t|\n|\r|\f)と同じ意味
\d        数字。[0-9]と同じ
\w        すべてのアルファベットとアンダースコアのうち任意の一文字。[a-zA-Z0-9_]と同じ
\l        すべての半角英小文字のうち１文字
\u        すべての半角英大文字のうち１文字
\v        垂直タブ
\a        ベル文字
\cX       Ctrl + X (Xは任意の文字を表します)
```

大文字
```
\R        すべての改行コード（「\n|\r|\n\r」と同じ意味)
\S        空白文字以外のすべての文字
\W        すべてのアルファベットとアンダースコア以外の１文字[^a-zA-Z0-9_]と同じ
\D        数字以外。[^0-9]と同じ
\L        すべての半角英小文字の以外の文字１文字（英大文字、数字、全角文字など含む）
\U        すべての半角英大文字以外の１文字（英小文字、数字、全角文字など含む）
\0        NULL文字（0の後に数字を続けると、８進数を表す数字を表すエスケープシーケンスとなるので注意）
```

# やや高度な正規表現

### 量指定子
```
R?        最短一致の量指定子 (.*? や *? や ?? や {N,}? や {N,M}? など最小で一致したケースがマッチすることになります)
```

### 後方参照
```
\Nは整数。キャプチャした文字列を後方参照する。Nはキャプチャした順
```

### 先読み・後読み
```
(?=R)   肯定・先読み
(?!R)   肯定・後読み
(?<=R)  否定・先読み
(?<!R)  否定・後読み
```

### グルーピング
```
(?F)             パターンの途中でフラグFを有効可する
(?-F)            パターンの途中でフラグFを解除する
(?A-B)           パターンの途中でフラグAを有効可、Bを解除する
(?A-B)           パターンの途中でフラグAを追加、Bを解除する
(?:R)            正規表現をグルーピング。カッコ内の正規表現にマッチした文字列をキャプチャしない
(?F:R)           (?:)内でフラグを有効可.
(?(条件)A)       条件を満たせば正規表現Aを有効化
(?(条件)A|B)     条件を満たせば正規表現Aを有効化、そうでなければBを有効化
```

### 量指定子
正規表現ではデフォルトでは最大限の文字列とマッチさせようとしてしまいます。このような量指定子を最大量指定子や欲張りな量指定子といいます。
「R?」については最短マッチを表しますが、具体的にいくつかの例を列挙しておきます。
```
{N,M}?     N回以上、M回以下の繰り返しの最小一致
{N,}?      N回以上の繰り返しの最小一致
{N}?       N回の繰り返しの最小一致
*?         0回以上の繰り返しの最小一致
.*?        1文字以上の0回以上の繰り返しの最小一致
+?         1回以上の繰り返しの最小一致
.+?        1文字以上の1回以上の繰り返しの最小一致
??         0または1回の繰り返しの最小一致
```

### 右側に条件を追加する
以下の場合には文字の右側にある条件にマッチします。
```
(?=,)
```

例えば、以下の文章だと上記正規表現は「level」の右側にある「,」にマッチします
```
const level, setLevel
```

下記の正規表現であれば
```
level(?=,)
```

下記から「level」の部分だけを抽出することができます。
```
const level, setLevel
```

### 否定先読み

```
level(?!,)
```


# URLやメールアドレスで参考になる正規表現

### URLの正規表現
残念なことに公式の正規表現というのも特に存在してなさそうである。

いくつかサンプルサイトを提示しておく
- What is the best regular expression to check if a string is a valid URL?
  - https://stackoverflow.com/questions/161738/what-is-the-best-regular-expression-to-check-if-a-string-is-a-valid-url
- What is a good regular expression to match a URL? [duplicate]
  - https://stackoverflow.com/questions/3809401/what-is-a-good-regular-expression-to-match-a-url
- Regular expression for URL validation (in JavaScript)
  - https://stackoverflow.com/questions/1410311/regular-expression-for-url-validation-in-javascript
- Regex for website or url validation [duplicate]
  - https://stackoverflow.com/questions/42618872/regex-for-website-or-url-validation
- Regular expression for checking website url
  - https://stackoverflow.com/questions/2490310/regular-expression-for-checking-website-url
- O'REILLY
  - https://www.oreilly.com/library/view/regular-expressions-cookbook/9781449327453/ch08s01.html


実務で適用させる際には以下についてはしっかりと吟味した方が良い
- http, httpsを含めるかどうか
- フラグメント(#)を含むかどうか

### Emailの正規表現
Emailについては非常に難しい
- http://emailregex.com/

上記サイトでは下記がRFC5322に99.9%にマッチする正規表現として記載されている。公式ではなくあくまでも参考として
```
(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\])
```

# 参考サイト
### 正規表現を可視化してくれるサイト
非常に便利なサイトである。
- https://www.debuggex.com/

正規表現チェッカー
- https://www-creators.com/tool/regex-checker

### 検索しにくい正規表現
- https://stackoverflow.com/questions/22937618/reference-what-does-this-regex-mean
  - この回答がすべてのリンクを網羅している。

