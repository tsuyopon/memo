# 概要
rubyで処理内容を定義できるビルドツールです。  
実はruby専用というわけではなくJAVAのビルドにも利用しようと思えば使うことができます。


MakefileでいうターゲットをRakefileではタスクと呼びます。タスクは次の４つから構成されています。
- 名前
- アクション
- 事前タスク
- パラメータ

# 使ってみる
以下のサンプルファイルをRakefileという名称で保存する。
```
$ cat > Rakefile << "EOF"
## 書き方
# task <タスク名> , [<パラメータ名>, <パラメータ名> ... ] => [<前提タスク名>,<前提タスク名> ... ] do
#    # アクション
# end

# "hello" を表示するだけのタスク
task :hello do
  puts 'hello'
end

# "hello"の後に"world"を出力するタスク
task :hellow_world=>[:hello] do
  puts 'world'
end

# アクションなしのタスク
task :all=>[:hellow_world, :echo]

#パラメータを受け付けるタスク
task :echo, [:message] => [:hello] do |t, args|
  # ブロックへのパラメータとしてタスクオブジェクトとパラメータが渡される。
  puts args.message
end
EOF
```

上記サンプルではいくつかタスクが定義されているので実行してみることにする。
```
$ ls Rakefile
Rakefile
$ rake hello
hello
$ rake hellow_world
hello
world
$ rake all
hello
world
```

# 参考URL

