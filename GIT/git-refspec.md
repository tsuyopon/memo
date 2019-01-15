# 概要
gitの内側の参照仕様(refspec)について

# 詳細

### refsの前に付与する+記号について
- https://git-scm.com/book/ja/v1/Git%E3%81%AE%E5%86%85%E5%81%B4-%E5%8F%82%E7%85%A7%E4%BB%95%E6%A7%98%EF%BC%88Refspec%EF%BC%89

参照仕様はコロン（:）で分割した <src>:<dst> の形式で、オプションとして先頭に + を付けます。<src> はリモート側への参照に対するパターンで、<dst> はそれらの参照がローカル上で書かれる場所を示します。+ の記号は Git にそれが早送り（fast-forward）でない場合でも参照を更新することを伝えます。

### fast-forwardとは
- https://qiita.com/shoichi0599/items/0bbaef4e224201f9c30f

あるコミットに対してコミット履歴上で直接到達できる別のコミットをマージしようとした場合、
Git は単にポインタを前に進めるだけで済ませます。マージ対象が分岐しているわけではないからです。これをfast-forwardと呼びます。

# 参考URL
- https://git-scm.com/book/ja/v1/Git%E3%81%AE%E5%86%85%E5%81%B4-%E5%8F%82%E7%85%A7%E4%BB%95%E6%A7%98%EF%BC%88Refspec%EF%BC%89
