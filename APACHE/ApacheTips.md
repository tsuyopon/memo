# 概要
Apacheに関してのTIPSなど

# 詳細
### ファイルの中でフックしている処理を表示する。
ある環境変数をセットするとファイルでフックしている処理一覧を表示してくれるようです。
http://d.hatena.ne.jp/Ewigkeit/20090407/1239079281

```
$ sudo -u bash
$ SHOW_HOOKS="1"
$ export SHOW_HOOKS
# /usr/local/apache2/bin/apachectl restart
Registering hooks for core.c
  Hooked create_connection
  Hooked pre_connection
  Hooked post_config
  Hooked translate_name
  Hooked map_to_storage
  Hooked open_logs
  Hooked child_init
  Hooked handler
  Hooked type_checker
  Hooked fixups
  Hooked access_checker
  Hooked create_request
  Hooked create_req
  Hooked pre_mpm
  Hooked insert_filter
Registering hooks for mod_authn_file.c
Registering hooks for mod_authn_default.c
  Hooked check_user_id
```

### Apache2ファイルレイアウト
```
/etc/apache2/
  +- sites-available/ 
  +- sites-enabled/   
  +- mods-available/  利用可能な追加モジュール設定ファイルのあるフォルダ
  +- mods-enabled/    利用する設定のシンボリックリンクが置かれるフォルダ
  +- conf.d/          apache2.confによってこの中の設定ファイルが読み込まれる
  +- apache2.conf     デフォルトの設定、ApacheのユーザーとかListenPort etc...
  +- httpd.conf       なんかいじる時はここに書けってことか？
  +- ports.conf       
  +- envvars
```

### apacheで子プロセスのリソース制限を行う
apache2.0では以下のディレクティブを設定することでサーバリソースを制限できます。
但し、apacheからforkされたものに限るため、mod_perl,mod_phpでは無効です。

- CPU占有時間を60秒に設定
  - RLimitCPU 60 
- メモリ使用量を30Mbytes（30×1024×1034）に設定
  - RLimitMEM 31457280 
- 起動されたプロセスがさらに起動可能なプロセス数の上限を10に設定
  - RLimitNPROC 10
