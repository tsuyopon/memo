# 概要
opensslコマンドのdebug関連のTIPS

# 詳細
```
$ openssl s_client -connect www.yahoo.co.jp:443 -msg
CONNECTED(00000003)
>>> TLS 1.2  [length 0005]
    16 03 01 01 2c
>>> TLS 1.2 Handshake [length 012c], ClientHello
    01 00 01 28 03 03 65 95 a6 d7 32 de d7 03 47 9c
    56 11 ea 50 78 f9 aa 00 d8 54 77 fd 9f 31 1c 1c
    1b e1 3c 7d b7 1a 00 00 aa c0 30 c0 2c c0 28 c0
    24 c0 14 c0 0a 00 a5 00 a3 00 a1 00 9f 00 6b 00
    6a 00 69 00 68 00 39 00 38 00 37 00 36 00 88 00
    87 00 86 00 85 c0 32 c0 2e c0 2a c0 26 c0 0f c0
    05 00 9d 00 3d 00 35 00 84 c0 2f c0 2b c0 27 c0
    23 c0 13 c0 09 00 a4 00 a2 00 a0 00 9e 00 67 00
    40 00 3f 00 3e 00 33 00 32 00 31 00 30 00 9a 00
    99 00 98 00 97 00 45 00 44 00 43 00 42 c0 31 c0
    2d c0 29 c0 25 c0 0e c0 04 00 9c 00 3c 00 2f 00
    96 00 41 c0 11 c0 07 c0 0c c0 02 00 05 00 04 c0
    12 c0 08 00 16 00 13 00 10 00 0d c0 0d c0 03 00
    0a 00 ff 01 00 00 55 00 0b 00 04 03 00 01 02 00
    0a 00 1c 00 1a 00 17 00 19 00 1c 00 1b 00 18 00
    1a 00 16 00 0e 00 0d 00 0b 00 0c 00 09 00 0a 00
    23 00 00 00 0d 00 20 00 1e 06 01 06 02 06 03 05
    01 05 02 05 03 04 01 04 02 04 03 03 01 03 02 03
    03 02 01 02 02 02 03 00 0f 00 01 01
<<< ??? [length 0005]
    16 03 03 00 3d
<<< TLS 1.2 Handshake [length 003d], ServerHello
    02 00 00 39 03 03 5c eb b8 05 c9 79 ee 83 cb 1d
    66 bb 5a e4 5b 8d e4 06 86 ee a1 3a 2e 1f 44 4f
    57 4e 47 52 44 01 00 c0 2f 00 00 11 ff 01 00 01
    00 00 0b 00 04 03 00 01 02 00 23 00 00
<<< ??? [length 0005]
    16 03 03 18 30
<<< TLS 1.2 Handshake [length 1830], Certificate
    0b 00 18 2c 00 18 29 00 0e b8 30 82 0e b4 30 82
    0d 9c a0 03 02 01 02 02 14 36 2a b1 30 14 0a 46
    b4 c4 90 c8 9d 64 a2 8a 70 67 6a 1e 90 30 0d 06
    09 2a 86 48 86 f7 0d 01 01 0b 05 00 30 5e 31 0b
    30 09 06 03 55 04 06 13 02 4a 50 31 23 30 21 06
    03 55 04 0a 13 1a 43 79 62 65 72 74 72 75 73 74
    20 4a 61 70 61 6e 20 43 6f 2e 2c 20 4c 74 64 2e
    31 2a 30 28 06 03 55 04 03 13 21 43 79 62 65 72
    74 72 75 73 74 20 4a 61 70 61 6e 20 53 75 72 65
    53 65 72 76 65 72 20 43 41 20 47 34 30 1e 17 0d
    32 32 30 34 30 36 31 30 30 31 32 37 5a 17 0d 32
    33 30 35 30 35 31 34 35 39 30 30 5a 30 71 31 0b
    30 09 06 03 55 04 06 13 02 4a 50 31 0e 30 0c 06
    03 55 04 08 13 05 54 6f 6b 79 6f 31 13 30 11 06
    03 55 04 07 13 0a 43 68 69 79 6f 64 61 2d 6b 75
    31 20 30 1e 06 03 55 04 0a 13 17 59 61 68 6f 6f
    20 4a 61 70 61 6e 20 43 6f 72 70 6f 72 61 74 69
    6f 6e 31 1b 30 19 06 03 55 04 03 13 12 65 64 67
    65 30 31 2e 79 61 68 6f 6f 2e 63 6f 2e 6a 70 30
    82 01 22 30 0d 06 09 2a 86 48 86 f7 0d 01 01 01
    05 00 03 82 01 0f 00 30 82 01 0a 02 82 01 01 00
    f4 20 08 66 0e 73 65 87 14 26 24 b1 67 39 f6 80
    3d ba 93 4d e5 cf 4d f0 54 6c 3b 80 fa 13 e1 6b
    19 21 50 de 42 42 cb 7e 72 1f ba bc 6b 9d c0 cf
    10 de 0b f2 69 f2 57 e6 ac 18 02 3f 7d 91 43 ef
    05 dc 10 dc 42 5f 8a 59 7c bb fe 6a 62 59 8a a6
    c4 33 4a f8 69 c2 1e a8 3d d2 0a b3 60 29 d2 59
    c2 44 f7 7e e8 e7 50 78 18 b8 54 4c f1 08 a6 29
    78 dc 3f a2 fe c5 10 da e3 0f c5 06 9c 2a 3d 0a
    7e 2b d1 cc 07 df 47 12 c9 aa d7 e4 bc f6 04 53
    dc 9c f4 4b c9 89 af 80 43 3d 15 87 f7 e4 7b 37
    a3 2d b3 42 75 e7 c7 fa 16 74 c6 0b 1e 93 bb 7e
    df fe ee 71 7f 90 f0 a4 42 f9 b2 b6 e1 65 31 5b
    ac 3f f1 ec b6 86 91 e8 79 b6 11 72 a9 9f 76 33
    f7 a6 fc e4 06 bf 48 94 d2 04 c7 be 9a f2 57 5d
    04 cf 6f 3c 20 a7 fb 55 c9 18 8c d1 46 1f 23 a3
    b7 97 ae 8c 02 be 53 4d 07 31 d9 b3 9e 0e d1 09
    02 03 01 00 01 a3 82 0b 55 30 82 0b 51 30 0c 06
    03 55 1d 13 01 01 ff 04 02 30 00 30 66 06 03 55
    1d 20 04 5f 30 5d 30 51 06 09 2a 83 08 8c 9b 11
    01 17 01 30 44 30 42 06 08 2b 06 01 05 05 07 02
    01 16 36 68 74 74 70 73 3a 2f 2f 77 77 77 2e 63
    79 62 65 72 74 72 75 73 74 2e 6e 65 2e 6a 70 2f
    73 73 6c 2f 72 65 70 6f 73 69 74 6f 72 79 2f 69
    6e 64 65 78 2e 68 74 6d 6c 30 08 06 06 67 81 0c
    01 02 02 30 82 07 99 06 03 55 1d 11 04 82 07 90
    30 82 07 8c 82 12 65 64 67 65 30 31 2e 79 61 68
    6f 6f 2e 63 6f 2e 6a 70 82 0d 2a 2e 79 61 68 6f
    6f 2e 63 6f 2e 6a 70 82 11 2a 2e 61 6e 65 2e 79
    61 68 6f 6f 2e 63 6f 2e 6a 70 82 16 2a 2e 61 75
    63 74 69 6f 6e 73 2e 79 61 68 6f 6f 2e 63 6f 2e
    6a 70 82 0b 2a 2e 63 2e 79 69 6d 67 2e 6a 70 82
    18 2a 2e 63 68 69 65 62 75 6b 75 72 6f 2e 79 61
    68 6f 6f 2e 63 6f 2e 6a 70 82 15 2a 2e 63 6c 6f
    72 64 65 72 2e 79 61 68 6f 6f 2e 63 6f 2e 6a 70
    82 1c 2a 2e 65 61 73 74 2e 65 64 67 65 2e 73 74
    6f 72 61 67 65 2d 79 61 68 6f 6f 2e 6a 70 82 1f
    2a 2e 65 61 73 74 2e 65 64 67 65 2e 73 74 6f 72
    61 67 65 2d 79 61 68 6f 6f 62 6f 78 2e 6a 70 82
    17 2a 2e 65 64 67 65 2e 73 74 6f 72 61 67 65 2d
    79 61 68 6f 6f 2e 6a 70 82 15 2a 2e 66 69 6e 61
    6e 63 65 2e 79 61 68 6f 6f 2e 63 6f 2e 6a 70 82
    1e 2a 2e 67 6c 6f 62 61 6c 2e 65 64 67 65 2e 73
    74 6f 72 61 67 65 2d 79 61 68 6f 6f 2e 6a 70 82
    15 2a 2e 6c 69 73 74 69 6e 67 2e 79 61 68 6f 6f
    2e 63 6f 2e 6a 70 82 12 2a 2e 6c 6f 63 6f 2e 79
    61 68 6f 6f 2e 63 6f 2e 6a 70 82 12 2a 2e 6e 65
    77 73 2e 79 61 68 6f 6f 2e 63 6f 2e 6a 70 82 13
    2a 2e 6f 72 64 65 72 2e 79 61 68 6f 6f 2e 63 6f
    2e 6a 70 82 14 2a 2e 73 68 6f 70 70 69 6e 67 2e
    63 2e 79 69 6d 67 2e 6a 70 82 16 2a 2e 73 68 6f
    70 70 69 6e 67 2e 79 61 68 6f 6f 2e 63 6f 2e 6a
    70 82 13 2a 2e 73 74 6f 72 65 2e 79 61 68 6f 6f
    2e 63 6f 2e 6a 70 82 14 2a 2e 74 72 61 76 65 6c
    2e 79 61 68 6f 6f 2e 63 6f 2e 6a 70 82 1c 2a 2e
    77 65 73 74 2e 65 64 67 65 2e 73 74 6f 72 61 67
    65 2d 79 61 68 6f 6f 2e 6a 70 82 1f 2a 2e 77 65
    73 74 2e 65 64 67 65 2e 73 74 6f 72 61 67 65 2d
    79 61 68 6f 6f 62 6f 78 2e 6a 70 82 19 2a 2e 78
    6d 6c 2e 6c 69 73 74 69 6e 67 2e 79 61 68 6f 6f
    2e 63 6f 2e 6a 70 82 0f 2a 2e 79 61 68 6f 6f 2d
    6c 61 62 73 2e 6a 70 82 0e 2a 2e 79 61 68 6f 6f
    61 70 69 73 2e 6a 70 82 0d 2a 2e 79 61 68 6f 6f
    62 6f 78 2e 6a 70 82 09 2a 2e 79 69 6d 67 2e 6a
    70 82 0a 2a 2e 79 6a 74 61 67 2e 6a 70 82 13 2a
    2e 79 6a 74 61 67 2e 79 61 68 6f 6f 2e 63 6f 2e
    6a 70 82 13 61 64 64 2e 64 69 72 2e 79 61 68 6f
    6f 2e 63 6f 2e 6a 70 82 13 2a 2e 70 75 73 68 2e
    79 61 68 6f 6f 61 70 69 73 2e 6a 70 82 12 2a 2e
    67 79 61 6f 2e 79 61 68 6f 6f 2e 63 6f 2e 6a 70
    82 13 2a 2e 6e 65 77 73 2e 79 61 68 6f 6f 61 70
    69 73 2e 6a 70 82 15 2a 2e 73 65 61 72 63 68 2e
    79 61 68 6f 6f 61 70 69 73 2e 6a 70 82 16 2a 2e
    63 61 72 6e 61 76 69 2e 79 61 68 6f 6f 61 70 69
    73 2e 6a 70 82 17 2a 2e 6d 61 72 6b 65 74 69 6e
    67 2e 79 61 68 6f 6f 2e 63 6f 2e 6a 70 82 0f 2a
    2e 79 61 68 6f 6f 2d 68 65 6c 70 2e 6a 70 82 1a
    2a 2e 62 79 6c 69 6e 65 73 2e 6e 65 77 73 2e 79
    61 68 6f 6f 2e 63 6f 2e 6a 70 82 0e 2a 2e 67 65
    6f 63 69 74 69 65 73 2e 6a 70 82 0b 2a 2e 62 73
    70 61 63 65 2e 6a 70 82 12 2a 2e 6d 61 69 6c 2e
    79 61 68 6f 6f 2e 63 6f 2e 6a 70 82 14 2a 2e 70
    6f 69 6e 74 73 2e 79 61 68 6f 6f 2e 63 6f 2e 6a
    70 82 0a 2a 2e 79 61 68 6f 6f 2e 6a 70 82 13 2a
    2e 65 64 69 74 2e 79 61 68 6f 6f 61 70 69 73 2e
    6a 70 82 17 2a 2e 61 75 63 74 69 6f 6e 73 2e 79
    61 68 6f 6f 61 70 69 73 2e 6a 70 82 14 2a 2e 77
    61 6c 6c 65 74 2e 79 61 68 6f 6f 2e 63 6f 2e 6a
    70 82 15 2a 2e 77 61 6c 6c 65 74 2e 79 61 68 6f
    6f 61 70 69 73 2e 6a 70 82 18 2a 2e 77 65 62 68
    6f 73 74 69 6e 67 2e 79 61 68 6f 6f 2e 63 6f 2e
    6a 70 82 12 2a 2e 62 6f 78 2e 79 61 68 6f 6f 61
    70 69 73 2e 6a 70 82 11 2a 2e 70 73 69 2e 79 61
    68 6f 6f 2e 63 6f 2e 6a 70 82 10 2a 2e 6d 73 2e
    79 61 68 6f 6f 2e 63 6f 2e 6a 70 82 1c 61 63 74
    69 76 69 74 79 2e 74 72 61 76 65 6c 2e 79 61 68
    6f 6f 2d 6e 65 74 2e 6a 70 82 14 2a 2e 79 73 2d
    69 6e 73 75 72 61 6e 63 65 2e 63 6f 2e 6a 70 82
    19 61 70 69 2e 79 2e 63 6c 6f 72 64 65 72 2e 79
    61 68 6f 6f 2e 63 6f 2e 6a 70 82 14 61 72 63 2e
    68 65 6c 70 2e 79 61 68 6f 6f 2e 63 6f 2e 6a 70
    82 19 62 69 7a 74 78 2e 70 6f 69 6e 74 73 2e 79
    61 68 6f 6f 61 70 69 73 2e 6a 70 82 18 63 67 69
    32 2e 72 2d 61 67 65 6e 74 2e 79 61 68 6f 6f 2e
    63 6f 2e 6a 70 82 17 63 6b 73 79 6e 63 2e 70 64
    73 70 2e 79 61 68 6f 6f 2e 63 6f 2e 6a 70 82 14
    63 6d 2e 66 72 6f 6d 61 2e 79 61 68 6f 6f 2e 63
    6f 2e 6a 70 82 1b 63 6f 6d 70 61 73 73 2e 79 6d
    6f 62 69 6c 65 2e 79 61 68 6f 6f 2e 63 6f 2e 6a
    70 82 19 63 75 73 74 6f 6d 2e 73 65 61 72 63 68
    2e 79 61 68 6f 6f 2e 63 6f 2e 6a 70 82 17 65 2e
    64 65 76 65 6c 6f 70 65 72 2e 79 61 68 6f 6f 2e
    63 6f 2e 6a 70 82 20 66 65 65 64 62 61 63 6b 2e
    61 64 76 65 72 74 69 73 69 6e 67 2e 79 61 68 6f
    6f 2e 63 6f 2e 6a 70 82 1d 66 65 65 64 62 61 63
    6b 2e 70 72 65 6d 69 61 64 73 2e 79 61 68 6f 6f
    2e 63 6f 2e 6a 70 82 23 66 65 65 64 62 61 63 6b
    2e 70 72 6f 6d 6f 74 69 6f 6e 61 6c 61 64 73 2e
    79 61 68 6f 6f 2e 63 6f 2e 6a 70 82 1a 66 6f 72
    6d 73 2e 62 75 73 69 6e 65 73 73 2e 79 61 68 6f
    6f 2e 63 6f 2e 6a 70 82 17 66 72 61 6d 65 2e 67
    61 6d 65 73 2e 79 61 68 6f 6f 2e 63 6f 2e 6a 70
    82 17 68 72 6d 2e 67 72 6d 74 72 65 7a 2e 79 61
    68 6f 6f 2e 63 6f 2e 6a 70 82 11 69 6d 2e 6f 76
    2e 79 61 68 6f 6f 2e 63 6f 2e 6a 70 82 19 69 6e
    66 6f 2e 68 61 74 61 6c 69 6b 65 2e 79 61 68 6f
    6f 2e 63 6f 2e 6a 70 82 1a 6d 6f 76 69 65 2e 63
    68 6f 63 6f 74 6c 65 2e 79 61 68 6f 6f 2e 63 6f
    2e 6a 70 82 1b 6f 6e 6c 69 6e 65 2e 73 65 63 75
    72 69 74 79 2e 79 61 68 6f 6f 2e 63 6f 2e 6a 70
    82 16 70 61 74 72 6f 6c 2e 73 68 70 2e 79 61 68
    6f 6f 2e 63 6f 2e 6a 70 82 17 70 6f 69 65 64 69
    74 2e 6d 61 70 2e 79 61 68 6f 6f 2e 63 6f 2e 6a
    70 82 21 70 6f 72 74 61 6c 2e 79 61 64 75 69 2e
    62 75 73 69 6e 65 73 73 2e 79 61 68 6f 6f 2e 63
    6f 2e 6a 70 82 24 73 73 6c 2d 74 6f 6f 6c 73 2e
    6b 61 69 6e 61 76 69 2e 73 65 61 72 63 68 2e 79
    61 68 6f 6f 2e 63 6f 2e 6a 70 82 18 73 73 6c 2e
    61 70 69 2e 6f 6c 70 2e 79 61 68 6f 6f 61 70 69
    73 2e 6a 70 82 13 73 73 6c 2e 6d 61 70 2e 73 72
    76 2e 79 69 6d 67 2e 6a 70 82 12 77 77 77 2e 74
    65 63 68 62 61 73 65 76 6e 2e 63 6f 6d 82 10 77
    77 77 2e 79 6a 63 61 72 64 2e 63 6f 2e 6a 70 82
    0b 79 61 68 6f 6f 2e 63 6f 2e 6a 70 82 08 79 61
    68 6f 6f 2e 6a 70 82 05 79 6a 2e 70 6e 82 0f 77
    77 77 2e 73 70 2d 68 69 6e 61 6e 2e 6a 70 82 10
    77 77 77 2e 73 65 61 72 63 68 33 31 31 2e 6a 70
    30 81 8b 06 08 2b 06 01 05 05 07 01 01 04 7f 30
    7d 30 35 06 08 2b 06 01 05 05 07 30 01 86 29 68
    74 74 70 3a 2f 2f 73 73 6f 63 73 70 2e 63 79 62
    65 72 74 72 75 73 74 2e 6e 65 2e 6a 70 2f 4f 63
    73 70 53 65 72 76 65 72 30 44 06 08 2b 06 01 05
    05 07 30 02 86 38 68 74 74 70 3a 2f 2f 63 72 6c
    2e 63 79 62 65 72 74 72 75 73 74 2e 6e 65 2e 6a
    70 2f 53 75 72 65 53 65 72 76 65 72 2f 6f 76 63
    61 67 34 2f 6f 76 63 61 67 34 2e 63 72 74 30 0e
    06 03 55 1d 0f 01 01 ff 04 04 03 02 05 a0 30 1d
    06 03 55 1d 25 04 16 30 14 06 08 2b 06 01 05 05
    07 03 01 06 08 2b 06 01 05 05 07 03 02 30 1f 06
    03 55 1d 23 04 18 30 16 80 14 62 a7 d2 da de 85
    b6 92 f1 85 bc f6 e8 95 9d 75 a0 fa 4e 1f 30 46
    06 03 55 1d 1f 04 3f 30 3d 30 3b a0 39 a0 37 86
    35 68 74 74 70 3a 2f 2f 63 72 6c 2e 63 79 62 65
    72 74 72 75 73 74 2e 6e 65 2e 6a 70 2f 53 75 72
    65 53 65 72 76 65 72 2f 6f 76 63 61 67 34 2f 63
    64 70 2e 63 72 6c 30 1d 06 03 55 1d 0e 04 16 04
    14 f5 41 56 4c 75 8f 0a 42 cb 97 9f ae 8c fe 0c
    2e 79 45 60 f0 30 82 01 f5 06 0a 2b 06 01 04 01
    d6 79 02 04 02 04 82 01 e5 04 82 01 e1 01 df 00
    75 00 e8 3e d0 da 3e f5 06 35 32 e7 57 28 bc 89
    6b c9 03 d3 cb d1 11 6b ec eb 69 e1 77 7d 6d 06
    bd 6e 00 00 01 7f fe 9a 7b 2a 00 00 04 03 00 46
    30 44 02 20 46 cb 9c 94 45 a5 87 3e 10 db ce 0f
    f6 91 82 c3 ae cf fe c2 d4 85 52 a0 90 b0 f8 25
    bb a2 e6 af 02 20 4b 5c 8f f6 a2 4a 04 74 29 e3
    a2 82 ff 10 87 e4 51 9f 8f 2e 0a 70 4e 11 c3 bc
    00 fc ed 24 1f 7b 00 76 00 ad f7 be fa 7c ff 10
    c8 8b 9d 3d 9c 1e 3e 18 6a b4 67 29 5d cf b1 0c
    24 ca 85 86 34 eb dc 82 8a 00 00 01 7f fe 9a 81
    db 00 00 04 03 00 47 30 45 02 21 00 93 9b fd 68
    17 b7 76 04 22 12 d4 76 07 7e 9d e6 7d e7 13 40
    f4 df ea f9 59 bf a5 13 e2 b5 c5 5c 02 20 47 f2
    05 92 35 cb fc 18 72 7e 06 71 8c b0 c0 89 f1 60
    42 60 dd a6 0d 16 b4 a4 67 ec 26 5b 33 f7 00 76
    00 6f 53 76 ac 31 f0 31 19 d8 99 00 a4 51 15 ff
    77 15 1c 11 d9 02 c1 00 29 06 8d b2 08 9a 37 d9
    13 00 00 01 7f fe 9a a0 b9 00 00 04 03 00 47 30
    45 02 21 00 bc 84 25 3a 5d 17 1a ad e6 98 7a ca
    8c 30 79 1b e1 61 4d 46 5f 95 27 fb 98 77 db b2
    54 46 6c 01 02 20 58 5c a5 89 f3 5d 6c e6 37 29
    04 28 79 1c 68 37 36 8d f4 bd aa fc 7c 46 d9 c7
    36 48 84 2c ab 11 00 76 00 55 81 d4 c2 16 90 36
    01 4a ea 0b 9b 57 3c 53 f0 c0 e4 38 78 70 25 08
    17 2f a3 aa 1d 07 13 d3 0c 00 00 01 7f fe 9a a7
    10 00 00 04 03 00 47 30 45 02 21 00 a5 5c d8 02
    75 8c 33 28 0d 46 48 fc 01 42 88 b3 07 e6 06 0a
    41 d0 34 0e 3f f8 46 9c 5d 8b f1 72 02 20 29 19
    7b c2 9f c5 20 ba eb e3 d7 63 4c 4f d8 13 64 d3
    f5 dc be a6 d6 37 98 82 3c 19 bb 38 1a ea 30 0d
    06 09 2a 86 48 86 f7 0d 01 01 0b 05 00 03 82 01
    01 00 2a c6 3b e8 2e 61 4c 41 c0 6e 74 38 58 ce
    e4 cb 89 f6 c6 ef 40 4b 64 3a f5 a6 80 35 63 8e
    f2 83 3f a1 aa ae 96 e8 f2 34 0c 34 f4 c2 a7 a6
    2e 39 5f c0 79 c0 14 12 29 63 63 64 81 71 af 3f
    9d 1a e9 d5 1b 11 f5 ce df bf 31 58 14 c9 9b 4e
    fe f0 df b2 fa 9c d7 93 e2 01 6c 44 56 a5 b3 98
    12 44 39 ea fe 4f 6e d1 6d d1 fc b6 13 f5 84 62
    43 97 33 ad e2 08 f0 ae 8d f5 87 e4 81 5c d8 2a
    00 1d 24 71 c8 69 cb 89 ae fc e5 48 18 f4 54 2b
    05 17 5b 79 2b 3d 32 14 e1 35 97 61 a9 a5 74 bf
    14 bc 53 6c ab e4 1c fc f6 25 1c fa 36 ee 15 38
    bc 37 ac 21 3e 45 1d 86 e3 21 1d d7 2c bc fb c3
    01 19 de 29 2b 66 b3 5f d3 59 48 d9 da 78 fc 07
    42 fe 65 20 c5 13 fa 3f d9 31 2f 5f f6 04 82 48
    18 f5 f8 33 49 fc a2 20 67 41 8e 42 ca 9e 81 3f
    18 04 02 1c 99 e3 c7 59 8f 2b 98 3c 56 57 45 a2
    ce 92 00 04 f2 30 82 04 ee 30 82 03 d6 a0 03 02
    01 02 02 09 22 b9 b1 63 0c ec b4 3c 2e 30 0d 06
    09 2a 86 48 86 f7 0d 01 01 0b 05 00 30 5d 31 0b
    30 09 06 03 55 04 06 13 02 4a 50 31 25 30 23 06
    03 55 04 0a 13 1c 53 45 43 4f 4d 20 54 72 75 73
    74 20 53 79 73 74 65 6d 73 20 43 4f 2e 2c 4c 54
    44 2e 31 27 30 25 06 03 55 04 0b 13 1e 53 65 63
    75 72 69 74 79 20 43 6f 6d 6d 75 6e 69 63 61 74
    69 6f 6e 20 52 6f 6f 74 43 41 32 30 1e 17 0d 31
    39 30 39 32 37 30 31 35 34 32 33 5a 17 0d 32 39
    30 35 32 39 30 35 30 30 33 39 5a 30 5e 31 0b 30
    09 06 03 55 04 06 13 02 4a 50 31 23 30 21 06 03
    55 04 0a 13 1a 43 79 62 65 72 74 72 75 73 74 20
    4a 61 70 61 6e 20 43 6f 2e 2c 20 4c 74 64 2e 31
    2a 30 28 06 03 55 04 03 13 21 43 79 62 65 72 74
    72 75 73 74 20 4a 61 70 61 6e 20 53 75 72 65 53
    65 72 76 65 72 20 43 41 20 47 34 30 82 01 22 30
    0d 06 09 2a 86 48 86 f7 0d 01 01 01 05 00 03 82
    01 0f 00 30 82 01 0a 02 82 01 01 00 cb 6e 9c 59
    a8 b1 3f 08 c4 19 15 14 ff 8e 9e 41 a4 71 59 9b
    ba 2f a1 75 50 65 19 98 67 8a 78 95 96 e0 21 8a
    09 b6 59 4c 71 a7 85 f9 57 70 7f 40 a2 4b 66 67
    80 b3 09 b3 c4 62 97 68 30 b3 72 89 98 c5 74 f2
    80 d5 dc 4c b2 3e 20 cc 91 8a c1 0e ed 5d 4d 5c
    51 d4 8d 21 25 29 a6 35 2f 30 80 f7 f7 a6 95 d9
    e6 46 35 fa 07 d6 6d e7 15 ca e6 ad 76 58 e2 16
    90 91 02 13 0c 0a 92 ee fb b6 fb 4a 64 f4 4a 68
    23 42 1a c6 79 1e 36 bb 3c 1b 34 ee 32 e8 13 4a
    cc b9 92 d0 64 d4 04 07 45 ba dd ab 6d 28 60 86
    cc 49 39 d2 50 e3 fb 04 34 52 55 1b 42 4d f3 00
    4b 2f 74 4e 97 a3 5a 99 cb d9 7b f3 75 5a e3 4b
    d2 c7 75 6a 84 66 1b e2 35 90 ae 0d 82 ac 0b 49
    70 a4 0d 48 9d 26 f7 2c 49 55 54 03 c2 94 10 c0
    6c 47 3b 91 26 42 fd 4b 18 91 31 01 27 a0 39 7c
    e1 ce a0 ab e7 28 b0 10 27 d2 ac eb 02 03 01 00
    01 a3 82 01 ae 30 82 01 aa 30 1d 06 03 55 1d 0e
    04 16 04 14 62 a7 d2 da de 85 b6 92 f1 85 bc f6
    e8 95 9d 75 a0 fa 4e 1f 30 1f 06 03 55 1d 23 04
    18 30 16 80 14 0a 85 a9 77 65 05 98 7c 40 81 f8
    0f 97 2c 38 f1 0a ec 3c cf 30 12 06 03 55 1d 13
    01 01 ff 04 08 30 06 01 01 ff 02 01 00 30 0e 06
    03 55 1d 0f 01 01 ff 04 04 03 02 01 06 30 49 06
    03 55 1d 1f 04 42 30 40 30 3e a0 3c a0 3a 86 38
    68 74 74 70 3a 2f 2f 72 65 70 6f 73 69 74 6f 72
    79 2e 73 65 63 6f 6d 74 72 75 73 74 2e 6e 65 74
    2f 53 43 2d 52 6f 6f 74 32 2f 53 43 52 6f 6f 74
    32 43 52 4c 2e 63 72 6c 30 52 06 03 55 1d 20 04
    4b 30 49 30 47 06 0a 2a 83 08 8c 9b 1b 64 87 05
    04 30 39 30 37 06 08 2b 06 01 05 05 07 02 01 16
    2b 68 74 74 70 73 3a 2f 2f 72 65 70 6f 73 69 74
    6f 72 79 2e 73 65 63 6f 6d 74 72 75 73 74 2e 6e
    65 74 2f 53 43 2d 52 6f 6f 74 32 2f 30 81 85 06
    08 2b 06 01 05 05 07 01 01 04 79 30 77 30 30 06
    08 2b 06 01 05 05 07 30 01 86 24 68 74 74 70 3a
    2f 2f 73 63 72 6f 6f 74 63 61 32 2e 6f 63 73 70
    2e 73 65 63 6f 6d 74 72 75 73 74 2e 6e 65 74 30
    43 06 08 2b 06 01 05 05 07 30 02 86 37 68 74 74
    70 3a 2f 2f 72 65 70 6f 73 69 74 6f 72 79 2e 73
    65 63 6f 6d 74 72 75 73 74 2e 6e 65 74 2f 53 43
    2d 52 6f 6f 74 32 2f 53 43 52 6f 6f 74 32 63 61
    2e 63 65 72 30 1d 06 03 55 1d 25 04 16 30 14 06
    08 2b 06 01 05 05 07 03 01 06 08 2b 06 01 05 05
    07 03 02 30 0d 06 09 2a 86 48 86 f7 0d 01 01 0b
    05 00 03 82 01 01 00 c5 51 79 2e 40 06 4a 63 93
    db fc 9b e0 b9 f8 b3 27 cb 99 2a 93 7e f9 f8 88
    f2 43 93 82 4a d2 ae 23 58 36 33 bd 88 47 53 c1
    55 77 b1 6d cf 69 ba f7 94 07 42 1a b2 7e c2 00
    2b 2c b5 27 05 9e d5 18 cf ff 52 50 e1 4d 17 b8
    03 5f 5c d1 39 95 d6 e7 53 49 bc 5a 6f 04 09 6c
    dd 73 20 66 c6 dc a4 2c ba 68 3d ff bd 0f 68 89
    1a c2 78 a1 c7 df d3 c4 60 ab 26 40 07 e5 6f bd
    a6 45 fb 39 67 9f b1 a8 72 97 08 8f 90 a4 64 25
    1b f6 7a 6f ef ac c4 72 6f 72 f1 45 4e 6d f3 89
    35 c5 0a 82 9c cc 53 11 63 80 89 6a 0e b5 ab 44
    c5 9d fc 6b c9 27 f2 4a a2 13 53 44 be d3 ce cd
    2a d5 8d 2b c3 ee 91 f9 e8 09 6f 3b b8 73 1b 39
    e0 eb 49 32 5a 70 33 e8 ee 6b 43 4b 6c 14 88 16
    f7 19 68 59 34 10 55 c7 c4 b7 3b e3 73 ca 6d b8
    ff 68 9e 46 c0 8c c4 43 25 aa 8b 5e b2 15 b4 1e
    c6 31 e9 3b 4b a0 0e 00 04 76 30 82 04 72 30 82
    03 5a a0 03 02 01 02 02 09 12 b9 b0 fa 72 e0 d8
    48 c6 30 0d 06 09 2a 86 48 86 f7 0d 01 01 0b 05
    00 30 50 31 0b 30 09 06 03 55 04 06 13 02 4a 50
    31 18 30 16 06 03 55 04 0a 13 0f 53 45 43 4f 4d
    20 54 72 75 73 74 2e 6e 65 74 31 27 30 25 06 03
    55 04 0b 13 1e 53 65 63 75 72 69 74 79 20 43 6f
    6d 6d 75 6e 69 63 61 74 69 6f 6e 20 52 6f 6f 74
    43 41 31 30 1e 17 0d 31 35 30 33 32 34 30 32 32
    32 33 35 5a 17 0d 32 33 30 39 32 39 30 32 32 32
    33 35 5a 30 5d 31 0b 30 09 06 03 55 04 06 13 02
    4a 50 31 25 30 23 06 03 55 04 0a 13 1c 53 45 43
    4f 4d 20 54 72 75 73 74 20 53 79 73 74 65 6d 73
    20 43 4f 2e 2c 4c 54 44 2e 31 27 30 25 06 03 55
    04 0b 13 1e 53 65 63 75 72 69 74 79 20 43 6f 6d
    6d 75 6e 69 63 61 74 69 6f 6e 20 52 6f 6f 74 43
    41 32 30 82 01 22 30 0d 06 09 2a 86 48 86 f7 0d
    01 01 01 05 00 03 82 01 0f 00 30 82 01 0a 02 82
    01 01 00 d0 15 39 52 b1 52 b3 ba c5 59 82 c4 5d
    52 ae 3a 43 65 80 4b c7 f2 96 bc db 36 97 d6 a6
    64 8c a8 5e f0 e3 0a 1c f7 df 97 3d 4b ae f6 5d
    ec 21 b5 41 ab cd b9 7e 76 9f be f9 3e 36 34 a0
    3b c1 f6 31 11 45 74 93 3d 57 80 c5 f9 89 99 ca
    e5 ab 6a d4 b5 da 41 90 10 c1 d6 d6 42 89 c2 bf
    f4 38 12 95 4c 54 05 f7 36 e4 45 83 7b 14 65 d6
    dc 0c 4d d1 de 7e 0c ab 3b c4 15 be 3a 56 a6 5a
    6f 76 69 52 a9 7a b9 c8 eb 6a 9a 5d 52 d0 2d 0a
    6b 35 16 09 10 84 d0 6a ca 3a 06 00 37 47 e4 7e
    57 4f 3f 8b eb 67 b8 88 aa c5 be 53 55 b2 91 c4
    7d b9 b0 85 19 06 78 2e db 61 1a fa 85 f5 4a 91
    a1 e7 16 d5 8e a2 39 df 94 b8 70 1f 28 3f 8b fc
    40 5e 63 83 3c 83 2a 1a 99 6b cf de 59 6a 3b fc
    6f 16 d7 1f fd 4a 10 eb 4e 82 16 3a ac 27 0c 53
    f1 ad d5 24 b0 6b 03 50 c1 2d 3c 16 dd 44 34 27
    1a 75 fb 02 03 01 00 01 a3 82 01 40 30 82 01 3c
    30 1d 06 03 55 1d 0e 04 16 04 14 0a 85 a9 77 65
    05 98 7c 40 81 f8 0f 97 2c 38 f1 0a ec 3c cf 30
    1f 06 03 55 1d 23 04 18 30 16 80 14 a0 73 49 99
    68 dc 85 5b 65 e3 9b 28 2f 57 9f bd 33 bc 07 48
    30 0f 06 03 55 1d 13 01 01 ff 04 05 30 03 01 01
    ff 30 0e 06 03 55 1d 0f 01 01 ff 04 04 03 02 01
    06 30 49 06 03 55 1d 1f 04 42 30 40 30 3e a0 3c
    a0 3a 86 38 68 74 74 70 3a 2f 2f 72 65 70 6f 73
    69 74 6f 72 79 2e 73 65 63 6f 6d 74 72 75 73 74
    2e 6e 65 74 2f 53 43 2d 52 6f 6f 74 31 2f 53 43
    52 6f 6f 74 31 43 52 4c 2e 63 72 6c 30 4c 06 03
    55 1d 20 04 45 30 43 30 41 06 04 55 1d 20 00 30
    39 30 37 06 08 2b 06 01 05 05 07 02 01 16 2b 68
    74 74 70 73 3a 2f 2f 72 65 70 6f 73 69 74 6f 72
    79 2e 73 65 63 6f 6d 74 72 75 73 74 2e 6e 65 74
    2f 53 43 2d 52 6f 6f 74 31 2f 30 40 06 08 2b 06
    01 05 05 07 01 01 04 34 30 32 30 30 06 08 2b 06
    01 05 05 07 30 01 86 24 68 74 74 70 3a 2f 2f 73
    63 72 6f 6f 74 63 61 31 2e 6f 63 73 70 2e 73 65
    63 6f 6d 74 72 75 73 74 2e 6e 65 74 30 0d 06 09
    2a 86 48 86 f7 0d 01 01 0b 05 00 03 82 01 01 00
    0d f8 a7 c3 9f f7 5d b2 da d7 b6 3c 69 b2 97 96
    d2 ba 96 c7 e0 5d 58 2c 8a 61 3a f4 d2 1b 7b 4b
    ea 46 e7 75 c5 96 05 53 36 ed be dd 14 3d 29 4c
    8b a7 51 2c c1 85 f9 6c 58 e8 81 25 0f 1a 11 c9
    86 1d 48 3b 57 a9 39 da 41 bb bd 2a 03 ea 0a 30
    d9 a5 d4 1f 08 15 c5 b5 ad eb 9b e9 96 2e 41 8e
    21 7e 58 e8 54 34 0b 4a 19 cd 05 ea 4f b0 41 f1
    d2 b8 d8 cc 0f 83 5d 68 fc 5a ae 41 76 f3 07 d2
    83 e4 be d2 b2 fd 6d ba f7 dd 5e 4c cd e7 bd 68
    31 d3 f5 3a 71 98 2b 26 60 b9 9f 59 cf b9 29 5d
    f0 2f 54 e9 f3 9b 92 c9 a0 3b bb 96 6e 0a 3c 5e
    af 18 f7 a9 2d 6b 33 8e 9b 70 47 e3 a2 99 da 0f
    b8 67 25 74 98 88 bd 5d d3 2c 39 cd 25 b6 3c 47
    be 2c 77 68 20 06 f6 23 a0 fc f1 41 49 1f 40 a5
    8b ab 18 e6 5f 23 86 39 0e 3a cd 72 7a ed 42 fd
    17 18 d3 e3 41 1c a6 64 14 47 84 6f a7 b3 d2 c8
depth=3 C = JP, O = SECOM Trust.net, OU = Security Communication RootCA1
verify return:1
depth=2 C = JP, O = "SECOM Trust Systems CO.,LTD.", OU = Security Communication RootCA2
verify return:1
depth=1 C = JP, O = "Cybertrust Japan Co., Ltd.", CN = Cybertrust Japan SureServer CA G4
verify return:1
depth=0 C = JP, ST = Tokyo, L = Chiyoda-ku, O = Yahoo Japan Corporation, CN = edge01.yahoo.co.jp
verify return:1
<<< ??? [length 0005]
    16 03 03 01 4d
<<< TLS 1.2 Handshake [length 014d], ServerKeyExchange
    0c 00 01 49 03 00 17 41 04 82 bf c8 a2 0d 91 ff
    49 24 08 9c 1d 5e 33 6c aa 6b 1a 64 87 d7 de bc
    45 ce 43 5b 76 8b d7 32 d4 f8 0a 11 0a 6e 88 67
    ec ad 41 db d4 fc b2 90 00 e3 ac 74 33 5d a7 9d
    b1 24 02 99 cc a7 aa ea 9e 04 01 01 00 88 e2 98
    58 e4 e3 42 bc 38 00 33 bf 30 bd 15 94 00 47 54
    74 f0 98 39 a4 69 27 5e dd d9 e8 f5 bc 5c 9e e4
    ab 0c 3b d2 ff 6a 45 00 2f 62 2e 36 92 86 a6 2b
    63 ae 06 99 f1 ae 0d 18 cd 2b 29 b7 1b fd fe f9
    7c fc a0 60 74 4f a6 96 a8 0e 06 95 b6 1d a9 55
    1e 86 98 e7 4c ea 99 ee a1 56 16 5f 66 a2 ab 9f
    33 2a 45 55 59 10 1f 81 53 2d 44 62 10 69 ee 24
    a2 20 b5 44 63 cc 8a 07 b5 7e 4b 9d 00 ed a6 48
    9d 94 7f 30 30 e0 44 26 b1 ca 9e 1f c9 86 aa 50
    93 72 f1 a1 61 f0 e3 f6 7c 1e df 89 96 5b 12 b5
    bd 50 6b ae b6 7a 49 8b a2 ea 7d 0d d7 7d 6e 7d
    a2 ee be c6 58 3c 4c e5 2b 15 f7 54 66 83 1d 49
    bc 97 23 cb 7f 09 00 b9 1a 5d e8 1d fb b0 40 8f
    bb 3d df 79 9e 58 14 15 00 5e 75 79 04 af ad ed
    06 bb 31 29 d4 33 84 15 fc 8a 23 a1 94 27 e6 23
    f5 37 dd a2 fd af 25 10 e6 b1 ae ba b1
<<< ??? [length 0005]
    16 03 03 00 04
<<< TLS 1.2 Handshake [length 0004], ServerHelloDone
    0e 00 00 00
>>> ??? [length 0005]
    16 03 03 00 46
>>> TLS 1.2 Handshake [length 0046], ClientKeyExchange
    10 00 00 42 41 04 19 bc c9 73 6d 01 68 9a 2e 87
    b4 31 83 7d a0 b1 0e 71 30 af a5 f8 5e 2a d4 7b
    c2 5c 30 4f 6c 78 98 63 0d b8 15 51 fb 1d 6a 75
    3d 06 28 9d 6d 2c 79 98 33 dd 2b 45 41 5c 5b 4d
    2d 82 4c f8 4c d6
>>> ??? [length 0005]
    14 03 03 00 01
>>> TLS 1.2 ChangeCipherSpec [length 0001]
    01
>>> ??? [length 0005]
    16 03 03 00 28
>>> TLS 1.2 Handshake [length 0010], Finished
    14 00 00 0c ab 4e 73 29 cf 0b ad 29 08 86 c4 f1
<<< ??? [length 0005]
    16 03 03 00 ca
<<< TLS 1.2 Handshake [length 00ca]???
    04 00 00 c6 00 00 1c 20 00 c0 65 64 67 65 2e 65
    64 67 65 2e 61 74 73 5f 73 73 20 c6 27 51 bf 76
    f6 7e 88 ff b9 29 e4 eb a6 4a 02 a7 8d f7 30 9b
    8c 4f f6 b7 e2 1f 56 2d f2 05 0f 28 1a 88 37 74
    67 c1 36 2d 98 ee fe bc 2c 34 d6 32 35 0f 05 b9
    2b 5a 38 6a 42 9b 28 8d cf 45 e1 7c 75 8b 6e 6d
    6d 81 d7 75 e2 1f 6f 86 12 83 a3 b5 7e bf a3 ce
    46 fa 35 b1 28 0e 62 4e 92 03 9b 43 6f 55 e6 b6
    8e dc 77 53 7a 5c b0 73 c7 0d 9e c2 d9 1c a5 76
    0e 38 5b c9 8c 47 db 0c 04 48 9b dc 28 54 b2 c5
    b0 40 55 ff f6 85 7f 71 36 3b 16 46 d8 33 48 3d
    f9 00 27 c6 b8 d1 f6 e7 6d 25 48 45 77 f8 e5 6e
    83 39 7e 0f c0 f4 be b6 64 49
<<< ??? [length 0005]
    14 03 03 00 01
<<< TLS 1.2 ChangeCipherSpec [length 0001]
    01
<<< ??? [length 0005]
    16 03 03 00 28
<<< TLS 1.2 Handshake [length 0010], Finished
    14 00 00 0c ab c9 5e b2 52 96 3e c0 c4 d5 0b d8
---
Certificate chain
 0 s:/C=JP/ST=Tokyo/L=Chiyoda-ku/O=Yahoo Japan Corporation/CN=edge01.yahoo.co.jp
   i:/C=JP/O=Cybertrust Japan Co., Ltd./CN=Cybertrust Japan SureServer CA G4
 1 s:/C=JP/O=Cybertrust Japan Co., Ltd./CN=Cybertrust Japan SureServer CA G4
   i:/C=JP/O=SECOM Trust Systems CO.,LTD./OU=Security Communication RootCA2
 2 s:/C=JP/O=SECOM Trust Systems CO.,LTD./OU=Security Communication RootCA2
   i:/C=JP/O=SECOM Trust.net/OU=Security Communication RootCA1
---
Server certificate
-----BEGIN CERTIFICATE-----
MIIOtDCCDZygAwIBAgIUNiqxMBQKRrTEkMidZKKKcGdqHpAwDQYJKoZIhvcNAQEL
BQAwXjELMAkGA1UEBhMCSlAxIzAhBgNVBAoTGkN5YmVydHJ1c3QgSmFwYW4gQ28u
LCBMdGQuMSowKAYDVQQDEyFDeWJlcnRydXN0IEphcGFuIFN1cmVTZXJ2ZXIgQ0Eg
RzQwHhcNMjIwNDA2MTAwMTI3WhcNMjMwNTA1MTQ1OTAwWjBxMQswCQYDVQQGEwJK
UDEOMAwGA1UECBMFVG9reW8xEzARBgNVBAcTCkNoaXlvZGEta3UxIDAeBgNVBAoT
F1lhaG9vIEphcGFuIENvcnBvcmF0aW9uMRswGQYDVQQDExJlZGdlMDEueWFob28u
Y28uanAwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQD0IAhmDnNlhxQm
JLFnOfaAPbqTTeXPTfBUbDuA+hPhaxkhUN5CQst+ch+6vGudwM8Q3gvyafJX5qwY
Aj99kUPvBdwQ3EJfill8u/5qYlmKpsQzSvhpwh6oPdIKs2Ap0lnCRPd+6OdQeBi4
VEzxCKYpeNw/ov7FENrjD8UGnCo9Cn4r0cwH30cSyarX5Lz2BFPcnPRLyYmvgEM9
FYf35Hs3oy2zQnXnx/oWdMYLHpO7ft/+7nF/kPCkQvmytuFlMVusP/HstoaR6Hm2
EXKpn3Yz96b85Aa/SJTSBMe+mvJXXQTPbzwgp/tVyRiM0UYfI6O3l66MAr5TTQcx
2bOeDtEJAgMBAAGjggtVMIILUTAMBgNVHRMBAf8EAjAAMGYGA1UdIARfMF0wUQYJ
KoMIjJsRARcBMEQwQgYIKwYBBQUHAgEWNmh0dHBzOi8vd3d3LmN5YmVydHJ1c3Qu
bmUuanAvc3NsL3JlcG9zaXRvcnkvaW5kZXguaHRtbDAIBgZngQwBAgIwggeZBgNV
HREEggeQMIIHjIISZWRnZTAxLnlhaG9vLmNvLmpwgg0qLnlhaG9vLmNvLmpwghEq
LmFuZS55YWhvby5jby5qcIIWKi5hdWN0aW9ucy55YWhvby5jby5qcIILKi5jLnlp
bWcuanCCGCouY2hpZWJ1a3Vyby55YWhvby5jby5qcIIVKi5jbG9yZGVyLnlhaG9v
LmNvLmpwghwqLmVhc3QuZWRnZS5zdG9yYWdlLXlhaG9vLmpwgh8qLmVhc3QuZWRn
ZS5zdG9yYWdlLXlhaG9vYm94LmpwghcqLmVkZ2Uuc3RvcmFnZS15YWhvby5qcIIV
Ki5maW5hbmNlLnlhaG9vLmNvLmpwgh4qLmdsb2JhbC5lZGdlLnN0b3JhZ2UteWFo
b28uanCCFSoubGlzdGluZy55YWhvby5jby5qcIISKi5sb2NvLnlhaG9vLmNvLmpw
ghIqLm5ld3MueWFob28uY28uanCCEyoub3JkZXIueWFob28uY28uanCCFCouc2hv
cHBpbmcuYy55aW1nLmpwghYqLnNob3BwaW5nLnlhaG9vLmNvLmpwghMqLnN0b3Jl
LnlhaG9vLmNvLmpwghQqLnRyYXZlbC55YWhvby5jby5qcIIcKi53ZXN0LmVkZ2Uu
c3RvcmFnZS15YWhvby5qcIIfKi53ZXN0LmVkZ2Uuc3RvcmFnZS15YWhvb2JveC5q
cIIZKi54bWwubGlzdGluZy55YWhvby5jby5qcIIPKi55YWhvby1sYWJzLmpwgg4q
LnlhaG9vYXBpcy5qcIINKi55YWhvb2JveC5qcIIJKi55aW1nLmpwggoqLnlqdGFn
LmpwghMqLnlqdGFnLnlhaG9vLmNvLmpwghNhZGQuZGlyLnlhaG9vLmNvLmpwghMq
LnB1c2gueWFob29hcGlzLmpwghIqLmd5YW8ueWFob28uY28uanCCEyoubmV3cy55
YWhvb2FwaXMuanCCFSouc2VhcmNoLnlhaG9vYXBpcy5qcIIWKi5jYXJuYXZpLnlh
aG9vYXBpcy5qcIIXKi5tYXJrZXRpbmcueWFob28uY28uanCCDyoueWFob28taGVs
cC5qcIIaKi5ieWxpbmVzLm5ld3MueWFob28uY28uanCCDiouZ2VvY2l0aWVzLmpw
ggsqLmJzcGFjZS5qcIISKi5tYWlsLnlhaG9vLmNvLmpwghQqLnBvaW50cy55YWhv
by5jby5qcIIKKi55YWhvby5qcIITKi5lZGl0LnlhaG9vYXBpcy5qcIIXKi5hdWN0
aW9ucy55YWhvb2FwaXMuanCCFCoud2FsbGV0LnlhaG9vLmNvLmpwghUqLndhbGxl
dC55YWhvb2FwaXMuanCCGCoud2ViaG9zdGluZy55YWhvby5jby5qcIISKi5ib3gu
eWFob29hcGlzLmpwghEqLnBzaS55YWhvby5jby5qcIIQKi5tcy55YWhvby5jby5q
cIIcYWN0aXZpdHkudHJhdmVsLnlhaG9vLW5ldC5qcIIUKi55cy1pbnN1cmFuY2Uu
Y28uanCCGWFwaS55LmNsb3JkZXIueWFob28uY28uanCCFGFyYy5oZWxwLnlhaG9v
LmNvLmpwghliaXp0eC5wb2ludHMueWFob29hcGlzLmpwghhjZ2kyLnItYWdlbnQu
eWFob28uY28uanCCF2Nrc3luYy5wZHNwLnlhaG9vLmNvLmpwghRjbS5mcm9tYS55
YWhvby5jby5qcIIbY29tcGFzcy55bW9iaWxlLnlhaG9vLmNvLmpwghljdXN0b20u
c2VhcmNoLnlhaG9vLmNvLmpwghdlLmRldmVsb3Blci55YWhvby5jby5qcIIgZmVl
ZGJhY2suYWR2ZXJ0aXNpbmcueWFob28uY28uanCCHWZlZWRiYWNrLnByZW1pYWRz
LnlhaG9vLmNvLmpwgiNmZWVkYmFjay5wcm9tb3Rpb25hbGFkcy55YWhvby5jby5q
cIIaZm9ybXMuYnVzaW5lc3MueWFob28uY28uanCCF2ZyYW1lLmdhbWVzLnlhaG9v
LmNvLmpwghdocm0uZ3JtdHJlei55YWhvby5jby5qcIIRaW0ub3YueWFob28uY28u
anCCGWluZm8uaGF0YWxpa2UueWFob28uY28uanCCGm1vdmllLmNob2NvdGxlLnlh
aG9vLmNvLmpwghtvbmxpbmUuc2VjdXJpdHkueWFob28uY28uanCCFnBhdHJvbC5z
aHAueWFob28uY28uanCCF3BvaWVkaXQubWFwLnlhaG9vLmNvLmpwgiFwb3J0YWwu
eWFkdWkuYnVzaW5lc3MueWFob28uY28uanCCJHNzbC10b29scy5rYWluYXZpLnNl
YXJjaC55YWhvby5jby5qcIIYc3NsLmFwaS5vbHAueWFob29hcGlzLmpwghNzc2wu
bWFwLnNydi55aW1nLmpwghJ3d3cudGVjaGJhc2V2bi5jb22CEHd3dy55amNhcmQu
Y28uanCCC3lhaG9vLmNvLmpwggh5YWhvby5qcIIFeWoucG6CD3d3dy5zcC1oaW5h
bi5qcIIQd3d3LnNlYXJjaDMxMS5qcDCBiwYIKwYBBQUHAQEEfzB9MDUGCCsGAQUF
BzABhilodHRwOi8vc3NvY3NwLmN5YmVydHJ1c3QubmUuanAvT2NzcFNlcnZlcjBE
BggrBgEFBQcwAoY4aHR0cDovL2NybC5jeWJlcnRydXN0Lm5lLmpwL1N1cmVTZXJ2
ZXIvb3ZjYWc0L292Y2FnNC5jcnQwDgYDVR0PAQH/BAQDAgWgMB0GA1UdJQQWMBQG
CCsGAQUFBwMBBggrBgEFBQcDAjAfBgNVHSMEGDAWgBRip9La3oW2kvGFvPbolZ11
oPpOHzBGBgNVHR8EPzA9MDugOaA3hjVodHRwOi8vY3JsLmN5YmVydHJ1c3QubmUu
anAvU3VyZVNlcnZlci9vdmNhZzQvY2RwLmNybDAdBgNVHQ4EFgQU9UFWTHWPCkLL
l5+ujP4MLnlFYPAwggH1BgorBgEEAdZ5AgQCBIIB5QSCAeEB3wB1AOg+0No+9QY1
MudXKLyJa8kD08vREWvs62nhd31tBr1uAAABf/6aeyoAAAQDAEYwRAIgRsuclEWl
hz4Q284P9pGCw67P/sLUhVKgkLD4Jbui5q8CIEtcj/aiSgR0KeOigv8Qh+RRn48u
CnBOEcO8APztJB97AHYArfe++nz/EMiLnT2cHj4YarRnKV3PsQwkyoWGNOvcgooA
AAF//pqB2wAABAMARzBFAiEAk5v9aBe3dgQiEtR2B36d5n3nE0D03+r5Wb+lE+K1
xVwCIEfyBZI1y/wYcn4GcYywwInxYEJg3aYNFrSkZ+wmWzP3AHYAb1N2rDHwMRnY
mQCkURX/dxUcEdkCwQApBo2yCJo32RMAAAF//pqguQAABAMARzBFAiEAvIQlOl0X
Gq3mmHrKjDB5G+FhTUZflSf7mHfbslRGbAECIFhcpYnzXWzmNykEKHkcaDc2jfS9
qvx8RtnHNkiELKsRAHYAVYHUwhaQNgFK6gubVzxT8MDkOHhwJQgXL6OqHQcT0wwA
AAF//pqnEAAABAMARzBFAiEApVzYAnWMMygNRkj8AUKIswfmBgpB0DQOP/hGnF2L
8XICICkZe8KfxSC66+PXY0xP2BNk0/XcvqbWN5iCPBm7OBrqMA0GCSqGSIb3DQEB
CwUAA4IBAQAqxjvoLmFMQcBudDhYzuTLifbG70BLZDr1poA1Y47ygz+hqq6W6PI0
DDT0wqemLjlfwHnAFBIpY2NkgXGvP50a6dUbEfXO378xWBTJm07+8N+y+pzXk+IB
bERWpbOYEkQ56v5PbtFt0fy2E/WEYkOXM63iCPCujfWH5IFc2CoAHSRxyGnLia78
5UgY9FQrBRdbeSs9MhThNZdhqaV0vxS8U2yr5Bz89iUc+jbuFTi8N6whPkUdhuMh
HdcsvPvDARneKStms1/TWUjZ2nj8B0L+ZSDFE/o/2TEvX/YEgkgY9fgzSfyiIGdB
jkLKnoE/GAQCHJnjx1mPK5g8VldFos6S
-----END CERTIFICATE-----
subject=/C=JP/ST=Tokyo/L=Chiyoda-ku/O=Yahoo Japan Corporation/CN=edge01.yahoo.co.jp
issuer=/C=JP/O=Cybertrust Japan Co., Ltd./CN=Cybertrust Japan SureServer CA G4
---
No client certificate CA names sent
Peer signing digest: SHA256
Server Temp Key: ECDH, P-256, 256 bits
---
SSL handshake has read 6868 bytes and written 431 bytes
---
New, TLSv1/SSLv3, Cipher is ECDHE-RSA-AES128-GCM-SHA256
Server public key is 2048 bit
Secure Renegotiation IS supported
No ALPN negotiated
SSL-Session:
    Protocol  : TLSv1.2
    Cipher    : ECDHE-RSA-AES128-GCM-SHA256
    Session-ID: CB109D648026C2A2AA7F7D9EAF819D6D2CEC55BA2AA819C08E3649188340DDB6
    Session-ID-ctx: 
    Master-Key: B172288286EB1212B6FE7CB468F61CD261CF769702C798F3A643C25F0E288607227FF4F767E319F07877387A2E7D3495
    Key-Arg   : None
    PSK identity: None
    PSK identity hint: None
    SRP username: None
    TLS session ticket lifetime hint: 7200 (seconds)
    TLS session ticket:
    0000 - 65 64 67 65 2e 65 64 67-65 2e 61 74 73 5f 73 73   edge.edge.ats_ss
    0010 - 20 c6 27 51 bf 76 f6 7e-88 ff b9 29 e4 eb a6 4a    .'Q.v.~...)...J
    0020 - 02 a7 8d f7 30 9b 8c 4f-f6 b7 e2 1f 56 2d f2 05   ....0..O....V-..
    0030 - 0f 28 1a 88 37 74 67 c1-36 2d 98 ee fe bc 2c 34   .(..7tg.6-....,4
    0040 - d6 32 35 0f 05 b9 2b 5a-38 6a 42 9b 28 8d cf 45   .25...+Z8jB.(..E
    0050 - e1 7c 75 8b 6e 6d 6d 81-d7 75 e2 1f 6f 86 12 83   .|u.nmm..u..o...
    0060 - a3 b5 7e bf a3 ce 46 fa-35 b1 28 0e 62 4e 92 03   ..~...F.5.(.bN..
    0070 - 9b 43 6f 55 e6 b6 8e dc-77 53 7a 5c b0 73 c7 0d   .CoU....wSz\.s..
    0080 - 9e c2 d9 1c a5 76 0e 38-5b c9 8c 47 db 0c 04 48   .....v.8[..G...H
    0090 - 9b dc 28 54 b2 c5 b0 40-55 ff f6 85 7f 71 36 3b   ..(T...@U....q6;
    00a0 - 16 46 d8 33 48 3d f9 00-27 c6 b8 d1 f6 e7 6d 25   .F.3H=..'.....m%
    00b0 - 48 45 77 f8 e5 6e 83 39-7e 0f c0 f4 be b6 64 49   HEw..n.9~.....dI

    Start Time: 1650760960
    Timeout   : 300 (sec)
    Verify return code: 0 (ok)
---
<<< ??? [length 0005]
    15 03 03 00 1a
<<< TLS 1.2 Alert [length 0002], warning close_notify
    01 00
closed
>>> ??? [length 0005]
    15 03 03 00 1a
>>> TLS 1.2 Alert [length 0002], warning close_notify
    01 00

```

