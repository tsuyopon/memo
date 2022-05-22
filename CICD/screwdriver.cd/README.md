# 概要
Screwdriver.cd周りのメモ

# 詳細

## 資料
- 全体像
  - https://docs.screwdriver.cd/ja/cluster-management/
- Getting Started with Screwdriver
  - https://docs.screwdriver.cd/ja/user-guide/quickstart.html
- SCM
  - https://docs.screwdriver.cd/ja/user-guide/scm.html
- テンプレート(Templates)
  - https://docs.screwdriver.cd/ja/user-guide/templates.html
- コマンド(Command)
  - https://docs.screwdriver.cd/ja/user-guide/commands
- 環境変数
  -  https://docs.screwdriver.cd/ja/user-guide/environment-variables
- トークン
  - https://docs.screwdriver.cd/ja/user-guide/tokens.html
- metadata
  - https://docs.screwdriver.cd/ja/user-guide/metadata.html
- API
  - https://docs.screwdriver.cd/ja/user-guide/api.html
- YAML設定
  - https://docs.screwdriver.cd/ja/user-guide/configuration/
- sd-local
  - https://docs.screwdriver.cd/ja/user-guide/local.html
- FAQ
  - https://docs.screwdriver.cd/ja/user-guide/FAQ.html

## 各種コンポーネントのデバッグログを出力したい
以下の資料を元に手元のMAC環境を構築します。 途中でgithubのClientID, ClientSecretを発行して入力する箇所があります。
- SD-in-a-Boxを使ってローカルでScrewdriverを実行
  - https://docs.screwdriver.cd/ja/cluster-management/running-locally
- github
  - https://github.com/screwdriver-cd/in-a-box#screwdriver-in-a-box
- Running Screwdriver Locally using SD-in-a-Box
  - https://docs.screwdriver.cd/cluster-management/running-locally

これでdocker-composeを使って簡単に起動できるようになります。
```
$ docker-compose -p screwdriver up -d
```

バックグラウンドにせずにアクセスがあったUIやAPIの情報を出力したければ-dオプションを付与しないで起動するのが良いでしょう。
```
$ docker-compose -p screwdriver up
```

例えば以下のようにUIにアクセスするだけで、アクセスされたリソースの情報が全て確認することができます。
```
ui_1     | 172.20.0.1 - - [30/Mar/2022:23:47:53 +0000] "GET /dashboards/1 HTTP/1.1" 200 5202 "-" "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.60 Safari/537.36" "-"
ui_1     | 172.20.0.1 - - [30/Mar/2022:23:47:53 +0000] "GET /assets/supplementary_config.js HTTP/1.1" 200 281 "http://192.168.3.7:9000/dashboards/1" "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.60 Safari/537.36" "-"
ui_1     | 172.20.0.1 - - [30/Mar/2022:23:47:53 +0000] "GET /assets/vendor-f82866a96fd8478ec578d361fafd79c9.css HTTP/1.1" 200 57266 "http://192.168.3.7:9000/dashboards/1" "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.60 Safari/537.36" "-"
ui_1     | 172.20.0.1 - - [30/Mar/2022:23:47:53 +0000] "GET /assets/screwdriver-ui-86a0de645924e76bc564dcef739a4871.css HTTP/1.1" 200 213689 "http://192.168.3.7:9000/dashboards/1" "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.60 Safari/537.36" "-"
api_1    | 220330/234753.595, (1648684073595:22fa5673c07b:26:l1e771so:10082) [response,api,auth,context] http://192.168.3.7:9001: get /v4/auth/contexts {} 200 (7ms)
api_1    | 220330/234753.629, (1648684073629:22fa5673c07b:26:l1e771so:10084) [response,api,collections] http://192.168.3.7:9001: get /v4/collections {} 200 (52ms)
api_1    | 220330/234753.623, (1648684073623:22fa5673c07b:26:l1e771so:10083) [response,api,collections] http://192.168.3.7:9001: get /v4/collections/1 {} 200 (61ms)
api_1    | 220330/234753.707, (1648684073707:22fa5673c07b:26:l1e771so:10085) [response,api,banners] http://192.168.3.7:9001: get /v4/banners {} 200 (10ms)
api_1    | 220330/234753.817, (1648684073817:22fa5673c07b:26:l1e771so:10086) [response,api,pipelines,metrics] http://192.168.3.7:9001: get /v4/pipelines/1/metrics {"count":20,"page":1,"sort":"descending"} 200 (59ms)
api_1    | 220330/234753.819, (1648684073819:22fa5673c07b:26:l1e771so:10087) [response,api,pipelines,metrics] http://192.168.3.7:9001: get /v4/pipelines/2/metrics {"count":20,"page":1,"sort":"descending"} 200 (60ms)
```

## テーブル

データベースはmainしか存在しません。
```
sqlite> .databases
main: /Users/tsuyoshi/athenz/docker/./data/storage.db
```

数多くのテーブルが存在します。
以下ではINDEXも存在するのでテーブルの項目は「CREATE TABLE」のみを参照すれば良いでしょう。
```
sqlite> .schema
CREATE TABLE sqlite_sequence(name,seq);
CREATE TABLE `banners` (`id` INTEGER PRIMARY KEY, `message` VARCHAR(512), `isActive` TINYINT(1), `createTime` VARCHAR(32), `createdBy` VARCHAR(128), `type` VARCHAR(32));
CREATE INDEX `banners_is_active` ON `banners` (`isActive`);
CREATE TABLE `builds` (`id` INTEGER PRIMARY KEY, `environment` TEXT, `eventId` DOUBLE PRECISION, `jobId` DOUBLE PRECISION, `parentBuildId` TEXT, `parentBuilds` TEXT, `number` DOUBLE PRECISION, `container` TEXT, `cause` TEXT, `sha` TEXT, `subscribedConfigSha` TEXT, `commit` TEXT, `createTime` VARCHAR(32), `startTime` TEXT, `endTime` TEXT, `parameters` TEXT, `meta` TEXT, `status` TEXT, `statusMessage` TEXT, `stats` TEXT, `templateId` DOUBLE PRECISION, `buildClusterName` VARCHAR(50));
CREATE INDEX `builds_event_id_create_time` ON `builds` (`eventId`, `createTime`);
CREATE INDEX `builds_job_id` ON `builds` (`jobId`);
CREATE INDEX `builds_parent_build_id` ON `builds` (`parentBuildId`);
CREATE INDEX `builds_template_id` ON `builds` (`templateId`);
CREATE TABLE `buildClusters` (`id` INTEGER PRIMARY KEY, `name` VARCHAR(50), `description` VARCHAR(100), `scmContext` VARCHAR(128), `scmOrganizations` TEXT, `isActive` TINYINT(1), `managedByScrewdriver` TINYINT(1), `maintainer` VARCHAR(64), `weightage` DOUBLE PRECISION);
CREATE INDEX `build_clusters_name` ON `buildClusters` (`name`);
CREATE TABLE `steps` (`id` INTEGER PRIMARY KEY, `buildId` DOUBLE PRECISION, `name` VARCHAR(64), `command` TEXT, `code` DOUBLE PRECISION, `startTime` TEXT, `endTime` TEXT, `lines` DOUBLE PRECISION);
CREATE INDEX `steps_build_id` ON `steps` (`buildId`);
CREATE INDEX `steps_name` ON `steps` (`name`);
CREATE TABLE `events` (`id` INTEGER PRIMARY KEY, `parentEventId` DOUBLE PRECISION, `groupEventId` DOUBLE PRECISION, `causeMessage` VARCHAR(512), `commit` TEXT, `createTime` VARCHAR(32), `creator` TEXT, `meta` TEXT, `pipelineId` DOUBLE PRECISION, `sha` VARCHAR(40), `configPipelineSha` VARCHAR(40), `startFrom` TEXT, `type` VARCHAR(10), `workflowGraph` TEXT, `pr` TEXT, `prNum` DOUBLE PRECISION, `baseBranch` TEXT);
CREATE INDEX `events_create_time_pipeline_id` ON `events` (`createTime`, `pipelineId`);
CREATE INDEX `events_pipeline_id` ON `events` (`pipelineId`);
CREATE INDEX `events_type` ON `events` (`type`);
CREATE INDEX `events_group_event_id` ON `events` (`groupEventId`);
CREATE INDEX `events_parent_event_id` ON `events` (`parentEventId`);
CREATE TABLE `jobs` (`id` INTEGER PRIMARY KEY, `name` VARCHAR(110), `prParentJobId` DOUBLE PRECISION, `permutations` TEXT, `description` VARCHAR(100), `pipelineId` DOUBLE PRECISION, `state` VARCHAR(10), `stateChanger` VARCHAR(128), `stateChangeTime` TEXT, `stateChangeMessage` VARCHAR(512), `archived` TINYINT(1), `templateId` DOUBLE PRECISION);
CREATE INDEX `jobs_pipeline_id_state` ON `jobs` (`pipelineId`, `state`);
CREATE INDEX `jobs_state` ON `jobs` (`state`);
CREATE INDEX `jobs_template_id` ON `jobs` (`templateId`);
CREATE TABLE `pipelines` (`id` INTEGER PRIMARY KEY, `name` TEXT, `scmUri` VARCHAR(128), `scmContext` VARCHAR(128), `scmRepo` TEXT, `createTime` TEXT, `admins` TEXT, `workflowGraph` TEXT, `annotations` TEXT, `lastEventId` DOUBLE PRECISION, `configPipelineId` DOUBLE PRECISION, `childPipelines` TEXT, `prChain` TINYINT(1), `parameters` TEXT, `settings` TEXT, `subscribedScmUrlsWithActions` TEXT);
CREATE INDEX `pipelines_scm_uri` ON `pipelines` (`scmUri`);
CREATE INDEX `pipelines_subscribed_scm_urls_with_actions` ON `pipelines` (`subscribedScmUrlsWithActions`);
CREATE TABLE `users` (`id` INTEGER PRIMARY KEY, `username` VARCHAR(128), `token` TEXT, `scmContext` VARCHAR(128), `settings` TEXT);
CREATE INDEX `users_username` ON `users` (`username`);
CREATE INDEX `users_scm_context` ON `users` (`scmContext`);
CREATE TABLE `secrets` (`id` INTEGER PRIMARY KEY, `pipelineId` DOUBLE PRECISION, `name` VARCHAR(64), `value` TEXT, `allowInPR` TINYINT(1));
CREATE INDEX `secrets_pipeline_id` ON `secrets` (`pipelineId`);
CREATE TABLE `templates` (`id` INTEGER PRIMARY KEY, `labels` TEXT, `config` TEXT, `name` VARCHAR(64), `version` VARCHAR(16), `description` VARCHAR(256), `maintainer` VARCHAR(64), `pipelineId` DOUBLE PRECISION, `namespace` VARCHAR(64), `images` TEXT, `createTime` VARCHAR(32), `trusted` TINYINT(1), `latest` TINYINT(1));
CREATE INDEX `templates_namespace` ON `templates` (`namespace`);
CREATE INDEX `templates_name` ON `templates` (`name`);
CREATE TABLE `templateTags` (`id` INTEGER PRIMARY KEY, `createTime` VARCHAR(32), `namespace` VARCHAR(64), `name` VARCHAR(64), `tag` VARCHAR(30), `version` VARCHAR(16));
CREATE INDEX `template_tags_namespace` ON `templateTags` (`namespace`);
CREATE INDEX `template_tags_name` ON `templateTags` (`name`);
CREATE INDEX `template_tags_tag` ON `templateTags` (`tag`);
CREATE TABLE `tokens` (`id` INTEGER PRIMARY KEY, `hash` VARCHAR(86), `userId` DOUBLE PRECISION, `pipelineId` DOUBLE PRECISION, `name` VARCHAR(128), `description` VARCHAR(256), `lastUsed` TEXT);
CREATE INDEX `tokens_hash` ON `tokens` (`hash`);
CREATE INDEX `tokens_user_id` ON `tokens` (`userId`);
CREATE INDEX `tokens_pipeline_id` ON `tokens` (`pipelineId`);
CREATE TABLE `triggers` (`id` INTEGER PRIMARY KEY, `src` VARCHAR(64), `dest` VARCHAR(64));
CREATE INDEX `triggers_dest` ON `triggers` (`dest`);
CREATE INDEX `triggers_src` ON `triggers` (`src`);
CREATE TABLE `collections` (`id` INTEGER PRIMARY KEY, `userId` DOUBLE PRECISION, `name` VARCHAR(128), `description` VARCHAR(256), `pipelineIds` TEXT, `type` VARCHAR(32));
CREATE INDEX `collections_user_id` ON `collections` (`userId`);
CREATE TABLE `commands` (`id` INTEGER PRIMARY KEY, `namespace` VARCHAR(64), `version` VARCHAR(16), `description` VARCHAR(256), `maintainer` VARCHAR(64), `format` VARCHAR(16), `habitat` TEXT, `docker` TEXT, `binary` TEXT, `name` VARCHAR(64), `pipelineId` DOUBLE PRECISION, `createTime` VARCHAR(32), `usage` VARCHAR(4096), `trusted` TINYINT(1), `latest` TINYINT(1));
CREATE INDEX `commands_namespace` ON `commands` (`namespace`);
CREATE INDEX `commands_name` ON `commands` (`name`);
CREATE TABLE `commandTags` (`id` INTEGER PRIMARY KEY, `createTime` VARCHAR(32), `namespace` VARCHAR(64), `name` VARCHAR(64), `tag` VARCHAR(30), `version` VARCHAR(16));
CREATE INDEX `command_tags_namespace` ON `commandTags` (`namespace`);
CREATE INDEX `command_tags_name` ON `commandTags` (`name`);
CREATE INDEX `command_tags_tag` ON `commandTags` (`tag`);
```

# 公式資料
- github
  - https://github.com/screwdriver-cd
- github(サンプル集など)
  - https://github.com/screwdriver-cd-test
- ユーザドキュメント
  - https://docs.screwdriver.cd/ja/user-guide/quickstart
- APIドキュメント(v4)
  - https://api.screwdriver.cd/v4/documentation
- metaコマンド
  - https://github.com/screwdriver-cd/meta-cli
