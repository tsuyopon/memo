# 概要
mmdbについて試してみる

# 詳細
# セットアップ(Ubuntu)
下記でセットアップできる。mmdblookupコマンドも入る
```
sudo apt install libmaxminddb0 libmaxminddb-dev mmdb-bin
```

mmdbファイル自体は下記のリンクから取得します。
- 今回取得したのは「GeoLite2-City.mmdb」を取得した
  - https://github.com/P3TERX/GeoLite.mmdb


mmdblookupを試してみます。
```
 mmdblookup -f ~/GeoLite2-City.mmdb -i 133.2.168.5

  {
    "continent": 
      {
        "code": 
          "AS" <utf8_string>
        "geoname_id": 
          6255147 <uint32>
        "names": 
          {
            "de": 
              "Asien" <utf8_string>
            "en": 
              "Asia" <utf8_string>
            "es": 
              "Asia" <utf8_string>
            "fr": 
              "Asie" <utf8_string>
            "ja": 
              "アジア" <utf8_string>
            "pt-BR": 
              "Ásia" <utf8_string>
            "ru": 
              "Азия" <utf8_string>
            "zh-CN": 
              "亚洲" <utf8_string>
          }
      }
    "country": 
      {
        "geoname_id": 
          1861060 <uint32>
        "iso_code": 
          "JP" <utf8_string>
        "names": 
          {
            "de": 
              "Japan" <utf8_string>
            "en": 
              "Japan" <utf8_string>
            "es": 
              "Japón" <utf8_string>
            "fr": 
              "Japon" <utf8_string>
            "ja": 
              "日本" <utf8_string>
            "pt-BR": 
              "Japão" <utf8_string>
            "ru": 
              "Япония" <utf8_string>
            "zh-CN": 
              "日本" <utf8_string>
          }
      }
    "location": 
      {
        "accuracy_radius": 
          500 <uint16>
        "latitude": 
          35.689700 <double>
        "longitude": 
          139.689500 <double>
        "time_zone": 
          "Asia/Tokyo" <utf8_string>
      }
    "registered_country": 
      {
        "geoname_id": 
          1861060 <uint32>
        "iso_code": 
          "JP" <utf8_string>
        "names": 
          {
            "de": 
              "Japan" <utf8_string>
            "en": 
              "Japan" <utf8_string>
            "es": 
              "Japón" <utf8_string>
            "fr": 
              "Japon" <utf8_string>
            "ja": 
              "日本" <utf8_string>
            "pt-BR": 
              "Japão" <utf8_string>
            "ru": 
              "Япония" <utf8_string>
            "zh-CN": 
              "日本" <utf8_string>
          }
      }
  }
```
