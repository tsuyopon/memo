# 概要
Apacheモジュールについてまとめる

# Apacheモジュール概要について
core以外のモジュールについての概要は以下の通り
- IPアドレスやネットワーク、ドメインによりアクセス制限を行う
  - mod\_access
- ログのカスタマイズを行う
  - mod\_log\_config
- Basic認証、Digest認証を利用する
  - mod\_auth
- WebDAVを利用する
  - mod\_dav
- rewriteを実現したい
  - mod\_rewrite
- 各ユーザでpublic\_htmlとしてウェブページを実現したい
  - mod\_userdir
- エイリアスを設定する
  - mod\_alias
- 拡張子と関連ファイル付けを行う
  - mod\_mime
- perlを利用してapacheハンドラを作成する
  - mod\_perl
- SSLを使用したい場合
  - mod\_ssl
- ディレクトリ情報をインデックスとしてそのまま参照できるようにしたい
  - mod\_autoindex
- リクエスト情報及びレスポンス情報のヘッダを操作したい
  - mod\_headers

# 参考URL
- Apache HTTP Server Version 2.4 コアモジュール一覧
  - 上記の他にも様々なモジュールがあるので以下を参考のこと
  - https://httpd.apache.org/docs/2.4/en/mod/
