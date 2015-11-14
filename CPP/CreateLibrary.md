# 共有ライブラリとスタティックライブラリの生成方法について
ライブラリには以下の２種類が存在します。
- 共有ライブラリ
 - 共有ライブラリ
  - プログラムの実行時にロードされます。共有ライブラリが無かったりすると動作がしないという欠点があります。
  - 拡張子は.soや.saで終わります。
 - ダイナミックライブラリ
  - 共有ライブラリの一種です。モジュールのロード位置に依存しないコードですので、gcc で -fPIC オプションをつけてコンパイルします。
- スタティックライブラリ
 - 全てのコードがコンパイル時に組み込まれます。このため、ファイルサイズが大きくなりますが、リンク間の依存関係という大きな問題がなくなるメリットがあります。
 - 拡張子は.aとなります。


## 共有ライブラリ(ダイナミックライブラリ)

### 利用方法
lオプションでリンク先を指定します。libxxxx.soを指定する場合には以下のように指定します。
```
 $ gcc sample.c -o sample -lxxxx 
```

### 作成方法
```
 $ gcc -fPIC -c xxx.c                                       // -fPICをつけるとダイナミックライブラリらしい...
 $ gcc -shared -Wl,-soname,libxxx.so.1 -o libxxx.so.1.0 xxx.o  // sharedオプションがポイント!!
 # cp libxxx.so.1.0 /usr/lib
 # /sbin/ldconfig /usr/lib
 # ln -s /usr/lib/libxxx.so.1 /usr/lib/libxxx.so
```


## スタティックライブラリ [#u546371f]

### 利用方法
```
 $ gcc sample.c -o sample /usr/lib/libxxxx.a
```

### 作成方法
以下はスタティックライブラリ作成の際の手順になります。
```
 $ ar rv libxxx.a xxx.o
 $ ranlib libxxx.a
 $ strip libxxx.a
```

- 上記コマンドに関する説明をします。
 - スタティックライブラリは、ar コマンドで作成します
 - ranlib コマンドは、 BSD系のUNIX で使われており、各ライブラリの先頭に __.SYMDEF というメンバを 追加します。これによりリンクが高速になります。
 - strip コマンドは、オブジェクトファイルの中のsymbol table を削除します

# 参考URL
- ライブラリの基礎知識
 - http://www.hi-ho.ne.jp/babaq/linux/libtips.html
- gcc -fPICについて
 - http://cheesy.dip.jp/blog/butcher/2006/02/post_1.html
