# 概要
docker hubへのイメージ登録方法について

# 詳細
### docker hubにpushする
- https://qiita.com/umi/items/d4b5a68263ad0444693b#docker-hub-%E3%81%ABpush-%E3%81%97%E3%81%A6%E3%81%BF%E3%82%8B


試したわけではないが流れだけ記載しておく
- 1. 以下のdocker hubからアカウントを作成します。
  - https://hub.docker.com/explore/
- 2. ログインする
```
$ sudo docker login
```
- 3. タグ付けをする
```
$ sudo docker tag 18247f8cdbc4 ubuntu/mysql:latest
$ sudo docker images
```
- 4.リモートレポジトリにプッシュする
```
$ sudo docker push ubuntu/mysql:latest
```
- 5. docker hubを確認してレポジトリが作成されたことを確認する。
