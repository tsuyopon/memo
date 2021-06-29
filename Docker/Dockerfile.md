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
WORKDIR ... ワークディレクトリ(コンテナログイン時のディレクトリを指定する)
ONBUILD ... ビルド時に実行するコマンド
STOPSIGNAL ... コンテナ終了時に送信されるシグナル
HEALTHCHECK ... ヘルスチェック
```
- 参考: http://www.tohoho-web.com/docker/dockerfile.html



### FROM
このイメージをベースにしてこれから記述するコマンドを実施するという意味です。
```
FROM centos:centos7
```

### RUN
FROMで指定したイメージにパッケージをインストールする場合にはRUNを用います。
```
RUN yum -y install httpd
```

### COPY
Dockerイメージ内にコピーしたいファイルを指定します。
以下の例では、hoge.txtをDockerイメージ上の/tmpにコピーします。
```
FROM centos:centos7
 
COPY hoge.txt /tmp
```

### ADD

ADDはCOPYと似ていますが、以下の2点で異なります。
- URL指定が可能である
- tarアーカイブでgzip、bzip2、xzで圧縮されていた場合、自動で展開される


hoge.tar.gzは展開して/tmpに配置されます。
```
FROM centos:centos7
  
ADD hoge.tar.gz /tmp
```

また、次のようにURL上のファイルを指定することもできるます。
```
FROM centos:centos7
 
ADD http://ftp.meisei-u.ac.jp/mirror/apache/dist/tomcat/tomcat-8/v8.5.54/bin/apache-tomcat-8.5.54.tar.gz /tmp
```

### CMD
docker runコマンドで実行する際のコマンドを指定します。コマンド内のスペースはカンマで区切ります。
```
FROM centos:centos7
 
CMD ["free","-t"]
```

### ENTRYPOINT

docker runコマンドで実行する際のコマンドを指定します。
CMDとの違いとしては、ENTRYPOINTでは、docker run時にENTRYPOINTで指定したコマンドの引数が追加できます。では、dockerrun時に-hオプションを追加してみます。

```
FROM centos:centos7
 
CMD ["-h"]
ENTRYPOINT ["free","-t"]
```

### ENV
docker buildでイメージを作成する際に指定する環境変数を定義することができます
```
FROM centos:centos7
 
ENV hoge=fuga
 
RUN echo $hoge
```

実行結果は以下の通り
```
$ docker build -t envtest .
Sending build context to Docker daemon  2.048kB
Step 1/3 : FROM centos:centos7
 ---> 5e35e350aded
Step 2/3 : ENV hoge=fuga
 ---> Using cache
 ---> d910a6b78848
Step 3/3 : RUN echo $hoge
 ---> Running in 5624ad7d6184
fuga
Removing intermediate container 5624ad7d6184
 ---> 1fb0ac8cba93
Successfully built 1fb0ac8cba93
Successfully tagged envtest:latest
```

### EXPOSE
Dockerコンテナ内で公開するポートを指定します。
例えば、Apacheのコンテナを作成して80番ポートを公開するときは以下のようにDockerfileを作成します。
```
FROM centos:centos7
 
RUN yum install -y httpd
 
EXPOSE 80
CMD ["apachectl", "-D", "FOREGROUND"]
```

### USER
実行ユーザーを指定することができます。
```
FROM centos:centos7
 
RUN adduser nobody
 
USER nobody
 
RUN echo "hoge" > /tmp/hoge.txt
```

