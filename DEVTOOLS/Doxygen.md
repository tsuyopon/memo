# 概要
DoxygenはC++、C、Java、Objective-C、Python、IDL (Corba、Microsoft 風)、Fortran、VHDL、PHP、C#に用途のあったドキュメンテーションシステムです。
以下の特徴があります。
- 仕様書を作成する無駄を省くことができます
- HTML形式、LATEX形式を生成することができます
- Graphvizと連携してグラフを描画することができます


# 詳細
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

## doxygen記法

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

### グラフ機能について
graphvizツールと連携して提供される、グラフ機能はC++でしか利用できません。
この場合には、設定ファイルで HAVE_DOT を YES に設定します。
また、設定ファイルで以下の各種オプションが設定できます。
GRAPHICAL_HIERARCHY が YES に設定されていれば、 クラス階層のグラフ表現が、テキストによる表現とともに、描画されます。 現在、この機能は HTML に対してのみサポートされています。
CLASS_GRAPH が YES に設定されていれば、 ドキュメント付けされた各クラスについて、直接および間接的な継承関係を 示すグラフが生成されます。これは、ビルトインのクラス継承図生成機能を 無効にします。 
INCLUDE_GRAPH が YES に設定されていれば、 ドキュメント付けされ、少なくとも他の1つのファイルをインクルードしている ファイルについて、インクルードの依存関係のグラフが生成されます。 
COLLABORATION_GRAPH が YES に設定されていれば、 ドキュメント付けされたクラスや構造体について、 以下のことを示すグラフが描画されます: 
基底クラスとの継承関係。 
他の構造体やクラスとの利用関係 (たとえば、クラス A がクラス B 型のメンバー変数 m_a を保持していれば、 A は、m_a というラベルの付いた、B に向かう矢印を持ちます)。 

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
  - http://www.doxygen.jp/
- doxygen公式ホームページ マニュアル
  - http://www.doxygen.jp/manual.html
