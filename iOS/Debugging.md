# 概要
iphone端末のデバッグ方法について

# 詳細

## iphone端末からweb inspectorへの接続

### web inspectorの使い方ドキュメント
以下にappleが用意する公式ドキュメントがあります
- https://developer.apple.com/library/content/documentation/AppleApplications/Conceptual/Safari_Developer_Guide/GettingStarted/GettingStarted.html

### Safariのweb inspectorでiphone端末を接続する
iPhone端末をMAC PCに接続して、Safariのweb inspectorから解析することができます。
端末及びPC側で両方で操作します。

- 1. 「Safari」→「Safari」メニュー→「環境設定の下部にある「メニューバーに”開発”メニューを表示」をチェックします。
- 2. iphone端末の設定で「設定」->「Safari」->「詳細」から「Webインスペクタ」をオンにします。
- 3. iphone端末とMACをケーブルで指します。
- 4. iphone端末にてsafariで該当ページを開きます。例えば、www.yahoo.co.jpを開いたと仮定します。
- 5. MAC PCのSafariを起動して「開発」->「端末の名前」を選択すると現在開いているURL(www.yahoo.co.jpなど)が表示されますので、それを選択します。
- 6. 以上で連携できます。iphone上でサイトを更新したり、MAC PC上で更新するだけでiphoneの端末上のサイトが更新され、web inspectorで検知することができます。

- 参考
  - https://qiita.com/stakei1/items/590788e6c9b2f8e6b3d2

なお、自分はiOS11が出たばかりにiphone端末を更新して、MAC PC上からweb inspectorで解析しようとしましたが、iphone端末の名前が表示されて即座に消えるという減少に直面しました。これはOSバージョンを上げて、Safariも最新にアップデートすることにより回避できるようになりました。


### Safariのweb inspecotrでシミュレータを接続する
基本的には「Safariのweb inspectorでiphone端末を接続する」の手順とほとんど同じです。 
予めXcodeは最新版を入れることによってOSバージョンが最新のシミュレータも利用可能になりますので頭にいれておきましょう。

- 1. 「Safari」→「Safari」メニュー→「環境設定の下部にある「メニューバーに”開発”メニューを表示」をチェックします。
- 2. xcodeを開きます。
- 3. xcodeからシングルページなどのデフォルトで起動可能なアプリを作成して、該当シミュレータ(そこでOSバージョンも決定する)を起動します。
- 4. 起動したシミュレータのsafariを利用したいのでHOMEボタンを押下します。シミュレータだとHOMEボタン押下は「shift + command + H」となるようです。
  - (参考) https://ideacloud.co.jp/dev/home_button.html
- 5. シミュレータのsafariを開いて該当ページをひらいておきます。
- 6. MAC PCのSafariを起動して「開発」->ここで該当シミュレータを選択します。

### Safariのweb inspectorで接続のヘッダ情報を見る
以外にわかりにくかったのでメモとして残しておきます。

「ネットワーク」などのタブを選択 -> 該当リクエスト行を選択する -> 画面右上の右側のゴミ箱の横にある「メニューバーを表示させるようなものを想起させるアイコン」(詳細サイドバーを表示)をクリックするとリクエストヘッダ・レスポンスヘッダなどの詳細を表示してくれるようになります。

## 端末データをtcpdumpする

### 仮想インターフェイス(rvi)を利用する
仮想インターフェイス(Remote Virtual Interface)を使ってできるらしい。
自分もまだ試したことが無いのでとりあえずURLだけ添付しておく
- https://qiita.com/ionis_h/items/661a9a9d41cb1574e357

### jailブレークする
試したことありません。TODO: 試したら追記する

### MAC経由でtcpdumpする
- 1. 予めMAC PCでWifi通信などしている場合にはイーサネットケーブルを接続して有線接続します。
- 2. 「システム環境設定」->「共有」-> 「インターネット共有」にチェックを入れます。これでMACがwifi stationになります。
- 3. iphone端末から上記で作成したwifiに接続する。
- 4. ターミナル上でtcpdumpをします。
```
$ sudo tcpdump -i bridge100 -w hogehoge.pcap
```



