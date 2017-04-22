# 概要
yumコマンドについて

# 詳細

### パッケージを検索しインストールする
```
$ yum search <pkgname>
$ yum install <pkgname>
```

### アップデート可能なパッケージを確認したい場合
```
$ yum check-update       // アップデート可能なパッケージを確認する
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
例えば、rubyとその他に依存しない関連パッケージを除去するにはremoveを実行します
```
$ sudo yum remove ruby
```

### 古いパッケージをインストールする場合

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

### 普段利用しないレポジトリから取得したい場合
/etc/yum.repos.d/xxx.repoにはenabled=0の設定で記述されているが、一時的にそのレポジトリから取得したい場合には次のようにします。
hogerepoという普段使わないレポジトリからmypackageを取得する場合は次のコマンドとなる。

```
$yum --enablerepo='hogerepo' install mypackage
```

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


# 参考
- http://www.atmarkit.co.jp/flinux/rensai/linuxtips/795tmprepo.html
- YUMコマンドチートシート - RedHat Enterprise Linux
  - https://access.redhat.com/sites/default/files/attachments/rh_yum_cheatsheet_1214_jcs_print-ja.pdf
 

