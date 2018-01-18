# 概要
Chefにはサーバ管理規模に応じて利用形態が３つに分類されるようです。以下でChef Workstaionと呼ぶのは単なるクライアントマシンです。
Chef SoloやChef Zeroは小中規模、Chef Serverは大規模な運用で用いられる構成となっています。

- Chef Solo(廃止予定)
  - 1. Chef Workstation(管理クライアント)からknife soloによって各Nodeにcookbookを転送して、
  - 2. Nodeの中ではchef soloがcookbookのサーバ構成情報を元にして自身のセットアップを行う
- Chef Zero
  - 1. Chef Workstation(管理クライアント)がknife zeroを稼働して、そこからchef zeroを起動する。
  - 2. Chef zeroが起動するとNodeからChef Workstation内にあるCookbookが参照できる状態となる
  - 3. Chef Workstationでknife zeroを実行するとNodeへとリモート通信してTCPフォワーディングを設定してNodeからChef Workstationへ通信できる状態にする
  - 4. Nodeからchef clientが実行され、NodeからChef Workstation内のCookbookなどのサーバ構成情報を取得する
  - 5. NodeがChef Workstationから取得したcookbookなどのサーバ構成情報を元にして自身のセットアップを行う
- Chef Server
  - 1. Chef Workstationにてknifeを使ってChef ServerへCookbookなどのサーバ構成情報を転送する。
  - 2. chef clientがNodeからChef Server内部のcookbookなどのサーバ構成情報を取得する。
  - 3. Nodeはchef clientにて取得したcookbookなどのサーバ構成情報を元に自身のセットアップを行う。

- SeeAlso
  - https://docs.chef.io/chef_quick_overview.html
  - https://www.conoha.jp/guide/chef.php

簡単にひとめぐりするには最初は以下のドキュメントがおすすめです
- https://qiita.com/deko2369/items/7a8c239cc5415eedbcc3

### knife bootstrapについて
knifeのbootstrapは実行すると次の処理を行うらしい
- 1. Chef Clientのインストール
- 2. 鍵の作成(Chef Server側の"/etc/chef-server/chef-validator.pem"の内容をChef Client側の"/etc/chef/validation.pem"にコピーする)
- 3. Chef Clientの定義ファイルの作成(/etc/chef/client.rb)


# 設定値
nodes, roles, environmentsなどのディレクトリが存在するようだ

### nodes設定
ホストごとの設定でnodes/<hostname>.jsonという名称で準備されるもののようです。以下はサンプル
```
{
    "name": "sample",
    "chef_type": "node",
    "json_class": "Chef::Node",
    "chef_environment" : "sample_env",
    "run_list": [
        "recipe[hoge]",
        "role[foo]"
    ],
    "default": {
    },
    "normal": {
    },
    "override": {
    },
    "automatic": {
    }
}
```

Chef::Nodeについては以下を参考に
- https://github.com/chef/chef/blob/master/lib/chef/node.rb

- SeeAlso
  - https://docs.chef.io/nodes.html

### roles設定
以下はサンプル。 roles/<ロール名>.jsonなどとなる。ロール名はdevelopment, prod, stagingなどが一般的のようです。
```
{
  "name": "web",
  "chef_type": "role",
  "json_class": "Chef::Role",
  "default_attributes": {
    "apache": {
      "listen_ports": [
        "80",
        "443",
      ]
  },
  "override_attributes": {
    "apache": {
      "max_children": "50"
    }
  },
  "run_list": [
    "recipe[git]",
    "recipe[apache2]"
  ]
}
```

- json_classで指定されるChef::Roleは以下が該当する
  - https://github.com/chef/chef/blob/master/lib/chef/role.rb
- SeeAlso
  - https://docs.chef.io/roles.html

### environments設定
以下はサンプル。environments/<envname>.jsonなどのファイル名となることが一般的です。
```
{
    "name": "sample",
    "description": "サンプル環境",
    "chef_type": "environment",
    "json_class": "Chef::Environment",
    "default_attributes": {
    },
    "override_attributes": {
    },
    "cookbook_versions" : {
        "rabbitmq", "= 3.2.2"
    }
}
```

上記の各種設定ではChef::Environmentをjson_classで指定しているが以下が該当する。
- https://github.com/chef/chef/blob/master/lib/chef/environment.rb

- SeeAlso
  - https://docs.chef.io/environments.html


### recipe設定
以下は代表的な一部のみを添付することにする。以下のリンクにある公式ドキュメントの左側のタブを見ると沢山あるのでそちらを参照すること

- package: yumやapt等のパッケージインストールを行うことのできるリソースです
  - https://docs.chef.io/resource_package.html
```
package "ant" do
 action :install
end
```

- template: あらかじめ設定ファイルのテンプレートを用意しておき、template リソースを使って差し替えを行います。
  - https://docs.chef.io/resource_template.html
```
template "/etc/my.cnf" do
    source "my.cnf.erb"
end
```

- execute: シェルの実行で利用するリソースです
  - https://docs.chef.io/resource_execute.html
```
execute "init-infoscoop" do
 command "./import.sh"
end
```

- file: ファイル操作を行うことが可能です
  - https://docs.chef.io/resource_file.html
```
file "/usr/share/tomcat/webapps" do
    content IO.read( "/tmp/infoscoop.war" )
end
```

- SeeAlso
  - https://docs.chef.io/recipes.html

# コマンドなど
### 初期設定について
次のディレクトリを作成します
```
~/chef-repo/.chef/
```

上記ディレクトリに
- knife.rb
- account.pem (名称任意)

account.pemはChefServerのWebUI上で取得した秘密鍵を登録します。


### cookbookテンプレートの作成
以下はsample_bookというcookbookの雛形テンプレートを作成します。
```
$ knife cookbook create sample_book
$ tree cookbooks/sample_book
cookbooks/sample_book
├── CHANGELOG.md
├── README.md
├── attributes
├── definitions
├── files
│   └── default
├── libraries
├── metadata.rb
├── providers
├── recipes
│   └── default.rb
├── resources
└── templates
    └── default
```

### Cookbookを公式レポジトリからダウンロード・展開する
事前に~/chef-repo/cookbook以下をGit管理下に置く必要があります。Git管理下にない場合、
```
$ knife cookbook site install chef-client
Installing chef-client to /home/chef-admin/chef-repo/cookbooks
Checking out the master branch.
(以下略)
```

### Chef ServerへのCookbookのアップロードの登録と確認を行う
以下のサンプルをcookbookへアップロードして確認までを行います。
```
$ git clone https://github.com/opscode-cookbooks/getting-started
```

続いてアップロードします。
```
$ knife cookbook upload getting-started -o .
Uploading getting-started [0.4.0]
Uploaded 1 cookbook.
$ knife cookbook show getting-started
getting-started 0.4.0
```

登録されたcookbookのリストを確認します。
```
$ knife cookbook list
getting-started   0.4.0
```

### nodeの情報を取得する
```
$ knife node show chef-client
Node Name:   chef-client
Environment: _default
FQDN:        chef-client
IP:          10.0.2.15
Run List:    recipe[getting-started]
Roles:
Recipes:     getting-started, getting-started::default
Platform:    centos 6.6
Tags:
```

### ユーザーリストを表示する
```
$ knife user list
admin
yamato
```

### knife bootstrapを実行する
knife bootstrapの書式は次の通り
```
$ knife bootstrap (Chef ClientホストのFQDN) \
-t TEMPLATE              (TEMPLATEにOSタイプに合わせたbootstrap script名を記載）\
-r, --run-list RUN_LIST  (RUN_LISTにカンマ区切りのRecipeやRoleのリストを記載) \
-i IDENTITY_FILE         (SSH秘密鍵ファイルを指定) \
-x USERNAME              (SSH接続するユーザー名を指定) \
--sudo                   (sudoコマンドを使うか指定)
```

以下は例として「chef-client::delete_validation」というレシピを実行していて、Chef ClientとChef Serverが接続した後にClient側に保存されたOrganization認証秘密鍵を削除します。
```
$ knife bootstrap chef-client.local -t centos -i ~/.ssh/id_rsa -x chef-client --sudo -r 'recipe[chef-client::delete_validation]'
```

### SSL通信できるかチェックする
```
$ knife ssl check
```

# 参考URL
- 本家
  - https://docs.chef.io/
- chefのgithub(knifeなどのコマンドが有ります)
  - https://github.com/chef/chef/blob/master/lib/chef/knife/bootstrap.rb
