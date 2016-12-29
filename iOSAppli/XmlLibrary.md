▪️iOS標準のXMLライブラリでパースする
iOSでは標準で以下の２種類の方法が存在するようだ。
    NSXMLParser(SAX)
    Libxml2(DOM, SAX)

あまり大きなXMLをDOMでパースするのは避けておいたほうがよさそうだ。
iPhoneSDKにはXMLPerformanceというサンプルで上記２つのパフォーマンスが比較できるサンプルが
存在している。
圧倒的にlibxml2のほうが早いらしい、これは以下の違いによるらしい
	NSXMLParserはすべてのXMLダウンロードが完了してから、パースをしている。パース処理にはlibxml2を使用している。
	Libxml2はダウンロード開始次第、パースをしている。


▪️ライブラリ

標準と標準以外についてのXMLのパフォーマンスや機能比較したサイト
	http://www.raywenderlich.com/553/xml-tutorial-for-ios-how-to-choose-the-best-xml-parser-for-your-iphone-project

小さなXMLのReadだけするのならば
	TouchXML, KissXML, GDataXML 

小さなXMLのRead, Writeの両方をしたいのならば、
	KissXML, GDataXML

すごい大きなXMLをReadするのであれば、
	libxml2 SAX, TBXML, libxml DOM



TouchXMLは1年ほど更新されていない、KissXMLは3-4年ほど更新されていい、GDataXMLは7ヶ月ほど

