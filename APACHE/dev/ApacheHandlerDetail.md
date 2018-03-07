# 概要
Apacheハンドラの詳細について


### 適用範囲がRoot直下なのかDirectoryやLocationでも有効なのか知りたい
ディレクティブを指定するマクロとして次のマクロが存在します。
```
AP_INIT_TAKE1(directive, func, info, where, help)
```

上記のwhereではディレクティブの適用範囲を指定することができるようです。
- ACCESS_CONF
  - httpd.conf 内の <Directory> か <Location> の中． 
- RSRC_CONF
  - httpd.conf 内の <Directory> 及び <Location> の外．

参考URL
- http://dsas.blog.klab.org/archives/50596409.html

