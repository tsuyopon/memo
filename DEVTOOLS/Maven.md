# Mavenとは
プロジェクトの一元管理、統一したビルドプロセスの提供、依存ライブラリの管理機能などを持つビルドツールです。  

以下の資料がドキュメント分量が適切で非常にわかりやすいです。
- http://www.techscore.com/tech/Java/ApacheJakarta/Maven/index/

Mavenを包括的に理解するためのアーキテクチャ概念図としては以下の資料に目を通しておくと良いと思います。
- http://www.techscore.com/tech/Java/ApacheJakarta/Maven/2/#maven-2-1

# 詳細

### mvn基本コマンド
```
プロジェクト作成
 	mvn <archtype>:create
	mvn <archtype:create> -DgroupId=com.example -DartifactId=sample
コンパイル
	mvn compile
テスト
	mvn test
ドキュメンテーション(javadoc生成)
	mvn javadoc:javadoc
ドキュメンテーション(site生成)
	mvn site
パッケージング
	mvm package
インストール
	mvn install
公開
	mvn deploy
```

### targetディレクトリを削除する
mvn packageなどでtarget配下に作成されたパッケージを削除するためには以下を実行します。
```
$ mvm clean
```

### MavenプロジェクトをEclipseプロジェクトに変換する
以下のコマンドでEclipseに必要な.classpathや.projectファイルを作成してくれるようになる。
```
$ mvn eclipse:eclipse
```

### Pom.xmlについて
プロジェクトに関する情報を持つ重要なファイルです。
プロジェクトのビルドに関する情報、依存するライブラリ情報、プラグイン設定などが含まれます。

- 参考
  - http://www.techscore.com/tech/Java/ApacheJakarta/Maven/2-2/#maven-2-4

### EclipseからMavenプロジェクトをインポートする。
m2eclipseプラグインが必要です。インストールするとインポートからMVNという項目が表示されるようになります。

