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

### プログラムなどのファイルがどのパッケージに入っているのかを知りたい
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
--requiresは-Rと同じです。
yumコマンドでもyum -q deplistでも依存情報を確認することができます。
```
$ rpm -q --requires lv        // $ rpm -qR lv  と同じ
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

上記で表示されるファイルがすべて存在しなければインストール（アップデート）ができないので、その点は覚えておく必要があります。
上記の出力はファイル名やパッケージ名(バージョン指定)などが含まれています。

### コンフリクトするパッケージのリストを表示します
```
$ rpm -q --conflicts yum
pirut < 1.1.4
rpm >= 5-0
zif <= 0.1.3-3.fc15
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
rpmに関する設定は定義やマクロは以下で可能です
```
[rpmrc設定]
/usr/lib/rpm/rpmrc
/usr/lib/rpm/redhat/rpmrc
/etc/rpmrc
~/.rpmrc

[マクロ設定]
/usr/lib/rpm/macros
/usr/lib/rpm/redhat/macros
/etc/rpm/macros
~/.rpmmacros
```
- 上記参考
  - https://linuxjm.osdn.jp/html/rpm/man8/rpm.8.html


システムとしてどのような設定になっているのかはshowrcオプションで確認できます。
大量に出力されるので出力をtailで絞っているが、上記で設定された内容を出力している。
```
$ rpm --showrc | tail -30
%{nil}
-14: sysusers_create	
systemd-sysusers %{?*} >/dev/null 2>&1 || : 
%{nil}
-14: sysusers_create_inline	
echo %{?*} | systemd-sysusers - >/dev/null 2>&1 || : 
%{nil}
-14: tests_req	%{expand:
BuildRequires: %*
%%tests_subpackage_requires %*
}
-14: tests_subpackage_provides	%{expand: 
%global __tests_spkg_prov %{?__tests_spkg_prov} %* 
}
-14: tests_subpackage_requires	%{expand: 
%global __tests_spkg_req %{?__tests_spkg_req} %* 
}
-14: tmpfiles_create	
systemd-tmpfiles --create %{?*} >/dev/null 2>&1 || : 
%{nil}
-14: udev_hwdb_update	
udevadm hwdb --update >/dev/null 2>&1 || : 
%{nil}
-14: udev_rules_update	
udevadm control --reload >/dev/null 2>&1 || : 
%{nil}
-14: undefined	%{expand:%%{?%{1}:0}%%{!?%{1}:1}}
-14: with	%{expand:%%{?with_%{1}:1}%%{!?with_%{1}:0}}
-14: without	%{expand:%%{?with_%{1}:0}%%{!?with_%{1}:1}}
======================== active 427 empty 0
```

また、現在の値を知りたい場合には下記コマンド例の様にして確認することもできます。
```
$ rpm --eval %{_libdir}
```

### フォーマットを指定してパッケージ情報を参照する
```
$ rpm -qa --queryformat "%{NAME} %{ARCH}\n" openssl
openssl x86_64
```

### rpmインストール・アンインストール時に実行されるスクリプトを表示する
```
$ rpm -q --scripts dbus
preinstall scriptlet (using /bin/sh):
# Add the "dbus" user and group
/usr/sbin/groupadd -r -g 81 dbus 2>/dev/null || :
/usr/sbin/useradd -c 'System message bus' -u 81 -g 81 \
    -s /sbin/nologin -r -d '/' dbus 2> /dev/null || :
preuninstall scriptlet (using /bin/sh):

if [ $1 -eq 0 ] ; then 
        # Package removal, not upgrade 
        systemctl --no-reload disable stop dbus.service dbus.socket > /dev/null 2>&1 || : 
        systemctl stop stop dbus.service dbus.socket > /dev/null 2>&1 || : 
fi
postuninstall scriptlet (using /bin/sh):

systemctl daemon-reload >/dev/null 2>&1 || :
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


## まだインストールしていないrpmへの操作

基本的にはpオプションを指定するとパッケージファイルを指定することができます。

### rpmパッケージの情報を取得する

```
$ rpm -qpi httpd-2.2.23-1.fc17.x86_64.rpm 
Name        : httpd
Version     : 2.2.23
Release     : 1.fc17
Architecture: x86_64
Install Date: (not installed)
Group       : System Environment/Daemons
Size        : 3123824
License     : ASL 2.0
Signature   : RSA/SHA256, Thu Jan 31 09:34:23 2013, Key ID 50e94c991aca3465
Source RPM  : httpd-2.2.23-1.fc17.src.rpm
Build Date  : Tue Jan 29 21:38:27 2013
Build Host  : buildvm-07.phx2.fedoraproject.org
Relocations : (not relocatable)
Packager    : Fedora Project
Vendor      : Fedora Project
URL         : http://httpd.apache.org/
Summary     : Apache HTTP Server
Description :
The Apache HTTP Server is a powerful, efficient, and extensible
web server.

```

### config扱いとなっているファイルのみを表示する
```
$ rpm -qpc httpd-2.2.23-1.fc17.x86_64.rpm | tail -5
/var/www/error/HTTP_VARIANT_ALSO_VARIES.html.var
/var/www/error/contact.html.var
/var/www/error/include/bottom.html
/var/www/error/include/spacer.html
/var/www/error/include/top.html
```

文書ファイルのみを抽出もできる
```
$ rpm -qpd httpd-2.2.23-1.fc17.x86_64.rpm | tail -5
/usr/share/man/man8/httpd.event.8.gz
/usr/share/man/man8/httpd.worker.8.gz
/usr/share/man/man8/logresolve.8.gz
/usr/share/man/man8/rotatelogs.8.gz
/usr/share/man/man8/suexec.8.gz
```

### パッケージファイルが正常かどうかを確認する
```
$ rpm -K httpd-2.2.23-1.fc17.x86_64.rpm 
httpd-2.2.23-1.fc17.x86_64.rpm: rsa sha1 (md5) pgp md5 OK
```
### rpmに含まれるファイル一覧を取得する
```
$ rpm -qpl httpd-2.2.23-1.fc17.x86_64.rpm | head -5
/etc/httpd
/etc/httpd/conf
/etc/httpd/conf.d
/etc/httpd/conf.d/README
/etc/httpd/conf.d/welcome.conf
```

### rpmパッケージ内のファイルを全て展開する
rpmの展開は次のようにして行う。ディレクトリを新しく作ってその中で行うのが良いです。
```
$ mkdir xxxx; cp *.rpm xxx; cd xxxx
$ rpm2cpio httpd-2.2.23-1.fc17.x86_64.rpm | cpio -idv
```

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


### rpm周りのデバッグ情報を合わせて出力する(vvオプション)

どのようなコマンドに対してでも-vvオプションを付与することでrpmコマンドのデバッグ出力を表示することができるようです。
```
$ rpm -q -vv redis
D: loading keyring from pubkeys in /var/lib/rpm/pubkeys/*.key
D: couldn't find any keys in /var/lib/rpm/pubkeys/*.key
D: loading keyring from rpmdb
D: serialize failed, using private dbenv
D: opening  db environment /var/lib/rpm cdb:private:0x401
D: opening  db index       /var/lib/rpm/Packages 0x400 mode=0x0
D: locked   db index       /var/lib/rpm/Packages
D: opening  db index       /var/lib/rpm/Name 0x400 mode=0x0
D:  read h#     307 Header SHA1 digest: OK (489efff35e604042709daf46fb78611fe90a75aa)
D: added key gpg-pubkey-f4a80eb5-53a7ff4b to keyring
D:  read h#     409 Header SHA1 digest: OK (3c2f0e6784751b2e7879528410f408de6a6deb1e)
D: added key gpg-pubkey-34fa74dd-540237d4 to keyring
D:  read h#     421 Header SHA1 digest: OK (da1e8a96678f04aee5107687ba95bccb3105cbf7)
D: added key gpg-pubkey-f2ee9d55-560cfc0a to keyring
D:  read h#     443 Header SHA1 digest: OK (dd737a402556b7653c2bc971f343532046e26384)
D: added key gpg-pubkey-352c64e5-52ae6884 to keyring
D: Using legacy gpg-pubkey(s) from rpmdb
D:  read h#     445 Header V3 RSA/SHA256 Signature, key ID 352c64e5: OK
redis-3.2.12-2.el7.x86_64
D: closed   db index       /var/lib/rpm/Name
D: closed   db index       /var/lib/rpm/Packages
D: closed   db environment /var/lib/rpm
```

# Normative Ref
- RPM Documentation
  - 参考資料となるポインタへのリファレンスが多い
  - https://rpm.org/documentation.html
- Maximum RPM
  - rpmに関してはこれが一番良い資料かも
  - http://ftp.rpm.org/max-rpm/index.html
- Fedora Packaging/Guideline/ja(日本語)
  - https://fedoraproject.org/wiki/Packaging/Guidelines/ja
- Fedora draft Documentati0n
  - https://docs.fedoraproject.org/en-US/Fedora_Draft_Documentation/0.1/html/RPM_Guide/index.html
- RPM Packaging Guide
  - https://rpm-packaging-guide.github.io/
- RPM Packging Guide(SPHINX)
  - https://rpm-guide.readthedocs.io/en/latest/rpm-guide.html
- rpmコマンドソースコード(github)
  - https://github.com/rpm-software-management/rpm/blob/master/rpm.c

# Informative Ref
- RPMパッケージの管理に使うRPMコマンド使えるオプション一覧
  - http://jp.layer8.sh/reference/entry/show/id/662
- RPM Tips
  - http://www2.westwind.dyndns.org/contents/tips/rpm.html
- ITmedia RPMコマンドを使いこなしたい
  - http://www.itmedia.co.jp/help/tips/linux/l0052.html
