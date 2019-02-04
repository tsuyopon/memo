# Advanced Encryption Standard(AES)
AES$B$O%*%j%8%J%k%M!<%`$H$7$F(BRijndael$B$H$7$FCN$i$l$F$$$^$9!#(B
$B3+H/<T$O%Y%k%.!<$N0E9f3X<T!V(BJoan Daemen$B!W$H!V(BVincent Rijmen$B!W$G$"$j!"$3$NFs?M$NL>>-$+$iL>IU$1$i$l$?$H$5$l$F$$$k!#(B
NIST$B$N%3%s%Z$K$h$C$FA*Dj$5$l$?0E9f$G$9!#(B

AES(2001$BG/H/I=(B)$B$O%"%a%j%+@/I\$K$h$C$F:NMQ$5$l!"8=:_$G$O(BDES(1977$BG/H/I=(B)$B$K<h$C$FBe$o$C$F$$$^$9!#(B3DES$B$h$j$bAa$/$F0BA4$i$7$$$G$9!#(B
$B6&DL800E9fJ}<0(B($B%V%m%C%/7?(B)$B$H$7$F0E9f2=5Z$SJ#9g$7$^$9!#(B

$B6&DL800E9f$K$O%V%m%C%/7?$NB>$K$b%9%H%j!<%`7?$H$7$F(BCHACHA20$B$,B8:_$7$^$9!#%V%m%C%/7?$O<!$N#2$D$N<oN`$KJ,N`$5$l$^$9!#(B
- Feistel$B9=B$(B
  - DES, Camellia
- SPN$B9=B$(B
  - AES

AES$B$O80D9$K1~$8$F#3<oN`$N%P%j%(!<%7%g%s$,B8:_$7$^$9!#8=;~E@$G$O(BAES-128$B$G$b==J,$K0BA4$H9M$($i$l$F$$$^$9!#(B
AES$B$G$O%V%m%C%/D9$O>o$K(B128bit$B$G8GDj$H$J$j$^$9!#(B
```
AES$B5,3J(B  $B80D9(B     $B%V%m%C%/D9(B  $B%i%&%s%I?t(B
AES-128   128bit   128bit      10$BCJ(B
AES-192   192bit   128bit      12$BCJ(B
AES-256   256bit   128bit      14$BCJ(B
```

AES$B$N@($$$H$3$m$O!"(BSubBytes,ShiftRows,MixColumns $B$=$l$>$l$N=hM}$r%S%C%H1i;;$@$1$G<B8=$G$-$k$3$H$K$"$k$N$G!"Aa$/%O!<%I%&%'%"$N<BAu$b4JC1(B

TODO: $B%V%m%C%/D9$h$j$bD9$$80D9$r;H$&$N$O$J$<(B?


# AES$B%"%k%4%j%:%`35MW(B
$B0J2<$O(BAES-128$B$N>l9g$N(B10$B%i%&%s%I$NNc$@$,(BSubBytes,ShiftRows,MixColumn, AddRoundKey$B$N(B4$B$D$r(B10$B2sO"B3$G2s$;$P$$$$$@$1$J$o$1$G$O$J$$!#(B
$B:G=i$K(BAddRoundKey$B$r<B;\$7$F$+$i!"(B9$B%i%&%s%I=hM}$r<B9T$7$F!":G8e$K(BShiftRows,MixColumn, AddRoundKey$B$r<B9T$9$k$3$H$G(B10$B%i%&%s%I$H$7$F07$o$l$k!#(B
```
AddRoundKey

int roundSum = 10;                    // AES-128$B$@$H(B10
for (round = 1; round < roundSum - 1; round++){
	SubBytes
	ShiftRows
	MixColumns
	AddRoundKey
}

SubBytes
ShiftRows
AddRoundKey
```

$BNc$($P!"(BIntel-CPU$B$G$O(BAES-NI$B$H$$$&L?Na$rMQ$$$k;v$K$h$C$F!"(BSubBytes, ShiftRows, MixColumns, AddRoundKey$B$H$$$&(B1$B%i%&%s%I$N=hM}$r(B1$BL?Na$G<B9T$G$-$k$h$&$K$J$k!#(B

# $BF~NO$H=PNO(B

### Encrypt
- $BF~NO(B: $B80(B($B80D9$b7hDj$9$k(B)$B!"J?J8(B
- $B=PNO(B: $B0E9fJ8(B

### Decrypt
- $BF~NO(B: $B80(B($B80D9$b7hDj$9$k(B)$B!"0E9fJ8(B
- $B=PNO(B: $BJ?J8(B


# $B<BAu%5%s%W%k(B
- https://github.com/dhuertas/AES/blob/master/aes.c
  - C$B8@8l$N<BAu%5%s%W%k(B
- https://en.wikipedia.org/wiki/Advanced_Encryption_Standard
  - Python$B$K$*$1$k(BAES$B$N<BAu$G!"$o$:$+(B200$B9TDxEY$J$N$GM}2r$7$d$9$$(B
  - $B35MWM}2r$J$I$O$3$l$,0lHV$o$+$j$d$9$$5$$,$9$k(B

# $B;29M(BURL
- Wikipedia: Advanced Encryption Standard
  - https://en.wikipedia.org/wiki/Advanced_Encryption_Standard

# SeeAlso
- AES$B$N0l<!>pJs(B
  - http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf
- https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines/archived-crypto-projects/aes-development

