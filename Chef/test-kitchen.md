# 概要
chefへの操作を気軽に仮想環境を作成して試せる仕組みのようです。

# 詳細

### 使ってみる

必要な方はtest-kitchenをインストールしてください。自分はbrewでchefdkをインストールした際に一緒にインストールされたと思います。
```
$ gem install test-kitchen
```

今回以下のバージョンで環境構築を確認しています。
```
$ chef --version
ChefDK version: 4.10.0
Chef Infra Client version: 15.13.8
Chef InSpec version: 4.22.1
Test Kitchen version: 2.5.4
Foodcritic version: 16.3.0
Cookstyle version: 5.23.0
```

Test KitchenのdriverはデフォルトでVagrantを利用します。
```
$ brew install --cask vagrant
```

chef generate cookbookで初期化されたcookbookを作成します。
```
$ chef generate cookbook hello-chef
Hyphens are discouraged in cookbook names as they may cause problems with custom resources. See https://docs.chef.io/ctl_chef.html#chef-generate-cookbook for more information.
Generating cookbook hello-chef
- Ensuring correct cookbook content
- Committing cookbook files to git

Your cookbook is ready. Type `cd hello-chef` to enter it.

There are several commands you can run to get started locally developing and testing your cookbook.
Type `delivery local --help` to see a full list of local testing commands.

Why not start by writing an InSpec test? Tests for the default recipe are stored at:

test/integration/default/default_test.rb

If you'd prefer to dive right in, the default recipe can be found at:

recipes/default.rb

$ cd hello-chef
```

cookbookディレクトリ直下には雛形として生成されたkitchen.ymlを見てみます。
```
$ cat kitchen.yml 
---
driver:
  name: vagrant

## The forwarded_port port feature lets you connect to ports on the VM guest via
## localhost on the host.
## see also: https://www.vagrantup.com/docs/networking/forwarded_ports.html

#  network:
#    - ["forwarded_port", {guest: 80, host: 8080}]

provisioner:
  name: chef_zero

  ## product_name and product_version specifies a specific Chef product and version to install.
  ## see the Chef documentation for more details: https://docs.chef.io/config_yml_kitchen.html
  #  product_name: chef
  #  product_version: 15

verifier:
  name: inspec

platforms:
  - name: ubuntu-18.04
  - name: centos-7

suites:
  - name: default
    verifier:
      inspec_tests:
        - test/integration/default
    attributes:
```

- driver: Test Kitchen が仮想環境構築を委託するドライバの名前。デフォルトはvagrant
- provisioner: Test Kitchen がプロビジョニングで使うツールの名前。デフォルトはchef_zero
- platforms: 構築対象のプラットフォーム
- suites: Test Kitchen が構築するテストスイート 


インスタンスの作成にはkitchen verifyを実行します。
```
$ kitchen verify
-----> Starting Test Kitchen (v2.5.4)
WARN: Unresolved or ambigious specs during Gem::Specification.reset:
      minitest (~> 5.1)
      Available/installed versions of this gem:
      - 5.14.1
      - 5.11.3
WARN: Clearing out unresolved specs. Try 'gem cleanup <gem>'
Please report a bug if this causes problems.
-----> Converging <default-ubuntu-1804>...
       Preparing files for transfer
       Policy lock file doesn't exist, running `chef install` for Policyfile /Users/tsuyoshi/git/test/hello-chef/Policyfile.rb...
       Building policy hello-chef
       Expanded run list: recipe[hello-chef::default]
       Caching Cookbooks...
       Installing hello-chef >= 0.0.0 from path

...

       Installing chef 
       installing with rpm...
       warning: /tmp/omnibus/cache/chef-16.4.41-1.el7.x86_64.rpm: Header V4 DSA/SHA1 Signature, key ID 83ef826a: NOKEY
       Preparing...                          ################################# [100%]
       Updating / installing...
          1:chef-16.4.41-1.el7               ################################# [100%]
       Thank you for installing Chef Infra Client! For help getting started visit https://learn.chef.io
       Transferring files to <default-centos-7>
       +---------------------------------------------+
       ✔ 2 product licenses accepted.
       +---------------------------------------------+
       Starting Chef Infra Client, version 16.4.41
       Creating a new client identity for default-centos-7 using the validator key.
       Using policy 'hello-chef' at revision '4ec3e9522db538a3fb8e7c94fc087c7e7e9775d69986c00a40e2a98ce8373082'
       resolving cookbooks for run list: ["hello-chef::default@0.1.0 (d22971f)"]
       Synchronizing Cookbooks:
         - hello-chef (0.1.0)
       Installing Cookbook Gems:
       Compiling Cookbooks...
       Converging 0 resources
       
       Running handlers:
       Running handlers complete
       Chef Infra Client finished, 0/0 resources updated in 01 seconds
       Downloading files from <default-centos-7>
       Finished converging <default-centos-7> (0m14.50s).
-----> Setting up <default-centos-7>...
       Finished setting up <default-centos-7> (0m0.00s).
-----> Verifying <default-centos-7>...
       Loaded tests from {:path=>".Users.tsuyoshi.git.test.hello-chef.test.integration.default"} 

Profile: tests from {:path=>"/Users/tsuyoshi/git/test/hello-chef/test/integration/default"} (tests from {:path=>".Users.tsuyoshi.git.test.hello-chef.test.integration.default"})
Version: (not specified)
Target:  ssh://vagrant@127.0.0.1:2200

  User root
     ↺  
  Port 80
     ↺  

Test Summary: 0 successful, 0 failures, 2 skipped
       Finished verifying <default-centos-7> (0m0.51s).
-----> Test Kitchen is finished. (0m35.92s)
```

インスタンス一覧を確認してみます。
```
$  kitchen list
Instance             Driver   Provisioner  Verifier  Transport  Last Action  Last Error
default-ubuntu-1804  Vagrant  ChefZero     Inspec    Ssh        Verified     <None>
default-centos-7     Vagrant  ChefZero     Inspec    Ssh        Verified     <None>
```

ではもう一度、インスタンスを指定して実行してみましょう。必要なダウンロードは完了しているので今度は即座に実行できています。
```
$  kitchen verify default-ubuntu-1804
-----> Starting Test Kitchen (v2.5.4)
WARN: Unresolved or ambigious specs during Gem::Specification.reset:
      minitest (~> 5.1)
      Available/installed versions of this gem:
      - 5.14.1
      - 5.11.3
WARN: Clearing out unresolved specs. Try 'gem cleanup <gem>'
Please report a bug if this causes problems.
-----> Verifying <default-ubuntu-1804>...
       Loaded tests from {:path=>".Users.tsuyoshi.git.test.hello-chef.test.integration.default"} 

Profile: tests from {:path=>"/Users/tsuyoshi/git/test/hello-chef/test/integration/default"} (tests from {:path=>".Users.tsuyoshi.git.test.hello-chef.test.integration.default"})
Version: (not specified)
Target:  ssh://vagrant@127.0.0.1:2222

  User root
     ↺  
  Port 80
     ↺  

Test Summary: 0 successful, 0 failures, 2 skipped
       Finished verifying <default-ubuntu-1804> (0m0.61s).
-----> Test Kitchen is finished. (0m3.22s)
```

デフォルトのテストだと上記2つは条件に合わずにskippedされてしまっています。

ではテストを追加してみます。
```
$ vim test/integration/default/default_test.rb
// 以下の行を追加します。
describe file('/tmp/test.txt') do
  its(:content) { should match %r(^hello world\.$) }
end
```

もちろん/tmp/test.txt自体存在していないので、失敗しました。
```
$  kitchen verify default-ubuntu-1804
-----> Starting Test Kitchen (v2.5.4)
WARN: Unresolved or ambigious specs during Gem::Specification.reset:
      minitest (~> 5.1)
      Available/installed versions of this gem:
      - 5.14.1
      - 5.11.3
WARN: Clearing out unresolved specs. Try 'gem cleanup <gem>'
Please report a bug if this causes problems.
-----> Verifying <default-ubuntu-1804>...
       Loaded tests from {:path=>".Users.tsuyoshi.git.test.hello-chef.test.integration.default"} 

Profile: tests from {:path=>"/Users/tsuyoshi/git/test/hello-chef/test/integration/default"} (tests from {:path=>".Users.tsuyoshi.git.test.hello-chef.test.integration.default"})
Version: (not specified)
Target:  ssh://vagrant@127.0.0.1:2222

  User root
     ↺  
  Port 80
     ↺  
  File /tmp/test.txt
     ×  content is expected to match /^hello world\.$/
     expected nil to match /^hello world\.$/

Test Summary: 0 successful, 1 failure, 2 skipped
>>>>>> ------Exception-------
>>>>>> Class: Kitchen::ActionFailed
>>>>>> Message: 1 actions failed.
>>>>>>     Verify failed on instance <default-ubuntu-1804>.  Please see .kitchen/logs/default-ubuntu-1804.log for more details
>>>>>> ----------------------
>>>>>> Please see .kitchen/logs/kitchen.log for more details
>>>>>> Also try running `kitchen diagnose --all` for configuration
```

では、/tmp/test.txtを実行するレシピを追加してみます。
```
$ vim recipes/default.rb 
// 以下の行を追加
file '/tmp/test.txt' do
  content "hello world.\n"
end
```

あとは、kitchen.ymlへのrun_listにレシピを追加します。run_listの行が追加されたことを確認してください。
```
$ vim kitchen.yml

// 一部のみ抜粋
suites:
  - name: default
    run_list: recipe[hello-chef::default]
    verifier:
      inspec_tests:
        - test/integration/default
    attributes:
```

レシピを実行します。
```
$ kitchen converge
(出力は省略)
```

テストを実行するためverifyを実行して確認してみます。今度は/tmp/test.txtが存在するので成功するようになりました。
```
$ kitchen verify default-ubuntu-1804
-----> Starting Test Kitchen (v2.5.4)
-----> Setting up <default-ubuntu-1804>...
       Finished setting up <default-ubuntu-1804> (0m0.00s).
-----> Verifying <default-ubuntu-1804>...
       Loaded tests from {:path=>".Users.tsuyoshi.git.test.hello-chef.test.integration.default"} 

Profile: tests from {:path=>"/Users/tsuyoshi/git/test/hello-chef/test/integration/default"} (tests from {:path=>".Users.tsuyoshi.git.test.hello-chef.test.integration.default"})
Version: (not specified)
Target:  ssh://vagrant@127.0.0.1:2222

  User root
     ↺  
  Port 80
     ↺  
  File /tmp/test.txt
     ✔  content is expected to match /^hello world\.$/

Test Summary: 1 successful, 0 failures, 2 skipped
       Finished verifying <default-ubuntu-1804> (0m0.63s).
-----> Test Kitchen is finished. (0m3.13s)
```

以上が簡単なtest-kitchenの使い方です。


### attributeとtemplate機能を使って、設定ファイルを作成する
ここでは「使ってみる」までの処理が終わっていて、run_listへの追加が完了していることを仮定しています。

サンプルとして/tmp/ntp.confに設定ファイルを配置することを考えてみます。その設定ファイルはattributesで指定した値が入っています。

attributeディレクトリが存在しない場合には、以下で雛形を作れます。
```
$ chef generate attribute . default
Recipe: code_generator::attribute
  * directory[././attributes] action create
    - create new directory ././attributes
  * template[././attributes/default.rb] action create
    - create new file ././attributes/default.rb
    - update content in file ././attributes/default.rb from none to e3b0c4
    (diff output suppressed by config)

$ tree attributes/
attributes/
└── default.rb

0 directories, 1 file
```

動的に変更できるように次のように値を入れておきます。
```
$ vim attributes/default.rb
$ cat attributes/default.rb 
default["test_cookbook"]["servers"] = [ 'ntp1.jst.mfeed.ad.jp', 'ntp2.jst.mfeed.ad.jp', 'ntp3.jst.mfeed.ad.jp' ]
```

続いて、レシピを追加します。
今回は/tmp/へのntp.confの配置なのでntpdの再起動部分についてはコメントにしておきます。もし/etc/ntp.confに配置するのであればここはコメントを外す必要があります。
```
$ vim recipes/default.rb 
$ cat recipes/default.rb 
template "/tmp/ntp.conf" do
  source "ntp.conf.erb"
#  notifies :restart, "service[ntpd]"
  action :create
  variables({
    :ntp_servers => node["test_cookbook"]["servers"]
  })  
end
```

続いて、templateディレクトリが存在しない場合には、以下で雛形を作れます。
```
$ chef generate template . ntp.conf.erb
Recipe: code_generator::template
  * directory[././templates] action create
    - create new directory ././templates
  * template[././templates/ntp.conf.erb] action create
    - create new file ././templates/ntp.conf.erb
    - update content in file ././templates/ntp.conf.erb from none to e3b0c4
    (diff output suppressed by config)

$ tree templates/
templates/
└── ntp.conf.erb

0 directories, 1 file
```

続いて、テンプレートを配置します。
```
$ vim templates/ntp.conf.erb 
$ cat templates/ntp.conf.erb 
<% @ntp_servers.each do |ntp_server| %>
server <%= ntp_server %>
<% end %>
```

ではレシピを実行してみます。
```
$ kitchen converge
```

仮想インスタンスでファイルが正しく生成されたかどうかを確認します。
```
$ kitchen list                                       // instanceを確認
$ kitchen login default-ubuntu-1804                  // instanceを指定してログイン
vagrant@default-ubuntu-1804:~$ cat /tmp/ntp.conf 
server ntp1.jst.mfeed.ad.jp
server ntp2.jst.mfeed.ad.jp
server ntp3.jst.mfeed.ad.jp
```

### テストを実行する
これを実行すると、 作成、Chefレシピ反映、InSpecテストを通して全てを実行するらしい。
```
$ kitchen test
```

オプションとしてはtestはcreate, setup, converage, verify, destroyの一連のライフサイクルが全て実行される。
```
- kitchen create:   インスタンスを作成する
- kitchen setup:    chefとbusserをインストールしてChef-repoをアップロード、初回のconvergenceを行う。
- kitchen converge: chef-reposが再度アップロードされ、Chef-Solo(またはローカルモード)を実行する。 繰り返し実行可能。
- kitchen verify:   testディレクトリがアップロードされ、busser経由でテストスイートをインストールし、テストを実行する。 繰り返し実行可能。
- kitchen destroy:  インスタンスを破棄する。
- kitchen test:     上記テストのライフサイクルを一括で行う。 実行時にインスタンスがすでに存在する場合は初手でもDestroyが実行される。
```

### 不要になったインスタンスを削除する
一覧を確認します。
```
$ kitchen list
Instance             Driver   Provisioner  Verifier  Transport  Last Action  Last Error
default-ubuntu-1804  Vagrant  ChefZero     Inspec    Ssh        Converged    Kitchen::ActionFailed
default-centos-7     Vagrant  ChefZero     Inspec    Ssh        Converged    <None>
```

不要になったので一旦綺麗にします。
```
$ kitchen destroy
-----> Starting Test Kitchen (v2.5.4)
-----> Destroying <default-ubuntu-1804>...
       ==> default: Forcing shutdown of VM...
       ==> default: Destroying VM and associated drives...
       Vagrant instance <default-ubuntu-1804> destroyed.
       Finished destroying <default-ubuntu-1804> (0m8.18s).
-----> Destroying <default-centos-7>...
       ==> default: Forcing shutdown of VM...
       ==> default: Destroying VM and associated drives...
       Vagrant instance <default-centos-7> destroyed.
       Finished destroying <default-centos-7> (0m6.23s).
-----> Test Kitchen is finished. (0m17.41s)
```

一覧には表示されますが、Last Actionが変わったことが確認できます。
```
$ kitchen list
Instance             Driver   Provisioner  Verifier  Transport  Last Action    Last Error
default-ubuntu-1804  Vagrant  ChefZero     Inspec    Ssh        <Not Created>  <None>
default-centos-7     Vagrant  ChefZero     Inspec    Ssh        <Not Created>  <None>
```

試しにログインしてみようとするとエラーになります。
```
$ kitchen login default-ubuntu-1804
>>>>>> ------Exception-------
>>>>>> Class: Kitchen::UserError
>>>>>> Message: Instance <default-ubuntu-1804> has not yet been created
>>>>>> ----------------------
>>>>>> Please see .kitchen/logs/kitchen.log for more details
>>>>>> Also try running `kitchen diagnose --all` for configuration
```


### kitchenコマンドヘルプ
```
$ kitchen 
Commands:
  kitchen console                                 # Kitchen Console!
  kitchen converge [INSTANCE|REGEXP|all]          # Change instance state to converge. Use a provisioner to configure one or more instances
  kitchen create [INSTANCE|REGEXP|all]            # Change instance state to create. Start one or more instances
  kitchen destroy [INSTANCE|REGEXP|all]           # Change instance state to destroy. Delete all information for one or more instances
  kitchen diagnose [INSTANCE|REGEXP|all]          # Show computed diagnostic configuration
  kitchen doctor INSTANCE|REGEXP                  # Check for common system problems
  kitchen exec INSTANCE|REGEXP -c REMOTE_COMMAND  # Execute command on one or more instance
  kitchen help [COMMAND]                          # Describe available commands or one specific command
  kitchen init                                    # Adds some configuration to your cookbook so Kitchen can rock
  kitchen list [INSTANCE|REGEXP|all]              # Lists one or more instances
  kitchen login INSTANCE|REGEXP                   # Log in to one instance
  kitchen package INSTANCE|REGEXP                 # package an instance
  kitchen setup [INSTANCE|REGEXP|all]             # Change instance state to setup. Prepare to run automated tests. Install busser and related gems on one or more instances
  kitchen test [INSTANCE|REGEXP|all]              # Test (destroy, create, converge, setup, verify and destroy) one or more instances
  kitchen verify [INSTANCE|REGEXP|all]            # Change instance state to verify. Run automated tests on one or more instances
  kitchen version                                 # Print Kitchen's version information
```

### kitchenコマンドの概要

テスト実行に必要なコマンド
- kitchen create:   インスタンスを作成する
- kitchen setup:    chefとbusserをインストールしてChef-repoをアップロード、初回のconvergenceを行う。
- kitchen converge: chef-reposが再度アップロードされ、Chef-Solo(またはローカルモード)を実行する。 繰り返し実行可能。
- kitchen verify:   testディレクトリがアップロードされ、busser経由でテストスイートをインストールし、テストを実行する。 繰り返し実行可能。
- kitchen destroy:  インスタンスを破棄する。
- kitchen test:     上記テストのライフサイクルを一括で行う。 実行時にインスタンスがすでに存在する場合は初手でもDestroyが実行される。


なお、kitchen testには --destroy=neverというオプションをつけて実行するとインスタンスが破棄されずに保持される。


構成確認、デバッグ
- kitchen list:      .kitchen.ymlにあるInstanceリストとライフサイクル上の状態を表示する。 Instanceの状態は逐一.kitchen/以下にyamlで吐かれているのでそれをみてもよい。
- kitchen login:     InstanceにSSHでログインする。execで物足りない時に。
- kitchen console:  .kitchen.yml と設定を読み込んだRubyのプロンプトが立ち上がる。@instancesや@suitesで各種設定が妥当か確認できる。
- kitchen diagnose: .kitchen.ymlほかによって最終的に有効になっている各種設定をダンプする。consoleの簡易版。

- 参考
  - https://qiita.com/sawanoboly/items/9f560bd63ad0712b17ba

### test-kitchen実行に必要な雛形を作成する
kitchen initで必要な雛形を作成することができます。
```
$ kitchen init
      create  kitchen.yml
    conflict  chefignore
Overwrite /Users/tsuyoshi/git/chef-repo/chefignore? (enter "h" for help) [Ynaqdhm] ls
        Y - yes, overwrite
        n - no, do not overwrite
        a - all, overwrite this and all others
        q - quit, abort
        d - diff, show the differences between the old and the new
        h - help, show this help
        m - merge, run merge tool
Overwrite /Users/tsuyoshi/git/chef-repo/chefignore? (enter "h" for help) [Ynaqdhm] n
        skip  chefignore
      create  test/integration/default
      append  .gitignore
      append  .gitignore
```

# 公式URL
- github test-kitchen/test-kitchen
  - https://github.com/test-kitchen/test-kitchen

仮想サーバ関連プラグイン
- github test-kitchen/kitchen-vagrant
  - https://github.com/test-kitchen/kitchen-vagrant
- github test-kitchen/kitchen-docker
  - https://github.com/test-kitchen/kitchen-docker
