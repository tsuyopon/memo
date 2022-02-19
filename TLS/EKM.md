# 概要
Keying Material Exporters for Transport Layer Security (TLS)

# 解決したい課題
アプリケーションがTLS通信経路も暗号学的に含めた上で鍵生成したいという要望があります。

これには以下の要求を満たす必要があります。
- サーバとクライアントで同一のEKM値を生成できること
- EKMの値はランダム値と区別がつかないこと
- 同じTLS/DTLSからは複数のEKM値を生成できるようにすべきであること
- 1つのEKMが知られたとしても、そこからそのmaster_secretやその他のEKM値について何も関連していない情報であること

# 解決方法
Exporterを定義します。
Exporterはmaster_secret, ランダム値、labelの値を用いて、PRFから生成されます。


# 詳細

EKMを生成するには次の3つのパラメータを受け取ります
- (1) 曖昧さがないラベル文字列
- (2) exporterを使っているアプリケーションによって提示されたそれぞれに関連付けられるcontext value
- (3) EKMの長さ

contextが与えられない場合には次のように計算される
```
PRF(SecurityParameters.master_secret, label,
    SecurityParameters.client_random +
    SecurityParameters.server_random
    )[length]
```

contextが与えられたら次のように計算される。
```
PRF(SecurityParameters.master_secret, label,
    SecurityParameters.client_random +
    SecurityParameters.server_random +
    context_value_length + context_value
    )[length]
```

(1)のラベルはNULLで終端されていないASCII文字列となっています。
「EXPERIMENTAL」で始まるラベルの値は登録なしでプライベート利用しても構わない。


# 参考URL
- https://datatracker.ietf.org/doc/html/rfc5705
