# 概要
opensslライブラリについて

# 詳細

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
