# Direct Memory Accessとは
DMAはアキュムレータ(CPU)を介さずに直接メモリにアクセスする方式である。
専用の回路のことをDMA Controller(DMAC)と呼ぶ。

- メリット
  - 
  - この辺の記事を参考にすること
    - https://www.uquest.co.jp/embedded/learning/lecture15-1.html
- デメリット
  - DMACが転送している間は、他のデバイスはアクセスできない。例えば、CPU、DMAC、メインメモリが同一パスであればCPUがアクセスできなくなる時もある。

