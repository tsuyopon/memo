# 概要
BerksfileとはCookbookとその依存関係の管理を行うツールです。
- https://docs.chef.io/workstation/berkshelf/

# 詳細

### Berksfileを使ってみる

Berksfileを手動で作成します。
```
$ vim Berksfile
$ cat Berksfile
source "https://supermarket.getchef.com"

# community cookbook
cookbook 'yum'
```

berksコマンドを実行して取得します。これはberks installを実行するのと同じです。
```
$ berks
Resolving cookbook dependencies...
Fetching cookbook index from https://supermarket.getchef.com...
Installing yum (5.1.0) from https://supermarket.getchef.com ([opscode] https://supermarket.chef.io:443/api/v1)
```

Berksfile.lockファイルが作成されています。
Berksfile.lockにはインストールされたCookbookのバージョンや依存関係の情報が含まれています。
```
$ ls Berksfile.lock
$ cat Berksfile.lock 
DEPENDENCIES
  yum

GRAPH
  yum (5.1.0)
```

- 参考資料
  - http://akuwano.hatenablog.jp/entry/20140806/1407291260


### 新しいバージョンのCookbookがあるかどうかを確認する
新しいcookbookの存在を確認するには次のコマンドを実行します。
```
$ berks outdated
The following cookbooks have newer versions:
  * ark (0.8.2 => 0.9.0) [https://supermarket.getchef.com]
  * consul (0.2.3 => 0.3.0) [https://supermarket.getchef.com]
  * erlang (1.5.4 => 1.5.6) [https://supermarket.getchef.com]
  * golang (1.3.0 => 1.4.0) [https://supermarket.getchef.com]
  * sensu (1.0.0 => 2.0.0) [https://supermarket.getchef.com]
  * windows (1.31.0 => 1.34.0) [https://supermarket.getchef.com]
  * yum (3.2.0 => 3.2.2) [https://supermarket.getchef.com]
  * yum-epel (0.3.6 => 0.4.0) [https://supermarket.getchef.com]
```

### berks outdatedで表示されたような変更を更新したい

berks updateコマンドによって全Cookbookの強制アップデートになります。
引数を指定すると単体のcookbookを指定することも可能です。
```
$ berks update
Resolving cookbook dependencies...
Fetching 'webserver' from http://git.example.com/ca-cookbooks/webserver.git (at master)
Fetching 'nginx-test' from http://git.example.com/ca-cookbooks/nginx-test.git (at master)
Fetching 'apache-test' from http://git.example.com/ca-cookbooks/apache-test.git (at master)
Fetching cookbook index from https://supermarket.getchef.com...
Using 'webserver' from http://git.example.com/ca-cookbooks/webserver.git (at master)
Using 'nginx-test' from http://git.example.com/ca-cookbooks/nginx-test.git (at master)
Using 'apache-test' from http://git.example.com/ca-cookbooks/apache-test.git (at master)
Using apt (2.4.0)
Using ark (0.8.2)
...
```

たとえば、webserver単体だけ実行する場合には次のコマンドを実行します。
```
$ berks update webserver
```

実行するとBerksfile.lockが更新されます。

### cookbookをtar.gz形式で出力したい

```
$ ls *.tar.gz
ls: *.tar.gz: No such file or directory
$ berks package
Cookbook(s) packaged to /Users/tsuyoshi/git/test/chef-repo/cookbooks-1598089458.tar.gz
$ ls *.tar.gz
cookbooks-1598089458.tar.gz
```

### 現在インストールされているcookbookを表示する
```
$ berks list
Cookbooks installed by your Berksfile:
  * yum (5.1.0)
```

### 依存先も含めたcookbookをダウンロードする
berks venderコマンドはBerkshelfファイルの内容に従い、オプションで指定したディレクトリにcookbookをインストールします。


以下の例ではcookbooksディレクトリ配下にインストールします。
```
$ berks vendor cookbooks
```

以下の例ではディレクトリが指定されていません。
```
$ berks vendor
Resolving cookbook dependencies...
Using mysql (8.7.3)
Using yum (5.1.0)
Vendoring mysql (8.7.3) to /Users/tsuyoshi/git/test/chef-repo/berks-cookbooks/mysql
Vendoring yum (5.1.0) to /Users/tsuyoshi/git/test/chef-repo/berks-cookbooks/yum
```

上記のように、保存先ディレクトリを指定しないとberks-cookbooksディレクトリに保存されます。
```
$ ls berks-cookbooks/
mysql yum
```

### コミュニティクックブックを検索する

以下の例ではredisについて探索しています。
```
$ berks search redis
L7-redis (1.0.8)
docker-redis (0.3.0)
ds_redis (2.0.0)
formatron_redis (0.1.1)
newrelic_redis_plugin (1.0.0)
php-redis (0.1.1)
redis (3.0.4)
redis-cookbook (0.2.1)
redis-multi (1.0.1)
redis-omnibus (3.0.0)
redis-package (1.0.0)
redis-simple (0.1.1)
redis-test (0.2.0)
redis2 (0.5.1)
redis_2_cookbook (0.3.3)
redisio (4.1.1)
```

### Cookbookのメタ情報を表示する
berks infoの引数にcookbook名を指定することでそのcookbookのメタ情報を表示することができます。
```
$ berks info yum
        Name: yum
     Version: 5.1.0
 Description: Configures various yum components on Red Hat-like systems
      Author: Chef Software, Inc.
       Email: cookbooks@chef.io
     License: Apache-2.0
   Platforms: amazon (>= 0.0.0)
              centos (>= 0.0.0)
              fedora (>= 0.0.0)
              oracle (>= 0.0.0)
              redhat (>= 0.0.0)
              scientific (>= 0.0.0)
              zlinux (>= 0.0.0)
```

### 現在使っているCookbookの実際のサーバ上での位置を表示する
```
$ berks show yum
/Users/tsuyoshi/.berkshelf/cookbooks/yum-5.1.0
```

### CookbookをChef Serverへアップデートする
Berkshelfで使ったCookbookをChef Serverへとアップロードしたい場合には、berks uploadコマンドを利用します。
Cookbookの管理にBerkshelfを使って、実行はchef client経由でしたい。バージョン管理はChef-server側で行いたい、等の場合はberks uploadするようにします。
```
$ berks upload
```

# 公式URL
- ドキュメント
  - https://docs.chef.io/workstation/berkshelf/
