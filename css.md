# 概要
CSSについてのメモ

### 透過度を設定する
以下はdivに指定する場合の例です。複数ブラウザ対応の例です。
```
div {
    filter:alpha(opacity=50);  /* IE向けの設定 */
    -moz-opacity: 0.5;         /* Firefox（Mozilla）向けの指定 */
    opacity: 0.5;              /* SafariやOpera向けの設定 */
}
```
- 参考
  - http://black-flag.net/css/20110513-3045.html

