# 概要
/procのosについて


### バージョンを表示する(/proc/version)
```
$ cat /proc/version 
Linux version 3.3.4-5.fc17.x86_64 (mockbuild@x86-14.phx2.fedoraproject.org) (gcc version 4.7.0 20120504 (Red Hat 4.7.0-4) (GCC) ) #1 SMP Mon May 7 17:29:34 UTC 2012
```

### カーネルモジュールを表示する(/proc/modules)

1番目のフィールドはモジュール名が表示されます。  
2番目のフィールドにはモジュールのメモリ容量(byte)が表示されます。  
3番目のフィールドには現在ロードされているモジュールのインスタンス数が表示されます。  
4番目のフィールドにはそのモジュールが依存するモジュール名が表示されます。「-」の場合には独立したモジュールとなります。  
5番目のフィールドはロード状態があり、Live、Loading、Unloadingの３つの状態がある。  
6番目のフィールドは、カーネルメモリオフセットが表示される。  

```
$ cat /proc/modules 
fuse 77772 4 - Live 0xffffffffa01a6000
bnep 19584 2 - Live 0xffffffffa01a0000
bluetooth 273667 7 bnep, Live 0xffffffffa014a000
rfkill 21384 3 bluetooth, Live 0xffffffffa013e000
ip6t_REJECT 12939 2 - Live 0xffffffffa0139000
nf_conntrack_ipv6 14297 10 - Live 0xffffffffa0130000
nf_defrag_ipv6 18095 1 nf_conntrack_ipv6, Live 0xffffffffa0126000
ipt_MASQUERADE 12880 1 - Live 0xffffffffa0121000
xt_state 12578 19 - Live 0xffffffffa011c000
iptable_nat 13383 1 - Live 0xffffffffa0117000
nf_nat 25179 2 ipt_MASQUERADE,iptable_nat, Live 0xffffffffa010b000
nf_conntrack_ipv4 14622 12 iptable_nat,nf_nat, Live 0xffffffffa0102000
nf_defrag_ipv4 12673 1 nf_conntrack_ipv4, Live 0xffffffffa00f4000
ip6table_filter 12815 1 - Live 0xffffffffa00fd000
nf_conntrack 82339 6 nf_conntrack_ipv6,ipt_MASQUERADE,xt_state,iptable_nat,nf_nat,nf_conntrack_ipv4, Live 0xffffffffa00de000
ip6_tables 27073 1 ip6table_filter, Live 0xffffffffa0073000
snd_intel8x0 38143 2 - Live 0xffffffffa00d3000
microcode 19252 0 - Live 0xffffffffa00a1000
e1000 145411 0 - Live 0xffffffffa00aa000
snd_ac97_codec 133281 1 snd_intel8x0, Live 0xffffffffa007f000
ac97_bus 12718 1 snd_ac97_codec, Live 0xffffffffa0053000
snd_pcm 97129 2 snd_intel8x0,snd_ac97_codec, Live 0xffffffffa005a000
snd_page_alloc 18101 2 snd_intel8x0,snd_pcm, Live 0xffffffffa0042000
snd_timer 28690 1 snd_pcm, Live 0xffffffffa004a000
snd 78862 8 snd_intel8x0,snd_ac97_codec,snd_pcm,snd_timer, Live 0xffffffffa002d000
soundcore 14491 1 snd, Live 0xffffffffa0025000
i2c_piix4 13694 0 - Live 0xffffffffa0006000
i2c_core 38028 1 i2c_piix4, Live 0xffffffffa001a000
uinput 17673 0 - Live 0xffffffffa0014000
binfmt_misc 17463 1 - Live 0xffffffffa000b000
video 18980 0 - Live 0xffffffffa0000000
```

### Linuxカーネルが利用している暗号化アルゴリズムを表示する(/proc/crypto)
```
$ sudo cat /proc/crypto | tail -25
min keysize  : 16
max keysize  : 32

name         : aes
driver       : aes-aesni
module       : kernel
priority     : 300
refcnt       : 1
selftest     : passed
type         : cipher
blocksize    : 16
min keysize  : 16
max keysize  : 32

name         : aes
driver       : aes-asm
module       : kernel
priority     : 200
refcnt       : 1
selftest     : passed
type         : cipher
blocksize    : 16
min keysize  : 16
max keysize  : 32
```

nameだけを表示した例は次の通り
```
$ grep '^name' /proc/crypto
name         : stdrng
name         : crc32c
name         : aes
name         : sha1
name         : md5
name         : xts(aes)
name         : pcbc(aes)
name         : lrw(aes)
name         : rfc3686(ctr(aes))
name         : rfc4106(gcm(aes))
name         : __gcm-aes-aesni
name         : ctr(aes)
name         : __ctr-aes-aesni
name         : cbc(aes)
name         : __ecb-aes-aesni
name         : ecb(aes)
name         : __cbc-aes-aesni
name         : __ecb-aes-aesni
name         : __aes-aesni
name         : aes
name         : aes
```

- 参考
 - https://www.centos.org/docs/5/html/5.1/Deployment_Guide/s2-proc-crypto.html
