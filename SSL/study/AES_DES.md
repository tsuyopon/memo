# $B35MW(B
$B%V%m%C%/0E9f(B(DES, AES)$B$K$D$$$F@bL@$9$k!#(B
```
$BBP>]0E9f(B($B6&DL80(B)
	$B%9%H%j!<%`0E9f(B: 
		$B%G!<%?$rC`<!0E9f2=(B(RC4, Chacha20)
	$B%V%m%C%/0E9f(B:
		$B%G!<%?$r%V%m%C%/Kh$K0E9f2=(B(DES, AES)
```

# $B>\:Y(B

### DES(Data Encryption Standard)
AES$B$h$jA0$NJ}<0$G$9!#(B
DES$B$O<!$NLdBj$,$"$C$?!#(B
- $B!&;~Be$N7P2a$K$h$kAjBPE*$J6/EY$NDc2<(B
- $B!&(BNSA$B$N4XM?$,$"$k$=$N@_7W$NITF)L@@-(B


$B;29M(B
- https://ja.wikipedia.org/wiki/Data_Encryption_Standard

### AES(Advanced Encryption Standard) $B$H$O2?$+(B?
$B%"%a%j%+$G$O(BDES$B$d%H%j%W%k(BDES$B$H$$$C$?0E9fJ}<0$,;H$o$l$F$$$?!#(B  
$B$7$+$7!"$3$NJ}K!$O8E$/$J$C$?$N$G%"%a%j%+@/I\$O8xJg$K$h$C$F$h$j6/NO$J0E9f2=J}<0$rA*Br$7$?!#(B  
$B$=$l$,!"(BRijndael ($B%i%$%s%@!<%k(B) $B$H$$$&%"%k%4%j%:%`$G!"$3$l$,(B AES $B$H$7$F:NBr$5$l$k$3$H$K$J$j$^$7$?!#(B  
AES$B$NFCD'$H$7$F$O<!$NDL$j(B
- SPN$B9=B$$N%V%m%C%/0E9f(B
- $B%V%m%C%/D9$O(B128$B%S%C%H(B
- $B80D9$O(B128$B%S%C%H!&(B192$B%S%C%H!&(B256$B%S%C%H$N(B3$B$D$,MxMQ$G$-$k!#(B

AES$B$OL5@~(BLAN$B$G;H$o$l$k$3$H$,B?$/!"0BA4$H$5$l$k(BWPA2$B$K:NMQ$5$l$F$$$k!#(B  
(WEP, WPA, WPA2$B$O0E9f2=$K4X$9$k5,3J$rI=$7!"(BTKIP$B$d(BAES$B$O0E9f2=J}<0$rI=$935G0(B)
- $B;29M(B: http://wa3.i-3-i.info/word15121.html

$B;29M%]%$%s%?(B
- AES$B;EMM=q(B
  - http://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf
  - $B%"%k%4%j%:%`$d(Binput, output$B$J$I$,5-=R$5$l$F$$$k!#(B
- AES$B35@b(B
  - http://web.archive.org/web/20090503235219/http://www-ailab.elcom.nitech.ac.jp/security/aes/overview.html
- NIST$B$K$h$k;qNA(B(Report on Development of the AES)
  - http://csrc.nist.gov/archive/aes/round2/r2report.pdf
- $B@lMQ$N(BCPU$BL?Na$,$"$k!#(B($B=P$7$F$_$?$$(B*TODO)
  - https://ja.wikipedia.org/wiki/AES-NI
  - https://ja.wikipedia.org/wiki/CLMUL_instruction_set
- wikipedia
 - https://ja.wikipedia.org/wiki/Advanced_Encryption_Standard

### DES$B$H(BAES$B$N5;=QE*$J0c$$$K$D$$$F(B
DES$B$H(BAES$B$NHf3S$r5-=R$9$k!#(B
- $B80D9(B
  - DES: 56bit
  - AES: 128/192/256bit$B$+$iA*Br2DG=(B
- $B%V%m%C%/D9(B
  - DES: 64bit
  - AES: 128bit
- $B%i%&%s%I?t(B
  - DES: 16
  - AES: 10, 12, 14($B80D9$K$h$k(B)
- $B9=B$(B
  - DES: $B%U%!%$%9%F%k9=B$(B
    - $BF~NO$5$l$?%G!<%?$r>e2<(B32bit$B$:$D$KJ,$1$F!"$=$l$KBP$7$F(B16$BCJ$N0E9f2==hM}$r7+$jJV$7E,MQ$9$k!#(B
    - $B;qNA(B: http://www.atmarkit.co.jp/ait/articles/1505/21/news030.html
  - AES: SPN$B9=B$(B(Substitution Permutation Network)
    - $BF~NO$5$l$?%G!<%?$KBP$7$FF1$8$h$&$J=hM}$r2?2s$+7+$jJV$7E,MQ$9$k!#(B




