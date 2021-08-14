# 概要
go toolコマンドで出来ることについてまとめる

以下のドキュメントにcmd一覧への各種リンクがあるので参考にすると良い
- https://pkg.go.dev/cmd

# 詳細

### go toolのオプションの確認
引数なしでgo toolと実行するとオプションが確認できます。
```
$ go tool 
addr2line
api
asm
buildid
cgo
compile
cover
dist
doc
fix
link
nm
objdump
pack
pprof
test2json
trace
vet
```

たとえば、nmのオプションを確認したければオプションまでを指定することでヘルプページを確認することができます。
```
$ go tool nm
usage: go tool nm [options] file...
  -n
      an alias for -sort address (numeric),
      for compatibility with other nm commands
  -size
      print symbol size in decimal between address and type
  -sort {address,name,none,size}
      sort output in the given order (default name)
      size orders from largest to smallest
  -type
      print symbol type after name
```


### バイナリの情報をダンプする(go tool objdump)
アセンブラなども表示してくれます。非常に出力量が多いので本当にごく一部のみを記載
```
$ go tool objdump main
```

### シンボル情報とアドレスを表示する(go tool nm)

```
$ go tool nm main | grep gin
 136fdf0 T encoding/gob.(*Decoder).getDecEnginePtr
 16e1400 R encoding/gob.(*Decoder).getDecEnginePtr.stkobj
 1370070 T encoding/gob.(*Decoder).getIgnoreEnginePtr
 13787e0 T encoding/gob.buildEncEngine
 16f4ba0 R encoding/gob.buildEncEngine.stkobj
 13786c0 T encoding/gob.getEncEngine
 16ec120 R encoding/gob.getEncEngine.stkobj
 13087f0 T encoding/json.stateBeginString
(省略)
```

シンボルは以下のドキュメントに定義されている。
- https://pkg.go.dev/cmd/nm@go1.16.7
```
T   text (code) segment symbol
t   static text segment symbol
R   read-only data segment symbol
r   static read-only data segment symbol
D   data segment symbol
d   static data segment symbol
B   bss segment symbol
b   static bss segment symbol
C   constant address
U   referenced but undefined symbol
```

オプションもあるので確認してみる。
nオプションは-sort addressと同じなので、アドレス順にそーとしている
```
$ go tool nm -n main | tail
 1ad74a0 B runtime.gcController
 1ad7540 B runtime.fwdSig
 1ad7640 B runtime.sigprofCallers
 1ad7740 B vendor/golang.org/x/text/secure/bidirule.asciiTable
 1ad7840 B runtime.printBacklog
 1ad7a40 B runtime.zeroVal
 1ad7e40 B crypto/des.feistelBox
 1ad8640 B runtime.memstats
 1ad9da8 B runtime.end
 1ad9da8 B runtime.enoptrbss
(snip)
```

sizeオプションはシンボルのサイズを出力をしてくれるようです。
```
$ go tool nm -size main | tail
 1a7c9a0      12512 D vendor/golang.org/x/text/unicode/norm.nfcValues
 1aa8d28          8 B vendor/golang.org/x/text/unicode/norm.nfkcData
 1a78be0       2816 D vendor/golang.org/x/text/unicode/norm.nfkcIndex
 1aaaf00         64 B vendor/golang.org/x/text/unicode/norm.nfkcSparse
 1a9b4e0        448 D vendor/golang.org/x/text/unicode/norm.nfkcSparseOffset
 1a796e0       3520 D vendor/golang.org/x/text/unicode/norm.nfkcSparseValues
 1a81ae0      12032 D vendor/golang.org/x/text/unicode/norm.nfkcValues
 1269090       1456 T vendor/golang.org/x/text/unicode/norm.patchTail
 1aa8d30         16 B vendor/golang.org/x/text/unicode/norm.recompMap
 1ad6c00         48 B vendor/golang.org/x/text/unicode/norm.recompMapOnce
```

名前の順番でsortする
```
$ go tool nm -sort name main | tail
 1a7c9a0 D vendor/golang.org/x/text/unicode/norm.nfcValues
 1aa8d28 B vendor/golang.org/x/text/unicode/norm.nfkcData
 1a78be0 D vendor/golang.org/x/text/unicode/norm.nfkcIndex
 1aaaf00 B vendor/golang.org/x/text/unicode/norm.nfkcSparse
 1a9b4e0 D vendor/golang.org/x/text/unicode/norm.nfkcSparseOffset
 1a796e0 D vendor/golang.org/x/text/unicode/norm.nfkcSparseValues
 1a81ae0 D vendor/golang.org/x/text/unicode/norm.nfkcValues
 1269090 T vendor/golang.org/x/text/unicode/norm.patchTail
 1aa8d30 B vendor/golang.org/x/text/unicode/norm.recompMap
 1ad6c00 B vendor/golang.org/x/text/unicode/norm.recompMapOnce
```

サイズでsortする。sizeオプションを付与しないとサイズを表示してくれないので、以下の例では併せて指定しています。
```
$ go tool nm -sort size -size main
           16781312 U _close
           16781312 U _write
...
 1724a20    3380831 R runtime.pclntab
 1724a20    3380831 R runtime.esymtab
 1724a20    3380831 R runtime.symtab
 1724a20    3380831 R runtime.eitablink
 14ffee0    1102584 R runtime.rodata
 14ffee0    1102584 R type.*
 14ffee0    1102584 R runtime.types
(snip)
```

# 参考資料
- https://pkg.go.dev/cmd

