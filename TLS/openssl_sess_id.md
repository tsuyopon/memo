### SSL$B%;%C%7%g%s>pJs$r2rFI$9$k(B
sess_out$B$G(BSSL$B%;%C%7%g%s>pJs$r%U%!%$%k$KJ]B8$9$k$3$H$,$G$-$^$9!#(Bsess_out.txt$B$K$O80>pJs$b4^$^$l$F$$$k$N$G<h$j07$$$OCm0U$9$k$3$H(B
```
$ echo Q | openssl s_client -connect www.yahoo.co.jp:443 -sess_out sess_out.txt
$ cat sess_out.txt 
-----BEGIN SSL SESSION PARAMETERS-----
MIIN2AIBAQICAwEEAgAvBCAojDT12uPks31zRTxR/4OLzaf/mxqgHVlUX0LEj7Jb
(snip)
-----END SSL SESSION PARAMETERS-----
```

SSL$B%;%C%7%g%s>pJs$r2rFI$9$k%3%^%s%I$H$7$F!V(Bopenssl sess_id$B!W$,MQ0U$5$l$F$$$^$9!#(B
```
$ openssl sess_id -text -noout -in sess_out.txt
SSL-Session:
    Protocol  : TLSv1
    Cipher    : 002F
    Session-ID: 288C34F5DAE3E4B37D73453C51FF838BCDA7FF9B1AA01D59545F42C48FB25B7E
    Session-ID-ctx: 
    Master-Key: 2661AFF37A1B4EA86AED1CCBB1CB884405B65E234E53D0BE27BE7986AB761C049E494BD0B17F0861C70DE93CAE34971C
    Key-Arg   : None
    Start Time: 1520725126
    Timeout   : 300 (sec)
    Verify return code: 0 (ok)
```
