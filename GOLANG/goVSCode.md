# 概要
go言語でVSCodeを使う際のちょっとしたメモ

# 詳細
### goplsを入れる
定義元などにジャンプする際にはgoplsが必要なので、下記からインストールできます。
```
Go: Install/Update Tools
```

### 定義元に遷移しようとすると「no definition found」と表示される。
以下でgoplsが再起動できるようです。
```
Go: Restart Lauguage Server
```

自分の場合だとそれでもうまく動かなかったのでワークスペースを作り直したらうまくいきました
