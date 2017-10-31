# 概要
openssl.cnfの簡単な説明について


# セクション全体像
デフォルト(+alt_namds)の各セクションを表すと次のようなセクションの関連となっている。
#が付与されているのは、デフォルトのopenssl.cnf設定でアンコメントしないと設定が有効とならない箇所となっている。
```
├── CA_default
│   ├── crl_ext#
│   ├── policy_anything#
│   ├── policy_match
│   └── usr_cert
│       └── alt_names#
├── proxy_cert_ext
├── req
│   ├── req_attributes
│   ├── req_distinguished_name
│   ├── v3_ca#
│   └── v3_req#
└── tsa
    └── tsa_config1
```

# 各セクションについて

### caセクション
caセクションにはデフォルトCA設定となるセクションを指定する。caには次の設定しか含まれていない。
```
[ ca ]
default_ca  = CA_default        #  **ここでCAのデフォルト設定となるセクションを指定している**
```

### CA_defaultセクション
```
[ CA_default ]

dir     = ../ca1                # CAとしての各種設定(demoCAなど)が含まれるディレクトリを指定する。
certs       = $dir/certs        # 証明書が配置されるパス
crl_dir     = $dir/crl          # CRLが配置されるディレクトリを指定する
database    = $dir/index.txt    # 現在有効か、revokeされた情報かなどが記載されたファイル。OCSPレスポンダを起動するときにも使われる。
#unique_subject = no            # Set to 'no' to allow creation of
                    # several ctificates with same subject.
new_certs_dir   = $dir/newcerts     # default place for new certs.

certificate = $dir/ca1.crt      # CAの中間証明書
serial      = $dir/serial       # 中にはシリアル番号が記載されていて、そのファイルを指定している
crlnumber   = $dir/crlnumber    # CRLの番号を指定しているようだ。
                    # must be commented out to leave a V1 CRL
crl     = $dir/crl.pem          # The current CRL
private_key = $dir/ca1.key      # CAの秘密鍵を指定する
RANDFILE    = $dir/private/.rand    # private random number file

x509_extensions = usr_cert      # **証明書に追加する拡張を指定する。ここではuser_certセクションを指定している。**

# Comment out the following two lines for the "traditional"
# (and highly broken) format.
name_opt    = ca_default        # Subject Name options
cert_opt    = ca_default        # Certificate field options

# Extension copying option: use with caution.
# copy_extensions = copy

# Extensions to add to a CRL. Note: Netscape communicator chokes on V2 CRLs
# so this is commented out by default to leave a V1 CRL.
# crlnumber must also be commented out to leave a V1 CRL.
# crl_extensions    = crl_ext

default_days    = 365           # how long to certify for
default_crl_days= 30            # how long before next CRL
default_md  = default       # use public key default MD
preserve    = no            # keep passed DN ordering

# A few difference way of specifying how similar the request should look
# For type CA, the listed attributes must be the same, and the optional
# and supplied fields are just that :-)
policy      = policy_match      # **policy_matchセクションをポリシー内容として指定している。**
```

### reqセクション
CAへの証明書発行要求に関する設定である
```
[ req ]
default_bits        = 2048
default_keyfile     = privkey.pem
distinguished_name  = req_distinguished_name   # **req_distinguished_nameセクションをDN(Distinguished Name)情報として指定している**
attributes      = req_attributes               # セクションを指定している。
x509_extensions = v3_ca                        # The extentions to add to the self signed cert

# Passwords for private keys if not present they will be prompted for
# input_password = secret
# output_password = secret

# This sets a mask for permitted string types. There are several options. 
# default: PrintableString, T61String, BMPString.
# pkix   : PrintableString, BMPString (PKIX recommendation before 2004)
# utf8only: only UTF8Strings (PKIX recommendation after 2004).
# nombstr : PrintableString, T61String (no BMPStrings or UTF8Strings).
# MASK:XXXX a literal mask value.
# WARNING: ancient versions of Netscape crash on BMPStrings or UTF8Strings.
string_mask = utf8only

# req_extensions = v3_req # The extensions to add to a certificate request
```

### req_attributesセクション
このセクションはreqセクションのattributesで指定されている。
```
[ req_attributes ]
challengePassword       = A challenge password
challengePassword_min       = 4
challengePassword_max       = 20

unstructuredName        = An optional company name
```

### usr_certセクション
```
[ usr_cert ]

# These extensions are added when 'ca' signs a request.

# This goes against PKIX guidelines but some CAs do it and some software
# requires this to avoid interpreting an end user certificate as a CA.

basicConstraints=CA:FALSE             # "CA:TRUE"だとCAとして署名を許可し、"CA:FALSE"だとCAとして署名することはできません。

# Here are some examples of the usage of nsCertType. If it is omitted
# the certificate can be used for anything *except* object signing.

# This is OK for an SSL server.
nsCertType          = server          # サーバ証明書の場合

# For an object signing certificate this would be used.
# nsCertType = objsign

# For normal client use this is typical
# nsCertType = client, email

# and for everything including object signing:
# nsCertType = client, email, objsign

# This is typical in keyUsage for a client certificate.
# keyUsage = nonRepudiation, digitalSignature, keyEncipherment

# This will be displayed in Netscape's comment listbox.
nsComment           = "OpenSSL Generated Certificate"        # "openssl x509 -in xxx.crt -noout -text"などで表示される項目

# PKIX recommendations harmless if included in all certificates.
subjectKeyIdentifier=hash
authorityKeyIdentifier=keyid,issuer

# This stuff is for subjectAltName and issuerAltname.
# Import the email address.
# subjectAltName=email:copy
# An alternative to produce certificates that aren't
# deprecated according to PKIX.
# subjectAltName=email:move
subjectAltName=@alt_names                                    # SANオプションのセクションを指定しています。これによりalt_namesというセクションを作成します。

# Copy subject details
# issuerAltName=issuer:copy

#nsCaRevocationUrl      = http://www.domain.dom/ca-crl.pem
#nsBaseUrl
#nsRevocationUrl
#nsRenewalUrl
#nsCaPolicyUrl
#nsSslServerName

# This is required for TSA certificates.
# extendedKeyUsage = critical,timeStamping
```

### v3_reqセクション

```
[ v3_req ]

# Extensions to add to a certificate request

basicConstraints = CA:FALSE
keyUsage = nonRepudiation, digitalSignature, keyEncipherment
```


### v3_caセクション
```
# Extensions for a typical CA


# PKIX recommendation.

subjectKeyIdentifier=hash

#authorityKeyIdentifier=keyid:always,issuer

# This is what PKIX recommends but some broken software chokes on critical
# extensions.
#basicConstraints = critical,CA:true
# So we do this instead.
basicConstraints = CA:true

# Key usage: this is typical for a CA certificate. However since it will
# prevent it being used as an test self-signed certificate it is best
# left out by default.
# keyUsage = cRLSign, keyCertSign

# Some might want this also
# nsCertType = sslCA, emailCA

# Include email address in subject alt name: another PKIX recommendation
# subjectAltName=email:copy
# Copy issuer details
# issuerAltName=issuer:copy

# DER hex encoding of an extension: beware experts only!
# obj=DER:02:03
# Where 'obj' is a standard or added object
# You can even override a supported extension:
# basicConstraints= critical, DER:30:03:01:01:FF
```

- nsCertTypeにはカンマ区切りで次の値を指定できる(詳細はRFC2459参照)
  - server:  SSLサーバ
  - client:  SSLクライアント
  - email:   S/MIME
  - objsign: Object Sign
  - sslCA:   SSL CA
  - emailCA: S/MIME CA
  - objCA:   Object Sign CA


### policy_matchセクション, policy_anythingセクション
このセクションはCA_defaultセクションのpolicyで指定されているセクションである。

これらセクションで指定される値としては次の３つである。
- match
  - CAの内容と一致しなければならない
- optional
  - なくても良い
- supplied
  - なければならない

以下はpolicy_matchの場合のデフォルト設定例。CAの設定となることが多いようだ。
```
[ policy_match ]
countryName     = match
stateOrProvinceName = match
organizationName    = match
organizationalUnitName  = optional
commonName      = supplied
emailAddress        = optional
```

このセクションはpolicy_matchより緩いポリシーを設定する。こちらに変更したい場合にはCA_defaultセクションのpolicyを変更すれば良い。
```
[ policy_anything ]
countryName     = optional
stateOrProvinceName = optional
localityName        = optional
organizationName    = optional
organizationalUnitName  = optional
commonName      = supplied
emailAddress        = optional
```

### req_distinguished_nameセクション
このセクションはreqセクションのdistinguished_nameで指定されているセクションです。
サーバ証明書に記載される項目を指定しているようです。
```
[ req_distinguished_name ]
countryName         = Country Name (2 letter code)
countryName_default     = AU
countryName_min         = 2
countryName_max         = 2

stateOrProvinceName     = State or Province Name (full name)
stateOrProvinceName_default = Some-State

localityName            = Locality Name (eg, city)

0.organizationName      = Organization Name (eg, company)
0.organizationName_default  = Internet Widgits Pty Ltd

# we can do this but it is not needed normally :-)
#1.organizationName     = Second Organization Name (eg, company)
#1.organizationName_default = World Wide Web Pty Ltd

organizationalUnitName      = Organizational Unit Name (eg, section)
#organizationalUnitName_default =

commonName          = Common Name (e.g. server FQDN or YOUR name)
commonName_max          = 64

emailAddress            = Email Address
emailAddress_max        = 64

# SET-ex3           = SET extension number 3
```

### tsaセクション, tsa_config1セクション
TSAはTime Stamp Authorityの略称らしい。

```
[ tsa ]

default_tsa = tsa_config1   # the default TSA section
```

続いて、上記で指定されているtsa_config1セクションを見てみる
```
[ tsa_config1 ]

# These are used by the TSA reply generation only.
dir     = ./ca1 # TSA root directory
serial      = $dir/tsaserial    # The current serial number (mandatory)
crypto_device   = builtin       # OpenSSL engine to use for signing
signer_cert = $dir/tsacert.pem  # The TSA signing certificate
                    # (optional)
certs       = $dir/cacert.pem   # Certificate chain to include in reply
                    # (optional)
signer_key  = $dir/private/tsakey.pem # The TSA private key (optional)

default_policy  = tsa_policy1       # Policy if request did not specify it
                    # (optional)
other_policies  = tsa_policy2, tsa_policy3  # acceptable policies (optional)
digests     = md5, sha1     # Acceptable message digests (mandatory)
accuracy    = secs:1, millisecs:500, microsecs:100  # (optional)
clock_precision_digits  = 0 # number of digits after dot. (optional)
ordering        = yes   # Is ordering defined for timestamps?
                # (optional, default: no)
tsa_name        = yes   # Must the TSA name be included in the reply?
                # (optional, default: no)
ess_cert_id_chain   = no    # Must the ESS cert id chain be included?
                # (optional, default: no)
```

### alt_namesセクション
このセクションはsubjectAltNameで指定されたもので決定される。
```
[ alt_names ]
DNS.1 = example1.com
DNS.2 = example2.com
DNS.3 = example3.com
DNS.4 = example4.com
DNS.5 = example5.com
DNS.6 = hoge*.com
```
