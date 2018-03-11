# 概要
Ruby Documentation System(RDoc) は、Rubyで書かれたソースコードからドキュメントを自動生成を行うための、Ruby本体付属の標準ライブラリです。 rdocコマンドによりドキュメントを自動生成できます。

# 詳細

### 簡単な使い方
```
# mkdir -p /var/www/html/testdoc
# cd /var/www/html/testdoc
# 続いて、ディレクトリ内部に適当なRubyのファイルを設置してから以下のコマンドを実行します。
# rdoc test.rb

                       test.rb: mc......
Generating HTML... 

Files:   1
Classes: 1
Modules: 1
Methods: 6
Elapsed: 4.223s
```

以上により/var/www/htmlをapacheのDocumentRootと仮定すると
```
http://<servername>/testdoc/
```
によって生成されたHTMLにアクセスすることができます。

# 参考URL
- RDOC - Ruby Documentation System
  - http://www.kmc.gr.jp/~ohai/rdoc.ja.html
