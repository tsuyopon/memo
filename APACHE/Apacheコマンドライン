

*** ヘルプを表示する
基本的なオプションは、下記コマンドで確認することができます。
 $ /usr/sbin/httpd -h
 Usage: /usr/sbin/httpd [-D name] [-d directory] [-f file]
       [-C "directive"] [-c "directive"]
       [-k start|restart|graceful|graceful-stop|stop]
       [-v] [-V] [-h] [-l] [-L] [-t] [-T] [-S]
 
 Options:
 -D name            : define a name for use in <IfDefine name> directives
 -d directory       : specify an alternate initial ServerRoot
 -f file            : specify an alternate ServerConfigFile
 -C "directive"     : process directive before reading config files
 -c "directive"     : process directive after reading config files
 -e level           : show startup errors of level (see LogLevel)
 -E file            : log startup errors to file
 -v                 : show version number
 -V                 : show compile settings
 -h                 : list available command line options (this page)
 -l                 : list compiled in modules
 -L                 : list available configuration directives
 -t -D DUMP_VHOSTS  : show parsed settings (currently only vhost settings)
 -S                 : a synonym for -t -D DUMP_VHOSTS
 -t -D DUMP_MODULES : show all loaded modules
 -M                 : a synonym for -t -D DUMP_MODULES
 -t                 : run syntax check for config files
 -T                 : start without DocumentRoot(s) check


*** バージョンを確認する
 $ /usr/sbin/httpd -v
 Server version: Apache/2.2.17 (Unix)
 Server built:   Dec 17 2010 11:58:24

*** コンパイル設定を確認する
 $ /usr/sbin/httpd -V
 Server version: Apache/2.2.17 (Unix)
 Server built:   Dec 17 2010 11:58:24
 Server's Module Magic Number: 20051115:25
 Server loaded:  APR 1.3.12, APR-Util 1.3.9
 Compiled using: APR 1.3.12, APR-Util 1.3.9
 Architecture:   32-bit
 Server MPM:     Prefork
   threaded:     no
     forked:     yes (variable process count)
 Server compiled with....
  -D APACHE_MPM_DIR="server/mpm/prefork"
  -D APR_HAS_SENDFILE
  -D APR_HAS_MMAP
  -D APR_HAVE_IPV6 (IPv4-mapped addresses enabled)
  -D APR_USE_SYSVSEM_SERIALIZE
  -D APR_USE_PTHREAD_SERIALIZE
  -D SINGLE_LISTEN_UNSERIALIZED_ACCEPT
  -D APR_HAS_OTHER_CHILD
  -D AP_HAVE_RELIABLE_PIPED_LOGS
  -D DYNAMIC_MODULE_LIMIT=128
  -D HTTPD_ROOT="/etc/httpd"
  -D SUEXEC_BIN="/usr/sbin/suexec"
  -D DEFAULT_PIDLOG="logs/httpd.pid"
  -D DEFAULT_SCOREBOARD="logs/apache_runtime_status"
  -D DEFAULT_LOCKFILE="logs/accept.lock"
  -D DEFAULT_ERRORLOG="logs/error_log"
  -D AP_TYPES_CONFIG_FILE="conf/mime.types"
  -D SERVER_CONFIG_FILE="conf/httpd.conf"

*** 設定ファイルを読み込みsyntaxをチェックする
 $ sudo /usr/sbin/httpd -t
 Syntax OK

*** バーチャルホスト情報を表示する
 $ sudo /usr/sbin/httpd -S
 VirtualHost configuration:
 wildcard NameVirtualHosts and _default_ servers:
 _default_:443          localhost.localdomain (/etc/httpd/conf.d/ssl.conf:75)
 Syntax OK

*** モジュールを表示する
 $ sudo /usr/sbin/httpd -M
 Loaded Modules:
  core_module (static)
  mpm_prefork_module (static)
  http_module (static)
  so_module (static)
  auth_basic_module (shared)
 auth_digest_module (shared)

利用しているモードは次のようにして確認できます。
  $ /usr/local/apache2.4.23/bin/httpd -M | grep -ie prefork -ie event -ie worker
   mpm_prefork_module (static)

*** 組み込みされたモジュールのソースコード名を確認する
 $ /usr/sbin/httpd -l
 Compiled in modules:
  core.c
  prefork.c
  http_core.c
  mod_so.c


*** 利用可能なディレクティブ情報を表示する
 $ /usr/sbin/httpd -L
 <Directory (core.c)
        Container for directives affecting resources located in the specified directories
        Allowed in *.conf only outside <Directory>, <Files> or <Location>
 <Location (core.c)
        Container for directives affecting resources accessed through the specified URL paths
        Allowed in *.conf only outside <Directory>, <Files> or <Location>
 <VirtualHost (core.c)
        Container to map directives to a particular virtual host, takes one or more host addresses
        Allowed in *.conf only outside <Directory>, <Files> or <Location>
 <Files (core.c)
        Container for directives affecting files matching specified patterns
        Allowed in *.conf anywhere and in .htaccess
        when AllowOverride isn't None
 (以下省略)


