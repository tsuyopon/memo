# 概要
readelfとobjdumpと似たコマンドが２つあってわかりにくいので、やりたいことベースにTIPSとしてまとめます。

# 詳細

### バイナリのABI情報を取得したい
```
 $ readelf -n clientSSL 

Displaying notes found at file offset 0x00000254 with length 0x00000020:
  Owner                 Data size	Description
  GNU                  0x00000010	NT_GNU_ABI_TAG (ABI version tag)
    OS: Linux, ABI: 2.6.32

Displaying notes found at file offset 0x00000274 with length 0x00000024:
  Owner                 Data size	Description
  GNU                  0x00000014	NT_GNU_BUILD_ID (unique build ID bitstring)
    Build ID: 741536a2b8fa5b2003237f5acdbc96bca4c669c1
```

以下のオプションでもABIやABI Version情報が出力されます。
```
$ readelf -h /bin/ls
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00  
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0   
  Type:                              EXEC (Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1 
  Entry point address:               0x404b48
  Start of program headers:          64 (bytes into file)
  Start of section headers:          115736 (bytes into file)
  Flags:                             0x0 
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         9   
  Size of section headers:           64 (bytes)
  Number of section headers:         30  
  Section header string table index: 29
```

### コンパイル時のGCCバージョンを取得する
.commentセクションから取得することが可能です。
```
$ readelf -p .comment clientSSL 

String dump of section '.comment':
  [     0]  GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-36)
```

```
$ objdump -s --section .comment clientSSL 

clientSSL:     file format elf64-x86-64

Contents of section .comment:
 0000 4743433a 2028474e 55292034 2e382e35  GCC: (GNU) 4.8.5
 0010 20323031 35303632 33202852 65642048   20150623 (Red H
 0020 61742034 2e382e35 2d333629 00        at 4.8.5-36). 
```


### コンパイル情報を取得したい
gccコンパイラに指定されたコンパイル時のオプション、コンパイル時のファイル名、コンパイル時のディレクトリパスの情報などを表示します。

```
$ readelf -wi clientSSL  | head -20
Contents of the .debug_info section:

  Compilation Unit @ offset 0x0:
   Length:        0x49d8 (32-bit)
   Version:       4
   Abbrev Offset: 0x0
   Pointer Size:  8
 <0><b>: Abbrev Number: 1 (DW_TAG_compile_unit)
    <c>   DW_AT_producer    : (indirect string, offset: 0x10fa): GNU C 4.8.5 20150623 (Red Hat 4.8.5-36) -mtune=generic -march=x86-64 -g -O0
    <10>   DW_AT_language    : 1	(ANSI C)
    <11>   DW_AT_name        : (indirect string, offset: 0x3e): client_SSL.c
    <15>   DW_AT_comp_dir    : (indirect string, offset: 0x12e1): /home/tsuyoshi/git/cpp/openssl/simple
    <19>   DW_AT_low_pc      : 0x400ead
    <21>   DW_AT_high_pc     : 0x28b
    <29>   DW_AT_stmt_list   : 0x0
 <1><2d>: Abbrev Number: 2 (DW_TAG_base_type)
    <2e>   DW_AT_byte_size   : 1
    <2f>   DW_AT_encoding    : 8	(unsigned char)
    <30>   DW_AT_name        : (indirect string, offset: 0x917): unsigned char
 <1><34>: Abbrev Number: 2 (DW_TAG_base_type)  	
```


### gccのオプション時にセクション情報としてgccコンパイルオプションを埋め込んでしまいたい。

次のオプションを付与してコンパイルすることで
```
-frecord-gcc-switches
```

.GCC.command.lineというセクションにオプション情報が出力されるようです。
```
$ readelf -p .GCC.command.line  clientSSL 

String dump of section '.GCC.command.line':
  [     0]  -I /opt/openssl-1.1.1/include
  [    1e]  client_SSL.c
  [    2b]  -mtune=generic
  [    3a]  -march=x86-64
  [    48]  -g
  [    4b]  -O0
  [    4f]  -frecord-gcc-switches
```

- 参考
  - https://stackoverflow.com/questions/12112338/get-the-compiler-options-from-a-compiled-executable


