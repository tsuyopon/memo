

### C言語のプログラムの中にアセンブリ言語のプログラムを混ぜて書く方法。

書式は以下のとおり
```
asm ( アセンブラの命令列 : 出力オペランド(省略可) : 入力オペランド(省略可) : 破壊するレジスタ(省略可) )
```

- オペランドの形式: "制約"(Cの値)
- 制約で = があると、書き込み専用
- 制約で、使えるレジスタが書ける。
- オペランドは、「,」で区切って複数書ける 
- volatile をつけると、コンパイラによる最適化（命令の順番の入れ替え等）を 抑止できる。 

※ 参考
	* http://www.coins.tsukuba.ac.jp/~yas/coins/os2-2010/2011-02-01/index.html


*** 現在動作しているカーネルパラメータを確認する
$ cat /proc/cmdline 
BOOT_IMAGE=/vmlinuz-3.3.4-5.fc17.x86_64 root=/dev/mapper/vg-lv_root ro rd.md=0 rd.dm=0 SYSFONT=True rd.lvm.lv=vg/lv_root rd.luks=0 KEYTABLE=jp106 rd.lvm.lv=vg/lv_swap LANG=en_US.UTF-8 rhgb quiet


### コントロールレジスタ
	http://caspar.hazymoon.jp/OpenBSD/annex/intel_arc.html


### ハードウェア周りについてよくまとまっているページ
	http://caspar.hazymoon.jp/OpenBSD/annex/


### 
- プロテクトモード
	割り込みディスクリプタ・テーブル(IDT)を使用し設定する
リアルモード

### IDTディスクリプタ
IDTには以下の３種類のゲートディスクリプタのいずれかがエントリーされる。
	タスクゲートディスクリプタ
	割り込みゲートディスクリプタ
	トラップゲートディスクリプタ

	(参考) ディスクリプタ構造については以下の図を参考のこと
		http://caspar.hazymoon.jp/OpenBSD/annex/interrupt_protect.html

ローカルディスクリプタテーブル(LDT)
	http://wiki.bit-hive.com/north/pg/%A5%ED%A1%BC%A5%AB%A5%EB%A5%C7%A5%A3%A5%B9%A5%AF%A5%EA%A5%D7%A5%BF%A5%C6%A1%BC%A5%D6%A5%EB%28LDT%29]

