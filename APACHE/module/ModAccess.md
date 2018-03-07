# mod_accessについて
IPアドレス、ネットワーク、ドメインにより制限をかけることができます。
mod_accessの各ディレクティブは以下に対して記述することができます。
- <Directory> 
- <Location> 
- <Files> 
- .htaccess 

# 詳細
### 基本アクセス許可する
```
Order Deny,Allow
```
全ての接続をDenyしてから、全ての接続をAllowしますので全許可となります。

### 基本アクセス拒否する
```
Order Allow,Deny
```
全ての接続をAllowしてから、全ての接続をDenyしますので全許可となります。

### 192.168.0.1のIPと、192.168.10.0/24, 172.10, test.co.jpのネットワーク以外全ての接続を許可
```
Order Deny,Allow
deny from 192.168.0.1
deny from 192.168.10.0/24
deny from 172.10
deny from test.co.jp
```

尚、/24の行は以下のサブネットマスク記載でも問題ありません。
```
deny from 192.168.10.0/255.255.255.0
```

# 参考URL
- Apache2.0
  - http://httpd.apache.org/docs/2.0/ja/mod/mod_access.html
