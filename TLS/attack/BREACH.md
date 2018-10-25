# 概要
BREACH(Browser Reconnaissance and Exfiltration via Adaptive Compression of Hypertext Attack)攻撃についてまとめます。
CVE-2013-3587に該当します。

# 詳細
### どのような攻撃か
BREACH攻撃もCRIMEと同様に暗号を解読せずに暗号コンテンツを解読する攻撃です、CRIMEはHTTPリクエスト(Cookieなど)を解読する攻撃でしたが、BREACHはHTTPレスポンスを解読する攻撃です。
Content-Encodingがgzipかdeflateである場合にHTTPコンテンツが圧縮されることを利用して、HTTPレスポンスを解読します。

攻撃対象となるのは次の状態となっているコンテンツです。
- HTTPレベルでの圧縮でサーバが提供していること (TLSであるかどうかは要求に含まれない)
- HTTPレスポンスボディ中にユーザーの入力値が反映されていること
- HTTPレスポンスボディ中にsecret値(CSRF tokenのような)が反映されていること


### 攻撃手法
次の２つの資料に攻撃手法が記載されています。
- Research Paper
  - http://breachattack.com/resources/BREACH%20-%20SSL,%20gone%20in%2030%20seconds.pdf
- Black Hat USA Presentation
  - http://breachattack.com/resources/BREACH%20-%20BH%202013%20-%20PRESENTATION.pdf


たとえば、圧縮前の以下のHTMLを48byteとする。
```
<html>
tkn = supersecret
...
guess = supersecreX
```

上記では「supersecre」の10文字が重複するので、圧縮後は48 - 10 = 38byteとなる。
```
<html>
tkn = supersecret
...
guess = supersecreX
```

最後の1文字のXの部分をずらすことによって
以下の例だとXをtに変換すると11文字が重複するので、圧縮後は48 -11 = 37byteとなる。
```
<html>
tkn = supersecret
...
guess = supersecret
```

1byte減ったということは攻撃者は、その前にすでにでてきた文字列であると推測することができる。

TODO: 概要っぽいことしかわかってないので、ちゃんと論文を読みたい

### 対処方法
- CRIMEではTLSでのデータ圧縮で回避可能だったが、BREACHではHTTPコンテンツの圧縮を無効とする
- Disable HTTP compression
- Separating secrets from user input
- Randomizing secrets per request
- Masking secrets (effectively randomizing by XORing with a random secret per request)
- Protecting vulnerable pages with CSRF
- Length hiding (by adding random number of bytes to the responses)
- Rate-limiting requests


### ツール
- BREACH攻撃を試せるツール
  - https://github.com/nealharris/BREACH


# 参考URL
下記３つの資料が最も良い
- CERT/CC Vulnerability Note
  - http://www.kb.cert.org/vuls/id/987798
- Research Paper
  - http://breachattack.com/resources/BREACH%20-%20SSL,%20gone%20in%2030%20seconds.pdf
- Black Hat USA Presentation
  - http://breachattack.com/resources/BREACH%20-%20BH%202013%20-%20PRESENTATION.pdf

以下は参考やポインタとして利用すると良い。
- Wikipedia: BREACH
  - https://en.wikipedia.org/wiki/BREACH
- SSL暗号を無効化する仕組み – BREACH, CRIME, etc
  - https://blog.ohgaki.net/breach-attack-explained-why-and-how
