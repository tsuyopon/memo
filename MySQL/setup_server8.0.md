# 概要
Mysql Server8.0に関するセットアップ手順についてまとめる

# 詳細

### 外部環境に接続していないお試し環境として作成するMySQLの例
本当にお試しで何かのコンポーネントを試してみたいといったときに、MySQLではまりたくありません。
外部に接続されていない安全な環境でMySQL Serverを使って何かを試してみたいといった場合の構築手順です。


今回の手順は以下の環境で構築することを前提とします。
```
$ cat /etc/lsb-release
DISTRIB_ID=Ubuntu
DISTRIB_RELEASE=20.04
DISTRIB_CODENAME=focal
DISTRIB_DESCRIPTION="Ubuntu 20.04.3 LTS"
```

MySQL Server 8.0をインストールします。
```
$ sudo apt-get -y install mysql-server-8.0
```

MySQLの初期設定はmysql_secure_installationを使って行います。
```
$ sudo mysql_secure_installation

Securing the MySQL server deployment.

Connecting to MySQL using a blank password.

VALIDATE PASSWORD COMPONENT can be used to test passwords
and improve security. It checks the strength of password
and allows the users to set only those passwords which are
secure enough. Would you like to setup VALIDATE PASSWORD component?

Press y|Y for Yes, any other key for No: n                                 // パスワード品質チェックを有効にするか否か: nを入力する
Please set the password for root here.

New password:                                                              // 適当に"password"と入力

Re-enter new password:              
By default, a MySQL installation has an anonymous user,
allowing anyone to log into MySQL without having to have
a user account created for them. This is intended only for
testing, and to make the installation go a bit smoother.
You should remove them before moving into a production
environment.

Remove anonymous users? (Press y|Y for Yes, any other key for No) : n                    // 匿名ユーザーを削除するか否か

 ... skipping.


Normally, root should only be allowed to connect from
'localhost'. This ensures that someone cannot guess at
the root password from the network.

Disallow root login remotely? (Press y|Y for Yes, any other key for No) : n              // root ユーザーのリモートログインを無効とするか否か

 ... skipping.
By default, MySQL comes with a database named 'test' that
anyone can access. This is also intended only for testing,
and should be removed before moving into a production
environment.


Remove test database and access to it? (Press y|Y for Yes, any other key for No) : n     // テストデータベースを削除するか否か

 ... skipping.
Reloading the privilege tables will ensure that all changes
made so far will take effect immediately.

Reload privilege tables now? (Press y|Y for Yes, any other key for No) : y               // 特権情報をリロードするか否か
Success.

All done! 
```

接続を行います。rootへの接続の場合には、sudoを付与しないとパスワードが正しくても下記のエラーが表示されますので注意してください
```
$ mysql -uroot -p
Enter password: 
ERROR 1698 (28000): Access denied for user 'root'@'localhost'
```

以下でパスワードを「password」と入力すれば良いです。
```
$ sudo mysql -u root -p
```

### 停止と開始と再起動
```
systemctl start mysql
systemctl stop mysql
systemctl restart mysql
```


### MySQL Server8.0を削除する

パスワードを忘れてしまったのでMySQL Server8.0を削除する。
```
$ sudo apt-get remove --purge mysql-server* mysql-common
$ sudo apt-get autoremove --purge
$ sudo rm -r /etc/mysql
$ sudo rm -r /var/lib/mysql
```

- cf: https://qiita.com/King_kenshi/items/b6f217a8a3083c98904b
