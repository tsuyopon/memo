# 概要
Apacheの主要な構造体の情報がたまに知りたいことがあるので、簡単なダンプデータを載せておきます。
この結果は、Apache2.4.23のソースコードを元にしています。
```
(gdb) where
#0  ap_die_r (type=0, r=0x721cf0, recursive_error=200) at http_request.c:83
#1  0x000000000047778d in ap_process_async_request (r=0x721cf0) at http_request.c:433
#2  0x00000000004777c4 in ap_process_request (r=0x721cf0) at http_request.c:445
#3  0x0000000000473167 in ap_process_http_sync_connection (c=0x71dec0) at http_core.c:210
#4  0x0000000000473275 in ap_process_http_connection (c=0x71dec0) at http_core.c:251
#5  0x0000000000467849 in ap_run_process_connection (c=0x71dec0) at connection.c:42
#6  0x0000000000467edd in ap_process_connection (c=0x71dec0, csd=0x71dcd0) at connection.c:226
#7  0x0000000000481d78 in child_main (child_num_arg=0, child_bucket=0) at prefork.c:723
#8  0x0000000000481ea9 in make_child (s=0x6da5c8, slot=0, bucket=0) at prefork.c:767
#9  0x0000000000482534 in prefork_run (_pconf=0x6b1138, plog=0x6de378, s=0x6da5c8) at prefork.c:979
#10 0x0000000000434270 in ap_run_mpm (pconf=0x6b1138, plog=0x6de378, s=0x6da5c8) at mpm_common.c:96
#11 0x000000000042c027 in main (argc=2, argv=0x7fffffffe4f8) at main.c:783
```

# 詳細

### request_rec
リクエストに関する情報が含まれる。  
server_rec, conn_rec, apr_pool_tなどの情報にはrequest_rec構造体経由でアクセスすることができる。
```
$31 = {
  pool = 0x721c78, 
  connection = 0x71dec0, 
  server = 0x6da5c8, 
  next = 0x0, 
  prev = 0x0, 
  main = 0x0, 
  the_request = 0x723210 "POST / HTTP/1.1", 
  assbackwards = 0, 
  proxyreq = 0, 
  header_only = 0, 
  proto_num = 1001, 
  protocol = 0x723248 "HTTP/1.1", 
  hostname = 0x7233a0 "localhost", 
  request_time = 1480731853030120, 
  status_line = 0x492e9c "200 OK", 
  status = 200, 
  method_number = 2, 
  method = 0x723228 "POST", 
  allowed = 0, 
  allowed_xmethods = 0x0, 
  allowed_methods = 0x721fc8, 
  sent_bodyct = 1, 
  bytes_sent = 45, 
  mtime = 1181587994000000, 
  range = 0x0, 
  clength = 45, 
  chunked = 0, 
  read_body = 0, 
  read_chunked = 0, 
  expecting_100 = 0, 
  kept_body = 0x0, 
  body_table = 0x0, 
  remaining = 0, 
  read_length = 0, 
  headers_in = 0x722008, 
  headers_out = 0x723ad8, 
  err_headers_out = 0x727ca8, 
  subprocess_env = 0x727ef8, 
  notes = 0x7239b0, 
  content_type = 0x704e48 "text/html", 
  handler = 0x0, 
  content_encoding = 0x0, 
  content_languages = 0x0, 
  vlist_validator = 0x0, 
  user = 0x0, 
  ap_auth_type = 0x0, 
  unparsed_uri = 0x723238 "/", 
  uri = 0x7270c0 "/index.html", 
  filename = 0x727100 "/usr/local/apache2.4.23/htdocs/index.html", 
  canonical_filename = 0x7270d0 "/usr/local/apache2.4.23/htdocs/index.html", 
  path_info = 0x0, 
  args = 0x0, 
  used_path_info = 2, 
  eos_sent = 1, 
  per_dir_config = 0x723720, 
  request_config = 0x722fd0, 
  log = 0x6da5e8, 
  log_id = 0x0, 
  htaccess = 0x0, 
  output_filters = 0x723158, 
  input_filters = 0x7233c0, 
  proto_output_filters = 0x723158, 
  proto_input_filters = 0x7233c0, 
  no_cache = 0, 
  no_local_copy = 0, 
  invoke_mtx = 0x7233e8, 
  parsed_uri = {
    scheme = 0x0, 
    hostinfo = 0x0, 
    user = 0x0, 
    password = 0x0, 
    hostname = 0x0, 
    port_str = 0x7233b9 "8080", 
    path = 0x723240 "/", 
    query = 0x0, 
    fragment = 0x0, 
    hostent = 0x0, 
    port = 8080, 
    is_initialized = 1, 
    dns_looked_up = 0, 
    dns_resolved = 0
  }, 
  finfo = {
    pool = 0x725c98, 
    valid = 7598960, 
    protection = 1604, 
    filetype = APR_REG, 
        user = 0, 
    group = 0, 
    inode = 198790, 
    device = 64769, 
    nlink = 1, 
    size = 45, 
    csize = 4096, 
    atime = 1480262792855609, 
    mtime = 1181587994000000, 
    ctime = 1474597625861167, 
    fname = 0x727100 "/usr/local/apache2.4.23/htdocs/index.html", 
    name = 0x0, 
    filehand = 0x0
  }, 
  useragent_addr = 0x71dde0, 
  useragent_ip = 0x71e220 "127.0.0.1", 
  trailers_in = 0x722388, 
  trailers_out = 0x727dd0, 
  useragent_host = 0x0, 
  double_reverse = 0
}
```


### server_rec
VirtualHostに関する情報が入ると思われる。
```
(gdb) p r.server
$32 = (server_rec *) 0x6da5c8
(gdb) p *r.server
$30 = {
  process = 0x6af218, 
  next = 0x0, 
  error_fname = 0x6fe1c0 "logs/error_log", 
  error_log = 0x6af1a0, 
  log = {
    module_levels = 0x0, 
    level = 4
  }, 
  module_config = 0x6da8b0, 
  lookup_defaults = 0x6e47a8, 
  defn_name = 0x0, 
  defn_line_number = 0, 
  is_virtual = 0 '\000', 
  port = 0, 
  server_scheme = 0x0, 
  server_admin = 0x7039d8 "you@example.com", 
  server_hostname = 0x6ff580 "localhost.localdomain", 
  addrs = 0x6da700, 
  timeout = 60000000, 
  keep_alive_timeout = 5000000, 
  keep_alive_max = 100, 
  keep_alive = 1, 
  names = 0x0, 
  wild_names = 0x0, 
  path = 0x0, 
  pathlen = 0, 
  limit_req_line = 8190, 
  limit_req_fieldsize = 8190, 
  limit_req_fields = 100, 
  context = 0x0, 
  keep_alive_timeout_set = 0
}
```

### conn_rec
接続先に関する情報を保存しておくための構造体です。
```
(gdb) p r.connection
$40 = (conn_rec *) 0x71dec0
(gdb) p *r.connection
$41 = {
  pool = 0x71dc58, 
  base_server = 0x6da5c8, 
  vhost_lookup_data = 0x0, 
  local_addr = 0x71dd20, 
  client_addr = 0x71dde0, 
  client_ip = 0x71e220 "127.0.0.1", 
  remote_host = 0x0, 
  remote_logname = 0x0, 
  local_ip = 0x71e1f0 "127.0.0.1", 
  local_host = 0x0, 
  id = 0, 
  conn_config = 0x71df88, 
  notes = 0x71e050, 
  input_filters = 0x71e328, 
  output_filters = 0x71e300, 
  sbh = 0x71bce8, 
  bucket_alloc = 0x71fc68, 
  cs = 0x0, 
  data_in_input_filters = 0, 
  data_in_output_filters = 1, 
  clogging_input_filters = 0, 
  double_reverse = 0, 
  aborted = 0, 
  keepalive = AP_CONN_KEEPALIVE, 
  keepalives = 1, 
  log = 0x0, 
  log_id = 0x0, 
  current_thread = 0x71bcc0, 
  master = 0x0
}
```

### apr_pool_t
```
(gdb) p r.pool
$35 = (apr_pool_t *) 0x721c78
(gdb) p *r.pool
$36 = {
  parent = 0x71dc58, 
  child = 0x725c98, 
  sibling = 0x0, 
  ref = 0x729cc8, 
  cleanups = 0x728290, 
  free_cleanups = 0x0, 
  allocator = 0x71b0e0, 
  subprocesses = 0x0, 
  abort_fn = 0x42a6ae <abort_on_oom>, 
  user_data = 0x0, 
  tag = 0x487955 "request", 
  active = 0x727c80, 
  self = 0x721c50, 
  self_first_avail = 0x721cf0 "x\034r", 
  pre_cleanups = 0x0
}
```

# TODO
- 他のデータもダンプしておきたい。
- データ構造などについてちゃんとまとめておきたい

# まとめ
- server_rec, conn_rec, apr_pool_tなどの情報にはrequest_rec構造体経由でアクセスすることができる。
- 今後参考になりそうなダンプ情報を取得することができたので何かのときの参考程度になる資料として作成した

