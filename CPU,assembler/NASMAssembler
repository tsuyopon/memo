NASM(Netwide Assembler)とはx86用アセンブラの１つです.
アセンブラの種類については以下を参照
	http://ja.wikibooks.org/wiki/X86%E3%82%A2%E3%82%BB%E3%83%B3%E3%83%96%E3%83%A9/x86%E3%82%A2%E3%82%BB%E3%83%B3%E3%83%96%E3%83%A9
	
NASMのユーザーマニュアルは以下にあります。
	http://www.nasm.us/doc/

*** インストール
$ wget "http://sourceforge.net/projects/nasm/files/nasm%20sources/2.07/nasm-2.07.tar.gz/download"
$ tar xvfz download
$ cd nasm-2.07
$ ./configure
$ make
$ su
# make install

参考: http://dqn.sakusakutto.jp/2011/05/hello-world.html

*** helloworldプログラム

参考: http://ravelll.hatenadiary.jp/entry/2014/10/09/142134

$ vim hello.asm
section .text

global main

main:
  push dword len
  push dword msg
  push dword 1

  mov eax, 0x4
  sub esp, 4
  int 0x80

  add esp, 16

  push dword 0

  mov eax, 0x1
  sub esp, 4
  int 0x80

section .data
  msg db "Hello, World", 0xa
  len equ $-msg

アセンブル＋リンカ
$ nasm -f macho hello.asm
$ ld -o hello -e main hello.o
$ ./hello
