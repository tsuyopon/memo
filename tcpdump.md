# 概要
tcpdumpコマンドについて

# 詳細
### etho0の80番ポートを除く
```
$ tcpdump -Z root -i eth0 -X -S port 80
```
