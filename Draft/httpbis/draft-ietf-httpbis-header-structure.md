# Structured Headers for HTTP
- https://datatracker.ietf.org/doc/draft-ietf-httpbis-header-structure/

# 解決する課題
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
