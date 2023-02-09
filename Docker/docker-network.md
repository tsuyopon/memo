# 概要
Dockerのnetworkサブコマンドについて

# 詳細

### 一覧を表示する
```
$ sudo docker network ls 
NETWORK ID          NAME                DRIVER
10aa51e2d993        bridge              bridge
202b87d7b8a4        none                null
92316fc5522f        host                host
```

- NAME
  - (1) none: ネットワークへの接続を必要としないコンテナの場合
  - (2) host: Docker ホストと同じネットワークにスタックするドライバで、Docker ホストマシンと同じネットワークインタフェース、IP アドレスを持つようになります。
  - (3) bridge: Linux bridge 機能を使った、Linux 上に別ネットワークを使う方式。 (--netオプションを指定しないとデフォルトはこれになります)

上記の3つはそれぞれbusyboxを立ち上げてifconfigを確認してみましょう。

- (1) none
```
```

- (2) none
```
```

- (3) bridge
  - コンテナ側とhost側のifconfigを比較すると
```
$ docker run --name bridge_net_busybox -ti busybox /bin/sh
(docker)$ ifconfig
(docker)$ exit
$ ifconfig 
```

### NETWORK IDを指定して利用しているネットワーク情報を確認する

```
$ docker network inspect cdn-in-a-box_default
[
    {
        "Name": "cdn-in-a-box_default",
        "Id": "b2760768ff9702e3056c389e0d2bdea82cc6bf7ceb8994bbaefd06668b0e48f2",
        "Created": "2023-02-05T10:17:00.2060996Z",
        "Scope": "local",
        "Driver": "bridge",
        "EnableIPv6": false,
        "IPAM": {
            "Driver": "default",
            "Options": null,
            "Config": [
                {
                    "Subnet": "192.168.160.0/20",
                    "Gateway": "192.168.160.1"
                }
            ]
        },
        "Internal": false,
        "Attachable": true,
        "Ingress": false,
        "ConfigFrom": {
            "Network": ""
        },
        "ConfigOnly": false,
        "Containers": {
            "321066db6f40bb4761d9964bb4e8aedf88ee0080ded436609dc3c6b9e5fc145e": {
                "Name": "cdn-in-a-box_enroller_1",
                "EndpointID": "7c1694a6765228de4958eb00fca919825958656299164c8132774399d4c83fca",
                "MacAddress": "02:42:c0:a8:a0:08",
                "IPv4Address": "192.168.160.8/20",
                "IPv6Address": ""
            },

(snip)

            "f1ebaf6b81d5653671eebdae6b71521f884373bada69716028448ca0a4397bb7": {
                "Name": "cdn-in-a-box_grafana_1",
                "EndpointID": "eabfcb1fe72132c0984769ec5172f251e599c105b8c36d5cd42e4841710787b2",
                "MacAddress": "02:42:c0:a8:a0:0f",
                "IPv4Address": "192.168.160.15/20",
                "IPv6Address": ""
            },
            "f248aca0ccbbfbcfb402a8aeba1556be659e6019e18b5b3fe3a22e43cc62df38": {
                "Name": "cdn-in-a-box_trafficportal_1",
                "EndpointID": "1fd23ea0f52fa28a22316ae7595da65d9f936e93968bcfeca9d1030c05b9cc7c",
                "MacAddress": "02:42:c0:a8:a0:0b",
                "IPv4Address": "192.168.160.11/20",
                "IPv6Address": ""
            }
        },
        "Options": {},
        "Labels": {
            "com.docker.compose.network": "default",
            "com.docker.compose.project": "cdn-in-a-box",
            "com.docker.compose.version": "1.29.2"
        }
    }
]
```
