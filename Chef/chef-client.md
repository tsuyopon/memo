# 概要
chef-clientの実行方法について

# 詳細

### chef-clientを実行する
```
$ sudo chef-client
or
$ knife ssh "name:ノード名" -a 
```

### debugモードで実行する
```
$ sudo chef-client -l debug
```

### chef-zeroモードだとzを付与する。(knife.rbがlocal_mode trueでも-zが必要だった)
```
$ sudo chef-client -z
```

### configファイルを指定する
```
$ chef-client -c ~/.chef/knife.rb 
```
