# 概要
Javaについてのメモ(まだ何もない..)

### インストールしてみる 
```
yum install java
```
これだけだとjavacが入らないみたいなみたいなので
```
java -version
```
でjavaのバージョンをチェックしてから、JDKを取得する
```
yum install java-1.7.0-openjdk-devel
```

### HeloWorldを実行してみる。
クラスの中にmainを含める必要がある。ファイル名とクラス名は合わせる。
```
$ cat Test.java 
public class Test{
	public static void main(String[] args){
		System.out.print("hello");
	}
}
```

javacでコンパイルするとclassファイルが生成される。
```
$ javac Test.java
$ ls Test*
Test.class  Test.java
```

あとは拡張子なしで実行するクラスをjavaコマンドの後に指定する。
```
$ java Test
hello
```

