# 概要
recipe(rubyスクリプト)はresourceを記述することで構成されます。

基本的にはわからない用語などはここでページ探索で探すことができる。
- https://docs.chef.io/resources/#common-functionality-resources_common_notification

chefのcookbookを探したい場合には、以下を参考にすると良い
- supermarket
  - https://supermarket.chef.io/cookbooks
- github chef-cookbooks
  - https://github.com/chef-cookbooks


# 関連リンク
- action
  - https://docs.chef.io/custom_resources/#define-actions
- template
  - https://docs.chef.io/custom_resources/#create-templates

# 詳細

### 記法がわからない
以下でSearchすると大抵出てくる。
- https://docs.chef.io/resources/


### サービス起動、停止、再起動
```
### httpdの起動 + chkconfig on を実施
service 'start httpd add chkconfig on' do
  service_name 'httpd'
  action [:enable, :start]
end         
# actionは複数じゃなければ、[]はいらないが、文言統一のために毎回[]でくくった方が良い
# supports status: true, restart: true, reload: true を指定すると、httpdではこのコマンドが使えるよ！と教えて上げれる。使う場合は記述しましょう。
# restart => trueを指定しない場合、stop + start で代用される
# ignore_failure true を指定すると、エラーは無視します。

### Action  説明
# :enable ブート時の起動を有効化
# :disable  ブート時の起動を無効化
# :nothing  何もしない（default）
# :start  サービスを起動
# :stop サービスを停止
# :restart  サービスを再起動
# :reload
```

### Unix user, groupの管理を行う
以下でgroupやuserを作成できます。 passwordは「openssl passwd -1 <平文>」で出力された値を設定します。
```
#
# someone グループを id=1234 で作成
#
group "someone" do
  action :create
  gid 1234
end

#
# someone ユーザを id=1234 で someone グループに所属させて作成
# ホームディレクトリ /home/someone に作成する
# シェルは /bin/bash 
#
user "someone" do
  action :create
  password "$1$KCZSWBS7$lEdJee271ba2dlsb.YOwD0"     # 「openssl passwd -1 "this is plain text password"」
  uid 1234
  gid "someone"
  home "/home/someone"
  shell "/bin/bash"
  supports { :manage_home => true }
end

#
# app ユーザをシステムユーザとして作成
#
user "app" do
  uid 2345
  system true
  shell "/bin/false"
end
```

groupの修正の場合の例も添付しておく
```
# append trueにすると、追加するユーザだけ記述すればいい。
# append falseにすれば、apacheに属しているユーザを全て書かなければならない。
# 新しくgroupを作りたい場合はデフォルトのcreateです。
group 'apache' do
   gid 48
   members ['hoge', 'fuga']
   append true
   action :modify
end
```

### ファイルを定義する

以下で指定したパスにファイルを作成します。ファイルの内容はcontentに記述します。
```
#
# file: サーバ内のファイルを定義する
#
file "/tmp/platform.txt" do 
  content "platform: #{node[:platform]}"
  mode 0644 # 注: 0644は8進数表記。644だと違う意味になってしまう。文字列で"644"の方がミスしにくい。
  owner "root"
end
```

以下の記法は、不必要なファイルが存在しない状態を定義する。削除するというタスクではないことに注意!!
```
file "/tmp/unused.txt" do
  action :delete
end
```

### ディレクトリの管理を行う
階層の深いディレクトリを作る場合などは、recursive trueをつけます。
```
directory "/tmp/too/deep/dir" do
  action :create
  recursive true
  owner "someone"
  mode 0755
end
```

### シンボリックリンクを管理する
```
link "/tmp/ip.txt" do
  to "/tmp/hoge/ipaddress.txt"
end
```

削除する場合には以下の通りです
```
link "/tmp/unknown_link" do
  action :delete
end
```

### パッケージインストール
```
# symlinksとprelink packageのインストール + アップデート
package 'install package' do
  package_name [
    'symlinks',
    'prelink'
  ]
  options "--disablerepo=* --enablerepo=base,epel"
  action :upgrade
end
```


### パッケージインストール、サービス起動、関連パッケージとnotifies通知
```
# httpdパッケージ(version2.4.6)をインストールする
package 'httpd' do
	version '2.4.6'
	action :install
end

# httpdサービスをenableにして、startする
# 注意すべき点として、 この記述の場合、サービスが（起動していない場合に）起動するタイミングはChefの処理の最後 になります。
# これは、serviceリソースなどはデフォルトでは遅延実行となっており、chef実行の最後に行われます。
service "httpd" do
	action [ :enable, :start ]
end

# mod_sslをインストールしたら、service[httpd]をrestartする。detalyedが指定されている場合、レシピの最後に実行される。
package 'mod_ssl' do
	action :install
	notifies :restart, 'service[httpd]', :delayed
end
```

delayed(リソース実行後に遅延実行)やimmedeatery(即時実行)があります。

### スクリプトを実行させたい場合
not_ifの条件がない場合には、何度でも実行されてしまいます。
```
bash "test script" do
  code <<-EOS
    # script here
    touch evidence
  EOS
  user "someone"
  cwd "/path/to/execute"
  environment { "PATH" => "/usr/local/pgsql/bin" }
  not_if "test -e /path/to/execute/evidence"
end
```

bashでなくてもtemplate等他のresourceでも利用することができます。


### 設定ファイルに変更があったら即時に他のリソースのアクションを実行する(notifies, subscribes)

以下はnotifiesの例です。notifiesは自身のリソースの更新があったら、他のリソースのアクションを実行します。
```
#
# リソース定義のみ。何もしない。
#
service "ntp" do
  action :nothing
end

#
# ntpd.confに変更があったら、即時
#
template "/etc/ntpd.conf" do
  mode 0644
  notifies :restart, "service[ntp]", :immediately
end
```

上記と同様のことをsubscribeで記述できます。subscribeは監視しているリソースの更新があったら自身のリソースを実行します。
```
#
# ntpd.confの変更を監視する
# 
service "ntp" do
  action :nothing
  subscribes :restart, "template[/etc/ntpd.conf]", :immediately
end

#
# ntpd.confテンプレート
#
template "/etc/ntpd.conf" do
  mode 0644
end
```


### templateに変数を渡す
以下の例ではinstance_nameとportという変数を渡すことができます。 
```
template "/etc/httpd/conf/httpd-#{new_resource.instance_name}.conf" do
  source 'httpd.conf.erb'
  variables(
    instance_name: new_resource.instance_name,
    port: new_resource.port
  )
  action :create
  owner  'root'
  group  'root'
  mode   '0644'
end
```


### インターネット上のファイルをダウンロードして保存する
```
#
# remote_file: インターネット上のファイルをダウンロードして保存する
#
remote_file "/tmp/resource.html" do
  source "http://docs.getchef.com/chef/resources.html"
  mode "644"
  owner 'root'
  group 'root'
end
```

### 文字列置換したい場合
```
### /tmp/hoge.txtに書かれてるeth0をeth1に変更
file '/tmp/hoge.txt' do
  f = Chef::Util::FileEdit.new(path)
  f.searchfile_replace_line('eth0', 'eth10')
  content f.send(:editor).lines.join
end
```

### only_ifとnot_if
not_if : 既にファイルが存在している場合コマンドを実行しない
```
### only_ifの例
# file が存在し、シンボリックリンクであれば、削除を実行する。
link "/tmp/mylink" do
  action :delete
  only_if "test -L /tmp/mylink"
end

# /var/lib/mysqlが存在した場合、/tmp/hoge.txtを作成する
file '/tmp/hoge.txt' do
  owner 'root'
  group 'root'
  mode '0644'
  only_if {Dir.exist?("/var/lib/mysql")}
end
```

only_if : 既にファイルが存在している場合コマンドを実行する
```
### not_ifの例
# /tmp/hogeが存在した場合、書き込まない
bash "fugaaa" do
    code <<-EOS
      echo "fugaaaaa" >> /tmp/hoge
    EOS
    not_if { File.exist?('/tmp/hoge') }
end
```

### environmentsの情報を取得する

```
### もしenvironmentsがproductionだったら・・・
### もしenvironmentsがdevelopmentだったら・・・
if node.chef_environment == "production"
   ・・・・
elsif node.chef_environment == "development"
   ・・・・
end 
```

### Docker Cookbookについて
docker_image, docker_container, docker_serviceなどのリソースは以下のドキュメントを参照すること
- https://github.com/chef-cookbooks/docker


### デバッグモードを有効にしたい
以下のchefspec_options[:log_level]にdebugを設定すれば良い。「
```
describe 'something' do
  chefspec_options[:log_level] = :debug
end
```

### カスタムリソースを作成する
custom resourceはresourcesディレクトリを作成して配置する。
以下を参考にresources/greet.rbとspec/greet_spec.rbを作成して、「chef exec rspec」でテストを実行することができる。
- https://github.com/chefspec/chefspec/tree/v8.0.0#when-to-use-chefspec

簡単なサンプルは以下に配置している。
- https://github.com/tsuyopon/hello-chef

### 上書きさせたくないような場合
上書きが困る場合はaction: create_if_missing や not_if {File.exist?} などを使いましょう


# 参考
- chef公式ドキュメント(Resource)
  - https://docs.chef.io/resources/
- chef公式ドキュメント(package)
  - https://docs.chef.io/resources/package/
- supermarket
  - https://supermarket.chef.io/cookbooks
- apache2関連
  - https://github.com/sous-chefs/apache2

# 関連資料
- https://qiita.com/sion_cojp/items/656f35fef354db833dbf
