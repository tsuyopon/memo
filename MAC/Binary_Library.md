# バイナリ・ライブラリについて
MAC OSではELFではなくMach-Oと呼ばれるバイナリ形式になっている。
ただし、セクション名などはELFに似通った名前が存在している。


# 詳細

### Linuxでの/optなどの代替のインストール先
- https://apple.stackexchange.com/questions/119230/what-is-standard-for-os-x-filesystem-e-g-opt-vs-usr

### lddが使えない
MACではlddが使えない。そのためにotoolコマンドを利用します。
```
$ which curl
/usr/bin/curl
$ otool -L /usr/bin/curl
/usr/bin/curl:
    /usr/lib/libcurl.4.dylib (compatibility version 7.0.0, current version 8.0.0)
    /usr/lib/libz.1.dylib (compatibility version 1.0.0, current version 1.2.5)
    /usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1213.0.0)
```

### Machヘッダを見る
```
$ otool -h /bin/sleep 
/bin/sleep:
Mach header
      magic cputype cpusubtype  caps    filetype ncmds sizeofcmds      flags
 0xfeedfacf 16777223          3  0x80           2    17       1472 0x00200085
```

### textセクションを表示する
```
$ otool -t /bin/sleep 
/bin/sleep:
(__TEXT,__text) section
0000000100000ca0 55 48 89 e5 41 57 41 56 41 54 53 48 83 ec 20 48 
0000000100000cb0 89 f3 83 ff 03 75 1e 48 8b 73 08 48 8d 3d c6 02 
0000000100000cc0 00 00 e8 c3 01 00 00 85 c0 0f 85 95 00 00 00 48 
0000000100000cd0 83 c3 10 eb 0d 83 ff 02 0f 85 86 00 00 00 48 83 
0000000100000ce0 c3 08 48 8b 1b 48 ff c3 4c 8b 35 21 03 00 00 41 
...
```

### スタティックリンクについて
MAC OSではスタティックリンクをサポートしていないらしい。

### バイナリのセクションを確認する
```
$ otool -l /bin/sleep 
/bin/sleep:
Load command 0
      cmd LC_SEGMENT_64
  cmdsize 72
  segname __PAGEZERO
   vmaddr 0x0000000000000000
   vmsize 0x0000000100000000
  fileoff 0
 filesize 0
  maxprot 0x00000000
 initprot 0x00000000
   nsects 0
    flags 0x0
Load command 1
      cmd LC_SEGMENT_64
  cmdsize 632
  segname __TEXT
   vmaddr 0x0000000100000000
   vmsize 0x0000000000001000
  fileoff 0
 filesize 4096
  maxprot 0x00000007
 initprot 0x00000005
   nsects 7
    flags 0x0
Section
  sectname __text
   segname __TEXT
      addr 0x0000000100000ca0
      size 0x00000000000001de
    offset 3232
     align 2^0 (1)
    reloff 0
    nreloc 0
     flags 0x80000400
 reserved1 0
 reserved2 0
Section
  sectname __stubs
   segname __TEXT
      addr 0x0000000100000e7e
      size 0x000000000000001e
    offset 3710
     align 2^1 (2)
    reloff 0
    nreloc 0
     flags 0x80000408
 reserved1 0 (index into indirect symbol table)
 reserved2 6 (size of stubs)
Section
  sectname __stub_helper
   segname __TEXT
      addr 0x0000000100000e9c
      size 0x0000000000000042
    offset 3740
     align 2^2 (4)
    reloff 0
    nreloc 0
     flags 0x80000400
 reserved1 0
 reserved2 0
Section
  sectname __const
   segname __TEXT
      addr 0x0000000100000ee0
      size 0x00000000000000a8
    offset 3808
     align 2^4 (16)
    reloff 0
    nreloc 0
     flags 0x00000000
 reserved1 0
 reserved2 0
Section
  sectname __cstring
   segname __TEXT
      addr 0x0000000100000f88
      size 0x0000000000000003
    offset 3976
     align 2^0 (1)
    reloff 0
    nreloc 0
     flags 0x00000002
 reserved1 0
 reserved2 0
Section
  sectname __unwind_info
   segname __TEXT
      addr 0x0000000100000f8c
      size 0x0000000000000050
    offset 3980
     align 2^2 (4)
    reloff 0
    nreloc 0
     flags 0x00000000
 reserved1 0
 reserved2 0
Section
  sectname __eh_frame
   segname __TEXT
      addr 0x0000000100000fe0
      size 0x0000000000000018
    offset 4064
     align 2^3 (8)
    reloff 0
    nreloc 0
     flags 0x00000000
 reserved1 0
 reserved2 0
Load command 2
      cmd LC_SEGMENT_64
  cmdsize 312
  segname __DATA
   vmaddr 0x0000000100001000
   vmsize 0x0000000000001000
  fileoff 4096
 filesize 4096
  maxprot 0x00000007
 initprot 0x00000003
   nsects 3
    flags 0x0
Section
  sectname __nl_symbol_ptr
   segname __DATA
      addr 0x0000000100001000
      size 0x0000000000000010
    offset 4096
     align 2^3 (8)
    reloff 0
    nreloc 0
     flags 0x00000006
 reserved1 5 (index into indirect symbol table)
 reserved2 0
Section
  sectname __got
   segname __DATA
      addr 0x0000000100001010
      size 0x0000000000000008
    offset 4112
     align 2^3 (8)
    reloff 0
    nreloc 0
     flags 0x00000006
 reserved1 7 (index into indirect symbol table)
 reserved2 0
Section
  sectname __la_symbol_ptr
   segname __DATA
      addr 0x0000000100001018
      size 0x0000000000000028
    offset 4120
     align 2^3 (8)
    reloff 0
    nreloc 0
     flags 0x00000007
 reserved1 8 (index into indirect symbol table)
 reserved2 0
Load command 3
      cmd LC_SEGMENT_64
  cmdsize 72
  segname __LINKEDIT
   vmaddr 0x0000000100002000
   vmsize 0x0000000000002000
  fileoff 8192
 filesize 5824
  maxprot 0x00000007
 initprot 0x00000001
   nsects 0
    flags 0x0
Load command 4
            cmd LC_DYLD_INFO_ONLY
        cmdsize 48
     rebase_off 8192
    rebase_size 8
       bind_off 8200
      bind_size 56
  weak_bind_off 0
 weak_bind_size 0
  lazy_bind_off 8256
 lazy_bind_size 80
     export_off 8336
    export_size 32
Load command 5
     cmd LC_SYMTAB
 cmdsize 24
  symoff 8400
   nsyms 9
  stroff 8596
 strsize 128
Load command 6
            cmd LC_DYSYMTAB
        cmdsize 80
      ilocalsym 0
      nlocalsym 1
     iextdefsym 1
     nextdefsym 1
      iundefsym 2
      nundefsym 7
         tocoff 0
           ntoc 0
      modtaboff 0
        nmodtab 0
   extrefsymoff 0
    nextrefsyms 0
 indirectsymoff 8544
  nindirectsyms 13
      extreloff 0
        nextrel 0
      locreloff 0
        nlocrel 0
Load command 7
          cmd LC_LOAD_DYLINKER
      cmdsize 32
         name /usr/lib/dyld (offset 12)
Load command 8
     cmd LC_UUID
 cmdsize 24
    uuid F39B90BD-F41E-36B2-A366-857BAFC766EA
Load command 9
      cmd LC_VERSION_MIN_MACOSX
  cmdsize 16
  version 10.10
      sdk 10.10
Load command 10
      cmd LC_SOURCE_VERSION
  cmdsize 16
  version 179.0
Load command 11
       cmd LC_MAIN
   cmdsize 24
  entryoff 3232
 stacksize 0
Load command 12
          cmd LC_LOAD_DYLIB
      cmdsize 56
         name /usr/lib/libSystem.B.dylib (offset 24)
   time stamp 2 Thu Jan  1 09:00:02 1970
      current version 1213.0.0
compatibility version 1.0.0
Load command 13
      cmd LC_FUNCTION_STARTS
  cmdsize 16
  dataoff 8368
 datasize 8
Load command 14
      cmd LC_DATA_IN_CODE
  cmdsize 16
  dataoff 8376
 datasize 0
Load command 15
      cmd LC_DYLIB_CODE_SIGN_DRS
  cmdsize 16
  dataoff 8376
 datasize 24
Load command 16
      cmd LC_CODE_SIGNATURE
  cmdsize 16
  dataoff 8736
 datasize 5280
```



# TODO(要整理)
- How to copy (and relink) binaries on OSX using otool and install_name_tool
  - http://thecourtsofchaos.com/2013/09/16/how-to-copy-and-relink-binaries-on-osx/
- Mac OS Xでライブラリの設定変更について
  - https://qiita.com/itoru257/items/d36b4e3908a39bfbbb18
