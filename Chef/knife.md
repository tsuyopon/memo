# 概要
knifeコマンドについての基本事項についてまとめます。
ヘルプを見るとわかりますが、knifeはサブコマンドの種類も非常に豊富です。このファイルでは基本的なことについてのみまとめます。


Chef11.xからローカルモードというのが加わりました。
knifeコマンドの各サブコマンドに「-z (--local-mode)」オプションを付与して実行することで、Node Objectのみならず、このchef-repoディレクトリ内の情報を操作できます。これはレポジトリ直下の.repo/knife.rbに「local_mode true」を設定することで回避できます。


knife-zeroについては以下の資料も役立ちます
- https://knife-zero.github.io/

---
# helpについて
knifeのヘルプオプションを参考にすることができます
```
$ knife --help
Usage: knife sub-command (options)
    -s, --server-url URL             Chef Infra Server URL.
        --chef-zero-host HOST        Host to start Chef Infra Zero on.
        --chef-zero-port PORT        Port (or port range) to start Chef Infra Zero on. Port ranges like 1000,1010 or 8889-9999 will try all given ports until one works.
    -k, --key KEY                    Chef Infra Server API client key.
        --[no-]color                 Use colored output, defaults to enabled.
    -c, --config CONFIG              The configuration file to use.
        --config-option OPTION=VALUE Override a single configuration option.
        --defaults                   Accept default values for all questions.
    -d, --disable-editing            Do not open EDITOR, just accept the data as is.
    -e, --editor EDITOR              Set the editor to use for interactive commands.
    -E, --environment ENVIRONMENT    Set the Chef Infra Client environment (except for in searches, where this will be flagrantly ignored).
        --[no-]fips                  Enable FIPS mode.
    -F, --format FORMAT              Which format to use for output. (valid options: 'summary', 'text', 'json', 'yaml', or 'pp')
        --[no-]listen                Whether a local mode (-z) server binds to a port.
    -z, --local-mode                 Point knife commands at local repository instead of Chef Infra Server.
    -u, --user USER                  Chef Infra Server API client username.
        --print-after                Show the data after a destructive operation.
        --profile PROFILE            The credentials profile to select.
    -V, --verbose                    More verbose output. Use twice for max verbosity.
    -v, --version                    Show Chef Infra Client version.
    -y, --yes                        Say yes to all prompts for confirmation.
    -h, --help                       Show this help message.

Available subcommands: (for details, knife SUB-COMMAND --help)

** CHEF ORGANIZATION MANAGEMENT COMMANDS **
knife opc org create ORG_SHORT_NAME ORG_FULL_NAME (options)
knife opc org delete ORG_NAME
knife opc org edit ORG
knife opc org list
knife opc org show ORGNAME
knife opc org user add ORG_NAME USER_NAME
knife opc org user remove ORG_NAME USER_NAME
knife opc user create USERNAME FIRST_NAME [MIDDLE_NAME] LAST_NAME EMAIL PASSWORD
knife opc user delete USERNAME [-d] [-R]
knife opc user edit USERNAME
knife opc user list
knife opc user password USERNAME [PASSWORD | --enable-external-auth]
knife opc user show USERNAME

** OPSCODE HOSTED CHEF ACCESS CONTROL COMMANDS **
knife acl add MEMBER_TYPE MEMBER_NAME OBJECT_TYPE OBJECT_NAME PERMS
knife acl bulk add MEMBER_TYPE MEMBER_NAME OBJECT_TYPE REGEX PERMS
knife acl bulk remove MEMBER_TYPE MEMBER_NAME OBJECT_TYPE REGEX PERMS
knife acl remove MEMBER_TYPE MEMBER_NAME OBJECT_TYPE OBJECT_NAME PERMS
knife acl show OBJECT_TYPE OBJECT_NAME
knife group add MEMBER_TYPE MEMBER_NAME GROUP_NAME
knife group create GROUP_NAME
knife group destroy GROUP_NAME
knife group list
knife group remove MEMBER_TYPE MEMBER_NAME GROUP_NAME
knife group show GROUP_NAME
knife user dissociate USERNAMES
knife user invite add USERNAMES
knife user invite list
knife user invite recind [USERNAMES] (options)

(非常に出力が多いので省略)

** ZERO COMMANDS **
knife zero apply QUERY (options)
knife zero bootstrap [SSH_USER@]FQDN (options)
knife zero chef_client QUERY (options) | It's same as converge
knife zero converge QUERY (options)
knife zero diagnose # show configuration from file
```

サブコマンドのヘルプも「knife SUB-COMMAND --hellp」で表示できます。
以下はSUB-COMMANDがnodeの場合の例です。
```
$ knife node --help
FATAL: Cannot find subcommand for: 'node --help'
Available node subcommands: (for details, knife SUB-COMMAND --help)

** NODE COMMANDS **
knife node bulk delete REGEX (options)
knife node create NODE (options)
knife node delete [NODE [NODE]] (options)
knife node edit NODE (options)
knife node environment set NODE ENVIRONMENT
knife node from file FILE (options)
knife node list (options)
knife node policy set NODE POLICY_GROUP POLICY_NAME (options)
knife node run_list add [NODE] [ENTRY [ENTRY]] (options)
knife node run_list remove [NODE] [ENTRY [ENTRY]] (options)
knife node run_list set NODE ENTRIES (options)
knife node show NODE (options)
knife node status [<node> <node> ...]
```

サブコマンドの概要については以下のドキュメントに表形式で記載されています。
- https://docs.chef.io/workstation/knife/

---
# nodeに関する操作

### node一覧を表示する
```
$ knife node list
localhost
localhost.local
```

### nodeの詳細を確認する
```
$ knife node show localhost.local
Node Name:   localhost.local
Environment: _default
FQDN:        
IP:          192.168.3.4
Run List:    role[linux-server]
Roles:       linux-server
Recipes:     test-cook, test-cook::default
Platform:    mac_os_x 10.14.5
Tags:        
```

### nodeを削除する
本当に削除しても良いか尋ねられますので、Yを実行します。
```
$ knife node delete localhost
Do you really want to delete localhost? (Y/N) y
Deleted node[localhost]
```

### editorを使ってnode情報を編集する
```
$ EDITOR=vim knife node edit localhost
```

### nodeにレシピを追加する
以下ではlocalhostにrecipe "fuga_recipe"を追加している
```
$ knife node run_list add localhost 'recipe['fuga_recipe']'
```

### nodeからレシピを削除する
以下ではlocalhostからrecipe "fuga_recipe"を削除する
```
$ knife node run_list remove localhost 'recipe['fuga_recipe']'
```


---
# environmentに関する操作

### environment情報一覧を表示する
```
$ knife environment list -V
INFO: Using configuration from /Users/tsuyoshi/git/test/hello-chef/.chef/knife.rb
_default
development
production
```

### environment情報を探索する
```
$ knife search environment 'name:dev*'
1 items found

chef_type:           environment
cookbook_versions:
default_attributes:
description:         
json_class:          Chef::Environment
name:                development
override_attributes:
```

### environment情報を確認する
```
$ knife environment show development
chef_type:           environment
cookbook_versions:
default_attributes:
description:         
json_class:          Chef::Environment
name:                development
override_attributes:
```

### environmentを作成する
```
$ EDITOR=vim knife environment create staging 
```

以下のような情報が表示されるので、デフォルトで問題無い場合にはそのまま表示すればOK。
```
{
  "name": "staging",
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

### environmentを編集する
先ほど作成したstagingを修正します。
```
$ EDITOR=vim knife environment edit staging
```

### environmentを削除する

```
$ knife environment list
_default
development
production
staging
```

ではstagingを削除します。
```
$ knife environment delete staging
Do you really want to delete staging? (Y/N) y 
Deleted staging
```

削除されたことを確認します。
```
$ knife environment list
_default
development
production
```

---
# roleに関する操作

### roleの情報を確認する
```
$ knife role show linux
chef_type:           role
default_attributes:
description:         
env_run_lists:
json_class:          Chef::Role
name:                linux
override_attributes:
run_list:            recipe[default]
```

### role一覧を表示する
```
$ knife role list
freebsd
linux
```

### roleを作成する
```
$ knife role create role_test
```

### roleを編集する
```
$ knife role edit role_test
```

### roleを削除する
```
$ knife role delete role_test
```

### roleに該当するnodeを全て表示する
```
$ knife search role:linux
1 items found

Node Name:   localhost.local
Environment: \_default
FQDN:        
IP:          
Run List:    role[linux]
Roles:       
Recipes:     
Platform:     
Tags:        
```

---
# cookbookに関する操作

### cookbookに指定したcookbookが存在することを確認する
```
$ knife cookbook show hello-chef
hello-chef   0.1.0
```

### cookbook一覧を表示する
```
$ knife cookbook list
hello-chef   0.1.0
ntp          3.7.0
```

### cookbookを作成する
以下ではtest-cookという名前のcookbookの作成を指示します。
```
$ knife cookbook create test-cook
```

oオプションを指定するとパスも指定できる。デフォルトはカレントディレクトリ配下に作成となる。
```
$ knife cookbook create sample -o ./site-cookbook/
```

### cookbookをuploadする
```
$ knife cookbook upload sample
```

### cookbookを全てuploadする
```
$ knife cookbook upload --all
Uploading hello-chef     [0.1.0]
Uploading ntp            [3.7.0]
Uploaded all cookbooks.

```

oオプションを指定してパスを指定することも可能です
```
$ knife cookbook upload -a -o ./cookbooks
```

### uploadしたcookbookを削除する
```
// cookbookのリストを確認する
$ knife cookbook list
hello-chef   0.1.0
ntp          3.7.0

// ntpを削除する
$ knife cookbook delete ntp
Do you really want to delete ntp version 3.7.0? (Y/N) y
Deleted cookbook[ntp version 3.7.0]

// 削除されたことを確認する
$ knife cookbook list
hello-chef   0.1.0
```

--- 
# tagに関する操作

### タグを追加する
```
$ knife tag create node1.co.jp testtag
```

### タグを削除する
```
$ knife tag delete node1.co.jp testtag
```

### nodeに紐づくタグを表示する
```
knife tag list NODE
```

--- 
# supermarketに関する操作

### ダウンロードしたいcookbookの情報を表示する
次のように存在するバージョンやバージョン毎のダウンロード回数等の情報を表示します。
```
$ knife supermarket show ntp
average_rating:  
category:        Other
created_at:      2009-10-25T23:52:56.000Z
deprecated:      false
description:     Installs and configures ntp as a client or server
external_url:    https://github.com/chef-cookbooks/ntp
issues_url:      https://github.com/chef-cookbooks/ntp/issues
latest_version:  https://supermarket.chef.io/api/v1/cookbooks/ntp/versions/3.7.0
maintainer:      chef
metrics:
  collaborators: 1
  downloads:
    total:    33551071
    versions:
      0.7.0:  1253281
      0.8.1:  1247065
      0.8.2:  1247196
      1.0.0:  1253860
(snip)
      3.5.6:  414571
      3.6.0:  258411
      3.6.1:  104209
      3.6.2:  558134
      3.7.0:  592782
  followers:     246
name:            ntp
source_url:      https://github.com/chef-cookbooks/ntp
up_for_adoption: 
updated_at:      2019-10-01T17:19:00.140Z
versions:
  https://supermarket.chef.io/api/v1/cookbooks/ntp/versions/3.7.0
  https://supermarket.chef.io/api/v1/cookbooks/ntp/versions/3.6.2
  https://supermarket.chef.io/api/v1/cookbooks/ntp/versions/3.6.1
  https://supermarket.chef.io/api/v1/cookbooks/ntp/versions/3.6.0
  https://supermarket.chef.io/api/v1/cookbooks/ntp/versions/3.5.6
  https://supermarket.chef.io/api/v1/cookbooks/ntp/versions/3.5.5
  https://supermarket.chef.io/api/v1/cookbooks/ntp/versions/3.5.4
(snip)
```

### 手元にcookbookをtar.gzでダウンロードする
```
$ knife supermarket download ntp
Downloading ntp from Supermarket at version 3.7.0 to /Users/tsuyoshi/git/test/hello-chef/ntp-3.7.0.tar.gz
Cookbook saved: /Users/tsuyoshi/git/test/hello-chef/ntp-3.7.0.tar.gz
$ ls ntp-3.7.0.tar.gz 
ntp-3.7.0.tar.gz
```

なお、バージョンを指定することもできます。
```
$ knife supermarket download ntp 3.6.0
Downloading ntp from Supermarket at version 3.6.0 to /Users/tsuyoshi/git/test/hello-chef/ntp-3.6.0.tar.gz
Cookbook saved: /Users/tsuyoshi/git/test/hello-chef/ntp-3.6.0.tar.gz
```

### cookbookを探索する
searchで探索することができます。
```
$ knife supermarket search yapache2
apache:
  cookbook:             https://supermarket.chef.io/api/v1/cookbooks/apache
  cookbook_description: various apache server related resource provides (LWRP)
  cookbook_maintainer:  melezhik
  cookbook_name:        apache
apache2:
  cookbook:             https://supermarket.chef.io/api/v1/cookbooks/apache2
  cookbook_description: Installs and configures apache2
  cookbook_maintainer:  sous-chefs
  cookbook_name:        apache2
apache2-git-site:
  cookbook:             https://supermarket.chef.io/api/v1/cookbooks/apache2-git-site
  cookbook_description: Sets up an apache vhost site backed by a git repo
  cookbook_maintainer:  sdetheridge
  cookbook_name:        apache2-git-site

(snip)
```

### 外部からダウンロードできるcookbook一覧を表示する
非常に大量な出力があるので一部だけ抜粋します。
```
$ knife supermarket list | head -5
1password                             chef_bird                           
301                                   chef-bitcoind                       
3cx                                   chef_blockdev                       
7dtd                                  chef_bundle                         
7-zip                                 chef_ca    
(snip)
```


---
# sshに関する操作

### 特定のnodeに対してchef-clientを実行する。
```
$ knife ssh 'name:hoge' 'sudo chef-client' -x username -P pass
```

### 全てのnodeに対してchef-clientを実行する
```
$ knife ssh 'name:*' 'sudo chef-client'
```

---
# diffに関する操作

### chefサーバとのdiffを表示する
```
$ knife diff roles/linux.json 
diff --knife roles/linux.json roles/linux.json
--- roles/linux.json	2020-08-24 22:44:44.892464759 +0900
+++ roles/linux.json	2020-08-24 22:44:44.891378696 +0900
@@ -1,5 +1,6 @@
 {
   "name": "linux",
+  "description": "this is linux server",
   "run_list": [
     "recipe[default]"
   ]
```


---

# clientに関する操作
### クライアント一覧を表示する
```
$ knife client list
tsuyopon-validator
```


# 参考資料
- knife zeroに関する資料
  - https://knife-zero.github.io/

# あとでまとめたい資料
- https://gist.github.com/ipedrazas/aadbaeb808f5ace5d3ce
- https://qiita.com/sawanoboly/items/4f363909615d8a76e9e5  
- https://qiita.com/szit/items/8afcca1160b9a27e0e70
