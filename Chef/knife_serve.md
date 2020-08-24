# 概要
knife serveについて

# とりあえず使ってみる
レポジトリ内部でknife serveを実行します。
```
$ knife serve
Serving files from:
repository at /Users/tsuyoshi/git/test/hello-chef
  One version per cookbook

>> Starting Chef Zero (v15.0.0)...
>> WEBrick (v1.4.2) on Rack (v2.2.3) is listening at http://localhost:8889
>> Press CTRL+C to stop
```

続いて、別のターミナルから情報を取得してみます。

試しにenviroments配下を取得してみます。
```
$ curl -H 'Accept: application/json' localhost:8889/environments
{
  "development": "http://localhost:8889/environments/development",
  "production": "http://localhost:8889/environments/production"
}
```

上記の出力から、enviroments/developmentの情報を取得してみます。
```
$ curl -H 'Accept: application/json' localhost:8889/environments/development
{
  "name": "development",
  "description": "",
  "cookbook_versions": {

  },
  "json_class": "Chef::Environment",
  "chef_type": "environment",
  "default_attributes": {

  },
  "override_attributes": {

  }
}
```

- 参考
  - https://qiita.com/sawanoboly/items/4f363909615d8a76e9e5

