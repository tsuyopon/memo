

SSLネゴシエーションの流れ　() s: server, c: client で *マークについては省略可能)
	1. Client Hello (c->s)
	2. Server Hello (s->c)
	3. Server Certificate* (s->c)
	4. Server Key Exchange* (s->c)
	5. Certificate Request* (s->c)
	6. Server Hello Done(s->c)
		クライアントは、内部にあるルート証明書からサーバ証明書を検証する。
		クライアントは、ルート証明書に含まれる公開鍵と乱数を使って、プリマスターシークレットを生成する。
	7. Client Certificate* (c->s)
	8. Client Key Exchange (c->s)
	9. Certificate Vefiry* (c->s)
		クライアントは公開鍵が含まれるクライアント証明書を送付する。
	10. Change Cipher Spec (c->s)
	11. Finished (c->s)
		クライアントは7〜11を送って、プリマスターシークレットからマスターシークレットを生成する。
		サーバはクライアント証明書を検証する。
		サーバはクライアントから送られてきた暗号化されたプリマスターシークレットを秘密鍵で復号化する。
		サーバは復号化されたプリマスターシークレットからマスターシークレッットを作成する。
		クライアントとサーバでは、マスターシークレットからMACシークレットとセッション鍵を生成する。
	12. Change Cipher Spec (s->c)
	13. Finished (s->c)
		次からはクライアントとサーバの通信が発生する。


	参考資料: https://www.jp.websecurity.symantec.com/welcome/pdf/wp_ssl_negotiation.pdf

AES(Advanced Encryption Standard) とは何か?
	アメリカではDESやトリプルDESといった暗号方式が使われていた。
	しかし、この方法は古くなったのでアメリカ政府は公募によってより強力な暗号化方式を選択した。
	それが、Rijndael (ラインダール) というアルゴリズムで、これが AES として採択されることになりました。
	AESはSPN構造のブロック暗号で、ブロック長は128ビット、鍵長は128ビット・192ビット・256ビットの3つが利用できる。
	無線LANで使われることが多く、安全とされるWPA2に採用されている。
		(WEP, WPA, WPA2は暗号化に関する規格を表し、TKIPやAESは暗号化方式を表す概念)
		この辺が参考になる：http://wa3.i-3-i.info/word15121.html



	専用のCPU命令がある。(出してみたい*TODO)
		https://ja.wikipedia.org/wiki/AES-NI
		https://ja.wikipedia.org/wiki/CLMUL_instruction_set

	AES仕様書
		http://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf

	AES概説
		http://web.archive.org/web/20090503235219/http://www-ailab.elcom.nitech.ac.jp/security/aes/overview.html

	NISTによる資料(Report on Development of the AES)
		http://csrc.nist.gov/archive/aes/round2/r2report.pdf

DES(Data Encryption Standard)
	AESより前の方式
	DESは次の問題があった。(https://ja.wikipedia.org/wiki/Advanced_Encryption_Standard)
		・時代の経過による相対的な強度の低下
		・NSAの関与があるその設計の不透明性

	https://ja.wikipedia.org/wiki/Data_Encryption_Standard

DESとAESの技術的な違いについて
	DES: ファイステル構造
		入力されたデータを上下32bitずつに分けて、それに対して16段の暗号化処理を繰り返し適用する。
		資料: http://www.atmarkit.co.jp/ait/articles/1505/21/news030.html

	AES: SPN構造(Substitution Permutation Network)
		入力されたデータに対して同じような処理を何回か繰り返し適用する。


対象暗号(共通鍵)
	ストリーム暗号: 
		データを逐次暗号化(RC4, Chacha20)
	ブロック暗号:
		データをブロック毎に暗号化(DES, AES)

DH鍵交換とは
	1976年にWhitfield DiffieとMartin E. Hellmanによって考案された鍵交換方式
	分かった気になれた資料(スライドp34以降)
		https://www.slideshare.net/kenjiurushima/qpstudy-20151114-ssltls

セキュリティプロトコルのことを暗号プロトコルと呼ぶこともある。セキュリティプロトコルだとより広義な解釈を持つがどのようなものを含むか
	セキュリティプロトコル: SSL, S-HTTP, PGP, S/MIME, SET, SSH(以上L7), TLS, Socks(以上L4), IPSEC(L3), PPTP, L2F, L2TP(以上、L2)など
		参考: http://www.ieice-hbkb.org/files/03/03gun_07hen_06.pdf

	暗号プロトコル: 
		暗号を組み合わせて用いた通信手順(プロトコル)
		暗号プロトコル評価リスト
			https://www.nict.go.jp/press/2015/10/20-2.html
			http://crypto-protocol.nict.go.jp/


鍵交換アルゴリズムにはどのようなものがあるか?
	RSA(素因数分解), DH(楕円曲線暗号)などがある。

AliceとBobだけが知っているハッシュ鍵とはどのようにして手にはいるのか? プリマスターシークレットとは何が違うのか?

	以下はRSA手順の流れとなります。
		1. クライアントは認証局の RSA 公開鍵で証明書を検証する。
		2. クライアントは証明書からサーバーの RSA 公開鍵を取り出します。
		3. クライアントは共通鍵のタネとなるプリマスターシークレットと呼ばれる値を生成する。
		4. クライアントはプリマスターシークレットを暗号化してサーバーへ送信する。
		5. クライアントとサーバーそれぞれでプリマスターシークレットから共通鍵を生成する。

	以下はDHE_RSAの流れ
		1. まずサーバーは動的にDHパラメータを生成します。DHパラメータに対してサーバーのRSA秘密鍵で署名をしておきます。
		2. サーバはDHパラメータをクライアントに送信します
		3. クライアントはサーバ証明書からにペアとなるRSA公開鍵が含まれているのでそれを取り出す。
		4. クライアントはその公開鍵を使って受け取ったDHパラメータの署名を検証する。
		5. クライアントとサーバはそれぞれでDHパラメータから共通鍵を設定します。


DES・トリプルDESの仕組みは?	
   DESを３回かけるものが3DES

暗号モードとは	、DESやAESについてさらに掘り下げた暗号の仕組みのこと
	CBCモード(Cipher Block Chaining)
	CFBモード(Cipher FeedBack)
	OFBモード(Output FeedBack)
	CTRモード(CounTR)

連番はプロトコルのどこのフィールドに入ることになるのか?
	https://tools.ietf.org/html/rfc5246
		seq_numの箇所

会話の最後に送られる特別なメッセージとはなんのなのか?


どのようにして会話を途中で中断させることができるのか?


AESの暗号方式方法についてもう少し深堀したい



----------
インターネットの脅威の種類
	盗聴・改ざん・なりすまし・否認

TLS CipherSuites
	TLS_<鍵交換>_<デジタル署名>_WITH_<対象暗号>_<鍵長>_<暗号モード>_<メッセージ認証>

	(例)
	TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256
	TLS_RSA_WITH_AES_128_GCM_SHA256  (この場合：鍵交換とデジタル署名両方にRSAを利用するということになる)

	$ openssl ciphers -v
	などで対応一覧を表示できる。

メッセージ認証(HMAC)
	1. 事前に共通鍵を共有しておく
	2. データと共通鍵を組み合わせた一方向ハッシュ関数によりハッシュ値を生成する。
	3. データの完全性とハッシュ作成者を認証する。

	メリット
		データ完全性を担保できる。
		送信元を認証できる
	※デジタル署名との違いとしては、共通鍵か公開鍵かの部分だけ!?

鍵交換の仕組み
	DHやECDH(楕円曲線DH)が存在する。

デジタル署名
	1. Aliceが秘密鍵を使ってデータハッシュ値を暗号化して、デジタル署名作成(つまり、デジタル署名の中にはデータハッシュ値が含まれる)
	2. AliceがBobにデータとデジタル署名を送付する。
	3. Bobは公開鍵を持っている。
	4. Bobはデジタル署名を復号化する。データハッシュ値を取り出す。
	5. Bobは元のデータのデータハッシュ値を算出する。
	6. 4と5で取得したデータを検証する。

	メリット
		データの完全性を担保できる。
		送信元を認証できる。

一方向ハッシュの種類
	MD5, SHA1, SHA2, SHA3

----------　　興味関連

ガイドライン
	情報処理推進機構では次のガイドラインを提供している。
		https://www.ipa.go.jp/security/vuln/ssl_crypt_config.html

	上記ページから以下の資料をダウンロードできる。
		SSL/TLS暗号設定ガイドライン （全93ページ、7.52MB）PDF
		SSL/TLS暗号設定チェックリスト（PDF形式　872KB）PDF
		SSL/TLS暗号設定チェックリスト（Excel形式　1.44MB）	

SAN(Subject Alter Name)
	SSLサーバ証明書に含まれるCN(コモンネーム)とは別に「SAN」という拡張領域が存在する。
	これを利用することによって1枚の証明書で複数のドメインが対応できる。

	SANを発行できるかどうかは認証局による。
	SANにはクライアント側のサポートも必要となる。フィーチャーフォンや古いAndroid端末などは要注意

	SNIと似ているような気はするが、SNI自体は1個のIPとポートの組み合わせで複数証明書を切り替える技術


EV証明書(Extended Validation)になる技術的に何が変わってくるのか?
	EV SSLにおいては、URLの正当性をCAが担保する目的から、通常のSSLで使われるようなワイルドカード証明書の発行は認めらない。
	仮にそのような証明書を無理に発行したとしても、Webブラウザ側で受け入れを拒否される

	参考: https://ja.wikipedia.org/wiki/Extended_Validation_%E8%A8%BC%E6%98%8E%E6%9B%B8


証明書チェーンの見方について





GCM



AEAD






