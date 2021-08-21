# 概要
Rustの初期セットアップ

これはMacOS CatallinaからRustをセットアップした際の記録です。

# 詳細

### パッケージのインストール
```
$curl https://sh.rustup.rs -sSf | sh
(snip)
1) Proceed with installation (default)
2) Customize installation
3) Cancel installation
>1                               # 1を入れてエンター
(snip)

  stable-x86_64-apple-darwin installed - rustc 1.54.0 (a178d0322 2021-07-26)


Rust is installed now. Great!

To get started you may need to restart your current shell.
This would reload your PATH environment variable to include
Cargo's bin directory ($HOME/.cargo/bin).

To configure your current shell, run:
source $HOME/.cargo/env
```

続いて以下の設定を行います。毎回設定するのも面倒なので.bash_profileに記述しておくのが良いでしょう。
```
$ source $HOME/.cargo/env
$ export PATH="$HOME/.cargo/bin:$PATH"
```

### HelloWorldプログラム
以下のサンプルを用意します。
```
$ cat main.rs 
fn main() {
    println!("Hello, world!");
}
```

コンパイルして実行します
```
$ rustc main.rs
$ ./main
Hello, world!
```

# 参考資料
- RUSTの環境構築とHello,world!について
  - https://qiita.com/Veritas666777/items/c01a0df0c9b97f6b2a95
