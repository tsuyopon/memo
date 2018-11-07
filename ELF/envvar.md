# 概要
ELFで定義している環境変数などについて
以下のドキュメントで記載されているものについて実際にどのような出力内容になるのかの視点でまとめる。
- https://linuxjm.osdn.jp/html/LDP_man-pages/man8/ld.so.8.html

# 詳細

## LD_DEBUGを利用する

### help
helpを指定するとhelpページを表示します。 LD_DEBUG=libs,relocのようにして複数指定することも可能です。
```
$ LD_DEBUG=help /bin/ls
Valid options for the LD_DEBUG environment variable are:

  libs        display library search paths
  reloc       display relocation processing
  files       display progress for input file
  symbols     display symbol table processing
  bindings    display information about symbol binding
  versions    display version dependencies
  scopes      display scope information
  all         all previous options combined
  statistics  display relocation statistics
  unused      determined unused DSOs
  help        display this help message and exit

To direct the debugging output into a file instead of standard output
a filename can be specified using the LD_DEBUG_OUTPUT environment variable.
```

### libs
```
$ LD_DEBUG=libs /bin/ls
      2010:	find library=libselinux.so.1 [0]; searching
      2010:	 search cache=/etc/ld.so.cache
      2010:	  trying file=/lib64/libselinux.so.1
      2010:	
      2010:	find library=libcap.so.2 [0]; searching
      2010:	 search cache=/etc/ld.so.cache
      2010:	  trying file=/lib64/libcap.so.2
      2010:	
      2010:	find library=libacl.so.1 [0]; searching
      2010:	 search cache=/etc/ld.so.cache
      2010:	  trying file=/lib64/libacl.so.1
      2010:	
      2010:	find library=libc.so.6 [0]; searching
      2010:	 search cache=/etc/ld.so.cache
      2010:	  trying file=/lib64/libc.so.6
     (snip)
```

### reloc
```
$ LD_DEBUG=reloc /bin/ls
      2013:	
      2013:	relocation processing: /lib64/libc.so.6
      2013:	
      2013:	relocation processing: /lib64/libpthread.so.0 (lazy)
      2013:	
      2013:	relocation processing: /lib64/libattr.so.1 (lazy)
      2013:	
      2013:	relocation processing: /lib64/libdl.so.2 (lazy)
      2013:	
      2013:	relocation processing: /lib64/libpcre.so.1 (lazy)
      2013:	
      2013:	relocation processing: /lib64/libacl.so.1 (lazy)
      2013:	
     (snip)
```

### files
```
$ LD_DEBUG=files /bin/ls
      2015:	
      2015:	file=libselinux.so.1 [0];  needed by /bin/ls [0]
      2015:	file=libselinux.so.1 [0];  generating link map
      2015:	  dynamic: 0x00007fdd2e345d48  base: 0x00007fdd2e122000   size: 0x0000000000226970
      2015:	    entry: 0x00007fdd2e128ac0  phdr: 0x00007fdd2e122040  phnum:                  8
      2015:	
      2015:	
      2015:	file=libcap.so.2 [0];  needed by /bin/ls [0]
      2015:	file=libcap.so.2 [0];  generating link map
      2015:	  dynamic: 0x00007fdd2e120df0  base: 0x00007fdd2df1d000   size: 0x0000000000204240
      2015:	    entry: 0x00007fdd2df1e620  phdr: 0x00007fdd2df1d040  phnum:                  7
      2015:	
(snip)
      2015:	calling init: /lib64/libacl.so.1
      2015:	
      2015:	
      2015:	calling init: /lib64/libcap.so.2
      2015:	
      2015:	
      2015:	calling init: /lib64/libselinux.so.1
      2015:	
      2015:	
      2015:	initialize program: /bin/ls
      2015:	
      2015:	
      2015:	transferring control: /bin/ls
      2015:	
```

### symbols
```
$ LD_DEBUG=symbols /bin/ls
      2018:	symbol=_res;  lookup in file=/bin/ls [0]
      2018:	symbol=_res;  lookup in file=/lib64/libselinux.so.1 [0]
      2018:	symbol=_res;  lookup in file=/lib64/libcap.so.2 [0]
      2018:	symbol=_res;  lookup in file=/lib64/libacl.so.1 [0]
      2018:	symbol=_res;  lookup in file=/lib64/libc.so.6 [0]
      2018:	symbol=stderr;  lookup in file=/bin/ls [0]
      2018:	symbol=stderr;  lookup in file=/lib64/libselinux.so.1 [0]
      2018:	symbol=stderr;  lookup in file=/lib64/libcap.so.2 [0]
      2018:	symbol=stderr;  lookup in file=/lib64/libacl.so.1 [0]
      2018:	symbol=stderr;  lookup in file=/lib64/libc.so.6 [0]
      2018:	symbol=error_one_per_line;  lookup in file=/bin/ls [0]
      2018:	symbol=error_one_per_line;  lookup in file=/lib64/libselinux.so.1 [0]
      2018:	symbol=error_one_per_line;  lookup in file=/lib64/libcap.so.2 [0]
      2018:	symbol=error_one_per_line;  lookup in file=/lib64/libacl.so.1 [0]
      2018:	symbol=error_one_per_line;  lookup in file=/lib64/libc.so.6 [0]
(snip)
```

### bindings
```
$ LD_DEBUG=bindings /bin/ls
      2021:	binding file /lib64/libc.so.6 [0] to /lib64/libc.so.6 [0]: normal symbol `_res' [GLIBC_2.2.5]
      2021:	binding file /lib64/libc.so.6 [0] to /lib64/libc.so.6 [0]: normal symbol `stderr' [GLIBC_2.2.5]
      2021:	binding file /lib64/libc.so.6 [0] to /lib64/libc.so.6 [0]: normal symbol `error_one_per_line' [GLIBC_2.2.5]
      2021:	binding file /lib64/libc.so.6 [0] to /lib64/libc.so.6 [0]: normal symbol `__malloc_initialize_hook' [GLIBC_2.2.5]
      2021:	binding file /lib64/libc.so.6 [0] to /lib64/ld-linux-x86-64.so.2 [0]: normal symbol `_dl_starting_up' [GLIBC_PRIVATE]
      2021:	binding file /lib64/libc.so.6 [0] to /lib64/libc.so.6 [0]: normal symbol `__morecore' [GLIBC_2.2.5]
      2021:	binding file /lib64/libc.so.6 [0] to /lib64/libc.so.6 [0]: normal symbol `__key_encryptsession_pk_LOCAL' [GLIBC_2.2.5]
      2021:	binding file /lib64/libc.so.6 [0] to /lib64/libc.so.6 [0]: normal symbol `__progname_full' [GLIBC_2.2.5]
      2021:	binding file /lib64/libc.so.6 [0] to /lib64/libc.so.6 [0]: normal symbol `__ctype32_tolower' [GLIBC_2.2.5]
      2021:	binding file /lib64/libc.so.6 [0] to /lib64/libc.so.6 [0]: normal symbol `_environ' [GLIBC_2.2.5]
      2021:	binding file /lib64/libc.so.6 [0] to /lib64/ld-linux-x86-64.so.2 [0]: normal symbol `_rtld_global' [GLIBC_PRIVATE]
(snip)
```

### versions
```
$ LD_DEBUG=versions /bin/ls
      2026:	checking for version `ACL_1.0' in file /lib64/libacl.so.1 [0] required by file /bin/ls [0]
      2026:	checking for version `GLIBC_2.14' in file /lib64/libc.so.6 [0] required by file /bin/ls [0]
      2026:	checking for version `GLIBC_2.4' in file /lib64/libc.so.6 [0] required by file /bin/ls [0]
      2026:	checking for version `GLIBC_2.17' in file /lib64/libc.so.6 [0] required by file /bin/ls [0]
      2026:	checking for version `GLIBC_2.3.4' in file /lib64/libc.so.6 [0] required by file /bin/ls [0]
      2026:	checking for version `GLIBC_2.2.5' in file /lib64/libc.so.6 [0] required by file /bin/ls [0]
      2026:	checking for version `GLIBC_2.3' in file /lib64/libc.so.6 [0] required by file /bin/ls [0]
      2026:	checking for version `GLIBC_2.2.5' in file /lib64/libdl.so.2 [0] required by file /lib64/libselinux.so.1 [0]
      2026:	checking for version `GLIBC_2.3' in file /lib64/ld-linux-x86-64.so.2 [0] required by file /lib64/libselinux.so.1 [0]
      2026:	checking for version `GLIBC_2.14' in file /lib64/libc.so.6 [0] required by file /lib64/libselinux.so.1 [0]
      2026:	checking for version `GLIBC_2.8' in file /lib64/libc.so.6 [0] required by file /lib64/libselinux.so.1 [0]
      2026:	checking for version `GLIBC_2.4' in file /lib64/libc.so.6 [0] required by file /lib64/libselinux.so.1 [0]
      2026:	checking for version `GLIBC_2.7' in file /lib64/libc.so.6 [0] required by file /lib64/libselinux.so.1 [0]
      2026:	checking for version `GLIBC_2.3' in file /lib64/libc.so.6 [0] required by file /lib64/libselinux.so.1 [0]
      2026:	checking for version `GLIBC_2.2.5' in file /lib64/libc.so.6 [0] required by file /lib64/libselinux.so.1 [0]
      2026:	checking for version `GLIBC_2.3.4' in file /lib64/libc.so.6 [0] required by file /lib64/libselinux.so.1 [0]
      2026:	checking for version `GLIBC_2.3.4' in file /lib64/libc.so.6 [0] required by file /lib64/libcap.so.2 [0]
      2026:	checking for version `GLIBC_2.3' in file /lib64/libc.so.6 [0] required by file /lib64/libcap.so.2 [0]
      2026:	checking for version `GLIBC_2.8' in file /lib64/libc.so.6 [0] required by file /lib64/libcap.so.2 [0]
      2026:	checking for version `GLIBC_2.4' in file /lib64/libc.so.6 [0] required by file /lib64/libcap.so.2 [0]
      2026:	checking for version `GLIBC_2.2.5' in file /lib64/libc.so.6 [0] required by file /lib64/libcap.so.2 [0]
      2026:	checking for version `ATTR_1.0' in file /lib64/libattr.so.1 [0] required by file /lib64/libcap.so.2 [0]
(snip)
```

### scopes
```
$ LD_DEBUG=scopes /bin/ls
      2028:	
      2028:	Initial object scopes
      2028:	object=/bin/ls [0]
      2028:	 scope 0: /bin/ls /lib64/libselinux.so.1 /lib64/libcap.so.2 /lib64/libacl.so.1 /lib64/libc.so.6 /lib64/libpcre.so.1 /lib64/libdl.so.2 /lib64/ld-linux-x86-64.so.2 /lib64/libattr.so.1 /lib64/libpthread.so.0
      2028:	
      2028:	object=linux-vdso.so.1 [0]
      2028:	 scope 0: /bin/ls /lib64/libselinux.so.1 /lib64/libcap.so.2 /lib64/libacl.so.1 /lib64/libc.so.6 /lib64/libpcre.so.1 /lib64/libdl.so.2 /lib64/ld-linux-x86-64.so.2 /lib64/libattr.so.1 /lib64/libpthread.so.0
      2028:	 scope 1: linux-vdso.so.1
      2028:	
      2028:	object=/lib64/libselinux.so.1 [0]
      2028:	 scope 0: /bin/ls /lib64/libselinux.so.1 /lib64/libcap.so.2 /lib64/libacl.so.1 /lib64/libc.so.6 /lib64/libpcre.so.1 /lib64/libdl.so.2 /lib64/ld-linux-x86-64.so.2 /lib64/libattr.so.1 /lib64/libpthread.so.0
(snip)
```

### statistic
```
$ LD_DEBUG=statistics /bin/ls
      2032:	
      2032:	runtime linker statistics:
      2032:	  total startup time in dynamic loader: 1435010 cycles
      2032:		    time needed for relocation: 422148 cycles (29.4%)
      2032:	                 number of relocations: 173
      2032:	      number of relocations from cache: 9
      2032:	        number of relative relocations: 1358
      2032:		   time needed to load objects: 798425 cycles (55.6%)
hoge.txt
```

### all
LD_DEBUGに指定できるすべての値(helpを除く)が含まれる
```
$ LD_DEBUG=all /bin/ls
      2042:	
      2042:	file=libselinux.so.1 [0];  needed by /bin/ls [0]
      2042:	find library=libselinux.so.1 [0]; searching
      2042:	 search cache=/etc/ld.so.cache
      2042:	  trying file=/lib64/libselinux.so.1
      2042:	
      2042:	file=libselinux.so.1 [0];  generating link map
      2042:	  dynamic: 0x00007f6d401ded48  base: 0x00007f6d3ffbb000   size: 0x0000000000226970
      2042:	    entry: 0x00007f6d3ffc1ac0  phdr: 0x00007f6d3ffbb040  phnum:                  8
      2042:	
      2042:	
(snip)
      2042:	checking for version `ACL_1.0' in file /lib64/libacl.so.1 [0] required by file /bin/ls [0]
      2042:	checking for version `GLIBC_2.14' in file /lib64/libc.so.6 [0] required by file /bin/ls [0]
      2042:	checking for version `GLIBC_2.4' in file /lib64/libc.so.6 [0] required by file /bin/ls [0]
      2042:	checking for version `GLIBC_2.17' in file /lib64/libc.so.6 [0] required by file /bin/ls [0]
(snip)
      2042:	Initial object scopes
      2042:	object=/bin/ls [0]
      2042:	 scope 0: /bin/ls /lib64/libselinux.so.1 /lib64/libcap.so.2 /lib64/libacl.so.1 /lib64/libc.so.6 /lib64/libpcre.so.1 /lib64/libdl.so.2 /lib64/ld-linux-x86-64.so.2 /lib64/libattr.so.1 /lib64/libpthread.so.0
(snip)
      2042:	relocation processing: /lib64/libc.so.6
      2042:	symbol=_res;  lookup in file=/bin/ls [0]
      2042:	symbol=_res;  lookup in file=/lib64/libselinux.so.1 [0]
      2042:	symbol=_res;  lookup in file=/lib64/libcap.so.2 [0]            
(snip)
```

## LD_DEBUGの内容をログに記録したい
LD_DEBUG_OUTPUT環境変数に出力先を指定します。ファイル名にはpidもついていますので注意してください。
```
$ LD_DEBUG_OUTPUT=debugLog LD_DEBUG=statistics,libs /bin/ls
hoge.txt
$ ls debugLog.2082 
debugLog.2082
```

## 補助ベクトルを取得する
```
$ LD_SHOW_AUXV=1 /bin/ls
AT_SYSINFO_EHDR: 0x7ffe9a704000
AT_HWCAP:        78bfbff
AT_PAGESZ:       4096
AT_CLKTCK:       100
AT_PHDR:         0x400040
AT_PHENT:        56
AT_PHNUM:        9
AT_BASE:         0x7f627ea73000
AT_FLAGS:        0x0
AT_ENTRY:        0x404b48
AT_UID:          1000
AT_EUID:         1000
AT_GID:          1000
AT_EGID:         1000
AT_SECURE:       0
AT_RANDOM:       0x7ffe9a669cb9
AT_HWCAP2:       0x0
AT_EXECFN:       /bin/ls
AT_PLATFORM:     x86_64
hoge.txt hoge2.txt
```

上記の各種説明については以下のManに載っています。
- https://linuxjm.osdn.jp/html/LDP_man-pages/man3/getauxval.3.html

### どのようにリンクされているのかを確認する
```
$ LD_TRACE_PRELINKING=1 /bin/ls 
	/bin/ls => /bin/ls (0x0000000000400000, 0x0000000000000000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f24c104f000, 0x00007f24c104f000) TLS(0x1, 0x00000000000000e8)
	libcap.so.2 => /lib64/libcap.so.2 (0x00007f24c0e4a000, 0x00007f24c0e4a000)
	libacl.so.1 => /lib64/libacl.so.1 (0x00007f24c0c41000, 0x00007f24c0c41000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f24c087e000, 0x00007f24c087e000) TLS(0x2, 0x0000000000000180)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f24c061c000, 0x00007f24c061c000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f24c0418000, 0x00007f24c0418000)
	/lib64/ld-linux-x86-64.so.2 => /lib64/ld-linux-x86-64.so.2 (0x00007f24c1276000, 0x00007f24c1276000)
	libattr.so.1 => /lib64/libattr.so.1 (0x00007f24c0213000, 0x00007f24c0213000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f24bfff7000, 0x00007f24bfff7000)
lookup 0x00007f24c087e000 0x00000000000061e8 -> 0x00007f24c087e000 0x00000000003c0a40 /0 _res
lookup 0x00007f24c087e000 0x000000000000b918 -> 0x00007f24c087e000 0x00000000003bd868 /0 stderr
lookup 0x00007f24c087e000 0x000000000000cf08 -> 0x00007f24c087e000 0x00000000003c1d70 /0 error_one_per_line
lookup 0x00007f24c087e000 0x000000000000e330 -> 0x00007f24c087e000 0x00000000003bea40 /0 __malloc_initialize_hook
lookup 0x00007f24c087e000 0x0000000000003d70 -> 0x00007f24c1276000 0x0000000000222f80 /0 _dl_starting_up
lookup 0x00007f24c087e000 0x000000000000fbf0 -> 0x00007f24c087e000 0x00000000003bd880 /0 __morecore
lookup 0x00007f24c087e000 0x0000000000007c88 -> 0x00007f24c087e000 0x00000000003c2138 /0 __key_encryptsession_pk_LOCAL
lookup 0x00007f24c087e000 0x000000000000cea8 -> 0x00007f24c087e000 0x00000000003bd018 /0 __progname_full
lookup 0x00007f24c087e000 0x000000000000ab80 -> 0x00007f24c087e000 0x00000000003bd150 /0 __ctype32_tolower
lookup 0x00007f24c087e000 0x0000000000005798 -> 0x00007f24c087e000 0x00000000003bf4a8 /0 _environ
lookup 0x00007f24c087e000 0x0000000000003d88 -> 0x00007f24c1276000 0x0000000000222000 /0 _rtld_global
lookup 0x00007f24c087e000 0x00000000000056c0 -> 0x00007f24c087e000 0x00000000003bd010 /0 __progname
lookup 0x00007f24c087e000 0x000000000000b4e0 -> 0x00007f24c087e000 0x00000000003bc3a4 /0 argp_err_exit_status
lookup 0x00007f24c087e000 0x000000000000b030 -> 0x00007f24c087e000 0x00000000003c1cd8 /0 mallwatch
lookup 0x00007f24c087e000 0x0000000000004ec8 -> 0x00007f24c087e000 0x00000000003c2040 /0 __rcmd_errstr
lookup 0x00007f24c087e000 0x000000000000be58 -> 0x00007f24c087e000 0x00000000003bda40 /0 __vdso_clock_gettime
lookup 0x00007f24c087e000 0x000000000000aaf0 -> 0x00007f24c087e000 0x00000000003c2120 /0 svcauthdes_stats
lookup 0x00007f24c087e000 0x0000000000003da0 -> 0x00007f24c1276000 0x0000000000221df8 /0 __libc_enable_secure
lookup 0x00007f24c087e000 0x000000000000c890 -> 0x00007f24c087e000 0x00000000003c1f80 /0 _res_hconf
lookup 0x00007f24c087e000 0x000000000000aad8 -> 0x00007f24c087e000 0x00000000000800c0 /0 malloc
lookup 0x00007f24c087e000 0x0000000000004460 -> 0x00007f24c087e000 0x00000000003c1d44 /0 getdate_err
lookup 0x00007f24c087e000 0x0000000000005648 -> 0x00007f24c087e000 0x00000000003bd000 /0 __tzname
lookup 0x00007f24c087e000 0x000000000000df10 -> 0x00007f24c087e000 0x00000000003bee00 /0 __timezone
lookup 0x00007f24c087e000 0x0000000000003dd0 -> 0x00007f24c1276000 0x0000000000221c00 /0 _rtld_global_ro
lookup 0x00007f24c087e000 0x000000000000b8a0 -> 0x00007f24c087e000 0x00000000003c1d68 /0 optarg
lookup 0x00007f24c087e000 0x0000000000007d30 -> 0x00007f24c087e000 0x00000000003bd160 /0 __ctype_tolower
lookup 0x00007f24c087e000 0x0000000000009f20 -> 0x00007f24c087e000 0x00000000003bd158 /0 __ctype_toupper
lookup 0x00007f24c087e000 0x000000000000f758 -> 0x00007f24c087e000 0x00000000003c2060 /0 svc_max_pollfd
lookup 0x00007f24c087e000 0x0000000000008618 -> 0x00007f24c087e000 0x00000000003bd170 /0 __ctype_b
lookup 0x00007f24c087e000 0x0000000000006a70 -> 0x00007f24c087e000 0x00000000003c1db8 /0 argp_program_version_hook
lookup 0x00007f24c087e000 0x000000000000e6d8 -> 0x00007f24c087e000 0x00000000003bea20 /0 __after_morecore_hook
lookup 0x00007f24c087e000 0x000000000000b540 -> 0x00007f24c087e000 0x00000000003bf4a8 /0 __environ
lookup 0x00007f24c087e000 0x000000000000f4a0 -> 0x00007f24c087e000 0x00000000003bd168 /0 __ctype32_b
lookup 0x00007f24c087e000 0x0000000000009e78 -> 0x00007f24c087e000 0x00000000003bf4e0 /0 __curbrk
lookup 0x00007f24c087e000 0x0000000000005018 -> 0x00007f24c087e000 0x00000000003c1db0 /0 argp_program_version
lookup 0x00007f24c087e000 0x0000000000010ca0 -> 0x00007f24c087e000 0x00000000003bee10 /0 __daylight
lookup 0x00007f24c087e000 0x0000000000010b68 -> 0x00007f24c087e000 0x00000000003bc720 /0 __memalign_hook
lookup 0x00007f24c087e000 0x000000000000a220 -> 0x00007f24c087e000 0x00000000003bc740 /0 __malloc_hook
lookup 0x00007f24c087e000 0x0000000000005120 -> 0x00007f24c087e000 0x00000000003bea30 /0 __free_hook
lookup 0x00007f24c087e000 0x000000000000b348 -> 0x00007f24c087e000 0x00000000003c2068 /0 svc_pollfd
lookup 0x00007f24c087e000 0x000000000000dfd0 -> 0x00007f24c087e000 0x00000000003c1c08 /0 _nl_domain_bindings
lookup 0x00007f24c087e000 0x000000000000f7a0 -> 0x00007f24c087e000 0x00000000003c1c10 /0 _nl_msg_cat_cntr
lookup 0x00007f24c087e000 0x000000000000a538 -> 0x00007f24c087e000 0x00000000003c1da8 /0 argp_program_bug_address
lookup 0x00007f24c087e000 0x000000000000fff8 -> 0x00007f24c087e000 0x00000000003c2148 /0 __key_decryptsession_pk_LOCAL
lookup 0x00007f24c087e000 0x0000000000008990 -> 0x00007f24c087e000 0x00000000003b95e0 /0 h_errlist
lookup 0x00007f24c087e000 0x000000000000e3d8 -> 0x00007f24c087e000 0x00000000003bd010 /0 program_invocation_short_name
lookup 0x00007f24c087e000 0x0000000000004f88 -> 0x00007f24c087e000 0x00000000003bc2a0 /0 optind
lookup 0x00007f24c087e000 0x0000000000009de8 -> 0x00007f24c087e000 0x00000000003bd870 /0 stdout
lookup 0x00007f24c087e000 0x000000000000ea50 -> 0x00007f24c087e000 0x00000000003bcff0 /0 obstack_alloc_failed_handler
lookup 0x00007f24c087e000 0x00000000000059f0 -> 0x00007f24c087e000 0x00000000003c1d78 /0 error_print_progname
lookup 0x00007f24c087e000 0x000000000000bd98 -> 0x00007f24c087e000 0x00000000003bc280 /0 optopt
lookup 0x00007f24c087e000 0x0000000000008138 -> 0x00007f24c087e000 0x0000000000068a00 /0 _IO_funlockfile
lookup 0x00007f24c087e000 0x000000000000f2c0 -> 0x00007f24c087e000 0x00000000003bc1f8 /0 obstack_exit_failure
lookup 0x00007f24c087e000 0x000000000000bdb0 -> 0x00007f24c087e000 0x00000000003c1d80 /0 error_message_count
lookup 0x00007f24c087e000 0x000000000000b780 -> 0x00007f24c087e000 0x00000000003c2080 /0 svc_fdset
lookup 0x00007f24c087e000 0x0000000000007160 -> 0x00007f24c087e000 0x00000000003bd018 /0 program_invocation_name
lookup 0x00007f24c087e000 0x000000000000fd70 -> 0x00007f24c087e000 0x00000000003c1d88 /0 loc1
lookup 0x00007f24c087e000 0x0000000000010c58 -> 0x00007f24c087e000 0x00000000000804c0 /0 free
lookup 0x00007f24c087e000 0x000000000000fdb8 -> 0x00007f24c087e000 0x00000000003c1d90 /0 loc2
lookup 0x00007f24c087e000 0x000000000000bd08 -> 0x00007f24c087e000 0x00000000003bc084 /0 __fpu_control
lookup 0x00007f24c087e000 0x000000000000bf00 -> 0x00007f24c087e000 0x00000000003c1d60 /0 re_syntax_options
lookup 0x00007f24c087e000 0x0000000000006d40 -> 0x00007f24c087e000 0x00000000003bd878 /0 stdin
lookup 0x00007f24c087e000 0x000000000000c950 -> 0x00007f24c087e000 0x00000000003bc3c0 /0 __check_rhosts_file
lookup 0x00007f24c087e000 0x000000000000fe60 -> 0x00007f24c087e000 0x00000000003bc290 /0 opterr
lookup 0x00007f24c087e000 0x000000000000cd28 -> 0x00007f24c087e000 0x00000000003bd148 /0 __ctype32_toupper
lookup 0x00007f24c087e000 0x000000000000c6c8 -> 0x00007f24c087e000 0x00000000003bc730 /0 __realloc_hook
lookup 0x00007f24c087e000 0x0000000000003de8 -> 0x00007f24c1276000 0x0000000000221d88 /0 _dl_argv
lookup 0x00007f24c087e000 0x000000000000b498 -> 0x00007f24c087e000 0x00000000003c2100 /0 rpc_createerr
lookup 0x00007f24c087e000 0x000000000000ba08 -> 0x00007f24c087e000 0x00000000003bd1c0 /0 _IO_2_1_stderr_
lookup 0x00007f24c087e000 0x0000000000008798 -> 0x00007f24c087e000 0x00000000003bd400 /0 _IO_2_1_stdout_
lookup 0x00007f24c087e000 0x0000000000005e10 -> 0x00007f24c087e000 0x00000000003bd640 /0 _IO_2_1_stdin_
lookup 0x00007f24c087e000 0x0000000000006ae8 -> 0x00007f24c087e000 0x00000000000805a0 /1 realloc
lookup 0x00007f24c087e000 0x000000000000aad8 -> 0x00007f24c087e000 0x00000000000800c0 /1 malloc
lookup 0x00007f24c087e000 0x0000000000003db8 -> 0x00007f24c1276000 0x0000000000012400 /1 __tls_get_addr
lookup 0x00007f24c087e000 0x00000000000066f8 -> 0x00007f24c087e000 0x0000000000080950 /1 memalign
lookup 0x00007f24c087e000 0x0000000000008420 -> 0x00007f24c087e000 0x0000000000080ab0 /1 calloc
lookup 0x00007f24c087e000 0x0000000000010c58 -> 0x00007f24c087e000 0x00000000000804c0 /1 free
lookup 0x00007ffca9775000 0xfffffffffffdd130 -> 0x00007ffca9775000 0xffffffffff700f50 /0 __vdso_time
lookup 0x00007ffca9775000 0xfffffffffffdd130 -> 0x00007ffca9775000 0xffffffffff700c70 /0 __vdso_gettimeofday
lookup 0x00007f24bfff7000 0x0000000000001008 -> 0x00007f24c087e000 0x0000000000000010 /4 errno
lookup 0x00007f24bfff7000 0x0000000000001020 -> 0x00007f24c087e000 0x000000000000007c /4 h_errno
lookup 0x00007f24bfff7000 0x0000000000001080 -> 0x00007f24c087e000 0x0000000000000008 /4 __resp
lookup 0x00007f24bfff7000 0x0000000000001140 -> 0x00007f24c1276000 0x0000000000221df8 /0 __libc_enable_secure
lookup 0x00007f24bfff7000 0x00000000000012a8 -> 0x00007f24c1276000 0x0000000000221df0 /0 __libc_stack_end
lookup 0x00007f24bfff7000 0x0000000000001338 -> 0x00007f24c1276000 0x0000000000221c00 /0 _rtld_global_ro
lookup 0x00007f24bfff7000 0x0000000000001518 -> 0x00007f24c087e000 0x0000000000134320 /0 __libc_dl_error_tsd
lookup 0x00007f24bfff7000 0x00000000000015f0 -> 0x00007f24c087e000 0x00000000003bf4a8 /0 __environ
lookup 0x00007f24bfff7000 0x00000000000016b0 -> 0x00007f24c1276000 0x0000000000222000 /0 _rtld_global
lookup 0x00007f24bfff7000 0x00000000000016f8 -> 0x00007f24c087e000 0x0000000000038d40 /0 __cxa_finalize
lookup 0x00007f24c0213000 0x00000000000007e8 -> 0x00007f24c0213000 0x0000000000002e40 /0 attr_copy_check_permissions
lookup 0x00007f24c0213000 0x0000000000000560 -> 0x00007f24c087e000 0x0000000000038d40 /0 __cxa_finalize
conflict 0x00007f24c0418000 0x0000000000000338 -> 0x00007f24bfff7000 0x000000000000c6e0 x 0x0000000000000000 0x0000000000000000 /0 __pthread_key_create
conflict 0x00007f24c0418000 0x0000000000000368 -> 0x00007f24bfff7000 0x000000000000c780 x 0x0000000000000000 0x0000000000000000 /0 __pthread_getspecific
lookup 0x00007f24c0418000 0x0000000000000410 -> 0x00007f24c1276000 0x0000000000221c00 /0 _rtld_global_ro
conflict 0x00007f24c0418000 0x0000000000000440 -> 0x00007f24bfff7000 0x000000000000cdd0 x 0x0000000000000000 0x0000000000000000 /0 __pthread_once
lookup 0x00007f24c0418000 0x0000000000000470 -> 0x00007f24c087e000 0x000000000017debc /0 _libc_intl_domainname
lookup 0x00007f24c0418000 0x00000000000004d0 -> 0x00007f24c087e000 0x00000000003bf4a8 /0 __environ
conflict 0x00007f24c0418000 0x0000000000000500 -> 0x00007f24bfff7000 0x000000000000c800 x 0x0000000000000000 0x0000000000000000 /0 __pthread_setspecific
lookup 0x00007f24c0418000 0x0000000000000530 -> 0x00007f24c1276000 0x0000000000222000 /0 _rtld_global
lookup 0x00007f24c0418000 0x0000000000000548 -> 0x00007f24c087e000 0x0000000000038d40 /0 __cxa_finalize
lookup 0x00007f24c061c000 0x0000000000000668 -> 0x00007f24c061c000 0x0000000000261128 /0 pcre_callout
lookup 0x00007f24c061c000 0x0000000000000620 -> 0x00007f24c061c000 0x0000000000261110 /0 pcre_malloc
lookup 0x00007f24c061c000 0x00000000000006c8 -> 0x00007f24c061c000 0x0000000000261108 /0 pcre_free
lookup 0x00007f24c061c000 0x0000000000000530 -> 0x00007f24c087e000 0x0000000000038d40 /0 __cxa_finalize
lookup 0x00007f24c061c000 0x0000000000000338 -> 0x00007f24c087e000 0x00000000000804c0 /0 free
lookup 0x00007f24c061c000 0x0000000000000488 -> 0x00007f24c087e000 0x00000000000800c0 /0 malloc
lookup 0x00007f24c0c41000 0x00000000000003f0 -> 0x00007f24c0213000 0x00000000000032f0 /0 getxattr
lookup 0x00007f24c0c41000 0x0000000000000828 -> 0x00007f24c0c41000 0x0000000000208200 /0 closed
lookup 0x00007f24c0c41000 0x0000000000000a50 -> 0x00007f24c0c41000 0x0000000000208278 /0 num_dir_handles
lookup 0x00007f24c0c41000 0x00000000000006a8 -> 0x00007f24c0213000 0x0000000000003310 /0 lgetxattr
lookup 0x00007f24c0c41000 0x0000000000000af8 -> 0x00007f24c0c41000 0x0000000000208220 /0 head
lookup 0x00007f24c0c41000 0x0000000000000810 -> 0x00007f24c087e000 0x0000000000038d40 /0 __cxa_finalize
lookup 0x00007f24c0e4a000 0x0000000000000888 -> 0x00007f24c0e4a000 0x0000000000204120 /0 _cap_names
lookup 0x00007f24c0e4a000 0x0000000000000570 -> 0x00007f24c087e000 0x0000000000038d40 /0 __cxa_finalize
lookup 0x00007f24c104f000 0x0000000000000b30 -> 0x00007f24c087e000 0x00000000003bd870 /0 stdout
lookup 0x00007f24c104f000 0x0000000000001e68 -> 0x00007f24c104f000 0x0000000000225788 /0 selinux_mnt
lookup 0x00007f24c104f000 0x0000000000000c08 -> 0x00007f24c087e000 0x00000000003bd878 /0 stdin
lookup 0x00007f24c104f000 0x0000000000000f68 -> 0x00007f24c087e000 0x00000000000bac60 /0 alphasort
lookup 0x00007f24c104f000 0x0000000000001ef8 -> 0x00007f24c104f000 0x0000000000224650 /0 myprintf
lookup 0x00007f24c104f000 0x00000000000010e8 -> 0x00007f24bfff7000 0x000000000000c6e0 /0 pthread_key_create
lookup 0x00007f24c104f000 0x00000000000011f0 -> 0x00007f24bfff7000 0x000000000000cdd0 /0 pthread_once
lookup 0x00007f24c104f000 0x0000000000001970 -> 0x00007f24c104f000 0x00000000002257a8 /0 myprintf_compat
lookup 0x00007f24c104f000 0x0000000000001310 -> 0x00007f24bfff7000 0x000000000000c800 /0 pthread_setspecific
lookup 0x00007f24c104f000 0x0000000000001400 -> 0x00007f24bfff7000 0x000000000000c740 /0 pthread_key_delete
lookup 0x00007f24c104f000 0x0000000000001610 -> 0x00007f24c061c000 0x0000000000261108 /0 pcre_free
lookup 0x00007f24c104f000 0x0000000000002360 -> 0x00007f24c104f000 0x00000000000095e0 /0 avc_netlink_loop
lookup 0x00007f24c104f000 0x0000000000001628 -> 0x00007f24c087e000 0x0000000000038d40 /0 __cxa_finalize
lookup 0x00007f24c104f000 0x0000000000001688 -> 0x00007f24c087e000 0x00000000003bd868 /0 stderr
lookup 0x0000000000400000 0x0000000000000390 -> 0x00007f24c087e000 0x00000000000804c0 /0 free
lookup 0x0000000000400000 0x0000000000000438 -> 0x00007f24c087e000 0x00000000003bd870 /0 stdout
lookup 0x0000000000400000 0x0000000000000588 -> 0x00007f24c087e000 0x00000000003bc2a0 /0 optind
lookup 0x0000000000400000 0x0000000000000948 -> 0x00007f24c087e000 0x00000000003c1d68 /0 optarg
lookup 0x0000000000400000 0x00000000000009f0 -> 0x00007f24c087e000 0x00000000003bd018 /0 program_invocation_name
lookup 0x0000000000400000 0x0000000000000a80 -> 0x00007f24c087e000 0x00000000000800c0 /0 malloc
lookup 0x0000000000400000 0x0000000000000df8 -> 0x00007f24c087e000 0x00000000003bd010 /0 program_invocation_short_name
lookup 0x0000000000400000 0x0000000000000e88 -> 0x00007f24c087e000 0x00000000003bd868 /0 stderr
lookup 0x00007f24c1276000 0x0000000000000618 -> 0x00007f24c1276000 0x0000000000221df8 /0 __libc_enable_secure
lookup 0x00007f24c1276000 0x0000000000000498 -> 0x00007f24c1276000 0x0000000000223120 /0 _r_debug
conflict 0x00007f24c1276000 0x0000000000000438 -> 0x00007f24c087e000 0x00000000000804c0 x 0x00007f24c1276000 0x0000000000017e90 /0 free
conflict 0x00007f24c1276000 0x00000000000004c8 -> 0x00007f24c087e000 0x0000000000080950 x 0x00007f24c1276000 0x0000000000017d30 /1 __libc_memalign
conflict 0x00007f24c1276000 0x00000000000005d0 -> 0x00007f24c087e000 0x00000000000800c0 x 0x00007f24c1276000 0x0000000000017e40 /1 malloc
lookup 0x00007f24c1276000 0x00000000000005a0 -> 0x00007f24c1276000 0x0000000000012400 /1 __tls_get_addr
conflict 0x00007f24c1276000 0x00000000000004f8 -> 0x00007f24c087e000 0x0000000000080ab0 x 0x00007f24c1276000 0x0000000000017e50 /1 calloc
conflict 0x00007f24c1276000 0x0000000000000450 -> 0x00007f24c087e000 0x00000000000805a0 x 0x00007f24c1276000 0x0000000000017ec0 /1 realloc
conflict 0x00007f24c1276000 0x0000000000000438 -> 0x00007f24c087e000 0x00000000000804c0 x 0x00007f24c1276000 0x0000000000017e90 /1 free
```
