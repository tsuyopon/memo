# 概要
dockerで容量が足りなくなった際の対応方法について

# 容量の確認と削除 
```
$ docker system df
TYPE            TOTAL     ACTIVE    SIZE      RECLAIMABLE
Images          13        1         10.72GB   9.912GB (92%)
Containers      1         0         247.9kB   247.9kB (100%)
Local Volumes   0         0         0B        0B
Build Cache     225       0         39.8GB    39.8GB
```

```
$ docker system prune --volumes
```

Images以外は削除されました。

```
$ docker system df
TYPE            TOTAL     ACTIVE    SIZE      RECLAIMABLE
Images          12        0         10.72GB   10.72GB (100%)
Containers      0         0         0B        0B
Local Volumes   0         0         0B        0B
Build Cache     29        0         0B        0B
```

全てのコンテナやプロセスを削除する。これはイメージも全て削除されますので注意してください。
```
sudo docker system prune --all
```

以上でまっさらになりました。
```
$ docker system df
TYPE            TOTAL     ACTIVE    SIZE      RECLAIMABLE
Images          0         0         0B        0B
Containers      0         0         0B        0B
Local Volumes   0         0         0B        0B
Build Cache     0         0         0B        0B
```

どこかのコンテナに入ってみるとoverlayがほぼ100%だったのが5%ほどに減りました。
```
# df
Filesystem     1K-blocks    Used Available Use% Mounted on
overlay         61255492 2676316  55437852   5% /
tmpfs              65536       0     65536   0% /dev
tmpfs            1017700       0   1017700   0% /sys/fs/cgroup
shm                65536       0     65536   0% /dev/shm
/dev/vda1       61255492 2676316  55437852   5% /etc/hosts
tmpfs            1017700       0   1017700   0% /proc/acpi
tmpfs            1017700       0   1017700   0% /sys/firmware
```
