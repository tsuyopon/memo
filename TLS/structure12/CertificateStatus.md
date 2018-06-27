# Certificate Status

厳密にはこのパケットはクライアント、サーバ双方がstatus_requestに対応している場合に送られるものと思われます。

次の３パターンが観察できました。
- certsが付与されない場合
- 1枚certsを付与される場合
- 2枚certsが付与される場合(パケットを添付していない)


- パターン1
```
    TLSv1.2 Record Layer: Handshake Protocol: Certificate Status
        Content Type: Handshake (22)
        Version: TLS 1.2 (0x0303)
        Length: 480
        Handshake Protocol: Certificate Status
            Handshake Type: Certificate Status (22)
            Length: 476
            Certificate Status Type: OCSP (1)
            OCSP Response Length: 472
            OCSP Response
                responseStatus: successful (0)
                responseBytes
                    ResponseType Id: 1.3.6.1.5.5.7.48.1.1 (id-pkix-ocsp-basic)
                    BasicOCSPResponse
                        tbsResponseData
                            responderID: byKey (2)
                                byKey: 90af6a3a945a0bd890ea125673df43b43a28dae7
                            producedAt: 2018-06-26 08:38:24 (UTC)
                            responses: 1 item
                                SingleResponse
                                    certID
                                        hashAlgorithm (SHA-1)
                                            Algorithm Id: 1.3.14.3.2.26 (SHA-1)
                                        issuerNameHash: 7ae13ee8a0c42a2cb428cbe7a605461940e2a1e9
                                        issuerKeyHash: 90af6a3a945a0bd890ea125673df43b43a28dae7
                                        serialNumber: 0x00e7758cf685eb4d70126c8cf43edd9c54
                                    certStatus: good (0)
                                        good
                                    thisUpdate: 2018-06-26 08:38:24 (UTC)
                                    nextUpdate: 2018-07-03 08:38:24 (UTC)
                        signatureAlgorithm (sha256WithRSAEncryption)
                            Algorithm Id: 1.2.840.113549.1.1.11 (sha256WithRSAEncryption)
                        Padding: 0
                        signature: 163a0f664ea5fc1c401a0cf0f223f8774718aae2dcfe18c7...
```

- パターン2
```
Secure Sockets Layer
    TLSv1.2 Record Layer: Handshake Protocol: Certificate Status
        Content Type: Handshake (22)
        Version: TLS 1.2 (0x0303)
        Length: 480
        Handshake Protocol: Certificate Status
            Handshake Type: Certificate Status (22)
            Length: 476
            Certificate Status Type: OCSP (1)
--
                responseStatus: successful (0)
                responseBytes
                    ResponseType Id: 1.3.6.1.5.5.7.48.1.1 (id-pkix-ocsp-basic)
                    BasicOCSPResponse
                        tbsResponseData
                            responderID: byKey (2)
                                byKey: 2737ab19fab105fac3f77481d0e65ce5b93ea88b
                            producedAt: 2018-06-24 17:34:42 (UTC)
                            responses: 1 item
                                SingleResponse
                                    certID
                                        hashAlgorithm (SHA-1)
                                            Algorithm Id: 1.3.14.3.2.26 (SHA-1)
                                        issuerNameHash: 12eadf46cc0880387360b65a691601cc0cb5e9e2
                                        issuerKeyHash: a92b87e1ce24473b1bbfcf853702559d0d9458e6
                                        serialNumber: 0x469b0d35cfb9e99dc8ac05f0
                                    certStatus: good (0)
                                        good
                                    thisUpdate: 2018-06-24 17:34:42 (UTC)
                                    nextUpdate: 2018-06-28 17:34:42 (UTC)
                        signatureAlgorithm (sha256WithRSAEncryption)
                            Algorithm Id: 1.2.840.113549.1.1.11 (sha256WithRSAEncryption)
                        Padding: 0
                        signature: 53d0db740350168c43cd118b9aab9d5ce675ca5ddf18ec8d...
                        certs: 1 item
                            Certificate (id-at-commonName=GlobalSign CloudSSL CA - SHA256 - G3 OCSP Resp,id-at-serialNumber=201804100004,id-at-organizationName=GlobalSign Pte Ltd,id-at-countryName=SG)
                                signedCertificate
                                    version: v3 (2)
                                    serialNumber: 0x538755474b70496b92ba2ca9
                                    signature (sha256WithRSAEncryption)
                                        Algorithm Id: 1.2.840.113549.1.1.11 (sha256WithRSAEncryption)
                                    issuer: rdnSequence (0)
                                        rdnSequence: 3 items (id-at-commonName=GlobalSign CloudSSL CA - SHA256 - G3,id-at-organizationName=GlobalSign nv-sa,id-at-countryName=BE)
                                            RDNSequence item: 1 item (id-at-countryName=BE)
                                                RelativeDistinguishedName item (id-at-countryName=BE)
                                                    Id: 2.5.4.6 (id-at-countryName)
                                                    CountryName: BE
                                            RDNSequence item: 1 item (id-at-organizationName=GlobalSign nv-sa)
                                                RelativeDistinguishedName item (id-at-organizationName=GlobalSign nv-sa)
                                                    Id: 2.5.4.10 (id-at-organizationName)
                                                    DirectoryString: printableString (1)
                                                        printableString: GlobalSign nv-sa
                                            RDNSequence item: 1 item (id-at-commonName=GlobalSign CloudSSL CA - SHA256 - G3)
                                                RelativeDistinguishedName item (id-at-commonName=GlobalSign CloudSSL CA - SHA256 - G3)
                                                    Id: 2.5.4.3 (id-at-commonName)
                                                    DirectoryString: printableString (1)
                                                        printableString: GlobalSign CloudSSL CA - SHA256 - G3
                                    validity
                                        notBefore: utcTime (0)
                                            utcTime: 18-04-10 07:33:11 (UTC)
                                        notAfter: utcTime (0)
                                            utcTime: 18-07-11 07:33:11 (UTC)
                                    subject: rdnSequence (0)
                                        rdnSequence: 4 items (id-at-commonName=GlobalSign CloudSSL CA - SHA256 - G3 OCSP Resp,id-at-serialNumber=201804100004,id-at-organizationName=GlobalSign Pte Ltd,id-at-countryName=SG)
                                            RDNSequence item: 1 item (id-at-countryName=SG)
                                                RelativeDistinguishedName item (id-at-countryName=SG)
                                                    Id: 2.5.4.6 (id-at-countryName)
                                                    CountryName: SG
                                            RDNSequence item: 1 item (id-at-organizationName=GlobalSign Pte Ltd)
                                                RelativeDistinguishedName item (id-at-organizationName=GlobalSign Pte Ltd)
                                                    Id: 2.5.4.10 (id-at-organizationName)
                                                    DirectoryString: printableString (1)
                                                        printableString: GlobalSign Pte Ltd
                                            RDNSequence item: 1 item (id-at-serialNumber=201804100004)
                                                RelativeDistinguishedName item (id-at-serialNumber=201804100004)
                                                    Id: 2.5.4.5 (id-at-serialNumber)
                                                    PrintableString: 201804100004
                                            RDNSequence item: 1 item (id-at-commonName=GlobalSign CloudSSL CA - SHA256 - G3 OCSP Resp)
                                                RelativeDistinguishedName item (id-at-commonName=GlobalSign CloudSSL CA - SHA256 - G3 OCSP Responder)
                                                    Id: 2.5.4.3 (id-at-commonName)
                                                    DirectoryString: printableString (1)
                                                        printableString: GlobalSign CloudSSL CA - SHA256 - G3 OCSP Responder
                                    subjectPublicKeyInfo
                                        algorithm (rsaEncryption)
                                            Algorithm Id: 1.2.840.113549.1.1.1 (rsaEncryption)
                                        subjectPublicKey: 3082010a0282010100aaaca33bbd7e4a67effeacf429aef7...
                                            modulus: 0x00aaaca33bbd7e4a67effeacf429aef7ce491602ca7223cd...
                                            publicExponent: 65537
                                    extensions: 6 items
                                        Extension (id-ce-subjectKeyIdentifier)
                                            Extension Id: 2.5.29.14 (id-ce-subjectKeyIdentifier)
                                            SubjectKeyIdentifier: 2737ab19fab105fac3f77481d0e65ce5b93ea88b
                                        Extension (id-ce-authorityKeyIdentifier)
                                            Extension Id: 2.5.29.35 (id-ce-authorityKeyIdentifier)
                                            AuthorityKeyIdentifier
                                                keyIdentifier: a92b87e1ce24473b1bbfcf853702559d0d9458e6
                                        Extension (id-pkix-ocsp-nocheck)
                                            Extension Id: 1.3.6.1.5.5.7.48.1.5 (id-pkix-ocsp-nocheck)
                                            NULL
                                        Extension (id-ce-certificatePolicies)
                                            Extension Id: 2.5.29.32 (id-ce-certificatePolicies)
                                            CertificatePoliciesSyntax: 1 item
                                                PolicyInformation
                                                    policyIdentifier: 1.3.6.1.4.1.4146.1.95 (iso.3.6.1.4.1.4146.1.95)
                                                    policyQualifiers: 1 item
                                                        PolicyQualifierInfo
                                                            Id: 1.3.6.1.5.5.7.2.1 (id-qt-cps)
                                                            DirectoryString: https://www.globalsign.com/repository/
                                        Extension (id-ce-keyUsage)
                                            Extension Id: 2.5.29.15 (id-ce-keyUsage)
                                            critical: True
                                            Padding: 7
                                            KeyUsage: 80 (digitalSignature)
                                                1... .... = digitalSignature: True
                                                .0.. .... = contentCommitment: False
                                                ..0. .... = keyEncipherment: False
                                                ...0 .... = dataEncipherment: False
                                                .... 0... = keyAgreement: False
                                                .... .0.. = keyCertSign: False
                                                .... ..0. = cRLSign: False
                                                .... ...0 = encipherOnly: False
                                                0... .... = decipherOnly: False
                                        Extension (id-ce-extKeyUsage)
                                            Extension Id: 2.5.29.37 (id-ce-extKeyUsage)
                                            KeyPurposeIDs: 1 item
                                                KeyPurposeId: 1.3.6.1.5.5.7.3.9 (OCSPSigning)
                                algorithmIdentifier (sha256WithRSAEncryption)
                                    Algorithm Id: 1.2.840.113549.1.1.11 (sha256WithRSAEncryption)
                                Padding: 0
                                encrypted: 73fa27968be2c13fa03760c36e26cf37c69c74de6874cd27...
```
