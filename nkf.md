# 概要
nkf(Network Kanji Filter)コマンドについて


# 詳細
### 現在のディレクトリ直下に存在するファイルの文字コードを確認する
```
$ nkf -g *
Makefile.md: UTF-8
Markdown.md: UTF-8
UnixCommand.md: UTF-8
...
```

### 現在のディレクトリ直下に存在する既存のファイルを全てUTF-8に変換して上書きする
あらかじめ既存のファイルなどをバックアップしてから次のコマンドを実行するのが良いです。
```
$ nkf -w --overwrite *
```

余談ですが、EUC-JPやShift-JIS, ISO-2022-JPに変換する場合は次の通り
```
// EUC-JP
$ nkf -e --overwrite *


// Shift-JIS(cp932)
$ nkf -s --overwrite *


// JISコード(ISO-2022-JP)
$ nkf -j --overwrite *
```

### 改行形式を指定して変換する
同一OS内などであればe, s, jなどだけのオプションで十分ですが、異なるOSの改行形式にするには次の
```
-Lu          : unix改行形式(LF)に変換
-Lw          : windows改行形式(CRLF)に変換
-Lm          : macintosh改行形式(CR)に変換
```

#### 文字コードの入力エンコーディング判定を指定する
入力されたエンコーディング判定だと意図しない出力になることがあります。
たとえば、入力されたエンコーディングがsjisと判定されない場合などについては次の通り
```
// EUCコードとして入力し、UTF-8に変換
$ nkf -E -w test.txt

// UTF-8コードとして入力し、EUC-JPに変換
$ nkf -W -e test.txt

// Shift-JISコードとして入力し、UTF-8に変換
$ nkf -S -w test.txt
```

### その他nkfでできること
この他でもnkfsでは次にあげるような様々なことが実現可能です。詳細は参考URLを参考にすること
- ひらがなで出力する
- カタカナで出力する
- 半角カナを全角カナに変換する
- 全角を半角にする
- UTF-16を出力する
- SO-2022-JP以外の漢字コードを「〓（げた記号）」に変換する

# 参考URL
- 上記であげた例はよく利用されるものの一部です
  - http://www.atmarkit.co.jp/ait/articles/1609/29/news016.html
