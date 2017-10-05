# 概要
Screwdriver.cdとは2017年1月に米Yahooから継続的プラットフォームとしてオープンソースに公開されている。
- 利用にはPython 2.7、Docker 1.12、Docker Compose 1.8.1などが必要。

screwdriver全体像は以下を参考に
- http://docs.screwdriver.cd/cluster-management/

# 詳細

### サンプル
- https://github.com/screwdriver-cd-test

### プロジェクト画面
こんな感じ
- https://cd.screwdriver.cd/pipelines/114

### ローカルで動かしたい
以下に方法はあるが、要件はMac OSX 10.10+となっている。
- http://docs.screwdriver.cd/cluster-management/running-locally

この辺のREADMEあたりにもまとまってそう
- https://github.com/screwdriver-cd/screwdriver

### 設定ファイル(Yaml Configuration)
- http://docs.screwdriver.cd/user-guide/configuration/
- http://docs.screwdriver.cd/about/appendix/domain

デフォルトの設定ファイルは以下
- https://github.com/screwdriver-cd/screwdriver/blob/master/config/default.yaml

### 利用できる環境変数
- https://github.com/screwdriver-cd/screwdriver/blob/master/config/custom-environment-variables.yaml

### validatorページ
この辺?
- https://github.com/screwdriver-cd/screwdriver/blob/5911bff2bc2d7b584634e402ab306b0f5a8f9843/test/plugins/validator.test.js#L55

### Screwdriver API
- http://docs.screwdriver.cd/user-guide/api

### ドキュメント
- https://github.com/screwdriver-cd/guide
- http://docs.screwdriver.cd/user-guide/quickstart

### Contributing
- http://docs.screwdriver.cd/about/contributing

# 参考URL
- http://screwdriver.cd/
- https://github.com/screwdriver-cd
- https://github.com/screwdriver-cd-test
