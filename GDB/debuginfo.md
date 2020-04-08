# 概要
debuginfoは実行ファイルとは別のパスに配置されたデバッグ情報を参照することを許容するための仕組みです。


GDBは次の２つの方法をサポートしています。自分が知っている方式は前者のみ
- ELFにdebuglinkを含む場合。実行ファイルがhogehogeならば、分離されたデバッグファイルはhogehoge.debugとなります。
- ELFにbuild IDを含む場合

上記の理由からビルドした生成したdebuginfoのrpmと対応する実行プログラムが含まれたrpmは同時にインストールしないとGDBにデバッグ情報が認識されないので注意が必要です。


# 詳細

### gdb利用中にdebuginfoが利用されたかどうか知りたい
info sharedを実行して読み込んだライブラリの横に(\*)が存在する場合には、debuginfoが読み込まれていないことになります。
gdb起動時などにもdebug symbol not foundのような表示が表示されるかと思います。
```
Breakpoint 1, 0x00000000004028c0 in main ()
(gdb) info shared
From                To                  Syms Read   Shared Object Library
0x00007ffff7ddbad0  0x00007ffff7df6f80  Yes         /lib64/ld-linux-x86-64.so.2
0x00007ffff7bba9d0  0x00007ffff7bd07d6  Yes (*)     /lib64/libselinux.so.1
0x00007ffff79b0620  0x00007ffff79b1e56  Yes (*)     /lib64/libcap.so.2
0x00007ffff77a7f80  0x00007ffff77abda1  Yes (*)     /lib64/libacl.so.1
0x00007ffff73f8930  0x00007ffff7547d2f  Yes         /lib64/libc.so.6
0x00007ffff71785f0  0x00007ffff71be5b0  Yes (*)     /lib64/libpcre.so.1
0x00007ffff6f73d90  0x00007ffff6f7488e  Yes         /lib64/libdl.so.2
0x00007ffff6d6f3d0  0x00007ffff6d7140a  Yes (*)     /lib64/libattr.so.1
0x00007ffff6b578b0  0x00007ffff6b62d51  Yes         /lib64/libpthread.so.0
(*): Shared library is missing debugging information.
```

# 参考URL
- Debugging Information in Separate Files
  - https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/4/html/Debugging_with_gdb/separate-debug-files.html
- https://stackoverflow.com/questions/866721/how-to-generate-gcc-debug-symbol-outside-the-build-target

