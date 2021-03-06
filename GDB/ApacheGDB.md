# 概要
このページはApacheでGDBを使いたい場合の方法などについてまとめるページです。

# 詳細
## Apacheにgdbを当てて実行する(FC17)
```
$ cat /proc/version 
Linux version 3.3.4-5.fc17.x86_64 (mockbuild@x86-14.phx2.fedoraproject.org) (gcc version 4.7.0 20120504 (Red Hat 4.7.0-4) (GCC) ) #1 SMP Mon May 7 17:29:34 UTC 2012
```

とりあえずgdbを当ててみる
```
$ gdb
(gdb) file /usr/sbin/httpd
Reading symbols from /usr/sbin/httpd...(no debugging symbols found)...done.
Missing separate debuginfos, use: debuginfo-install httpd-2.2.23-1.fc17.x86_64
```

エラーメッセージを見ると下記を実行すればデバッグ情報が入りそうな感じなので、実行する。
```
$ sudo debuginfo-install httpd-2.2.23-1.fc17.x86_64
```

複数プロセスあるとgdbでのデバッグが大変なので、停止してから起動させるようにする。
```
$ sudo apachectl stop
$ sudo gdb /usr/sbin/httpd
(gdb) b ap_process_request
(gdb) run -X 
ここでリクエストを出す
(gdb) list
(gdb) where
通常のgdbとしては問題なくソースコードが表示されていることが確認できます
```

### Apacheにgdbを当てる(Ubuntu)
Ubuntuの2.4をダウンロードした時のパッケージが以下の通り。debuginfoではなくdbgというパッケージ名になっている。
```
$ sudo apt-get install apache2 apache2-dbg
```

あとは通常どおり
```
$ gdb
(gdb) file /usr/sbin/apache2
Reading symbols from /usr/sbin/apache2...Reading symbols from /usr/lib/debug//usr/sbin/apache2...done.
done.
(gdb) b ap_process_request
Breakpoint 1 at 0x6e810: file http_request.c, line 357.
```

しかし、環境変数になっている点があってうまくいかない。
```
(gdb) run -X
Starting program: /usr/sbin/apache2 -X
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
[Tue Apr 18 08:35:37.340426 2017] [core:warn] [pid 2928] AH00111: Config variable ${APACHE_LOCK_DIR} is not defined
[Tue Apr 18 08:35:37.341482 2017] [core:warn] [pid 2928] AH00111: Config variable ${APACHE_PID_FILE} is not defined
[Tue Apr 18 08:35:37.342941 2017] [core:warn] [pid 2928] AH00111: Config variable ${APACHE_RUN_USER} is not defined
[Tue Apr 18 08:35:37.343890 2017] [core:warn] [pid 2928] AH00111: Config variable ${APACHE_RUN_GROUP} is not defined
[Tue Apr 18 08:35:37.344348 2017] [core:warn] [pid 2928] AH00111: Config variable ${APACHE_LOG_DIR} is not defined
[Tue Apr 18 08:35:37.467419 2017] [core:warn] [pid 2928:tid 140737353983872] AH00111: Config variable ${APACHE_LOG_DIR} is not defined
```

この辺に解決法が記されていた。
- https://msmania.wordpress.com/tag/apache/

174-176行目をapache2ctlに追加する
```
$ sudo vim /usr/sbin/apache2ctl 
171 fullstatus)
172     get_status
173     ;;
174 debug)
175     gdb $HTTPD
176     ;;
```

さらにgdbを実行しても次のエラーになる場合がある。
```
AH00558: apache2: Could not reliably determine the server's fully qualified domain name, using 127.0.0.1. Set the 'ServerName' directive globally to suppress this message
```

この場合次の２つのコマンドを実行すれば良い。
```
$ echo "ServerName localhost" | sudo tee /etc/apache2/conf-available/fqdn.conf
$ sudo a2enconf fqdn
```

あとは以下のコマンドで動くようになります。2.4だとworkerがデフォルトとなります。
```
$ sudo /usr/sbin/apache2ctl debug
(gdb) b ap_process_request
(gdb) run -X
```

## Apache ソースコードからコンパイルしてgdbにあてる
適当なバージョンのものを持ってきます。2.4だといろいろ大変そうだったので今回は2.2にしておきます。 
CFLAGSに-gオプションを付与しているのがポイントです。
prefork以外でコンパイルしたい場合にはconfigureのオプションとして「--with-mpm=worker」などとします。
```
$ wget http://ftp.yz.yamagata-u.ac.jp/pub/network/apache//httpd/httpd-2.2.27.tar.gz
$ tar zxvf httpd-2.2.27.tar.gz
$ cd httpd-2.2.27
$ CFLAGS="-g" ./configure --prefix=/usr/local/apache2.2
$ make
$ sudo make install
$ sudo gdb /usr/local/apache2.2/bin/httpd
GNU gdb (GDB) Fedora (7.4.50.20120120-54.fc17)
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from /usr/local/apache2.2/bin/httpd...done.
(gdb) b ap_process_request_internal                     // 適当な関数を選択
Breakpoint 1 at 0x43989d: file request.c, line 104.
(gdb) run -X                                            // 1プロセスのみ起動したいので-Xを付与する。ファイルも指定したい場合には  -f <filepath> とすればOK
Starting program: /usr/local/apache2.2/bin/httpd -X
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".
```

(プロンプトから応答がかえってこないですが、ブラウザからapacheをたたくと以下の行が出力されます) 
 
```
Breakpoint 1, ap_process_request_internal (r=0x7afbf0) at request.c:104
104	    int file_req = (r->main && r->filename);
Missing separate debuginfos, use: debuginfo-install apr-1.4.6-1.fc17.x86_64 apr-util-1.4.1-2.fc17.x86_64 db4-4.8.30-10.fc17.x86_64 expat-2.1.0-3.1.fc17.x86_64 glibc-2.15-58.fc17.x86_64 libuuid-2.21.1-1.fc17.x86_64 nss-softokn-freebl-3.14.3-1.fc17.x86_64
(gdb) p *r
$1 = {pool = 0x7afb78, connection = 0x7abdc0, server = 0x6be148, next = 0x0, prev = 0x0, main = 0x0, 
  the_request = 0x7b1190 "GET / HTTP/1.1", assbackwards = 0, proxyreq = 0, header_only = 0, protocol = 0x7b1200 "HTTP/1.1", 
  proto_num = 1001, hostname = 0x7b15f8 "localhost", request_time = 1403571888584841, status_line = 0x0, status = 200, 
  method = 0x7b11e0 "GET", method_number = 0, allowed = 0, allowed_xmethods = 0x0, allowed_methods = 0x7afe90, 
  sent_bodyct = 0, bytes_sent = 0, mtime = 0, chunked = 0, range = 0x0, clength = 0, remaining = 0, read_length = 0, 
  read_body = 0, read_chunked = 0, expecting_100 = 0, headers_in = 0x7afed0, headers_out = 0x7b05d0, 
  err_headers_out = 0x7b0818, subprocess_env = 0x7b0250, notes = 0x7b09b8, content_type = 0x0, handler = 0x0, 
  content_encoding = 0x0, content_languages = 0x0, vlist_validator = 0x0, user = 0x0, ap_auth_type = 0x0, no_cache = 0, 
  no_local_copy = 0, unparsed_uri = 0x7b11f0 "/", uri = 0x7b11f8 "/", filename = 0x0, canonical_filename = 0x0, 
  path_info = 0x0, args = 0x0, finfo = {pool = 0x0, valid = 0, protection = 0, filetype = APR_NOFILE, user = 0, group = 0, 
    inode = 0, device = 0, nlink = 0, size = 0, csize = 0, atime = 0, mtime = 0, ctime = 0, fname = 0x0, name = 0x0, 
    filehand = 0x0}, parsed_uri = {scheme = 0x0, hostinfo = 0x0, user = 0x0, password = 0x0, hostname = 0x0, 
    port_str = 0x7b1611 "8080", path = 0x7b11f8 "/", query = 0x0, fragment = 0x0, hostent = 0x0, port = 8080, 
    is_initialized = 1, dns_looked_up = 0, dns_resolved = 0}, used_path_info = 2, per_dir_config = 0x6c2670, 
  request_config = 0x7b0b58, htaccess = 0x0, output_filters = 0x7b10b0, input_filters = 0x7b1618, 
  proto_output_filters = 0x7b10b0, proto_input_filters = 0x7b1618, eos_sent = 0}
(gdb) set print pretty on        // 出力をきれいに整形します
(gdb) p *(r->connection)         // connection構造体を出力してみます。
$4 = {
  pool = 0x7abb58, 
  base_server = 0x6be148, 
  vhost_lookup_data = 0x0, 
  local_addr = 0x7abc20, 
  remote_addr = 0x7abce0, 
  remote_ip = 0x7ac510 "10.0.2.2", 
  remote_host = 0x0, 
  remote_logname = 0x0, 
  aborted = 0, 
  keepalive = AP_CONN_UNKNOWN, 
  double_reverse = 0, 
  keepalives = 0, 
  local_ip = 0x7ac4e0 "10.0.2.15", 
  local_host = 0x0, 
  id = 0, 
  conn_config = 0x7abe68, 
  notes = 0x7ac340, 
  input_filters = 0x7ac560, 
  output_filters = 0x7ac588, 
  sbh = 0x7a9bc0, 
  bucket_alloc = 0x7adb68, 
  cs = 0x0, 
  data_in_input_filters = 0, 
  clogging_input_filters = 0
}
(gdb) p *(r->connection->base_server)
$5 = {
  process = 0x6b7218, 
  next = 0x0, 
  defn_name = 0x0, 
  defn_line_number = 0, 
  server_admin = 0x759360 "you@example.com", 
  server_hostname = 0x6e63e8 "localhost.localdomain", 
  port = 0, 
  error_fname = 0x6e4540 "logs/error_log", 
  error_log = 0x6b71a0, 
  loglevel = 4, 
  is_virtual = 0, 
  module_config = 0x6be368, 
  lookup_defaults = 0x6c2670, 
  addrs = 0x6be278, 
  timeout = 300000000, 
  keep_alive_timeout = 5000000, 
  keep_alive_max = 100, 
  keep_alive = 1, 
  path = 0x0, 
  pathlen = 0, 
  names = 0x0, 
  wild_names = 0x0, 
  limit_req_line = 8190, 
  limit_req_fieldsize = 8190, 
  limit_req_fields = 100, 
  server_scheme = 0x0
}
(gdb) bt                      // 現在いる時点までのバックとレースが出力されます
#0  ap_process_request_internal (r=0x7afbf0) at request.c:104
#1  0x00000000004620d6 in ap_process_request (r=0x7afbf0) at http_request.c:280
#2  0x000000000045efd3 in ap_process_http_connection (c=0x7abdc0) at http_core.c:190
#3  0x0000000000449395 in ap_run_process_connection (c=0x7abdc0) at connection.c:43
#4  0x000000000044982b in ap_process_connection (c=0x7abdc0, csd=0x7abbd0) at connection.c:190
#5  0x000000000047d13e in child_main (child_num_arg=0) at prefork.c:667
#6  0x000000000047d235 in make_child (s=0x6be148, slot=0) at prefork.c:712
#7  0x000000000047d7ed in ap_mpm_run (_pconf=0x6b9138, plog=0x6fb348, s=0x6be148) at prefork.c:988
#8  0x00000000004260bf in main (argc=2, argv=0x7fffffffe4e8) at main.c:753
```

## 起動中のプロセスからPIDを指定してgdbにあてる場合

あらかじめ調査したいpidを押さえておきます
```
$ ps aux | grep -i httpd
$ gdb
(gdb) file /usr/sbin/httpd
(gdb) attach <pid>
(gdb) break ap_process_request
(gdb) continue
```

## コアファイルからApacheのgdbにあてる場合
まずcoreファイルはどのように生成するかというと(apacheに限ったものではない) 
 
### (1) gcoreからpidを指定して生成する
```
$ gcore <pid>
```

### (2) gdbから生成する
```
$ gdb
(gdb) attach <pid>
(gdb) gcore core
(gdb) detach
$ ls -alt ./core
```

### (3) CoreDumpDirectoryディレクティブで吐かせる
```
CoreDumpDirectory /tmp
```
などをconfに加えて再起動する 
参考: [http://sarface2012.hatenablog.com/entries/2010/10/27]

これのcoreを利用すると以下のようにして原因箇所の特定ができるようです。
```
$ sudo gdb /usr/sbin/httpd core
(gdb) where
(gdb) bt
(gdb) bt full
```

またはこんな感じでもいけると思う
```
$ sudo gdb
(gdb) file /usr/sbin/httpd
(gdb) core-file core          // 適切なコアファイル名を入力する
(gdb) bt
```

### 全てのhookにブレークポイントを貼る
以下を実行して全てのap_run_xxxにフックを貼ることが可能
```
(gdb) rbreak ap_run_*
```

### apacheの.gdbinitを使う
httpd-2.4.xxのディレクトリ直下に移動して.gdbinitを読み込ませる。
```
(gdb) source ./.gdbinit
(gdb) dump_table r->headers_in
[0] 'User-Agent'='curl/7.24.0 (x86_64-redhat-linux-gnu) libcurl/7.24.0 NSS/3.13.5.0 zlib/1.2.5 libidn/1.24 libssh2/1.4.1' [0x723264]
[1] 'Host'='localhost:8080' [0x7232d6]
[2] 'Accept'='*/*' [0x7232f0]
[3] 'Content-Length'='9' [0x723308]
[4] 'Content-Type'='application/x-www-form-urlencoded' [0x72331e]
```

```
(gdb) dump_string_array r->headers_in
[0] 'User-Agent'
[1] 'curl/7.24.0 (x86_64-redhat-linux-gnu) libcurl/7.24.0 NSS/3.13.5.0 zlib/1.2.5 libidn/1.24 libssh2/1.4.1'
[2Cannot access memory at address 0x55534552
```

```
(gdb) dump_brigade bb 
dump of brigade 0x7283d0
   | type     (address)    | length | data addr  | contents               | rc
--------------------------------------------------------------------------------
 0 | FILE     (0x0071fca8) | 45     | 0x0071fe88 | [**unknown**]          | n/a
 1 | EOS      (0x0071fd48) | 0      | 0x00000000 |                        | n/a
```

- 参考URL
  - https://httpd.apache.org/dev/debugging.html
  - http://events.linuxfoundation.org/sites/events/files/slides/AC2014-Debug.pdf
  - http://www.myiphoneadventure.com/linux-2/debugging-apache-modules-in-linux-with-gdbddd
  - http://prefetch.net/articles/debuggingapache.html
  - https://ja.scribd.com/document/83753710/Apache-Presentation

## TIPS
### gdbでapacheのrequest_rec構造体の内容を表示したい
```
request_rec構造体は以下のように出力します。
(gdb) set print pretty on   // 整形します
(gdb) p *r
```

### フックまでわかっているばあい
gdbでフックの箇所までわかっている場合には、そのフック関数でブレークポイントを貼って、
ブレークポイントに到達したらstep実行するとどのモジュールでエラーになっているのかまで追うことができます。

### voidの値を表示する。

今回チェックするデータは次の通り
```
static void *merge_core_dir_configs(apr_pool_t *a, void *basev, void *newv)
```

newvのデータを見たく、データに入ってくる値がわかっている場合には正しく型を指定すると表示できる。
```
Breakpoint 1, merge_core_dir_configs (a=0x729cb8, basev=0x6e4fd0, newv=0x72b638) at core.c:201
201	in core.c
(gdb) p *newv
Attempt to dereference a generic pointer.
(gdb) p newv
$4 = (void *) 0x72b638
 (gdb) p *(core_dir_config *)0x72b638
$7 = {d = 0x703e10 "/usr/local/apache2.4.23/htdocs/", d_components = 5, opts = 5 '\005', opts_add = 0 '\000', opts_remove = 0 '\000', override = 0, 
  override_opts = 255 '\377', response_code_strings = 0x0, hostname_lookups = 3, content_md5 = 2, use_canonical_name = 3, d_is_fnmatch = 0, 
  add_default_charset = 2, add_default_charset_name = 0x487f6d "iso-8859-1", limit_cpu = 0x0, limit_mem = 0x0, limit_nproc = 0x0, limit_req_body = -1, 
  limit_xml_body = -1, server_signature = srv_sig_unset, sec_file = 0x0, sec_if = 0x0, r = 0x0, mime_type = 0x0, handler = 0x0, output_filters = 0x0, 
  input_filters = 0x0, accept_path_info = 3, etag_bits = 0, etag_add = 0, etag_remove = 0, enable_mmap = 2, enable_sendfile = 2, 
  use_canonical_phys_port = 2, allow_encoded_slashes = 0, decode_encoded_slashes = 0, condition_ifelse = 0, condition = 0x0, log = 0x0, override_list = 0x0, 
  max_ranges = -1, max_overlaps = -1, max_reversals = -1, refs = 0x0, response_code_exprs = 0x0, cgi_pass_auth = 2, qualify_redirect_url = 2, 
  expr_handler = 0x0, cgi_var_rules = 0x0}
```
^上記内容はgdb.mdにも重複転載

# 参考
- Apacheモジュールの作成とgdbとloggerでのデバッグ方法
  - http://d.hatena.ne.jp/yone098/20090518/1242703019
- Apache Debugging Guide
  - https://httpd.apache.org/dev/debugging.html

