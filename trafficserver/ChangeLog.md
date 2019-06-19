# 概要
trafficserverのバージョン間の変更点を確認する場合の方法

現在ダウンロード可能なバージョンについては以下のリンクで確認することができます。
- https://trafficserver.apache.org/downloads

ChangeLog以外に関する資料の説明はDocumentLink.md にもありますのでそちらも参考にしてください。

# ドキュメント

### What's New?
ポータルは以下のリンクから遷移できます。
- https://cwiki.apache.org/confluence/pages/viewpage.action?pageId=34020337

上記ページからは各バージョン毎に次のような情報を確認することができます。
- 新機能
- 新プラグイン
- 新設された設定情報
- 現行のプラグインへの変更点
- その他開発視点情報(ビルド環境、ビルドオプション変更など)

### Updating Traffic Server
ポータルは以下のリンクから遷移できます。
- https://cwiki.apache.org/confluence/display/TS/Upgrading+Traffic+Server

上記ページからは各バージョン毎に次のような情報を確認することができます。
- Deprecatedされた機能
- API変更点
- 設定情報変更点
- その他

### ChangeLog
githubで各バージョンタグの直下にChangeLogが配置されているので確認すると良い。
7系と8系については以下にリンクを記載しているが、それ以前については記載していない。
- trafficserver-7.0.x
  - https://github.com/apache/trafficserver/blob/7.0.x/CHANGES
- trafficserver-7.1.x
  - https://github.com/apache/trafficserver/blob/7.1.x/CHANGELOG-7.1.0
  - https://github.com/apache/trafficserver/blob/7.1.x/CHANGELOG-7.1.1
  - https://github.com/apache/trafficserver/blob/7.1.x/CHANGELOG-7.1.2
  - https://github.com/apache/trafficserver/blob/7.1.x/CHANGELOG-7.1.3
  - https://github.com/apache/trafficserver/blob/7.1.x/CHANGELOG-7.1.4
  - https://github.com/apache/trafficserver/blob/7.1.x/CHANGELOG-7.1.5
  - https://github.com/apache/trafficserver/blob/7.1.x/CHANGELOG-7.1.6
  - https://github.com/apache/trafficserver/blob/7.1.x/CHANGELOG-7.1.7
- trafficserver-8.0.x
  - https://github.com/apache/trafficserver/blob/8.0.x/CHANGELOG-8.0.0
  - https://github.com/apache/trafficserver/blob/8.0.x/CHANGELOG-8.0.1
  - https://github.com/apache/trafficserver/blob/8.0.x/CHANGELOG-8.0.2
  - https://github.com/apache/trafficserver/blob/8.0.x/CHANGELOG-8.0.3
  - https://github.com/apache/trafficserver/blob/8.0.x/CHANGELOG-8.0.4


### PRラベルからのバージョンごとの変更点
次のページからmilestonesやlabelsごとに遷移することができます。
- マイルストン(主にバージョンごと)
  - https://github.com/apache/trafficserver/milestones
- ラベル(QUIC, TLSなど)
  - https://github.com/apache/trafficserver/labels

