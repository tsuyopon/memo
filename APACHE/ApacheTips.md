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
