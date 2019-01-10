# LCOV
GCCのカバレッジテスト用ツールgcovをグラフィカルなUIでみることができるツールです。
画面については以下を参照してください。
- http://ltp.sourceforge.net/coverage/lcov.php

LCOVがやっていることはgcovデータを集めて、カバレッジレポート情報のためのソースコード情報などを含んだHTMLページを生成します。

細かいことは以下のreadme.phpを参照すると良いかもしれません。
- http://ltp.sourceforge.net/coverage/lcov/readme.php

# 詳細
### パッケージインストール
あらかじめパッケージがインストールされていることを確認しておきます。
```
$ sudo yum install lcov
```

### クィックスタート
- 1. gccへのコンパイラやリンカへのフラグとして--coverageを付与してコンパイルしてから、実行をする。
- 2. 次のコマンドでgcovデータを集めて、coverage.infoファイルへと変換します。directoryにはgcovファイルがある対象のディレクトリを指定します。
```
$ lcov --capture --directory ./ --output-file coverage.info
```
- 3. coverage.info情報からHTMLを生成する
```
$ mkdir out
$ genhtml coverage.info --output-directory out
$ ls out/
amber.png  emerald.png  gcov  gcov.css  glass.png  index-sort-f.html  index-sort-l.html  index.html  ruby.png  snow.png  updown.png
```
- 4. HTTPサーバを起動しておく(以下の例は8080ポート)
```
$ cd out
$ python -m CGIHTTPServer 8080      // ここではpythonで8080ポートを利用しています。
```
あとはブラウザからhttp://servername:8080/などでアクセスしてlcovレポートを閲覧できます。

### C++で関数名をデマングルさせるには
C++だと関数がデマングルされていないようなので、genhtml時に--demangle-cppオプションをつけらいし。(c++filtがインストールされている必要あり)
- 参考
  - http://shusaku721-bibou6.seesaa.net/article/451638174.html

# 参考URL
- 公式ページ
  - http://ltp.sourceforge.net/coverage/lcov.php
- github
  - https://github.com/linux-test-project/lcov
- lcovコマンドのmanpage
  - http://ltp.sourceforge.net/coverage/lcov/lcov.1.php
