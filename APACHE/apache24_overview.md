# 概要 
apache2.4

### prefork overview

作業途中...
```
main
	ap_run_rewrite_args
	ap_run_pre_config
	ap_run_check_config
	ap_run_test_config
	ap_run_mpm
		prefork_run               // shutdownやgraceful処理はここで行うが細かいところは省略
			ap_run_pre_mpm
			make_child
				fork
				child_main
					ap_run_drop_privileges
					ap_run_child_init
					while(しぬまで){
						ap_unixd_accept
							apr_socket_accept
								accept4              // wait
						ap_run_create_connection
						ap_process_connection
							ap_run_pre_connection
								ap_run_process_connection
					}

			startup_children

```
