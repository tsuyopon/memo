# 概要
TLSに関するwiresharkについて(../wireshrk.mdも参考のこと)

# 詳細

### ハンドシェイクを追跡する
例えば、https://www.yahoo.co.jpのハンドシェイクwiresharkで追跡する場合
- 1. パケットをキャプチャする。この時には様々な他のデータも取得される。
- 2. プロトコルでソートをかけて、"Protocol"タブでソートをかけた後に"Info"タブでソートをかけると「Client Hello」が並ぶことになる。
- 3. 選択したパケットから「Extension: server_name」の「Server Name Indication extension」の中のServer Nameにサーバ名前があるのでここをクリックする。
- 4. パケット一覧を再度クリックして、そのまま上矢印や下矢印で前や次のパケットに移動すると「Server Name」もそのパケットのものに切り替わるので容易に探したい「www.yahoo.co.jp」を探すことができる。
- 5. 続いて、そのパケットを選択して右クリックして「Follow」-> 「TCP Stream」を選択する
- 6. そのパケットをクリックした状態において「No.」タブをクリックしてソートすると、該当のパケットに関する情報が並んで整列されることになる。

### 秘密鍵を登録する
wiresharkでは秘密鍵をあらかじめ登録しておくことによってTLS通信の中身を確認することができるようになります。
- 1. wiresharkを開く
- 2. 「Preference」-> 左側タブから「Protocols」の中の「SSL」をクリックする
- 3. SSLの設定画面から秘密鍵を登録します

### 「Follow SSL Stream」を利用する
Wiresharkで便利な機能の１つに「Follow TCP Stream」がありますが、秘密鍵を登録することによって「Follow SSL Stream」で流れを追うことができるようになります。

- SeeAlso
  - http://d.hatena.ne.jp/ozuma/20140413/1397397632

