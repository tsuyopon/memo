### SSLセッション情報を解読する
sess_outでSSLセッション情報をファイルに保存することができます。sess_out.txtには鍵情報も含まれているので取り扱いは注意すること
```
$ echo Q | openssl s_client -connect www.yahoo.co.jp:443 -sess_out sess_out.txt
$ cat sess_out.txt 
-----BEGIN SSL SESSION PARAMETERS-----
MIIN2AIBAQICAwEEAgAvBCAojDT12uPks31zRTxR/4OLzaf/mxqgHVlUX0LEj7Jb
(snip)
-----END SSL SESSION PARAMETERS-----
```

SSLセッション情報を解読するコマンドとして「openssl sess_id」が用意されています。
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
