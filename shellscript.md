# シェルスクリプト関連のメモ
よく忘れてしまって検索で引っかかりにくい特殊変数などに関するメモ

以下のリファレンスが超絶役に立つので何かあればこちらを参考するとよさそう
 - http://shellscript.sunone.me/

# メモ 


### 準変数
書式と意味が次の通り
```
${VAR:-expression} 	    値がセットされていない(NULL)場合、:-以降の式を評価結果を返す。
${VAR:+expression} 	    値がセットされている(NONE-NULL)場合、:+以降の式を評価結果を返す。
${VAR:=expression} 	    値がセットされていない(NULL)場合、:=以降の式を評価結果を返し変数に代入。
${VAR:?[expression]}    値がセットされていない(NULL)場合、式が標準エラーに出力。
```

サンプルは次の通り
```
#!/bin/sh
 
echo "[ null variable ]"
VAR=
EXPAND=${VAR:-blue}
echo "-var    : $VAR"
echo "-expand : $EXPAND"
EXPAND=${VAR:+yellow}
echo "+var    : $VAR"
echo "+expand : $EXPAND"
EXPAND=${VAR:=green}
echo "=var    : $VAR"
echo "=expand : $EXPAND"
echo ""
echo "[ non-null variable ]"
VAR=red
EXPAND=${VAR:-blue}
echo "-var    : $VAR"
echo "-expand : $EXPAND"
EXPAND=${VAR:+yellow}
echo "+var    : $VAR"
echo "+expand : $EXPAND"
EXPAND=${VAR:=green}
echo "=var    : $VAR"
echo "=expand : $EXPAND"
exit 0
```

実行結果は次の通り
```
$ ./var.sh
[ null variable ]
-var    :
-expand : blue
+var    :
+expand :
=var    : green
=expand : green
 
[ non-null variable ]
-var    : red
-expand : red
+var    : red
+expand : yellow
=var    : red
=expand : red
```

この辺も参考にすると良い
- http://shellscript.sunone.me/variable.html#%E5%A4%89%E6%95%B0%E3%81%AE%E7%89%B9%E6%AE%8A%E3%81%AA%E5%8F%82%E7%85%A7%E6%96%B9%E6%B3%95

上記サイトでは以下の違いについて詳細に説明している。
```
${VAR=aaa}
${VAR:=aaa}
${VAR-aaa}
${VAR:-aaa}
${VAR+aaa}
${VAR:+aaa}
```

### 特殊記号

<table>
    <tr>
        <td>$?</td>
        <td>直前に実行されたコマンドの終了ステータスが設定される変数</td>
    </tr>
    <tr>
        <td>$!</td>
        <td>バックグラウンドで実行されたコマンドのプロセスID が設定される変数</td>
    </tr>
    <tr>
        <td>$-</td>
        <td>set コマンドで設定されたフラグ、もしくはシェルの起動時に指定されたフラグの一覧が設定される変数。「abc」ならば「-abc」が指定されたことになる</td>
    </tr>
    <tr>
        <td>$$</td>
        <td>コマンド自身の PID (プロセスID)が設定される変数</td>
    </tr>
    <tr>
        <td>$#</td>
        <td>シェル変数の数</td>
    </tr>
    <tr>
        <td>$@</td>
        <td>実行時に指定された引数の数が設定される変数。"$@"とダブルクォートで囲むと"$1" "$2" ...と等価。</td>
    </tr>
    <tr>
        <td>$*</td>
        <td>シェルスクリプト実行時、もしくは set コマンド実行時に指定された全パラメータが設定される変数。"$*"とダブルクォートで囲むと"$1 $2 ... $n"と等価。IFS環境変数で区切り文字を指定可能</td>
    </tr>
    <tr>
        <td>$LINENO</td>
        <td>この変数を使用している行の行番号が設定される変数</td>
    </tr>
    <tr>
        <td>${PIPESTATUS[@]}</td>
        <td>パイプで連結した各コマンドの終了ステータスが設定される変数(配列)</td>
    </tr>
    <tr>
        <td>$0</td>
        <td>実行したシェルスクリプト名が設定される。</td>
    </tr>
    <tr>
        <td>$1から$9、${10}から${100}</td>
        <td>N番目の引数。10以上はカッコで囲む必要がある。</td>
    </tr>
</table>

### 環境変数
<table>
    <tr>
        <td>$PS1</td>
        <td>プロンプトに使用される文字列が設定されている環境変数</td>
    </tr>
    <tr>
        <td>$PS2</td>
        <td>コマンドが複数行にわたった場合のプロンプトに使用される文字列が設定されている環境変数</td>
    </tr>
    <tr>
        <td>$PATH</td>
        <td>コマンドが格納されているディレクトリのパスが設定されている環境変数</td>
    </tr>
    <tr>
        <td>$TZ</td>
        <td>タイムゾーンが設定されている環境変数</td>
    </tr>
    <tr>
        <td>$PWD</td>
        <td>カレントディレクトリのパスが設定されている環境変数</td>
    </tr>
    <tr>
        <td>$IFS</td>
        <td>デリミタ(区切り文字)として使用される値が設定されている環境変数。デフォルトではタブ、スペース、改行が設定されている。for 文の値リストの区切りや、read コマンドで読み込む値の区切りなどに使用される。</td>
    </tr>
</table>

### 数値比較
```
-eq 	test num1 -eq num2 	        num1 と num2 が等しければ真となる(num1=num2)
-ne 	test num1 -ne num2 	        num1 と num2 が等しくなければ真となる(num1≠num2)
-lt 	test num1 -lt num2 	        num1 が num2 より小ならば真となる(num1<num2)
-le 	test num1 -le num2 	        num1 が num2 以下ならば真となる(num1≦num2)
-gt 	test num1 -gt num2 	        num1 が num2 より大ならば真となる(num1>num2)
-ge 	test num1 -ge num2 	        num1 が num2 以上ならば真となる(num1≧num2)
```

- 参考
 - http://shellscript.sunone.me/if_and_test.html


### ファイルが新しいか古いかでの評価
```
オプション  使用例                         オプションの意味
-nt         test ファイル1 -nt ファイル2   ファイル1 is newer than ファイル2
-ot         test ファイル1 -ot ファイル2   ファイル1 is older than ファイル2
```


### testコマンドによるファイルや文字列の評価
```
オプション  使用例             オプションの意味
-z 	        test -z string     string の文字列長が 0 ならば真となる。
-n 	        test -n string     string の文字列長が 0 より大ならば真となる。
-d 	        test -d file       file がディレクトリならば真となる。
-f 	        test -f file       file が普通のファイルならば真となる。
-s 	        test -s file       file が 0 より大きいサイズならば真となる。
-e 	        test -e file       file が存在するならば真となる。
-r 	        test -r file       file が読み取り可能ならば真となる。
-w 	        test -w file       file が書き込み可能ならば真となる。
-x 	        test -x file       file が実行可能ならば真となる。
```




- 参考
 - http://shellscript.sunone.me/if_and_test.html

### 計算

```
x=10
echo $x # 10
echo $x+2 # 10+2
echo `expr $x + 2` # 12
echo `expr \($x + 5\) \* 2` # 30 

readonly y=20
y=25 # y: readonly variableというエラーが出る
```

ポイントは次の通り
- 計算したい時は`(バッククォート)を使う
- 数値として展開したい変数の前にexprを使う。（この時計算する四則演算記号の前後にスペースを入れる）
- 掛け算やカッコを使う場合は \* のように、記号の前にバックスラッシュが必要（エスケープ）
- readonly とすると変数の上書きができなくなる


$(())も利用することができるようです。
```
// $(())も利用することができる。
$ echo $(( (x + 5) * 2 ))
30
```


- 参考: http://qiita.com/katsukii/items/383b241209fe96eae6e7

### オプション解析
オプションの使い方としては次の通りでdは値を取り、aとhは値を取りません。
```
usage_exit() {
        echo "Usage: $0 [-a] [-d dir] item ..." 1>&2
        exit 1
}

while getopts ad:h OPT
do
    case $OPT in
        a)  FLAG_A=1
            ;;
        d)  VALUE_D=$OPTARG
            ;;
        h)  usage_exit
            ;;
        \?) usage_exit
            ;;
    esac
done
```

getoptは外部コマンドのため、バージョンや環境によって差異があります。それが、BSD 系と GNU 系の違いです。
- http://qiita.com/b4b4r07/items/dcd6be0bb9c9185475bb

### ユーザーからの入力
readで読み込みを行う。
```
while : 
do
    read key
    echo "you pressed $key"
    if [ $key = "end" ]; then
        break
    fi
done
```

### 選択しで選ばせたい場合
```
select option in CODE DIE
do
    echo "you pressed $option"
    break;
done
```

こうすると次のように表示され、数字で選択することができる。
```
1) CODE
2) DIE
#? 1
you pressed CODE
```

### ファイルから読み込ませる
引数にファイル名を指定して読み込ませるには次のようにすれば良い。
```
i=1
while read line
do
    echo "$i: $line"
    i=`expr $i + 1`
done <$1
```

### 配列
ループして実行する場合
```
a=(1 2 3 4 5)
for i in ${a[@]}
do
    echo $i
done
```

- http://shellscript.sunone.me/array.html



### 変数の解釈関連
- http://shellscript.sunone.me/variable.html

${VAR}とか


## テクニック

### ステータス情報の退避
次のようにしておけば、$?のコマンドステータスが他のコマンドを実行する前に退避しておくことが可能である。
```
echo "$var" | grep -sq "hoge"; CMDRESULT=$?
if [ $CMDRESULT -eq 0 ]; then
	echo "hoge が見つかりました。"
fi
```


### スクリプト自身のパスを知る
```
BASEDIR=$(cd $(/usr/bin/dirname $0); pwd)
```

### 変数がNULLかどうかのチェック
変数が null だった場合、以下の条件式ではエラーになります。
```
if [ $answer = yes ]; then
```
これは $answer がから文字列だった場合、 if [ = yes ]; then と評価されエラーになります。 ではダブルクォーテーションで囲めばよいのか？
```
if [ "$answer" = yes ]; then
```

実はこれでもまだ安全ではありません。もし $answer が -f だった場合 if [ -f = yes ]; then となりエラーと判断されるかもしれません。
最も安全場記述方法は以下のように確実に文字列として評価されるように記述することです。
```
if [ x"$answer" = xyes ]; then
```


### "[]"と"[[]]"の違いについて

動作上の違いとして次の違いがある。
```
$ unset hoge
$ [ $hoge = "HOGE" ]
-bash: [: =: unary operator expected
$ [[ $hoge = "HOGE" ]]
$
```

加えて終了ステータスにも次の違いがある。
```
$ [ $hoge = "HOGE" ]
-bash: [: =: unary operator expected
$ echo $?
2
$ [[ $hoge = "HOGE" ]]
$ echo $?
1
```

変数展開後の条件式が「= “HOGE”」となるため [] の場合にはエラーメッセージが出力されている。
一方で [[ ]] ではエラーメッセージは表示されないのでこの辺は使い分けると良いかも



## デバッグ


### -v

### -xオプションで実行したら、その時の変数の値なども同時に出力する
bashの場合には-xオプションによってコマンド実行時の変数の値なども出力することができる。
```
#!/bin/bash -x
# ↑ここで「-x」オプションを指定する。(bashであることに注意!!)

var1=`date +%M`
var2=`ls -1 | wc -l`

if [ $var1 -ge 30 ]; then
  var3="BIG"
else
  var3="SMALL"
fi

exit 0
```

実行すると結果は次のようになる。
```
$ ./script.sh
++ date +%M
+ var1=47
++ ls -1
++ wc -l
+ var2=26
+ '[' 47 -ge 30 ']'
+ var3=BIG
+ exit 0
```
	

# 参考URL
- UNIX&LINUXコマンド・シェルスクリプトリファレンス
 - 今後もリファレンスとして非常によさそう
 - http://shellscript.sunone.me/debug.html
- シェルスクリプトの基礎知識まとめ
 - http://qiita.com/katsukii/items/383b241209fe96eae6e7
- UNIX&LINUXコマンド・シェルスクリプトリファレンス
 - http://shellscript.sunone.me/variable.html

