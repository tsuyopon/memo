# CDNI Triggers Interface SVA Extensions

# 解決したい課題
近年のOpenCachingワーキング・グループでは商業利用によりISPでのCDN利用するケースが出てきた。
このケースだとCDN業者がuCDN、ISP業者側がdCDNとなる特別なケースである。

OpenCaching自体はYoutube, Huluなどの動画プロバイダだと、ネットワーク上に輻輳が発生するので、ISP自体にオリジンを持つことでそれを緩和させることによっって、ユーザのwaiting時間なども短縮できるといった試みです。

# 解決方法
dCDNに対してトリガー(v2)を発行するための特別な仕組みを用意する。
トリガー自体はRFC8007で定義されているが、OpenCaching仕様のために「Regular Expression」、「Content Playlist」の２つの選択オプションが必要となる。
- https://tools.ietf.org/html/rfc8007#section-5.2.1

また、この仕様ではTimePolicy(時間による制約指定)やLocationPolicy(場所による制約指定)といったことについても規定しています。


# 仕様詳細

### サンプル書式
一般的な書式は次のとおりです。cdn-pathにAS番号などを入れるのがおそらく今回の特別なケース(?)ということでしょうか?
```

         POST /triggers HTTP/1.1
         User-Agent: example-user-agent/0.1
         Host: dcdn.example.com
         Accept: */*
         Content-Type: application/cdni; ptype=ci-trigger-command.v2
         {
           "trigger.v2": { <properties of a trigger.v2 object> },
           "cdn-path": [ "AS64496:1" ]
         }
```

### LocationPolicy サンプル
generic-trigger-extension-typeでCIT.LocationPolicyを指定していて、それに紐づく値をgeneric-trigger-extension-valueで指定しています。
以下の例だとusは許可するが、caは許可しないといった例になっています。
```
      {
        "trigger": {
          "type": "preposition",
          "content.urls": [
              "https://www.example.com/a/b/c/1",
              "https://www.example.com/a/b/c/2"
          ],
          "extensions": [
             {
                "generic-trigger-extension-type": "CIT.LocationPolicy",
                "generic-trigger-extension-value":
                 {
                    "locations": [
                      {
                        "action": "allow",
                        "footprints": [
                          {
                            "footprint-type": "countrycode",
                            "footprint-value": ["us"]
                          }
                        ]
                      },
                      {
                        "action": "deny",
                        "footprints": [
                          {
                            "footprint-type": "countrycode",
                            "footprint-value": ["ca"]
                          }
                        ]
                      }
                    ]
                 },
                "mandatory-to-enforce": true,
                "safe-to-redistribute": true,
                "incomprehensible": false
           }
          ]
        },
        "cdn-path": [ "AS64496:1" ]
      }
```

### TimePolicy サンプル
generic-trigger-extension-typeでCIT.TimePolicyが指定されていて、generic-trigger-extension-valueの値として開始時刻と終了時刻が指定されている。
これによってuCDNからdCDNへと時刻操作を行うことができる。

```
      POST /triggers HTTP/1.1
      User-Agent: example-user-agent/0.1
      Host: dcdn.example.com
      Accept: */*
      Content-Type: application/cdni; ptype=ci-trigger-command
      Content-Length: 352

      {
        "trigger": {
          "type": "preposition",
          "content.urls": [
              "https://www.example.com/a/b/c/1",
              "https://www.example.com/a/b/c/2"
            ],
          "extensions": [
             {
                "generic-trigger-extension-type": "CIT.TimePolicy",
                "generic-trigger-extension-value":
                 {
                   "windows": {
                      "start": 946717200,
                      "end": 946746000
                   }
                 }
                "mandatory-to-enforce": true,
                "safe-to-redistribute": true,
                "incomprehensible": false
             }
          ],
        },
        "cdn-path": [ "AS64496:1" ]
      }
```

# 参考URL
- https://tools.ietf.org/html/draft-finkelman-cdni-triggers-sva-extensions-00
- OpenCachigについては以下の動画がわかりやすい
  - https://www.youtube.com/watch?v=S5ZBQYm-rm0
