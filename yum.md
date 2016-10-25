# 概要
yumコマンドについて

# 詳細

### 基本コマンド

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

- 参考
 - http://www.atmarkit.co.jp/flinux/rensai/linuxtips/795tmprepo.html

