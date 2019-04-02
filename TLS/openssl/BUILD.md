# 概要
opensslライブラリのコンパイル・インストール方法について

詳細は以下のドキュメントがまとまっているのでこちらを参考にすること
- https://wiki.openssl.org/index.php/Compilation_and_Installation

# 手順
この手順では1.1.1bについてコンパイルする手順について記します。
```
$ git clone https://github.com/openssl/openssl.git
$ git checkout OpenSSL_1_1_1b
```

通常だと-gビルドしかされませんので、g3や00を付与して徹底的にデバッグに特化させましょう。
```
$ ./config --prefix=/opt/openssl-1.1.1 -d shared no-asm no-ssl2 -g3 -ggdb -gdwarf-4 -fno-inline -O0 -fno-omit-frame-pointer
```
- d: configへのオプションでデバッグを有効にします。
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
