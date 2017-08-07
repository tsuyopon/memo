# Certificate Transparency(RFC6962)
次のような記事を読みCertificate Transparency(CT)について調べてみることにする。
```
2016年6月1日以降にSymantecが発行する証明書に関して、Certificate Transparencyのポリシーに準拠したものだけを信頼する仕組みを、Chromeのバージョン53に実装した。 
だが、同ブラウザーには、CTの情報を信頼する期間を10週間に限定する仕組みが別途実装されていた。古くなった情報への信頼を防ぐために行われた。
```

SSL/TLSの信頼性を高めるための新たな技術で、Google社により提唱されました。RFC6962としてRFC化されています。
証明書の誤発行を防ぐための新しい技術として注目されています。

CTは認証局が発行する証明書を都度、すべての証明書の発行の証跡を第三者の監査ログに残すための仕組みです。



# CTの流れ

1. CAが第三者の監査ログサーバにプレ証明書を登録する
2. 監査ログサーバがプレ証明書にSCT(Signed Certificate Timestamp)を付与して返却する
3. 認証局はサービス提供者にサーバ証明書(プレ証明書+SCT付きから変換)を提供します。
4. サービス提供者がWebサーバにサーバ証明書SCT付きを配置します。
5. サービス利用者がサーバ証明書SCT付きを取得します。
6. サービス利用者が監査ログサーバのサーバ証明書SCT付きを照合します。

SCTというのはログが特定の時間内に発行されたことを保証するタイムスタンプ情報です。

# 対応状況確認
Chromeブラウザから確認すると「公開監査記録がありません」と表示されるような場合にはCT未対応です。
Chromeでは、2015年2月1日以降、Chromeは、ホワイトリストに登録されておらず、かつCTに適応していないEV SSL証明書については、EV SSL証明書固有の表示をしない（グリーンバーや組織名が表示されない）としています。

# TODO
- CTはTLSハンドシェイクのどこに登場するのかを確認しておく

# 参考URL
- RFC
  - https://tools.ietf.org/html/rfc6962
- Certificate Transparency
  - http://www.certificate-transparency.org/
- 画像
  - https://www.cybertrust.ne.jp/sureserver/productinfo/ct.html

