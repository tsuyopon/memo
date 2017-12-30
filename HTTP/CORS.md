# $B35MW(B
Cross-Origin Resource Sharing$B!J(BCORS$B!K$O!"(BHTML5 $B@$Be$N;EMM$G$9!#(Bw3c$B$K$h$j4+9p$5$l$F$$$^$9!#(B
- https://www.w3.org/TR/cors/

$B%/%m%9%I%a%$%s@)Ls$KBP$9$k0[$J$k%*%j%8%s$X$N%"%/%;%9$r5v2D$9$k$K$O(BCORS$B$r;HMQ$7$^$9!#(B
$B%/%m%9%*%j%8%s%I%a%$%s@)Ls$H$O!"(BAjax$B%j%/%(%9%H(B(XMLHttpRequest)$B$J$I$G%3%s%F%s%D$,@8@.$5$l$?%I%a%$%s$H$OJL$N%I%a%$%s$K%"%/%;%9$7$?>l9g$K$O%(%i!<$H$J$k;EAH$_$G$9!#(B

$BNc$($P!"%V%i%&%6$GI=<($5$l$k<!$N%(%i!<$O%/%m%9%I%a%$%s@)Ls$KBP$9$k$b$N$G$9!#(B
```
$B%/%m%9%*%j%8%sMW5a$r%V%m%C%/$7$^$7$?(B: $BF10l@8@.85%]%j%7!<$K$h$j!"(Bhttp://example.co.jp/test.html $B$K$"$k%j%b!<%H%j%=!<%9$NFI$_9~$_$O5qH]$5$l$^$9(B ($BM}M3(B: CORS $B%X%C%@!<(B $B!F(BAccess-Control-Allow-Origin$B!G(B $B$,B-$j$J$$(B)$B!#(B
```

# $B>\:Y(B

### $B%/%m%9%I%a%$%s@)Ls$r<u$1$J$$>l9g(B
$B0J2<$N;XDj$N>l9g$K$O%/%m%9%I%a%$%s@)Ls$r$&$1$J$$!#(B
```
<link rel="stylesheet" href="...">
<script src="..."></script>
<img>
<video>
<audio>
<object>
<embed>
<applet>
@font-face $B$G;XDj$5$l$?%U%)%s%H(B
<frame>
<iframe>
```

- SeeAlso
  - https://developer.mozilla.org/ja/docs/Web/Security/Same-origin_policy


### CORS$B$GI,MW$J%j%/%(%9%H%X%C%@(B
- Orign
  - Origin$B$O%j%/%(%9%H$r:G=i$K3+;O$7$?%5!<%P!<$r<($9(B URI $B$G$9!#$3$3$K%Q%9>pJs$O4^$a$:!"%5!<%P!<L>$@$1$K$7$^$9!#(B
  - Ajax$B$G%j%/%(%9%H$5$l$kJL%I%a%$%s$O$3$N%X%C%@$r8+$F!"(BOrigin$B$,$3$N%5!<%P$G$"$l$PBg>fIW$+$I$&$+$rH=CG$7$^$9!#(B
```
Origin: http://origin.co.jp
```
- Access-Control-Request-Method
  - $B%j%/%(%9%H$O(B POST $B%j%/%(%9%H%a%=%C%I$GAw$i$l$k$3$H$r!"%W%j%U%i%$%H%j%/%(%9%H$N0lIt$G%5!<%P!<$KDLCN$7$^$9(B
```
Access-Control-Request-Method: POST
```
- Access-Control-Request-Headers
  - $B<B:]$N%j%/%(%9%H$K$3$3$G;XDj$5$l$?%X%C%@$,4^$^$l$k$3$H$rDLCN$7$^$9!#Nc$($P!"!V(BX-PINGOTHER, Content-Type$B!W$NCM$,4^$^$l$F$$$l$P$3$l$i#2$D$N%X%C%@$,%j%/%(%9%H$KF~$k$3$H$rDLCN$7$^$9!#(B
```
Access-Control-Request-Headers: X-PINGOTHER, Content-Type
```

### CORS$B$GI,MW$J!!%l%9%]%s%9%X%C%@(B
- Access-Control-Allow-Origin
  - $B$3$N%X%C%@$K$O%/%m%9%5%$%HJ}<0$G%"%/%;%9$G$-$k%I%a%$%s$rJV$7$^$9!#%j%/%(%9%H$X$N(BOrigin$B%X%C%@$K4^$^$l$kCM$r4^$`$Y$-$G$9!#!V(B*$B!W$J$I$rJV$9$3$H$b$"$j$^$9!#(B
```
Access-Control-Allow-Origin: http://origin.co.jp
```
- Access-Control-Allow-Methods
  - $BEv3:%j%=!<%9$X$N%"%/%;%9$KBP$7$F;XDj$5$l$?%a%=%C%I$@$1$,2DG=$G$"$k$3$H$r<($7$^$9!#(B
```
Access-Control-Allow-Methods: POST, GET, OPTIONS
```
- Access-Control-Allow-Headers
  - $B<B:]$K;HMQ$G$-$k%j%/%(%9%H%X%C%@$H$7$FG'$a$k$b$N$rI=$7$F$$$^$9!#(B
```
Access-Control-Allow-Headers: X-PINGOTHER, Content-Type
```
- Access-Control-Max-Age
  - $B%W%j%U%i%$%H%j%/%(%9%H(B(OPTIONS)$B$rAwIU$7$J$/$F$b$$$$$h$&$K$3$N%l%9%]%s%9$r%-%c%C%7%e$7$F$b$h$$;~4V$rIC?t$G;XDj$7$^$9!#(B
```
Access-Control-Max-Age: 86400
```
- Access-Control-Allow-Credentials
  - $B%/%m%9%I%a%$%s$+$i%j%/%(%9%H$rAwIU$5$l$F$-$F$b(BCookie$B$,Aw$i$l$F$3$J$$>l9g$K$O!"$3$N%X%C%@$r(Btrue$B$K$9$kI,MW$,$"$k!#(B
  - $B$"$H!"(BAccess-Control-Allow-Origin$B%X%C%@!<$r(B*$B;XDj$K$7$FA45v2D$K$7$?$i!"$&$^$/$$$+$J$+$C$?$H$N5-;v$b$"$C$?$j$9$k$N$GCm0U$9$k$3$H(B
```
Access-Control-Allow-Credentials: true
```
- Access-Control-Expose-Headers
  - $B%V%i%&%6$,;HMQ$G$-$k%X%C%@$N%[%o%$%H%j%9%H$r%5!<%P!<$,<($9$3$H$,$G$-$^$9!#Nc$($P0J2<$N>l9g$G$"$l$P!"%V%i%&%6$KBP$7$F(B X-My-Custom-Header $B$*$h$S(B X-Another-Custom-Header $B%X%C%@$r5v2D$7$^$9!#%*!<%W%s$K8x3+$7$F$$$^$9(B
```
Access-Control-Expose-Headers: X-My-Custom-Header, X-Another-Custom-Header
```

https://qiita.com/tomoyukilabs/items/81698edd5812ff6acb34

### $B%W%j%U%i%$%H%j%/%(%9%H(B
$B%W%j%U%i%$%H%j%/%(%9%H$H$O!"%V%i%&%6$,(BCORS$B$K3:Ev$9$k$H$-$KJL%5!<%P$KBP$7$F2?$,5v2D$5$l$F$$$k$+$r<B:]$K%j%/%(%9%H$9$kA0$K(BOPTIONS$B$G3NG'$9$kJ}K!$G$9!#(B

- 1. $B%5!<%P$+$i%/%i%$%"%s%H$K(BOPTIONS$B%a%=%C%I$G<!$N>r7o$G%"%/%;%9$G$-$k$+$I$&$+$r3NG'$7$^$9!#(B
```
Method: OPTIONS
Origin: http://example.com/
Access-Control-Request-Headers: content-type
Access-Control-Request-Method: POST
```
- 2. $B%5!<%PB&$O>e5-%j%/%(%9%H$r<u$1<h$C$F(BOrigin$B%5!<%P$,LdBjL5$$$3$H$N3NG'!"%a%=%C%I$J$I$,LdBjL5$$$3$H$r3NG'$7$^$9!#3NG'$G$-$?$i<!$N%l%9%]%s%9$r1~Ez$7$^$9!#(B
```
Access-Control-Allow-Origin: http://example.com/
Access-Control-Allow-Headers: content-type
Access-Control-Allow-Method: POST
```
- 3. $B%/%i%$%"%s%H$+$i%5!<%PB&$K%j%/%(%9%H$7$^$9!#(B
```
Method: POST
content-type: application/json
{json1: param1, json2: param2, ...}
```
- 4. $B%5!<%P$+$i%/%i%$%"%s%H$K%l%9%]%s%9$,1~Ez$5$l$^$9!#(B
```
content-type: application/json
```

### JSONP$B$K$h$kF10l@8@.852sHrJ}K!(B
JSONP$B$G$O!"(BCORS$B$rHr$1$k$?$a$K(Bscript$B%?%0$N%9%/%j%W%H%=!<%9$K$OF10l@8@.85%]%j%7!<$,$J$$$3$H$rMxMQ$7$^$9!#(B
```
<script type="text/javascript" src="http://www.example.com/foo.php?id=1"></script>
```

JSONP$B$H$7$F$O$D$.$N$h$&$J(BJSON $BJ8;zNs$K$h$k%*%V%8%'%/%H%j%F%i%k$NAw?.$K2C$($F!"4X?t8F$S=P$7$rIU$1B-$7$^$9!#(B
```
func1( {"id":1, "firstname":"Taro", "lastname":"Yamada"} );
```

JSONP$B$@$HC/$G$bFI$_9~$`$3$H$,$G$-$k$N$G%"%/%;%9;~$KG'>Z>pJs$r%Q%i%a!<%?$J$I$KIUM?$9$k$H$h$$$G$7$g$&!#(B

# $B;29M(BURL
- Cross-Origin Resource Sharing(W3C)
  - https://www.w3.org/TR/cors/
- The Web Origin Concept
  - https://www.ietf.org/rfc/rfc6454.txt
- HTTP $B%"%/%;%9@)8f(B (CORS)(Mozilla)
  - https://developer.mozilla.org/ja/docs/Web/HTTP/HTTP_access_control
- Using CORS
  - https://www.html5rocks.com/en/tutorials/cors/
