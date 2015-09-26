
# 概要
glibcは標準ライブラリです。  
chown, write, ldconfig等のシステムで標準で使われているようなコマンドやmemcmp, mmap等のシステムコールなども含んでいます。

# 内容

### ソースコードに内容が記載されていない
例えば、glibc/io/chown.c などのソースコードを見るとロジックの記載が存在しない。

```
 18 #include <errno.h>
 19 #include <stddef.h>
 20 #include <unistd.h>
 21 #include <sys/types.h>
 22 
 23 /* Change the owner and group of FILE.  */
 24 int
 25 __chown (file, owner, group)
 26      const char *file;
 27      uid_t owner;
 28      gid_t group;
 29 {
 30   if (file == NULL)
 31     {
 32       __set_errno (EINVAL);
 33       return -1;
 34     }
 35 
 36   __set_errno (ENOSYS);
 37   return -1;
 38 }
 39 libc_hidden_def (__chown)
 40 stub_warning (chown)
 41 
 42 weak_alias (__chown, chown)
```

おそらく、stub_warning(chown)のような記述が存在する場合には下記に示すsysdepsディレクトリ配下に存在しています。

```
    sysdeps/unix/sysv/linux
    sysdeps/posix
    sysdeps/i386 (or x86_64 or whatever your cpu arch is)
```

* 参考URL
	* Need help with glibc source(Stack Overflow)
		* http://stackoverflow.com/questions/6515583/need-help-with-glibc-source
