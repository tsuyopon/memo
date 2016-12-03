# 概要
Apacheのコマンドラインについてまとめていくことにする。
バージョンは2.4.23を対象としています。

```
$ ls /usr/local/apache2.4.23/bin/
ab            apxs          dbmmanage     htcacheclean  htdigest      httpd         logresolve    
apachectl     checkgid      fcgistarter   htdbm         htpasswd      httxt2dbm     rotatelogs
```

# コマンド

## httpd

### 設定ファイルのsyntax checkを行う
```
$ /usr/local/apache2.4.23/bin/httpd -t
Syntax OK
```

### バージョンとビルド時刻を表示する
```
$ /usr/local/apache2.4.23/bin/httpd -v
Server version: Apache/2.4.23 (Unix)
Server built:   Sep 23 2016 11:25:51
```

### 組み込まれたモジュールを確認する。
```
$ /usr/local/apache2.4.23/bin/httpd -l
Compiled in modules:
  core.c
  mod_so.c
  http_core.c
  prefork.c
```

### 読み込まれるモジュールを表示する
-lオプションとは異なりstaticの他にDSOとしてのライブラリも表示する。  
モジュール名を表示している
```
$ /usr/local/apache2.4.23/bin/httpd -M
Loaded Modules:
 core_module (static)
 so_module (static)
 http_module (static)
 mpm_prefork_module (static)
 authn_file_module (shared)
 authn_core_module (shared)
 authz_host_module (shared)
 authz_groupfile_module (shared)
 authz_user_module (shared)
 authz_core_module (shared)
 access_compat_module (shared)
 auth_basic_module (shared)
 reqtimeout_module (shared)
 filter_module (shared)
 mime_module (shared)
 log_config_module (shared)
 env_module (shared)
 headers_module (shared)
 setenvif_module (shared)
 version_module (shared)
 unixd_module (shared)
 status_module (shared)
 autoindex_module (shared)
 dir_module (shared)
 alias_module (shared)
```

### 利用可能な設定ディレクティブを表示する
```
$ /usr/local/apache2.4.23/bin/httpd -L | head -20
<Directory (core.c)
	Container for directives affecting resources located in the specified directories
	Allowed in *.conf only outside <Directory>, <Files>, <Location>, or <If>
<Location (core.c)
	Container for directives affecting resources accessed through the specified URL paths
	Allowed in *.conf only outside <Directory>, <Files>, <Location>, or <If>
<VirtualHost (core.c)
	Container to map directives to a particular virtual host, takes one or more host addresses
	Allowed in *.conf only outside <Directory>, <Files>, <Location>, or <If>
<Files (core.c)
	Container for directives affecting files matching specified patterns
	Allowed in *.conf anywhere and in .htaccess
	when AllowOverride isn't None
<Limit (core.c)
	Container for authentication directives when accessed using specified HTTP methods
	Allowed in *.conf only inside <Directory>, <Files>, <Location>, or <If> and in .htaccess
	when AllowOverride includes AuthConfig or Limit
<LimitExcept (core.c)
	Container for authentication directives to be applied when any HTTP method other than those specified is used to access the resource
	Allowed in *.conf only inside <Directory>, <Files>, <Location>, or <If> and in .htaccess
```

### 主要設定を確認する
-Sオプションでたしか設定されているVirtualHostの一覧も出力することができたはず...(参考: http://mathtti.hatenablog.com/entry/20110911/p1)
```
$ /usr/local/apache2.4.23/bin/httpd -S
VirtualHost configuration:
ServerRoot: "/usr/local/apache2.4.23"
Main DocumentRoot: "/usr/local/apache2.4.23/htdocs"
Main ErrorLog: "/usr/local/apache2.4.23/logs/error_log"
Mutex default: dir="/usr/local/apache2.4.23/logs/" mechanism=default 
Mutex mpm-accept: using_defaults
PidFile: "/usr/local/apache2.4.23/logs/httpd.pid"
Define: DUMP_VHOSTS
Define: DUMP_RUN_CFG
User: name="daemon" id=2 not_used
Group: name="daemon" id=2 not_used
```

### コンパイル設定を確認する
```
$ sudo /usr/local/apache2.4.23/bin/httpd -V
Server version: Apache/2.4.23 (Unix)
Server built:   Sep 23 2016 11:25:51
Server's Module Magic Number: 20120211:61
Server loaded:  APR 1.5.2, APR-UTIL 1.5.4
Compiled using: APR 1.4.6, APR-UTIL 1.4.1
Architecture:   64-bit
Server MPM:     prefork
  threaded:     no
    forked:     yes (variable process count)
Server compiled with....
 -D APR_HAS_SENDFILE
 -D APR_HAS_MMAP
 -D APR_HAVE_IPV6 (IPv4-mapped addresses enabled)
 -D APR_USE_SYSVSEM_SERIALIZE
 -D APR_USE_PTHREAD_SERIALIZE
 -D SINGLE_LISTEN_UNSERIALIZED_ACCEPT
 -D APR_HAS_OTHER_CHILD
 -D AP_HAVE_RELIABLE_PIPED_LOGS
 -D DYNAMIC_MODULE_LIMIT=256
 -D HTTPD_ROOT="/usr/local/apache2.4.23"
 -D SUEXEC_BIN="/usr/local/apache2.4.23/bin/suexec"
 -D DEFAULT_PIDLOG="logs/httpd.pid"
 -D DEFAULT_SCOREBOARD="logs/apache_runtime_status"
 -D DEFAULT_ERRORLOG="logs/error_log"
 -D AP_TYPES_CONFIG_FILE="conf/mime.types"
 -D SERVER_CONFIG_FILE="conf/httpd.conf"
```

### 読み込まれたincludeファイルなどを全て表示する
以下の例は1つしかないので微妙だがincludeで読み込まれたファイルを全て表示するようだ
```
$ sudo /usr/local/apache2.4.23/bin/httpd --t -D DUMP_INCLUDES
Included configuration files:
  (*) /usr/local/apache2.4.23/conf/httpd.conf
```

### 起動時にログレベルを指定する
例えば、apachectl経由でなく、以下のようにしてhttpdを直接起動してみると次のようにdebugログれbるの出力を吐きます。
```
$ sudo /usr/local/apache2.4.23/bin/httpd -e debug
[Mon Nov 28 00:29:14.465008 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module authn_file_module from /usr/local/apache2.4.23/modules/mod_authn_file.so
[Mon Nov 28 00:29:14.466256 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module authn_core_module from /usr/local/apache2.4.23/modules/mod_authn_core.so
[Mon Nov 28 00:29:14.466953 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module authz_host_module from /usr/local/apache2.4.23/modules/mod_authz_host.so
[Mon Nov 28 00:29:14.467686 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module authz_groupfile_module from /usr/local/apache2.4.23/modules/mod_authz_groupfile.so
[Mon Nov 28 00:29:14.468227 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module authz_user_module from /usr/local/apache2.4.23/modules/mod_authz_user.so
[Mon Nov 28 00:29:14.468962 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module authz_core_module from /usr/local/apache2.4.23/modules/mod_authz_core.so
[Mon Nov 28 00:29:14.469714 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module access_compat_module from /usr/local/apache2.4.23/modules/mod_access_compat.so
[Mon Nov 28 00:29:14.470336 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module auth_basic_module from /usr/local/apache2.4.23/modules/mod_auth_basic.so
[Mon Nov 28 00:29:14.471347 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module reqtimeout_module from /usr/local/apache2.4.23/modules/mod_reqtimeout.so
[Mon Nov 28 00:29:14.472101 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module filter_module from /usr/local/apache2.4.23/modules/mod_filter.so
[Mon Nov 28 00:29:14.472758 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module mime_module from /usr/local/apache2.4.23/modules/mod_mime.so
[Mon Nov 28 00:29:14.474076 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module log_config_module from /usr/local/apache2.4.23/modules/mod_log_config.so
[Mon Nov 28 00:29:14.474729 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module env_module from /usr/local/apache2.4.23/modules/mod_env.so
[Mon Nov 28 00:29:14.475238 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module headers_module from /usr/local/apache2.4.23/modules/mod_headers.so
[Mon Nov 28 00:29:14.477259 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module setenvif_module from /usr/local/apache2.4.23/modules/mod_setenvif.so
[Mon Nov 28 00:29:14.477850 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module version_module from /usr/local/apache2.4.23/modules/mod_version.so
[Mon Nov 28 00:29:14.478907 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module unixd_module from /usr/local/apache2.4.23/modules/mod_unixd.so
[Mon Nov 28 00:29:14.479422 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module status_module from /usr/local/apache2.4.23/modules/mod_status.so
[Mon Nov 28 00:29:14.479944 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module autoindex_module from /usr/local/apache2.4.23/modules/mod_autoindex.so
[Mon Nov 28 00:29:14.480333 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module dir_module from /usr/local/apache2.4.23/modules/mod_dir.so
[Mon Nov 28 00:29:14.480579 2016] [so:debug] [pid 2619] mod_so.c(266): AH01575: loaded module alias_module from /usr/local/apache2.4.23/modules/mod_alias.so
```

### デバッグ用
gdbなどをする場合におなじみの1プロセス、1worker用のオプションです。
```
$ sudo /usr/local/apache2.4.23/bin/httpd -X
```

### その他のオプション
実際に試していないのでヘルプに出てくる文言を載せる程度にとどめる。
```
  -D name            : define a name for use in <IfDefine name> directives
  -d directory       : specify an alternate initial ServerRoot
  -f file            : specify an alternate ServerConfigFile
  -C "directive"     : process directive before reading config files
  -c "directive"     : process directive after reading config files
  -e level           : show startup errors of level (see LogLevel)
  -E file            : log startup errors to file
  -T                 : start without DocumentRoot(s) check
```
