# Overview
This is TCPv4 Header Details

# TCPv4 Packet Structure

- Refer from: https://tools.ietf.org/html/rfc793#section-3.1
```

    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |          Source Port          |       Destination Port        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                        Sequence Number                        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Acknowledgment Number                      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |  Data |           |U|A|P|R|S|F|                               |
   | Offset| Reserved  |R|C|S|S|Y|I|            Window             |
   |       |           |G|K|H|T|N|N|                               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |           Checksum            |         Urgent Pointer        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Options                    |    Padding    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                             data                              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                            TCP Header Format
```

### FIN and RST
- https://stackoverflow.com/questions/13049828/fin-vs-rst-in-tcp-connections

### RSTパケットが発生するケース
よくあるりそうなのが次のようなケース
- Listenしていないポートに対してSYNパケットが送信された場合、RSTがSYNの送信元に返却される。
- Accept済のソケットに対して、データを全て読み取っていない(EOFになっていない)でcloseを発行した場合に、コネクションの相手側にRSTが送られる

これ以外にも存在しているようだ。
- http://d.hatena.ne.jp/IchiRoku/20101027/1288199148

### RSTを受信したときのOSの挙動について
LinuxでWindowsで挙動が違うようです。
- Linux
  - packet1 -> packet2 -> RSTという順番で受信したとすると、readシステムコールはpacket1, packet2をユーザプログラムに読み込ませた後にエラーを返す
- Windows
  - packet1 -> packet2 -> RSTという順番で受信したとすると、packet1, packet2がバッファ上に残っていたとしてもrecv関数はユーザプログラムにpacket1, packet2を受信させることなくエラーを返す

- 参考
  - http://zi-kuwai.blog.so-net.ne.jp/2011-01-03

# Checksum
- http://www.erg.abdn.ac.uk/users/gorry/course/inet-pages/ip-cksum.html
