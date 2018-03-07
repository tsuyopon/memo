# 概要
mod_coreについてまとめます。

# 詳細
### エラーログのレベルを変更したい
LogLevelのデフォルト値がwarnとなっている。
```
LogLevel warn
```

以下のレベルが指定できる。
```
 emerg       緊急事態で、Webサーバを使用できない状態
 alert       直ちに処置が必要
 crit        致命的な状態
 error       エラー状態
 warn        警告
 notice      正常だが重要な情報
 info        追加情報
 debug       デバッグレベルのメッセージ
```

### httpd.conf以外にもローカル設定ファイルの場所を定義したい
Includeを利用すればよい。
例えば、以下の様にhttpd.confを記述すると、/etc/apache/conf.d
ディレクトリ以下のファイルがapacheの再起動時に読み込まれることになる。
```
Include /etc/apache/conf.d
```

### Apacheでsyslogを利用したい
以下の1行を追記すればいい。
```
Errorlog syslog
```

### LocationディレクティブとDirectoryディレクティブの違い
- Directory: 指定のファイルシステムのディレクトリとサブディレクトリとのみに 適用されるディレクティブを囲む
- Location:  ファイルシステム外のコンテンツにディレクティブを適用するときに 使用してください

