# 概要
iozoneはファイルシステムのためのベンチマークです。

# 詳細

### インストール
```
#cd /tmp
#wget http://www.iozone.org/src/current/iozone3_263.tar
#tar xvf iozone3_263.tar
#cd src/current
#make linux     <=ここはターゲットを指定する。makeと打つとターゲット一覧が表示される。
```

以上により/tmp/iozone3_263/src/currentディレクトリ内にiozoneという実行 ファイルが作成される。
```
<使い方>
オプション 意味 
-R           Excelのファイルを出力 
-a           自動テストモード 
-b           出力ファイルの名前を指定 
-i 数字  	 テストの内容を指定 
  0               write/rewrite 
  1  		 read/re-read 
  2    		 random-read/write 
  3  		 Read-backwards 
  4		 Re-write-record 
  5  		 stride-read 
  6   		 fwrite/re-fwrite 
  7  		 fread/Re-fread 
  8  		 random mix 
  9  		 pwrite/Re-pwrite 
 10  		 pread/Re-pread 
 11 		 pwritev/Re-pwritev 
 12 		 preadv/Repreadv 
```

- 例1:自動モードでテストを行う。
```
$ ./iozone -a
```
- 例2:読み込み、読み込みのテストを行う。
```
$ ./iozone -i 0 -i 1
```
