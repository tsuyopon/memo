# 概要
docker topによりdockerコンテナ内のtop情報を閲覧することができます。

# 詳細

### 実行する
```
$ sudo docker top cdn-in-a-box_enroller_1 
UID                 PID                 PPID                C                   STIME               TTY                 TIME                CMD
root                19767               19742               0                   03:06               ?                   00:00:00            /bin/sh -c /run.sh
root                19997               19767               0                   03:06               ?                   00:00:00            bash /run.sh
root                25537               19997               1                   03:07               ?                   00:11:11            dlv --continue --listen=:2343 --accept-multiclient=true --headless=true --api-version=2 exec /enroller -- -dir /shared/enroller
root                25548               25537               0                   03:07               ?                   00:00:04            /enroller -dir /shared/enroller
```


docker container topというのもありますが出力内容はdocker topと変わらなそう。
```
$ sudo docker container top cdn-in-a-box_enroller_1 
UID                 PID                 PPID                C                   STIME               TTY                 TIME                CMD
root                19767               19742               0                   03:06               ?                   00:00:00            /bin/sh -c /run.sh
root                19997               19767               0                   03:06               ?                   00:00:00            bash /run.sh
root                25537               19997               1                   03:07               ?                   00:11:14            dlv --continue --listen=:2343 --accept-multiclient=true --headless=true --api-version=2 exec /enroller -- -dir /shared/enroller
root                25548               25537               0                   03:07               ?                   00:00:04            /enroller -dir /shared/enroller
```

### topの出力を変える

```
$ sudo docker top cdn-in-a-box_enroller_1 aux
USER                PID                 %CPU                %MEM                VSZ                 RSS                 TTY                 STAT                START               TIME                COMMAND
root                19767               0.0                 0.0                 2484                576                 ?                   Ss                  03:06               0:00                /bin/sh -c /run.sh
root                19997               0.0                 0.0                 4164                3360                ?                   S                   03:06               0:00                bash /run.sh
root                25537               1.5                 0.3                 4910124             28800               ?                   Sl                  03:07               11:15               dlv --continue --listen=:2343 --accept-multiclient=true --headless=true --api-version=2 exec /enroller -- -dir /shared/enroller
root                25548               0.0                 0.1                 711756              12220               ?                   Sl                  03:07               0:04                /enroller -dir /shared/enroller
```

### docker-composeで一括実行する
docker-composeだと対象のコンテナ全てで表示してくれます。 若干の出力の違いはあります。
```
$ docker-compose -f ./docker-compose.yml top

cdn-in-a-box_dns_1
 UID     PID    PPID    C   STIME   TTY     TIME                          CMD                     
--------------------------------------------------------------------------------------------------
root    19341   19290   0   03:06   ?     00:00:00   /bin/bash /sbin/entrypoint.sh /usr/sbin/named
uuidd   19620   19341   0   03:06   ?     00:00:07   /usr/sbin/named -u bind -g                   

cdn-in-a-box_edge_1
UID     PID    PPID    C   STIME   TTY     TIME                                                                       CMD                                                                   
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
root   19109   19084   0   03:06   ?     00:00:00   bash /run.sh                                                                                                                            
root   27410   19109   0   03:08   ?     00:00:01   crond -im off                                                                                                                           
root   27418   19109   0   03:08   ?     00:00:07   /usr/bin/coreutils --coreutils-prog-shebang=tail /usr/bin/tail -Fn+1 /opt/trafficserver/var/log/trafficserver/diags.log /var/log/ort.log
root   37925   19109   0   15:01   ?     00:00:00   /usr/sbin/anacron -s                                                                                                                    

cdn-in-a-box_enroller_1
UID     PID    PPID    C   STIME   TTY     TIME                                                                   CMD                                                              
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
root   19767   19742   0   03:06   ?     00:00:00   /bin/sh -c /run.sh                                                                                                             
root   19997   19767   0   03:06   ?     00:00:00   bash /run.sh                                                                                                                   
root   25537   19997   1   03:07   ?     00:11:12   dlv --continue --listen=:2343 --accept-multiclient=true --headless=true --api-version=2 exec /enroller -- -dir /shared/enroller
root   25548   25537   0   03:07   ?     00:00:04   /enroller -dir /shared/enroller 

(snip)
```


# 参考
### 仕組み(ソースコードまで見ている)
- https://qiita.com/HommaHomma/items/16b9dd97bfe43eecef23

