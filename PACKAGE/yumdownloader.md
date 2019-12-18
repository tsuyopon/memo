# 概要
yumdownloaderはrpmパッケージをダウンロードする際に便利なツールです。
コマンドが入っていない場合には以下のコマンドでインストールしましょう。
```
$ sudo yum install yum-utils
```

yumでもdownloadonlyオプションなどがありますが、yumでのダウンロードの場合には依存を勝手に解決してくれてしまうのでcurl-1.0.0, openssl-0.98.0のように指定をしたとしてcurl-1.0.0がopenssl-1.0.1以上を要求していると勝手にcurl-1.0.0とopenssl-1.0.1を取得しようとするのでこのような使い勝手ではよろしくありません。


# 詳細

### 基本ダウンロード方法
```
$ yumdownloader curl          # 最新版をダウンロードしようとする
$ yumdownloader curl-1.0.0    # 1.0.0版をダウンロードしようとする
$ yumdownloader --enablerepo=updates-base  curl  # レポジトリを指定してダウンロードする
$ yumdownloader --disablerepo=updates-base curl  # 不要なレポジトリを指定してダウンロードする
$ yumdownloader --enablerepo=updates-base --disablerepo=* curl  # updates-baseのみ以外のレポジトリ以外からはcurlのダウンロードを許可しない
```

ソースコードを指定する場合にはsourceオプションを指定します。 
```
$ yumdownloader --source curl
```
上記により、(例) curl-7.29.0-51.el7.src.rpm のようなsrc.rpmファイルをダウンロードできます。src.rpmの展開方法は後述します。


### rpmパッケージを取得して、展開する
rpmをダウンロードする場合には次のようにします。destdirでダウンロード先を指定します。拡張子が.rpm隣っていることに注意すること
```
$ yumdownloader --destdir=/tmp httpd 
httpd-2.2.23-1.fc17.x86_64.rpm
```

rpmを展開するには
```
$ mkdir xxxx; cp *.rpm xxx; cd xxxx
$ rpm2cpio httpd-2.2.23-1.fc17.x86_64.rpm | cpio -idv
```

### ソースコードを取得したい
たとえば、mysqlのソースコードを取得したい場合
```
$ yumdownloader --source mysql-server-5.5.32-1.fc17.x86_64
$ ls
mysql-5.5.32-1.fc17.src.rpm
```

src.rpmに含まれるファイル一覧を表示する場合は次のコマンドで確認できる。
```
$ rpm2cpio mysql-5.5.32-1.fc17.src.rpm | cpio --list
```

src.rpmを展開するには次のようにする。
```
$ mkdir work
$ cd work/
$ rpm2cpio ../mysql-5.5.32-1.fc17.src.rpm | cpio -id
42555 blocks
$ ls
README.mysql-docs           mysql-chain-certs.patch      mysql-innodbwarn.patch    mysql-stack-guard.patch      mysqld-wait-ready
README.mysql-license        mysql-cipherspec.patch       mysql-install-test.patch  mysql-string-overflow.patch  mysqld.service
filter-requires-mysql.sh    mysql-dh1024.patch           mysql-logrotate.patch     mysql-strmov.patch           rh-skipped-tests-arm.list
generate-tarball.sh         mysql-dubious-exports.patch  mysql-man-gpl.tar.gz      mysql-va-list.patch          rh-skipped-tests-base.list
libmysql.version            mysql-embedded-check.c       mysql-netdevname.patch    mysql-versioning.patch       scriptstub.c
my.cnf                      mysql-errno.patch            mysql-plugin-bool.patch   mysql.spec
my_config.h                 mysql-expired-certs.patch    mysql-plugin-test.patch   mysql.tmpfiles.d
mysql-5.5.32-nodocs.tar.gz  mysql-file-contents.patch    mysql-s390-tsc.patch      mysqld-prepare-db-dir
$ tar zxvf mysql-5.5.32-nodocs.tar.gz
$ cd mysql
```
あとはこの中にソースコードが含まれているので適宜参照すればよい。


