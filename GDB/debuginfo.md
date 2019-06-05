# 概要
debuginfoは実行ファイルとは別のパスに配置されたデバッグ情報を参照することを許容するための仕組みです。


GDBは次の２つの方法をサポートしています。自分が知っている方式は前者のみ
- ELFにdebuglinkを含む場合。実行ファイルがhogehogeならば、分離されたデバッグファイルはhogehoge.debugとなります。
- ELFにbuild IDを含む場合

上記の理由からビルドした生成したdebuginfoのrpmと対応する実行プログラムが含まれたrpmは同時にインストールしないとGDBにデバッグ情報が認識されないので注意が必要です。


# 参考URL
- Debugging Information in Separate Files
  - https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/4/html/Debugging_with_gdb/separate-debug-files.html
- https://stackoverflow.com/questions/866721/how-to-generate-gcc-debug-symbol-outside-the-build-target


