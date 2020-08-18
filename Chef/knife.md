# 概要
knifeコマンドについての基本事項についてまとめます。
ヘルプを見るとわかりますが、knifeはサブコマンドの種類も非常に豊富です。このファイルでは基本的なことについてのみまとめます。


knifeコマンドの各サブコマンドに「-z (--local-mode)」オプションを付与して実行することで、Node Objectのみならず、このchef-repoディレクトリ内の情報を操作できます。これはレポジトリ直下の.repo/knife.rbに「local_mode true」を設定することで回避できます。

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


# roleに関する操作

### role一覧を表示する
```
$ knife role list
linux-server
```

### roleを作成する
```
$ knife role create role_test
```

### roleを編集する
```
$ knife role edit role_test
```

# cookbookに関する操作

### cookbook一覧を表示する
```
$ knife cookbook list
example     1.0.0
test-cook   0.1.0
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

### uploadしたcookbookを削除する
```
$ knife cookbook delete sample
```



