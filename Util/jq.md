# 概要
最近のWebAPIはJSON形式で返すものが多い  
仕事でもJSONから特定の要素を取り出したいといった場合などに役立つことをまとめておく

# インストール
インストール不要で、以下の画面にw3mなどでアクセスして該当のPlatformのjqをdownloadするだけで利用可能となる。
- https://stedolan.github.io/jq/

ローカルディレクトリへ配置
```
$ sudo curl -o /usr/local/bin/jq -L https://github.com/stedolan/jq/releases/download/jq-1.5/jq-linux64 && sudo chmod +x /usr/local/bin/jq
```

グローバルへ配置
```
$ sudo curl -o /usr/bin/jq -L https://github.com/stedolan/jq/releases/download/jq-1.5/jq-linux64 && sudo chmod +x /usr/bin/jq
```


# 使ってみる
ドットでルートノードを表すようです。
```
$ echo '[{},{}]' | ~/jq .
[
  {},
  {}
]
```

中かっこの中を取り出したい場合には次のようにする。
```
$ echo '[1,2,3]' | ~/jq '.[]'
1
2
3
$ echo '[1,2,3]' | ~/jq '.[0,2]'    // カンマで複数指定が可能
1
3
```

単純に綺麗に整形たいだけであればjqに引数無しでパイプで渡せばOK
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


### オブジェクトの中身を取り出す
```
$ echo '{ "a":1 , "b":2 }'  | ~/jq '.b'
2
$ echo '{ "a": { "c": 1 }, "b":2 }'  | ~/jq '.a.c'
1
```

### 特定の要素だけ取り出す
パイプを使うことができます
```
$ echo '[ { "a":1 },  { "x": 1 } ]'  | ~/jq '.[] | select(.x)'
{
  "x": 1
}
```

### 要素の値を比較してtrue, falseを判定する
```
$ echo '[ { "a":1 },  { "x": 1 } ]'  | ~/jq '(.[].a==1)'
true
false
```


# 参考URL
- 公式ドキュメント
 - http://stedolan.github.io/jq/manual/
- http://qiita.com/takeshinoda@github/items/2dec7a72930ec1f658af
- jq で 条件にマッチするオブジェクトを取り出す where 句的なこと
 - http://takuya-1st.hatenablog.jp/entry/2016/12/26/180057
