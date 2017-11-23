# 概要
opensslライブラリについて

# 詳細

### ソースコードからインストールする
至って標準的なインストール方法は以下の通り。make実行時に5〜10分ぐらいかかるかもしれない。
```
$ wget https://www.openssl.org/source/openssl-1.0.2m.tar.gz
$ tar zxvf openssl-1.0.2m.tar.gz 
$ cd openssl-1.0.2m/
$ ./config --prefix=/opt/openssl 
$ make
$ sudo make install
```

```
$ tree -d 3 /opt/openssl/ 
3 [error opening dir]
/opt/openssl/
├── bin
├── include
│   └── openssl
├── lib
│   ├── engines
│   └── pkgconfig
└── ssl
    ├── certs
    ├── man
    │   ├── man1
    │   ├── man3
    │   ├── man5
    │   └── man7
    ├── misc
    └── private

15 directories
```

### ビルドオプションを含めてソースコードからインストールする
折角のopenssl自前ビルドなのでデバッグオプションも含めて指定したくなります。

oepnsslのビルドオプションは以下の公式ドキュメントを参考のこと
- https://wiki.openssl.org/index.php/Compilation_and_Installation

```
$ wget https://www.openssl.org/source/openssl-1.0.2m.tar.gz
$ tar zxvf openssl-1.0.2m.tar.gz 
$ cd openssl-1.0.2m/
$ ./config --prefix=/opt/openssl-dbg --openssldir=/opt/openssl-dbg -d shared no-asm no-ssl2 -g3 -ggdb -gdwarf-4 -fno-inline -O0 -fno-omit-frame-pointer
$ make
$ sudo make install
```

configで指定しているオプションは次の通り
```
--prefix and --openssldir control the configuration of installed components
-d: Debug build of the library
share: Build a shared object in addition to the static archive
no-asm: Disables assembly language routines (and uses C routines)
no-ssl2: Disables SSLv2
no-ssl3: Disables SSLv3
-g3: Include extra debug information. Some debuggers support macro expansions when you use -g3
-ggdb3: Use most expressive format available to produce debugging information
-gdwarf-4: Produce debugging information in DWARF format (if that is supported). For more information, visit: debuggingwith attributedrecord formats
-fno-inline: Do not expand any functions inline apart from those marked with "always_inline" attribute
-O0: Reduce compilation time and make debugging produce the expected results
-fno-omit-frame-pointer: Omitting it makes debugging impossible on some machines (Recommended by official OpenSSL)
```

### libsslを使った場合にデフォルトで参照されるルート証明書について
libsslを使った場合のルート証明書はどこにあるのだろうか?
opensslからだと通常はSSL_CTX_set_cert_store()にて指定が行われているはずだが、これらがプログラム中からセットされていない場合には何が参照されるのだろうか?

実は特にAPIで指定されなければデフォルトで利用されるものが決まっています。
- https://github.com/openssl/openssl/blob/0e598a3d185e9bbfe1a513c05063970a1c532e23/include/internal/cryptlib.h#L58-L66

libopensslにはlibsslやlibcryptが含まれていますが、上記のOPENSSLDIRはビルド時のconfigureで指定するprefixやopenssldirで決定してきます。

ライブラリを確認するには次のようにしてパスを確認することが出来ます。
```
tsuyoshi@tsuyoshi:~:$ ldd /usr/bin/openssl
	linux-vdso.so.1 =>  (0x00007ffcd950d000)
	libssl.so.1.0.0 => /lib/x86_64-linux-gnu/libssl.so.1.0.0 (0x00007f55a848a000)
	libcrypto.so.1.0.0 => /lib/x86_64-linux-gnu/libcrypto.so.1.0.0 (0x00007f55a80a6000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f55a7cdb000)
	libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f55a7ad7000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f55a8702000)
tsuyoshi@tsuyoshi:~:$ strings /lib/x86_64-linux-gnu/libcrypto.so.1.0.0  | grep -i openssldir
OPENSSLDIR: "/usr/lib/ssl"
```

上記のパスから参照されるルート証明書は以下のパスとなることがわかります。
```
$ ls /usr/lib/ssl/certs
00673b5b.0  8470719d.0								TURKTRUST_Certificate_Services_Provider_Root_1.pem
024dc131.0  84cba82f.0								TURKTRUST_Certificate_Services_Provider_Root_2.pem
02b73561.0  85cde254.0								TURKTRUST_Certificate_Services_Provider_Root_2007.pem
```

例えば、rpm系パッケージの場合にはopensslパッケージとbundle.crtが含まれるca-certificateが同一のパスを指していたりします。

### 環境変数から証明書ディレクトリとファイル名を指定する
X509_CERT_DIR_EVP, X509_CERT_FILE_EVPといった環境変数を指定すれば良さそうだ
- https://github.com/openssl/openssl/blob/0e598a3d185e9bbfe1a513c05063970a1c532e23/include/internal/cryptlib.h#L74-L76
