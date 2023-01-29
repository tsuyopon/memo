# 概要
簡易FTPサーバの構築と簡単な使い方

# 構築(Ubuntu22.04)
下記で必要なパッケージをインストールします。
```
$ sudo apt install vsftpd
```

Ubuntu 22.04.1 LTS
デフォルトだと/etc/vsftpd.confの
write_enable=YES
が有効になっていないのでコメントを外して有効にします。

その後、下記で起動します。
```
$ sudo systemctl enable vsftpd
$ sudo systemctl restart vsftpd
```

# 簡単な使い方
下記でFTPにログインします。
```
$ ftp ubuntu
Connected to ubuntu.
220 (vsFTPd 3.0.5)
Name (ubuntu:tsuyoshi): 
331 Please specify the password.
Password: 
230 Login successful.
```

データを一括でインストールしたい場合には、特定のディレクトリに移動して「mput」を実行します。
あらかじめ「prompt」を実行しておかないと、毎回インタラクティブに実行するかどうかを尋ねられてしまうので、一括で許可したい場合には「prompt」をあらかじめ実行しておきます。
```
ftp> cd data
250 Directory successfully changed.
ftp> prompt
Interactive mode off.
ftp> mput *.log
```
