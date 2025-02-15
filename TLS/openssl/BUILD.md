# 概要
opensslライブラリのソースコードからのコンパイル・インストール方法についてのメモ

詳細は以下のドキュメントがまとまっているのでこちらを参考にするとよいでしょう
- https://wiki.openssl.org/index.php/Compilation_and_Installation

なお、本手順はUbuntu-22.04で試したものです。

# ソースコードからのビルド手順

### 1系の手順
この手順では1.1.1bについてコンパイルする手順について記します。
```
$ git clone https://github.com/openssl/openssl.git
$ cd openssl
$ git checkout OpenSSL_1_1_1b
```

通常だと-gビルドしかされませんので、g3や00を付与して徹底的にデバッグに特化させましょう。
enable-ssl-traceオプションを付与することでs_clientのtraceオプションでデバッグ時に有用な情報が落ちるようになったりOSSL_trace_cbコールバックが利用できるようになるようです。
```
$ ./config --prefix=/opt/openssl-1.1.1 -d shared no-asm no-ssl2 -pg -g3 -ggdb -gdwarf-4 -fno-inline -O0 -fno-omit-frame-pointer enable-ssl-trace
```
- d: configへのオプションでデバッグを有効にします。
- pg: プログラムを実行した際にプロファイル用のファイルgmon.outを生成します
- g3: プログラムに存在するすべてのマクロ定義が含まれます。
- ggdb: gdbで利用するためのデバッグ情報を埋め込みます。gdbの拡張形式が使われる場合には多くの情報を提供する形式を生成します。
- O0: 最適化しません。
- fno-inline:
- fno-omit-frame-pointer: 
- gdwarf-4:

あとはコンパイルして、インストールするだけです。
```
$ make
$ sudo make install
```

### 3系の手順

1.1.1系の手順と変わりありませんが、コマンドを記載しておきます。
今回は3.4.1をビルドしています。

```
$ git clone https://github.com/openssl/openssl.git
$ cd openssl/
$ git checkout openssl-3.4.1
```

下記でコンパイルします。 オプションの説明は1系の手順側に記載していますのでそちらを参考にしてください。
3系だとconfigではなく、Configureを使うようですが、互換性のためにwrapperとしてconfigが残されているので今回はそちらで試しています。
```
$ ./config --prefix=/opt/openssl-1.1.1 -d shared no-asm no-ssl2 -pg -g3 -ggdb -gdwarf-4 -fno-inline -O0 -fno-omit-frame-pointer enable-ssl-trace
$ make
$ sudo make install
```

### 補足
なお「make install」せずに、opensslコマンドを実行するにはLD_LIBRARY_PATHでライブラリを指定して実行してください。
ライブラリはレポジトリ直下にあるので、LD_LIBRARY_PATHは.(ドット)を指定しています。
```
$ LD_LIBRARY_PATH=. ./apps/openssl s_client -connect www.google.com:443
```
