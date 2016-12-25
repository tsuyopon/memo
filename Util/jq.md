# 概要
最近のWebAPIはJSON形式で返すものが多い  
仕事でもJSONから特定の要素を取り出したいといった場合などに役立つことをまとめておく

# インストール
インストール不要で、以下の画面にw3mなどでアクセスして該当のPlatformのjqをdownloadするだけで利用可能となる。
- https://stedolan.github.io/jq/

# 使ってみる

```
$ echo '{"items":[{"item_id":1,"name":"hoge","age":15},{"item_id":2,"name":"fuga","age":20}]}' | ~/jq
{
  "items": [
    {
      "item_id": 1,
      "name": "hoge",
      "age": 15
    },
    {
      "item_id": 2,
      "name": "fuga",
      "age": 20
    }
  ]
}
```

2番目配列の要素を取り出してみる
```
$ echo '{"items":[{"item_id":1,"name":"hoge","age":15},{"item_id":2,"name":"fuga","age":20}]}' | ~/jq '.[][1]'
{
  "item_id": 2,
  "name": "fuga",
  "age": 20
}
```

2番目の配列のnameキーの値を取得する。
```
$ echo '{"items":[{"item_id":1,"name":"hoge","age":15},{"item_id":2,"name":"fuga","age":20}]}' | ~/jq '.[][1]["name"]'
"fuga"
```

nameキーの値を全て取得する。
```
$ echo '{"items":[{"item_id":1,"name":"hoge","age":15},{"item_id":2,"name":"fuga","age":20}]}' | ~/jq '.[][]["name"]'
"hoge"
"fuga"
```

# 参考URL
- 公式ドキュメント
 - http://stedolan.github.io/jq/manual/
- http://qiita.com/takeshinoda@github/items/2dec7a72930ec1f658af
