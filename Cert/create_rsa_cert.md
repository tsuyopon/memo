# 概要
opensslからRSA証明書を発行するテストです。

# 詳細
秘密鍵と秘密鍵から公開鍵を生成します。
```
$ openssl genrsa -out key.pem 4096
$ openssl rsa -in key.pem -pubout -out pubkey.pem
writing RSA key
```

発行された秘密鍵と公開鍵を確認します。

秘密鍵を確認します。
```
$ cat key.pem 
-----BEGIN PRIVATE KEY-----
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
wJl/2bJgQQ2THYP55g8Kpy5oC+GM
-----END PRIVATE KEY-----
```

秘密鍵に含まれる詳細情報を可視化してみます。
```
$ openssl rsa -text -noout -in key.pem 
Private-Key: (4096 bit, 2 primes)
modulus:
    00:a4:8d:ca:bf:18:e7:0b:9a:4b:de:91:0b:3f:ef:
    47:77:5a:ad:79:9c:21:65:bc:9d:79:a4:aa:18:4b:
    5f:47:26:af:f5:9d:31:45:1c:7e:12:1e:41:33:67:
    5a:d6:03:b0:47:79:87:a6:63:e4:70:8e:c3:bb:55:
    9b:3a:64:ba:be:c2:55:71:1b:8e:b3:a4:29:fa:94:
    c5:70:4b:7b:ef:cf:89:e3:0a:34:e5:be:49:b5:4a:
    04:a2:b2:13:d5:1f:ca:e3:23:ae:44:bb:1d:ee:bf:
    16:fb:aa:97:bf:e3:35:a6:97:02:34:78:c6:40:97:
    d8:00:8e:ca:89:ee:2b:02:ab:8c:cf:3b:37:b7:96:
    69:60:0b:3f:1e:76:96:c3:0f:fc:e8:5e:ba:2e:81:
    4e:df:bc:be:be:19:f5:23:1b:e0:9a:c8:47:21:32:
    3d:8d:b2:ed:2f:65:bf:61:37:cd:9a:94:0d:66:8e:
    3a:3c:c3:e8:5e:d2:ce:93:7c:89:a7:7f:f0:6d:db:
    0f:01:d3:91:8f:2b:b4:c6:ca:f2:76:1d:65:56:b9:
    c2:c6:9e:77:85:ca:c2:bf:05:30:4b:37:39:87:c9:
    c4:40:c4:53:3c:46:90:65:e2:a4:5c:10:ea:a2:b5:
    63:06:a1:33:5e:5b:a2:e6:16:c4:12:b4:93:52:92:
    fd:c6:0f:51:b0:52:77:82:5a:6e:3d:84:74:35:de:
    42:bb:0f:63:1f:f4:71:f2:98:42:37:0e:5b:15:aa:
    75:0a:04:13:0b:ca:a2:ed:fc:9f:00:f2:b1:49:8d:
    e8:12:6c:90:27:12:d7:ef:0f:1b:3d:36:1f:1b:bf:
    c9:a7:30:47:8f:25:d8:16:4b:43:4f:9a:d8:be:0a:
    b4:5e:66:78:95:19:b6:f1:a9:13:b3:b9:ad:eb:17:
    19:03:45:fb:2d:cf:d6:2b:a6:64:f3:08:e3:a4:b7:
    13:5d:73:72:ac:40:47:3c:da:7f:89:dc:be:ba:c3:
    ee:34:2d:f0:ce:21:fc:86:e2:28:1f:19:62:2e:f2:
    ae:dd:ea:16:3d:9e:27:c7:e7:8d:e8:4d:55:05:b9:
    76:36:88:4a:ce:bf:18:b5:49:e4:6f:9d:a6:ad:87:
    b6:f0:b3:2b:57:3c:5d:c9:e6:eb:de:68:52:0d:63:
    d9:e9:c8:80:41:92:7d:3a:cf:a7:b5:cf:f8:f4:9b:
    c2:43:a2:53:1c:18:6c:49:c8:a9:43:35:08:48:2a:
    70:87:6d:fd:97:72:00:d6:97:88:ac:3c:ec:d9:2a:
    1e:2d:09:10:e5:3d:9f:f2:6f:8b:fe:a6:be:e0:3b:
    21:86:58:3f:cc:a0:b6:99:83:b0:eb:b0:44:1b:b6:
    ea:77:7b
publicExponent: 65537 (0x10001)
privateExponent:
    00:a5:b8:55:60:1e:fa:05:12:76:9b:dd:a5:a5:49:
    83:c7:0c:ff:a8:05:38:28:e0:57:2b:fc:1d:dd:13:
    dc:b1:f9:e7:3b:a3:13:6f:fb:13:59:5a:64:ac:a5:
    f5:bd:f0:27:97:d3:e4:0e:f4:2e:04:73:37:37:a1:
    8a:e1:a1:1b:e5:8c:e8:7f:8c:58:87:d8:12:6e:d5:
    93:a4:9b:49:4d:22:fb:e9:4e:01:0f:30:65:f3:a2:
    0b:f1:cd:f1:71:0e:f0:b9:72:d8:9a:5f:7a:ae:6a:
    db:46:3b:cd:80:b8:69:4f:b9:ad:c4:9e:c5:f3:01:
    84:b6:50:e9:4c:2e:32:c5:94:e7:dd:40:80:50:c0:
    fb:8d:32:af:18:b9:0f:d6:4b:89:7f:f0:15:05:4c:
    7a:7f:c1:c4:b4:3a:87:60:77:3e:76:17:9a:45:1a:
    25:40:8f:4f:09:84:29:0a:79:b4:39:9b:c9:b4:96:
    42:6d:7b:99:43:e5:f2:b0:c4:8c:c5:f5:2a:5c:61:
    29:a4:ad:3f:01:d9:bc:92:d4:e7:e5:af:29:77:16:
    b4:b4:f5:cb:69:4f:b2:d1:67:dc:af:86:34:3b:a3:
    b1:a4:ce:41:ee:15:22:9d:1c:2e:f6:5a:cd:38:55:
    d1:93:67:50:b1:87:f5:11:f2:95:b3:29:9c:d7:ba:
    d4:34:1d:14:d4:22:e8:b0:a7:80:9c:c8:ae:db:06:
    8a:36:dc:8a:6f:cb:2e:ee:f5:fd:a6:74:95:2a:32:
    aa:81:e2:3d:0d:be:f7:66:21:b0:cd:5b:52:6a:e2:
    29:89:8d:e8:69:2c:c4:75:f5:5d:44:10:ef:c9:e2:
    f2:45:21:6f:46:db:4f:ce:c6:c5:f3:4d:c0:3d:ae:
    98:f1:d4:fb:e2:4f:12:47:8c:bf:02:62:a9:a7:d1:
    b4:90:be:3e:73:be:96:ec:54:62:27:85:dd:c5:a6:
    72:4c:6e:b4:36:4e:bf:1b:94:29:93:fc:c7:17:37:
    44:8c:0d:b7:d6:e7:11:4d:d4:6c:e4:fb:44:4f:12:
    ec:8d:fa:8e:0d:e0:d1:d4:e9:ba:de:12:54:6c:64:
    47:4c:3f:66:d8:35:64:96:f1:1c:43:f5:1c:28:4d:
    a6:c1:13:bd:f2:41:9e:34:ea:20:06:11:83:22:ff:
    d2:10:eb:db:69:77:db:65:86:d4:e7:1e:8d:76:5e:
    bf:e1:18:08:e2:8f:9f:0e:ce:f9:af:95:b3:2b:1e:
    56:ff:b5:ca:9e:28:0c:e7:d9:b0:15:37:e1:0e:99:
    6b:04:b6:aa:d6:a0:1c:4f:1f:e5:d7:92:ce:35:49:
    43:63:fa:fa:99:64:2c:33:82:2c:51:4d:22:b9:d5:
    b4:01
prime1:
    00:cb:e7:48:ac:64:22:6e:ec:f0:20:37:c7:97:ea:
    47:be:87:f0:ea:f7:9f:2d:09:a2:b4:0a:ae:a3:c1:
    f2:ae:0d:cb:17:1c:7a:0c:a8:c7:ca:b2:6b:49:f2:
    de:be:43:4c:84:3d:2e:b1:7d:1e:be:45:63:0b:72:
    f6:b1:c9:32:e8:a4:75:3a:17:a5:1f:87:55:a8:a3:
    f8:44:af:0e:42:de:e3:f3:b9:94:ae:53:7d:7b:71:
    64:3d:06:17:c8:85:b3:0e:73:df:36:8f:84:bc:e9:
    35:7d:1d:c7:58:94:0e:59:cf:11:ec:d3:2c:24:31:
    5f:6a:0d:06:1f:41:b1:39:89:21:19:b7:cf:0e:7f:
    1a:fc:7b:26:a3:7d:e7:cb:aa:09:5d:91:ee:41:1a:
    56:25:94:b6:1e:34:2d:4f:a9:4f:fe:0a:a4:39:55:
    c5:2b:50:3e:6a:38:61:13:a7:2e:75:96:c5:01:29:
    90:93:67:71:7f:f5:a8:4f:64:2e:15:32:9a:e5:00:
    fc:0a:5d:c3:3d:68:77:cb:14:8f:d4:c7:3e:95:59:
    fe:49:68:91:e4:b2:fc:22:b8:67:cb:27:77:bb:90:
    7a:56:91:4a:1f:f3:2a:9f:11:f9:01:87:3b:de:3d:
    c1:52:b2:e0:64:79:33:af:40:1d:5f:1f:ba:ff:ea:
    4f:81
prime2:
    00:ce:98:c5:0a:5a:68:4c:14:ce:5e:fa:59:fb:a9:
    8b:33:0a:47:42:00:76:d7:58:d4:8a:a5:a1:a5:bd:
    39:17:89:60:7d:b4:9d:d0:8c:c4:08:19:16:ee:2b:
    4e:52:0e:3e:0a:5d:8c:ea:11:59:58:c7:17:07:8e:
    dc:77:ed:2a:7b:9f:d5:27:85:92:c1:4d:2a:7b:0c:
    58:b4:fe:b4:ac:e9:e2:4d:f8:41:d8:f2:c2:85:e7:
    26:2c:14:93:83:35:fd:d1:ad:fa:a3:ba:d3:e8:fa:
    2f:36:b0:b0:44:72:3a:46:8f:2f:36:84:7b:da:c7:
    2d:2d:f6:4d:5a:1c:7a:dc:57:ae:f8:a5:1f:1a:06:
    9b:65:a4:ce:55:b0:4d:3c:d2:65:73:cf:0e:a1:2f:
    69:6e:79:41:18:2b:f3:f7:75:ae:a1:7e:50:7a:70:
    8c:7a:2f:1c:f9:93:13:a0:07:18:77:86:73:ed:a7:
    58:d4:f2:91:bc:3c:b1:9f:a1:86:27:46:ac:ed:6d:
    71:a2:27:60:63:5b:c2:37:dc:6c:97:62:c5:9c:41:
    91:37:a8:03:6f:ef:76:2d:46:0b:09:75:7d:a9:7a:
    66:33:2b:eb:cb:ac:08:7b:c7:c6:9f:28:83:6a:0d:
    57:d3:89:47:38:0b:12:60:b4:dc:32:d0:38:93:30:
    84:fb
exponent1:
    2f:03:b2:0f:05:bb:a6:c5:fd:0c:00:b0:85:c7:a0:
    29:3f:60:fe:5c:80:18:3b:5b:87:95:da:f4:a9:38:
    92:87:5d:a7:83:8a:64:b6:d9:f2:53:b7:47:42:b7:
    b7:38:ff:40:92:76:dc:b7:d3:c9:dd:67:db:f0:f3:
    0e:c5:2c:76:d5:cc:ad:cb:5b:e8:6c:25:05:10:61:
    a3:3c:95:d6:37:5c:6a:0b:05:4c:38:b5:fb:2b:87:
    08:47:0a:5e:d2:ed:19:4d:00:4f:ad:41:d6:e9:12:
    cb:39:7d:88:60:02:fb:14:32:b6:df:6e:13:1e:4b:
    38:c1:ae:02:b0:fb:f3:1f:3a:41:9a:cf:24:31:8c:
    80:60:c8:e4:f3:97:e9:ae:d8:1f:fa:10:ec:73:ed:
    1f:17:2d:f2:c2:e7:1b:b2:17:5e:a5:07:7e:ac:d7:
    1c:88:91:0b:9e:da:4b:54:c5:f2:99:03:ed:a3:ae:
    d1:3e:0d:be:8a:5e:f7:87:4a:d4:da:69:3a:9a:42:
    83:05:61:8a:1c:37:5a:dc:ef:d9:08:e3:d6:3d:fc:
    d2:e2:48:99:69:e7:96:fd:db:f8:cc:ad:df:d2:8d:
    52:be:87:4f:dc:9a:9c:38:e1:a8:47:8d:37:4e:17:
    f0:40:8c:5a:be:53:7b:7a:16:0b:a3:de:53:39:ac:
    81
exponent2:
    6b:d5:43:6b:7e:fa:d7:53:38:d0:4c:3d:f1:64:72:
    3a:86:cf:e0:bc:5b:4b:55:9b:42:6e:e7:6b:99:d3:
    95:dc:67:97:d5:51:56:0c:53:39:a2:d6:dc:23:90:
    72:b5:ea:5e:00:ac:4f:74:14:bd:88:d5:15:65:d4:
    df:67:d3:f7:c8:da:3a:11:b7:22:dc:03:23:4c:b3:
    74:6d:49:a2:c3:45:12:cb:54:9b:47:42:8f:1f:b2:
    45:e9:cb:80:fe:0a:68:8a:35:bb:86:05:9b:a2:12:
    48:aa:7a:a6:8f:34:a9:a5:8c:d0:18:e0:88:b5:d3:
    78:1d:0a:0c:d1:b6:b3:11:b5:4b:24:ec:91:ea:06:
    ec:4b:d4:42:d7:8d:c9:04:4c:5d:e1:22:52:b1:6b:
    87:75:14:ab:e8:2d:23:e9:b1:e7:ab:05:98:92:ec:
    4f:ce:0d:82:9a:e8:f0:6b:23:b3:27:63:95:14:f7:
    01:d7:46:88:08:e9:f1:57:1e:ad:9b:6f:21:52:31:
    b0:a0:7a:e8:01:79:e3:2c:53:25:c5:31:3d:b8:df:
    72:3c:68:e6:e1:07:3e:e4:43:58:81:91:c0:87:19:
    96:f6:02:d2:41:0e:00:85:aa:bf:62:27:0d:90:bf:
    59:b3:5a:8f:fe:ff:6d:a8:99:12:90:aa:26:f1:79:
    47
coefficient:
    55:2e:c1:bc:1f:c5:7b:02:e8:5c:7a:77:2a:4f:81:
    69:b7:83:65:ff:2d:e3:da:0c:b6:3d:08:b8:72:92:
    28:56:24:53:76:85:c8:a8:58:0f:4d:86:7e:10:d9:
    13:44:20:74:96:05:88:fe:d7:04:3c:f1:58:92:95:
    e0:65:33:4a:2d:86:5e:06:e1:e4:7c:9d:11:b7:93:
    4c:af:81:3e:93:94:f8:55:36:bd:03:ac:3a:37:13:
    5c:55:b7:d2:07:5a:91:c6:49:ea:e2:dc:0b:a7:3f:
    89:70:44:65:47:38:b7:44:60:ea:ab:e7:46:06:0d:
    97:73:ff:06:10:84:75:93:c8:82:b9:ad:76:6d:a4:
    ec:7a:e5:9a:36:22:20:20:6e:cd:f7:8d:61:0b:31:
    59:5d:7e:fe:91:4d:6e:d9:92:8e:3a:47:88:e2:ef:
    9e:70:86:02:71:4b:eb:30:51:e9:3e:bb:50:42:ba:
    90:ab:8c:64:e8:04:6c:d9:aa:3e:07:62:6d:3d:61:
    1f:9e:2c:3b:d0:73:48:e2:e4:db:b5:ce:8d:66:2a:
    c7:1d:fa:2d:e5:3c:5f:36:c5:96:fa:b2:25:44:11:
    01:c4:12:6c:fe:2c:fc:94:08:65:c0:99:7f:d9:b2:
    60:41:0d:93:1d:83:f9:e6:0f:0a:a7:2e:68:0b:e1:
    8c
```

公開鍵を確認します。
```
$ cat pubkey.pem 
-----BEGIN PUBLIC KEY-----
MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEApI3KvxjnC5pL3pELP+9H
d1qteZwhZbydeaSqGEtfRyav9Z0xRRx+Eh5BM2da1gOwR3mHpmPkcI7Du1WbOmS6
vsJVcRuOs6Qp+pTFcEt778+J4wo05b5JtUoEorIT1R/K4yOuRLsd7r8W+6qXv+M1
ppcCNHjGQJfYAI7Kie4rAquMzzs3t5ZpYAs/HnaWww/86F66LoFO37y+vhn1Ixvg
mshHITI9jbLtL2W/YTfNmpQNZo46PMPoXtLOk3yJp3/wbdsPAdORjyu0xsrydh1l
VrnCxp53hcrCvwUwSzc5h8nEQMRTPEaQZeKkXBDqorVjBqEzXlui5hbEErSTUpL9
xg9RsFJ3glpuPYR0Nd5Cuw9jH/Rx8phCNw5bFap1CgQTC8qi7fyfAPKxSY3oEmyQ
JxLX7w8bPTYfG7/JpzBHjyXYFktDT5rYvgq0XmZ4lRm28akTs7mt6xcZA0X7Lc/W
K6Zk8wjjpLcTXXNyrEBHPNp/idy+usPuNC3wziH8huIoHxliLvKu3eoWPZ4nx+eN
6E1VBbl2NohKzr8YtUnkb52mrYe28LMrVzxdyebr3mhSDWPZ6ciAQZJ9Os+ntc/4
9JvCQ6JTHBhsScipQzUISCpwh239l3IA1peIrDzs2SoeLQkQ5T2f8m+L/qa+4Dsh
hlg/zKC2mYOw67BEG7bqd3sCAwEAAQ==
-----END PUBLIC KEY-----
```

公開鍵の情報は秘密鍵の確認コマンドに「-pubin」を付与することで確認できます。
```
$ openssl rsa -text -noout -pubin -in pubkey.pem 
Public-Key: (4096 bit)
Modulus:
    00:a4:8d:ca:bf:18:e7:0b:9a:4b:de:91:0b:3f:ef:
    47:77:5a:ad:79:9c:21:65:bc:9d:79:a4:aa:18:4b:
    5f:47:26:af:f5:9d:31:45:1c:7e:12:1e:41:33:67:
    5a:d6:03:b0:47:79:87:a6:63:e4:70:8e:c3:bb:55:
    9b:3a:64:ba:be:c2:55:71:1b:8e:b3:a4:29:fa:94:
    c5:70:4b:7b:ef:cf:89:e3:0a:34:e5:be:49:b5:4a:
    04:a2:b2:13:d5:1f:ca:e3:23:ae:44:bb:1d:ee:bf:
    16:fb:aa:97:bf:e3:35:a6:97:02:34:78:c6:40:97:
    d8:00:8e:ca:89:ee:2b:02:ab:8c:cf:3b:37:b7:96:
    69:60:0b:3f:1e:76:96:c3:0f:fc:e8:5e:ba:2e:81:
    4e:df:bc:be:be:19:f5:23:1b:e0:9a:c8:47:21:32:
    3d:8d:b2:ed:2f:65:bf:61:37:cd:9a:94:0d:66:8e:
    3a:3c:c3:e8:5e:d2:ce:93:7c:89:a7:7f:f0:6d:db:
    0f:01:d3:91:8f:2b:b4:c6:ca:f2:76:1d:65:56:b9:
    c2:c6:9e:77:85:ca:c2:bf:05:30:4b:37:39:87:c9:
    c4:40:c4:53:3c:46:90:65:e2:a4:5c:10:ea:a2:b5:
    63:06:a1:33:5e:5b:a2:e6:16:c4:12:b4:93:52:92:
    fd:c6:0f:51:b0:52:77:82:5a:6e:3d:84:74:35:de:
    42:bb:0f:63:1f:f4:71:f2:98:42:37:0e:5b:15:aa:
    75:0a:04:13:0b:ca:a2:ed:fc:9f:00:f2:b1:49:8d:
    e8:12:6c:90:27:12:d7:ef:0f:1b:3d:36:1f:1b:bf:
    c9:a7:30:47:8f:25:d8:16:4b:43:4f:9a:d8:be:0a:
    b4:5e:66:78:95:19:b6:f1:a9:13:b3:b9:ad:eb:17:
    19:03:45:fb:2d:cf:d6:2b:a6:64:f3:08:e3:a4:b7:
    13:5d:73:72:ac:40:47:3c:da:7f:89:dc:be:ba:c3:
    ee:34:2d:f0:ce:21:fc:86:e2:28:1f:19:62:2e:f2:
    ae:dd:ea:16:3d:9e:27:c7:e7:8d:e8:4d:55:05:b9:
    76:36:88:4a:ce:bf:18:b5:49:e4:6f:9d:a6:ad:87:
    b6:f0:b3:2b:57:3c:5d:c9:e6:eb:de:68:52:0d:63:
    d9:e9:c8:80:41:92:7d:3a:cf:a7:b5:cf:f8:f4:9b:
    c2:43:a2:53:1c:18:6c:49:c8:a9:43:35:08:48:2a:
    70:87:6d:fd:97:72:00:d6:97:88:ac:3c:ec:d9:2a:
    1e:2d:09:10:e5:3d:9f:f2:6f:8b:fe:a6:be:e0:3b:
    21:86:58:3f:cc:a0:b6:99:83:b0:eb:b0:44:1b:b6:
    ea:77:7b
Exponent: 65537 (0x10001)
```

CSRを生成します
```
$ openssl req -new -sha256 -key key.pem > localhost.csr
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.
-----
Country Name (2 letter code) [AU]:JP
State or Province Name (full name) [Some-State]:Saitama Pref
Locality Name (eg, city) []:Kawaguchi
Organization Name (eg, company) [Internet Widgits Pty Ltd]:Test Company
Organizational Unit Name (eg, section) []:
Common Name (e.g. server FQDN or YOUR name) []:example.co.jp
Email Address []:

Please enter the following 'extra' attributes
to be sent with your certificate request
A challenge password []:
An optional company name []:
```

生成されたlocalhost.csrをcatします。
```
-----BEGIN CERTIFICATE REQUEST-----
MIIErDCCApQCAQAwZzELMAkGA1UEBhMCSlAxFTATBgNVBAgMDFNhaXRhbWEgUHJl
ZjESMBAGA1UEBwwJS2F3YWd1Y2hpMRUwEwYDVQQKDAxUZXN0IENvbXBhbnkxFjAU
BgNVBAMMDWV4YW1wbGUuY28uanAwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIK
AoICAQCkjcq/GOcLmkvekQs/70d3Wq15nCFlvJ15pKoYS19HJq/1nTFFHH4SHkEz
Z1rWA7BHeYemY+RwjsO7VZs6ZLq+wlVxG46zpCn6lMVwS3vvz4njCjTlvkm1SgSi
shPVH8rjI65Eux3uvxb7qpe/4zWmlwI0eMZAl9gAjsqJ7isCq4zPOze3lmlgCz8e
dpbDD/zoXrougU7fvL6+GfUjG+CayEchMj2Nsu0vZb9hN82alA1mjjo8w+he0s6T
fImnf/Bt2w8B05GPK7TGyvJ2HWVWucLGnneFysK/BTBLNzmHycRAxFM8RpBl4qRc
EOqitWMGoTNeW6LmFsQStJNSkv3GD1GwUneCWm49hHQ13kK7D2Mf9HHymEI3DlsV
qnUKBBMLyqLt/J8A8rFJjegSbJAnEtfvDxs9Nh8bv8mnMEePJdgWS0NPmti+CrRe
ZniVGbbxqROzua3rFxkDRfstz9YrpmTzCOOktxNdc3KsQEc82n+J3L66w+40LfDO
IfyG4igfGWIu8q7d6hY9nifH543oTVUFuXY2iErOvxi1SeRvnaath7bwsytXPF3J
5uveaFINY9npyIBBkn06z6e1z/j0m8JDolMcGGxJyKlDNQhIKnCHbf2XcgDWl4is
POzZKh4tCRDlPZ/yb4v+pr7gOyGGWD/MoLaZg7DrsEQbtup3ewIDAQABoAAwDQYJ
KoZIhvcNAQELBQADggIBAIpZrz+0cHZo/suRj1hS3T6Xis41b4zCYM6eklf3nAu0
8gA0vV2eIImT2Wf1FEh+1HN/gzR9Q/8QNk7g730h5G5GX8sngrUcfKrD/IH95VUt
ARtK7Oy2NV/iqcphSHnV+hE6Xx9EmGcf25hVifeGMYgAUxQP6DJZJ2fshPXLZbFI
292ioocwENJwDJ37RF6c3RKDAc1iVXJL4jgERfWbj83mRuy6hW61ok3QuIoNLoR0
azCjifXHlbxsTD02tSafgDimnOttqDF+O0FSD/79hGPNWIPM81YzhEpMuwDquG5a
dniv9phnsdzC9bJkXwxg0E4oWBOsWQFCHroRZrJxu4QUgx0RBcV2t9BZm64q4TVY
yPzG9aBOQ8YXE8I+Iy7rbk8PgFSbzPzx1gUPPEba3Mm4+OQHcsCvZ5qxnI/qOBL4
6KImPgytFqdubJtOzqXEY+hoooxWEZ6wDX9mBhZvMgxHx8oG75Up2zTOK6VL6Mq5
ivLYRE+byvijovEPOFHfgE6lrTByygp0ZI8esT87I/xdEOW8WYyW0EvnLGXZOWCz
aniTzqoWKHLVh3kWfihga+4e9bqoERnf3+NWb8fE2pKDZz88hgCYbagLdAARoe5U
bES7k39LBpI7eUrXQbv6Sye8AgFOKhMm7yoNtN8xBStfm6wCGVKb3QM6RD205Vuv
-----END CERTIFICATE REQUEST-----
```

localhost.csrを可視化します
```
$ openssl req -text -noout -in localhost.csr
Certificate Request:
    Data:
        Version: 1 (0x0)
        Subject: C = JP, ST = Saitama Pref, L = Kawaguchi, O = Test Company, CN = example.co.jp
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption
                Public-Key: (4096 bit)
                Modulus:
                    00:a4:8d:ca:bf:18:e7:0b:9a:4b:de:91:0b:3f:ef:
                    47:77:5a:ad:79:9c:21:65:bc:9d:79:a4:aa:18:4b:
                    5f:47:26:af:f5:9d:31:45:1c:7e:12:1e:41:33:67:
                    5a:d6:03:b0:47:79:87:a6:63:e4:70:8e:c3:bb:55:
                    9b:3a:64:ba:be:c2:55:71:1b:8e:b3:a4:29:fa:94:
                    c5:70:4b:7b:ef:cf:89:e3:0a:34:e5:be:49:b5:4a:
                    04:a2:b2:13:d5:1f:ca:e3:23:ae:44:bb:1d:ee:bf:
                    16:fb:aa:97:bf:e3:35:a6:97:02:34:78:c6:40:97:
                    d8:00:8e:ca:89:ee:2b:02:ab:8c:cf:3b:37:b7:96:
                    69:60:0b:3f:1e:76:96:c3:0f:fc:e8:5e:ba:2e:81:
                    4e:df:bc:be:be:19:f5:23:1b:e0:9a:c8:47:21:32:
                    3d:8d:b2:ed:2f:65:bf:61:37:cd:9a:94:0d:66:8e:
                    3a:3c:c3:e8:5e:d2:ce:93:7c:89:a7:7f:f0:6d:db:
                    0f:01:d3:91:8f:2b:b4:c6:ca:f2:76:1d:65:56:b9:
                    c2:c6:9e:77:85:ca:c2:bf:05:30:4b:37:39:87:c9:
                    c4:40:c4:53:3c:46:90:65:e2:a4:5c:10:ea:a2:b5:
                    63:06:a1:33:5e:5b:a2:e6:16:c4:12:b4:93:52:92:
                    fd:c6:0f:51:b0:52:77:82:5a:6e:3d:84:74:35:de:
                    42:bb:0f:63:1f:f4:71:f2:98:42:37:0e:5b:15:aa:
                    75:0a:04:13:0b:ca:a2:ed:fc:9f:00:f2:b1:49:8d:
                    e8:12:6c:90:27:12:d7:ef:0f:1b:3d:36:1f:1b:bf:
                    c9:a7:30:47:8f:25:d8:16:4b:43:4f:9a:d8:be:0a:
                    b4:5e:66:78:95:19:b6:f1:a9:13:b3:b9:ad:eb:17:
                    19:03:45:fb:2d:cf:d6:2b:a6:64:f3:08:e3:a4:b7:
                    13:5d:73:72:ac:40:47:3c:da:7f:89:dc:be:ba:c3:
                    ee:34:2d:f0:ce:21:fc:86:e2:28:1f:19:62:2e:f2:
                    ae:dd:ea:16:3d:9e:27:c7:e7:8d:e8:4d:55:05:b9:
                    76:36:88:4a:ce:bf:18:b5:49:e4:6f:9d:a6:ad:87:
                    b6:f0:b3:2b:57:3c:5d:c9:e6:eb:de:68:52:0d:63:
                    d9:e9:c8:80:41:92:7d:3a:cf:a7:b5:cf:f8:f4:9b:
                    c2:43:a2:53:1c:18:6c:49:c8:a9:43:35:08:48:2a:
                    70:87:6d:fd:97:72:00:d6:97:88:ac:3c:ec:d9:2a:
                    1e:2d:09:10:e5:3d:9f:f2:6f:8b:fe:a6:be:e0:3b:
                    21:86:58:3f:cc:a0:b6:99:83:b0:eb:b0:44:1b:b6:
                    ea:77:7b
                Exponent: 65537 (0x10001)
        Attributes:
            (none)
            Requested Extensions:
    Signature Algorithm: sha256WithRSAEncryption
    Signature Value:
        8a:59:af:3f:b4:70:76:68:fe:cb:91:8f:58:52:dd:3e:97:8a:
        ce:35:6f:8c:c2:60:ce:9e:92:57:f7:9c:0b:b4:f2:00:34:bd:
        5d:9e:20:89:93:d9:67:f5:14:48:7e:d4:73:7f:83:34:7d:43:
        ff:10:36:4e:e0:ef:7d:21:e4:6e:46:5f:cb:27:82:b5:1c:7c:
        aa:c3:fc:81:fd:e5:55:2d:01:1b:4a:ec:ec:b6:35:5f:e2:a9:
        ca:61:48:79:d5:fa:11:3a:5f:1f:44:98:67:1f:db:98:55:89:
        f7:86:31:88:00:53:14:0f:e8:32:59:27:67:ec:84:f5:cb:65:
        b1:48:db:dd:a2:a2:87:30:10:d2:70:0c:9d:fb:44:5e:9c:dd:
        12:83:01:cd:62:55:72:4b:e2:38:04:45:f5:9b:8f:cd:e6:46:
        ec:ba:85:6e:b5:a2:4d:d0:b8:8a:0d:2e:84:74:6b:30:a3:89:
        f5:c7:95:bc:6c:4c:3d:36:b5:26:9f:80:38:a6:9c:eb:6d:a8:
        31:7e:3b:41:52:0f:fe:fd:84:63:cd:58:83:cc:f3:56:33:84:
        4a:4c:bb:00:ea:b8:6e:5a:76:78:af:f6:98:67:b1:dc:c2:f5:
        b2:64:5f:0c:60:d0:4e:28:58:13:ac:59:01:42:1e:ba:11:66:
        b2:71:bb:84:14:83:1d:11:05:c5:76:b7:d0:59:9b:ae:2a:e1:
        35:58:c8:fc:c6:f5:a0:4e:43:c6:17:13:c2:3e:23:2e:eb:6e:
        4f:0f:80:54:9b:cc:fc:f1:d6:05:0f:3c:46:da:dc:c9:b8:f8:
        e4:07:72:c0:af:67:9a:b1:9c:8f:ea:38:12:f8:e8:a2:26:3e:
        0c:ad:16:a7:6e:6c:9b:4e:ce:a5:c4:63:e8:68:a2:8c:56:11:
        9e:b0:0d:7f:66:06:16:6f:32:0c:47:c7:ca:06:ef:95:29:db:
        34:ce:2b:a5:4b:e8:ca:b9:8a:f2:d8:44:4f:9b:ca:f8:a3:a2:
        f1:0f:38:51:df:80:4e:a5:ad:30:72:ca:0a:74:64:8f:1e:b1:
        3f:3b:23:fc:5d:10:e5:bc:59:8c:96:d0:4b:e7:2c:65:d9:39:
        60:b3:6a:78:93:ce:aa:16:28:72:d5:87:79:16:7e:28:60:6b:
        ee:1e:f5:ba:a8:11:19:df:df:e3:56:6f:c7:c4:da:92:83:67:
        3f:3c:86:00:98:6d:a8:0b:74:00:11:a1:ee:54:6c:44:bb:93:
        7f:4b:06:92:3b:79:4a:d7:41:bb:fa:4b:27:bc:02:01:4e:2a:
        13:26:ef:2a:0d:b4:df:31:05:2b:5f:9b:ac:02:19:52:9b:dd:
        03:3a:44:3d:b4:e5:5b:af
```

生成したCSRを自己署名してサーバ証明書を生成します
```
$ openssl x509 -req -signkey key.pem < localhost.csr > localhost.crt
Certificate request self-signature ok
subject=C = JP, ST = Saitama Pref, L = Kawaguchi, O = Test Company, CN = example.co.jp
```

生成したCSRをcatしてみます。
```
$ cat localhost.crt
-----BEGIN CERTIFICATE-----
MIIFVTCCAz0CFDDsPoLpGRJByw8i1YMGbzgIVhMHMA0GCSqGSIb3DQEBCwUAMGcx
CzAJBgNVBAYTAkpQMRUwEwYDVQQIDAxTYWl0YW1hIFByZWYxEjAQBgNVBAcMCUth
d2FndWNoaTEVMBMGA1UECgwMVGVzdCBDb21wYW55MRYwFAYDVQQDDA1leGFtcGxl
LmNvLmpwMB4XDTIyMTExNDAwMzUwMVoXDTIyMTIxNDAwMzUwMVowZzELMAkGA1UE
BhMCSlAxFTATBgNVBAgMDFNhaXRhbWEgUHJlZjESMBAGA1UEBwwJS2F3YWd1Y2hp
MRUwEwYDVQQKDAxUZXN0IENvbXBhbnkxFjAUBgNVBAMMDWV4YW1wbGUuY28uanAw
ggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCkjcq/GOcLmkvekQs/70d3
Wq15nCFlvJ15pKoYS19HJq/1nTFFHH4SHkEzZ1rWA7BHeYemY+RwjsO7VZs6ZLq+
wlVxG46zpCn6lMVwS3vvz4njCjTlvkm1SgSishPVH8rjI65Eux3uvxb7qpe/4zWm
lwI0eMZAl9gAjsqJ7isCq4zPOze3lmlgCz8edpbDD/zoXrougU7fvL6+GfUjG+Ca
yEchMj2Nsu0vZb9hN82alA1mjjo8w+he0s6TfImnf/Bt2w8B05GPK7TGyvJ2HWVW
ucLGnneFysK/BTBLNzmHycRAxFM8RpBl4qRcEOqitWMGoTNeW6LmFsQStJNSkv3G
D1GwUneCWm49hHQ13kK7D2Mf9HHymEI3DlsVqnUKBBMLyqLt/J8A8rFJjegSbJAn
EtfvDxs9Nh8bv8mnMEePJdgWS0NPmti+CrReZniVGbbxqROzua3rFxkDRfstz9Yr
pmTzCOOktxNdc3KsQEc82n+J3L66w+40LfDOIfyG4igfGWIu8q7d6hY9nifH543o
TVUFuXY2iErOvxi1SeRvnaath7bwsytXPF3J5uveaFINY9npyIBBkn06z6e1z/j0
m8JDolMcGGxJyKlDNQhIKnCHbf2XcgDWl4isPOzZKh4tCRDlPZ/yb4v+pr7gOyGG
WD/MoLaZg7DrsEQbtup3ewIDAQABMA0GCSqGSIb3DQEBCwUAA4ICAQAVpxq5komQ
Yr9k+iKpDz+ftMDaL3Ha2WS5vMvqQaAwRfsgm6POKefgq3LUdGHNeYHbNjSAm+aQ
GTp2Q8fPc7idet8mUK1MRu0/Sp2T+3wVly/uh0EtSuuiBBE8bokxjnaSbu1nJcIT
73i6led3qvqoQBUjO+svzoZmdsHa4yeVdGqKplNnAQB80b7zxlXYGIPLrU4tbJMb
saIrn3kJ7RSNHdH4j5pUwGxubL1NQxMVOUknKzIBCvZCeArbAFzGLULVSLutcxi4
IsczvG4IyEbUW16GS4njSpQ1Vadbdo7sdAdHg8RYBMgQqAREOXZLNP54enfyKbgz
nLwhkwTy/5ySDg3ECHS2DxO7oVNLzvPy5e0j4eEZWrVliUcRxQYxj33hxz3DRJzT
7QyKj+WklekpURcDBW8wHZnSB1Mj7sMt5++xV9iSrIe0l5EmTbfaRsSDAH1XDYf6
uOBRP2PhgChgO5KU/8dVvi2W2XfHUHIqdZXQDgBPtw4vVB5dF6qWtTmnXMYwX/PD
9ULcR3KzJv9kINUfaTZZJg1PwwHf0xbz3n5blkqZ2dh2DT0lNqVDfl33zNXB3YtW
r0iPaPA9CJec0cVq7QRfsh4nq27NwfTT9Y8Yhe3Tj8AawftmoBnaTg6yY/8gSqS5
j1rgS2Ubeu+BLRWNVnnKT39jadLWIspguQ==
-----END CERTIFICATE-----
```

生成したサーバ証明書を可視化します
```
$ openssl x509 -text -noout -in localhost.crt
Certificate:
    Data:
        Version: 1 (0x0)
        Serial Number:
            30:ec:3e:82:e9:19:12:41:cb:0f:22:d5:83:06:6f:38:08:56:13:07
        Signature Algorithm: sha256WithRSAEncryption
        Issuer: C = JP, ST = Saitama Pref, L = Kawaguchi, O = Test Company, CN = example.co.jp
        Validity
            Not Before: Nov 14 00:35:01 2022 GMT
            Not After : Dec 14 00:35:01 2022 GMT
        Subject: C = JP, ST = Saitama Pref, L = Kawaguchi, O = Test Company, CN = example.co.jp
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption
                Public-Key: (4096 bit)
                Modulus:
                    00:a4:8d:ca:bf:18:e7:0b:9a:4b:de:91:0b:3f:ef:
                    47:77:5a:ad:79:9c:21:65:bc:9d:79:a4:aa:18:4b:
                    5f:47:26:af:f5:9d:31:45:1c:7e:12:1e:41:33:67:
                    5a:d6:03:b0:47:79:87:a6:63:e4:70:8e:c3:bb:55:
                    9b:3a:64:ba:be:c2:55:71:1b:8e:b3:a4:29:fa:94:
                    c5:70:4b:7b:ef:cf:89:e3:0a:34:e5:be:49:b5:4a:
                    04:a2:b2:13:d5:1f:ca:e3:23:ae:44:bb:1d:ee:bf:
                    16:fb:aa:97:bf:e3:35:a6:97:02:34:78:c6:40:97:
                    d8:00:8e:ca:89:ee:2b:02:ab:8c:cf:3b:37:b7:96:
                    69:60:0b:3f:1e:76:96:c3:0f:fc:e8:5e:ba:2e:81:
                    4e:df:bc:be:be:19:f5:23:1b:e0:9a:c8:47:21:32:
                    3d:8d:b2:ed:2f:65:bf:61:37:cd:9a:94:0d:66:8e:
                    3a:3c:c3:e8:5e:d2:ce:93:7c:89:a7:7f:f0:6d:db:
                    0f:01:d3:91:8f:2b:b4:c6:ca:f2:76:1d:65:56:b9:
                    c2:c6:9e:77:85:ca:c2:bf:05:30:4b:37:39:87:c9:
                    c4:40:c4:53:3c:46:90:65:e2:a4:5c:10:ea:a2:b5:
                    63:06:a1:33:5e:5b:a2:e6:16:c4:12:b4:93:52:92:
                    fd:c6:0f:51:b0:52:77:82:5a:6e:3d:84:74:35:de:
                    42:bb:0f:63:1f:f4:71:f2:98:42:37:0e:5b:15:aa:
                    75:0a:04:13:0b:ca:a2:ed:fc:9f:00:f2:b1:49:8d:
                    e8:12:6c:90:27:12:d7:ef:0f:1b:3d:36:1f:1b:bf:
                    c9:a7:30:47:8f:25:d8:16:4b:43:4f:9a:d8:be:0a:
                    b4:5e:66:78:95:19:b6:f1:a9:13:b3:b9:ad:eb:17:
                    19:03:45:fb:2d:cf:d6:2b:a6:64:f3:08:e3:a4:b7:
                    13:5d:73:72:ac:40:47:3c:da:7f:89:dc:be:ba:c3:
                    ee:34:2d:f0:ce:21:fc:86:e2:28:1f:19:62:2e:f2:
                    ae:dd:ea:16:3d:9e:27:c7:e7:8d:e8:4d:55:05:b9:
                    76:36:88:4a:ce:bf:18:b5:49:e4:6f:9d:a6:ad:87:
                    b6:f0:b3:2b:57:3c:5d:c9:e6:eb:de:68:52:0d:63:
                    d9:e9:c8:80:41:92:7d:3a:cf:a7:b5:cf:f8:f4:9b:
                    c2:43:a2:53:1c:18:6c:49:c8:a9:43:35:08:48:2a:
                    70:87:6d:fd:97:72:00:d6:97:88:ac:3c:ec:d9:2a:
                    1e:2d:09:10:e5:3d:9f:f2:6f:8b:fe:a6:be:e0:3b:
                    21:86:58:3f:cc:a0:b6:99:83:b0:eb:b0:44:1b:b6:
                    ea:77:7b
                Exponent: 65537 (0x10001)
    Signature Algorithm: sha256WithRSAEncryption
    Signature Value:
        15:a7:1a:b9:92:89:90:62:bf:64:fa:22:a9:0f:3f:9f:b4:c0:
        da:2f:71:da:d9:64:b9:bc:cb:ea:41:a0:30:45:fb:20:9b:a3:
        ce:29:e7:e0:ab:72:d4:74:61:cd:79:81:db:36:34:80:9b:e6:
        90:19:3a:76:43:c7:cf:73:b8:9d:7a:df:26:50:ad:4c:46:ed:
        3f:4a:9d:93:fb:7c:15:97:2f:ee:87:41:2d:4a:eb:a2:04:11:
        3c:6e:89:31:8e:76:92:6e:ed:67:25:c2:13:ef:78:ba:95:e7:
        77:aa:fa:a8:40:15:23:3b:eb:2f:ce:86:66:76:c1:da:e3:27:
        95:74:6a:8a:a6:53:67:01:00:7c:d1:be:f3:c6:55:d8:18:83:
        cb:ad:4e:2d:6c:93:1b:b1:a2:2b:9f:79:09:ed:14:8d:1d:d1:
        f8:8f:9a:54:c0:6c:6e:6c:bd:4d:43:13:15:39:49:27:2b:32:
        01:0a:f6:42:78:0a:db:00:5c:c6:2d:42:d5:48:bb:ad:73:18:
        b8:22:c7:33:bc:6e:08:c8:46:d4:5b:5e:86:4b:89:e3:4a:94:
        35:55:a7:5b:76:8e:ec:74:07:47:83:c4:58:04:c8:10:a8:04:
        44:39:76:4b:34:fe:78:7a:77:f2:29:b8:33:9c:bc:21:93:04:
        f2:ff:9c:92:0e:0d:c4:08:74:b6:0f:13:bb:a1:53:4b:ce:f3:
        f2:e5:ed:23:e1:e1:19:5a:b5:65:89:47:11:c5:06:31:8f:7d:
        e1:c7:3d:c3:44:9c:d3:ed:0c:8a:8f:e5:a4:95:e9:29:51:17:
        03:05:6f:30:1d:99:d2:07:53:23:ee:c3:2d:e7:ef:b1:57:d8:
        92:ac:87:b4:97:91:26:4d:b7:da:46:c4:83:00:7d:57:0d:87:
        fa:b8:e0:51:3f:63:e1:80:28:60:3b:92:94:ff:c7:55:be:2d:
        96:d9:77:c7:50:72:2a:75:95:d0:0e:00:4f:b7:0e:2f:54:1e:
        5d:17:aa:96:b5:39:a7:5c:c6:30:5f:f3:c3:f5:42:dc:47:72:
        b3:26:ff:64:20:d5:1f:69:36:59:26:0d:4f:c3:01:df:d3:16:
        f3:de:7e:5b:96:4a:99:d9:d8:76:0d:3d:25:36:a5:43:7e:5d:
        f7:cc:d5:c1:dd:8b:56:af:48:8f:68:f0:3d:08:97:9c:d1:c5:
        6a:ed:04:5f:b2:1e:27:ab:6e:cd:c1:f4:d3:f5:8f:18:85:ed:
        d3:8f:c0:1a:c1:fb:66:a0:19:da:4e:0e:b2:63:ff:20:4a:a4:
        b9:8f:5a:e0:4b:65:1b:7a:ef:81:2d:15:8d:56:79:ca:4f:7f:
        63:69:d2:d6:22:ca:60:b9
```

# まとめ
RSAサーバ証明書の生成を行いました

# 公式情報
- https://www.openssl.org/docs/man1.1.1/man1/openssl-genrsa.html
- https://www.openssl.org/docs/man1.1.1/man1/openssl-rsa.html
