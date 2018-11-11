# TLS False Start
False Startとは英語で「フライング」を意味する言葉です。
TLSではフルハンドシェイクの場合でも、省略ハンドシェイクの場合でも、クライアントとサーバの両方がFinishedを送受信してからApplicationDataの送受信へと進みます。
しかし、Finishedを送付したあとであれば相手からのFinished到着を待たずにApplicationDataを送付しても良いという規格がTLS False StartでありRFC7918で規定されています。

TLS False StartはTLS1.2までに対応しています。TLS1.3についてはすでにラウンドトリップの削減もスコープに含まれているのでTLS False Startには対応していません。

# ブラウザでの対応
現時点でTLS False Startに対応しているのはGoogle Chromeのみと考えられています。

まずChromeはブラックリスト方式で対応し始めました。
- https://www.imperialviolet.org/2010/09/05/blacklisting.html

その後、Chromeはブラックリストの方針を変更して最新のCipherを使っている場合にのみTLS False Startを使うといった制限を行なうようになりました。
- https://www.imperialviolet.org/2012/04/11/falsestart.html

IETFでもその後2016年8月にRFC化されますが、最近ではTLS1.3シフトの方向へ進んでいて実質TLS Flase Startへほとんど対応されない状況となっています。

上記の経緯などについては以下の資料にまとまっているので参考にすると良いです。
- 参考資料: https://datko.net/2012/04/15/tls-false-start-is-dead/


# 参考URL
- RFC7918: Transport Layer Security (TLS) False Start
  - https://tools.ietf.org/html/rfc7918
- Google ChromeのTLS False Startへの対応の試みの経緯がわかる資料
  - https://datko.net/2012/04/15/tls-false-start-is-dead/
