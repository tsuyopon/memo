# 概要

Gradleはビルドツールです。

Gradle Wrapperスクリプト(gradlew)をgradle initコマンドにより作成しておくと、Gradleの実行環境をインストールしていない環境でもgradleコマンドを実行するのと同様にビルドすることができます。
Gradleで生成したプロジェクトには、Gradle Wapperと呼ばれるgradlewとgradlew.batという2つの実行ファイルができる。
- gradlew（Linux 用のシェルスクリプト）
- gradlew.bat（Windows 用のバッチファイル）

# gradle使い方

### gradleのインストール (MacOS 10.15.7)
sdkmanというパッケージマネージャーを使ってGradleをインストールします。
```
$ curl -s https://get.sdkman.io | bash
$ source ~/.sdkman/bin/sdkman-init.sh 
[~/git/memo/JAVA]$ sdk install gradle
==== BROADCAST =================================================================
* 2021-11-05: gradle 7.3-rc-5 available on SDKMAN! https://docs.gradle.org/7.3-rc-5/release-notes.html
* 2021-11-04: vertx 4.2.1 available on SDKMAN!
* 2021-11-03: jbang 0.83.0 available on SDKMAN! https://github.com/jbangdev/jbang/releases/tag/v0.83.0
================================================================================

Downloading: gradle 7.2

In progress...

################################################################################################################################################################################################ 100.0%

Installing: gradle 7.2
Done installing!


Setting gradle 7.2 as default.
```

以上によりgradle7.2がインストールされました。


### gradleで初期プロジェクトを作成してみる

JAVA_HOMEを設定しないとgradle initを実行した際にエラーになります。
JAVA_HOMEに設定するためのパスを以下のコマンドで確認します。
```
$ /usr/libexec/java_home -V
Matching Java Virtual Machines (1):
    16.0.2, x86_64:	"Java SE 16.0.2"	/Library/Java/JavaVirtualMachines/jdk-16.0.2.jdk/Contents/Home

/Library/Java/JavaVirtualMachines/jdk-16.0.2.jdk/Contents/Home
```

実行します。gradle initを実行する際にはJAVAアプリケーションを明示するためにjava-applicationを指定します。
以下の例ではscript DSLにGroovyを、テストフレームワークにJUnit Jupiterを指定しています。
```
$ export JAVA_HOME="/Library/Java/JavaVirtualMachines/jdk-16.0.2.jdk/Contents/Home"
$ gradle init --type java-application

Welcome to Gradle 7.2!

Here are the highlights of this release:
 - Toolchain support for Scala
 - More cache hits when Java source files have platform-specific line endings
 - More resilient remote HTTP build cache behavior

For more details see https://docs.gradle.org/7.2/release-notes.html

Starting a Gradle Daemon (subsequent builds will be faster)

Select build script DSL:
  1: Groovy
  2: Kotlin
Enter selection (default: Groovy) [1..2] 1

Select test framework:
  1: JUnit 4
  2: TestNG
  3: Spock
  4: JUnit Jupiter
Enter selection (default: JUnit Jupiter) [1..4] 4

Project name (default: GraddleApp): 

Source package (default: GraddleApp): 


> Task :init
Get more help with your project: https://docs.gradle.org/7.2/samples/sample_building_java_applications.html

BUILD SUCCESSFUL in 42s
2 actionable tasks: 2 executed
```

gradle initにより作成されたディレクトリ構成を確認します。
```
$ tree
.
├── app
│   ├── build.gradle
│   └── src
│       ├── main
│       │   ├── java
│       │   │   └── GraddleApp
│       │   │       └── App.java
│       │   └── resources
│       └── test
│           ├── java
│           │   └── GraddleApp
│           │       └── AppTest.java
│           └── resources
├── gradle
│   └── wrapper
│       ├── gradle-wrapper.jar
│       └── gradle-wrapper.properties
├── gradlew
├── gradlew.bat
└── settings.gradle

12 directories, 8 files
```


### インストールされたgradleバージョンを確認する
```
$ gradle -v

------------------------------------------------------------
Gradle 7.2
------------------------------------------------------------

Build time:   2021-08-17 09:59:03 UTC
Revision:     a773786b58bb28710e3dc96c4d1a7063628952ad

Kotlin:       1.5.21
Groovy:       3.0.8
Ant:          Apache Ant(TM) version 1.10.9 compiled on September 27 2020
JVM:          16.0.2 (Oracle Corporation 16.0.2+7-67)
OS:           Mac OS X 10.15.7 x86_64
```

### プロパティ(設定)を確認する
propertiesで設定の一覧を表示することができます。
```
$ gradle properties

> Task :properties

------------------------------------------------------------
Root project 'GraddleApp'
------------------------------------------------------------

allprojects: [root project 'GraddleApp', project ':app']
ant: org.gradle.api.internal.project.DefaultAntBuilder@2dfb41ad
antBuilderFactory: org.gradle.api.internal.project.DefaultAntBuilderFactory@53792a12
artifacts: org.gradle.api.internal.artifacts.dsl.DefaultArtifactHandler_Decorated@50cce312
asDynamicObject: DynamicObject for root project 'GraddleApp'
baseClassLoaderScope: org.gradle.api.internal.initialization.DefaultClassLoaderScope@6a18b862
buildDir: /Users/tsuyoshi/GraddleApp/build
buildFile: /Users/tsuyoshi/GraddleApp/build.gradle

(snip)
```

### 現在のプロジェクト構成を調べる
```
$ gradle -q projects

------------------------------------------------------------
Root project 'GraddleApp'
------------------------------------------------------------

Root project 'GraddleApp'
\--- Project ':app'

To see a list of the tasks of a project, run gradle <project-path>:tasks
For example, try running gradle :app:tasks
```

# Gradle Wrapper(gradlew)の使い方

### gradlewからのgradleのインストール

gradle initで生成されたgradlewのスクリプトを実行することで、２人目以降は簡単にgradleを導入することができます。
```
$ ./gradlew -v
Downloading https://services.gradle.org/distributions/gradle-7.2-bin.zip
..........10%...........20%...........30%...........40%...........50%...........60%...........70%...........80%...........90%...........100%

------------------------------------------------------------
Gradle 7.2
------------------------------------------------------------

Build time:   2021-08-17 09:59:03 UTC
Revision:     a773786b58bb28710e3dc96c4d1a7063628952ad

Kotlin:       1.5.21
Groovy:       3.0.8
Ant:          Apache Ant(TM) version 1.10.9 compiled on September 27 2020
JVM:          16.0.2 (Oracle Corporation 16.0.2+7-67)
OS:           Mac OS X 10.15.7 x86_64
```

### gradlew build
build.gradleがある階層でこのコマンドを実行するとbuildが実行され、build/libs/の下にjarファイルが生成される。
以下のコマンドでビルドすることができるようになります。
```
$ gradlew build
```

生成されたjarファイルを実行することで、localhost:8080でページにアクセスできるようになります。
```
$ java -jar build/libs/helloworld-0.0.1-SNAPSHOT.jar 
```

### 依存関係を表示する
非常に大量の出力が表示されるので以下は割愛する
```
$ ./gradlew dependencies

> Task :dependencies

------------------------------------------------------------
Root project 'demo'
------------------------------------------------------------

annotationProcessor - Annotation processors and their dependencies for source set 'main'.
No dependencies

apiElements - API elements for main. (n)
No dependencies

archives - Configuration for archive artifacts. (n)
No dependencies

bootArchives - Configuration for Spring Boot archive artifacts. (n)
No dependencies

compileClasspath - Compile classpath for source set 'main'.
+--- org.springframework.boot:spring-boot-starter -> 2.6.4
|    +--- org.springframework.boot:spring-boot:2.6.4
|    |    +--- org.springframework:spring-core:5.3.16
|    |    |    \--- org.springframework:spring-jcl:5.3.16
|    |    \--- org.springframework:spring-context:5.3.16
...
     \--- org.xmlunit:xmlunit-core:2.8.4

testCompileOnly - Compile only dependencies for source set 'test'. (n)
No dependencies

testImplementation - Implementation only dependencies for source set 'test'. (n)
\--- org.springframework.boot:spring-boot-starter-test (n)

testResultsElementsForTest - Directory containing binary results of running tests for the test Test Suite's test target. (n)
No dependencies
```

いくつかのカテゴリに分かれていますので下記を抑えておく必要があります。
- api: 外部(このライブラリの利用者)に公開する依存関係
- implementation: 外部(このライブラリの利用者)に公開せず、ライブラリ内の実装でのみ使う依存関係
- compileOnly: Java プラグインの "compileOnly" 構成は、メイン ソース セットコードをコンパイルするために必要な依存関係を定義しますが、それはランタイム クラスパスの一部であってはなりません。
- runtimeOnly: Javaプラグインの"runtimeOnly" 構成は、メイン ソース セットコードを実行するために必要な依存関係を定義しますが、コンパイルには必要ありません。

- testImplementation: Javaプラグインの"testImplementation" 構成は、テスト ソース セットコードをコンパイルして実行するために必要な依存関係を定義します。
- testCompileOnly: Javaプラグインの"testCompileOnly" 構成は、テスト ソース セットのコードをコンパイルするために必要な依存関係を定義しますが、それはランタイム クラスパスの一部であってはなりません。
- testRuntimeOnly: Javaプラグインの"testRuntimeOnly" 構成は、テスト ソース セットコードを実行するために必要な依存関係を定義しますが、コンパイルには必要ありません。runtimeOnlyを拡張します。runtimeOnlyで利用可能なものはすべて、「testRuntimeOnly」でも利用できます。この構成は、テストJava プラグイン タスクで使用されます。

以下は非推奨になっています
- compile: implementationに置き換えられるようになった
- runtime: runtimeOnlyに置き換えられるようになった 
- testCompile: testImplementationに置き換えられるようになった
- testRuntime: testImplementationに置き換えられるようになった


### gradlewで実行可能なタスク一覧を表示する
```
$ ./gradlew tasks

> Task :tasks

------------------------------------------------------------
Tasks runnable from root project 'GraddleApp'
------------------------------------------------------------

Application tasks
-----------------
run - Runs this project as a JVM application

Build tasks
-----------
assemble - Assembles the outputs of this project.
build - Assembles and tests this project.
buildDependents - Assembles and tests this project and all projects that depend on it.
buildNeeded - Assembles and tests this project and all projects it depends on.
classes - Assembles main classes.
clean - Deletes the build directory.
jar - Assembles a jar archive containing the main classes.
testClasses - Assembles test classes.

Build Setup tasks
-----------------
init - Initializes a new Gradle build.
wrapper - Generates Gradle wrapper files.

Distribution tasks
------------------
assembleDist - Assembles the main distributions
distTar - Bundles the project as a distribution.
distZip - Bundles the project as a distribution.
installDist - Installs the project as a distribution as-is.

Documentation tasks
-------------------
javadoc - Generates Javadoc API documentation for the main source code.

Help tasks
----------
buildEnvironment - Displays all buildscript dependencies declared in root project 'GraddleApp'.
dependencies - Displays all dependencies declared in root project 'GraddleApp'.
dependencyInsight - Displays the insight into a specific dependency in root project 'GraddleApp'.
help - Displays a help message.
javaToolchains - Displays the detected java toolchains.
outgoingVariants - Displays the outgoing variants of root project 'GraddleApp'.
projects - Displays the sub-projects of root project 'GraddleApp'.
properties - Displays the properties of root project 'GraddleApp'.
tasks - Displays the tasks runnable from root project 'GraddleApp' (some of the displayed tasks may belong to subprojects).

Verification tasks
------------------
check - Runs all checks.
test - Runs the unit tests.

To see all tasks and more detail, run gradlew tasks --all

To see more detail about a task, run gradlew help --task <task>

BUILD SUCCESSFUL in 677ms
1 actionable task: 1 executed
```
