# プロセス関連調査コマンドについて


### プロセスのメモリマッピング状態を確認する
vmmapにプロセスIDを指定することで、そのプロセスがマッピングしているメモリ情報を確認できます。
出力が多いので、途中snipしています。

```
$ sudo vmmap 94338
Password:
Process:         ocspd [94338]
Path:            /usr/sbin/ocspd
Load Address:    0x10c4ff000
Identifier:      ocspd
Version:         55124.20.1
Code Type:       X86-64
Parent Process:  launchd [1]

Date/Time:       2019-01-14 02:10:10.643 +0900
OS Version:      Mac OS X 10.10.5 (14F2511)
Report Version:  7
Analysis Tool:   /usr/bin/vmmap
----

Virtual Memory Map of process 94338 (ocspd)
Output report format:  2.3  -- 64-bit process

==== Non-writable regions for process 94338

REGION TYPE                      START - END             [ VSIZE] PRT/MAX SHRMOD  REGION DETAIL
__TEXT                 000000010c4ff000-000000010c516000 [   92K] r-x/rwx SM=COW  /usr/sbin/ocspd
__LINKEDIT             000000010c51a000-000000010c521000 [   28K] r--/rwx SM=COW  /usr/sbin/ocspd
__LINKEDIT             000000010c521000-000000010c522000 [    4K] r--/rwx SM=NUL  /usr/sbin/ocspd
MALLOC (admin)         000000010c523000-000000010c524000 [    4K] r--/rwx SM=ZER  
MALLOC (admin)         000000010c525000-000000010c526000 [    4K] ---/rwx SM=NUL  
MALLOC (admin)         000000010c53b000-000000010c53d000 [    8K] ---/rwx SM=NUL  
MALLOC (admin)         000000010c552000-000000010c553000 [    4K] ---/rwx SM=NUL  
...(snip)...
__DATA                 00007fff7891d000-00007fff78943000 [  152K] rw-/rwx SM=COW  /System/Library/Frameworks/IOBluetooth.framework/Versions/A/IOBluetooth
__DATA                 00007fff78943000-00007fff78945000 [    8K] rw-/rwx SM=COW  ...ry/PrivateFrameworks/ChunkingLibrary.framework/Versions/A/ChunkingLibrary
...(snip)...
__TEXT                 00007fff95f1d000-00007fff95fc0000 [  652K] r-x/r-x SM=COW  /System/Library/Frameworks/IOBluetooth.framework/Versions/A/IOBluetooth
__TEXT                 00007fff95fc0000-00007fff95fe7000 [  156K] r-x/r-x SM=COW  ...ry/PrivateFrameworks/ChunkingLibrary.framework/Versions/A/ChunkingLibrary
__IMAGE                00007fff95feb000-00007fff9606f000 [  528K] r--/r-- SM=COW  /System/Library/Frameworks/AppKit.framework/Versions/C/AppKit
__UNICODE              00007fff962f6000-00007fff96380000 [  552K] r--/r-- SM=COW  ...tem/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation
__LINKEDIT             00007fff96380000-00007fff9aa54000 [ 70.8M] r--/r-- SM=COW  dyld shared cache combined __LINKEDIT
VM_ALLOCATE            00007fffffe00000-00007fffffe01000 [    4K] r--/r-- SM=SHM  
shared memory          00007fffffef0000-00007fffffef1000 [    4K] r-x/r-x SM=SHM  

==== Writable regions for process 94338
REGION TYPE                      START - END             [ VSIZE] PRT/MAX SHRMOD  REGION DETAIL
__DATA                 000000010c516000-000000010c51a000 [   16K] rw-/rwx SM=PRV  /usr/sbin/ocspd
Kernel Alloc Once      000000010c522000-000000010c523000 [    4K] rw-/rwx SM=PRV  
MALLOC                 000000010c524000-000000010c525000 [    4K] rw-/rwx SM=ZER  
MALLOC                 000000010c526000-000000010c53b000 [   84K] rw-/rwx SM=PRV  

==== Legend
SM=sharing mode:  
	COW=copy_on_write PRV=private NUL=empty ALI=aliased 
	SHM=shared ZER=zero_filled S/A=shared_alias

==== Summary for process 94338
ReadOnly portion of Libraries: Total=180.0M resident=57.3M(32%) swapped_out_or_unallocated=122.7M(68%)
Writable regions: Total=54.5M written=1356K(2%) resident=104K(0%) swapped_out=1336K(2%) unallocated=54.4M(100%)

REGION TYPE                      VIRTUAL
===========                      =======
Dispatch continuations             8192K
Kernel Alloc Once                     8K
MALLOC                             36.3M        see MALLOC ZONE table below
MALLOC (admin)                       44K
MALLOC freed, no zone               264K
STACK GUARD                        56.0M
Stack                              9824K
VM_ALLOCATE                         336K
__DATA                             15.1M
__IMAGE                             528K
__LINKEDIT                         70.9M
__TEXT                            109.1M
__UNICODE                           552K
mapped file                        23.4M
shared memory                         4K
===========                      =======
TOTAL                             330.2M

                                 VIRTUAL ALLOCATION      BYTES
MALLOC ZONE                         SIZE      COUNT  ALLOCATED  % FULL
===========                      =======  =========  =========  ======
DefaultMallocZone_0x10c523000      36.0M       7081       634K      1%
GFXMallocZone_0x10c554000             0K          0         0K
===========                      =======  =========  =========  ======
TOTAL                              36.0M       7081       634K      1%
```
