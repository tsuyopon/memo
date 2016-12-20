# 概要
rpmについてまとめる

# 詳細

## 基本操作

### あるパッケージのパッケージ名、バージョン番号、リビジョン番号を表示したい
```
$ rpm -q screen
```

### 現在のサーバ上に入っているパッケージをすべて表示したい
```
$ rpm -qa
```

これによりある特定のパッケージがサーバ上に入っているかどうかは 以下の様にして確認することができる。
```
$ rpm -qa | grep xxxx
```

最新のインストール順に並べたい場合には下記コマンドを実行します。
```
$ rpm -qa --last
```

### RPMパッケージの情報を表示したい
例えば、nagiosのパッケージ情報が知りたい場合には以下の様にすればよい。
```
$ rpm -qi nagios
Name        : nagios                       Relocations: (not relocatable)
Version     : 3.2.3                             Vendor: Dag Apt Repository, http://dag.wieers.com/apt/
Release     : 3.el5.rf                      Build Date: 2010年11月26日 23時48分20秒
Install Date: 2011年01月25日 09時19分25秒      Build Host: lisse.hasselt.wieers.com
Group       : Applications/System           Source RPM: nagios-3.2.3-3.el5.rf.src.rpm
Size        : 7710465                          License: GPL
Signature   : DSA/SHA1, 2010年11月27日 08時20分37秒, Key ID a20e52146b8d79e6
Packager    : Dag Wieers <dag@wieers.com>
URL         : http://www.nagios.org/
Summary     : Open Source host, service and network monitoring program
Description :
Nagios is an application, system and network monitoring application.
It can escalate problems by email, pager or any other medium. It is
also useful for incident or SLA reporting.

Nagios is written in C and is designed as a background process,
intermittently running checks on various services that you specify.

The actual service checks are performed by separate "plugin" programs
which return the status of the checks to Nagios. The plugins are
located in the nagios-plugins package.
```

### プログラムなどのファイルがどのパッケージに入っているのかを知りたい。 †
例えば、/etc/rc.d/init.d/httpdの場合には以下の様にする。
```
$ rpm -qf /etc/rc.d/init.d/httpd
apache-1.3.2
```

### パッケージに入っているファイルを全て表示したい
screenに入っているパッケージをすべて表示したい場合には以下の様にする。
```
$ rpm -ql screen
```

### パッケージに入っている設定用ファイルを全て表示したい
```
$ rpm -qc screen
/etc/pam.d/screen
/etc/screenrc
```

### パッケージに入っているドキュメントを全て表示したい
```
$ rpm -qd screen
/usr/share/doc/screen-4.0.3/FAQ
/usr/share/doc/screen-4.0.3/NEWS
/usr/share/doc/screen-4.0.3/README
/usr/share/doc/screen-4.0.3/README.DOTSCREEN
/usr/share/info/screen.info.gz
/usr/share/man/man1/screen.1.gz
```

### そのパッケージが依存するすべてのファイルを表示したい
たとえば、httpdパッケージの場合は以下の様にする。
```
$ rpm -qR httpd
```

### カレントディレクトリにあるインストール前のパッケージファイルの依存関係を表示したい。
```
$ rpm -qRp alien-7.24-3.noarch.rpm
```

### パッケージの変更履歴を表示したい
```
$ rpm -q --changlog apache
```

### そのパッケージが提供するライブラリ等を表示します
```
$ rpm -q --provides openssl
config(openssl) = 0.9.8b-8.3.el5
(中略)
libnuron.so
libssl.so.6
libsureware.so
libubsec.so
openssl = 0.9.8b-8.3.el5
```

### そのパッケージが必要とするライブラリ等を表示します
```
$ rpm -q --requires lv
libc.so.6
libc.so.6(GLIBC_2.0)
libc.so.6(GLIBC_2.1)
libc.so.6(GLIBC_2.2)
libc.so.6(GLIBC_2.3.4)
libc.so.6(GLIBC_2.4)
libtermcap.so.2
rpmlib(CompressedFileNames) <= 3.0.4-1
rpmlib(PartialHardlinkSets) <= 4.0.4-1
rpmlib(PayloadFilesHavePrefix) <= 4.0-1
rtld(GNU_HASH)
```

### 指定したパッケージを使っているパッケージリストを表示します
```
$ rpm -q --whatrequires httpd
piranha-0.8.4-7.el5
gnome-user-share-0.10-6.el5
(中略)
httpd-manual-2.2.17-jason.1
nagios-3.2.3-3.el5.rf
```

### RPMパッケージが欲しい
下記のサイトで探すと良い。
- http://www.rpmfind.net

### rpmが使用する全てのオプション・システム変数を表示したい
```
$ rpm --showrc
```

また、現在の値を知りたい場合には下記コマンド例の様にして確認することもできます。
```
$ rpm --eval %{_libdir}
```

## インストール

### ドライランを実行したい 
rpmオプションに「--test」を付加すればよい。

### パッケージインストールを行う 
以下は例です。
```
$ rpm -ivh package-1.0.0.i386.rpm
```

### パッケージアップデートを行う 
```
$ rpm -Uvh  screen-1.0.1.i386.rpm
```

### パッケージのダウングレードを行う 
```
$ rpm -i --oldpackage xxxxxx.rpm 
```

### 既にインストールされた他のパッケージのファイルを置き換えてしまう場合でも、パッケージをインストールしたい 
```
$ rpm -i --replacefiles mypackage.rpm
```

### (非推奨) パッケージの強制インストールを行う 
```
$ rpm -i --force xxxxxx.rpm 
```

## アンインストール

### パッケージの削除を行う
パッケージの削除はeオプションを付与する
```
$ rpm -e screen-1.0.1
```

依存関係を気にせずに行う(インストール時、アップグレード時、削除時すべてで利用可)
```
$ rpm -e -nodeps screen-1.0.1
```

### アンインストール前にテスト(ドラインラン)を行いたい
```
$ rpm -e --test httpd
```

アンインストール時に依存関係で怒られる場合にはFailed Dependenciesという表示が出力されます。 
また、正常にアンインストールできる場合には何も表示されません。 このオプションでは、-vvのデバッグ出力オプションと同時に利用するのが一般的です。


## TIPS

### インストールされているパッケージ中のファイルが正常かどうかを確認する
```
$ rpm -qs nagios | head -5
通常          /etc/httpd/conf.d/nagios.conf
通常          /etc/nagios
通常          /etc/nagios/cgi.cfg
通常          /etc/nagios/nagios.cfg
通常          /etc/nagios/objects
```

### rpmデータベースが壊れた場合の対処を行いたい
RPMには，パッケージ情報を管理しているデータベースがあります。   
このデータベースファイルを再構築するのが「rebuilddb」です。 怪しい挙動を示した際には以下のコマンドを実行すると解決することがあります。
```
$ rpm --rebuilddb
```

### 修正した可能性のあるパッケージをチェック
以下のコマンド例ではnagiosパッケージで修正したファイルを探して表示しています。
```
$ rpm -V nagios
S.5....T c /etc/httpd/conf.d/nagios.conf
.....UG.   /etc/nagios
..5....T c /etc/nagios/cgi.cfg
..?..... c /etc/nagios/resource.cfg
```

左側に表示されている８個の記号には意味があります。尚、その８個の記号の横の「c」はconfigという意味を表しています。
```
記号 	意味
S	ファイルサイズが異なっている
5	MD5チェックサムが異なる
L	シンボリックリンクが変更されている
T	ファイルの更新時刻が変更されている
D	デバイスファイルが変更されている
U	ファイルの所有者が変更されている
G	ファイルの所有グループが変更されている
M	ファイルのパーミッションが変更されている
?	未知または理由不明
```

### パッケージ自身の更新履歴が知りたい
パッケージを作った人々が残した更新履歴を閲覧することができます。
```
$ rpm -q --changelog nagios
* 金 11月 19 2010 Christoph Maser <cmaser@gmx.de> - 3.2.3-3
- adapt the extraction for nagios-imagepak-base from BSD

* 火 11月 09 2010 Christoph Maser <cmaser@gmx.de> - 3.2.3-2
- remove -p ${pidfile} from killproc in reload el4 killproc doesnot support -p

* 金 11月 05 2010 Christoph Maser <cmaser@gmx.de> - 3.2.3-1
- Updated to version 3.2.3.
- Use orignial init script on el3

* 火 10月 05 2010 Dag Wieers <dag@wieers.com> - 3.2.2-1
- Updated to release 3.2.2.
```


# 参考URL
- RPMパッケージの管理に使うRPMコマンド使えるオプション一覧
 - http://jp.layer8.sh/reference/entry/show/id/662
- RPM Tips
 - http://www2.westwind.dyndns.org/contents/tips/rpm.html
- ITmedia RPMコマンドを使いこなしたい
 - http://www.itmedia.co.jp/help/tips/linux/l0052.html