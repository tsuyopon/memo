# 概要
CentOS7ではサービスの管理するシステムがSystemV系のinitからSystemdに変わっています。

これにより今までは次のようにして再起動出来ていましたが、
```
$ /etc/rc.d/init.d/sshd restart
```

次のようにsystemctlコマンドを利用するようになりました。
```
$ systemctl restart ssdh.service
```

ここでは、主にchkconfig関連対応(SysV)からsystemctl(SysD)への移行に関してまとめていきます。

# 詳細

### httpdをyumからインストールしたがchkconfigで起動スクリプトが存在しない場合

起動スクリプトや/etc/rc.d/init.d中に存在しない場合には新たに作成する必要があります。
httpdの場合にはapachectlが起動スクリプトですので、コピーします。
```
$ sudo cp -iv /usr/sbin/apachectl  /etc/rc.d/init.d/httpd
```

続いて、chkconfig --add httpsを実行すると
```
service https does not support chkconfig
```

というエラーが出力されますので、先ほどコピーしたhttpdファイルの先頭に以下のコメントが必要となります。
```
#!/bin/sh
# chkconfig: 345 98 20
# description: Apache Web Service
# processname: apache
```

上記例では、chkconfigの後には起動したいランレベルである345と起動時の順番98, 停止時の順番20を入れている。
descriptionとprocess nameは好きにしてよい

以上により
```
# chkconfig --add https
```
とすることによって指定したランレベル中の/etc/rc*.d/にスクリプトがあることがわかる

ただし、私が試したFedora17では、追加はされているはずなんですがchkconfigにリスト表示されないということになっているみたいです。
``` 
$ chkconfig --list

Note: This output shows SysV services only and does not include native
      systemd services. SysV configuration data might be overridden by native
      systemd configuration.

netconsole     0:off	1:off	2:off	3:off	4:off	5:off	6:off
network        	0:off	1:off	2:off	3:on	4:off	5:on	6:off
spice-vdagentd 0:off	1:off	2:off	3:off	4:off	5:on	6:off
``` 

このchkconfigは SysVという体系の一種なのですが、Fedora17以降に関してはsystemDを利用する必要があるとのこと。
仮想化関連に必要なものだけはここでリスト表示されるみたい(詳細は不明)
どうりでchkconfig用の起動スクリプトがデフォルトでは/etc/rc.dには入らない訳だ。

起動スクリプトは以下のコマンドで確認することができる。
``` 
$ rpm -ql httpd | grep -i systemd
/lib/systemd/system/httpd-event.service
/lib/systemd/system/httpd-worker.service
/lib/systemd/system/httpd.service
``` 

一応、先ほどchkconfigにて登録してしまったので、削除しておく
``` 
$ chkconfig --del httpd
``` 

では、SystemD系で起動をしてみると
``` 
$ sudo systemctl start httpd.service
$ ps auxww | grep -i apache
$ systemctl status httpd.service
httpd.service - The Apache HTTP Server (prefork MPM)
 Loaded: loaded (/usr/lib/systemd/system/httpd.service; enabled)
 Active: active (running) since Sat, 29 Dec 2012 16:56:04 +0900; 12min ago
Main PID: 15003 (httpd)
 CGroup: name=systemd:/system/httpd.service
 〓〓〓 15003 /usr/sbin/httpd -k start
 〓〓〓 15004 /usr/sbin/httpd -k start
 〓〓〓 15005 /usr/sbin/httpd -k start
 〓〓〓 15006 /usr/sbin/httpd -k start
``` 

SysDに登録されているサービス一覧を表示するためには
``` 
$ systemctl --full list-units --type=service
``` 

サーバ起動時にも自動的にあげるようにするには
``` 
$ systemctl is-enabled httpd.service
disabled
$ systemctl enable httpd.service
$ systemctl is-enabled httpd.service
enabled
``` 

なお、引数無しでsystemctlを呼び出すとactive状態のユニット一覧が表示するらしい。
起動していない状態も表示したければ--allを付与すればいいみたい
``` 
$ systemctl
UNIT                      LOAD   ACTIVE SUB       JOB DESCRIPTION
proc-sys...misc.automount loaded active waiting       Arbitrary Executable File 
sys-devi...ock-sr0.device loaded active plugged       VBOX_CD-ROM
sys-devi...et-p2p1.device loaded active plugged       82540EM Gigabit Ethernet C
``` 

# 参考URL
- chkconfigについて
  - http://makisuke.seesaa.net/article/6066867.html
- systemDとchkconfigとの比較について
  - http://fedorakenken.doorblog.jp/archives/51854520.html
- systemDにおけるランレベル変更について
  - http://wiki.bit-hive.com/tomizoo/pg/systemd%20%26%20systemctl
