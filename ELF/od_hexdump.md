# 概要
od, hexdumpコマンドについてまとめる

# 詳細

### メモリ内部を直接読む
```
$ od -x /dev/mem
```

### odはデフォルトで8進数の出力を行う。
```
$ od a.out  | head -3
0000000 042577 043114 000401 000001 000000 000000 000000 000000
0000020 000002 000003 000001 000000 101170 004004 000064 000000
0000040 016464 000000 000000 000000 000064 000040 000006 000050
```

### -xオプションで16進数を表示することができる。
```
$ od -x a.out | head -3
0000000 457f 464c 0101 0001 0000 0000 0000 0000
0000020 0002 0003 0001 0000 8278 0804 0034 0000
0000040 1d34 0000 0000 0000 0034 0020 0006 0028
```

### -dオプションで10進数表示をすることができる。
```
$ od -d a.out | head -3
0000000 17791 17996   257     1     0     0     0     0
0000020     2     3     1     0 33400  2052    52     0
0000040  7476     0     0     0    52    32     6    40
```

### ASCII文字列表示も調べたい場合には -t x1zとzを付ける。
```
$ od -t x1z -A x a.out  | more
000000 7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00  >.ELF............<
000010 02 00 03 00 01 00 00 00 78 82 04 08 34 00 00 00  >........x...4...<
(中略)
0001a0 00 6c 69 62 63 2e 73 6f 2e 36 00 70 72 69 6e 74  >.libc.so.6.print<
0001b0 66 00 5f 49 4f 5f 73 74 64 69 6e 5f 75 73 65 64  >f._IO_stdin_used<
0001c0 00 5f 5f 6c 69 62 63 5f 73 74 61 72 74 5f 6d 61  >.__libc_start_ma<
(以下略)
```

### 16進数とテキストデータを同一列で表示する
-tx1でzが付与されていないのでこの場合上と異なり行で表示する。
```
$ cat yum.md  | od -tx1 -a | tail -10
          s   i   t   e   s   /   d   e   f   a   u   l   t   /   f   i
0005160  6c  65  73  2f  61  74  74  61  63  68  6d  65  6e  74  73  2f
          l   e   s   /   a   t   t   a   c   h   m   e   n   t   s   /
0005200  72  68  5f  79  75  6d  5f  63  68  65  61  74  73  68  65  65
          r   h   _   y   u   m   _   c   h   e   a   t   s   h   e   e
0005220  74  5f  31  32  31  34  5f  6a  63  73  5f  70  72  69  6e  74
          t   _   1   2   1   4   _   j   c   s   _   p   r   i   n   t
0005240  2d  6a  61  2e  70  64  66  0a  20  0a  0a
          -   j   a   .   p   d   f  nl  sp  nl  nl
```

### 16進数を即座に取得する
Cオプションを付与すると標準的な 16進数 + ASCII での表示を行います。
```
$ echo "abcdefghijklmnopabcdefghijklmnopqrstu" | hexdump -C
00000000  61 62 63 64 65 66 67 68  69 6a 6b 6c 6d 6e 6f 70  |abcdefghijklmnop|
*
00000020  71 72 73 74 75 0a                                 |qrstu.|
00000026
```