# 概要
Java周りのデバッグ処理でよく利用するものについて記載する

# Java共通

### ネットワーク周りのデバッグ
プログラムに埋め込む場合
```
System.setProperty("javax.net.debug", "all");
```

all以外にもssl, packetなどを指定することができる。
下記の公式資料を確認のこと
- cf.  https://docs.oracle.com/en/java/javase/11/security/java-secure-socket-extension-jsse-reference-guide.html#GUID-31B7E142-B874-46E9-8DD0-4E18EC0EB2CF


出力されるデバッグの例については以下の資料が参考になりそう
- https://colinpaice.blog/2020/04/05/using-java-djavax-net-debug-to-examine-data-flows-including-tls/

### profileを指定する
カンマ区切りで複数のprofileを指定することもできます。
```
spring.profiles.active: local,hoge
```

application-[env].propertiesが読み込まれるようになります。

もしくは以下の環境変数を指定する事でもprofileをしていることができます。
```
SPRING_PROFILES_ACTIVE
```

なお、profileの指定方法はさまざまな方法があります。
- SPRING_PROFILES_ACTIVE: OS環境変数
- "-Dspring.profiles.active": Javaシステムプロパティ
- "--spring.profiles.active":  コマンドライン引数
- "--spring.profiles.active":  コマンドライン引数
- @ActiveProfiles アノテーション: （テスト限定）

詳細は下記の公式リファレンスを参照のこと
- cf. https://docs.spring.io/spring-boot/docs/current/reference/html/features.html#features.external-config

### リモートデバッグ

あらかじめJavaプログラム側はjavaプログラム起動時に下記設定を入れる必要があります。
```
-Xdebug -Xrunjdwp:transport=dt_socket,server=y,suspend=n,address=8000
```

上記オプションについて簡単に説明します。
- runjdwp
  - JVM中にJava Debug Wire Protocol (JDWP)を有効にします。これによってリモートデバッグが有効になります
- transport
  - デバッグコネクションにネットワークソケットを使うことを指定しています。
  - dt_socket や dt_shmemが指定できます
- server
  - 「y」の場合はデバッガアプリケーションの接続を待機、「n」の場合はaddress で指定されたデバッガアプリケーションに接続する
- suspend
  - JVM を一時停止してリモートデバッガー接続を待つ場合は、アプリケーションを起動する前にsuspendを"y"に変更します。
- address
  - デバッグコネクションでlistenするポート番号です

上記では8000番ポートで接続させるようにします。 ローカルホストから別リクエストさせる場合にはSSHトンネリングなどをさせる必要があります。
もし、SSHトンネリングが必要であれば

リモートにデプロイされているものと同じソースコードを取得します。実際にデプロイされるソースコードと異なる場合には、ブレークポイントの位置がずれる可能性があります。


IntelliJの場合、Run -> Edit Configurations -> 画面左上の"+"を指定してホストに接続先サーバ、ポートに上記のaddressで指定した8000を指定します。


### PKI周りの設定
起動時に下記のようなPKI関連の設定が指定できます。
```
"-Djavax.net.ssl.keyStore=../config/kstore" "-Djavax.net.ssl.keyStorePassword=mypwd"
"-Djavax.net.ssl.trustStore=../config/tstore" "-Djavax.net.ssl.trustStorePassword=mypwd"
"-Djavax.net.debug=ssl:handshake:trustmanager"
```

サーバ側の設定
- javax.net.ssl.keyStore
- javax.net.ssl.keyStorePassword

クライアント側の設定
- javax.net.ssl.trustStore
- javax.net.ssl.trustStorePassword


### 意図的にデバッガーから指定した例外を発生させる
以下で可能らしい
- https://tech.excite.co.jp/entry/2022/07/07/163117


# Spring Boot
Spring Bootでサポートされている全てのロギングシステムは、logging.level.\*=LEVEL使うことでSpring環境内(例えばapplication.properties等)にログレベルを持つことが出来る。
LEVELはTRACE、DEBUG、INFO、WARN、ERROR、FATAL、OFFから1つを選択、ルートロガーはlogging.level.rootを使用して設定することができる。

- cf. https://docs.spring.io/spring-boot/docs/1.2.1.RELEASE/reference/htmlsingle/#boot-features-custom-log-levels

### リモートデバッグ

Java共通と同じです。
- cf. https://www.baeldung.com/spring-debugging

リモートデバッグプロセスをgradle bootRunで起動するには以下の設定を埋め込みます。
```
bootRun {
    jvmArgs "-agentlib:jdwp=transport=dt_socket,server=y,suspend=n,address=8000"
}
```

### 実装アプリケーション自体のログレベル
以下を参考にすると良い
- https://www.baeldung.com/spring-boot-testing-log-level

### Spring Boot
Spring Framework全体でデバッグを出力したい場合には以下の設定を入れます。
```
logging.level.org.springframework=DEBUG
```

公式資料には以下の設定が記載されている
```
logging.level.org.springframework.web=DEBUG
logging.level.org.hibernate=ERROR
```
cf. https://docs.spring.io/spring-boot/docs/1.5.22.RELEASE/reference/html/boot-features-logging.html#boot-features-custom-log-levels

### Spring MVC
```
# Spring MVCへのリクエスト/レスポンスログの詳細情報出力を有効化
spring.mvc.log-request-details=true
```

- cf. https://qiita.com/kazuki43zoo/items/5bde40ad42a30b8e6683


### Spring Security
以下の設定が利用できる。TRACEレベルも存在する模様
```
logging.level.org.springframework.security=DEBUG
```

- cf. https://www.baeldung.com/spring-security-enable-logging

### Spring Rest Template
以下でリクエストが少し詳細に表示されるが、レスポンスが表示されない(思った以上に加工されていて生のリクエストの情報が出力されていない)
```
logging.level.org.springframework.web.client.RestTemplate=DEBUG
```

このためにはApache HttpClientを利用するように伝えなければ
```
RestTemplate restTemplate = new RestTemplate();
restTemplate.setRequestFactory(new HttpComponentsClientHttpRequestFactory());
```

以下の設定を追加する事でデバッグログが出力されるようになるはず
```
logging.level.org.apache.http=DEBUG
logging.level.httpclient.wire=DEBUG
```

- cf. https://www.baeldung.com/spring-resttemplate-logging


### Spring Retry
リトライしている様子をデバッグで確認する事ができます。
```
logging.level.org.springframework.retry=DEBUG
logging.level.org.apache.http.wire=DEBUG
```

# Mybatis

公式資料は以下に存在する
- https://mybatis.org/mybatis-3/logging.html

公式ではないが下記も参考になる
- https://oboe2uran.hatenablog.com/entry/2015/05/14/124949

# logback
xml設定の属性として「debug="false"」と指定します。
```
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE logback>
<configuration debug="false">
 ...
</configuration>
```

# Apache HttpClient
- org.apache.http.impl.client
- org.apache.http.wire
- org.apache.http.headers


