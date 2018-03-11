# 概要
rubyコマンドで利用できる環境変数について纏めます。

# 詳細
- RUBYOPT
  - rubyコマンドにデフォルトで渡すオプションを指定することができます。
```
(例) RUBYOPT='-Ke -rkconv'
```
- RUBYPATH
  - rubyコマンドに対して-Sのオプションを指定した際にRUBYPATHで指定したディレクトリも検索対象となり、PATHの値よりも優先されます。
```
(例) RUBYPATH=$HOME/tsuyoshi:/usr/local/ruby
```
- RUBYLIB
  - Rubyライブラリの探索パス$:のデフォルト値の前にこの環境変数で指定された値が付加されることになります。
```
(例) RUBYLIB=$RUBYLIB:/var/lib/gems/1.8/lib
```
- RUBYSHELL
  - この環境変数は有効となるプラットフォームが限定されています。OS2版、mswin32版、mingw32版のrubyで有効となります。
  - この値が指定されているとsystem()だけでなく、popen()などでもデフォルトシェルとして利用されるようになります。
  - この環境変数が省略されていればCOMSPEC(Windows環境変数であります)の値が使用されることになります。
- RUBYLIB_PREFIX
  - この環境変数はRUBYSHELLと同様に有効となるプラットフォームが限定されています。DJGPP版、Cygwin版、mswin32版、 mingw32版のrubyで有効となります。
  - この環境変数は「path1;path2」又は「path1 path2」という形式で格納されます。このような値を格納するとrubyライブラリの探索パス「$:」の先頭部分がpath1にマッチした場合にpath2に置き換えます。
```
(例) RUBYLIB_PREFIX=/usr/local/lib/ruby;c:/ruby
```

# 参考URL
- Ruby 1.8.7 リファレンスマニュアル > spec/envvars
  - http://doc.okkez.net/static/187/doc/spec=2fenvvars.html
