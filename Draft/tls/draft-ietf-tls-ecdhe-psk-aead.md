# ECDHE_PSK with AES-GCM and AES-CCM Cipher Suites for Transport Layer Security (TLS) Protocol version 1.2

# 解決したい課題
- TLS1.2のPSK認証において近年のセキュリティ設計要件として重要なPFS, AEADであるCipherSuitesを定義したい。
  - PSK認証は最近では3GPPやIoTのような低電力の場所で好まれている。
  - PFSは近年のセキュリティ事情で広く取り入れられており、ECDHEを使うことで小さい鍵長で高機能なPFSを提供することができる。また、ECDHEはHTTP/2やCoAPにおける実装として義務化されている。
  - AEADは暗号化と整合性検証のアルゴリズムとしてTLSで強く薦められている。AES-GCM, AES-CCMがこのドキュメントで規定される。

# 解決方法
- TLS1.2におけるPSK認証、PFS、AEADを提供する新しいCipherSuitesを定義する。

# 仕様
TLS1.2のために、次のCipherSuitesが定義される。
```
TLS_ECDHE_PSK_WITH_AES_128_GCM_SHA256   = {0xTBD,0xTBD};
TLS_ECDHE_PSK_WITH_AES_256_GCM_SHA384   = {0xTBD,0xTBD};
TLS_ECDHE_PSK_WITH_AES_128_CCM_8_SHA256 = {0xTBD,0xTBD};
TLS_ECDHE_PSK_WITH_AES_128_CCM_SHA256   = {0xTBD,0xTBD};
```
# 参考URL
- https://tools.ietf.org/html/draft-ietf-tls-ecdhe-psk-aead-05
