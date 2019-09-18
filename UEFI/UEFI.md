# 概要
UEFIはBIOSの後継である。UEFIをUEFI BIOS、BIOSをレガシーBIOSと呼ぶことがあるようです。

元々は従来のBIOSを廃止して、新しいファームウェアに移行しようという動きはインテルが2000年にEFIを発表したことに端を発する。 IA-64ベースのマシンが最初のEFI搭載機となった。
しかし、Intel-64はあまり評価されることがなかったため普及はしなかった。
その後、2005年に業界団体United EFIフォーラムを設立して、関連仕様をまとめEFI(EFI 1.10)の仕様を公開して多くの企業が利用できるように標準化の推進と普及を行ってきた。

UEFIに最初に対応したOSはWindows Server 2008 からで、コンシューマ向けでは64bitのWindows Vista(Service Pack適用後)からとなっている。
Intel6シリーズのチップセットからで本格的にUEFIが普及し始めるようになった。


# 特徴

### UEFI特徴
UEFIはレガシーBIOSの問題点を改善した仕様となっているので、多くの利点が存在する。
- 仕様がオープンである
  - https://uefi.org/specifications
- プログラムがC言語で記述可能
  - レガシーBIOSではアセンブリ言語を使ってアクセスする必要がありましたが、C言語のみで記述できるようになりました。
  - レガシーBIOSでは古いH/Wとの互換性のために16bitリアルモードからA20解放して、32bitプロテクトモードへの切り替えが必要でした。
- マルチプラットフォーム
- セキュアブート
- 2.2TB以上のディスクからのブートが可能になる
- 高速なシステムの起動とシャットダウン
- 高機能な設定画面操作
- UEFI は特定の OS に依存しない
- GPTドライブをサポート

### 注意点
- SATAデバイスのモードにはレガシーなIDEモードと、新しいAHCIモードがある。UEFIブートするためには、SATAはAHCIモードでなければならない
- GPTについて
  - セキュアブートを無効に設定することで、BIOS互換モードを利用できる。
  - インストール時のモードに基づいてWindowsは構成するために、別モードの機能を使うためにはドライブを再フォーマットする必要があるとのこと
    - OSインストールメニューの際にUEFIかAHCI(BIOSブート)の２つから選択できるが、これによってHDDパーティション形式がGPT（GUID Partition Table）かMBRかが決定されてしまうらしい。
    - http://dekomoriutamaru.com/blog-entry-985.html
  - GPTは、Windows Vista以降のOSならデータ用として使用できるが、GPTディスクに対応していないWindows XP 32bit版などでは使用できない。また、BIOSには対応していないので起動用のドライブとしては指定することができない。
- OS起動時の違い
  - XXX: なぜハードウェアテストがなくなった!?
```
・BIOSの場合
   電源ON ⇒ BIOS（ハードウェアテスト） ⇒ 起動デバイスを順番に探しブートローダープログラムを起動 ⇒ OSを起動

・UEFIの場合
   電源ON ⇒ 起動デバイスを順番に探しEFI システム パーティションから起動 ⇒ OSを起動
```


# サポート状況

## OSサポート状況

### Windowsサポート状況
- Windows7、Windows Vista SP1 は　64 ビットシステムでサポート
- Windows 8は、32 ビット (x86)、64 ビット (x64)の PC でサポート
- BIOS モードでのWindows起動　\bootmgr ファイル　が必要
- UEFI モードでWindows起動　\EFI\BOOT\BOOTX64.EFI ファイルが必要


### Linuxサポート状況
grub経由でブートする方法とUEFIから直接ブートする方法の２つがあるらしい。
直接ブートする場合には、以下のカーネル設定が対応している必要があるとのこと
- https://wiki.archlinux.jp/index.php/Unified_Extensible_Firmware_Interface?rdfrom=https%3A%2F%2Fwiki.archlinux.org%2Findex.php%3Ftitle%3DUnified_Extensible_Firmware_Interface_%28%25E6%2597%25A5%25E6%259C%25AC%25E8%25AA%259E%29%26redirect%3Dno#UEFI_.E3.83.95.E3.82.A1.E3.83.BC.E3.83.A0.E3.82.A6.E3.82.A7.E3.82.A2.E3.81.AE.E3.83.93.E3.83.83.E3.83.88.E6.95.B0.E3.82.92.E8.AA.BF.E3.81.B9.E3.82.8B


# ビルド環境

## SDK
次の３種類の方法がある
- 1) SDKを利用しない方法
  - 参考: https://shina-ecc.hatenadiary.org/entry/20140819/1408434995
- 2) gnu-efi
  - EDKⅡと比較して単純な操作しかできないので、細かい制御をしようとすると物足りなくなるらしい。
  - https://sourceforge.net/projects/gnu-efi/
- 3) EDKⅡ
  - 仕様策定基となるIntelが開発していたSDKなので機能が非常に豊富
  - https://sourceforge.net/projects/edk2/files/


SDKを利用しない場合には
```
fs/EFI/BOOT/BOOTX64.EFI: main.c
    mkdir -p fs/EFI/BOOT
    x86_64-w64-mingw32-gcc -Wall -Wextra -e efi_main -nostdinc -nostdlib \
    -fno-builtin -Wl,--subsystem,10 -o $@ $<

run: fs/EFI/BOOT/BOOTX64.EFI
    qemu-system-x86_64 -bios ~/OVMF.fd -hda fat:rw:fs
```

この辺のcupnesさんのサンプルが非常に試すのに有用です。(qemuのオプションはfat:rw:fsにしないと自分の環境ではエラーがでてはまりました。)
- https://github.com/cupnes/c92_uefi_bare_metal_programming_samples

rwについては以下を参考のこと
- https://tnishinaga.hatenablog.com/entry/2017/06/20/191955

## OVMF取得
OVMFとは「Open Virtual Machine Firmware」の略で仮想マシンの上でUEFIを実行するためのものらしいです． OVMFは次のリンクからダウンロードします。
- https://sourceforge.net/projects/edk2/files/OVMF/

上記からOVMF-X64-r15214.zipをダウンロードした(当時最新版)

OVFMは自分でビルドすることもできます。


ビルド方法は以下に記載されている
- https://jp3bgy.github.io/blog/linux/2018/12/18/Run-Linux-on-QEMU-Easily.html
- https://github.com/tianocore/tianocore.github.io/wiki/How-to-build-OVMF

ビルドしているのは次のレポジトリです
- https://github.com/tianocore/edk2/

QEMU/KVMでOVMFを指定する方法はいくつか存在します。一番手っ取り早いのは「-bios」オプションにファームウェアのファイル名を渡す方法です。

## OS環境構築
UEFIはPE32+というWindowsで利用されている形式のバイナリへと変換が必要です。
このため、MacやLinuxからはクロスコンパイルが必要となります。

### MacOS
```
$ brew install FiloSottile/musl-cross/musl-cross    // コンパイルがあり結構時間かかります。
$ brew install mingw-w64
```

上記をインストールすることでPE32+形式をコンパイルするためのx86_64-w64-mingw32-gccがインストールされます。
```
$ which x86_64-w64-mingw32-gcc
/usr/local/bin/x86_64-w64-mingw32-gcc
```

- 参考資料
  - https://blog.filippo.io/easy-windows-and-linux-cross-compilers-for-macos/


### Linux(未確認)
```
$ yum install mingw64-gcc
```

# Normative Reference
- UEFI仕様書
  - https://uefi.org/specifications

# Informative Reference
- gnu-efiでUEFI遊びをはじめよう
  - https://qiita.com/tnishinaga/items/40755f414557faf45dcb
- UEFIによるELFバイナリの起動 uchan_nos
  - https://www.slideshare.net/uchan_nos/uefielf
- 30分で分かる！OSの作り方 ver.2
  - https://www.slideshare.net/uchan_nos/30os-ver2
- 大神さんの資料
  - http://yuma.ohgami.jp/UEFI-Bare-Metal-Programming/main_1.html
  - http://yuma.ohgami.jp/#outline-container-org639724b
- ビルド参考資料
  - http://kuroneko0208.hatenablog.com/entry/2018/03/26/012835
- osdev-jp
  - https://github.com/osdev-jp/osdev-jp.github.io/wiki/UEFI

