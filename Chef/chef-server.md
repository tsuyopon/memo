# 概要
以下のChef-server管理画面を使うまでのセットアップ手順について
- https://manage.chef.io/

chefは資料が散在しているので、かなーり苦労した。。。

# 手順
まずはchefのアカウントを作成する必要があります。
- https://manage.chef.io/

作成すると秘密鍵が割り当てられますので、以下のパスに保存します。
```
$ ls -alt ~/.chef/tsuyopon.pem 
-rw-r--r--  1 tsuyoshi  staff  1675  8 22 17:12 /Users/tsuyoshi/.chef/tsuyopon.pem
```


cookbookレポジトリの直下に.chef/knife.rbを配置します。
chef-serverを利用する場合には、local_modeはfalseに設定して、以下のドキュメントに従ってセットアップします。
- https://docs.chef.io/workstation/getting_started/
```
$ cat .chef/knife.rb 
# Chef-Zeroモードの場合にはtrueにする。Chef-Serverを利用する場合にはfalseにする
local_mode false

# Chef-Serverを利用する場合の設定
# See: https://docs.chef.io/workstation/getting_started/
current_dir = File.dirname(__FILE__)
log_level                :info
log_location             STDOUT
client_key               "#{ENV['HOME']}/.chef/tsuyopon.pem"             # 鍵が配置されていること
node_name                'tsuyopon'                                      # ユーザー名
validation_client_name   'tsuyopon-validator'                            # 組織＋ -validator
validation_key           "#{current_dir}/tsuyopon-validator.pem"         # 組織名(このファイルは存在していない。。。本当に必要??)
chef_server_url          'https://api.chef.io/organizations/tsuyopon'    # サーバーのホスト名と、最後は組織名に変更する
cache_type               'BasicFile'
cache_options( :path => "#{ENV['HOME']}/.chef/checksums" )
cookbook_path            ["#{current_dir}/../cookbooks"]
#### Chef-Serverここまで

ssl_verify_mode        :verify_none

# 便利設定
chef_repo_dir = File.absolute_path( File.dirname(__FILE__) + "/.." )
node_path     "#{chef_repo_dir}/nodes"
role_path     "#{chef_repo_dir}/roles"

# data_bag設定
data_bag_path    "data_bags"
encrypted_data_bag_secret ".chef/data_bag_key"
```


```
// cookbookをアップロード
$ knife cookbook upload --all

// nodeをアップロード
$ knife upload nodes/localhost.local.json 

// environementをアップロード
$ knife upload environments/development.json 
$ knife upload environments/production.json 

// databagをアップロード
$ knife upload data_bags/credentials/aria.json 

// rolesをアップロード
$ knife upload roles/freebsd.json 
$ knife upload roles/linux.json 
```



