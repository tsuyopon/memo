# 概要
DoxygenはC++、C、Java、Objective-C、Python、IDL (Corba、Microsoft 風)、Fortran、VHDL、PHP、C#に用途のあったドキュメンテーションシステムです。
以下の特徴があります。
- 仕様書を作成する無駄を省くことができます
- HTML形式、LATEX形式を生成することができます
- Graphvizと連携してグラフを描画することができます


# 概要
## doxygen実行の流れ
doxygenを使うためには次の項目だけを押さえておけば良いです。
- 1. Doxyfileを準備する(doxygen -gコマンドで雛形を生成)
- 2. doxygenコマンドを実行する

## Doxyfileを生成する
以下のコマンドを実行するとdoxygen設定の雛形となるDoxyfileを生成してくれます。
```
$ doxygen -g
```

続いて最低限の修正を行います。　
```
< が自分で変更した部分。 
> がデフォルトの値である。

------------------------------------
< PROJECT_NAME           =  test
> PROJECT_NAME           =
------------------------------------
< PROJECT_NUMBER         = 1.0.0
> PROJECT_NUMBER         =
------------------------------------
< OUTPUT_DIRECTORY       = /home/tsuyoshi/public_html/doc
> OUTPUT_DIRECTORY       =
------------------------------------
< INPUT                  = /home/tsuyoshi/testpro
> INPUT                  =
------------------------------------
< HAVE_DOT               = NO
> HAVE_DOT               = YES
------------------------------------
```

## 出力ドキュメント形式
次の出力ドキュメント形式が選べるようです。
- HTML
  - GENERATE_HTMLが有効であれば生成される
- LATEX
  - GENERATE_LATEXが有効であれば生成される
- ManPages
  - GENERATE_MANが有効であれば生成される
- RTF
  - GENERATE_RTFが有効であれば生成される
- XML
  - GENERATE_XMLが有効であれば生成される
- Qt Help Project(.qhp)
  - GENERATE_QHPが有効であれば生成される
- Qt Compressed Help(.qch)
  - GENERATE_QHPが有効であれば生成される
- Compiled HTML Help
  - GENERATE_HTMLHELPが有効であれば生成される
- PostScript
  - Latex出力のディレクトリ内からmake psすることで生成されます
- PDF
  - Latex出力のディレクトリ内からmake pdfすることで生成されます

以下は公式ドキュメントです。
- 出力フォーマット
  - http://www.doxygen.jp/output.html
- 設定
  - http://www.doxygen.jp/config.html


# 設定

## 基本設定


### プロジェクトの指定
プロジェクト名
```
PROJECT_NAME = 	jubatus_core
```

プロジェクトバージョン
```
PROJECT_NUMBER = 0.1.0
```

### ドキュメント出力先の指定
出力先を指定する。以下ではhtmlディレクトリを指定している。
```
HTML_OUTPUT = html
```

### ソースコードの指定
ソースコードの場所を指定する
```
INPUT = ../iocore ../lib
```

ソースコードパターンを指定する。
```
FILE_PATTERNS = *.h *.hpp *.cpp
```

排除するディレクトリを指定する
```
EXCLUDE = ../iocore/hoge
```

以下で排除するファイル名のパターンも指定することができる。
```
EXCLUDE_PATTERNS = *_test.cpp
```

ディレクトリを再帰的にチェックするかを指定する
```
RECURSIVE = YES
```

### doxygen中にソースコードも表示する
```
SOURCE_BROWSER = YES
```

### グラフを表示する
graphvizパッケージが入っていればグラフを生成することができる。
```
HAVE_DOT = YES
```

クラス間の依存関係を表すグラフを生成することができる。
```
CLASS_GRAPH = YES
```

クラス図を生成することもできる。
```
CLASS_DIAGRAMS = YES
```

クラス図に関して実装依存関係(継承、所有、クラス参照変数)を生成する場合にチェックする
```
COLLABORATION_GRAPH = YES
```

コールグラフを生成する
```
CALL_GRAPH = YES
```

呼び出し元グラフを生成する
```
CALLER_GRAPH = YES
```

インクルード依存関係図および、インクルード元依存関係図を生成する。
```
INCLUDE_GRAPH = YES
INCLUDED_BY_GRAPH = YES
```

グラフ化された全クラス階層図を生成する場合にチェックする。
```
GRAPHICAL_HIERARCHY = YES
```

ディレクトリがどのディレクトリに依存しているのかを示す図を生成します。依存関係はディレクトリ中のファイル間の#include関係で決まります。
```
DIRECTORY_GRAPH = YES
```

グラフについては以下を参考にするとどの設定がどのようにビジュアル化できるのかを確認できる。
- https://www13.atwiki.jp/uhaku/pages/49.html

### グラフに関する設定
グラフの最大深度を設定することができる。
```
MAX_DOT_GRAPH_DEPTH = 3
```

dhtmlでグラフを展開する機能により見やすくすることもできる。
```
HTML_DYNAMIC_SECTIONS = YES
```

- 参考
  - http://idlysphere.blog66.fc2.com/blog-entry-176.html

### dotコマンドのパフォーマンスを高める
```
DOT_MULTI_TARGETS = YES
```

スレッド数は3に設定する
```
DOT_NUM_THREADS = 3
```


### ドキュメントに表記する関数の指定
全ての関数をドキュメント化する
```
EXTRACT_ALL = YES
```

```
EXTRACT_PRIVATE = YES
EXTRACT_STATIC = YES
EXTRACT_LOCAL_CLASS = YES
```

## 応用設定
TBD



# doxygen記法

### 主なコマンド
コマンドは以下に記すコメント内に記述します。
```
 ・「/*!」と「*/」 で囲まれたコメント文 
 ・「/**」と「*/」 で囲まれたコメント文 
 ・「///」ではじまるコメント行
 ・「//!」ではじまるコメント行
```

以下はJAVA Docスタイルの例です
```
 /**
 * @param s a constant character pointer.
 * @see testVar()
 * @return The test results
 */
```

ドキュメントは@か\で始まる必要があります。
通常は\で始まり、JAVA Docスタイルではアットマーク(@)になります。
```
	 @file             ファイル名
	 @author           著者
	 @date             日付
	 @brief            要約
	 @bug              バグについての記述
	 @param            関数の引数についての記述
	 @return           戻り値についての記述(@retvalと同じ)
	 @retval           戻り値についての記述(@returnと同じ)
	 @mainpage         メインページを作成する
	 @section          セクション名
	 @subsection       サブセクション名
	 @subsubsection    サブサブセクション名
	 @paragraph        パラグラフ名
	 @em               イタリック体
	 @n                改行
	 @image            画像
	 @def              #define マクロに対するドキュメントであることを表します
	 @example          ソース例を示す
	 @note             Noteを記述します
	 @sa               see also
	 @attention        注意書きを記述します
	 @deprecated       推奨されないことを示します
	 @exception/@throw 例外を表します
	 @version          バージョンを表します 
```

以下の形式でコマンドを記述したい場合には
```
	 /** Brief description which ends at this dot. Details follow
	  *  here.
	 */
```

これはJAVA Docスタイルと呼ばれています。この場合にはJAVADOC_AUTOBRIEF が設定ファイルで YES に設定されている必要があります。

### 構造化ファイルに関するコマンドについて
構造化ファイルに関するコマンドとはどのようなものかというとclassファイルと認識させたり、defineの定義ファイルと認識させるための識別子です。

以下に示します。
```
\struct     C の構造体にドキュメントを付けます。 
\union      共用体にドキュメントを付けます。 
\enum       列挙型にドキュメントを付けます。 
\fn         関数にドキュメントを付けます。 
\var        変数または typedef または列挙定数にドキュメントを付けます。 
\def        #define にドキュメントを付けます。 
\typedef    型定義にドキュメントを付けます。 
\file       ファイルにドキュメントを付けます。 
\namespace  ネームスペースにドキュメントを付けます。 
\package    Java のパッケージにドキュメントを付けます。 
\interface  IDL のインタフェースにドキュメントを付けます。 
```

これらが無い場合にはdoxygenはファイル説明文書を表示しません。

### @briefをhtml画面に出力したくない
この場合には設定ファイルで、BRIEF_MEMBER_DESC を NO に設定すると表示されなくなります

### JAVA Docスタイルでドキュメントブロックの最初の行は、自動的に要約説明として扱わせたい
この場合には設定ファイルで、 JAVADOC_AUTOBRIEF を YES に設定する必要があります。

以下の様な文章は自動的にファイルの要約として扱われます。
```
/**
*  A test class. A more elaborate class description.
*/
```

### ファイル、構造体、共用体、クラス、あるいは列挙型のメンバーをドキュメント付けしたい

以下の様にして、コメントブロックの中に"<"マーカーを追加します。
```
int var; /*!< Detailed description after the member */
```

これで、上記変数にはドキュメント付けされます。

# 参考URL
- doxygen公式ホームページ
  - http://www.doxygen.nl/index.html
- doxygen公式ホームページ(JP)
  - http://www.doxygen.jp/
- doxygen公式ホームページ マニュアル
  - http://www.doxygen.jp/manual.html
