# 概要
Dockerfileに指定できる値についてまとめています。

Dockerfile への記法についてはリファレンスも参考のこと
- https://docs.docker.jp/engine/reference/builder.html

# 詳細

### コマンド
Dockerfileでは以下のコマンドを利用することができます。
```
FROM ... ベースとなるイメージ
RUN ... docker build 時に実行するコマンド
CMD ... docker run 時に実行するコマンド
ENTRYPOINT ... docker run 時に実行するコマンド
MAINTAINER ... 作者情報
LABEL ... ラベル情報(メタデータ)
EXPOSE ... 公開ポート番号
ENV ... 環境変数
ARG ... 一時変数
COPY ... ホストからコンテナへのファイルコピー
ADD ... ホストからコンテナへのファイルコピー
VOLUME ... ボリューム
USER ... 実行ユーザ
SHELL ... シェル指定
WORKDIR ... ワークディレクトリ
ONBUILD ... ビルド時に実行するコマンド
STOPSIGNAL ... コンテナ終了時に送信されるシグナル
HEALTHCHECK ... ヘルスチェック
```
- 参考: http://www.tohoho-web.com/docker/dockerfile.html
