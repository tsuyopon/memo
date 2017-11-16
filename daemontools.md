# 概要
daemontoolsはUnix系OSにおけるサービスの管理作業(プロセス監視、ロギング)をシンプルな手法で行うための支援ツールである。  
daemontoolsはパッケージの総称であり、daemontoolsというプログラム自体が存在するわけではない。

次の３つのプログラムがdaemontoolsを構成する主要プログラムである。
- svscan
  - /servicesディレクトリ直下を監視して、ディレクトリを発見するとそのディレクトリ内でサービス管理デーモンsuperviseを起動する。
- supervise
  - superviseは/services/<servicedir>/runという名称のプロセス起動コマンドを実行する。runはシェルスクリプトで記述されている。
  - runの中では必要な環境変数を設定して、execで起動したいコマンドを指定する構造となっている。
  - runが何かしらの理由で終了すると、superviseはそのたびにrunを起動します。
- multilog
  - 標準入力からのパイプを処理し、指定したログファイルに出力します。
  - ログの取得にはUnixパイプを使用するので高負荷時でもsyslogd時のような取りこぼしはおきない。


# 詳細

### daemontoolsのインストール
- http://cr.yp.to/daemontools/install.html

# 参考URL
- daemontoolsドキュメント
  - http://cr.yp.to/daemontools.html
  - 日本語ドキュメント
    - http://www.emaillab.org/djb/tools/daemontools/top.html
- github
  - https://github.com/daemontools/daemontools
- runスクリプトのコレクション
  - http://smarden.org/runit/runscripts.html 
- (数少ない)日本語関連のページ
  - http://www.unixuser.org/~euske/doc/daemontools/index.html
