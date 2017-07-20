# 概要
A10のロードバランサの設定についてのメモ
(実際に実機を触ってこのmarkdownは書いていない)

何ができるのかを知っておきたかったのでまとめるための資料です。

基本的には操作はcisco機材と同様でenableで特権モードに移行して、その後show running-configなどで設定情報閲覧などをしています。

# 詳細

### リアルサーバの新規作成
リアルサーバをVIPに新規追加する場合には次のような書式となる
```
(config)# slb server server-name server-ipaddress
(config-real server)# port number [ tcp | udp ]
(config-real server-node port)# xxxx    ( 例: no health-check)
```

上記の書式では次のようなことおw行っている
- configモードから対象のサーバ名とIPアドレスを指定して新規作成し、
- config-real serverモードからヘルスチェック対象のポート番号とプロトコルを指定し、
- config-real server-node portモードからはそのポートのヘルスチェック方法を指定している。

以下は設定例となります。次の例ではconfigモードとconfig-real serverモードのみ設定している。
```
(config)# slb server HTTP-SV01 192.168.1.101
(config-real server)# port 80 tcp
```


### リアルサーバ設定方法
- リアルサーバの組み込み
```
# configure
(config)# slb server $リアルサーバ名
(config-real server)# enable
```

- リアルサーバの切り離し
```
# configure
(config)# slb server $リアルサーバ名
(config-real server)# disable
```

- コネクション数変更
```
# configure
(config)# slb server $リアルサーバ名
(config-real server)# conn-limit XXXX
```



# 参考URL
- http://www.infraeye.com/study/a10v01.html
  - http://www.infraeye.com/study/a10v04.html
- Adcとは？〜A10 Thunderで可能なこと〜 (スライドシェア)
  - https://www.slideshare.net/RyoTamura4/adca10-thunder-72359949

