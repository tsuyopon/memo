# Certificate

Certificateは最も差分が大きい箇所である。
以下はサンプル
```
Secure Sockets Layer
    TLSv1.2 Record Layer: Handshake Protocol: Certificate
        Content Type: Handshake (22)
        Version: TLS 1.2 (0x0303)
        Length: 2876
        Handshake Protocol: Certificate
            Handshake Type: Certificate (11)
            Length: 2872
            Certificates Length: 2869
            Certificates (2869 bytes)
                Certificate Length: 1687
                Certificate: 308206933082057ba00302010202100830c3a049785bf85c... (id-at-commonName=seal.digicert.com,id-at-organizationName=DigiCert, Inc.,id-at-localityName=Lehi,id-at-stateOrProvinceName=Utah,id-at-countryName=US)
                    signedCertificate
                        version: v3 (2)
                        serialNumber: 0x0830c3a049785bf85c1f475fadf8703b
                        signature (sha256WithRSAEncryption)
                            Algorithm Id: 1.2.840.113549.1.1.11 (sha256WithRSAEncryption)
                        issuer: rdnSequence (0)
                            rdnSequence: 3 items (id-at-commonName=DigiCert SHA2 Secure Server CA,id-at-organizationName=DigiCert Inc,id-at-countryName=US)
                                RDNSequence item: 1 item (id-at-countryName=US)
                                    RelativeDistinguishedName item (id-at-countryName=US)
                                        Id: 2.5.4.6 (id-at-countryName)
                                        CountryName: US
                                RDNSequence item: 1 item (id-at-organizationName=DigiCert Inc)
                                    RelativeDistinguishedName item (id-at-organizationName=DigiCert Inc)
                                        Id: 2.5.4.10 (id-at-organizationName)
                                        DirectoryString: printableString (1)
                                            printableString: DigiCert Inc
                                RDNSequence item: 1 item (id-at-commonName=DigiCert SHA2 Secure Server CA)
                                    RelativeDistinguishedName item (id-at-commonName=DigiCert SHA2 Secure Server CA)
                                        Id: 2.5.4.3 (id-at-commonName)
                                        DirectoryString: printableString (1)
                                            printableString: DigiCert SHA2 Secure Server CA
                        validity
                            notBefore: utcTime (0)
                                utcTime: 18-03-28 00:00:00 (UTC)
                            notAfter: utcTime (0)
                                utcTime: 20-04-29 12:00:00 (UTC)
                        subject: rdnSequence (0)
                            rdnSequence: 5 items (id-at-commonName=seal.digicert.com,id-at-organizationName=DigiCert, Inc.,id-at-localityName=Lehi,id-at-stateOrProvinceName=Utah,id-at-countryName=US)
                                RDNSequence item: 1 item (id-at-countryName=US)
                                    RelativeDistinguishedName item (id-at-countryName=US)
                                        Id: 2.5.4.6 (id-at-countryName)
                                        CountryName: US
                                RDNSequence item: 1 item (id-at-stateOrProvinceName=Utah)
                                    RelativeDistinguishedName item (id-at-stateOrProvinceName=Utah)
                                        Id: 2.5.4.8 (id-at-stateOrProvinceName)
                                        DirectoryString: printableString (1)
                                            printableString: Utah
                                RDNSequence item: 1 item (id-at-localityName=Lehi)
                                    RelativeDistinguishedName item (id-at-localityName=Lehi)
                                        Id: 2.5.4.7 (id-at-localityName)
                                        DirectoryString: printableString (1)
                                            printableString: Lehi
                                RDNSequence item: 1 item (id-at-organizationName=DigiCert, Inc.)
                                    RelativeDistinguishedName item (id-at-organizationName=DigiCert, Inc.)
                                        Id: 2.5.4.10 (id-at-organizationName)
                                        DirectoryString: printableString (1)
                                            printableString: DigiCert, Inc.
                                RDNSequence item: 1 item (id-at-commonName=seal.digicert.com)
                                    RelativeDistinguishedName item (id-at-commonName=seal.digicert.com)
                                        Id: 2.5.4.3 (id-at-commonName)
                                        DirectoryString: printableString (1)
                                            printableString: seal.digicert.com
                        subjectPublicKeyInfo
                            algorithm (rsaEncryption)
                                Algorithm Id: 1.2.840.113549.1.1.1 (rsaEncryption)
                            subjectPublicKey: 3082010a0282010100cbdf9e91a564b44a114a38ce90c169...
                                modulus: 0x00cbdf9e91a564b44a114a38ce90c16937fe881fee19cfae...
                                publicExponent: 65537
                        extensions: 10 items
                            Extension (id-ce-authorityKeyIdentifier)
                                Extension Id: 2.5.29.35 (id-ce-authorityKeyIdentifier)
                                AuthorityKeyIdentifier
                                    keyIdentifier: 0f80611c823161d52f28e78d4638b42ce1c6d9e2
                            Extension (id-ce-subjectKeyIdentifier)
                                Extension Id: 2.5.29.14 (id-ce-subjectKeyIdentifier)
                                SubjectKeyIdentifier: ac00854271b930f0dbed108e163063d9e6192d66
                            Extension (id-ce-subjectAltName)
                                Extension Id: 2.5.29.17 (id-ce-subjectAltName)
                                GeneralNames: 1 item
                                    GeneralName: dNSName (2)
                                        dNSName: seal.digicert.com
                            Extension (id-ce-keyUsage)
                                Extension Id: 2.5.29.15 (id-ce-keyUsage)
                                critical: True
                                Padding: 5
                                KeyUsage: a0 (digitalSignature, keyEncipherment)
                                    1... .... = digitalSignature: True
                                    .0.. .... = contentCommitment: False
                                    ..1. .... = keyEncipherment: True
                                    ...0 .... = dataEncipherment: False
                                    .... 0... = keyAgreement: False
                                    .... .0.. = keyCertSign: False
                                    .... ..0. = cRLSign: False
                                    .... ...0 = encipherOnly: False
                                    0... .... = decipherOnly: False
                            Extension (id-ce-extKeyUsage)
                                Extension Id: 2.5.29.37 (id-ce-extKeyUsage)
                                KeyPurposeIDs: 2 items
                                    KeyPurposeId: 1.3.6.1.5.5.7.3.1 (id-kp-serverAuth)
                                    KeyPurposeId: 1.3.6.1.5.5.7.3.2 (id-kp-clientAuth)
                            Extension (id-ce-cRLDistributionPoints)
                                Extension Id: 2.5.29.31 (id-ce-cRLDistributionPoints)
                                CRLDistPointsSyntax: 2 items
                                    DistributionPoint
                                        distributionPoint: fullName (0)
                                            fullName: 1 item
                                                GeneralName: uniformResourceIdentifier (6)
                                                    uniformResourceIdentifier: http://crl3.digicert.com/ssca-sha2-g6.crl
                                    DistributionPoint
                                        distributionPoint: fullName (0)
                                            fullName: 1 item
                                                GeneralName: uniformResourceIdentifier (6)
                                                    uniformResourceIdentifier: http://crl4.digicert.com/ssca-sha2-g6.crl
                            Extension (id-ce-certificatePolicies)
                                Extension Id: 2.5.29.32 (id-ce-certificatePolicies)
                                CertificatePoliciesSyntax: 2 items
                                    PolicyInformation
                                        policyIdentifier: 2.16.840.1.114412.1.1 (US company arc.114412.1.1)
                                        policyQualifiers: 1 item
                                            PolicyQualifierInfo
                                                Id: 1.3.6.1.5.5.7.2.1 (id-qt-cps)
                                                DirectoryString: https://www.digicert.com/CPS
                                    PolicyInformation
                                        policyIdentifier: 2.23.140.1.2.2 (joint-iso-itu-t.23.140.1.2.2)
                            Extension (id-pe-authorityInfoAccessSyntax)
                                Extension Id: 1.3.6.1.5.5.7.1.1 (id-pe-authorityInfoAccessSyntax)
                                AuthorityInfoAccessSyntax: 2 items
                                    AccessDescription
                                        accessMethod: 1.3.6.1.5.5.7.48.1 (id-pkix.48.1)
                                        accessLocation: 6
                                            uniformResourceIdentifier: http://ocsp.digicert.com
                                    AccessDescription
                                        accessMethod: 1.3.6.1.5.5.7.48.2 (id-pkix.48.2)
                                        accessLocation: 6
                                            uniformResourceIdentifier: http://cacerts.digicert.com/DigiCertSHA2SecureServerCA.crt
                            Extension (id-ce-basicConstraints)
                                Extension Id: 2.5.29.19 (id-ce-basicConstraints)
                                critical: True
                                BasicConstraintsSyntax [0 length]
                            Extension (SignedCertificateTimestampList)
                                Extension Id: 1.3.6.1.4.1.11129.2.4.2 (SignedCertificateTimestampList)
                                Serialized SCT List Length: 360
                                Signed Certificate Timestamp (Google 'Rocketeer' log)
                                    Serialized SCT Length: 117
                                    SCT Version: 0
                                    Log ID: ee4bbdb775ce60bae142691fabe19e66a30f7e5fb072d883...
                                    Timestamp: Mar 28, 2018 16:30:04.827000000 UTC
                                    Extensions length: 0
                                    Signature Algorithm: ecdsa_secp256r1_sha256 (0x0403)
                                        Signature Hash Algorithm Hash: SHA256 (4)
                                        Signature Hash Algorithm Signature: ECDSA (3)
                                    Signature Length: 70
                                    Signature: 3044022026c892edd5251a6bb5aa7d391fe862ddbdadda1d...
                                Signed Certificate Timestamp (Unknown Log)
                                    Serialized SCT Length: 119
                                    SCT Version: 0
                                    Log ID: 6f5376ac31f03119d89900a45115ff77151c11d902c10029...
                                    Timestamp: Mar 28, 2018 16:30:05.066000000 UTC
                                    Extensions length: 0
                                    Signature Algorithm: ecdsa_secp256r1_sha256 (0x0403)
                                        Signature Hash Algorithm Hash: SHA256 (4)
                                        Signature Hash Algorithm Signature: ECDSA (3)
                                    Signature Length: 72
                                    Signature: 3046022100ba9cec3d9ba2e5ae7c38ff1ede1fc3875f7d63...
                                Signed Certificate Timestamp (Google 'Skydiver' log)
                                    Serialized SCT Length: 118
                                    SCT Version: 0
                                    Log ID: bbd9dfbc1f8a71b593942397aa927b473857950aab52e81a...
                                    Timestamp: Mar 28, 2018 16:30:04.965000000 UTC
                                    Extensions length: 0
                                    Signature Algorithm: ecdsa_secp256r1_sha256 (0x0403)
                                        Signature Hash Algorithm Hash: SHA256 (4)
                                        Signature Hash Algorithm Signature: ECDSA (3)
                                    Signature Length: 71
                                    Signature: 3045022100f65bc0397034b6fc1a91c38060abf0bbb0f19a...
                    algorithmIdentifier (sha256WithRSAEncryption)
                        Algorithm Id: 1.2.840.113549.1.1.11 (sha256WithRSAEncryption)
                    Padding: 0
                    encrypted: d694c1fd2d47bb2eaf1f7230b8801788ab57ed2e9dc99064...
                Certificate Length: 1176
                Certificate: 308204943082037ca003020102021001fda3eb6eca75c888... (id-at-commonName=DigiCert SHA2 Secure Server CA,id-at-organizationName=DigiCert Inc,id-at-countryName=US)
                    signedCertificate
                        version: v3 (2)
                        serialNumber: 0x01fda3eb6eca75c888438b724bcfbc91
                        signature (sha256WithRSAEncryption)
                            Algorithm Id: 1.2.840.113549.1.1.11 (sha256WithRSAEncryption)
                        issuer: rdnSequence (0)
                            rdnSequence: 4 items (id-at-commonName=DigiCert Global Root CA,id-at-organizationalUnitName=www.digicert.com,id-at-organizationName=DigiCert Inc,id-at-countryName=US)
                                RDNSequence item: 1 item (id-at-countryName=US)
                                    RelativeDistinguishedName item (id-at-countryName=US)
                                        Id: 2.5.4.6 (id-at-countryName)
                                        CountryName: US
                                RDNSequence item: 1 item (id-at-organizationName=DigiCert Inc)
                                    RelativeDistinguishedName item (id-at-organizationName=DigiCert Inc)
                                        Id: 2.5.4.10 (id-at-organizationName)
                                        DirectoryString: printableString (1)
                                            printableString: DigiCert Inc
                                RDNSequence item: 1 item (id-at-organizationalUnitName=www.digicert.com)
                                    RelativeDistinguishedName item (id-at-organizationalUnitName=www.digicert.com)
                                        Id: 2.5.4.11 (id-at-organizationalUnitName)
                                        DirectoryString: printableString (1)
                                            printableString: www.digicert.com
                                RDNSequence item: 1 item (id-at-commonName=DigiCert Global Root CA)
                                    RelativeDistinguishedName item (id-at-commonName=DigiCert Global Root CA)
                                        Id: 2.5.4.3 (id-at-commonName)
                                        DirectoryString: printableString (1)
                                            printableString: DigiCert Global Root CA
                        validity
                            notBefore: utcTime (0)
                                utcTime: 13-03-08 12:00:00 (UTC)
                            notAfter: utcTime (0)
                                utcTime: 23-03-08 12:00:00 (UTC)
                        subject: rdnSequence (0)
                            rdnSequence: 3 items (id-at-commonName=DigiCert SHA2 Secure Server CA,id-at-organizationName=DigiCert Inc,id-at-countryName=US)
                                RDNSequence item: 1 item (id-at-countryName=US)
                                    RelativeDistinguishedName item (id-at-countryName=US)
                                        Id: 2.5.4.6 (id-at-countryName)
                                        CountryName: US
                                RDNSequence item: 1 item (id-at-organizationName=DigiCert Inc)
                                    RelativeDistinguishedName item (id-at-organizationName=DigiCert Inc)
                                        Id: 2.5.4.10 (id-at-organizationName)
                                        DirectoryString: printableString (1)
                                            printableString: DigiCert Inc
                                RDNSequence item: 1 item (id-at-commonName=DigiCert SHA2 Secure Server CA)
                                    RelativeDistinguishedName item (id-at-commonName=DigiCert SHA2 Secure Server CA)
                                        Id: 2.5.4.3 (id-at-commonName)
                                        DirectoryString: printableString (1)
                                            printableString: DigiCert SHA2 Secure Server CA
                        subjectPublicKeyInfo
                            algorithm (rsaEncryption)
                                Algorithm Id: 1.2.840.113549.1.1.1 (rsaEncryption)
                            subjectPublicKey: 3082010a0282010100dcae58904dc1c4301590355b6e3c82...
                                modulus: 0x00dcae58904dc1c4301590355b6e3c8215f52c5cbde3dbff...
                                publicExponent: 65537
                        extensions: 7 items
                            Extension (id-ce-basicConstraints)
                                Extension Id: 2.5.29.19 (id-ce-basicConstraints)
                                critical: True
                                BasicConstraintsSyntax
                                    cA: True
                                    pathLenConstraint: 0
                            Extension (id-ce-keyUsage)
                                Extension Id: 2.5.29.15 (id-ce-keyUsage)
                                critical: True
                                Padding: 1
                                KeyUsage: 86 (digitalSignature, keyCertSign, cRLSign)
                                    1... .... = digitalSignature: True
                                    .0.. .... = contentCommitment: False
                                    ..0. .... = keyEncipherment: False
                                    ...0 .... = dataEncipherment: False
                                    .... 0... = keyAgreement: False
                                    .... .1.. = keyCertSign: True
                                    .... ..1. = cRLSign: True
                                    .... ...0 = encipherOnly: False
                                    0... .... = decipherOnly: False
                            Extension (id-pe-authorityInfoAccessSyntax)
                                Extension Id: 1.3.6.1.5.5.7.1.1 (id-pe-authorityInfoAccessSyntax)
                                AuthorityInfoAccessSyntax: 1 item
                                    AccessDescription
                                        accessMethod: 1.3.6.1.5.5.7.48.1 (id-pkix.48.1)
                                        accessLocation: 6
                                            uniformResourceIdentifier: http://ocsp.digicert.com
                            Extension (id-ce-cRLDistributionPoints)
                                Extension Id: 2.5.29.31 (id-ce-cRLDistributionPoints)
                                CRLDistPointsSyntax: 2 items
                                    DistributionPoint
                                        distributionPoint: fullName (0)
                                            fullName: 1 item
                                                GeneralName: uniformResourceIdentifier (6)
                                                    uniformResourceIdentifier: http://crl3.digicert.com/DigiCertGlobalRootCA.crl
                                    DistributionPoint
                                        distributionPoint: fullName (0)
                                            fullName: 1 item
                                                GeneralName: uniformResourceIdentifier (6)
                                                    uniformResourceIdentifier: http://crl4.digicert.com/DigiCertGlobalRootCA.crl
                            Extension (id-ce-certificatePolicies)
                                Extension Id: 2.5.29.32 (id-ce-certificatePolicies)
                                CertificatePoliciesSyntax: 1 item
                                    PolicyInformation
                                        policyIdentifier: 2.5.29.32.0 (id-ce-certificatePolicies.0)
                                        policyQualifiers: 1 item
                                            PolicyQualifierInfo
                                                Id: 1.3.6.1.5.5.7.2.1 (id-qt-cps)
                                                DirectoryString: https://www.digicert.com/CPS
                            Extension (id-ce-subjectKeyIdentifier)
                                Extension Id: 2.5.29.14 (id-ce-subjectKeyIdentifier)
                                SubjectKeyIdentifier: 0f80611c823161d52f28e78d4638b42ce1c6d9e2
                            Extension (id-ce-authorityKeyIdentifier)
                                Extension Id: 2.5.29.35 (id-ce-authorityKeyIdentifier)
                                AuthorityKeyIdentifier
                                    keyIdentifier: 03de503556d14cbb66f0a3e21b1bc397b23dd155
                    algorithmIdentifier (sha256WithRSAEncryption)
                        Algorithm Id: 1.2.840.113549.1.1.11 (sha256WithRSAEncryption)
                    Padding: 0
                    encrypted: 233edf4bd23142a5b67e425c1a44cc69d168b45d4be00421...
```
