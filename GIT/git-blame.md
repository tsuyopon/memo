# 概要
git blameは過去に誰がどのコミット(ハッシュ値)で変更したのかを確認することができます。

たとえば、tls13-specなどではUI上からblameを見ようとすると多すぎてエラーになります。
- https://github.com/tlswg/tls13-spec/blob/master/draft-ietf-tls-tls13.md


# 詳細


### git blameで過去に変更されたコミットを確認する

```
$ git blame draft-ietf-tls-tls13.md
```

### git blameで表示した際よりもさらに前の変更があるコミットまで遡りたい

git blameのコマンドで次のようのさらに前の変更履歴よりも前のコミットがある場合
```
1326ca8b draft-ietf-tls-tls13.md       (Martin Thomson      2016-08-23 11:32:27 +1000 1875) - Removing the "early_data" extens
1326ca8b draft-ietf-tls-tls13.md       (Martin Thomson      2016-08-23 11:32:27 +1000 1876)   present. Early data is not permi
```

上記ハッシュ値で指定された値よりも1つ前としてキャロット(^)を追加します。
```
$ git blame 1326ca8b^ -- draft-ietf-tls-tls13.md 
```

上記の「--」の意味については、そのあとの文字はオプションではなくただの引数では見ろという意味のようです。
```
$ git checkout master         // masterブランチをチェックアウトする
$ git checkout -- master      // masterというファイル名をチェックアウトする
```

- 参考
  - https://qiita.com/DQNEO/items/f634dde498b19924dbd2
