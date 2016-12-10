# 概要
rsyncについて

# 詳細
例えばリモートホストhogeに/home/webのディレクトリをhogeの/home/backupに バックアップする時は次のようになる。
```
$rsync -azv -e ssh --delete /home/web hoge:/home/backup
```

これはローカルホスト上で行なう時も同様である。 例えば、/home/webを/mnt/flash-memoryに送るときは次のようにする。
```
$rsync -azv -e ssh --delete /home/web /mnt/flash-memory
```

rsyncの代表的なオプションを以下に示す。
```
-a     アーカイブモード。r,l,p,t,g,o,Dの全オプションを指定する。
       ディレクトリ内に含まれる全てのファイル、ディレクトリをシンボリック
       リンク、パーミッション属性、グループ属性、所有者属性、タイムスタン
       プを保持したまま同期する。 

-v     冗長モード。バックアップ時にバックアップしているファイル名を表示する。
-z     データを圧縮して転送する。
-e ssh ファイル転送の暗号化(付加しないとデフォルトはrshになる)
--delete  バックアップ元で削除されたファイルはバックアップ先でも削除する。
           --deleteオプションは2回目以降の転送時に付加する。
```

以下ではrsyncの上記以外のオプションを示す。
```
-r     指定したディレクトリ以下の各ディレクトリも再帰的にバックアップする
-l     シンボリックリンクをそのままバックアップする
-H     ハードリンクをそのままバックアップする
-p     パーミッション属性を保持したままバックアップする。
-o     所有者属性を保持したままバックアップする。
-g     グループ属性を保持したままバックアップする。
-t     タイムスタンプを保持したままバックアップする。
-D     デバイスファイルを保持したままバックアップする。
-z     データを圧縮して転送する。
-u     追加されたファイルだけをバックアップする。
--existing  更新されたファイルだけをバックアップして、追加されたファイルはバックアップしない。
--exclude 'pattern' patternで指定されたファイルはバックアップしない。
```

定期的なバックアップで利用したい場合、rsyncを--daemonオプションを付加して起動させる事で、rsyncサーバとして利用可能になる。 この場合、/etc/rsyncd.confに利用する為の設定を記述すればよい。 頻繁にバックアップをしない場合にはcronを利用した方がいいと思います。

### rsyncの詳細オプションについて
```
-v, --verbose           転送情報を詳しく表示
-q, --quiet             転送情報を表示しない
-c, --checksum          常にチェックサムを行う
-a, --archive           アーカイブモード(-rlptgoD オプションと同義)
-r, --recursive         ディレクトリで再帰的に実行する
-R, --relative          相対パス名を使う
-b, --backup            バックアップを作成する (デフォルトで ~ が付く)
--backup-dir            このディレクトリにバックアップを作成する
--suffix=SUFFIX         バックアップのサフィックスを変更
-u, --update            アップデートのみ許可 (上書き禁止)
-l, --links             ソフトリンクを維持する
-L, --copy-links        ファイルのようにソフトリンクを扱う
--copy-unsafe-links     送信側ツリー外のリンクをコピー
--safe-links            受信側ツリー外のリンクを無視
-H, --hard-links        ハードリンクを維持する
-p, --perms             パーミッションを維持する
-o, --owner             オーナーを維持する (root のみ)
-g, --group             グループを維持する
-D, --devices           デバイスを維持する (root のみ)
-t, --times             タイムスタンプを維持する
-S, --sparse            密度の低いファイルを効率的に扱う
-n, --dry-run           実行時の動作だけを表示
-W, --whole-file        rsync アルゴリズムを使わない
-x, --one-file-system   再帰的に実行された時にファイルシステムの境界を横断しない
-B, --block-size=SIZE   rsync アルゴリズムのチェックサムブロックサイズの制御(default 700)
-e, --rsh=COMMAND       rsh の代替を指定
--rsync-path=PATH       リモートのマシーンで rsync のコピーへのパスを指定
-C, --cvs-exclude       システム間で転送したくない広範囲のファイルを除外(CVSの方法と同じ)
--existing              既に存在するファイルだけをアップデート
--delete                送信側にないファイルを削除
--delete-excluded       受信側にある exclud ファイルも削除
--delete-after          転送完了後ではなく、転送前にファイルを削除
--ignore-errors         IOエラーが発生したとしてもファイルを削除 
--max-delete=NUM        NUM 以上のファイルを削除しない
--partial               転送途中のファイルを保存します
--force                 ディレクトリが空でなくても削除
--numeric-ids           ユーザとグループの id 番号を転送して、転送後にマッピング
--timeout=TIME          IO タイムアウトを設定(秒)
-I, --ignore-times      タイムスタンプとファイルサイズのチェックをしない
--size-only             タイムスタンプのチェックをしないで、ファイルサイズのチェックだけをする
--modify-window=NUM     Timestamp window (seconds) for file match (default=0)
-T  --temp-dir=DIR      tmp ファイルのディレクトリを指定
--compare-dest=DIR      受信側のファイルと比較するための追加ディレクトリ
-P                      --partial --progress と同義
-z, --compress          受信ファイルデータを圧縮
--exclude=PATTERN       パターン一致するファイルを除外
--exclude-from=FILE     ファイルに記述されたパターンと一致するファイルを除外
--include=PATTERN       パターン一致するファイルを除外しない
--include-from=FILE     ファイルに記述されたパターンと一致するファイルを除外しない
--version               rsync のバージョンを表示する
--daemon                rsync をデーモンとして走らせる
--address               指定されたアドレスに bind させる
--config=FILE           別の rsyncd.conf ファイルを指定
--port=PORT             別の rsync ポート番号を指定
--blocking-io           リモートシェルにブロッキング IO を使用
--stats                 rsync アルゴリズムの転送効率を表示
--progress              転送中の情報を表示
--log-format=FORMAT     ログフォーマットを指定
--password-file=FILE    ファイルからパスワードを得る
--bwlimit=KBPS          I/O 帯域をKB/秒で指定して制限
-h, --help              このヘルプを表示する 
```

### ローカルとリモートでの差分を取得したい
この場合にはチェックサムを確認するオプション-cとテスト用オプション-nを 利用すると良い。
```
	$ rsync -avz -c -n /home/tsuyoshi/test/ remote.co.jp:/home/tsuyoshi/test2/
```
これにより、ローカルに存在する/home/tsuyoshi/test/以下と/home/tsuyoshi/test2/以下 の差分を表示してくれます。

### sshの圧縮アルゴリズムで違うものを利用したい
blowfishアルゴリズムというのを使うと早いらしい。

- eの後にシングルクォート'で囲めばよい。
```
$ rsync -e 'ssh -c blowfish -ax' -avz example.org:/tmp .
-axオプションはSSHとX11 Forwardingを無効にするものらしく、rsyncでは不要らしい。
```

# 参考URL
- Manpage of rsync
 - http://www.infoscience.co.jp/technical/rsync/README.html
