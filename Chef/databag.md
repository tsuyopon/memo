# 概要
databagに機密データを追加してみます。

# 詳細

### databagを使ってみて、秘密の情報を保存する。(とりあえず使ってみる)
databag用の設定を配置します。レポジトリ直下の.chef/knife.rbに以下の情報を配置します。
```
$ cat .chef/knife.rb 
data_bag_path    "data_bags"
encrypted_data_bag_secret ".chef/data_bag_key"
```

乱数を生成して、その乱数を秘密鍵用の入力値として指定します。
なお--localオプションを付与しているのは、Chefのクライアントモードだから。これをつけないとChefサーバに情報が保存される??(未確認)
```
$ openssl rand -base64 512 > .chef/data_bag_key
$ EDITOR=vim knife data bag create credentials aria --secret-file .chef/data_bag_key --local
WARN: No cookbooks directory found at or above current directory.  Assuming /Users/tsuyoshi/git/test/hello-chef.
Data bag credentials already exists
Created data_bag_item[aria]
```

次のようにエディタが開きますが、secretの行は自分が記入しています。これが秘密の情報になります。
```
{
  "id": "aria",
  "secret": "this is my secret value"
}
```

上記保存を行うと、次のjson情報が生成されます。
```
$ cat ./data_bags/credentials/aria.json
{
  "id": "aria",
  "secret": {
    "encrypted_data": "5w6+7vvIIBg6/PN+zTLNbXjpuTiJCow5LtBagvXAQSedVzjlivTpf4rp\n",
    "iv": "xGMphCdbF1qIPw6o\n",
    "auth_tag": "UzlZt58sTbQEAneViUIJtA==\n",
    "version": 3,
    "cipher": "aes-256-gcm"
  }
```

jsonの情報は以下で確認することができます。
```
$ knife data bag show credentials aria --secret-file .chef/data_bag_key --local
WARN: No cookbooks directory found at or above current directory.  Assuming /Users/tsuyoshi/git/test/hello-chef.
Encrypted data bag detected, decrypting with provided secret.
id:     aria
secret: this is my secret value
```

鍵の値を更新するには次のコマンドを実行します。
```
$ EDITOR=vim knife data bag edit credentials aria --secret-file .chef/data_bag_key --local
```

鍵情報が更新されたことを確認します。
```
$ knife data bag show credentials aria --secret-file .chef/data_bag_key --local
WARN: No cookbooks directory found at or above current directory.  Assuming /Users/tsuyoshi/git/test/hello-chef.
Encrypted data bag detected, decrypting with provided secret.
id:     aria
secret: this is my second secret value 
```

なお、レシピ内では次のようにして取得できるようです。
```
test = Chef::EncryptedDataBagItem.load('credentials', 'aria')
aaa = test['secret']
```

- 参考資料
  - https://cross-black777.hatenablog.com/entry/2016/04/27/090000
