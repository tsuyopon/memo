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


### jps, jmap, jinfo, jstack, jmapなどを使ってみる
次のようなサンプルクラスCounterを準備してみる。
```
$ cat Counter.java 
import java.lang.*;

public class Counter
{
    public static void main(String[]args)
    {
        int i;

        for (i = 0; i <= 1000; i++)
        {
	    try {
               Thread.sleep(1000);
            } catch(InterruptedException e) {
               e.printStackTrace();
            }
        }
        System.out.println("finished.");
    }
}
```

コンパイル、実行してプロセスを表示する。
```
$ javac Counter.java
$ java Counter &
[1] 7423
$ jps
7439 Jps
7423 Counter
```

すべてのスレッドのスタックトレースを表示するにはjstackを使います。
```
$ jstack 7423
2017-03-27 08:36:37
Full thread dump OpenJDK 64-Bit Server VM (23.2-b09 mixed mode):

"Attach Listener" daemon prio=10 tid=0x00007f57e0001000 nid=0x1d24 waiting on condition [0x0000000000000000]
   java.lang.Thread.State: RUNNABLE

"Service Thread" daemon prio=10 tid=0x00007f57f8102000 nid=0x1d07 runnable [0x0000000000000000]
   java.lang.Thread.State: RUNNABLE

"C2 CompilerThread1" daemon prio=10 tid=0x00007f57f80ff800 nid=0x1d06 waiting on condition [0x0000000000000000]
   java.lang.Thread.State: RUNNABLE

"C2 CompilerThread0" daemon prio=10 tid=0x00007f57f80fd000 nid=0x1d05 waiting on condition [0x0000000000000000]
   java.lang.Thread.State: RUNNABLE

"Signal Dispatcher" daemon prio=10 tid=0x00007f57f80fb000 nid=0x1d04 runnable [0x0000000000000000]
   java.lang.Thread.State: RUNNABLE

"Finalizer" daemon prio=10 tid=0x00007f57f80a7000 nid=0x1d03 in Object.wait() [0x00007f57fd1b2000]
   java.lang.Thread.State: WAITING (on object monitor)
	at java.lang.Object.wait(Native Method)
	- waiting on <0x00000000d6605728> (a java.lang.ref.ReferenceQueue$Lock)
	at java.lang.ref.ReferenceQueue.remove(ReferenceQueue.java:135)
	- locked <0x00000000d6605728> (a java.lang.ref.ReferenceQueue$Lock)
	at java.lang.ref.ReferenceQueue.remove(ReferenceQueue.java:151)
	at java.lang.ref.Finalizer$FinalizerThread.run(Finalizer.java:177)

"Reference Handler" daemon prio=10 tid=0x00007f57f80a4800 nid=0x1d02 in Object.wait() [0x00007f57fd2b3000]
   java.lang.Thread.State: WAITING (on object monitor)
	at java.lang.Object.wait(Native Method)
	- waiting on <0x00000000d66052b0> (a java.lang.ref.Reference$Lock)
	at java.lang.Object.wait(Object.java:503)
	at java.lang.ref.Reference$ReferenceHandler.run(Reference.java:133)
	- locked <0x00000000d66052b0> (a java.lang.ref.Reference$Lock)

"main" prio=10 tid=0x00007f57f8008000 nid=0x1d00 waiting on condition [0x00007f57fe469000]
   java.lang.Thread.State: TIMED_WAITING (sleeping)
	at java.lang.Thread.sleep(Native Method)
	at Counter.main(Counter.java:12)

"VM Thread" prio=10 tid=0x00007f57f809c000 nid=0x1d01 runnable 

"VM Periodic Task Thread" prio=10 tid=0x00007f57f810d000 nid=0x1d08 waiting on condition 

JNI global references: 109
```

jmapはヒープダンプを行うツールです。
```
$ jmap 7423
Attaching to process ID 7423, please wait...
Debugger attached successfully.
Server compiler detected.
JVM version is 23.2-b09
0x0000000000400000	9K	/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/bin/java
0x0000003897600000	154K	/usr/lib64/ld-2.15.so
0x0000003897a00000	2017K	/usr/lib64/libc-2.15.so
0x0000003897e00000	141K	/usr/lib64/libpthread-2.15.so
0x0000003898200000	21K	/usr/lib64/libdl-2.15.so
0x0000003898600000	53K	/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/amd64/jli/libjli.so
0x0000003898a00000	94K	/usr/lib64/libz.so.1.2.5
0x0000003898e00000	1088K	/usr/lib64/libm-2.15.so
0x000000389b200000	87K	/usr/lib64/libgcc_s-4.7.2-20120921.so.1
0x00000038a0200000	955K	/usr/lib64/libstdc++.so.6.0.17
0x00007f57fd8fe000	32K	/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/amd64/libzip.so
0x00007f57fdb06000	61K	/usr/lib64/libnss_files-2.15.so
0x00007f57fdd28000	175K	/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/amd64/libjava.so
0x00007f57fdf54000	55K	/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/amd64/libverify.so
0x00007f57fe162000	46K	/usr/lib64/librt-2.15.so
0x00007f57fe46b000	10942K	/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/amd64/server/libjvm.so
```

jinfo は Java VM の構成情報を参照、設定するためのツールです。
```
$ jinfo 7423
Attaching to process ID 7423, please wait...
Debugger attached successfully.
Server compiler detected.
JVM version is 23.2-b09
Java System Properties:

java.runtime.name = OpenJDK Runtime Environment
java.vm.version = 23.2-b09
sun.boot.library.path = /usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/amd64
java.vendor.url = http://java.oracle.com/
java.vm.vendor = Oracle Corporation
path.separator = :
file.encoding.pkg = sun.io
java.vm.name = OpenJDK 64-Bit Server VM
sun.os.patch.level = unknown
sun.java.launcher = SUN_STANDARD
user.country = US
user.dir = /home/tsuyoshi/git/memo/JAVA
java.vm.specification.name = Java Virtual Machine Specification
java.runtime.version = 1.7.0_09-icedtea-mockbuild_2013_01_14_23_04-b00
java.awt.graphicsenv = sun.awt.X11GraphicsEnvironment
os.arch = amd64
java.endorsed.dirs = /usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/endorsed
java.io.tmpdir = /tmp
line.separator = 

java.vm.specification.vendor = Oracle Corporation
os.name = Linux
sun.jnu.encoding = ANSI_X3.4-1968
java.library.path = /usr/java/packages/lib/amd64:/usr/lib64:/lib64:/lib:/usr/lib
java.specification.name = Java Platform API Specification
java.class.version = 51.0
sun.management.compiler = HotSpot 64-Bit Tiered Compilers
os.version = 3.3.4-5.fc17.x86_64
user.home = /home/tsuyoshi
user.timezone = 
java.awt.printerjob = sun.print.PSPrinterJob
file.encoding = ANSI_X3.4-1968
java.specification.version = 1.7
user.name = tsuyoshi
java.class.path = .
java.vm.specification.version = 1.7
sun.arch.data.model = 64
sun.java.command = Counter
java.home = /usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre
user.language = en
java.specification.vendor = Oracle Corporation
awt.toolkit = sun.awt.X11.XToolkit
java.vm.info = mixed mode
java.version = 1.7.0_09-icedtea
java.ext.dirs = /usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/ext:/usr/java/packages/lib/ext
sun.boot.class.path = /usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/resources.jar:/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/rt.jar:/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/sunrsasign.jar:/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/jsse.jar:/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/jce.jar:/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/charsets.jar:/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/netx.jar:/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/plugin.jar:/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/rhino.jar:/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/lib/jfr.jar:/usr/lib/jvm/java-1.7.0-openjdk-1.7.0.9.x86_64/jre/classes
java.vendor = Oracle Corporation
file.separator = /
java.vendor.url.bug = http://bugreport.sun.com/bugreport/
sun.io.unicode.encoding = UnicodeLittle
sun.cpu.endian = little
sun.cpu.isalist = 

VM Flags:

```

jhat(Java Heap Analyzer Tool)を使います。まずはスナップショットを作ります。
```
$ jmap -dump:format=b,file=snapshot.jmap 7883
Dumping heap to /home/tsuyoshi/git/memo/JAVA/snapshot.jmap ...
Heap dump file created
$ ls snapshot.jmap 
snapshot.jmap
$ ls -alh snapshot.jmap 
-rw------- 1 tsuyoshi tsuyoshi 1.0M Mar 27 08:53 snapshot.jmap
```

jhatで作成したsnapshot.jmapを指定するとデフォルトで7000番ポートでWebサーバが起動します。
```
$ jhat snapshot.jmap
Reading from snapshot.jmap...
Dump file created Mon Mar 27 08:53:03 JST 2017
Snapshot read, resolving...
Resolving 6337 objects...
Chasing references, expect 1 dots.
Eliminating duplicate references.
Snapshot resolved.
Started HTTP server on port 7000
Server is ready.
```

次のようにしてアクセスしてヒープ状況を確認することができる。
http://localhost:7000/

