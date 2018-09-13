# Structured Headers for HTTP
- https://tools.ietf.org/html/draft-ietf-httpbis-header-structure-07

# 解決する課題
- HTTPヘッダは次で新しいヘッダが来た場合のガイドラインが存在してはいるが、多くの落とし穴などが存在する。
  - https://tools.ietf.org/html/rfc7231#section-8.3.1
- HTTPヘッダのパース処理はうんざりするような作業となっていて、一度HTTPヘッダが定義されるとそれに合わせてパーサーも書き換えてあげなければならない。
- このドラフトで解決したい課題は、HTTPのヘッダ構造を決定してしまって現在及び今後についてもそちらのヘッダ構造を統一仕様にしておきたいといった課題である。

# 解決方法
- ヘッダ構造をこのドラフトで定義している。
  - ヘッダのデータタイプとしては次の種類を規定している(Section3)
    - Dictionaries
    - Lists
    - Parameterised Lists
    - Items
    - Integers
    - Floats
    - Strings
    - Identifiers
    - Binary Content
  - HTTP/1のためにStrucure Headersのシリアライズ、パース処理の規定(Section4)
    - Structured HeadersをHTTP/1へとシリアライジングする
    - HTTP/1ヘッダフィールドをStructured Headersに書き換える 


# TODO
- いくつかのデータタイプの詳細を読みたい
