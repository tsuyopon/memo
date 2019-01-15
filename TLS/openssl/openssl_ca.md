# 概要

###

証明書を破棄するには，以下のようにする．
```
$ openssl ca -revoke 01.pem
```

また，破棄を CRL に反映させるためには以下のようにする．

```
$ openssl ca -gencrl -out crl.pem
```

- 参考
  - http://moca.wide.ad.jp/notes/ca_doc/openssl.html
