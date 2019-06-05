# $B35MW(B
yumdownloader$B$O(Brpm$B%Q%C%1!<%8$r%@%&%s%m!<%I$9$k:]$KJXMx$J%D!<%k$G$9!#(B
$B%3%^%s%I$,F~$C$F$$$J$$>l9g$K$O0J2<$N%3%^%s%I$G%$%s%9%H!<%k$7$^$7$g$&!#(B
```
$ sudo yum install yum-utils
```

yum$B$G$b(Bdownloadonly$B%*%W%7%g%s$J$I$,$"$j$^$9$,!"(Byum$B$G$N%@%&%s%m!<%I$N>l9g$K$O0MB8$r>!<j$K2r7h$7$F$/$l$F$7$^$&$N$G(Bcurl-1.0.0, openssl-0.98.0$B$N$h$&$K;XDj$r$7$?$H$7$F(Bcurl-1.0.0$B$,(Bopenssl-1.0.1$B0J>e$rMW5a$7$F$$$k$H>!<j$K(Bcurl-1.0.0$B$H(Bopenssl-1.0.1$B$r<hF@$7$h$&$H$9$k$N$G$3$N$h$&$J;H$$>!<j$G$O$h$m$7$/$"$j$^$;$s!#(B


# $B>\:Y(B

### $B4pK\%@%&%s%m!<%IJ}K!(B
```
$ yumdownloader curl          # $B:G?7HG$r%@%&%s%m!<%I$7$h$&$H$9$k(B
$ yumdownloader curl-1.0.0    # 1.0.0$BHG$r%@%&%s%m!<%I$7$h$&$H$9$k(B
$ yumdownloader --enablerepo=updates-base  curl  # $B%l%]%8%H%j$r;XDj$7$F%@%&%s%m!<%I$9$k(B
$ yumdownloader --disablerepo=updates-base curl  # $BITMW$J%l%]%8%H%j$r;XDj$7$F%@%&%s%m!<%I$9$k(B
$ yumdownloader --enablerepo=updates-base --disablerepo=* curl  # updates-base$B$N$_0J30$N%l%]%8%H%j0J30$+$i$O(Bcurl$B$N%@%&%s%m!<%I$r5v2D$7$J$$(B
```

$B%=!<%9%3!<%I$r;XDj$9$k>l9g$K$O(Bsource$B%*%W%7%g%s$r;XDj$7$^$9!#(B 
```
$ yumdownloader --source curl
```
$B>e5-$K$h$j!"(B($BNc(B) curl-7.29.0-51.el7.src.rpm $B$N$h$&$J(Bsrc.rpm$B%U%!%$%k$r%@%&%s%m!<%I$G$-$^$9!#(Bsrc.rpm$B$NE83+J}K!$O8e=R$7$^$9!#(B


### rpm$B%Q%C%1!<%8$r<hF@$7$F!"E83+$9$k(B
rpm$B$r%@%&%s%m!<%I$9$k>l9g$K$O<!$N$h$&$K$7$^$9!#(Bdestdir$B$G%@%&%s%m!<%I@h$r;XDj$7$^$9!#3HD%;R$,(B.rpm$BNY$C$F$$$k$3$H$KCm0U$9$k$3$H(B
```
$ yumdownloader --destdir=/tmp httpd 
httpd-2.2.23-1.fc17.x86_64.rpm
```

rpm$B$rE83+$9$k$K$O(B
```
$ mkdir xxxx; cp *.rpm xxx; cd xxxx
$ rpm2cpio httpd-2.2.23-1.fc17.x86_64.rpm | cpio -idv
```

### $B%=!<%9%3!<%I$r<hF@$7$?$$(B
$B$?$H$($P!"(Bmysql$B$N%=!<%9%3!<%I$r<hF@$7$?$$>l9g(B
```
$ yumdownloader --source mysql-server-5.5.32-1.fc17.x86_64
$ ls
mysql-5.5.32-1.fc17.src.rpm
```

src.rpm$B$K4^$^$l$k%U%!%$%k0lMw$rI=<($9$k>l9g$O<!$N%3%^%s%I$G3NG'$G$-$k!#(B
```
$ rpm2cpio mysql-5.5.32-1.fc17.src.rpm | cpio --list
```

src.rpm$B$rE83+$9$k$K$O<!$N$h$&$K$9$k!#(B
```
$ mkdir work
$ cd work/
$ rpm2cpio ../mysql-5.5.32-1.fc17.src.rpm | cpio -id
42555 blocks
$ ls
README.mysql-docs           mysql-chain-certs.patch      mysql-innodbwarn.patch    mysql-stack-guard.patch      mysqld-wait-ready
README.mysql-license        mysql-cipherspec.patch       mysql-install-test.patch  mysql-string-overflow.patch  mysqld.service
filter-requires-mysql.sh    mysql-dh1024.patch           mysql-logrotate.patch     mysql-strmov.patch           rh-skipped-tests-arm.list
generate-tarball.sh         mysql-dubious-exports.patch  mysql-man-gpl.tar.gz      mysql-va-list.patch          rh-skipped-tests-base.list
libmysql.version            mysql-embedded-check.c       mysql-netdevname.patch    mysql-versioning.patch       scriptstub.c
my.cnf                      mysql-errno.patch            mysql-plugin-bool.patch   mysql.spec
my_config.h                 mysql-expired-certs.patch    mysql-plugin-test.patch   mysql.tmpfiles.d
mysql-5.5.32-nodocs.tar.gz  mysql-file-contents.patch    mysql-s390-tsc.patch      mysqld-prepare-db-dir
$ tar zxvf mysql-5.5.32-nodocs.tar.gz
$ cd mysql
```
$B$"$H$O$3$NCf$K%=!<%9%3!<%I$,4^$^$l$F$$$k$N$GE,59;2>H$9$l$P$h$$!#(B


