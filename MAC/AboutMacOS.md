# OSバージョンの取得とCPU情報取得
- OSバージョン
  - https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man1/sw_vers.1.html
```
$ sw_vers
ProductName:    Mac OS X
ProductVersion: 10.9.3
BuildVersion:   13D65
```

- CPU情報
```
$ sysctl -n machdep.cpu.brand_string
machdep.cpu.brand_string: Intel(R) Core(TM) i5-5287U CPU @ 2.90GHz
```

```
$ sysctl  -a | grep -i machdep.cpu.features
machdep.cpu.features: FPU VME DE PSE TSC MSR PAE MCE CX8 APIC SEP MTRR PGE MCA CMOV PAT PSE36 CLFSH DS ACPI MMX FXSR SSE SSE2 SS HTT TM PBE SSE3 PCLMULQDQ DTES64 MON DSCPL VMX SMX EST TM2 SSSE3 CX16 TPR PDCM SSE4.1 SSE4.2 x2APIC POPCNT AES PCID XSAVE OSXSAVE TSCTMR AVX1.0 RDRAND F16C
```

# Apple周りのソースコード
- https://opensource.apple.com/

# MAC関連設定

# 一般操作
### keynoteなどのファイルが終了時に自動保存されてしまう。
Mac OS X Lion v10.7以降では自動保存が有効になってしまっているようです。
システム環境変数 -> 「一般」 -> 「書類を閉じるときに変更内容を保持するかどうかを確認」にチェックする。
- https://www.too.com/support/faq/mac/22483.html



### アップロードするときなどに、1つ上の階層に移動する
アップロードする画面で1つ上の階層に移動する方法のやり方がわからなかったのでメモしておく
```
Command + ↑
```

### ページの先頭・最後尾に移動する。
先頭に移動する。
```
Command + ↑
```

最高尾に移動する。
```
Command + ↓
```

### 画面を拡大・縮小する
ターミナルやブラウザなどでの拡大、縮小の方法です。

- 拡大する
```
Command + Shift + "+"
```
- 縮小する
```
Shift + "-"
```


### catしてクリップボードにコピペする
非常に大量の行があるファイルなどに便利
```
$ cat gdb.txt | pbcopy
```

リモートサーバにログインするためにsshを使っているような場合にもpbcopyを使うことができます。
```
$ ssh user@example.com 'cat hello.txt' | pbcopy
```

### クリップボードにコピーした文字列を貼り付ける
```
$ echo "hoge" | pbcopy
$ pbpaste
hoge
```

### 必須アプリ
- Alfred
-- 即座に必要なリソースにアクセス
- Trailer
-- github更新を即座に検知

### WindowsのAlt + F4(閉じる)と同じ
```
Command + Q
```

### ショートカット
```
PageUP                Fn + ↑
PageDown              Fn + ↓
Home                  Fn + ↑
End                   Fn + ↓ 
画面再下部まで移動    Command + ↓
画面再上部まで移動    Command + ↑
```

MAC公式ページでショートカット一覧を紹介しています。
- http://support.apple.com/kb/HT1343?viewlocale=ja_JP&locale=ja_JP

### ひらがな、カタカナ、全角半角英数への変換方法
- ひらがな: Ctrl + j
- カタカナ: Ctrl + k
- 全角英数: Ctrl + l
- 半角英数: Ctrl + ;

### Control KeyとCaps Lockキーの入れ替え
- システム環境変数を開く
- キーボードを開く
- 修飾キーボタンをクリック
- CapsLockをControlに、ControlをCapsLockに変更すればOK

(参考)  http://wayohoo.com/mac/tips/control-7-shortcut-key.html

### Deleteキーを有効にする
Mac ではDeleteキーが存在していますが、役割的にはBackSpaceと同じです。
Deleteキーと同じ挙動とするためには、
```
Fn + Delete
```
または
```
Control + D
```
とします。

(参考) http://wayohoo.com/mac/tips/control-7-shortcut-key.html

### 画面キャプチャー
```
コマンド+Shift+3  で画面全体
コマンド+Shift+4  で範囲指定
```

### 実行したコマンド結果などをクリップボードにコピーする
MacOS Xでは標準でpbcopyコマンドを利用することによってクリップボードにコピーできる。
```
$ echo "Helloaaa" | pbcopy
$ date | pbcopy
```

Mac OSのpbcopyと同様にxselというコマンドが存在する。
デフォルトではインストールされていないので要インストール

### 選択しただけでクリップボードにコピーしたい場合
TerminalCopyOnSelectをインストールすることにより可能になる。
http://www.moongift.jp/2009/11/terminalcopyonselect/

### 入力時にカタカナや英字に変換したい
Windowsでは F７や F１０でこのような操作をすることが可能ですが、
Macの場合でも同じですが、ノートパソコンの設定によっては
```
   Fn + F7 (カタカナ変換)
   Fn + F10 (英字変換)
```
となります。

### -Gオプションを付加することによって、色を付加することができます。ls --color=autoは利用できません。
```
$ ls -G 
```

### 色付きgrepをパイプに通すと色が消えてしまう。(Macに限らない??)
colorオプションにalwaysを指定するとパイプを通しても問題なさそう。
$ grep -rinH ap_run_log_tran -A 1 -B 1 --color="always" | less -R

(参考): http://d.hatena.ne.jp/hogem/20090217/1234854706


# 設定
### .vimrc最低限の設定
```
$ vim ~/.vimrc
syntax enable
set background=dark
let g:solarized_termcolors=256
```

### ターミナルのタブを移動する
```
右移動する   Command + Shift + ]   または  Command + Shift + ➡
左移動する   Command + Shift + [   または  Command + Shift + ⬅
```

### ターミナルのタブを新しく開く
```
Command + T
```
によってタブが新しく開かれます

### ターミナルのタブを閉じる
```
Command + W
```

### Safariショートカット
- http://inforati.jp/apple/mac-tips-techniques/internet-hints/how-to-use-mac-safari-browser-with-keyboard-shortcut.html

### ブックマークバーにあるN番目を即座に表示する
```
Command + N(番号)
```

### mysql起動
```
$ sudo mysql.server start
```
- http://qiita.com/hkusu/items/cda3e8461e7a46ecf25d

### ️ローカルアクセス
http://localhost:8080/
ssh localhost -p 50022

### ️.inputrc, .bash_profile設定
http://mactips-lib.net/m/terminal/001.html

### ️ターミナルの日本語がlsして文字化けする場合
ターミナルの環境設定 -> 詳細 -> 文字エンコーディングをUnicode(UTF-8)に設定すれば良い

### locateを使う
```
$ sudo launchctl load -w /System/Library/LaunchDaemons/com.apple.locate.plist
$ sudo /usr/libexec/locate.updatedb
```

### ターミナルで1wordずつ移動する
- 1 word進む
```
Esc, F
 または
Ctrl+[, F
```
- 1 word戻る
```
Esc, B
 または
Ctrl+[, B
```

- 参考: Is there any way in the OS X Terminal to move the cursor word by word?
 - http://stackoverflow.com/questions/81272/is-there-any-way-in-the-os-x-terminal-to-move-the-cursor-word-by-word

### IPv6をoffにする
```
$ networksetup -listnetworkserviceorder
$ sudo networksetup -setv6off Wi-Fi
```

# トラブルシューティング

### SierraにアップデートするとSSH接続で秘密鍵のパスを覚えてくれない
git cloneやgit pullでいままでパスワードを1回入力すればできていたのですが、常にパスワードを要求されるようになります。
次のような設定が必要となる。
```
Host *
	ForwardAgent yes
	UseKeychain yes
	AddKeysToAgent yes
```


- 参考
  - https://qiita.com/takumikkusu/items/3b18e475de02a91b37e8
- 公式ドキュメント
  - https://developer.apple.com/library/archive/navigation/
- 
  - http://macappstore.org/
