# 概要
yumコマンドやレポジトリ関連の設定確認・作成・更新・変更などの操作について。
yumdownloader自体はyum-utilsパッケージに入っています。

# 詳細

## 基本操作

### パッケージやパッケージグループなどの表示
- 全ての利用可能なパッケージの一覧を表示する
```
$ yum list bind*
```

- システムにインストール済みのすべてのパッケージ一覧を表示する。
```
$ yum list installed php
```

- レポジトリ上の利用可能なパッケージ一覧を表示する
```
$ yum list available php
```

- 全てのパッケージグループを一覧表示する
```
$ yum grouplist
```

### パッケージを検索し、インストールする
```
$ yum search <pkgname>
$ yum install <pkgname>
```

### グループパッケージを検索し、インストールする
パッケージグループの確認は次のようにして行います。
```
$ yum -v grouplist FTP*
Loading "auto-update-debuginfo" plugin
Not loading "blacklist" plugin, as it is disabled
Loading "fastestmirror" plugin
Loading "langpacks" plugin
Loading "presto" plugin
Loading "refresh-packagekit" plugin
Not loading "whiteout" plugin, as it is disabled
Adding en to language list
Config time: 0.027
Yum Version: 3.4.3
Setting up Package Sacks
rpmdb time: 0.000
Found 15 installed debuginfo package(s)
Enabling fedora-debuginfo: Fedora 17 - x86_64 - Debug
Enabling updates-debuginfo: Fedora 17 - x86_64 - Updates - Debug
Loading mirror speeds from cached hostfile
 * fedora: ftp.iij.ad.jp
 * fedora-debuginfo: ftp.iij.ad.jp
 * updates: ftp.iij.ad.jp
 * updates-debuginfo: ftp.iij.ad.jp
pkgsack time: 0.427
group time: 0.771
Available Groups:
   FTP Server (ftp-server)
Done
```

上記の()内がgroupinstallの引数として指定するグループIDとなります。
つまり、上記の例ではftp-serverとなります。
```
// グループパッケージのインストール
$ yum groupinstall ftp-server
```

### ファイル名を元にしてパッケージをインストール
```
$ yum install /usr/bin/php
```

### アップデート可能なパッケージを確認したい場合
```
$ yum check-update       // アップデート可能なパッケージを確認する
```

特定のパッケージだけを指定したい場合には引数にパッケージ名を指定します
```
$ yum check-update php
```

### アップデートしたい
```
// 全パッケージのアップデート
$ yum update

// 特定のパッケージのアップデート
$ yum update php
```

### グループパッケージをアップデートしたい
```
$ yum -v grouplist FTP*       // 対象を確認。ここでftp-serverを得る
$ yum groupupdate ftp-server  // baseの部分はパッケージグループ
```

### 例えば、php関連を除いてアップデートしたい場合
コマンドで実行する場合には次のようにします。
```
$ yum update --exclude=php*
```

自動アップデートなどでkernelが自動アップデートされるのを防ぐためには
/etc/yum.confに次の箇所を追加するとyum -y updateでも自動的にupdateされなくなります。
```
[main]
...
exclude=kernel*
```

- 参考
  - http://www.8wave.net/yum.html

### 不要なパッケージを丸ごと削除する
例えば、rubyとその他に依存しない関連パッケージを除去するにはremoveを実行します。ruby関連のパッケージであれば「ruby*」といった正規表現指定も可能です。
```
$ sudo yum remove ruby
```

グループパッケージの削除は次のようにします。以下はFTPの場合の例です。
```
$ yum -v grouplist FTP*
$ yum groupremove ftp-server
```


### 古いパッケージをインストールする場合(downgrade)

例えば、以下のように最新版がインストールされてsystemtapが使えないような場合、
```
$ uname -r
3.3.4-5.fc17.x86_64
$ rpm -qa | grep -i kernel-debug
kernel-debuginfo-common-x86_64-3.9.10-100.fc17.x86_64
kernel-debuginfo-3.9.10-100.fc17.x86_64
```

このサーバに古いパッケージをインストールする場合には次のようにdowngradeでバージョンを指定すると良い
```
$ sudo yum downgrade kernel-debuginfo-common-x86_64-3.3.4-5.fc17.x86_64 kernel-debuginfo-3.3.4-5.fc17.x86_64
```

### ファイル名やコマンド名からそのファイルを提供しているパッケージを確認する
該当のパッケージを表示してくれます。
```
$ yum provides php
Loaded plugins: auto-update-debuginfo, fastestmirror, langpacks, presto, refresh-packagekit
Loading mirror speeds from cached hostfile
 * fedora: ftp.iij.ad.jp
 * fedora-debuginfo: ftp.iij.ad.jp
 * updates: ftp.iij.ad.jp
 * updates-debuginfo: ftp.iij.ad.jp
php-5.4.1-1.fc17.i686 : PHP scripting language for creating dynamic web sites
Repo        : fedora

php-5.4.1-1.fc17.x86_64 : PHP scripting language for creating dynamic web sites
Repo        : fedora

php-5.4.17-2.fc17.x86_64 : PHP scripting language for creating dynamic web sites
Repo        : updates

php-5.4.17-2.fc17.x86_64 : PHP scripting language for creating dynamic web sites
Repo        : @updates
```

たとえば、*statという名称のコマンドやファイルを含むパッケージを抽出するのであれば次のように正規表現も使えます。
```
$ yum provides *stat
```

### パッケージ情報を表示する
次のようにyum infoを利用します。引数には正規表現を利用することも可能です。
```
$ yum info screen
Loaded plugins: auto-update-debuginfo, fastestmirror, langpacks, presto, refresh-packagekit
(snip)
Installed Packages
Name        : screen
Arch        : x86_64
Version     : 4.1.0
Release     : 0.9.20120314git3c2946.fc17
Size        : 872 k
Repo        : installed
From repo   : fedora
Summary     : A screen manager that supports multiple logins on one terminal
URL         : http://www.gnu.org/software/screen
License     : GPLv2+
Description : The screen utility allows you to have multiple logins on just one
            : terminal. Screen is useful for users who telnet into a machine or are
            : connected via a dumb terminal, but want to use more than just one
            : login.
            : 
            : Install the screen package if you need a screen manager that can
            : support multiple logins on one terminal.
```

### パッケージに依存する情報を表示する
```
$ yum deplist screen
Loaded plugins: auto-update-debuginfo, fastestmirror, langpacks, presto, refresh-packagekit
Loading mirror speeds from cached hostfile
 * fedora: ftp.iij.ad.jp
 * fedora-debuginfo: ftp.iij.ad.jp
 * updates: ftp.iij.ad.jp
 * updates-debuginfo: ftp.iij.ad.jp
package: screen.x86_64 4.1.0-0.9.20120314git3c2946.fc17
  dependency: /bin/sh
   provider: bash.x86_64 4.2.39-3.fc17
  dependency: /sbin/install-info
   provider: info.x86_64 4.13a-16.fc17
  dependency: /usr/sbin/groupadd
   provider: shadow-utils.x86_64 2:4.1.5.1-2.fc17
  dependency: libc.so.6(GLIBC_2.15)(64bit)
   provider: glibc.x86_64 2.15-59.fc17
  dependency: libcrypt.so.1()(64bit)
   provider: glibc.x86_64 2.15-59.fc17
  dependency: libcrypt.so.1(GLIBC_2.2.5)(64bit)
   provider: glibc.x86_64 2.15-59.fc17
  dependency: libpam.so.0()(64bit)
   provider: pam.x86_64 1.1.5-7.fc17
  dependency: libpam.so.0(LIBPAM_1.0)(64bit)
   provider: pam.x86_64 1.1.5-7.fc17
  dependency: libtinfo.so.5()(64bit)
   provider: ncurses-libs.x86_64 5.9-11.20130511.fc17
  dependency: libutempter.so.0()(64bit)
   provider: libutempter.x86_64 1.1.5-6.fc17
  dependency: rtld(GNU_HASH)
   provider: glibc.x86_64 2.15-59.fc17
   provider: glibc.i686 2.15-59.fc17

```

### キャッシュ削除など
通常キャッシュは/var/cache/yumに溜まるようだ。yum clean allを実行すると(全てが消えるわけではないようだが)多くのキャッシュが消えるようだ。
```
$  du -sh /var/cache/yum
618M	/var/cache/yum
$ sudo yum clean all
$  du -sh /var/cache/yum
181M	/var/cache/yum
```

- http://easyramble.com/yum-clean-and-update.html

### アップデート時のログについて
```
$ less /var/log/yum.log
```

### インストール履歴を確認する
履歴一覧は次のコマンドで表示できる。sudoが必要なのに注意すること。
```
$ sudo yum history
Loaded plugins: auto-update-debuginfo, fastestmirror, langpacks, presto, refresh-packagekit
ID     | Command line             | Date and time    | Action(s)      | Altered
-------------------------------------------------------------------------------
   114 | install boost141.x86_64  | 2017-04-23 03:59 | Install        |   13   
   113 | install boost141-date-ti | 2017-04-23 03:58 | Install        |    1   
   112 | install php-phpunit-PHPU | 2017-04-11 09:25 | Install        |   19   
   111 | install zeromq3 zeromq3- | 2016-12-30 22:53 | Install        |    3   
   110 | downgrade kernel-debugin | 2016-12-30 20:50 | Downgrade      |    2   
   109 | install systemtap system | 2016-12-30 20:42 | I, U           |    7   
   108 | install mysql-debuginfo  | 2016-12-30 19:55 | Install        |    1   
   107 | install rpcbind          | 2016-12-30 08:34 | Install        |    3   
   106 | install fuse-devel       | 2016-12-29 08:11 | I, U           |    2   
   105 | install cmake -y         | 2016-12-29 07:56 | Install        |    1   
   104 | install rpc2-devel       | 2016-12-28 12:47 | Install        |    4   
   103 | install inotify-tools -y | 2016-12-28 07:26 | Install        |    1   
   102 | install golang-vim       | 2016-12-25 21:21 | Install        |    1   
   101 | install golang           | 2016-12-25 21:21 | Install        |    1   
   100 | install htop             | 2016-12-10 20:02 | Install        |    1   
    99 | install scl-utils        | 2016-12-08 02:37 | Install        |    1   
    98 | install node node-debugi | 2016-12-06 19:45 | Install        |    1   
    97 | install node             | 2016-12-06 18:47 | Install        |    3   
    96 | install wireshark        | 2016-12-03 09:47 | Install        |    3   
    95 | install libpcap-devel    | 2016-11-13 06:33 | Install        |    1   
history list
```

そしてhistory infoで番号をその後に指定すると該当の処理を確認することができます。
```
$ sudo yum history info 114
Loaded plugins: auto-update-debuginfo, fastestmirror, langpacks, presto, refresh-packagekit
Transaction ID : 114
Begin time     : Sun Apr 23 03:59:39 2017
Begin rpmdb    : 1432:207915feefd75b5de2989dcac51a425e3c146306
End time       :            03:59:41 2017 (2 seconds)
End rpmdb      : 1445:1b07a252b320f1b7f4e358409f24b1909bb3b8be
User           : Azrashi <tsuyoshi>
Return-Code    : Success
Command Line   : install boost141.x86_64
Transaction performed with:
    Installed     rpm-4.9.1.3-8.fc17.x86_64                              @updates
    Installed     yum-3.4.3-31.fc17.noarch                               @updates
    Installed     yum-plugin-auto-update-debug-info-1.1.31-4.fc17.noarch @fedora
    Installed     yum-plugin-fastestmirror-1.1.31-4.fc17.noarch          @fedora
Packages Altered:
    Install     boost141-1.41.0-2.fc17.x86_64                 @fedora
    Dep-Install boost141-filesystem-1.41.0-2.fc17.x86_64      @fedora
    Dep-Install boost141-graph-1.41.0-2.fc17.x86_64           @fedora
    Dep-Install boost141-iostreams-1.41.0-2.fc17.x86_64       @fedora
    Dep-Install boost141-program-options-1.41.0-2.fc17.x86_64 @fedora
    Dep-Install boost141-python-1.41.0-2.fc17.x86_64          @fedora
    Dep-Install boost141-regex-1.41.0-2.fc17.x86_64           @fedora
    Dep-Install boost141-serialization-1.41.0-2.fc17.x86_64   @fedora
    Dep-Install boost141-signals-1.41.0-2.fc17.x86_64         @fedora
    Dep-Install boost141-system-1.41.0-2.fc17.x86_64          @fedora
    Dep-Install boost141-test-1.41.0-2.fc17.x86_64            @fedora
    Dep-Install boost141-thread-1.41.0-2.fc17.x86_64          @fedora
    Dep-Install boost141-wave-1.41.0-2.fc17.x86_64            @fedora
history info
```

### 履歴からロールバックする
さらに履歴からロールバックをすることもできます。
```
$ sudo yum history rollback 110
```

### 特定のパッケージについて調査する
特定のパッケージのインストール情報を確認するにはyum history packge-listでその後にパッケージ名を指定します。
```
$ sudo yum history packages-list openssh
Loaded plugins: auto-update-debuginfo, fastestmirror, langpacks, presto, refresh-packagekit
ID     | Action(s)      | Package                                              
-------------------------------------------------------------------------------
     6 | Updated        | openssh-5.9p1-22.fc17.x86_64                         
     6 | Update         |         5.9p1-27.fc17.x86_64                         
     1 | Dep-Install    | openssh-5.9p1-22.fc17.x86_64                         
history packages-list
```

特定のパッケージの情報を確認したい場合には次のようにします。
```
$ sudo yum history packages-info openssh-5.9p1-22.fc17.x86_64
Loaded plugins: auto-update-debuginfo, fastestmirror, langpacks, presto, refresh-packagekit
Transaction ID : 6
Begin time     : Sat Dec  1 14:42:38 2012
Package        : openssh-5.9p1-22.fc17.x86_64
State          : Updated
Size           : 793906
Build host     : x86-16.phx2.fedoraproject.org
Build time     : Sat Apr  7 04:26:26 2012
Packager       : Fedora Project
Vendor         : Fedora Project
License        : BSD
URL            : http://www.openssh.com/portable.html
Source RPM     : openssh-5.9p1-22.fc17.src.rpm
Commit Time    : Fri Apr  6 21:00:00 2012
Committer      : Petr Lautrbach <plautrba@redhat.com>
Reason         : dep
From repo      : koji-override-0
Installed by   : System <unset>

Transaction ID : 1
Begin time     : Wed May 23 05:39:48 2012
Package        : openssh-5.9p1-22.fc17.x86_64
State          : Dep-Install
Size           : 793906
Build host     : x86-16.phx2.fedoraproject.org
Build time     : Sat Apr  7 04:26:26 2012
Packager       : Fedora Project
Vendor         : Fedora Project
License        : BSD
URL            : http://www.openssh.com/portable.html
Source RPM     : openssh-5.9p1-22.fc17.src.rpm
Commit Time    : Fri Apr  6 21:00:00 2012
Committer      : Petr Lautrbach <plautrba@redhat.com>
Reason         : dep
From repo      : koji-override-0
Installed by   : System <unset>
history packages-info

```

### yum summaryを表示する。
```
$ sudo yum history summary
Loaded plugins: auto-update-debuginfo, fastestmirror, langpacks, presto, refresh-packagekit
Login user                 | Time                | Action(s)        | Altered 
-------------------------------------------------------------------------------
Azrashi <tsuyoshi>  | Last day            | Install          |       14
Azrashi <tsuyoshi>  | Last 2 weeks        | Install          |       19
Azrashi <tsuyoshi>  | Last 6 months       | D, I, U          |       41
Azrashi <tsuyoshi>  | Last year           | I, U             |       25
System <unset>             | Over a year ago     | Install          |     1089
Azrashi <tsuyoshi>  | Over a year ago     | E, I, U          |      371
history summary
```

### yumリポジトリ一追加リスト 完全版
- http://qiita.com/bezeklik/items/9766003c19f9664602fe

### yumdownloaderでソースコードを取得したい(rpm.mdと重複)
たとえば、mysqlのソースコードを取得したい場合には次のようにします。拡張子が.src.rpmとなっていることに注意すること
```
$ yumdownloader --source mysql-server-5.5.32-1.fc17.x86_64
$ ls
mysql-5.5.32-1.fc17.src.rpm
```

src.rpmに含まれるファイル一覧を表示する場合は次のコマンドで確認できる。
```
$ rpm2cpio mysql-5.5.32-1.fc17.src.rpm | cpio --list
```

### yumdownloaderでrpmパッケージを取得して、展開する
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


## レポジトリ関連

### 普段利用しないレポジトリから取得したい場合
/etc/yum.repos.d/xxx.repoにはenabled=0の設定で記述されているが、一時的にそのレポジトリから取得したい場合には次のようにします。
hogerepoという普段使わないレポジトリからmypackageを取得する場合は次のコマンドとなる。

```
// install
$yum --enablerepo='hogerepo' install mypackage

// update
$yum --enablerepo='hogerepo' update mypackage
```

### 特定のレポジトリから一時的に取得しないようにする
```
// install
$yum --disablerepo='hogerepo' install mypackage

// update
$yum --disablerepo='hogerepo' update mypackage
```

### 特定のレポジトリだけを動作対象としたい場合
```
$ yum --disablerepo=* --enablerepo=rpmforge repolist
```

### 参照可能なレポジトリ数を表示する
```
$ yum repolist all
repolist: 0
```

### 有効なレポジトリ、無効なレポジトリを表示する。

- 有効なレポジトリを表示する
```
$ yum repolist enabled
Loaded plugins: auto-update-debuginfo, fastestmirror, langpacks, presto, refresh-packagekit
Loading mirror speeds from cached hostfile
 * fedora: ftp.iij.ad.jp
 * fedora-debuginfo: ftp.iij.ad.jp
 * updates: ftp.iij.ad.jp
 * updates-debuginfo: ftp.iij.ad.jp
repo id                                                                repo name                                                                        status
fedora/17/x86_64                                                       Fedora 17 - x86_64                                                               27033
fedora-debuginfo/17/x86_64                                             Fedora 17 - x86_64 - Debug                                                        5919
updates/17/x86_64                                                      Fedora 17 - x86_64 - Updates                                                     13163
updates-debuginfo/17/x86_64                                            Fedora 17 - x86_64 - Updates - Debug                                              2446
repolist: 48561
```

- 無効なレポジトリを表示する
```
$ yum repolist disabled
Loaded plugins: auto-update-debuginfo, fastestmirror, langpacks, presto, refresh-packagekit
repo id                                                                  repo name
epel/x86_64                                                              EPEL RPM Repository for Red Hat Enterprise Linux
fedora-debuginfo/17/x86_64                                               Fedora 17 - x86_64 - Debug
fedora-source/17/x86_64                                                  Fedora 17 - Source    
updates-debuginfo/17/x86_64                                              Fedora 17 - x86_64 - Updates - Debug
updates-source/17/x86_64                                                 Fedora 17 - Updates Source
updates-testing/17/x86_64                                                Fedora 17 - x86_64 - Test Updates
updates-testing-debuginfo/17/x86_64                                      Fedora 17 - x86_64 - Test Updates Debug
updates-testing-source/17/x86_64                                         Fedora 17 - Test Updates Source
repolist: 0
```

### レポジトリの詳細な情報を表示する
詳細な情報を出力するには次のコマンドを実行します。  
下記の引数で「all」の部分を例えば「base」に差し替えるとbaseレポジトリから取得する。
```
$ yum repolist all -v
(snip)
Setting up Package Sacks
pkgsack time: 0.057
Repo-id      : epel/x86_64
Repo-name    : EPEL RPM Repository for Red Hat Enterprise Linux
Repo-status  : disabled
Repo-baseurl : http://ftp.riken.jp/Linux/fedora/epel/6/x86_64/
Repo-expire  : 21600 second(s) (last: Thu Dec  8 02:47:43 2016)
Repo-filename: ///etc/yum.repos.d/epel.repo

Repo-id      : fedora/17/x86_64
Repo-name    : Fedora 17 - x86_64
Repo-status  : enabled
Repo-revision: 1337941209
Repo-tags    : binary-x86_64
Repo-distro-tags: [cpe:/o:fedoraproject:fedora:17]: r
Repo-updated : Fri May 25 19:39:56 2012
Repo-pkgs    : 27033
Repo-size    : 27 G
Repo-metalink: https://mirrors.fedoraproject.org/metalink?repo=fedora-17&arch=x86_64
  Updated    : Fri May 25 19:39:56 2012
Repo-baseurl : http://ftp.iij.ad.jp/pub/linux/Fedora/archive/fedora/linux/releases/17/Everything/x86_64/os/ (6 more)
Repo-expire  : 604800 second(s) (last: Wed Sep 20 08:17:39 2017)
Repo-filename: ///etc/yum.repos.d/fedora.repo

Repo-id      : fedora-debuginfo/17/x86_64
Repo-name    : Fedora 17 - x86_64 - Debug
Repo-status  : enabled
Repo-revision: 1337934684
Repo-tags    : debuginfo-x86_64
Repo-distro-tags: [cpe:/o:fedoraproject:fedora:17]: r
Repo-updated : Fri May 25 17:34:00 2012
Repo-pkgs    : 5919
Repo-size    : 17 G
Repo-metalink: https://mirrors.fedoraproject.org/metalink?repo=fedora-debug-17&arch=x86_64
  Updated    : Fri May 25 17:34:00 2012
Repo-baseurl : http://ftp.iij.ad.jp/pub/linux/Fedora/archive/fedora/linux/releases/17/Everything/x86_64/debug/ (5 more)
Repo-expire  : 604800 second(s) (last: Wed Sep 20 08:13:33 2017)
Repo-filename: ///etc/yum.repos.d/fedora.repo

Repo-id      : fedora-source/17/x86_64
Repo-name    : Fedora 17 - Source
Repo-status  : disabled
Repo-mirrors : https://mirrors.fedoraproject.org/metalink?repo=fedora-source-17&arch=x86_64
Repo-expire  : 604800 second(s) (last: Unknown)
Repo-filename: ///etc/yum.repos.d/fedora.repo

Repo-id      : updates/17/x86_64
Repo-name    : Fedora 17 - x86_64 - Updates
Repo-status  : enabled
Repo-revision: 1375137576
Repo-tags    : binary-x86_64
Repo-updated : Tue Jul 30 08:13:02 2013
Repo-pkgs    : 13163
Repo-size    : 18 G
Repo-metalink: http://mirrors.fedoraproject.org/metalink?repo=updates-released-f17&arch=x86_64
  Updated    : Tue Jul 30 08:13:02 2013
Repo-baseurl : http://ftp.iij.ad.jp/pub/linux/Fedora/archive/fedora/linux/updates/17/x86_64/ (6 more)
Repo-expire  : 21600 second(s) (last: Wed Sep 20 08:17:40 2017)
Repo-filename: ///etc/yum.repos.d/fedora-updates.repo

Repo-id      : updates-debuginfo/17/x86_64
Repo-name    : Fedora 17 - x86_64 - Updates - Debug
Repo-status  : enabled
Repo-revision: 1375133118
Repo-tags    : debuginfo-x86_64
Repo-updated : Tue Jul 30 06:26:35 2013
Repo-pkgs    : 2446
Repo-size    : 15 G
Repo-metalink: http://mirrors.fedoraproject.org/metalink?repo=updates-released-debug-f17&arch=x86_64
  Updated    : Tue Jul 30 06:26:35 2013
Repo-baseurl : http://ftp.iij.ad.jp/pub/linux/Fedora/archive/fedora/linux/updates/17/x86_64/debug/ (5 more)
Repo-expire  : 21600 second(s) (last: Wed Sep 20 08:13:34 2017)
Repo-filename: ///etc/yum.repos.d/fedora-updates.repo

(snip)

Repo-id      : updates-testing-source/17/x86_64
Repo-name    : Fedora 17 - Test Updates Source
Repo-status  : disabled
Repo-mirrors : https://mirrors.fedoraproject.org/metalink?repo=updates-testing-source-f17&arch=x86_64
Repo-expire  : 21600 second(s) (last: Unknown)
Repo-filename: ///etc/yum.repos.d/fedora-updates-testing.repo

repolist: 48561
```

### レポジトリを有効にする
```
$ yum-config-manager --enable example
or
$ yum-config-manager --enable example\*            # 正規表現指定も可能
```

### レポジトリを無効する
```
$ yum-config-manager --disable example
or
$ yum-config-manager --disable example\*            # 正規表現指定も可能
```

### yumレポジトリを作成する
この辺を参考に
- http://kazmax.zpp.jp/linux_beginner/yum_createrepo.html

試していませんが、やることとしては次のような作業となる
- 1. createrepoコマンドでレポジトリ対象を作成してレポジトリを作成する
- 2. vi /etc/yum.repos.d/my_repo.repoなどを追加する
- 3. 対象のrpmを配置する。
- 4. createrepo --updateを実行してレポジトリ更新する

### レポジトリを追加する
/etc/yum.repos.d/に.repoファイルを追加します。
```
$ yum-config-manager --add-repo http://www.example.com/example.repo
```

たとえば、こんな感じのrepoファイルを読み込ませます。
```
[example]
name = My Test Repository
bandwidth = 0
base_persistdir = /var/lib/yum/repos/x86_64/6Server
baseurl = http://www.example.com/repo/6Server/x86_64/
cache = 0
cachedir = /var/cache/yum/x86_64/6Server/example
enabled = 1
```

- レポジトリID
  - []内にはレポジトリIDを記述します。上記ではexampleがレポジトリIDです。
- name
  - リポジトリの名前を記述。yum repolist 等で表示される。
- baseurl
  - リポジトリへのパスを記述する。http, ftp, ローカルパスを記述できる。
- enabled
  - yumコマンド利用時にこのレポジトリを使用するかどうかを指定します。


repoファイルの細かい設定については以下のドキュメントなどを参照のこと
- https://access.redhat.com/documentation/ja-JP/Red_Hat_Enterprise_Linux/7/html/System_Administrators_Guide/sec-Configuring_Yum_and_Yum_Repositories.html

### yum変数を使う
yumコマンド及びすべてのyum設定ファイル(/etc/yum.conf, /etc/yum.repos.d/ディレクトリ内すべて)で次の組み込み変数を利用出来ます。
- $releasever
  - /etc/yum.conf 設定ファイルにある distroverpkg=value の行から $releasever の値を取得します。
  - /etc/yum.conf にそのような行がない場合、yum は redhat-release ファイルを提供する redhat-releaseproduct パッケージからバージョン番号を取得することで、正しい値を推測します。
- $arch
  - Python の os.uname() 機能を呼び出す時に返り値としてシステムの CPU アーキテクチャーを参照できます。
- $basearch
  - システムのベースアーキテクチャーを参照できます
  - たとえば、i686 および i586 の両マシンは i386 のベースアーキテクチャーを持っており、AMD64 および Intel64 マシンは x86_64 のベースアーキテクチャーを持っています。 
- $YUM0-9
  - これら 10 個の変数は、同じ名前を持つシェル環境変数の値でそれぞれ置換されます

上記の他にもカスタム変数を利用することができます。  
カスタム変数の定義、既存の変数値の上書きを行うには、/etc/yum/vars/ ディレクトリー内に変数と同じ名前を持つファイルを作成して (「$」 記号はなし) 、1 行目に希望する値を追加します。  
たとえば、$hogehogeという変数に"fugafuga"という値を設定する変数を用意するには次のファイルを用意します。
```
$ cat /etc/yum/vars/hogehoge
fugafuga
```

- 参考資料
  - https://access.redhat.com/documentation/ja-JP/Red_Hat_Enterprise_Linux/7/html/System_Administrators_Guide/sec-Configuring_Yum_and_Yum_Repositories.html

# 参考
- http://kazmax.zpp.jp/linux_beginner/yum_info.html
- YUMコマンドチートシート - RedHat Enterprise Linux
  - https://access.redhat.com/sites/default/files/attachments/rh_yum_cheatsheet_1214_jcs_print-ja.pdf

# TODO
以下の内容をこのmdにマージしておく
- YUMコマンドチートシート - RedHat Enterprise Linux
  - https://access.redhat.com/sites/default/files/attachments/rh_yum_cheatsheet_1214_jcs_print-ja.pdf
