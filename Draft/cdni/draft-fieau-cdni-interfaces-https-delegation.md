# CDNI extensions for HTTPS delegation

# 解決したい問題
経路に従って1つもしくは複数のCDNに対してHTTPSでコンテンツを提供することはクレデンシャル管理が必要となります。
特にこれは１つのエンティティから信頼された別のエンティティに対して配信を委譲したい場合などに起こります。

このドキュメントでは、アップストリームCDN(uCDN)とダウンロードストリームCDN(dCDN)においてHTTPS委譲のための方法を提供します。


# 解決方法

- CDNIのオブジェクトに新しくsupportedDelegationMethodsを定義

```
PathMatch:
{
 "path-pattern": {
      "pattern": "/movies/*",
      "case-sensitive": true
 },
 "path-metadata": {
   "type": "MI.PathMetadata",
      "href": "https://metadata.ucdn.example/video.example.com/movies"
 }
}
```

PathMetadataは次のように規定する。
```
PathMetadata:
{
    "metadata": [
     {
     "generic-metadata-type": "MI.TimeWindowACL",
     "generic-metadata-value": {
      "times": [
       "windows": [
       {
        "start": "1213948800",
        "end": "1478047392"
       }
      ],
      "action": "allow",
  }},
  {
     "generic-metadata-type": "MI.SecureDelegation"
     "generic-metadata-type": {
      "supportedDelegationMethods": ["MI.AcmeStarDelegationMethod"],
     }
     }
 ]
}
```

上記のsupportedDelegationMethodsで指定される方法は次のような形式で記述する。
```
   AcmeStarDelegationMethod: {
       "generic-metadata-type": "MI.AcmeStarDelegationMethod",
       "generic-metadata-value": {
           "starproxy": "10.2.2.2",
           "acmeserver": "10.2.3.3",
           "credentialslocationuri": "www.ucdn.com/credentials",
           "periodicity": 36000
       }
   }
```

上記で指定するメソッドには次の種類がある。
- AcmeStarDelegationMethod (https://tools.ietf.org/html/draft-fieau-cdni-interfaces-https-delegation-04#section-4.2.1)
- SubcertsDelegationMethod (https://tools.ietf.org/html/draft-fieau-cdni-interfaces-https-delegation-04#section-4.2.2)
- LurkDelegationMethod     (https://tools.ietf.org/html/draft-fieau-cdni-interfaces-https-delegation-04#section-4.2.3)

上記それぞれのパターンでの記述例を記載しておく。
```
   AcmeStarDelegationMethod: {
       "generic-metadata-type": "MI.AcmeStarDelegationMethod",
       "generic-metadata-value": {
           "starproxy": "10.2.2.2",
           "acmeserver": "10.2.3.3",
           "credentialslocationuri": "www.ucdn.com/credentials",
           "periodicity": 36000
       }
   }
```

```
   SubcertsDelegationMethod: {
       "generic-metadata-type": "MI.SubcertsDelegationMethod",
       "generic-metadata-value": {
           "credentialsdelegatingentity": "10.2.2.2",
           "credentialsrecepiententity": "10.2.3.3",
           "credentialslocationuri": "www.ucdn.com/credentials",
           "periodicity": 36000
       }
   }
```

```
   LurkDelegationMethod: {
       "generic-metadata-type": "MI.LurkDelegationMethod",
       "generic-metadata-value": {
           "keyserver": "10.2.2.2",
       }
   }
```

# 参考URL
- https://tools.ietf.org/html/draft-fieau-cdni-interfaces-https-delegation-04
