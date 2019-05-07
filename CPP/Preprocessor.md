# 概要
defineなどで定義されているマクロを追いやすくするためのプリプロセッサについてのTIPSについてまとめる。

# 詳細

### 試しにlinux kernelのいくつかをヘッダファイルにかけてみる。
以下はlinux-2.6.32.65/kernel/mutex.hを試しにプリプロセッサにかけてみた例です。  
その環境のプリプロセッサを生成するためには、プリプロセッサにかける「-P」とそこで終了する「-E」を付与する。  
下記の例ではコメントも残しておきたいので「-C」を付与している。  
実行結果は*.oにプリプロセス結果がテキストとして出力されるおようになる。
```
$ cc -P -C -E  mutex.h
/*
 * Mutexes: blocking mutual exclusion locks
 *
 * started by Ingo Molnar:
 *
 *  Copyright (C) 2004, 2005, 2006 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *
 * This file contains mutex debugging related internal prototypes, for the
 * !CONFIG_DEBUG_MUTEXES case. Most of them are NOPs:
 */
static inline void mutex_set_owner(struct mutex *lock)
{
}
static inline void mutex_clear_owner(struct mutex *lock)
{
}
static inline void
debug_mutex_lock_common(struct mutex *lock, struct mutex_waiter *waiter)
{
```

続いて、include/linux/kernel.hをかけてみた。
```
$ cc -P -E include/linux/kernel.h
include/linux/kernel.h:720:2: warning: #warning Attempt to use kernel headers from user space, see http: [-Wcpp]
struct sysinfo {
 long uptime;
 unsigned long loads[3];
 unsigned long totalram;
 unsigned long freeram;
 unsigned long sharedram;
 unsigned long bufferram;
 unsigned long totalswap;
 unsigned long freeswap;
 unsigned short procs;
 unsigned short pad;
 unsigned long totalhigh;
 unsigned long freehigh;
 unsigned int mem_unit;
 char _f[20-2*sizeof(long)-sizeof(int)];
};
```

たとえば、tlbflush.hなどの場合にはIncludeを適切に設定すれば取得できる。
```
$ cc -P -E tlbflush.h -I/home/tsuyoshi/SOURCE/linux-2.6.32.65/include/ -I/home/tsuyoshi/SOURCE/linux-2.6.32.65/arch/x86/include/
```

### プリプロセッサのdefineを設定してプリプロセッサの処理を確認する
次のようにして定義変数を指定してプリプロセッサの処理を確認することができる。
```
$ gcc -P -E -DSOMAXCONN=true hogehoge.h
```

ただし、上記defineは最初に設定されるため、別のヘッダファイルなどでその後同一のdefineの値を上書きすることはできない。
この場合には次に示すようなハックを使って実施しなければならない
- Overriding macros using compiler options
  - https://stackoverflow.com/questions/4181490/overriding-macros-using-compiler-options

### プリプロセッサの定義済みマクロを確認する
指定するファイル(.ccや.h)がなければecho経由で出力させることで、現在定義されている値を確認することができる。
ファイルが存在していればecho経由にしなくて、直接ファイルを引数として指定すれば良い。
```
// C言語の場合
$ echo | gcc -dM -E -

// C++の場合
$ echo | g++ -dM -E -x c++ -
```

たとえば、特定のヘッダファイルからマクロの値を取得したいといったこともできる。
```
$ echo "#include <sys/socket.h>" | gcc -E -dM - | grep SOMAXCONN
#define SOMAXCONN 128
```

また、オプションによるマクロの違いといった部分についても確認できます。
```
$ echo "#include <stdlib.h>" | gcc -x c++  -dD -E - > noc11
$ echo "#include <stdlib.h>" | gcc -x c++ -std=c++11 -dD -E -  > c11
$ diff c11 noc11 
4c4
< #define __cplusplus 201103L
---
> #define __cplusplus 199711L
75d74
< #define __GXX_EXPERIMENTAL_CXX0X__ 1
197c196
< #define __GNUC_STDC_INLINE__ 1
---
> #define __GNUC_GNU_INLINE__ 1
199d197
< #define __STRICT_ANSI__ 1
238a237
> #define linux 1
240a240
> #define unix 1
341,342d340
< # 216 "/usr/include/features.h" 3 4
< #define __USE_ISOCXX11 1
```

- 参考: GCC dump preprocessor defines
  - https://stackoverflow.com/questions/2224334/gcc-dump-preprocessor-defines

以下に出力結果のサンプルを示す
```
$ echo | gcc -dM -E -
#define __DBL_MIN_EXP__ (-1021)
#define __UINT_LEAST16_MAX__ 65535
#define __ATOMIC_ACQUIRE 2
#define __FLT_MIN__ 1.17549435082228750797e-38F
#define __UINT_LEAST8_TYPE__ unsigned char
#define __INTMAX_C(c) c ## L
#define __CHAR_BIT__ 8
#define __UINT8_MAX__ 255
#define __WINT_MAX__ 4294967295U
#define __ORDER_LITTLE_ENDIAN__ 1234
#define __SIZE_MAX__ 18446744073709551615UL
#define __WCHAR_MAX__ 2147483647
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 1
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 1
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 1
#define __DBL_DENORM_MIN__ ((double)4.94065645841246544177e-324L)
#define __GCC_HAVE_SYNC_COMPARE_AND_SWAP_8 1
#define __GCC_ATOMIC_CHAR_LOCK_FREE 2
#define __FLT_EVAL_METHOD__ 0
#define __unix__ 1
#define __GCC_ATOMIC_CHAR32_T_LOCK_FREE 2
#define __x86_64 1
#define __UINT_FAST64_MAX__ 18446744073709551615UL
#define __SIG_ATOMIC_TYPE__ int
#define __DBL_MIN_10_EXP__ (-307)
#define __FINITE_MATH_ONLY__ 0
#define __GNUC_PATCHLEVEL__ 5
#define __UINT_FAST8_MAX__ 255
#define __DEC64_MAX_EXP__ 385
#define __INT8_C(c) c
#define __UINT_LEAST64_MAX__ 18446744073709551615UL
#define __SHRT_MAX__ 32767
#define __LDBL_MAX__ 1.18973149535723176502e+4932L
#define __UINT_LEAST8_MAX__ 255
#define __GCC_ATOMIC_BOOL_LOCK_FREE 2
#define __UINTMAX_TYPE__ long unsigned int
#define __linux 1
#define __DEC32_EPSILON__ 1E-6DF
#define __unix 1
#define __UINT32_MAX__ 4294967295U
#define __LDBL_MAX_EXP__ 16384
#define __WINT_MIN__ 0U
#define __linux__ 1
#define __SCHAR_MAX__ 127
#define __WCHAR_MIN__ (-__WCHAR_MAX__ - 1)
#define __INT64_C(c) c ## L
#define __DBL_DIG__ 15
#define __GCC_ATOMIC_POINTER_LOCK_FREE 2
#define __SIZEOF_INT__ 4
#define __SIZEOF_POINTER__ 8
#define __USER_LABEL_PREFIX__ 
#define __STDC_HOSTED__ 1
#define __LDBL_HAS_INFINITY__ 1
#define __FLT_EPSILON__ 1.19209289550781250000e-7F
#define __LDBL_MIN__ 3.36210314311209350626e-4932L
#define __DEC32_MAX__ 9.999999E96DF
#define __INT32_MAX__ 2147483647
#define __SIZEOF_LONG__ 8
#define __STDC_IEC_559__ 1
#define __STDC_ISO_10646__ 201103L
#define __UINT16_C(c) c
#define __DECIMAL_DIG__ 21
#define __gnu_linux__ 1
#define __LDBL_HAS_QUIET_NAN__ 1
#define __GNUC__ 4
#define __MMX__ 1
#define __FLT_HAS_DENORM__ 1
#define __SIZEOF_LONG_DOUBLE__ 16
#define __BIGGEST_ALIGNMENT__ 16
#define __DBL_MAX__ ((double)1.79769313486231570815e+308L)
#define __INT_FAST32_MAX__ 9223372036854775807L
#define __DBL_HAS_INFINITY__ 1
#define __DEC32_MIN_EXP__ (-94)
#define __INT_FAST16_TYPE__ long int
#define __LDBL_HAS_DENORM__ 1
#define __DEC128_MAX__ 9.999999999999999999999999999999999E6144DL
#define __INT_LEAST32_MAX__ 2147483647
#define __DEC32_MIN__ 1E-95DF
#define __DBL_MAX_EXP__ 1024
#define __DEC128_EPSILON__ 1E-33DL
#define __SSE2_MATH__ 1
#define __ATOMIC_HLE_RELEASE 131072
#define __PTRDIFF_MAX__ 9223372036854775807L
#define __amd64 1
#define __STDC_NO_THREADS__ 1
#define __ATOMIC_HLE_ACQUIRE 65536
#define __LONG_LONG_MAX__ 9223372036854775807LL
#define __SIZEOF_SIZE_T__ 8
#define __SIZEOF_WINT_T__ 4
#define __GCC_HAVE_DWARF2_CFI_ASM 1
#define __GXX_ABI_VERSION 1002
#define __FLT_MIN_EXP__ (-125)
#define __INT_FAST64_TYPE__ long int
#define __DBL_MIN__ ((double)2.22507385850720138309e-308L)
#define __LP64__ 1
#define __DECIMAL_BID_FORMAT__ 1
#define __DEC128_MIN__ 1E-6143DL
#define __REGISTER_PREFIX__ 
#define __UINT16_MAX__ 65535
#define __DBL_HAS_DENORM__ 1
#define __UINT8_TYPE__ unsigned char
#define __NO_INLINE__ 1
#define __FLT_MANT_DIG__ 24
#define __VERSION__ "4.8.5 20150623 (Red Hat 4.8.5-16)"
#define __UINT64_C(c) c ## UL
#define _STDC_PREDEF_H 1
#define __GCC_ATOMIC_INT_LOCK_FREE 2
#define __FLOAT_WORD_ORDER__ __ORDER_LITTLE_ENDIAN__
#define __STDC_IEC_559_COMPLEX__ 1
#define __INT32_C(c) c
#define __DEC64_EPSILON__ 1E-15DD
#define __ORDER_PDP_ENDIAN__ 3412
#define __DEC128_MIN_EXP__ (-6142)
#define __INT_FAST32_TYPE__ long int
#define __UINT_LEAST16_TYPE__ short unsigned int
#define unix 1
#define __INT16_MAX__ 32767
#define __SIZE_TYPE__ long unsigned int
#define __UINT64_MAX__ 18446744073709551615UL
#define __INT8_TYPE__ signed char
#define __ELF__ 1
#define __FLT_RADIX__ 2
#define __INT_LEAST16_TYPE__ short int
#define __LDBL_EPSILON__ 1.08420217248550443401e-19L
#define __UINTMAX_C(c) c ## UL
#define __GNUC_RH_RELEASE__ 16
#define __SSE_MATH__ 1
#define __k8 1
#define __SIG_ATOMIC_MAX__ 2147483647
#define __GCC_ATOMIC_WCHAR_T_LOCK_FREE 2
#define __SIZEOF_PTRDIFF_T__ 8
#define __x86_64__ 1
#define __DEC32_SUBNORMAL_MIN__ 0.000001E-95DF
#define __INT_FAST16_MAX__ 9223372036854775807L
#define __UINT_FAST32_MAX__ 18446744073709551615UL
#define __UINT_LEAST64_TYPE__ long unsigned int
#define __FLT_HAS_QUIET_NAN__ 1
#define __FLT_MAX_10_EXP__ 38
#define __LONG_MAX__ 9223372036854775807L
#define __DEC128_SUBNORMAL_MIN__ 0.000000000000000000000000000000001E-6143DL
#define __FLT_HAS_INFINITY__ 1
#define __UINT_FAST16_TYPE__ long unsigned int
#define __DEC64_MAX__ 9.999999999999999E384DD
#define __CHAR16_TYPE__ short unsigned int
#define __PRAGMA_REDEFINE_EXTNAME 1
#define __INT_LEAST16_MAX__ 32767
#define __DEC64_MANT_DIG__ 16
#define __INT64_MAX__ 9223372036854775807L
#define __UINT_LEAST32_MAX__ 4294967295U
#define __GCC_ATOMIC_LONG_LOCK_FREE 2
#define __INT_LEAST64_TYPE__ long int
#define __INT16_TYPE__ short int
#define __INT_LEAST8_TYPE__ signed char
#define __DEC32_MAX_EXP__ 97
#define __INT_FAST8_MAX__ 127
#define __INTPTR_MAX__ 9223372036854775807L
#define linux 1
#define __SSE2__ 1
#define __LDBL_MANT_DIG__ 64
#define __DBL_HAS_QUIET_NAN__ 1
#define __SIG_ATOMIC_MIN__ (-__SIG_ATOMIC_MAX__ - 1)
#define __code_model_small__ 1
#define __k8__ 1
#define __INTPTR_TYPE__ long int
#define __UINT16_TYPE__ short unsigned int
#define __WCHAR_TYPE__ int
#define __SIZEOF_FLOAT__ 4
#define __UINTPTR_MAX__ 18446744073709551615UL
#define __DEC64_MIN_EXP__ (-382)
#define __INT_FAST64_MAX__ 9223372036854775807L
#define __GCC_ATOMIC_TEST_AND_SET_TRUEVAL 1
#define __FLT_DIG__ 6
#define __UINT_FAST64_TYPE__ long unsigned int
#define __INT_MAX__ 2147483647
#define __amd64__ 1
#define __INT64_TYPE__ long int
#define __FLT_MAX_EXP__ 128
#define __ORDER_BIG_ENDIAN__ 4321
#define __DBL_MANT_DIG__ 53
#define __INT_LEAST64_MAX__ 9223372036854775807L
#define __GCC_ATOMIC_CHAR16_T_LOCK_FREE 2
#define __DEC64_MIN__ 1E-383DD
#define __WINT_TYPE__ unsigned int
#define __UINT_LEAST32_TYPE__ unsigned int
#define __SIZEOF_SHORT__ 2
#define __SSE__ 1
#define __LDBL_MIN_EXP__ (-16381)
#define __INT_LEAST8_MAX__ 127
#define __SIZEOF_INT128__ 16
#define __LDBL_MAX_10_EXP__ 4932
#define __ATOMIC_RELAXED 0
#define __DBL_EPSILON__ ((double)2.22044604925031308085e-16L)
#define _LP64 1
#define __UINT8_C(c) c
#define __INT_LEAST32_TYPE__ int
#define __SIZEOF_WCHAR_T__ 4
#define __UINT64_TYPE__ long unsigned int
#define __INT_FAST8_TYPE__ signed char
#define __DBL_DECIMAL_DIG__ 17
#define __FXSR__ 1
#define __DEC_EVAL_METHOD__ 2
#define __UINT32_C(c) c ## U
#define __INTMAX_MAX__ 9223372036854775807L
#define __BYTE_ORDER__ __ORDER_LITTLE_ENDIAN__
#define __FLT_DENORM_MIN__ 1.40129846432481707092e-45F
#define __INT8_MAX__ 127
#define __UINT_FAST32_TYPE__ long unsigned int
#define __CHAR32_TYPE__ unsigned int
#define __FLT_MAX__ 3.40282346638528859812e+38F
#define __INT32_TYPE__ int
#define __SIZEOF_DOUBLE__ 8
#define __FLT_MIN_10_EXP__ (-37)
#define __INTMAX_TYPE__ long int
#define __DEC128_MAX_EXP__ 6145
#define __ATOMIC_CONSUME 1
#define __GNUC_MINOR__ 8
#define __UINTMAX_MAX__ 18446744073709551615UL
#define __DEC32_MANT_DIG__ 7
#define __DBL_MAX_10_EXP__ 308
#define __LDBL_DENORM_MIN__ 3.64519953188247460253e-4951L
#define __INT16_C(c) c
#define __STDC__ 1
#define __PTRDIFF_TYPE__ long int
#define __ATOMIC_SEQ_CST 5
#define __UINT32_TYPE__ unsigned int
#define __UINTPTR_TYPE__ long unsigned int
#define __DEC64_SUBNORMAL_MIN__ 0.000000000000001E-383DD
#define __DEC128_MANT_DIG__ 34
#define __LDBL_MIN_10_EXP__ (-4931)
#define __SIZEOF_LONG_LONG__ 8
#define __GCC_ATOMIC_LLONG_LOCK_FREE 2
#define __LDBL_DIG__ 18
#define __FLT_DECIMAL_DIG__ 9
#define __UINT_FAST16_MAX__ 18446744073709551615UL
#define __GNUC_GNU_INLINE__ 1
#define __GCC_ATOMIC_SHORT_LOCK_FREE 2
#define __UINT_FAST8_TYPE__ unsigned char
#define __ATOMIC_ACQ_REL 4
#define __ATOMIC_RELEASE 3
```


