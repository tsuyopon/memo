# iOSでのSSLサイトへのアクセス

### NSURLRequestを拡張する。
NSURLRequest+SSL.hとNSURLRequest+SSL.mのファイルを準備して拡張する方法。  
AppStore申請時には削除やifdefでこれらの行が存在しないものとさせる必要あり
```
[NSURLRequest+SSL.h]
	#import <Foundation/Foundation.h>
	@interface NSURLRequest (SSL)
	+ (BOOL)allowsAnyHTTPSCertificateForHost:(NSString*)host;
	@end

[NSURLRequest+SSL.m]
	#import "NSURLRequest+SSL.h"
	 
	@implementation NSURLRequest(SSL)
	+ (BOOL)allowsAnyHTTPSCertificateForHost:(NSString *)host {
	    return YES;
	}
	@end
```
http://dev.classmethod.jp/smartphone/iphone/ios-nossl/


### iOSシミュレータに自己証明書（オレオレ証明書）をインストールする方法
- crtファイルをドラッグアンドドロップするだけのようでした。
 - http://blog.nambo.jp/2014/08/19/ios-simulator-crt/
