# Deprecating TLSv1.0 and TLSv1.1


# 解決したい課題
2008年にTLS1.2が策定されて、TLS1.3も策定されてきている中で古いバージョンをdeprecatedしたほうが良い。
PCIだとTLS1.2以上が推奨となってきてる。
- https://www.pcisecuritystandards.org/documents/Migrating-from-SSL-Early-TLS-Info-Supp-v1_1.pdf

deprecateとしたい意図としては、以下のような技術的な問題点も含まれている
- TLS1.0ではTLS_DHE_DSS_WITH_3DES_EDE_CBC_SHAを実装する義務があるが、セキュリティ強度としても適切ではない。
- 最近推奨されるAEADのようなciphersuitesへのサポートが不足している。これはTLS1.2以降に存在している。
- 4つのプロトコルバージョンのサポートは設定の誤りを生みがちである。
- 幅広く使われたライブラリのサポートバージョンからTLSv1.1とTLSv1.0を落としたい。これを使い続けるのは望ましくない。


# 解決方法
TLS1.0とTLS1.1を廃止する

# 詳細

### 使用とサポート
次の結果によるとTLSv1.2 (98.9%)、TLS1.0(0.8%)、さらに小さいのがTLS1.1
- Alexa Top 1 Million Analysis - February 2018
  - https://scotthelme.co.uk/alexa-top-1-million-analysis-february-2018/

多くのウェブサイトがPCI council deadlineのためにTLSv1.1とTLSv1.0をdeprecatedしました。
2018年6月にはTLS1.1のサポートも打ち切られるようになります。

# 参考URL
- https://tools.ietf.org/html/draft-ietf-tls-oldversions-deprecate-04

