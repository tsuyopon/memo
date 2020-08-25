# 概要
recipe(rubyスクリプト)はresourceを記述することで構成されます。

基本的にはわからない用語などはここでページ探索で探すことができる。
- https://docs.chef.io/resources/#common-functionality-resources_common_notification

chefのcookbookを探したい場合には、以下を参考にすると良い
- supermarket
  - https://supermarket.chef.io/cookbooks
- github chef-cookbooks
  - https://github.com/chef-cookbooks

# 詳細

### 記法がわからない
以下でSearchすると大抵出てくる。
- https://docs.chef.io/resources/


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
階層の深いディレクトリを作る場合などは、recursiveをつけます。
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


### インターネット上のファイルをダウンロードして保存する
```
#
# remote_file: インターネット上のファイルをダウンロードして保存する
#
remote_file "/tmp/resource.html" do
  source "http://docs.getchef.com/chef/resources.html"
  mode "644"
  owner "someone"
end
```

### Docker Cookbookについて
docker_image, docker_container, docker_serviceなどのリソースは以下のドキュメントを参照すること
- https://github.com/chef-cookbooks/docker


# 参考
- chef公式ドキュメント(Resource)
  - https://docs.chef.io/resources/
- chef公式ドキュメント(package)
  - https://docs.chef.io/resources/package/
- supermarket
  - https://supermarket.chef.io/cookbooks
- apache2関連
  - https://github.com/sous-chefs/apache2
