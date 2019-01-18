# signature_algorithms_cert拡張について
signature_algorithms_cert拡張についてはTLS1.3から規定された拡張です。
signature_algorithm拡張と大きく関連があります。

# 詳細

### 仕様
TLS1.2(only)ではsignature_algorithms拡張(_certではないことに注意)が必須で、この拡張は付与しなければならないとして規定されています。
signature_algorithms拡張は、次の箇所で影響がありました。
- (1) Certificateの検証
- (2) ServerKeyExchangeで送付されてくる署名情報

signature_algorithms_cert拡張が追加されたことによって、もしこの拡張が指定された場合には「(1) Certificateの検証」を行うアルゴリズムが(2)とは別で指定されたことを示します。

もし、signature_algorithms_cert拡張が指定されない場合には、signature_algorithms拡張が(1)と(2)の両方が指定されたものとみなします(つまり、TLS1.2と同様です)。

