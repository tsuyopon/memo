# 概要
/etc/hostsを即時反映させる方法についてのメモ

# 詳細


### Chrome

hostsファイルを変更
下記ページにアクセスして「Clear host cache」ボタンを押してホストキャッシュをクリアする
- chrome://net-internals/#dns

下記ページにアクセスして「Flush socket pools」ボタンを押してソケットプールの消去する
- chrome://net-internals/#sockets


### Firefox
- about:config
とアドレスバーに入力してnetwork.dnsCacheExpiration を0にするとキャッシュを使わずに名前解決をするようになるのでhostsが即時反映される。


# 参考資料
- https://qiita.com/aidadada/items/eddddb5d4ba8f99959eb
