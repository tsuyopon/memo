# 概要
redisへのパッケージのインストールと起動確認

# 詳細


### yumからのインストール (CentOS7)
CentOS Linux (3.10.0-957.el7.x86_64) 7 (Core)でパッケージインストールを行う。
```
$ sudo yum -y install epel-release
$ sudo yum -y install redis
```

redisの起動
```
$ sudo service redis start
Redirecting to /bin/systemctl start redis.service
$ ps auxww | grep -i redis
redis     4035  0.2  0.1 142956  5784 ?        Ssl  03:58   0:00 /usr/bin/redis-server 127.0.0.1:6379
tsuyoshi  4039  0.0  0.0   9088   668 pts/0    S+   03:58   0:00 grep --color=auto -i redis
```

たったこれだけでredisを使うことができます。
