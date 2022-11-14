# 概要
opensslコマンドでDSA証明書を生成する。
DSA証明書は世間的にほとんど存在していないらしい

# 詳細

DSAパラメータを作成する
```
$ openssl dsaparam -out params.pem 3072
```

生成されたparam.pemをcatする。
```
$ cat dsa_param.pem 
-----BEGIN DSA PARAMETERS-----
MIIDKQKCAYEA8A/Cg1rbgsa5Wf9f1vZDAk28JjtLDHqYDETS6MhfBtgnzQ2c2jFx
UTgelVX4Jj53z2vTmdhdGDKK+ar+qs5+6avWhFbs7P8XFGhS5zGzIILwCc4v5Vxq
r3zs++0iIMxnyKFQwPV8UnyKxKb3EbI3SUWSKhmjehlg/laSPO72fWccqbS1xLhZ
9CRTJl5ztzP3AIqms/W8eogrMwiEeTezUD8w45+EleHRozSMxfkH/YJi27Kgs9WP
iHOLUQE4ZCGR/w8a2n1DhwAmT7xhjj+6vqefkyMSam4tu4yfhxh9jkymecyVCj5s
d/JmLoz2JUeRF17gRW6N6GUZ6gL3mesrUqgKzUeR5rQkwe6QgxF99X+JibOgMkoQ
pnBmdtl00a2RxaEvzgC6ueDqUqtqkGVOtv+a91jlNtsvC59jAiZ0LLzFffa5GsZK
DsupzMYN53aZKfF1EtuyFeoz5GbkK5SudHZtk+5NbA7wr8LE5e5PBVlwhDCLcTJK
haR2e6GGlJ5ZAh0A+QkJDugKnwRiuk0RbbdmXe4kUDn/CK0fqfKjiwKCAYEAog94
to23irVT1mlNhb0OaGGA0SGGoBscq76/s/MYnIdB4xTkF50qOw2yGMJOcLgo5/i8
8rmMtApq9myMCABatfWMCNFuVfRrZUbKLmouIQyila8ksjX0BlamEZ5BUKFwv1MB
dkuWZhQxsU+H8r9Yz9zcqqQR3+fuaf2z26AnxuqZ3ZxT79f+0FrZ+/YDxy8tg/5H
4GAGkipzheRnUZzUnhv65RuxWa3kQuGvtGbbR4VBTLyk1CqX4OAIja/rFKKqAJW8
ENMKpWDlNlCudvO3GoVbDGX957lLZ31T+jPg1gHrLH1JV6TW2zVxdm78+ZLmodb2
eTuwXPXwqjo8lUtybM9eV7C923VJvl+8u4+edxw9WyPdzCv/+AyFHdH5XtD0hUOF
xK6A17yB7RDDiQ2AdWMFkY5Nu6lJuWgeqlszMfjqpQBvyW4baY62e5uYsKwAIMIY
LuwNQSZaUi1HwTkyFdyLVbr2hGPfo/Yn9kKglDDt/DHC4aiGSJ00LE47h8bk
-----END DSA PARAMETERS-----
```

DSA秘密鍵を生成する
```
$ openssl gendsa -out key.pem params.pem
```

生成された秘密鍵dsa_private.pemをcatする
```
$ cat key.pem
-----BEGIN PRIVATE KEY-----
MIIDXgIBADCCAzYGByqGSM44BAEwggMpAoIBgQDwD8KDWtuCxrlZ/1/W9kMCTbwm
O0sMepgMRNLoyF8G2CfNDZzaMXFROB6VVfgmPnfPa9OZ2F0YMor5qv6qzn7pq9aE
Vuzs/xcUaFLnMbMggvAJzi/lXGqvfOz77SIgzGfIoVDA9XxSfIrEpvcRsjdJRZIq
GaN6GWD+VpI87vZ9ZxyptLXEuFn0JFMmXnO3M/cAiqaz9bx6iCszCIR5N7NQPzDj
n4SV4dGjNIzF+Qf9gmLbsqCz1Y+Ic4tRAThkIZH/DxrafUOHACZPvGGOP7q+p5+T
IxJqbi27jJ+HGH2OTKZ5zJUKPmx38mYujPYlR5EXXuBFbo3oZRnqAveZ6ytSqArN
R5HmtCTB7pCDEX31f4mJs6AyShCmcGZ22XTRrZHFoS/OALq54OpSq2qQZU62/5r3
WOU22y8Ln2MCJnQsvMV99rkaxkoOy6nMxg3ndpkp8XUS27IV6jPkZuQrlK50dm2T
7k1sDvCvwsTl7k8FWXCEMItxMkqFpHZ7oYaUnlkCHQD5CQkO6AqfBGK6TRFtt2Zd
7iRQOf8IrR+p8qOLAoIBgQCiD3i2jbeKtVPWaU2FvQ5oYYDRIYagGxyrvr+z8xic
h0HjFOQXnSo7DbIYwk5wuCjn+LzyuYy0Cmr2bIwIAFq19YwI0W5V9GtlRsouai4h
DKKVrySyNfQGVqYRnkFQoXC/UwF2S5ZmFDGxT4fyv1jP3NyqpBHf5+5p/bPboCfG
6pndnFPv1/7QWtn79gPHLy2D/kfgYAaSKnOF5GdRnNSeG/rlG7FZreRC4a+0ZttH
hUFMvKTUKpfg4AiNr+sUoqoAlbwQ0wqlYOU2UK5287cahVsMZf3nuUtnfVP6M+DW
AessfUlXpNbbNXF2bvz5kuah1vZ5O7Bc9fCqOjyVS3Jsz15XsL3bdUm+X7y7j553
HD1bI93MK//4DIUd0fle0PSFQ4XEroDXvIHtEMOJDYB1YwWRjk27qUm5aB6qWzMx
+OqlAG/JbhtpjrZ7m5iwrAAgwhgu7A1BJlpSLUfBOTIV3ItVuvaEY9+j9if2QqCU
MO38McLhqIZInTQsTjuHxuQEHwIdAPS/Ehx6JY9hTo5lqdMxz5IeuOfC0fO/3uTs
Dps=
-----END PRIVATE KEY-----
```

秘密鍵から公開鍵を生成する
```
$ openssl dsa -in key.pem -pubout -out public.pem
read DSA key
writing DSA key
```

生成されたpublic.pemをcatする
```
$ cat public.pem 
-----BEGIN PUBLIC KEY-----
MIIExDCCAzYGByqGSM44BAEwggMpAoIBgQDwD8KDWtuCxrlZ/1/W9kMCTbwmO0sM
epgMRNLoyF8G2CfNDZzaMXFROB6VVfgmPnfPa9OZ2F0YMor5qv6qzn7pq9aEVuzs
/xcUaFLnMbMggvAJzi/lXGqvfOz77SIgzGfIoVDA9XxSfIrEpvcRsjdJRZIqGaN6
GWD+VpI87vZ9ZxyptLXEuFn0JFMmXnO3M/cAiqaz9bx6iCszCIR5N7NQPzDjn4SV
4dGjNIzF+Qf9gmLbsqCz1Y+Ic4tRAThkIZH/DxrafUOHACZPvGGOP7q+p5+TIxJq
bi27jJ+HGH2OTKZ5zJUKPmx38mYujPYlR5EXXuBFbo3oZRnqAveZ6ytSqArNR5Hm
tCTB7pCDEX31f4mJs6AyShCmcGZ22XTRrZHFoS/OALq54OpSq2qQZU62/5r3WOU2
2y8Ln2MCJnQsvMV99rkaxkoOy6nMxg3ndpkp8XUS27IV6jPkZuQrlK50dm2T7k1s
DvCvwsTl7k8FWXCEMItxMkqFpHZ7oYaUnlkCHQD5CQkO6AqfBGK6TRFtt2Zd7iRQ
Of8IrR+p8qOLAoIBgQCiD3i2jbeKtVPWaU2FvQ5oYYDRIYagGxyrvr+z8xich0Hj
FOQXnSo7DbIYwk5wuCjn+LzyuYy0Cmr2bIwIAFq19YwI0W5V9GtlRsouai4hDKKV
rySyNfQGVqYRnkFQoXC/UwF2S5ZmFDGxT4fyv1jP3NyqpBHf5+5p/bPboCfG6pnd
nFPv1/7QWtn79gPHLy2D/kfgYAaSKnOF5GdRnNSeG/rlG7FZreRC4a+0ZttHhUFM
vKTUKpfg4AiNr+sUoqoAlbwQ0wqlYOU2UK5287cahVsMZf3nuUtnfVP6M+DWAess
fUlXpNbbNXF2bvz5kuah1vZ5O7Bc9fCqOjyVS3Jsz15XsL3bdUm+X7y7j553HD1b
I93MK//4DIUd0fle0PSFQ4XEroDXvIHtEMOJDYB1YwWRjk27qUm5aB6qWzMx+Oql
AG/JbhtpjrZ7m5iwrAAgwhgu7A1BJlpSLUfBOTIV3ItVuvaEY9+j9if2QqCUMO38
McLhqIZInTQsTjuHxuQDggGGAAKCAYEAkPbwjSjO8daaUj1kwqgR1RkSn8+usPv5
xB15L50wytk+t9tEWGGlpZtkIoYdBcJuxXdwqV/iF5c/WqjMxhohPfYeSV8tJiY2
6VOhmiRLS7yuuI0WTwMEBCQLD4gWJ+qGhlpetpHAb7eykts6wPEiJwucSnb8spjs
5dWfdxr6nikpFkMI3ebziFGtkLQB7fMIcPjBla3qBJ1IStJ2w+ygKTKncx0FqlcL
pCSwJ6P66tcHnIQp8P3MKM704s/OcMIIuksEio/O0kBPgyjRRYjxn7ymb8FFVefk
djpfKNJuUnSKGhLziRfu8lg+vVdEYujlTDTNig39KcqU+ndSGTvPDfHe2ZQ6xe9N
CJm8+gIwdrxd4U6gb1B4L/bNJX+JUQEt2bn/Sn1xLhlmXEgfAw8bmktWAPYRDr/I
o7zM12hDZmbyEUvdVwpA7QGqfkMBz4oqnqfDEySLzma0ZkVVSjnJZD28HHpBrtPD
kd+NTfbFIjU49iQD3ElAiJBNVbQYdA0f
-----END PUBLIC KEY-----
```

CSRを生成する
```
$ openssl req -new -key key.pem -out localhost.csr
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

生成したCSRをcatする
```
$ cat localhost.csr
-----BEGIN CERTIFICATE REQUEST-----
MIIFiDCCBTYCAQAwZzELMAkGA1UEBhMCSlAxFTATBgNVBAgMDFNhaXRhbWEgUHJl
ZjESMBAGA1UEBwwJS2F3YWd1Y2hpMRUwEwYDVQQKDAxUZXN0IENvbXBhbnkxFjAU
BgNVBAMMDWV4YW1wbGUuY28uanAwggTEMIIDNgYHKoZIzjgEATCCAykCggGBAPAP
woNa24LGuVn/X9b2QwJNvCY7Swx6mAxE0ujIXwbYJ80NnNoxcVE4HpVV+CY+d89r
05nYXRgyivmq/qrOfumr1oRW7Oz/FxRoUucxsyCC8AnOL+Vcaq987PvtIiDMZ8ih
UMD1fFJ8isSm9xGyN0lFkioZo3oZYP5Wkjzu9n1nHKm0tcS4WfQkUyZec7cz9wCK
prP1vHqIKzMIhHk3s1A/MOOfhJXh0aM0jMX5B/2CYtuyoLPVj4hzi1EBOGQhkf8P
Gtp9Q4cAJk+8YY4/ur6nn5MjEmpuLbuMn4cYfY5MpnnMlQo+bHfyZi6M9iVHkRde
4EVujehlGeoC95nrK1KoCs1Hkea0JMHukIMRffV/iYmzoDJKEKZwZnbZdNGtkcWh
L84Aurng6lKrapBlTrb/mvdY5TbbLwufYwImdCy8xX32uRrGSg7LqczGDed2mSnx
dRLbshXqM+Rm5CuUrnR2bZPuTWwO8K/CxOXuTwVZcIQwi3EySoWkdnuhhpSeWQId
APkJCQ7oCp8EYrpNEW23Zl3uJFA5/witH6nyo4sCggGBAKIPeLaNt4q1U9ZpTYW9
DmhhgNEhhqAbHKu+v7PzGJyHQeMU5BedKjsNshjCTnC4KOf4vPK5jLQKavZsjAgA
WrX1jAjRblX0a2VGyi5qLiEMopWvJLI19AZWphGeQVChcL9TAXZLlmYUMbFPh/K/
WM/c3KqkEd/n7mn9s9ugJ8bqmd2cU+/X/tBa2fv2A8cvLYP+R+BgBpIqc4XkZ1Gc
1J4b+uUbsVmt5ELhr7Rm20eFQUy8pNQql+DgCI2v6xSiqgCVvBDTCqVg5TZQrnbz
txqFWwxl/ee5S2d9U/oz4NYB6yx9SVek1ts1cXZu/PmS5qHW9nk7sFz18Ko6PJVL
cmzPXlewvdt1Sb5fvLuPnnccPVsj3cwr//gMhR3R+V7Q9IVDhcSugNe8ge0Qw4kN
gHVjBZGOTbupSbloHqpbMzH46qUAb8luG2mOtnubmLCsACDCGC7sDUEmWlItR8E5
MhXci1W69oRj36P2J/ZCoJQw7fwxwuGohkidNCxOO4fG5AOCAYYAAoIBgQCQ9vCN
KM7x1ppSPWTCqBHVGRKfz66w+/nEHXkvnTDK2T6320RYYaWlm2Qihh0Fwm7Fd3Cp
X+IXlz9aqMzGGiE99h5JXy0mJjbpU6GaJEtLvK64jRZPAwQEJAsPiBYn6oaGWl62
kcBvt7KS2zrA8SInC5xKdvyymOzl1Z93GvqeKSkWQwjd5vOIUa2QtAHt8whw+MGV
reoEnUhK0nbD7KApMqdzHQWqVwukJLAno/rq1wechCnw/cwozvTiz85wwgi6SwSK
j87SQE+DKNFFiPGfvKZvwUVV5+R2Ol8o0m5SdIoaEvOJF+7yWD69V0Ri6OVMNM2K
Df0pypT6d1IZO88N8d7ZlDrF700Imbz6AjB2vF3hTqBvUHgv9s0lf4lRAS3Zuf9K
fXEuGWZcSB8DDxuaS1YA9hEOv8ijvMzXaENmZvIRS91XCkDtAap+QwHPiiqep8MT
JIvOZrRmRVVKOclkPbwcekGu08OR341N9sUiNTj2JAPcSUCIkE1VtBh0DR+gADAL
BglghkgBZQMEAwIDPwAwPAIccbuM2IGzPsnGLbts8HUkokpMNGQC/JQJBfIP5gIc
P0h7xtLrK4B5kN0QuYMd7D+7VOj1DiwLf8L1gg==
-----END CERTIFICATE REQUEST-----
```

可視化してみます
```
$ openssl req -text -noout -in localhost.csr
Certificate Request:
    Data:
        Version: 1 (0x0)
        Subject: C = JP, ST = Saitama Pref, L = Kawaguchi, O = Test Company, CN = example.co.jp
        Subject Public Key Info:
            Public Key Algorithm: dsaEncryption
                Public-Key: (3072 bit)
                pub: 
                    00:90:f6:f0:8d:28:ce:f1:d6:9a:52:3d:64:c2:a8:
                    11:d5:19:12:9f:cf:ae:b0:fb:f9:c4:1d:79:2f:9d:
                    30:ca:d9:3e:b7:db:44:58:61:a5:a5:9b:64:22:86:
                    1d:05:c2:6e:c5:77:70:a9:5f:e2:17:97:3f:5a:a8:
                    cc:c6:1a:21:3d:f6:1e:49:5f:2d:26:26:36:e9:53:
                    a1:9a:24:4b:4b:bc:ae:b8:8d:16:4f:03:04:04:24:
                    0b:0f:88:16:27:ea:86:86:5a:5e:b6:91:c0:6f:b7:
                    b2:92:db:3a:c0:f1:22:27:0b:9c:4a:76:fc:b2:98:
                    ec:e5:d5:9f:77:1a:fa:9e:29:29:16:43:08:dd:e6:
                    f3:88:51:ad:90:b4:01:ed:f3:08:70:f8:c1:95:ad:
                    ea:04:9d:48:4a:d2:76:c3:ec:a0:29:32:a7:73:1d:
                    05:aa:57:0b:a4:24:b0:27:a3:fa:ea:d7:07:9c:84:
                    29:f0:fd:cc:28:ce:f4:e2:cf:ce:70:c2:08:ba:4b:
                    04:8a:8f:ce:d2:40:4f:83:28:d1:45:88:f1:9f:bc:
                    a6:6f:c1:45:55:e7:e4:76:3a:5f:28:d2:6e:52:74:
                    8a:1a:12:f3:89:17:ee:f2:58:3e:bd:57:44:62:e8:
                    e5:4c:34:cd:8a:0d:fd:29:ca:94:fa:77:52:19:3b:
                    cf:0d:f1:de:d9:94:3a:c5:ef:4d:08:99:bc:fa:02:
                    30:76:bc:5d:e1:4e:a0:6f:50:78:2f:f6:cd:25:7f:
                    89:51:01:2d:d9:b9:ff:4a:7d:71:2e:19:66:5c:48:
                    1f:03:0f:1b:9a:4b:56:00:f6:11:0e:bf:c8:a3:bc:
                    cc:d7:68:43:66:66:f2:11:4b:dd:57:0a:40:ed:01:
                    aa:7e:43:01:cf:8a:2a:9e:a7:c3:13:24:8b:ce:66:
                    b4:66:45:55:4a:39:c9:64:3d:bc:1c:7a:41:ae:d3:
                    c3:91:df:8d:4d:f6:c5:22:35:38:f6:24:03:dc:49:
                    40:88:90:4d:55:b4:18:74:0d:1f
                P:   
                    00:f0:0f:c2:83:5a:db:82:c6:b9:59:ff:5f:d6:f6:
                    43:02:4d:bc:26:3b:4b:0c:7a:98:0c:44:d2:e8:c8:
                    5f:06:d8:27:cd:0d:9c:da:31:71:51:38:1e:95:55:
                    f8:26:3e:77:cf:6b:d3:99:d8:5d:18:32:8a:f9:aa:
                    fe:aa:ce:7e:e9:ab:d6:84:56:ec:ec:ff:17:14:68:
                    52:e7:31:b3:20:82:f0:09:ce:2f:e5:5c:6a:af:7c:
                    ec:fb:ed:22:20:cc:67:c8:a1:50:c0:f5:7c:52:7c:
                    8a:c4:a6:f7:11:b2:37:49:45:92:2a:19:a3:7a:19:
                    60:fe:56:92:3c:ee:f6:7d:67:1c:a9:b4:b5:c4:b8:
                    59:f4:24:53:26:5e:73:b7:33:f7:00:8a:a6:b3:f5:
                    bc:7a:88:2b:33:08:84:79:37:b3:50:3f:30:e3:9f:
                    84:95:e1:d1:a3:34:8c:c5:f9:07:fd:82:62:db:b2:
                    a0:b3:d5:8f:88:73:8b:51:01:38:64:21:91:ff:0f:
                    1a:da:7d:43:87:00:26:4f:bc:61:8e:3f:ba:be:a7:
                    9f:93:23:12:6a:6e:2d:bb:8c:9f:87:18:7d:8e:4c:
                    a6:79:cc:95:0a:3e:6c:77:f2:66:2e:8c:f6:25:47:
                    91:17:5e:e0:45:6e:8d:e8:65:19:ea:02:f7:99:eb:
                    2b:52:a8:0a:cd:47:91:e6:b4:24:c1:ee:90:83:11:
                    7d:f5:7f:89:89:b3:a0:32:4a:10:a6:70:66:76:d9:
                    74:d1:ad:91:c5:a1:2f:ce:00:ba:b9:e0:ea:52:ab:
                    6a:90:65:4e:b6:ff:9a:f7:58:e5:36:db:2f:0b:9f:
                    63:02:26:74:2c:bc:c5:7d:f6:b9:1a:c6:4a:0e:cb:
                    a9:cc:c6:0d:e7:76:99:29:f1:75:12:db:b2:15:ea:
                    33:e4:66:e4:2b:94:ae:74:76:6d:93:ee:4d:6c:0e:
                    f0:af:c2:c4:e5:ee:4f:05:59:70:84:30:8b:71:32:
                    4a:85:a4:76:7b:a1:86:94:9e:59
                Q:   
                    00:f9:09:09:0e:e8:0a:9f:04:62:ba:4d:11:6d:b7:
                    66:5d:ee:24:50:39:ff:08:ad:1f:a9:f2:a3:8b
                G:   
                    00:a2:0f:78:b6:8d:b7:8a:b5:53:d6:69:4d:85:bd:
                    0e:68:61:80:d1:21:86:a0:1b:1c:ab:be:bf:b3:f3:
                    18:9c:87:41:e3:14:e4:17:9d:2a:3b:0d:b2:18:c2:
                    4e:70:b8:28:e7:f8:bc:f2:b9:8c:b4:0a:6a:f6:6c:
                    8c:08:00:5a:b5:f5:8c:08:d1:6e:55:f4:6b:65:46:
                    ca:2e:6a:2e:21:0c:a2:95:af:24:b2:35:f4:06:56:
                    a6:11:9e:41:50:a1:70:bf:53:01:76:4b:96:66:14:
                    31:b1:4f:87:f2:bf:58:cf:dc:dc:aa:a4:11:df:e7:
                    ee:69:fd:b3:db:a0:27:c6:ea:99:dd:9c:53:ef:d7:
                    fe:d0:5a:d9:fb:f6:03:c7:2f:2d:83:fe:47:e0:60:
                    06:92:2a:73:85:e4:67:51:9c:d4:9e:1b:fa:e5:1b:
                    b1:59:ad:e4:42:e1:af:b4:66:db:47:85:41:4c:bc:
                    a4:d4:2a:97:e0:e0:08:8d:af:eb:14:a2:aa:00:95:
                    bc:10:d3:0a:a5:60:e5:36:50:ae:76:f3:b7:1a:85:
                    5b:0c:65:fd:e7:b9:4b:67:7d:53:fa:33:e0:d6:01:
                    eb:2c:7d:49:57:a4:d6:db:35:71:76:6e:fc:f9:92:
                    e6:a1:d6:f6:79:3b:b0:5c:f5:f0:aa:3a:3c:95:4b:
                    72:6c:cf:5e:57:b0:bd:db:75:49:be:5f:bc:bb:8f:
                    9e:77:1c:3d:5b:23:dd:cc:2b:ff:f8:0c:85:1d:d1:
                    f9:5e:d0:f4:85:43:85:c4:ae:80:d7:bc:81:ed:10:
                    c3:89:0d:80:75:63:05:91:8e:4d:bb:a9:49:b9:68:
                    1e:aa:5b:33:31:f8:ea:a5:00:6f:c9:6e:1b:69:8e:
                    b6:7b:9b:98:b0:ac:00:20:c2:18:2e:ec:0d:41:26:
                    5a:52:2d:47:c1:39:32:15:dc:8b:55:ba:f6:84:63:
                    df:a3:f6:27:f6:42:a0:94:30:ed:fc:31:c2:e1:a8:
                    86:48:9d:34:2c:4e:3b:87:c6:e4
        Attributes:
            (none)
            Requested Extensions:
    Signature Algorithm: dsa_with_SHA256
    Signature Value:
        r:   
            71:bb:8c:d8:81:b3:3e:c9:c6:2d:bb:6c:f0:75:24:
            a2:4a:4c:34:64:02:fc:94:09:05:f2:0f:e6
        s:   
            3f:48:7b:c6:d2:eb:2b:80:79:90:dd:10:b9:83:1d:
            ec:3f:bb:54:e8:f5:0e:2c:0b:7f:c2:f5:82
```


CSRを自身の秘密鍵で署名します。
```
$ openssl x509 -req -signkey key.pem < localhost.csr > localhost.crt
Certificate request self-signature ok
subject=C = JP, ST = Saitama Pref, L = Kawaguchi, O = Test Company, CN = example.co.jp
```

生成したDSAのサーバ証明書を可視化してみます。以下の表示があることを確認してください。
- Signature Algorithm: dsa_with_SHA256 
- Public Key Algorithm: dsaEncryption
```
$ openssl x509 -text -noout -in localhost.crt
Certificate:
    Data:
        Version: 1 (0x0)
        Serial Number:
            2d:8b:24:5b:c7:67:24:68:b2:ae:93:e0:0a:ae:c1:bd:f6:42:2e:44
        Signature Algorithm: dsa_with_SHA256
        Issuer: C = JP, ST = Saitama Pref, L = Kawaguchi, O = Test Company, CN = example.co.jp
        Validity
            Not Before: Nov 14 00:55:20 2022 GMT
            Not After : Dec 14 00:55:20 2022 GMT
        Subject: C = JP, ST = Saitama Pref, L = Kawaguchi, O = Test Company, CN = example.co.jp
        Subject Public Key Info:
            Public Key Algorithm: dsaEncryption
                Public-Key: (3072 bit)
                pub: 
                    00:90:f6:f0:8d:28:ce:f1:d6:9a:52:3d:64:c2:a8:
                    11:d5:19:12:9f:cf:ae:b0:fb:f9:c4:1d:79:2f:9d:
                    30:ca:d9:3e:b7:db:44:58:61:a5:a5:9b:64:22:86:
                    1d:05:c2:6e:c5:77:70:a9:5f:e2:17:97:3f:5a:a8:
                    cc:c6:1a:21:3d:f6:1e:49:5f:2d:26:26:36:e9:53:
                    a1:9a:24:4b:4b:bc:ae:b8:8d:16:4f:03:04:04:24:
                    0b:0f:88:16:27:ea:86:86:5a:5e:b6:91:c0:6f:b7:
                    b2:92:db:3a:c0:f1:22:27:0b:9c:4a:76:fc:b2:98:
                    ec:e5:d5:9f:77:1a:fa:9e:29:29:16:43:08:dd:e6:
                    f3:88:51:ad:90:b4:01:ed:f3:08:70:f8:c1:95:ad:
                    ea:04:9d:48:4a:d2:76:c3:ec:a0:29:32:a7:73:1d:
                    05:aa:57:0b:a4:24:b0:27:a3:fa:ea:d7:07:9c:84:
                    29:f0:fd:cc:28:ce:f4:e2:cf:ce:70:c2:08:ba:4b:
                    04:8a:8f:ce:d2:40:4f:83:28:d1:45:88:f1:9f:bc:
                    a6:6f:c1:45:55:e7:e4:76:3a:5f:28:d2:6e:52:74:
                    8a:1a:12:f3:89:17:ee:f2:58:3e:bd:57:44:62:e8:
                    e5:4c:34:cd:8a:0d:fd:29:ca:94:fa:77:52:19:3b:
                    cf:0d:f1:de:d9:94:3a:c5:ef:4d:08:99:bc:fa:02:
                    30:76:bc:5d:e1:4e:a0:6f:50:78:2f:f6:cd:25:7f:
                    89:51:01:2d:d9:b9:ff:4a:7d:71:2e:19:66:5c:48:
                    1f:03:0f:1b:9a:4b:56:00:f6:11:0e:bf:c8:a3:bc:
                    cc:d7:68:43:66:66:f2:11:4b:dd:57:0a:40:ed:01:
                    aa:7e:43:01:cf:8a:2a:9e:a7:c3:13:24:8b:ce:66:
                    b4:66:45:55:4a:39:c9:64:3d:bc:1c:7a:41:ae:d3:
                    c3:91:df:8d:4d:f6:c5:22:35:38:f6:24:03:dc:49:
                    40:88:90:4d:55:b4:18:74:0d:1f
                P:   
                    00:f0:0f:c2:83:5a:db:82:c6:b9:59:ff:5f:d6:f6:
                    43:02:4d:bc:26:3b:4b:0c:7a:98:0c:44:d2:e8:c8:
                    5f:06:d8:27:cd:0d:9c:da:31:71:51:38:1e:95:55:
                    f8:26:3e:77:cf:6b:d3:99:d8:5d:18:32:8a:f9:aa:
                    fe:aa:ce:7e:e9:ab:d6:84:56:ec:ec:ff:17:14:68:
                    52:e7:31:b3:20:82:f0:09:ce:2f:e5:5c:6a:af:7c:
                    ec:fb:ed:22:20:cc:67:c8:a1:50:c0:f5:7c:52:7c:
                    8a:c4:a6:f7:11:b2:37:49:45:92:2a:19:a3:7a:19:
                    60:fe:56:92:3c:ee:f6:7d:67:1c:a9:b4:b5:c4:b8:
                    59:f4:24:53:26:5e:73:b7:33:f7:00:8a:a6:b3:f5:
                    bc:7a:88:2b:33:08:84:79:37:b3:50:3f:30:e3:9f:
                    84:95:e1:d1:a3:34:8c:c5:f9:07:fd:82:62:db:b2:
                    a0:b3:d5:8f:88:73:8b:51:01:38:64:21:91:ff:0f:
                    1a:da:7d:43:87:00:26:4f:bc:61:8e:3f:ba:be:a7:
                    9f:93:23:12:6a:6e:2d:bb:8c:9f:87:18:7d:8e:4c:
                    a6:79:cc:95:0a:3e:6c:77:f2:66:2e:8c:f6:25:47:
                    91:17:5e:e0:45:6e:8d:e8:65:19:ea:02:f7:99:eb:
                    2b:52:a8:0a:cd:47:91:e6:b4:24:c1:ee:90:83:11:
                    7d:f5:7f:89:89:b3:a0:32:4a:10:a6:70:66:76:d9:
                    74:d1:ad:91:c5:a1:2f:ce:00:ba:b9:e0:ea:52:ab:
                    6a:90:65:4e:b6:ff:9a:f7:58:e5:36:db:2f:0b:9f:
                    63:02:26:74:2c:bc:c5:7d:f6:b9:1a:c6:4a:0e:cb:
                    a9:cc:c6:0d:e7:76:99:29:f1:75:12:db:b2:15:ea:
                    33:e4:66:e4:2b:94:ae:74:76:6d:93:ee:4d:6c:0e:
                    f0:af:c2:c4:e5:ee:4f:05:59:70:84:30:8b:71:32:
                    4a:85:a4:76:7b:a1:86:94:9e:59
                Q:   
                    00:f9:09:09:0e:e8:0a:9f:04:62:ba:4d:11:6d:b7:
                    66:5d:ee:24:50:39:ff:08:ad:1f:a9:f2:a3:8b
                G:   
                    00:a2:0f:78:b6:8d:b7:8a:b5:53:d6:69:4d:85:bd:
                    0e:68:61:80:d1:21:86:a0:1b:1c:ab:be:bf:b3:f3:
                    18:9c:87:41:e3:14:e4:17:9d:2a:3b:0d:b2:18:c2:
                    4e:70:b8:28:e7:f8:bc:f2:b9:8c:b4:0a:6a:f6:6c:
                    8c:08:00:5a:b5:f5:8c:08:d1:6e:55:f4:6b:65:46:
                    ca:2e:6a:2e:21:0c:a2:95:af:24:b2:35:f4:06:56:
                    a6:11:9e:41:50:a1:70:bf:53:01:76:4b:96:66:14:
                    31:b1:4f:87:f2:bf:58:cf:dc:dc:aa:a4:11:df:e7:
                    ee:69:fd:b3:db:a0:27:c6:ea:99:dd:9c:53:ef:d7:
                    fe:d0:5a:d9:fb:f6:03:c7:2f:2d:83:fe:47:e0:60:
                    06:92:2a:73:85:e4:67:51:9c:d4:9e:1b:fa:e5:1b:
                    b1:59:ad:e4:42:e1:af:b4:66:db:47:85:41:4c:bc:
                    a4:d4:2a:97:e0:e0:08:8d:af:eb:14:a2:aa:00:95:
                    bc:10:d3:0a:a5:60:e5:36:50:ae:76:f3:b7:1a:85:
                    5b:0c:65:fd:e7:b9:4b:67:7d:53:fa:33:e0:d6:01:
                    eb:2c:7d:49:57:a4:d6:db:35:71:76:6e:fc:f9:92:
                    e6:a1:d6:f6:79:3b:b0:5c:f5:f0:aa:3a:3c:95:4b:
                    72:6c:cf:5e:57:b0:bd:db:75:49:be:5f:bc:bb:8f:
                    9e:77:1c:3d:5b:23:dd:cc:2b:ff:f8:0c:85:1d:d1:
                    f9:5e:d0:f4:85:43:85:c4:ae:80:d7:bc:81:ed:10:
                    c3:89:0d:80:75:63:05:91:8e:4d:bb:a9:49:b9:68:
                    1e:aa:5b:33:31:f8:ea:a5:00:6f:c9:6e:1b:69:8e:
                    b6:7b:9b:98:b0:ac:00:20:c2:18:2e:ec:0d:41:26:
                    5a:52:2d:47:c1:39:32:15:dc:8b:55:ba:f6:84:63:
                    df:a3:f6:27:f6:42:a0:94:30:ed:fc:31:c2:e1:a8:
                    86:48:9d:34:2c:4e:3b:87:c6:e4
    Signature Algorithm: dsa_with_SHA256
    Signature Value:
        r:   
            00:e5:0c:45:60:af:39:54:4e:d6:77:28:6c:ee:41:
            98:8c:ec:de:6a:e9:0e:61:98:48:d1:00:ea:51
        s:   
            2a:8d:dd:e3:a9:fb:a9:4c:31:c9:65:1c:8a:6c:21:
            f6:7b:ac:19:6e:07:1e:2a:77:58:f6:1a:5d
```

# まとめ
DSAサーバ証明書を発行しました。


# 参考情報
- https://superuser.com/questions/644297/parameters-to-create-a-self-signed-dsa-certificate-on-ubuntu-12-04
- https://kb.swivelsecure.com/w/index.php/Key_and_Certificate_Generation


