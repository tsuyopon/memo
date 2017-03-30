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
 less /var/log/yum.log
```



# 参考
- http://www.atmarkit.co.jp/flinux/rensai/linuxtips/795tmprepo.html
- YUMコマンドチートシート - RedHat Enterprise Linux
  - https://access.redhat.com/sites/default/files/attachments/rh_yum_cheatsheet_1214_jcs_print-ja.pdf
 

