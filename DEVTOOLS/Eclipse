*** 参考URL
- エクリプス
-- http://www.eclipsewiki.net/eclipse/
- Javaの道
-- http://www.javaroad.jp/opensource/js_eclipse1.htm
- TIPS
-- http://www.h7.dion.ne.jp/~s_wat/eclipse/eclipsetips.html


#####################################################################
Eclipseショートカット
#####################################################################

*** ソースコード読解操作 [#z4474fa2]
- F3
-- カーソル位置のクラス、インタフェース、変数等の宣言場所へ移動
-- 尚、元の位置に戻るには「Alt + ←」を押下します。進むには「Alt + →」が利用できます。
- F4
-- カーソル位置のクラスの継承関係を表示
- Ctrl + Space
-- 変数やメソッドを補完する(コンテンツアシスト)
- Ctrl + O
-- カーソル位置のクラスのメソッド一覧を表示
- Ctrl + T
-- カーソル位置がメソッドにあり、そのメソッドのinterfaceでなくimplementsの方を閲覧したい場合に押下する。尚、interfaceが見たい場合にはF3で閲覧できる。
- Ctrl+Alt+H
-- メソッド等の使用箇所を表示する

*** カーソル操作 [#x3187987]
- Ctrl + D
-- 現在の行や選択された行を削除

*** パースペクティブ移動 [#hf16bc5f]
- Ctrl + F8
-- 前のパースペクティブ(DDMS, Java, Debug等の移動)
- Ctrl + Shift + F8
-- 次のパースペクティブ(DDMS, Java, Debug等の移動)

*** メソッド移動 [#n244bb61]
- Ctrl + ↓
-- 次のメソッド
- Ctrl +  Shift + ↑
-- 前のメソッド

*** デバッグ [#w2817269]
- Shift + Alt + X
-- 実行形式を選択(Run As)
- Shift + Alt + D
-- デバッグ形式を選択(Debug As)

*** 便利技 [#l80d953e]
- Ctrl + Shift + O
-- 必要なライブラリをimportしてくれます
- Ctrl + Shift + L
-- ショートカット一覧を表示する
- Ctrl + E
-- 開いているウィンドウ一覧(タブになっているところ)を切り替えできます
- Ctrl + /
-- Javaの場合などに行頭にコメント(//)を付与したり、削除したりを切り替えできます

*** 参考URL [#nfc48232]
- ニートになりたいプログラマ
-- http://fukata.org/2010/05/30/useful-eclipse-keyboard-shortcut-java/
- Eclipseコマンドリファレンス
-- http://www.geocities.jp/turtle_wide/tools/eclipse/cmd_index.htm

#####################################################################
.projectファイルについて
#####################################################################
* 概要 [#ne4ed227]
SVNでプロジェクトをチェックアウトを行い、それをEclipseにプロジェクトを取り込もうとした場合に「JAVAプロジェクト」と認識させることはできません。

.projectファイルを配置することにより、この問題点を解決することができます。
.projectファイルは、プロジェクト直下のルートディレクトリ直下に設置されるファイルです。

* 詳細 [#of37df50]

** サンプル [#g9195580]
 <?xml version="1.0" encoding="UTF-8"?>
 <projectDescription>
     <name>testtest</name><!-- プロジェクト名称 -->
     <comment></comment><!-- プロジェクトコメント -->
     <projects>
     </projects>
     <buildSpec>
         <buildCommand>
             <name>org.eclipse.jdt.core.javabuilder</name>
             <arguments>
             </arguments><!-- プロジェクトビルダーに引き渡す引数 -->
         </buildCommand>
     </buildSpec>
     <natures><!-- nature一覧を記載 -->
         <nature>org.eclipse.jdt.core.javanature</nature>
         <nature>com.google.appengine.eclipse.core.gaeNature</nature>
         <nature>com.google.gdt.eclipse.core.webAppNature</nature>
     </natures>
 </projectDescription>

COLOR(blue):上記で示した以外にも様々な要素があります。

* 参考URL [#b11eb411]
- Eclipse公式ドキュメント(英語)
-- http://dsdp.eclipse.org/help/latest/index.jsp?topic=%2Forg.eclipse.platform.doc.isv%2Freference%2Fmisc%2Fproject_description_file.html






#####################################################################

#####################################################################
