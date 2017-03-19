# Seleniumとは
- Selenium Core 
-- Seleniumの本体 
- Selenium IDE(Selenium Coreが既に含まれている)
-- Webブラウザから編集を可能にするFirefox拡張機能
- Selenium Remote Control
-- リモートサーバ経由からSeleniumを実施できるコンポーネント
- Selenium on Rails
-- Ruby on RailsにてSeleniumを実施できるコンポーネント
- Selenium Auto Exec Server(AES)
-- 毎日決められた時間に動作し、テスト結果をメールで報告することができるコンポーネント
- その他にも色々あります。下記URLを参照のこと
-- http://oss.infoscience.co.jp/seleniumhq/projects/index.html


# Selenium基礎知識

## 基礎概念
### コマンド呼び出しについて
- Seleniumのテストは下記３つの仕組みから成り立ちます。
-- コマンド
-- ターゲット
-- バリュー

### コマンドについて
下記３種類のコマンドがあります。
- Action
-- アプリケーションの状態を一般に操作するものです。動作に失敗するかエラーが発生した場合にはテストは中止される。
--- (例1) このリンクをクリックする
--- (例2) あのオプションを選択する
- Accessors
-- アプリケーションの状態が期待しているものと合致しているか検証するものです。また、自動的にAssertionコマンドを生成します。
- Assertion
-- 以下の３つの形式があります。
--- assert: 失敗した場合にはテストは中断される。
--- verify: 失敗した場合は、失敗はログに記録されてテストは継続実施されます。
--- waitFor: いくつかの条件が満たされることを待ちます。

各コマンドの詳細は http://wiki.openqa.org/display/SEL/Selenium+0.7+Reference+%28Japanese%29 を参考にしてください。

### ターゲットで指定可能な機能
- Elemenet Locator
-- Seleniumにおいて、コマンドが参照するhtml要素を特定するものです。
--- identifier, id, name, dom, xpath, link
- Element Filter
-- 候補となる要素を絞りこむためにElementLocatorと一緒に使用することができます。 
--- value, index
- 文字列マッチングパターン
-- 文字列のマッチングとしてパターン構文が利用可能です。
--- glob, regexp, exact

### バリューについて
- バリューはコマンドの第２引数として利用されることが多いです。
- コマンドによってはバリューは指定不要な場合もあります。

# Seleniumコマンドについて

### Yahoo Japanのトップページを開いて検索ボックスにあるワードを入力するサンプル

このサンプルは入力の簡単なテストを行います。
- 1.Yahoo Japanトップページを開きます。
- 2.プロンプトからトップページの検索ボックスに入力すべき文字列を促されます。
- 3.プロンプトで入力した文字を検索し、その検索結果ページを表示します。

サンプルは以下、
```
	 <?xml version="1.0" encoding="UTF-8"?>
	 <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
	 <html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
	 <head profile="http://selenium-ide.openqa.org/profiles/test-case">
	 <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
	 <link rel="selenium.base" href="http://www.yahoo.co.jp/" />
	 <title>New Test</title>
	 </head>
	 <body>
	 <table cellpadding="1" cellspacing="1" border="1">
	 <thead>
	 <tr><td rowspan="1" colspan="3">New Test</td></tr>
	 </thead><tbody>
	 <!-- Yahoo Japanトップページを開きます。-->
	 <tr>
	    <td>open</td>
	    <td>/</td>
	    <td></td>
	 </tr>
	 <!--プロンプト表示からの入力を促し、storevarという変数に格納します。-->
	 <tr>
	    <td>store</td>
	    <td>javascript{var ret=prompt('enter searchbox', '');ret}</td>
	    <td>storevar</td>
	 </tr>
	 <!--pというパラメータに先ほどプロンプトから入力したstorevar値を格納しています。-->
	 <tr>
	    <td>type</td>
	    <td>p</td>
	    <td>javascript{storedVars['storevar']}</td>
	 </tr>
	 <!--検索結果ページを取得します。クリックすべき箇所をXPathで指定しています。-->
	 <tr>
	    <td>clickAndWait</td>
	    <td>//input[@value=&quot;検索&quot;]</td>
	    <td></td>
	 </tr>
	 
	 </tbody></table>
	 </body>
	 </html>
```

### 現在表示されているページに「ヘルプ」という文字列があるかどうかを検証する場合
```
	 <tr>
	     <td>assertTextPresent</td>
	     <td>//</td>
	     <td>ヘルプ</td>
	 </tr>
```

### リンクURLを調べたい場合
```
	 <tr>
	    <td>verifyText</td>
	    <td>//a[@href='http://this.web.site/index.html</td>
	    <td>著作権について</td>
	 </tr>
```

### xpathにてリンクをチェックしたいような場合
```
	 <tr>
	     <td>linkCheck</td>
	     <td>xpath=/html/body/div/div[2]/div[3]/a</td>
	     <td>http://this.web.site/index.html</td>
	 </tr>
```

### 正規表現を利用してチェックしたい場合
```
	 <tr>
	     <td>verifyText</td>
	     <td><div flag="?">*</div></td>
	     <td></td>
	 </tr>
```
- 「*」や「?」には下記の意味があります。
-  *は任意の複数の文字にマッチします
-  ?は1文字にマッチします

### 画像のキャプチャーを取得する
```
 <tr>
 	<td>open</td>
 	<td>/</td>
 	<td></td>
 </tr>
 <tr>
 	<td>captureEntirePageScreenshot</td>
 	<td>C:\Documents and Settings\path\to\My Documents\selenium\capture.jpg</td>
 	<td></td>
 </tr>
```

# 参考URL
- Selenium マニュアル(英語)  
-- http://seleniumhq.org/docs/
- Selenium 日本語ドキュメント  
-- http://oss.infoscience.co.jp/seleniumhq/docs/index.html
- Selenium IDE ドキュメント  
-- http://oss.infoscience.co.jp/seleniumhq/docs/03_selenium_ide.html
- Selenium コマンド ドキュメント  
-- http://oss.infoscience.co.jp/seleniumhq/docs/04_selenese_commands.html
- Selenium IDE firefox addon  
-- https://addons.mozilla.org/ja/firefox/addon/2079
- Selenium リファレンスガイド（日本語版）  
-- http://wiki.openqa.org/display/SEL/Selenium+0.7+Reference+%28Japanese%29

