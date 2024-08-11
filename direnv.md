# direnvとは
direnvはそのディレクトリがカレントディレクトリになった時にだけ環境変数を有効・無効にしてくれるツールです。
開発中のアプリ毎に環境を変えたい様なケースで重宝してきます。

公式githubは下記に存在していて、go言語で実装されています。
- https://github.com/direnv/direnv


# とりあえず使ってみる (Getting Started)
手元はMacOSなのでbrewでインストールします。
```
$ brew install direnv
```

続いて.bashrcにdirenvのhookを追加します。
```
$ vim .bashrc
eval "$(direnv hook bash)"
```

では、次にdirenvが読み込む.envrcを用意します。
下記コマンドで.envrcを生成することができます。EDITOR環境変数の指定がないと怒られるのでvimをdirenv edit起動時に指定しています。
なお、下記で編集すると通常.envrcを読み込ませるために実行が費用となる「$ direnv allow .」も同時に実行されるようです。
```
$ EDITOR=vim direnv edit .
direnv: loading ~/worknix/.envrc
direnv: export +AZARASHI_TEST
```

.envrcには次の様な設定を保存しました。
```
$ cat .envrc 
export AZARASHI_TEST=test
unset AZARASHI_ABC
```

環境変数の状態を確認するとAZARASHI_TESTが自動的にセットされています。
```
$ env | grep AZARASHI
AZARASHI_TEST=test
```

では、1つ上のディレクトリに移動してみます。するとAZARASHI_TESTの環境変数が外れました。
```
$ cd ..
direnv: unloading
$ env | grep AZARASHI
$ env | grep AZARASHI
$
```

では、ここでAZARASHI_ABCの環境変数をセットしておきます。
```
$ export AZARASHI_ABC="abc"
$ env | grep AZARASHI
AZARASHI_ABC=abc
```

先ほどの.envrcが存在するディレクトリに移動して、.envrcに設定した通りにAZARASHI_ABCが削除されること、AZARASHI_TESTがセットされることを確認しましょう。
```
$ cd -
/Users/tsuyoshi/worknix
direnv: loading ~/worknix/.envrc
direnv: export +AZARASHI_TEST -AZARASHI_ABC
$ env | grep AZARASHI
AZARASHI_TEST=test
```

direnvを無効化したい場合には下記のコマンドを実行します。
```
$ direnv deny .
```

再度、有効にしたい場合には.envrcが存在するディレクトリで下記コマンドを実行します。
```
$ direnv allow
direnv: loading ~/worknix/.envrc
direnv: export +AZARASHI_TEST
$ env | grep -i AZARASHI
AZARASHI_TEST=test
```


注意点としては、.envrcはパスワードなどの機密情報を送る可能性があるので、必ずcommitしないようにします。


# TIPS
### 読み込むファイルについて
.envrcファイルまたは.envファイルが読み込まれます。両方が存在する場合には、.envrcファイルが優先とされます。
なお、.envファイルは.envrcファイルとは異なり、exportが不要で「KEY=VALUE」という指定ができます。


### direnv allowについて
.envrcは新規作成・編集後には一旦無効状態となるため、direnv allow .を実行して有効化する必要がある。


### gitに管理(commit)させない
個人だけの設定であれば
```
$ cat ~/.config/git/ignore
.envrc
.env
```

レポジトリでプロジェクトに共有しておきたければレポジトリ直下の.gitignoreファイルに記述しておけば良い。

### 親子のディレクトリで.envrcがそれぞれ存在する場合の挙動について
親子のディレクトリでそれぞれ.envrcが記述されているケース、子ディレクトリでは.envrcが存在しないケースについて確認します。

親ディレクトリの.envrcは下記の通りとする。
```
$ cat /path/to/.envrc
export TEST_AZARASHI=QOO
export TEST_LOCATION=NANKYOKU
```

上記の子ディレクトリである.envrcは下記の通りとする。
```
$ cat /path/to/foobar/.envrc
export TEST_HOGE=FUGA
export TEST_LOCATION=TOKYO
```

なお、/path/to/の子ディレクトリである/path/to/noexist/は.envrcを配置していないものとする。
```
$ ls /path/to/noexist/.envrc
ls: /path/to/noexist/.envrc: No such file or directory
```

この場合には、.envrcがあればそれが適用され、なければ親ディレクトリが適用されることになります。

```
$ cd /path/to/
$ env | grep -i TEST_
TEST_AZARASHI=QOO
TEST_LOCATION=NANKYOKU
```

```
$ cd /path/to/foobar/
$ env | grep -i TEST_
TEST_HOGE=FUGA
TEST_LOCATION=TOKYO
```

```
$ cd /path/to/noexist/
$ env | grep -i TEST
TEST_AZARASHI=QOO
TEST_LOCATION=NANKYOKU
```

### 親子のディレクトリで.envrcがそれぞれ存在する場合、親ディレクトリの環境変数情報をマージして適用したい
親ディレクトリの.envrcは下記の通りとする。
```
$ cat /path/to/.envrc
export TEST_AZARASHI=QOO
export TEST_LOCATION=NANKYOKU
```

上記の子ディレクトリである.envrcは下記の通りとする。なお、source_upは書く場所が大事です。記載されて以降からマージされます。
つまり、マージさせたくなければsource_upよりも後に記述すれば良いです。
```
$ cat /path/to/foobar/.envrc
export TEST_HOGE=FUGA
export TEST_LOCATION=TOKYO
source_up
```

その時の結果を確認してみます。子ディレクトリ側がTEST_AZARASHI環境変数も設定していることを確認できます。
```
$ cd /path/to/
$ env | grep -i TEST_
TEST_AZARASHI=QOO
TEST_LOCATION=NANKYOKU
```

```
$ cd /path/to/foobar/
$ env | grep -i TEST
TEST_AZARASHI=QOO
TEST_HOGE=FUGA
TEST_LOCATION=NANKYOKU
```


