# 概要
Bocksについてまとめます。
- http://bochs.sourceforge.net/

# インストール(MAC OS Mojave 10.14.5)

以下の参考にさせてもらっています。
この辺のページに従ってビルドをしますが、自分の環境でmakeした際にどうやらエラーとなるようです。(バージョンは2.6.9で、disable-debugger-guiはconfigureから除外することにしました。)
- https://qiita.com/yakawa/items/4a25f1da2663777940d9

次のページからソースコードを取得します。
- https://sourceforge.net/projects/bochs/files/bochs/2.6.9/bochs-2.6.9.tar.gz/download


必要なパッケージをいれます。
```
$ brew install sdl
```

```
$ mv ~/Downloads/bochs-2.6.9.tar.gz .
$ tar zxvf bochs-2.6.9.tar.gz
$ cd bochs-2.6.9
$ ./configure --enable-ne2000 \
            --enable-all-optimizations \
            --enable-cpu-level=6 \
            --enable-x86-64 \
            --enable-vmx=2 \
            --enable-pci \
            --enable-usb \
            --enable-usb-ohci \
            --enable-e1000 \
            --enable-debugger \
            --enable-disasm \
            --with-sdl \
            --prefix=$HOME/opt/bochs
$ make
$ make install            
```

上記のmake時に様々なコンパイルエラーが出てきたので修正した際の差分を添付します。
以下の記事も参考にしています。
- https://rayanfam.com/topics/bochs-config-and-build-on-windows-and-os-x/

```
$ diff ./bochs-2.6.9/iodev/hdimage/cdrom_osx.cc ./original/bochs-2.6.9/iodev/hdimage/cdrom_osx.cc
194c194
<   if ((devname = (char*)strrchr(devpath, '/')) != NULL) {
---
>   if ((devname = strrchr(devpath, '/')) != NULL) {
```

```
diff original/bochs-2.6.9/.bochsrc bochs-2.6.9/.bochsrc
914c914
< sound: driver=default, waveout=/dev/dsp. wavein=, midiout=
---
> #sound: driver=default, waveout=/dev/dsp. wavein=, midiout=
```

```
$ diff ./bochs-2.6.9/misc/bxhub.cc  original/bochs-2.6.9/misc/bxhub.cc 
34d33
< #define MSG_NOSIGNAL	0x4000
```

```
$ diff original/bochs-2.6.9/iodev/network/eth_socket.cc bochs-2.6.9/iodev/network/eth_socket.cc
86c86
< #include <netpacket/packet.h>
---
> //#include <netpacket/packet.h>
90c90,91
< #include <linux/types.h>
---
> //#include <linux/types.h>
> #include "my_linux_types.h"
```

```
$ cat bochs-2.6.9/iodev/network/my_linux_types.h 
#ifndef my_linux_types_h
#define my_linux_types_h

#ifdef __linux__
# include "linux/types.h"
#else
# include <stdint.h>
typedef int32_t __s32;
typedef uint8_t __u8;
typedef uint16_t __u16;
//[... and so on for whatever other types your program uses ...]
#define MSG_NOSIGNAL	0x4000
#endif

#endif
```
