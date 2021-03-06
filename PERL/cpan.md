# 概要
CPAN(Comprehensive Perl Archive Network)とは、perlのモジュール・ライブラリを集めた巨大なアーカイブです。
- モジュールの最新ソースファイルを取ってきて、コンパイルし、インストールします。
- ライブラリの依存関係を解決してくれます。

# インストール操作
## CPANによるソースコードからのインストール
- http://pocketstudio.jp/linux/?%A5%E2%A5%B8%A5%E5%A1%BC%A5%EB%A4%CE%B4%F0%CB%DC%20-%20CPAN%20%A4%AB%A4%E9%20Perl%20%A4%CE%A5%E2%A5%B8%A5%E5%A1%BC%A5%EB%A4%F2%A5%A4%A5%F3%A5%B9%A5%C8%A1%BC%A5%EB%A4%B9%A4%EB


## perl -MCPANからのインストール
基本的なインストール操作の例です。
```
$ perl -MCPAN -e'install DBD::mysql'
```

コマンド(cpan)とインタラクティブ操作(perl -MCPAN -e shell)による２つの操作方法があります。以下で説明します。

# インタラクティブ操作詳細

## 基本操作

### CPANをインタラクティブモードで起動する。
CPANモジュールを使用する為には以下のコマンドを打ちます。
尚、下記コマンドを初回実行の際には初期設定を行う必要があります。ですが、ほとんどがデフォルト値で問題ありません。
```
# perl -MCPAN -e shell
or
# cpan
```

### CPANのアップグレードを行う
```
cpan> install Bundle::CPAN           // 結構時間がかかります
cpan> reload cpan
```

## インストール操作

### モジュールをインストールする
```
 【書式】cpan> install <モジュール名>
 【例】  cpan> install File/NCopy
```

尚、強制的にモジュールをインストールしたい場合にはinstallの前に「force 」を付加すれば依存関係を無視してインストールできます。
また、バージョンを指定してインストールしたい場合には下記の例のようにバージョンを指定します。
```
cpan> install File/Copy-x.x.x.tar.gz
```

### モジュールを更新する
```
 【書式】cpan> upgrade <モジュール名>
 【例】  cpan> upgrade File::NCopy
```

### モジュールを削除する

## 設定操作

### 設定を初期化する
```
cpan> o conf init
```

### 設定を確認する。
下記コマンドCPAN設定一覧を確認できます。
```
cpan> o conf
```

特定の設定だけを見たい場合に引数として設定名を付与します。下記ではurllist設定を確認する際の例です。
```
cpan> o conf urllist
```

## 設定を変更する
```
 【書式】cpan> o conf [オプション名] [新しい設定内容]
 【例】  cpan> o conf urllist http://test.cpan.org
```

### http_proxy, ftp_proxyを変更する
```
cpan> o conf http_proxy http://プロキシ名：ポート番号
cpan> o conf ftp_proxy  http://プロキシ名：ポート番号
cpan> o conf commit
```

### 依存するモジュールを自動的にインストールさせる
依存するモジュールの場合にはインストール前にyesかどうかを確認されます。
これは、設定により自動的にデフォルト値でエンターが押下されたものと認識させることができるようになります。
```
cpan> o conf prerequisites_policy follow
cpan> o conf commit
```

### CPANのURLから削除・追加を行いたい場合
- 削除
-- 先頭の設定を削除
```
cpan> o conf urllist shift <削除するURL>
cpan> o conf commit
```
-- 末尾の設定を削除
```
cpan> o conf urllist pop <削除するURL>
cpan> o conf commit
```
- 追加
-- 先頭に設定を追加
```
cpan> o conf urllist unshift <追加するURL>
cpan> o conf commit
```
-- 末尾に設定を追加
```
cpan> o conf urllist push <追加するURL>
cpan> o conf commit
```


## 検索操作
### 作者、バンドル、ディレクトリビューション、モジュールを検索する。
以下の例はhogehogeに関するモジュール一覧を表示します。
```
cpan> m /hogehoge/
```

| COLOR(red): カテゴリ | COLOR(red): 対象 |
| a | 作者 |
| b | バンドル |
| d | ディレクトリビューション・ファイル |
| m | モジュール |
| i | a, b, d, m全てを表示 |
| r | インストール済みのバージョンよりもCPANサイトのバージョンが新しいもの |
| u | インストールされていないもの |

## TIPS関連
### トラブルシューティング(CentOS5)

「perl MCPAN -e shell」を初回実行時に地域一覧(Asia等)が表示されずにcontinentを選択する画面がでました。
この画面でどんな設定を入力しても先に進むことができなくなりました。
```
 Select your continent (or several nearby continents) [] 5
 invalid items entered, try again
```

上記設定では、番号を押下しても「invalid items entered, try again」というエラーが表示されたために$HOME/.cpanディレクトリをリネームし、「perl MCPAN -e shell」コマンドを再度実行したら、先ほどは表示されなかった地域一覧(Asia等)が表示され、設定を解釈してくれるようになりました。
```
$ mv -iv $HOME/.cpan $HOME/.cpan.bak
$ perl MCPAN -e shell
```

### モジュールの削除を行う
```
$ ppm remove <モジュール名>
```

### モジュールの一覧を取得する
```
$ find `perl -e 'print join(" ", @INC)'` -type f -name "*.pm" > ファイル名
```

### モジュールのバージョンを確認する
```
$ perl -Mファイル名 -e 'print $ファイル名::VERSION'
```

### CPAN設定について
個人用のCPAN設定は$HOME/.cpan/ディレクトリに保存されています。
以下のファイルに保存されています。
```
$ cat $HOME/.cpan/CPAN/MyConfig.pm
```

# cpanコマンド
インタラクティブ操作でなくてもcpanコマンドにより大抵の操作はできるみたいです。
以下を参照の事
- http://wiki.bayashi.net/perl/cpan#cpan_.E3.82.B3.E3.83.9E.E3.83.B3.E3.83.89.E3.81.AE.E4.BD.BF.E3.81.84.E6.96.B9

# 参考URL
- Mediaweb
-- http://www.mediaweb.biz/database/modules/database/article.php?articleid=54
- サンプルコードによるPerl入門
-- http://d.hatena.ne.jp/perlcodesample/20100504/1270894115
- CPAN::Mini
-- http://e8y.net/mag/006-cpan-mini/
- CPANコマンドの使い方
-- http://wiki.bayashi.net/perl/cpan#cpan_.E3.82.B3.E3.83.9E.E3.83.B3.E3.83.89.E3.81.AE.E4.BD.BF.E3.81.84.E6.96.B9
