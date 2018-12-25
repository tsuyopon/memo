# 概要
CPUでは仮想化を支援するテクノロジーが登場してきています。
ここでは、それらの技術に関する機能や仕組みについて説明しています。

# Intel

## Intel VTx, Intel
従来のx86 CPUの特権モードに加えてVMXという動作モードを追加している(VMX: Virtual Machine Extensions)。  
VMXの動作モードは「VMX root」「VMX nonroot」の２つが提供される。  
VM専用空間(VMX nonroot)上でVM上の命令を実行する。未実装命令・VMMによる処理が必要な命令に当たった場合にはVMX rootに制御を戻す。

- VMX root
  - 仮想マシンモニタ(VMM)が動作するモード
  - VMXON命令によって通常動作モードからVMX rootへ遷移する。
- VMX nonroot
  - Guest OSを動作させるモード
  - VMX rootからVMLAUNCH/VMRESUME命令によってVMX nonrootへ遷移する。

上記でも登場しているがVMX Instructionには次のような命令が存在する(主要な命令のみを記載)
説明で登場するVMCSは、Virtual Machine Control Structureを意味していて、特にオーバーヘッドが大きい特権命令の処理やコンテキストスイッチをハードウェアで支援する。
- VMXON: VMX rootへの状態遷移
- VMXOFF: VMX rootから通常動作モードへの状態遷移
- VMPTRLD: 操作対象となるCurrent VMCSを取得する
- VMPTRLD: VMCSのアドレスを設定する
- VMREAD: Current VMCSに対して、vCPUの状態を読み込み
- VMWRITE: Current VMCSに対して、vCPUの状態を書き込み
- VMLAUNCH: VMX nonrootへの最初の状態遷移を行う。Current VMCSで最初に仮想マシンを起動する時に実行
- VMRESUME: 再度VMX nonrootへ状態遷移を行う
- VMCLEAR: VMCS領域の初期化処理で実行

VMCSには一体何が入っているのだろうか? 基本的にはIntelの公式マニュアルを読めだろうが、、
以下を参考に記載させてもらっている。
- http://d.hatena.ne.jp/think_carefully/20090801/1249122184

VM exit/entry時のハードウェアの情報を保存したり、振る舞いを制御する構造体である。
- Guest-state area
  - ゲストOS用のプロセッサのレジスタの値を保持する。
  - VM exitの時にセーブして、VM entry時にロードする。Control Registers(CR0, CR3, CR4)やSegment Registerなどの一部のフィールドを保存します。
- Host-state area
  - ホストOS用のプロセッサのレジスタ値を保持します。
  - VM exitの時にロードします。構成はGuest-stateと似ている。
- VM-execution control fields
  - VMX nonroot操作でのプロセッサの振る舞いを制御するフィールド。またVM exitを引き起こした要因も保持する。
  - プロセッサの振る舞いの例
    - bit9が1であれば、INVLPGを実行してVM exitとなる
    - bit15が1であれば、CR3にwriteするとVM exitとなる
  - VM exitを引き起こした要因としては、
    - bit0が1であれば、VM exitを引き起こしたのは外部割り込み
    - bit3が1であれば、VM exitを引き起こしたのはNMI
- VM-exit control fields
  - VM exitの振る舞いを制御します 
  - 以下に例を示します。
    - bit 9が1であれば、VM exitの後にlogical processor が IA-32e mode となる。
    - bit 18が1であれば、IA32_PAT MSR を VM exit 時に保存する。
    - bit 19が1であれば、IA32_PAT MSR を VM exit 時にロードする。
- VM-entry control fields
  - Vm entryの振る舞いを制御します。
  - 以下に例を示します。
    - bit 9が1であれば、VM entryの後にlogical processor が IA-32e mode となる。
    - bit 14が1であれば、IA32_PAT MSR を VM entry時に保存する。
    - bit 15が1であれば、IA32_PAT MSR を VM entry時にロードする。
- VM exit information fields
  - 最初に発生したVM exitの情報を保持する。
  - 以下に例を示します。
    - Exit Reason: VM exitの要因に関する情報
    - Exit qualification: VM exit要因の詳細な情報。どのCPU命令で引き起こされたのかがわかる。
    - Guest-linear address: VM exitを引き起こした命令のメモリオペランドの内容。LSWM, INS/OUTなどの命令がVM exitした際に利用される。
    - Guest-physical address: EPT violation, EPT misconfigurationによってVM exitが引き起こされた場合に使用されます。

仮想マシン起動の流れ (参考: http://www.viops.jp/VIOPS04-5.1.pdf)
- 1. VMX rootモードへ状態遷移
- 2. VMCSの初期化
- 3. GuestOSのプログラムをメモリ上にロードする
- 4. VMX nonrootへ遷移してGuestOSを実行する。2でセットされたEIPレジスタのアドレスから実行を開始する。
- 5. VM Exit発生によってVMX rootへ状態遷移する
- 6. VMCSからVM Exitの発生要因を判定して各種エミュレーション処理を実施する
- 7. エミュレーションの実行結果をメモリやVMCSに設定する
- 8. VMRESUME命令によって仮想マシンの処理を再開する

その後は5-8が繰り返されるらしい(TODO: ソースコード追いかけてみたい)

## Intel VT-I
Itanium2向けの仮想化支援機構である。
VT-xとほとんど同じ機能を有するが、特にゲストOSに対する仮想CPUリソース割り当てを柔軟にできる特徴を持つらしい。



# Intel VT-d
ダイレクトI/O向けインテルVT(Intel VT-d)は、I/O処理の仮想化を支援する技術です。
この仮想化技術が存在しない場合には、VMMはI/OデバイスをエミュレートしてDMAのメモリ領域の李マッピングを行う必要があります。
VT-dでは、ハードウェア的にDMA転送時のリマッピングを行うことができます。この場合には、ゲストOSでも通常のデバイスドライバを利用することができます。

TBD

# Intel VT-c
Virtualization Technology for Connectivityは、均衡的なサーバー性能のための最適なI/Oの仮想化を支援する各種テクノロジーの総称です。  
次の技術で構成されています。
- 1. Virtual Machine Device Queues (VMDq)
  - 複数の仮想マシンからのNICへのアクセスを調整し、データの並び替えと通信の効率化を行う。
- 2. Intel I/O Acceleration Technology (I/O AT)
  - NICのTCP/IPプロトコルの処理を行うことで、OSの処理を簡略化してCPU負荷を軽減する。
- 3. Single Root I/O Virtualization (SR-IOV) 
  - I/Oデバイスを仮想化する。PCI-Expressカードを仮想化し、複数の仮想マシンからアクセスが可能になりパフォーマンスが改善する。

(TODO: 上記の３つの技術を深追いする)

# Intel EPT(Extended Page Tables)
TBD


# AMD
## AMD -V
TBD

# AMD NPT(Nested Page Tables)
TBD


# 参考リファレンス
- Intel VT ～仮想化を支える基礎技術～
  - すごい良いスライド
  - http://www.viops.jp/VIOPS04-5.1.pdf
- 仮想マシンを支える ハードウェア技術（インテル）
  - https://ipsj.ixsq.nii.ac.jp/ej/?action=repository_action_common_download&item_id=65793&item_no=1&attribute_id=1&file_no=1
- 仮想マシンを支える ハードウェア技術（AMD）
  - https://ipsj.ixsq.nii.ac.jp/ej/?action=repository_action_common_download&item_id=62972&item_no=1&attribute_id=1&file_no=1


# 公式マニュアル
- Intel 64 and IA-32 Architectures Developer's Manual: Vol. 3B
  - https://www.intel.co.jp/content/www/jp/ja/architecture-and-technology/64-ia-32-architectures-software-developer-vol-3b-part-2-manual.html
