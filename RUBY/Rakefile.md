# 概要
rubyで処理内容を定義できるビルドツールです。  
実はruby専用というわけではなくJAVAのビルドにも利用しようと思えば利用することができます。

MakefileでいうターゲットをRakefileではタスクと呼びます。タスクは次の４つから構成されています。
- 名前
- アクション
- 事前タスク
- パラメータ

# 詳細
### パッケージインストール
gem経由でrakeパッケージをインストールすることによってRakefileを使うことができるようになります。
```
$ gem install rake
```

### 使ってみる
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

### Rakefileからタスクの説明を取得する
たとえば、Rakefileが次のようになっているとして、
```
$ cat Rakefile
desc "This is desc"
task :hoge

desc "This is desc2"
task :hoge2

desc "This is desc3"
task :hoge3
```

TオプションでそのRakefileに存在するタスク名を表示し、#よりあとに説明を表示します。
```
$ rake -T
rake hoge   # This is desc
rake hoge2  # This is desc2
rake hoge3  # This is desc3
```

### Namespaceを定義する
タスクの概念をグルーピングしたい場合にはNamespaceを利用することができます。
```
$ cat Rakefile
# ネームスペースの中にタスクを定義する。
namespace :test do
  task :hello do
    puts 'hello'
  end
  task :hello_world=>[:hello] do
    puts 'world'
  end
end
```

rakeコマンドの引数として「namespace:task」を指定すると、該当のnamespaceに存在するtaskを実行します。
```
$ rake test:hello_world
hello
world
```

### helpを表示する
```
$ rake -h
rake [-f rakefile] {options} targets...

Options are ...
        --backtrace=[OUT]            Enable full backtrace.  OUT can be stderr (default) or stdout.
        --comments                   Show commented tasks only
        --job-stats [LEVEL]          Display job statistics. LEVEL=history displays a complete job list
        --rules                      Trace the rules resolution.
        --suppress-backtrace PATTERN Suppress backtrace lines matching regexp PATTERN. Ignored if --trace is on.
    -A, --all                        Show all tasks, even uncommented ones (in combination with -T or -D)
    -B, --build-all                  Build all prerequisites, including those which are up-to-date.
    -D, --describe [PATTERN]         Describe the tasks (matching optional PATTERN), then exit.
    -e, --execute CODE               Execute some Ruby code and exit.
    -E, --execute-continue CODE      Execute some Ruby code, then continue with normal task processing.
    -f, --rakefile [FILENAME]        Use FILENAME as the rakefile to search for.
    -G, --no-system, --nosystem      Use standard project Rakefile search paths, ignore system wide rakefiles.
    -g, --system                     Using system wide (global) rakefiles (usually '~/.rake/*.rake').
    -I, --libdir LIBDIR              Include LIBDIR in the search path for required modules.
    -j, --jobs [NUMBER]              Specifies the maximum number of tasks to execute in parallel. (default is number of CPU cores + 4)
    -m, --multitask                  Treat all tasks as multitasks.
    -n, --dry-run                    Do a dry run without executing actions.
    -N, --no-search, --nosearch      Do not search parent directories for the Rakefile.
    -P, --prereqs                    Display the tasks and dependencies, then exit.
    -p, --execute-print CODE         Execute some Ruby code, print the result, then exit.
    -q, --quiet                      Do not log messages to standard output.
    -r, --require MODULE             Require MODULE before executing rakefile.
    -R, --rakelibdir RAKELIBDIR,     Auto-import any .rake files in RAKELIBDIR. (default is 'rakelib')
        --rakelib
    -s, --silent                     Like --quiet, but also suppresses the 'in directory' announcement.
    -t, --trace=[OUT]                Turn on invoke/execute tracing, enable full backtrace. OUT can be stderr (default) or stdout.
    -T, --tasks [PATTERN]            Display the tasks (matching optional PATTERN) with descriptions, then exit. -AT combination displays all of tasks contained no description.
    -v, --verbose                    Log message to standard output.
    -V, --version                    Display the program version.
    -W, --where [PATTERN]            Describe the tasks (matching optional PATTERN), then exit.
    -X, --no-deprecation-warnings    Disable the deprecation warnings.
    -h, -H, --help                   Display this help message.
```

# 参考URL

