# apxsコマンド
apxsは、APache eXtenSionの略称です。apxsコマンドを利用して以下の処理を行うことができます。
- モジュールのコンパイルとロード
- モジュール作成の際のスケルトン生成

##  詳細
### apxsを利用した動的モジュール(DSO:Dynamic Shared Object)の管理
- apxsでモジュールをコンパイルするには-cを付加する
```
#apxs -c mod_foo.c
```
- apxsでコンパイルと同時にインストールする場合には-iを付加する
```
#apxs -ic mod_foo.c
```
- DSOモジュールの格納場所は以下の様にする亊により表示される
```
#apxs -q LIBEXECDIR
```
- 設定ファイル(httpd.conf)へのLoadModuleディレクティブの追加は以下の様にする
```
#apxs -a mod_foo.c
```

### apxsを利用してモジュールの作成を行う
以下の様にしてapxsコマンドを利用すれば簡単に雛形を作成することができます。
```
$ /usr/sbin/apxs -n test -g
Creating [DIR]  test
Creating [FILE] test/Makefile
Creating [FILE] test/modules.mk
Creating [FILE] test/mod_test.c
Creating [FILE] test/.deps
```

続いて、スケルトン生成直後にコンパイルを行います。
```
$ cd test
$ make
apxs -c    mod_test.c
gcc -DLINUX=22 -DEAPI -DTARGET="apache" -DHAVE_SET_DUMPABLE -DDB_DBM_HSEARCH=1 -DDEV_RANDOM=/dev/random -DUSE_HSREGEX -O1  -g -Wall -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -fPIC -DSHARED_MODULE -I/usr/include/apache-1.3  -c mod_test.c
gcc -shared -o mod_test.so mod_test.o
```

makeコマンドによりコンパイルが完了したらインストールを行います。make installを実行します。
```
$ sudo make install
make[1]: ディレクトリ `/home/tsuyoshi/work/apacheapi/test' に入ります
/usr/lib/apr-1/build/libtool --silent --mode=install cp mod_test.la /usr/lib/httpd/modules/
make[1]: ディレクトリ `/home/tsuyoshi/work/apacheapi/test' から出ます
/usr/lib/apr-1/build/libtool --silent --mode=install cp mod_test.la /usr/lib/httpd/modules/
```

「make install」により、LoadModuleがhttpd.confに記述されていますので確認します。
```
$ cat /etc/httpd/conf/httpd.conf | grep -i mod_test
LoadModule test_module        /usr/lib/httpd/modules/mod_test.so
```

続いて、mod_testハンドラを読み込むように下記設定を加えます。
```
$ sudo vim /etc/httpd/conf/httpd.conf
<Location "/test/">
   SetHandler test
</Location>
```

apacheの設定を変更したので再起動しておきます。
```
$ sudo /usr/sbin/apachectl restart
```

以上により、下記ページにアクセスすると「The sample page from mod_test.c 」という文言が表示されるようになれれば成功です。
```
http://<IP or Domain>/test/
```

## 参考URL
- DSAS開発者の部屋 apache module 開発事始め 
  - http://dsas.blog.klab.org/archives/50574774.html
- apacheモジュール作成のまとめ
  - http://d.hatena.ne.jp/yoshifumi1975/20080429/p1


# Apache 1.3系ハンドラ作成
Apache1.3系では、handler関数を実装し、module定義用の構造体にその関数を登録します。

## 詳細
### main処理部分
リクエスト処理メインフローは以下の関数で定められます
```
static void process_request_internal(request_rec *r);
```


### request_rec構造体について
request_recは構造体で、moduleやhandlerが処理を行う上で、以下の理由から利用されます。
- 現在のリクエスト情報を保持する
- リクエストを処理するために必要な情報を保持する
- レスポンス情報を保持する構造体でリクエスト毎に生成される。


## 参考URL
- Apache 1.3 API notes(English&Japanese)
  - http://httpd.apache.org/docs/1.3/misc/API.html
  - http://japache.infoscience.co.jp/japanese_1_3/manual/misc/API.html
- Apache Web server 1.3 API Dictionary
  - http://httpd.apache.org/dev/apidoc/index.html


# Apache 2系ハンドラ作成

## 詳細
### HelloWorldを作成する
Apacheハンドラ(2.x系)の処理の流れについてHelloworld的なサンプルを作成してまとめます。
下記コマンドで生成されたハンドラmod_test.cをサンプルプログラムとして処理の流れを整理していきます。
```
$ /usr/sbin/apxs -n test -g
```

###  mod_test.cの内容
```
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"

/* The sample content handler */
static int test_handler(request_rec *r)
{
    if (strcmp(r->handler, "test")) {
        return DECLINED;
    }
    r->content_type = "text/html";

    if (!r->header_only)
        ap_rputs("The sample page from mod_test.c\n", r);
    return OK;
}

static void test_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(test_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA test_module = {
    STANDARD20_MODULE_STUFF,
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    test_register_hooks  /* register hooks                      */
};
```

### 処理概要
- 1. モジュール宣言AP_MODULE_DECLARE_DATAに登録されているハンドラ情報を読み込みます。
  - この中でtest_register_hooks()というメソッド名が登録されています。この関数がフック関数を呼び出します。
- 2. test_register_hooks()を呼び出します。ap_hook_handler()関数では引数として、test_handler()を呼び出すことが明記されています。
  - この呼び出し関数にはフック関数が記述されます。COLOR(red): 尚、フック関数というのはメソッド名に応じて呼び出し時のタイミングが異なるメソッドです。以下にフック関数の種類を示します。
  - (参考) http://httpd.apache.org/docs/2.2/ja/developer/modules.html
- 3. test_handler()が呼び出されます。
  - ここでは、各タイミングで実施すべき処理を記述します。以下にメソッドの処理詳細について記します。
    - 以下はリクエストに含まれる「test」という要素をチェックし、このフック関数で処理すべきかどうかをチェックします。
```
     if (strcmp(r->handler, "test")) {
         return DECLINED;
     }
```
    - 以下はレスポンス内容として指定するMIMEタイプを指定しています。
```
     r->content_type = "text/html";
```
    - 以下はヘッダのみ(「HEAD」リクエスト)の場合にはリクエストを応答しないことを意味しています。
```
     if (!r->header_only)
         ap_rputs("The sample page from mod_test.c\n", r);
```

## 参考URL
- モジュールの Apache 1.3 から Apache 2.0 への移植
  - http://httpd.apache.org/docs/2.2/ja/developer/modules.html
- Apache Moduleをつくる - モジュール宣言とフック関数
  - http://blog.livedoor.jp/matssaku/archives/50421540.html


# apache1.3系とapache2.0系のAPI比較
```
	 AP13                       AP20
	 =====================================================
	 ap_array_pstrcat           apr_array_pstrcat
	 ap_construct_url           ap_construct_url
	 ap_copy_array              apr_array_copy
	 ap_document_root           ap_document_root
	 ap_escape_html             ap_escape_html
	 ap_escape_shell_cmd        ap_escape_shell_cmd
	 ap_escape_uri              ap_escape_uri
	 ap_get_basic_auth_pw       ap_get_basic_auth_pw
	 ap_get_client_block        ap_get_client_block
	 ap_get_module_config       ap_get_module_config
	 ap_get_server_name         ap_get_server_name
	 ap_get_server_port         ap_get_server_port
	 ap_get_server_version      ap_get_server_version
	 ap_getword                 ap_getword
	 ap_getword_conf            ap_getword_conf
	 ap_getword_conf_nc         ap_getword_nc
	 ap_getword_white           ap_getword_white
	 ap_getword_white_nc        ap_getword_nc
	 ap_gm_timestr_822          apr_rfc822_date
	 ap_hard_timeout
	 ap_http_method             ap_http_method
	 ap_internal_redirect       ap_internal_redirect
	 ap_kill_timeout
	 ap_log_error               ap_log_error
	 ap_log_printf
	 ap_log_rerror              ap_log_rerror
	 ap_make_array              apr_array_make
	 ap_make_full_path          ap_make_full_path
	 ap_make_table              apr_table_make
	 ap_md5                     ap_md5
	 ap_meets_conditions        ap_meets_conditions
	 ap_note_basic_auth_failure ap_note_basic_auth_failure
	 ap_note_cleanups_for_fd
	 ap_note_cleanups_for_file
	 ap_note_cleanups_for_h
	 ap_os_dso_error            apr_dso_error
	 ap_os_dso_load             apr_dso_load
	 ap_os_dso_sym              apr_dso_sym
	 ap_os_dso_unload           apr_dso_unload
	 ap_palloc                  apr_palloc
	 ap_parseHTTPdate           apr_date_parse_http
	 ap_pbase64decode           ap_pbase64decode
	 ap_pbase64encode           ap_pbase64encode
	 ap_pcalloc                 apr_pcalloc
	 ap_pclosedir               apr_dir_close
	 ap_pclosef                 apr_file_close
	 ap_pfclose                 apr_file_close
	 ap_pfdopen
	 ap_pfopen                  apr_file_open
	 ap_popendir                apr_dir_open
	 ap_popenf                  apr_file_open
	 ap_pregcomp                ap_pregcomp
	 ap_pregsub                 ap_pregsub
	 ap_psignature              ap_psignature
	 ap_psprintf                apr_psprintf
	 ap_pstrcat                 apr_pstrcat
	 ap_pstrdup                 apr_pstrdup
	 ap_pstrndup                apr_pstrndup
	 ap_push_array              apr_array_push
	 ap_pvsprintf
	 ap_regerror                ap_regerror
	 ap_regexec                 ap_regexec
	 ap_regfree                 ap_regfree
	 ap_requires                ap_requires
	 ap_reset_timeout
	 ap_rprintf                 ap_rprintf
	 ap_rputc                   ap_rputc
	 ap_rputs                   ap_rputs
	 ap_send_fd                 ap_send_fd
	 ap_send_http_header
	 ap_server_root_relative    ap_server_root_relative
	 ap_set_content_length      ap_set_content_length
	 ap_set_etag                ap_set_etag
	 ap_set_file_slot           ap_set_file_slot
	 ap_set_last_modified       ap_set_last_modified
	 ap_set_string_slot         ap_set_string_slot
	 ap_set_string_slot_lower   ap_set_string_slot_lower
	 ap_setup_client_block
	 ap_should_client_block
	 ap_table_add               apr_table_add
	 ap_table_do                apr_table_do
	 ap_table_elts              apr_table_elts
	 ap_table_get               apr_table_get
	 ap_table_merge             apr_table_merge
	 ap_table_set               apr_table_set
	 ap_table_unset             apr_table_unset
	 ap_unescape_url            ap_unescape_url
	 ap_update_mtime            ap_update_mtime
	 -----------------------------------------------------
	 array_header               apr_array_header_t
	 cmd_parms                  cmd_parms
	 command_rec                command_rec
	 module                     module
	 regex_t                    regex_t
	 regmatch_t                 regmatch_t
	 request_rec                request_rec
	 server_rec                 server_rec
	 table                      apr_table_t
	 table_entry                apr_table_entry_t
	 uri_components             apr_uri_t
	 pool                       apr_pool_t
```

-  Sleepless geek in Seattle
  - http://d.hatena.ne.jp/yoshifumi1975/20080429/p1


