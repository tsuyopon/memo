# Makefile$B$N4X?t$K$D$$$F(B

$B<+J,$NJ}$G$b<j$r;H$C$F$+$i5-:\$7$F$$$k$,!"$[$H$s$I$3$A$i$r;29M$K5-:\$7$?$b$N$H$J$C$F$$$^$9!#(B
- Qiita: Makefile$B$N4X?t(B
  - https://qiita.com/chibi929/items/b8c5f36434d5d3fbfa4a

$B4X?t$N8F$S=P$7$O<!$N$$$:$l$+$NJ}K!$K$h$C$F8F$S=P$9$3$H$,$G$-$^$9!#(B
```
$($B4X?t(B $B0z?t(B)
$B$^$?$O(B
${$B4X?t(B $B0z?t(B}
```

# $BJ8;zNs4XO"4X?t(B
## filter

- $B=q<0(B
  - TEXT$B$NCf$+$i(BPATTERN$B$NJ8;zNs$K0lCW$9$kMWAG$r<hF@$9$k!#(B
```
$(filter PATTERN...,TEXT)
```
- $B;H$$J}(B
```
VAR := hoge.h hoge.cpp hogera.h hogera.cpp

.PHONY: all
all:
	@echo "$(filter %.cpp,$(VAR))"
```
- $B<B9T7k2L(B
```
$ make
hoge.cpp hogera.cpp
```

## filter-out
- $B=q<0(B
  - filter$B$N5U$r9T$&(B
  - TEXT$B$NCf$+$i(BPATTERN$B$NJ8;zNs$K0lCW$7$J$$MWAG$r<hF@$9$k!#(B
```
$(filter-out PATTERN...,TEXT)
```
- $B;H$$J}(B
```
VAR := hoge.h hoge.cpp hogera.h hogera.cpp

.PHONY: all
all:
	@echo "$(filter-out %.cpp,$(VAR))"
```
- $B<B9T7k2L(B
```
$ make
hoge.h hogera.h
```

## findstring
- $B=q<0(B
  - IN$BFb$K(BFIND$B$NJ8;z$,4^$^$l$F$$$kMWAG$r<hF@$9$k!#(B
```
$(findstring FIND,IN)
```
- $B;H$$J}(B
```
VAR := abc def ghi

.PHONY: all
all:
	@echo "$(findstring bc,$(VAR))"
```
- $B<B9T7k2L(B
```
$ make
bc
```

## firstword
- $B=q<0(B
  - NAMES$BFb$N:G=i$NMWAG$r<hF@$9$k(B
```
$(firstword NAMES...)
```
- $B;H$$J}(B
```
VAR := abc def ghi

.PHONY: all
all:
	@echo "$(firstword $(VAR))"
```
- $B<B9T7k2L(B
```
$ make
abc
```

## lastword
- $B=q<0(B
  - NAMES$BFb$N:G8e$NMWAG$r<hF@$9$k!#(B
  - firstword$B$N5U$N=hM}$r9T$&(B
```
$(lastword NAMES...)
```
- $B;H$$J}(B
```
VAR := abc def ghi

.PHONY: all
all:
	@echo "$(lastword $(VAR))"
```
- $B<B9T7k2L(B
```
$ make
ghi
```

## patsubst
- $B=q<0(B
  - TEXT$BFb$+$i(BPATTERN$B$K%^%C%A$7$?CM$r(BREPLACEMENT$B$KCV$-49$($r9T$&!#(B
```
$(patsubst PATTERN,REPLACEMENT,TEXT)
```
- $B;H$$J}(B
```
VAR := hoge.cpp hogera.cpp .cppfile.o cpp.cpp cpp.x

.PHONY: all
all:
	@echo "$(patsubst %.cpp,%.o,$(VAR))"
```
- $B<B9T7k2L(B
```
$ make 
hoge.o hogera.o .cppfile.o cpp.o cpp.x
```

## subst
- $B=q<0(B
  - TEXT$BFb$+$i(BFROM$B$K%^%C%A$7$?CM$r(BTO$B$KCV$-49$($k!#(B
  - patsubst$B$N%Q%?!<%s%^%C%A$rMxMQ$7$J$$%P!<%8%g%s(B 
```
$(subst FROM,TO,TEXT)
```
- $B;H$$J}(B
```
VAR := hoge.cpp hogera.cpp .cpp.x

.PHONY: all
all:
	@echo "$(subst .cpp,.o,$(VAR))"
```
- $B<B9T7k2L(B
```
$ make
hoge.o hogera.o .o.x
```

## sort
- $B=q<0(B
  - LIST$B$N3F<oMWAG$r%=!<%H$9$k(B
```
$(sort LIST)
```
- $B;H$$J}(B
```
VAR := eee ddd bbb aa ddc aaa

.PHONY: all
all:
	@echo "$(sort $(VAR))"
```
- $B<B9T7k2L(B
```
$ make
aa aaa bbb ddc ddd eee
```

## strip
- $B=q<0(B
  - STRING$B$NL5BL$J6uGrItJ,$r<h$j=|$/(B
```
$(strip STRING)
```
- $B;H$$J}(B
```
VAR := a b    c    d

.PHONY: all
all:
	@echo "$(strip $(VAR))"
```
- $B<B9T7k2L(B
```
$ make
a b c d
```

## word
- $B=q<0(B
  - TEXT$BFb$N(BN$BHVL\$NMWAG$r<hF@$9$k(B
```
$(word N,TEXT)
```
- $B;H$$J}(B
```
VAR := abc def ghi jkl mno pqr

.PHONY: all
all:
	@echo "$(word 5,$(VAR))"
```
- $B<B9T7k2L(B
```
$ make
mno
```

## wordlist
- $B=q<0(B
  - TEXT$BFb$r(BSTART_NUM$B$G;XDj$5$l$?HV9f$+$i(BEND_NUM$B$G;XDj$5$l$?HV9f$^$G$NMWAG$r<hF@$9$k(B
```
$(wordlist START_NUM,END_NUM,TEXT)
```
- $B;H$$J}(B
```
VAR := abc def ghi jkl mno pqr

.PHONY: all
all:
	@echo "$(wordlist 4,5,$(VAR))"
```
- $B<B9T7k2L(B
```
$ make
jkl mno
```

## words
- $B=q<0(B
  - TEXT$BFb$NMWAG?t$r<hF@$9$k(B
```
$(words TEXT)
```
- $B;H$$J}(B
```
VAR := abc def ghi jkl mno pqr

.PHONY: all
all:
	@echo "$(words $(VAR))"
```
- $B<B9T7k2L(B
```
$ make
6
```

# MEMO

## sample for added
- $B=q<0(B
  - TBD
```
```
- $B;H$$J}(B
```
```
- $B<B9T7k2L(B
```
```

# $B;29M(BURL
- Makefile$B8x<0%^%K%e%"%k(B
  - https://www.gnu.org/software/make/manual/
- Qiita: Makefile$B$N4X?t(B
  - https://qiita.com/chibi929/items/b8c5f36434d5d3fbfa4a
- GNU Make
  - http://www.ecoop.net/coop/translated/GNUMake3.77/make_8.jp.html
