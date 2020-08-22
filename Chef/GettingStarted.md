# 概要
chefを始める際のメモです。
セットアップ手順やスタンドアローンの実行などchefの基本事項についてのメモです。

# MAC環境でのセットアップ 〜 利用してみる
以下から環境からChefDK(Development Kit)をダウンロードします。
- https://downloads.chef.io/products/chefdk


knife-zeroをインストールします。
途中でライセンス同意画面が表示されるので、yesを入力します。

```
$ sudo chef gem install knife-zero
+---------------------------------------------+
            Chef License Acceptance

Before you can continue, 3 product licenses
must be accepted. View the license at
https://www.chef.io/end-user-license-agreement/

Licenses that need accepting:
  * Chef Development Kit
  * Chef Infra Client
  * Chef InSpec

Do you accept the 3 product licenses (yes/no)?

> yes

Persisting 3 product licenses...
✔ 3 product licenses persisted.

+---------------------------------------------+
Fetching knife-zero-2.3.1.gem
WARNING:  You don't have /Users/tsuyoshi/.chefdk/gem/ruby/2.6.0/bin in your PATH,
	  gem executables will not run.
Successfully installed knife-zero-2.3.1
1 gem installed
```


chefのバージョンを確認しておく

```
$ chef -v
ChefDK version: 4.10.0
Chef Infra Client version: 15.13.8
Chef InSpec version: 4.22.1
Test Kitchen version: 2.5.4
Foodcritic version: 16.3.0
Cookstyle version: 5.23.0
```

パスを通します。
```
$ echo 'export PATH="/opt/chefdk/embedded/bin:$PATH"' >> ~/.bash_profile && source ~/.bash_profile
```


# chef-zeroをスタンドアローン(localhost)で実行させてみる

こちらの手順に従う
- https://qiita.com/ShibuyaBizman/items/2addccbf15e586220bda

## 1. レポジトリの作成
新しいレポジトリを作成します。
```
$ chef generate repo chef-repo
Generating Chef Infra repo chef-repo
- Ensuring correct Chef Infra repo file content

Your new Chef Infra repo is ready! Type `cd chef-repo` to enter it.
```

作成直後は次のようになっています。
```
$ tree chef-repo/
chef-repo/
├── LICENSE
├── README.md
├── chefignore
├── cookbooks
│   ├── README.md
│   └── example
│       ├── README.md
│       ├── attributes
│       │   └── default.rb
│       ├── metadata.rb
│       └── recipes
│           └── default.rb
├── data_bags
│   ├── README.md
│   └── example
│       └── example_item.json
└── policyfiles
    └── README.md

7 directories, 11 files

```


## 2.レポジトリの初期設定
レポジトリ直下に.chefディレクトリを作成してknife.rbを作成します。
```
$ cd chef-repo
$ mkdir .chef
$ vi .chef/knife.rb
```

.knife.rbにはローカルモードの設定を行います。
ローカルモードの使用は実行時のオプションで指定することもできますが、指定を忘れてしまって非ローカルモードとごっちゃになると想定通りの動きをしません。そこでハマってしまうのを防ぐためにもこのknife.rbの設定は必ずしておくべきです。
```
$ cat .chef/knife.rb
local_mode true

chef_repo_dir = File.absolute_path( File.dirname(__FILE__) + "/.." )
cookbook_path ["#{chef_repo_dir}/cookbooks"]
node_path     "#{chef_repo_dir}/nodes"
role_path     "#{chef_repo_dir}/roles"
ssl_verify_mode  :verify_peer
```

## 3. テスト実行
```
$ chef generate cookbook cookbooks/test-cook
Hyphens are discouraged in cookbook names as they may cause problems with custom resources. See https://docs.chef.io/ctl_chef.html#chef-generate-cookbook for more information.
Generating cookbook test-cook
- Ensuring correct cookbook content

Your cookbook is ready. Type `cd cookbooks/test-cook` to enter it.

There are several commands you can run to get started locally developing and testing your cookbook.
Type `delivery local --help` to see a full list of local testing commands.

Why not start by writing an InSpec test? Tests for the default recipe are stored at:

test/integration/default/default_test.rb

If you'd prefer to dive right in, the default recipe can be found at:

recipes/default.rb
```

続いて、recipeを編集する。/tmp/sampleを作成するように編集した。
```
$ vim cookbooks/test-cook/recipes/default.rb
$ cat cookbooks/test-cook/recipes/default.rb
#
# Cookbook:: test-cook
# Recipe:: default
#
# Copyright:: 2020, The Authors, All Rights Reserved.

file "/tmp/sample" do
  mode "0600"
  action :create
end
```

roleの作成します。以下を実行することで、linux-serverというroleの雛形をvimで表示します。
```
$ EDITOR=vim knife role create linux-server
```

実行するとvim上で次の情報が表示されますが、そのまま保存します。
```
{
  "name": "linux-server",
  "description": "", 
  "json_class": "Chef::Role",
  "default_attributes": {

  },  
  "override_attributes": {

  },  
  "chef_type": "role",
  "run_list": [

  ],  
  "env_run_lists": {

  }
}
```

続いて、run_listの追加を行います。
```
$ knife role run_list add linux-server test-cook
chef_type:           role
default_attributes:
description:         
env_run_lists:
json_class:          Chef::Role
name:                linux-server
override_attributes:
run_list:            recipe[test-cook]
```

以下のファイルが生成されます。
```
$ cat roles/linux-server.json 
{
  "name": "linux-server",
  "run_list": [
    "recipe[test-cook]"
  ]
}
```

続いて、environmentの作成を行います。
```
$ EDITOR=vim knife environment create dev
```

以下の画面が表示されますが、そのまま保存します。
```
{
  "name": "dev",
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

enviromentが生成されたことを確認します。
```
$ cat environments/dev.json
{
  "name": "dev"
}
```

続いて、nodeを作成します。
```
$ EDITOR=vim knife node create localhost
```

以下の画面が表示されますが、そのまま保存します。
```
{
  "name": "localhost",
  "chef_environment": "_default",
  "json_class": "Chef::Node",
  "automatic": {

  },  
  "normal": {

  },  
  "chef_type": "node",
  "default": {

  },  
  "override": {

  },  
  "run_list": [

  ]
}
```

以下のnodes用ファイルが生成されたことを確認します。
```
$ cat nodes/localhost.json
{
  "name": "localhost"
}
```

run_listを設定します。
```
$ knife node run_list set localhost role[linux-server]
localhost:
  run_list: role[linux-server]
```

先ほどのnodesファイルが更新されたことを確認できます。
```
$ cat nodes/localhost.json
{
  "name": "localhost",
  "normal": {
    "tags": [

    ]
  },
  "run_list": [
    "role[linux-server]"
  ]
}
```

では、実行してみます。
```
$ sudo chef-client -z 
Starting Chef Infra Client, version 15.13.8
resolving cookbooks for run list: ["test-cook"]
Synchronizing Cookbooks:
  - test-cook (0.1.0)
Installing Cookbook Gems:
Compiling Cookbooks...
Converging 1 resources
Recipe: test-cook::default
  * file[/tmp/sample] action create
    - create new file /tmp/sample
    - change mode from '' to '0600'

Running handlers:
Running handlers complete
Chef Infra Client finished, 1/1 resources updated in 05 seconds

```

レシピが実行されファイルが作成されたことを確認する
```
$ ls -alt /tmp/sample 
-rw-------  1 root  wheel  0  8 19 05:38 /tmp/sample
```

### Cookbookをlocalmodeで実行させる
oオプション(override-runlist)
```
$ chef-client -z -o "recipe[sample_cb::default]"
```

もしくは、以下のようにしてjson形式で指定することも可能です。
```
$ cat local.json
{
  "sample_cb": {
    "echo": "HelloWorld!!"
  },
  "run_list": [
    "recipe[sample_cb::default]"
  ]
}
chef-client -z -j local.json
```
