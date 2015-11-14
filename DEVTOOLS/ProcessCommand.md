
*** 特定のプロセス名のpidを取得する。
例えばhttpdのpidを取得する場合

```
$ pidof httpd
6924 6923 6922 6921 6920 6919 6918 6917 2050
```

複数のプロセスを同時にstraceするには以下のコマンドを実行します。
```
$ sudo sudo strace -tt -T -p <pid1つめ> -p <pid２つめ>
```

マルチスレッドなプログラムあるいは当該プロセスが今後作成する子プロセスを含めて対象にする場合には
-f というオプションを指定します。rsyslogdはマルチスレッドで動作するので以下のように指定します。
```
# strace -tt -T -f -p `pidof rsyslogd`
```

- 参考URL
 - http://www.intellilink.co.jp/article/column/oss11.html
